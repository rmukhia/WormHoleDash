// canvas.cpp
//
// This program allows the user to draw simple shapes on a canvas.
//
// Interaction:
// Left click on a box on the left to select a primitive.
// Then left click on the drawing area: once for point, twice for line or rectangle.
// Right click for menu options.
//
//  Sumanta Guha.
////////////////////////////////////////////////////////////////////////////////////

/* Raunak Mukhia, assignment 3 question 2*/

#include <cstdlib>
#include <vector>
#include <iostream>
#include <cmath>

#include <GL/glew.h>
#include <GL/freeglut.h>

#define NUMBERPRIMITIVES 6
// Value of PI
#define PI 3.14159265358979324

enum {
	SHP_INACTIVE,
	SHP_POINT,
	SHP_LINE,
	SHP_RECTANGLE,
	SHP_POLYLINE,
	SHP_CIRCLE,
	SHP_PENTAGON,
};

// Globals.
static int width, height; // OpenGL window size.
static float pointSize = 3.0; // Size of point
static int primitive = SHP_INACTIVE; // Current drawing primitive.
static int pointCount = 0; // Number of  specified points.
static int tempX, tempY; // Co-ordinates of clicked point.
static int isGrid = 1; // Is there grid?

// Vertices class
class Vert {
public:
	float x;
	float y;
	float z;
	Vert() {

	}
	Vert(float a, float b, float c) {
		x = a;
		y = b;
		z = c;
	}
	Vert operator=(const Vert &b) {
		Vert v;
		v.x = b.x;
		v.y = b.y;
		v.z = b.z;
		return v;
	}
};

// Parent class of all shapes
class Shape {
public:
	virtual void draw() = 0;
	void setTemp(bool v) { isTemp = v; }
private:
	bool isTemp = false;
protected:
	void setColor() {
		// Use red for temporary shapes and black for permenant shapes
		if (isTemp) glColor3f(1.0, 0.0, 0.0);
		else glColor3f(0.0, 0.0, 0.0);

	}
};

// The current shape being drawn
Shape *curr_shape = NULL;

void drawShape() {
	if (curr_shape) curr_shape->draw();
}

// Point class.
class Point: public Shape
{
public:
	Point(float xVal, float yVal, float sizeVal)
	{
		x = xVal; y = yVal; size = sizeVal;
	}
	Point() {};
	void draw(void); // Function to draw a point.
private:
	float x, y; // x and y co-ordinates of point.
	float size; // Size of point.
};

//float Point::size = pointSize; // Set point size.

// Function to draw a point.
void Point::draw()
{
	glPointSize(size);
	glBegin(GL_POINTS);
	glVertex3f(x, y, 0.0);
	glEnd();
}

// Vector of points.
std::vector<Point> points;

// Iterator to traverse a Point array.
std::vector<Point>::iterator pointsIterator;

// Function to draw all points in the points array.
void drawPoints(void)
{
	// Loop through the points array drawing each point.
	for (auto point : points) { point.draw(); }
}

// Line class.
class Line: public Shape
{
public:
	Line(float x1Val, float y1Val, float x2Val, float y2Val)
	{
		x1 = x1Val; y1 = y1Val; x2 = x2Val; y2 = y2Val;
	}
	Line() {};
	void draw();
private:
    float x1, y1, x2, y2; // x and y co-ordinates of endpoints.
};


// Function to draw a line.
void Line::draw()
{
	glBegin(GL_LINES);
	setColor();
	glVertex3f(x1, y1, 0.0);
	glVertex3f(x2, y2, 0.0);
	glEnd();
}

// Vector of lines.
std::vector<Line> lines;

// Function to draw all lines in the lines array.
void drawLines(void)
{
	// Loop through the lines array drawing each line.
	for (auto line : lines) { line.draw(); }
}


// Rectangle class.
class Rect: public Shape
{
public:
	Rect(float x1Val, float y1Val, float x2Val, float y2Val)
	{
		x1 = x1Val; y1 = y1Val; x2 = x2Val; y2 = y2Val;
	}
	Rect() {};
	void draw();
private:
    float x1, y1, x2, y2; // x and y co-ordinates of diagonally opposite vertices.
};

// Function to draw a rectangle.
void Rect::draw()
{
	setColor();
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glRectf(x1, y1, x2, y2);
}

// Vector of rectangles.
std::vector<Rect> rectangles;

// Function to draw all rectangles in the rectangles array.
void drawRectangles(void)
{
	// Loop through the rectangles array drawing each rectangle.
	for (auto rectangle : rectangles) { rectangle.draw(); }
}


// Polyline class.
class PolyLine: public Shape
{
public:
	PolyLine(std::vector<Vert> v)
	{
		vertices = v;
	}
	PolyLine() {};
	void draw();
private:
	std::vector<Vert> vertices; // vertices in a polyline
};

// Function to draw a polyline.
void PolyLine::draw()
{
	setColor();
	glBegin(GL_LINE_STRIP);
	for (auto v : vertices) { glVertex3f(v.x, v.y, v.z);}
	glEnd();
}

// Vector of polylines.
std::vector<PolyLine> polylines;

// Function to draw all polylines in the polylines array.
void drawPolylines(void)
{
	// Loop through the polylines array drawing each polyline.
	for (auto polyline : polylines) { polyline.draw(); }
}

std::vector<Vert> temp_vertices; // temporary vertices
void drawTempVertices() {
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(pointSize);
	if (primitive == SHP_POLYLINE && pointCount >= 1) {
		glBegin(GL_POINTS);
		for (size_t i = 0; i < temp_vertices.size(); i++) {
			glVertex3f(temp_vertices[i].x, temp_vertices[i].y, temp_vertices[i].z);
		}
		glEnd();
	}
}

// Circle class.
class Circ: public Shape
{
public:
	Circ(float x1Val, float y1Val, float x2Val, float y2Val)
	{
		x1 = x1Val; y1 = y1Val; x2 = x2Val; y2 = y2Val;
		radius = pow(pow(x2 - x1, 2) + pow(y2 - y1, 2), 0.5);
	}
	Circ() {};
	void draw();
private:
    float x1, y1, x2, y2; // x and y co-ordinates of centre and a point on the perimeter
	float radius;
};

void drawCircleG(float x, float y, float z, float radius) {
	int num_vertices = 24;
	float theta = 2 * (float)PI / num_vertices;
	glBegin(GL_LINE_LOOP);
	float t = 0;
	for (int i = 0; i < num_vertices; i++) {
		glVertex3f(x + radius * sin(t), y + radius * cos(t), 0);
		t += theta;
	}
	glEnd();
}

// Function to draw a circle.
void Circ::draw()
{
	setColor();
	drawCircleG(x1, y1, 0, radius);
}

// Vector of circles.
std::vector<Circ> circles;

// Function to draw all circles in the circles array.
void drawCircles(void)
{
	// Loop through the circles array drawing each circle.
	for (auto circle : circles) { circle.draw(); }
}

class Pent: public Shape
{
public:
	Pent(float x1Val, float y1Val, float x2Val, float y2Val)
	{
		x1 = x1Val; y1 = y1Val; x2 = x2Val; y2 = y2Val;
		radius = pow(pow(x2 - x1, 2) + pow(y2 - y1, 2), 0.5);
		initialAngle = atan2(x2 - x1, y2 - y1);
	}
	Pent() {};
	void draw();
private:
    float x1, y1, x2, y2; // x and y co-ordinates of centre and a point on the perimeter
	float radius;
	float initialAngle; // The angle offset
};

void drawPentagonG(float x, float y, float z, float radius, float initialAngle) {
	int num_vertices = 5;
	float theta = 2 * PI / num_vertices;
	glBegin(GL_LINE_LOOP);
	float t = 0;
	t = initialAngle;
	for (int i = 0; i < num_vertices; i++) {
		glVertex3f(x + radius * sin(t), y + radius * cos(t), 0);
		t += theta;
	}
	glEnd();
}

// Function to draw a circle.
void Pent::draw()
{
	setColor();
	drawPentagonG(x1, y1, 0, radius, initialAngle);
}

// Vector of circles.
std::vector<Pent> pentagons;

// Function to draw all circles in the circles array.
void drawPentagons(void)
{
	// Loop through the circles array drawing each circle.
	for (auto pentagon : pentagons) { pentagon.draw(); }
}


// Function to draw point selection box in left selection area.
void drawPointSelectionBox(void)
{
	if (primitive == SHP_POINT) glColor3f(1.0, 1.0, 1.0); // Highlight.
	else glColor3f(0.8, 0.8, 0.8); // No highlight.
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glRectf(0.0, 0.9*height, 0.1*width, height);

	// Draw black boundary.
	glColor3f(0.0, 0.0, 0.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glRectf(0.0, 0.9*height, 0.1*width, height);

	// Draw point icon.
	glPointSize(pointSize);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POINTS);
	glVertex3f(0.05*width, 0.95*height, 0.0);
	glEnd();
}

// Function to draw line selection box in left selection area.
void drawLineSelectionBox(void)
{
	if (primitive == SHP_LINE) glColor3f(1.0, 1.0, 1.0); // Highlight.
	else glColor3f(0.8, 0.8, 0.8); // No highlight.
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glRectf(0.0, 0.8*height, 0.1*width, 0.9*height);

	// Draw black boundary.
	glColor3f(0.0, 0.0, 0.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glRectf(0.0, 0.8*height, 0.1*width, 0.9*height);

	// Draw line icon.
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(0.025*width, 0.825*height, 0.0);
	glVertex3f(0.075*width, 0.875*height, 0.0);
	glEnd();
}

// Function to draw rectangle selection box in left selection area.
void drawRectangleSelectionBox(void)
{
	if (primitive == SHP_RECTANGLE) glColor3f(1.0, 1.0, 1.0); // Highlight.
	else glColor3f(0.8, 0.8, 0.8); // No highlight.
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glRectf(0.0, 0.7*height, 0.1*width, 0.8*height);

	// Draw black boundary.
	glColor3f(0.0, 0.0, 0.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glRectf(0.0, 0.7*height, 0.1*width, 0.8*height);

	// Draw rectangle icon.
	// glColor3f(0.0, 0.0, 0.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glRectf(0.025 * width, 0.72*height, 0.075*width, 0.78*height);
}

// Function to draw PolyLine selection box in left selection area.
void drawPolyLineSelectionBox(void)
{
	if (primitive == SHP_POLYLINE) glColor3f(1.0, 1.0, 1.0); // Highlight.
	else glColor3f(0.8, 0.8, 0.8); // No highlight.
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glRectf(0.0, 0.6*height, 0.1*width, 0.7*height);

	// Draw black boundary.
	glColor3f(0.0, 0.0, 0.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glRectf(0.0, 0.6*height, 0.1*width, 0.7*height);

	// Draw polyline icon.
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(0.025*width, 0.625*height, 0.0);
	glVertex3f(0.075*width, 0.675*height, 0.0);
	glVertex3f(0.075*width, 0.625*height, 0.0);
	glVertex3f(0.04*width, 0.66*height, 0.0);
	glEnd();
}

// Function to draw Circle selection box in left selection area.
void drawCircleSelectionBox(void)
{
	if (primitive == SHP_CIRCLE) glColor3f(1.0, 1.0, 1.0); // Highlight.
	else glColor3f(0.8, 0.8, 0.8); // No highlight.
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glRectf(0.0, 0.5*height, 0.1*width, 0.6*height);

	// Draw black boundary.
	glColor3f(0.0, 0.0, 0.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glRectf(0.0, 0.5*height, 0.1*width, 0.6*height);

	// Draw circle icon.
	glColor3f(0.0, 0.0, 0.0);
	//drawCircleG(0.05 * width, 0.55 * height, 0.0, 20.0);
	//glEnd();
	//glBegin(GL_LINE_STRIP);
	//glVertex3f(0.05*width, 0.55*height, 0.0);
	//glVertex3f(0.09*width, 0.59*height, 0.0);
	//glEnd();
	drawCircleG(0.05 * width, 0.55 * height, 0.0,
		pow(pow(0.07 * width - 0.05 * width,2) + pow(0.57 * height - 0.55 * height, 2), 0.5));
}

// Function to draw Pentagon selection box in left selection area.
void drawPentagonSelectionBox(void)
{
	if (primitive == SHP_PENTAGON) glColor3f(1.0, 1.0, 1.0); // Highlight.
	else glColor3f(0.8, 0.8, 0.8); // No highlight.
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glRectf(0.0, 0.4*height, 0.1*width, 0.5*height);

	// Draw black boundary.
	glColor3f(0.0, 0.0, 0.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glRectf(0.0, 0.4*height, 0.1*width, 0.5*height);

	// Draw circle icon.
	glColor3f(0.0, 0.0, 0.0);
	//drawCircleG(0.05 * width, 0.55 * height, 0.0, 20.0);
	//glEnd();
	//glBegin(GL_LINE_STRIP);
	//glVertex3f(0.05*width, 0.55*height, 0.0);
	//glVertex3f(0.09*width, 0.59*height, 0.0);
	//glEnd();
	drawPentagonG(0.05 * width, 0.45 * height, 0.0,
		pow(pow(0.07 * width - 0.05 * width,2) + pow(0.47 * height - 0.45 * height, 2), 0.5),
		0);
}

// Function to draw unused part of left selection area.
void drawInactiveArea(void)
{
	glColor3f(0.6, 0.6, 0.6);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glRectf(0.0, 0.0, 0.1*width, (1 - NUMBERPRIMITIVES*0.1)*height);

	glColor3f(0.0, 0.0, 0.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glRectf(0.0, 0.0, 0.1*width, (1 - NUMBERPRIMITIVES*0.1)*height);
}

// Function to draw temporary point.
void drawTempPoint(void)
{
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(pointSize);
	glBegin(GL_POINTS);
	glVertex3f(tempX, tempY, 0.0);
	glEnd();
}

// Function to draw a grid.
void drawGrid(void)
{
	int i;

	glEnable(GL_LINE_STIPPLE);
	glLineStipple(1, 0x5555);
	glColor3f(0.75, 0.75, 0.75);

	glBegin(GL_LINES);
	for (i = 2; i <= 9; i++)
	{
		glVertex3f(i*0.1*width, 0.0, 0.0);
		glVertex3f(i*0.1*width, height, 0.0);
	}
	for (i = 1; i <= 9; i++)
	{
		glVertex3f(0.1*width, i*0.1*height, 0.0);
		glVertex3f(width, i*0.1*height, 0.0);
	}
	glEnd();
	glDisable(GL_LINE_STIPPLE);
}

// Drawing routine.
void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);

	drawPointSelectionBox();
	drawLineSelectionBox();
	drawRectangleSelectionBox();
	drawPolyLineSelectionBox();
	drawCircleSelectionBox();
	drawPentagonSelectionBox();
	drawInactiveArea();

	drawPoints();
	drawLines();
	drawRectangles();
	drawPolylines();
	drawCircles();
	drawPentagons();

	// Draw temporary shape
	drawShape();

	if (((primitive == SHP_LINE) || (primitive == SHP_RECTANGLE) ||
		(primitive == SHP_CIRCLE) || (primitive == SHP_PENTAGON)) &&
		(pointCount == 1)) drawTempPoint();

	if ((primitive == SHP_POLYLINE) && (pointCount >= 1)) drawTempVertices();
	if (isGrid) drawGrid();

	glutSwapBuffers();
}

// Function to pick primitive if click is in left selection area.
void pickPrimitive(int y)
{
	if (y < (1 - NUMBERPRIMITIVES*0.1)*height) primitive = SHP_INACTIVE;
	else if (y < (1 - 5 * 0.1)*height) primitive = SHP_PENTAGON;
	else if (y < (1 - 4 * 0.1)*height) primitive = SHP_CIRCLE;
	else if (y < (1 - 3 * 0.1)*height) primitive = SHP_POLYLINE;
	else if (y < (1 - 2 * 0.1)*height) primitive = SHP_RECTANGLE;
	else if (y < (1 - 1 * 0.1)*height) primitive = SHP_LINE;
	else primitive = SHP_POINT;
}

// The mouse callback routine.
void mouseControl(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		y = height - y; // Correct from mouse to OpenGL co-ordinates.

		if (x < 0 || x > width || y < 0 || y > height); // Click outside canvas - do nothing.

		// Click in left selection area.
		else if (x < 0.1*width)
		{
			pickPrimitive(y);
			pointCount = 0;
		}

		// Click in canvas.
		else
		{
			if (primitive == SHP_POINT) points.push_back(Point(x, y, pointSize));
			else if (primitive == SHP_LINE)
			{
				if (pointCount == 0)
				{
					tempX = x; tempY = y;
					pointCount++;
				}
				else
				{
					lines.push_back(Line(tempX, tempY, x, y));
					pointCount = 0;
					delete curr_shape;
					curr_shape = NULL;
				}
			}
			else if (primitive == SHP_RECTANGLE)
			{
				if (pointCount == 0)
				{
					tempX = x; tempY = y;
					pointCount++;
				}
				else
				{
					rectangles.push_back(Rect(tempX, tempY, x, y));
					pointCount = 0;
					delete curr_shape;
					curr_shape = NULL;
				}
			}
			else if (primitive == SHP_CIRCLE)
			{
				if (pointCount == 0)
				{
					tempX = x; tempY = y;
					pointCount++;
				}
				else
				{
					circles.push_back(Circ(tempX, tempY, x, y));
					pointCount = 0;
					delete curr_shape;
					curr_shape = NULL;
				}
			}
			else if (primitive == SHP_PENTAGON)
			{
				if (pointCount == 0)
				{
					tempX = x; tempY = y;
					pointCount++;
				}
				else
				{
					pentagons.push_back(Pent(tempX, tempY, x, y));
					pointCount = 0;
					delete curr_shape;
					curr_shape = NULL;
				}
			}
			else if (primitive == SHP_POLYLINE)
			{
				// Add new point
				temp_vertices.push_back(Vert(x, y, 0));
				pointCount++;
			}
		}
	}

	else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
		pointCount = 0;
		polylines.push_back(PolyLine(temp_vertices));
		temp_vertices.clear();
		delete curr_shape;
		curr_shape = NULL;
	}
	glutPostRedisplay();
}

void mouseMotion(int x, int y)
{
	if (pointCount >= 1) {
		y = height - y; // Correct from mouse to OpenGL co-ordinates.
		// We have started a shape, track it
		// Update the current shape for each mouse movement.
		std::vector<Vert> vt = temp_vertices;
		switch (primitive) {
		case SHP_LINE:
			if (!curr_shape) delete curr_shape;
			curr_shape = new Line(tempX, tempY, x, y);
			curr_shape->setTemp(true);
			break;
		case SHP_RECTANGLE:
			if (!curr_shape) delete curr_shape;
			curr_shape = new Rect(tempX, tempY, x, y);
			curr_shape->setTemp(true);
			break;
		case SHP_POLYLINE:
			if (!curr_shape) delete curr_shape;
			vt.push_back(Vert(x, y, 0));
			curr_shape = new PolyLine(vt);
			curr_shape->setTemp(true);
			break;
		case SHP_CIRCLE:
			if (!curr_shape) delete curr_shape;
			curr_shape = new Circ(tempX, tempY, x, y);
			curr_shape->setTemp(true);
			break;
		case SHP_PENTAGON:
			if (!curr_shape) delete curr_shape;
			curr_shape = new Pent(tempX, tempY, x, y);
			curr_shape->setTemp(true);
			break;
		default:
			break;
		};
		glutPostRedisplay();
	}

}

// OpenGL window reshape routine.
void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set viewing box dimensions equal to window dimensions.
	glOrtho(0.0, (float)w, 0.0, (float)h, -1.0, 1.0);

	// Pass the size of the OpenGL window to globals.
	width = w;
	height = h;

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(0);
		break;
	case 'd':
	case 'D':
		// Clear on right click
		pointCount = 0;
		temp_vertices.clear();
		delete curr_shape;
		curr_shape = NULL;
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

// Clear the canvas and reset for fresh drawing.
void clearAll(void)
{
	points.clear();
	lines.clear();
	rectangles.clear();
	polylines.clear();
	circles.clear();
	pentagons.clear();

	temp_vertices.clear();
	primitive = SHP_INACTIVE;
	pointCount = 0;

	if (curr_shape) {
		delete curr_shape;
		curr_shape = NULL;
	}
}

// The right button menu callback function.
void rightMenu(int id)
{
	if (id == 1)
	{
		clearAll();
		glutPostRedisplay();
	}
	if (id == 2) exit(0);
}

// The sub-menu callback function.
void grid_menu(int id)
{
	if (id == 3) isGrid = 1;
	if (id == 4) isGrid = 0;
	glutPostRedisplay();
}

// Function to create menu.
void makeMenu(void)
{
	int sub_menu;
	sub_menu = glutCreateMenu(grid_menu);
	glutAddMenuEntry("On", 3);
	glutAddMenuEntry("Off", 4);

	glutCreateMenu(rightMenu);
	glutAddSubMenu("Grid", sub_menu);
	glutAddMenuEntry("Clear", 1);
	glutAddMenuEntry("Quit", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

// Initialization routine.
void setup(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);

	makeMenu(); // Create menu.
}

// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
	std::cout << "Interaction:" << std::endl;
	std::cout << "Left click on a box on the left to select a primitive." << std::endl
		<< "Then left click on the drawing area: once for point, twice for line, rectangle, circle or pentagon." << std::endl
		<< "Middle click to end a polyline." << std::endl
		<< "Right click for menu options." << std::endl
		<< "To discard the current shape being drawn, press d/D." << std::endl;
}

// Main routine.
int main(int argc, char **argv)
{
	printInteraction();
	glutInit(&argc, argv);

	glutInitContextVersion(4, 2);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("RaunakMukhiAssign3Q2.cpp");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);
	glutMouseFunc(mouseControl);
	glutPassiveMotionFunc(mouseMotion);

	glewExperimental = GL_TRUE;
	glewInit();

	setup();

	glutMainLoop();
}
