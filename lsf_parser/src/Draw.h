/*
 * Draw.h
 *
 *  Created on: Oct 11, 2012
 *      Author: ster
 */

#ifndef DRAW_H_
#define DRAW_H_

#include "cgf/CGFobject.h"
#include <iostream>
#include <string>

using namespace std;
/*
 *
 */
class Draw: public CGFobject
{
public:
  Draw();
  virtual
  ~Draw();
  void draw(string primitive);
};

#endif /* DRAW_H_ */
