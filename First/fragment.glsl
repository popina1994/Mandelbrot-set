#version 450 core

out vec4 outColor;

const double MAND_THRESHOLD = 2;
const int MAX_IT = 100;

vec4 mapToColor(float t)
{
	return vec4(t, t, t, 1);
}

double mandelbroNumItRatio(dvec2 c)
{
	double itMax = MAX_IT, x, y;
	dvec2 z = dvec2(0, 0);
	int i;
	
	for (i = 0; i < itMax; i++) {
		x = z.x * z.x - z.y * z.y + c.x;
		y = 2 * z.y * z.x + c.y;
		if ((x * x + y * y) > MAND_THRESHOLD) break;
		z.x = x;
		z.y = y;
	}
	return i / itMax;
}

void main()
{
	double itNum, zoom = 1.0;
	dvec2 center;
	dvec2 c, z, screen_size;
	screen_size.x = 1920;
	screen_size.y = 1080;
	double screen_ratio = screen_size.x / screen_size.y;
	center.x = 0;
	center.y = 0;
	c.x = screen_ratio * (gl_FragCoord.x / screen_size.x - 0.5);
	c.y = (gl_FragCoord.y / screen_size.y - 0.5);
	c.x += center.x;
	c.y += center.y;

	itNum = mandelbroNumItRatio(c);
	outColor = mapToColor(float(itNum));
};

/*
void main()
{
	dvec2 z, c;
	c.x = screen_ratio * (gl_FragCoord.x / screen_size.x - 0.5);
	c.y = (gl_FragCoord.y / screen_size.y - 0.5);

	c.x /= zoom;
	c.y /= zoom;

	c.x += center.x;
	c.y += 1;

	int i;
	for (i = 0; i < itNum; i++) {
		double x = (z.x * z.x - z.y * z.y) + c.x;
		double y = (z.y * z.x + z.x * z.y) + c.y;

		if ((x * x + y * y) > 2.0) break;
		z.x = x;
		z.y = y;
	}

	double t = double(i) / double(itNum);

	outColor = map_to_color(float(t));
}
*/

