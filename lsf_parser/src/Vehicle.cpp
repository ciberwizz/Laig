/*
 * Vehicle.cpp
 */

#include "Vehicle.h"
#include "primitives.h"
#include "Patch.h"

Vehicle::Vehicle(): body(0.0, 0.0, 3.0, 2.0){
	this->thruster = new Cylinder(0.75,1,2,50,50);
	wing_bottom = new Triangle( 0, 0, 0,
							1, 0,-1,
							1, 0, 0 );

	wing_top = new Triangle(0, 0, 0,
							1, 0, 0,
							1, 0,-1 );

	rudder_right = new Triangle(0, 0, 0,
							   1, 0, 0,
							   1, 1, 0);

	rudder_left = new Triangle(0, 0, 0,
								1, 1, 0,
								1, 0, 0);
	int n[2] ={10,10};
	this->nose = new Patch(n,"fill");

}

void Vehicle::draw() {

	glPushMatrix();

		glRotatef(90,0,1,0);
		glTranslatef(-3,0,-0.75);

		//nose
		glPushMatrix();
			glTranslatef(0,0,0.75);
			glRotatef(-90,0,1,0);
			glTranslatef(0.0,1,0);
			glScalef(0.375,0.5,-4);
			nose->draw();
		glPopMatrix();


		//main body = cube
		glPushMatrix();
			glScalef(2,1,1);
			//front
			glPushMatrix();
				glTranslatef(0,0,1.5);
				this->body.draw();
			glPopMatrix();

			//back
			glPushMatrix();
				glTranslatef(1.5,0,0);
				glRotatef(180,0,1,0);
				glTranslatef(-1.5,0,0);
				this->body.draw();
			glPopMatrix();

			//left
			glPushMatrix();
				glScalef(1,1,0.5);
				glRotatef(270,0,1,0);
				this->body.draw();
			glPopMatrix();

			//right
			glPushMatrix();
				glScalef(1,1,0.5);
				glTranslatef(3,0,1.5);
				glRotatef(90,0,1,0);
				glTranslatef(-1.5,0,0);
				this->body.draw();
			glPopMatrix();

			//bottom
			glPushMatrix();
				glScalef(1,1,0.75);
				glRotatef(90,1,0,0);
				this->body.draw();
			glPopMatrix();

			//top
			glPushMatrix();
				glTranslatef(0,2,1.5);
				glScalef(1,1,0.75);
				glRotatef(270,1,0,0);
				this->body.draw();
			glPopMatrix();
		glPopMatrix();

		//thruster
		glPushMatrix();
			glTranslatef(5,1,0.75);
			glRotatef(90,0,1,0);
			this->thruster->draw();
		glPopMatrix();

		//wing_right
		glPushMatrix();
			glTranslatef(0,1,0);
			glScalef(3,3,3);
			//wing_top
			this->wing_top->draw();

			//wing_bottom
			this->wing_bottom->draw();
		glPopMatrix();


		//wing_right
		glPushMatrix();
			glTranslatef(0,1,1.5);
			glRotatef(180,1,0,0);

			glScalef(3,3,3);
			//wing_top
			this->wing_top->draw();

			//wing_bottom
			this->wing_bottom->draw();
		glPopMatrix();

		//rudder
		glPushMatrix();
			//right
			glPushMatrix();
				glTranslatef(4,2,0.75);
				this->rudder_right->draw();
			glPopMatrix();
			//left
			glPushMatrix();
				glTranslatef(4,2,0.75);
				this->rudder_left->draw();
			glPopMatrix();

		glPopMatrix();
	glPopMatrix();
}

Vehicle::~Vehicle() {
}

