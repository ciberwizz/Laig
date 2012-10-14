#include "Scene.h"
#include "cgf/CGFaxis.h"
#include "cgf/CGFapplication.h"
#include "primitives.h"
#include "parser.h"
#include <sstream>
#include <list>
#include <math.h>

#include "cgf/CGFappearance.h"

Scene::Scene(Elems* globals,elemContainer* lconfig):lights(){
	Elems::iterator it = globals->begin();
	cullEnabled = false;
	graph = NULL;

	//GLOBAL STUFF

	for(; it != globals->end() ; it++){
		if( (*it)->name == "background" ){
			//<background r="0" g="0" b="0" a="0" />
			stringstream ss;
			ss << (*it)->attr["r"]; ss >> background[0];
			ss << (*it)->attr["g"]; ss >> background[1];
			ss << (*it)->attr["b"]; ss >> background[2];
			ss << (*it)->attr["a"]; ss >> background[3];

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

	delete globals;

	//LIGHTING CONFIG STUFF
//root	   <lighting doublesided="false" local="true" enabled="true" >
//	  elems:     <ambient r="1" g="1" b="1" a="0" />
	if( lconfig->root->attr["doublesided"] == "true" )
		this->doublesided = true;
	else
		this->doublesided = false;

	if( lconfig->root->attr["local"] == "true" )
		this->local = true;
	else
		this->local = false;

	if( lconfig->root->attr["enabled"] == "true" )
		this->enabled = true;
	else
		this->enabled = false;

	for( it = lconfig->elems->begin() ; it != lconfig->elems->end() ; it++ )
		if((*it)->name == "ambient"){
			stringstream ss;
			ss << (*it)->attr["r"]; ss >> this->ambient[0];
			ss << (*it)->attr["g"]; ss >> this->ambient[1];
			ss << (*it)->attr["b"]; ss >> this->ambient[2];
			ss << (*it)->attr["a"]; ss >> this->ambient[3];
			break;
		}

}


void Scene::addLight(Light *light){
	this->lights.push_back(light);
}

//includes adding cgfobgjects
void Scene::setGraph(Graph* gr){
	graph = gr;
}

void Scene::addCGFcamera(CGFcamera* cam){
	this->scene_cameras.push_back(cam);
	//TODO set active camera
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

	//Lighting Config!!
	if(this->doublesided)
		glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	else
		glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);

	if( this->local)
		glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	else
		glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, this->ambient);  // Define ambient light



	if(polygShading == "gouraud")
		glShadeModel(GL_SMOOTH);
	else
		glShadeModel(GL_FLAT);

	list<Light *>::iterator light_it = lights.begin();
	for(int i = 0; (light_it != lights.end()) && (i < 8) ; light_it++)
		if( (*light_it)->isEnabled() ){
			(*light_it)->init();
			i++;
		}


	/*
	 * TESTING AREA
	 */

	this->test = new GraphNode();

	//TODO NOT WORKING
	this->test->setCGFobject(new Triangle(0,0,0,10,0,0,5,10,1));

	//this->test->setCGFobject(new Torus(2,5,10,10));

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

	// Apply transformations corresponding to the camera position relative to the origin
	CGFscene::activeCamera->applyView();


	//draw lights: only 8 at the most
	list<Light *>::iterator light_it = lights.begin();
	for(int i = 0; (light_it != lights.end()) && (i < 8) ; light_it++){
		(*light_it)->draw();
		i++;
	}


	// Draw axis
	axis.draw();


	//TODO DRAW OBJECTS AND SHIT
	if(graph != NULL)
	{
		graph->getRoot()->draw();
	}

//	this->test->draw();


	// We have been drawing in a memory area that is not visible - the back buffer,
	// while the graphics card is showing the contents of another buffer - the front buffer
	// glutSwapBuffers() will swap pointers so that the back buffer becomes the front buffer and vice-versa
	glutSwapBuffers();

}

Scene::~Scene()
{

}
