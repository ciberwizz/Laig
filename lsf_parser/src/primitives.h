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

using namespace std;
//! Classe Sphere
/*!
  Criacao de Esferas
 */
class Sphere {
private:
  double radius;
  int slices;
  int stacks;
public:
  /*!
   * Construtor Sphere
   */
  Sphere();
  /*!
   * Construtor Sphere
   *
   * \param double r
   * \param int sl
   * \param int st
   *
   */
  Sphere(double r, int sl, int st);
  //! Retorna o raio da esfera
  /*!
   * \return radius
   */
  double getRadius();
  int getSlices();
  int getStacks();

  void setRadius(double r);
  void setSlices(int sl);
  void setStacks(int st);

}


//! Classe Sphere
/*!
  Criacao de Esferas
 */
class Cylinder {
private:
  double baseRadius;
  double topRadius
  double height;
  int slices;
  int stacks;
public:
  /*!
   * Construtor Cylinder
   */
  Cylinder();
  Cylinder(double br, double tr, double ht, int sl, int st);

  double getBaseradius();
  double getTopradius();
  double getHeight();
  int getSlices();
  int getStacks();

  void setTopradius(double tr);
  void setBaseradius(double br);
  void setHeight(double ht);
  void setSlices(int sl);
  void setStacks(int st);

}

class Rectangle {
private:
  double x1,y1,x2,y2;

public:
  /*!
   * Construtor Rectangle
   */
  Rectangle();
  Rectangle(double x_1, double y_1, double x_2, double y_2);

  void setX1();
  void setY1();
  void setX2();
  void setY2();

}

class Triangle {
private:
  double x1,y1,z1,x2,y2,z2,x3,y3,z3;

public:
  /*!
   * Construtor Rectangle
   */
  Rectangle();
  Rectangle(double x_1, double y_1, double z_1, double x_2, double y_2, double z_2,
  double x_3, double y_3, double z_3);

  void setX1();
  void setY1();
  void setZ1()
  void setX2();
  void setY2();
  void setZ2();
  void setX3();
  void setY3();
  void setZ3();

}



#endif /* PRIMITIVES_H_ */
