#include "Scene.h"
#include "cgf/CGFaxis.h"
#include "cgf/CGFapplication.h"
#include "primitives.h"
#include "parser.h"
#include <sstream>

#include <math.h>

#include "cgf/CGFappearance.h"

Scene::Scene(Elems* els){
	Elems::iterator it = els->begin();
	cullEnabled = false;

	for(; it != els->end() ; it++){
		if( (*it)->name == "background" ){
			//<background r="0" g="0" b="0" a="0" />
			stringstream ss;
			ss << (*it)->attr["r"]; ss >> ambient[0];
			ss << (*it)->attr["g"]; ss >> ambient[1];
			ss << (*it)->attr["b"]; ss >> ambient[2];
			ss << (*it)->attr["a"]; ss >> ambient[3];

		} else if( (*it)->name == "polygon" ){
	        //<polygon mode="fill" shading="gouraud" />
			polygMode = (*it)->attr["mode"];
			polygShading = (*it)->attr["shading"];

		} else if( (*it)->name == "culling" ){
	        //<culling frontfaceorder="CW" cullface="both" enabled="false" />
			frontFaceOrder = (*it)->attr["frontfaceorder"];
			cullFace = (*it)->attr["cullface"];
			cullEnabled = ((*it)->attr["enabled"] == "true" ? true : false);
		}

		//won't be needed anymore
		delete *it;
	}

	delete els;
}

void Scene::init()
{

	int mode = (polygMode == "fill" ? GL_FILL : 0);

	if(mode == 0)
		mode = (polygMode == "line" ? GL_LINE : 0);
	if(mode == 0)
		mode = (polygMode == "point" ? GL_POINT : 0);


//CULLING AND POLYGON MODES
	if(cullEnabled){

		glEnable(GL_CULL_FACE);

		if( cullFace == "both" || cullFace == "front"){

			if( cullFace == "both"){

				glCullFace(GL_FRONT_AND_BACK);
				glPolygonMode(GL_FRONT_AND_BACK, mode);

			} else if(cullFace == "front" ) {

				glCullFace(GL_FRONT);
				glPolygonMode(GL_FRONT, mode);
			}
			if( frontFaceOrder == "CCW")
				glFrontFace(GL_CCW);
			else
				glFrontFace(GL_CW);

		}else {
			glCullFace(GL_BACK);
			glPolygonMode(GL_BACK, mode);
		}
	}

	// Enables lighting computations
	glEnable(GL_LIGHTING);

	// Sets up some lighting parameters
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);  // Define ambient light

	if(polygShading == "gouraud")
		glShadeModel(GL_SMOOTH);
	else
		glShadeModel(GL_FLAT);


}

void Scene::update(long t)
{

}
	
void Scene::display()
{
	// ---- BEGIN Background, camera and axis setup

	// Clear image and depth buffer everytime we update the scene
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	// Initialize Model-View matrix as identity (no transformation
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	// Draw axis
	axis.draw();

	//TODO DRAW OBJECTS AND LIGHT AND SHIT




	// We have been drawing in a memory area that is not visible - the back buffer,
	// while the graphics card is showing the contents of another buffer - the front buffer
	// glutSwapBuffers() will swap pointers so that the back buffer becomes the front buffer and vice-versa
	glutSwapBuffers();

}

Scene::~Scene()
{

}
