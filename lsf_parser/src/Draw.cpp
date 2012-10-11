/*
 * Draw.cpp
 *
 *  Created on: Oct 11, 2012
 *      Author: ster
 */

#include "Draw.h"
using namespace std;

Draw::Draw()
{}

void Draw::draw(string primitive)
{

        glBegin(GL_QUADS);

        //Se a primitica for um rectangulo
        if(primitive == "rectangle")
          {

          }

        glEnd();
}

Draw::~Draw()
{}
