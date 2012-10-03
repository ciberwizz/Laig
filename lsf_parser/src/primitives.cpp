/*
 * primitives.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: ei06054
 */

#include "primitives.h"
#include <sstream>
using namespace std;

//ESFERA
Sphere::Sphere(double r, int sl, int st)
{
	radius = r;
	slices = sl;
	stacks = st;
}

Sphere::Sphere(elem* el){
	stringstream ss;

	ss << el->attr["radius"];

	ss >> this->radius;

	ss << el->attr["slices"];
	ss >> this->slices;

	ss << el->attr["stacks"];
	ss >> this->stacks;
}

double Sphere::getRadius() const
{
	return radius;
}

int Sphere::getSlices() const
{
	return slices;
}

int Sphere::getStacks() const
{
	return stacks;
}

void Sphere::setRadius(double r)
{
	radius = r;
}

void Sphere::setSlices(int sl)
{
	slices = sl;
}

void Sphere::setStacks(int st)
{
	stacks = st;
}

void Sphere::draw()
{
	GLUquadricObj *quadratic;               // Storage For Our Quadratic Objects
	quadratic = gluNewQuadric();

//	glBegin(GL_QUADS);
	gluSphere(quadratic, 2, 30, 30);
//	glEnd();
}

//CILINDRO
Cylinder::Cylinder(double br, double tr, double ht, int sl, int st)
{
	baseRadius = br;
	topRadius = tr;
	height = ht;
	slices = sl;
	stacks = st;
}

double Cylinder::getBaseradius() const
{
	return baseRadius;
}

double Cylinder::getTopradius() const
{
	return topRadius;
}
double Cylinder::getHeight() const
{
	return height;
}
int Cylinder::getSlices() const
{
	return slices;
}

int Cylinder::getStacks() const
{
	return stacks;
}

void Cylinder::setTopradius(double tr)
{
	topRadius = tr;
}

void Cylinder::setBaseradius(double br)
{
	baseRadius = br;
}

void Cylinder::setHeight(double ht)
{
	height = ht;
}

void Cylinder::setSlices(int sl)
{
	slices = sl;
}

void Cylinder::setStacks(int st)
{
	stacks = st;
}

void Cylinder::draw()
{
	glBegin(GL_QUADS);

	glEnd();
}

//RECTANGULO
Rectangle::Rectangle(double x_1, double y_1, double x_2, double y_2)
{
	x1 = x_1;
	x2 = x_2;
	y1 = y_1;
	y2 = y_2;
}

double Rectangle::getX1() const
{
	return x1;
}

double Rectangle::getX2() const
{
	return x2;
}

double Rectangle::getY1() const
{
	return y1;
}

double Rectangle::getY2() const
{
	return y2;
}

void Rectangle::setX1(double x_1)
{
	x1 = x_1;
}

void Rectangle::setX2(double x_2)
{
	x2 = x_2;
}

void Rectangle::setY1(double y_1)
{
	y1 = y_1;
}

void Rectangle::setY2(double y_2)
{
	y2 = y_2;
}

void Rectangle::draw()
{
	glBegin(GL_QUADS);

	glEnd();
}

//TRIANGULO
Triangle::Triangle(double x_1, double y_1, double z_1, double x_2, double y_2, double z_2,
		double x_3, double y_3, double z_3)
{
	x1 = x_1;
	x2 = x_2;
	x3 = x_3;
	y1 = y_1;
	y2 = y_2;
	y3 = y_3;
	z1 = z_1;
	z2 = z_2;
	z3 = z_3;
}

double Triangle::getX1() const
{
	return x1;
}

double Triangle::getX2() const
{
	return x2;
}

double Triangle::getX3() const
{
	return x3;
}

double Triangle::getY1() const
{
	return y1;
}

double Triangle::getY2() const
{
	return y2;
}

void Triangle::setX1(double x_1)
{
	x1 = x_1;
}

void Triangle::setX2(double x_2)
{
	x2 = x_2;
}

void Triangle::setX3(double x_3)
{
	x3 = x_3;
}

void Triangle::setY1(double y_1)
{
	y1 = y_1;
}

void Triangle::setY2(double y_2)
{
	y2 = y_2;
}

void Triangle::setY3(double y_3)
{
	y3 = y_3;
}

void Triangle::setZ1(double z_1)
{
	z1 = z_1;
}

void Triangle::setZ2(double z_2)
{
	z2 = z_2;
}

void Triangle::setZ3(double z_3)
{
	z3 = z_3;
}

void Triangle::draw()
{
	glBegin(GL_QUADS);

	glEnd();
}
//TORUS
Torus::Torus(double inR, double outR, int sl, int lp)
{
	innerRadius = inR;
	outerRadius = outR;
	slices = sl;
	loops = lp;
}

double Torus::getInnerRadius() const
{
	return innerRadius;
}

double Torus::getOuterRadius() const
{
	return outerRadius;
}

int Torus::getSlices() const
{
	return slices;
}

int Torus::getLoops() const
{
	return loops;
}

void Torus::setInnerRadius(double inR)
{
	innerRadius = inR;
}

void Torus::setOuterRadius(double outR)
{
	outerRadius = outR;
}

void Torus::setSlices(int sl)
{
	slices = sl;
}

void Torus::setLoops(int lp)
{
	loops = lp;
}

void Torus::draw()
{
	glBegin(GL_QUADS);

	glEnd();
}
