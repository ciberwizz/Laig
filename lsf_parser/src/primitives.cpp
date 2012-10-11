/*
 * primitives.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: ei06054
 */

#include "primitives.h"
#include <cmath>
#include <sstream>
using namespace std;



double* multMatrix(double* m1, double* m2){
	double *mf = new double[16];


	for(int i=0; i< 4; i++){
		for(int j = 0; j < 4; j++)
			mf[i+j*4] = m1[i]*m2[0+j*4] + m1[i+4]*m2[1+j*4] + m1[i+2*4]*m2[2+j*4] + m1[i+3*4]*m2[3+j*4];
	}

	for(int j = 0; j < 16 ; j++)
		m1[j] = mf[j];

	return m1;

}

double* createMatrixTranslate(double x, double y, double z){
	double *mat = new double[16];
	for( int i = 0 ; i < 16; i++){
		if( i%5 == 0)
			mat[i] = 1;
		else
			switch(i) {
			case 12:
				mat[i] = x;
				break;
			case 13:
				mat[i] = y;
				break;
			case 14:
				mat[i] = z;
				break;
			default:
				mat[i]=0.0;
				break;
			}
	}

	return mat;

}

double* createMatrixScale(double x, double y, double z){
	double *mat = new double[16];
	for( int i = 0 ; i < 16; i++){

		switch(i) {
		case 0:
			mat[i] = x;
			break;
		case 5:
			mat[i] = y;
			break;
		case 10:
			mat[i] = z;
			break;
		case 15:
			mat[i] = 1.0;
			break;
		default:
			mat[i]=0.0;
			break;
		}
	}

	return mat;

}


double* createMatrixRotate(string eixo,double rot){
	//M_PI -  180
	//x    -   ang
	double rad = M_PI*rot/180;
	double *mat = new double[16];
	for( int i = 0 ; i < 16; i++){
		if( i%5 == 0)
			mat[i] = 1.0;
		else
			mat[i]=0.0;
	}

	switch(eixo[0]) {
	case 'x':
		/*
		 * 1 0 0 0
		 * 0 cos(rad) -sin(rad) 0
		 * 0 sin(rad) cos(rad) 0
		 * 0 0 0 1
		 */

		mat[5] = cos(rad);
		mat[6] = sin(rad);
		mat[9] = -sin(rad);
		mat[10] = cos(rad);
		break;
	case 'y':
		/*
		 * cos(rad) 0 sin(rad) 0
		 * 0 1 0 0
		 * -sin(rad) 0 cos(rad) 0
		 * 0 0 0 1
		 */

		mat[0] = cos(rad);
		mat[2] = -sin(rad);
		mat[8] = sin(rad);
		mat[10] = cos(rad);
		break;
	case 'z':
		/*
		 * cos(rad) -sin(rad) 0 0
		 * sin(rad) cos(rad) 0 0
		 * 0 0 1 0 0
		 * 0 0 0 0 1
		 */

		mat[0] = cos(rad);
		mat[1] = sin(rad);
		mat[4] = -sin(rad);
		mat[5] = cos(rad);
		break;
	}


	return mat;

}

double* createIdentityMatrix(double* mat){
	for( int i = 0; i < 16 ; i++){
		mat[i] = (i%5 == 0? 1.0 : 0.0);
	}

	return mat;
}


//ESFERA
Sphere::Sphere(double r, int sl, int st)
{

	radius = r;
	slices = sl;
	stacks = st;
	createIdentityMatrix(transformation);
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
//transdormation functions
void Sphere::translate(double x, double y, double z){
	double *mat = createMatrixTranslate(x,y,z);
	multMatrix( this->transformation, mat);
	delete mat;
}
void Sphere::scale(double x, double y, double z){
	double *mat = createMatrixScale(x,y,z);
	multMatrix( this->transformation, mat);
	delete mat;
}
void Sphere::rotate(string eixo, double ang){
 	double *mat = createMatrixRotate(eixo,ang);
	multMatrix( this->transformation, mat);
	delete mat;
}

void Sphere::draw()
{
  GLUquadricObj *quadratic;               // Storage For Our Quadratic Objects
  quadratic = gluNewQuadric();


	glMultMatrixd(transformation);
  gluSphere(quadratic, radius, slices, stacks);
  glEnd();

}

//CILINDRO
Cylinder::Cylinder(double br, double tr, double ht, int sl, int st)
{

	baseRadius = br;
	topRadius = tr;
	height = ht;
	slices = sl;
	stacks = st;
	createIdentityMatrix(transformation);
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

//transdormation functions
void Cylinder::translate(double x, double y, double z){
	double *mat = createMatrixTranslate(x,y,z);
	multMatrix( this->transformation, mat);
	delete mat;
}

void Cylinder::scale(double x, double y, double z){
	double *mat = createMatrixScale(x,y,z);
	multMatrix( this->transformation, mat);
	delete mat;
}

void Cylinder::rotate(string eixo, double ang){
	double *mat = createMatrixRotate(eixo,ang);
	multMatrix( this->transformation, mat);
	delete mat;
}

void Cylinder::draw()
{

  GLUquadricObj *quadratic;               // Storage For Our Quadratic Objects
  quadratic = gluNewQuadric();


  glBegin(GL_QUADS);
	glMultMatrixd(transformation);
  gluCylinder(quadratic, baseRadius, topRadius, height, slices, stacks);
  glEnd();
}

//RECTANGULO
Rectangle::Rectangle(double x_1, double y_1, double x_2, double y_2)
{

	x1 = x_1;
	x2 = x_2;
	y1 = y_1;
	y2 = y_2;
	createIdentityMatrix(transformation);
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

//transdormation functions
void Rectangle::translate(double x, double y, double z){
	double *mat = createMatrixTranslate(x,y,z);
	multMatrix( this->transformation, mat);
	delete mat;
}

void Rectangle::scale(double x, double y, double z){
	double *mat = createMatrixScale(x,y,z);
	multMatrix( this->transformation, mat);
	delete mat;
}

void Rectangle::rotate(string eixo, double ang){
	double *mat = createMatrixRotate(eixo,ang);
	multMatrix( this->transformation, mat);
	delete mat;

}

void Rectangle::draw()
{
  GLUquadricObj *quadratic;               // Storage For Our Quadratic Objects
  quadratic = gluNewQuadric();


  glBegin(GL_QUADS);
	glMultMatrixd(transformation);
  glVertex3d(x1,y1,0);
  glVertex3d(x1,y2,0);
  glVertex3d(x2,y2,0);
  glVertex3d(x2,y1,0);
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
	createIdentityMatrix(transformation);
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

//transdormation functions
void Triangle::translate(double x, double y, double z){
	double *mat = createMatrixTranslate(x,y,z);
	multMatrix( this->transformation, mat);
	delete mat;
}

void Triangle::scale(double x, double y, double z){
	double *mat = createMatrixScale(x,y,z);
	multMatrix( this->transformation, mat);
	delete mat;
}

void Triangle::rotate(string eixo, double ang){
	double *mat = createMatrixRotate(eixo,ang);
	multMatrix( this->transformation, mat);
	delete mat;
}

void Triangle::draw()
{
  glBegin(GL_QUADS);
	glMultMatrixd(transformation);
  glVertex3d(x1,y1,z1);
  glVertex3d(x2,y2,z2);
  glVertex3d(x3,y3,z3);
  glEnd();

}
//TORUS
Torus::Torus(double inR, double outR, int sl, int lp)
{

	innerRadius = inR;
	outerRadius = outR;
	slices = sl;
	loops = lp;
	createIdentityMatrix(transformation);
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

//transdormation functions
void Torus::translate(double x, double y, double z){
	double *mat = createMatrixTranslate(x,y,z);
	multMatrix( this->transformation, mat);
	delete mat;
}

void Torus::scale(double x, double y, double z){
	double *mat = createMatrixScale(x,y,z);
	multMatrix( this->transformation, mat);
	delete mat;
}

void Torus::rotate(string eixo, double ang){
	double *mat = createMatrixRotate(eixo,ang);
	multMatrix( this->transformation, mat);
	delete mat;
}

void Torus::draw()
{

  glBegin(GL_QUADS);
	glMultMatrixd(transformation);
  glutSolidTorus(innerRadius,outerRadius,slices,loops);
  glEnd();

}
