#include "callbacks.h"

#include <iostream>

double zoom = 1.0;
double center[2] = { 400, 300};
double dim[2] = { 400, 300 };
double leftTop[2] = { 0, 0 };
double rightBottom[2] = { 800, 600 };
static double xClick = 0.0;
static double yClick = 0.0;

void mouseButtonCallback(GLFWwindow* pWindow, int button, int action, int mods)
{
	double xPos, yPos;
	glfwGetCursorPos(pWindow, &xPos, &yPos);
	if (GLFW_PRESS == action)
	{
		if ((GLFW_MOUSE_BUTTON_LEFT == button) || (GLFW_MOUSE_BUTTON_RIGHT == button))
		{
			xClick = xPos;
			yClick = yPos;
		}
	}

	if (GLFW_RELEASE == action)
	{
		if ((xClick != xPos) || (yClick != yPos))
		{
			leftTop[0] += zoom * (xPos - xClick);
			rightBottom[0] += zoom * (xPos - xClick);
			leftTop[1] -= zoom * (yPos - yClick);
			rightBottom[1] -= zoom * (yPos - yClick);
			center[0] = (leftTop[0] + rightBottom[0]) / 2;
			center[1] = (leftTop[1] + rightBottom[1]) / 2;
		}
		else if (GLFW_MOUSE_BUTTON_LEFT == button)
		{
			double zoomOld = zoom;
			zoom = zoom * 0.9;
			dim[0] = (rightBottom[0] - leftTop[0]) * 0.9;
			dim[1] = (rightBottom[1] - leftTop[1]) * 0.9;
			leftTop[0] += dim[0] / 2;
			leftTop[1] += dim[1] / 2;
			rightBottom[0] -= dim[0] / 2;
			rightBottom[1] -= dim[1] / 2;
			center[0] = (leftTop[0] + rightBottom[0]) / 2;
			center[1] = (leftTop[1] + rightBottom[1]) / 2;
			/*
			double mOld = (xPos - center[0]) * zoomOld;
			double nOld = (yPos - center[1]) * zoomOld;

			center[0] = xPos + (zoomOld / zoom) * (center[0] - xPos);
			center[1] = yPos + (zoomOld / zoom) * (center[1] - yPos);
			double m = (xPos - center[0]) * zoom;
			double n = (yPos - center[1]) * zoom; 
			double t = 1;
			std::cout << "Test" << std::endl;
			*/
		}
		else if (GLFW_MOUSE_BUTTON_RIGHT == button)
		{
			double zoomOld = zoom;
			zoom = zoom * 1.1;
			dim[0] = (rightBottom[0] - leftTop[0]) * 1.1;
			dim[1] = (rightBottom[1] - leftTop[1]) * 1.1;
			leftTop[0] -= dim[0] / 2;
			leftTop[1] -= dim[1] / 2;
			rightBottom[0] += dim[0] / 2;
			rightBottom[1] += dim[1] / 2;
			center[0] = (leftTop[0] + rightBottom[0]) / 2;
			center[1] = (leftTop[1] + rightBottom[1]) / 2;
			/*
			double mOld = (xPos - center[0]) * zoomOld;
			double nOld = (yPos - center[1]) * zoomOld;

			center[0] = xPos + (zoomOld / zoom) * (center[0] - xPos);
			center[1] = yPos + (zoomOld / zoom) * (center[1] - yPos);
			double m = (xPos - center[0]) * zoom;
			double n = (yPos - center[1]) * zoom;
			double t = 1;
			*/
		}
	}

}