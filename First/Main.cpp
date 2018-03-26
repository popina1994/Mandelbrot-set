#include <iostream>
#include <fstream>
#include <cstring>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#include "utils.h"
#include "CompilerShaderVertex.h"
#include "CompilerShaderFragment.h"
#include "LinkerShader.h"

// Window dimensions
constexpr GLuint WIDTH = 1920;
constexpr GLuint HEIGHT = 1080;

// Shaders
const char* VERTEX_SOURCE_PATH = "vertex.glsl";
const char* FRAGMENT_SOURCE_PATH = "fragment.glsl";

// The MAIN function, from here we start the application and run the game loop
int main()
{
	FILE *stream;
	freopen_s(&stream, "log.txt", "w", stderr);
	// Init GLFW
	glfwInit();
	atexit(glfwTerminate);

	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "The Mandelbrot Set", nullptr, nullptr);
	if (nullptr == window)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return EXIT_FAILURE;
	}
	glfwMakeContextCurrent(window);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (GLEW_OK != glewInit())
	{
		std::cerr << "Failed to initialize GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
	// Define the viewport dimensions
	glViewport(0, 0, screenWidth, screenHeight);

	CompilerShaderVertex compilerVertexShader(VERTEX_SOURCE_PATH);
	CompilerShaderFragment compilerFragmentShader(FRAGMENT_SOURCE_PATH);
	if (!compilerVertexShader.Success() || !compilerFragmentShader.Success())
	{
		return EXIT_FAILURE;
	}
	
	LinkerShader linkerShader({ &compilerVertexShader, &compilerFragmentShader });
	if (!linkerShader.Success())
	{
		return EXIT_FAILURE;
	}

	// Set up vertex data (and buffer(s)) and attribute pointers
	GLfloat vertices[] =
	{
		-0.5f, -0.5f, 0.0f, // Left
		0.5f, -0.5f, 0.0f, // Right
		0.0f,  0.5f, 0.0f  // Top
	};

	GLfloat colorData[] = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	};


	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colorData), colorData, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(1);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)


	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw our first triangle
		glUseProgram(linkerShader.Handle());
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 4);
		glBindVertexArray(0);

		// Swap the screen buffers
		glfwSwapBuffers(window);
	}

	// Properly de-allocate all resources once they've outlived their purpose
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	return EXIT_SUCCESS;
}


