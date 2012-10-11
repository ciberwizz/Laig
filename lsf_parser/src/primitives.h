/*
 * primitives.h
 *
 *  Created on: Sep 26, 2012
 *      Author: ei06054
 */

#ifndef PRIMITIVES_H_
#define PRIMITIVES_H_

#include <iostream>
#include <string>
#include "cgf/CGFobject.h"
#include "parser.h"

using namespace std;

//matrix operations
double* multMatrix(double*, double*);
double* createMatrixTranslate(double, double, double);
double* createMatrixScale(double, double, double);
double* createMatrixRotate(string,double);
double* createIdentityMatrix(double*);

//! Classe Sphere
/*!
  Criacao de Esferas
 */
class Sphere: public CGFobject {
private:
	double transformation[16];
  double radius;
  int slices;
  int stacks;
public:
  /*!
   * Construtor Sphere
   */
  Sphere(){};

  /*!
   * Construtor Sphere
   *
   * \param double r
   * \param int sl
   * \param int st
   *
   */
  Sphere(double r, int sl, int st);

  /*
   * recebe uma struct elem..
   */
  Sphere(elem*);


  //! Retorna o raio da esfera
  /*!
   * \return radius
   */
  double getRadius() const;
  int getSlices() const;
  int getStacks() const;

  void setRadius(double);
  void setSlices(int);
  void setStacks(int);

  //transdormation functions
  void translate(double, double, double);
  void scale(double, double, double);
  void rotate(string,double);

  void draw();

};


//! Classe Cylinder
/*!
  Criacao de Cilindros
 */
class Cylinder: public CGFobject {
private:
	double transformation[16];
  double baseRadius;
  double topRadius;
  double height;
  int slices;
  int stacks;
public:
  /*!
   * Construtor Cylinder
   */
  Cylinder();
  Cylinder(double br, double tr, double ht, int sl, int st);

  double getBaseradius() const;
  double getTopradius() const;
  double getHeight() const;
  int getSlices() const;
  int getStacks() const;

  void setTopradius(double);
  void setBaseradius(double);
  void setHeight(double);
  void setSlices(int);
  void setStacks(int);

  //transdormation functions
  void translate(double, double, double);
  void scale(double, double, double);
  void rotate(string,double);

  void draw();

};

class Rectangle: public CGFobject {
private:
	double transformation[16];
  double x1,y1,x2,y2;

public:
  /*!
   * Construtor Rectangle
   */
  Rectangle();
  Rectangle(double x_1, double y_1, double x_2, double y_2);

  double getX1() const;
  double getY1() const;
  double getX2() const;
  double getY2() const;

  void setX1(double);
  void setY1(double);
  void setX2(double);
  void setY2(double);

  //transdormation functions
  void translate(double, double, double);
  void scale(double, double, double);
  void rotate(string,double);

  void draw();

};

class Triangle: public CGFobject {
private:
	double transformation[16];
  double x1,y1,z1,x2,y2,z2,x3,y3,z3;

public:
  /*!
   * Construtor Triangle
   */
  Triangle();
  Triangle(double x_1, double y_1, double z_1, double x_2, double y_2, double z_2,
      double x_3, double y_3, double z_3);

  double getX1() const;
  double getY1() const;
  double getZ1() const;
  double getX2() const;
  double getY2() const;
  double getZ2() const;
  double getX3() const;
  double getY3() const;
  double getZ3() const;

  void setX1(double);
  void setY1(double);
  void setZ1(double);
  void setX2(double);
  void setY2(double);
  void setZ2(double);
  void setX3(double);
  void setY3(double);
  void setZ3(double);

  //transdormation functions
  void translate(double, double, double);
  void scale(double, double, double);
  void rotate(string,double);

  void draw();

};

//! Classe Torus
/*!
  Criacao de Donuts
 */
class Torus: public CGFobject {
private:
	double transformation[16];
  double innerRadius;
  double outerRadius;
  int slices;
  int loops;
public:
  /*!
   * Construtor Torus
   */
  Torus();
  /*!
   * Construtor Torus
   *
   * \param double inR
   * \param double outR
   * \param int sl
   * \param int lp
   *
   */
  Torus(double inR, double outR, int sl, int lp);

  double getInnerRadius() const;
  double getOuterRadius() const;
  int getSlices() const;
  int getLoops() const;

  void setInnerRadius(double);
  void setOuterRadius(double);
  void setSlices(int);
  void setLoops(int);

  //transdormation functions
  void translate(double, double, double);
  void scale(double, double, double);
  void rotate(string,double);

  void draw();

};

#endif /* PRIMITIVES_H_ */
