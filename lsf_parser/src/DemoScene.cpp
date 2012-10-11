#include "DemoScene.h"
#include "cgf/CGFaxis.h"
#include "cgf/CGFapplication.h"
#include "primitives.h"
#include "parser.h"


#include <math.h>

#include "cgf/CGFappearance.h"

void DemoScene::init() 
{
	// Enables lighting computations
	glEnable(GL_LIGHTING);

	// Sets up some lighting parameters
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, CGFlight::background_ambient);  // Define ambient light
	
	// Declares and enables a light
	float light0_pos[4] = {4.0, 6.0, 5.0, 1.0};
	light0 = new CGFlight(GL_LIGHT0, light0_pos);
	light0->enable();

	// Defines a default normal
	glNormal3f(0,0,1);

	/*
	 *
	 * CHANGES
	 *
	 *
	 *
	 */
/*	LSFParser a = LSFParser("ster.lsf");
	BigElemContainers* esf = a.getGraphNodes();
	elem *sph;
	bool check = true;
	for(BigElemContainers::iterator it = esf->begin(); it != esf->end() && check; it++)
		for(ElemContainers::iterator ecit = (*it)->elemCs->begin(); ecit != (*it)->elemCs->end() && check; ecit++ )
			if((*ecit)->root->name == "children")
				for(Elems::iterator eit = (*ecit)->elems->begin(); eit != (*ecit)->elems->end() && check; eit++ )
					if((*eit)->name == "sphere"){
						obj=new Sphere(*eit);
						check = false;
						break;
					}*/



	materialAppearance=new CGFappearance();
	textureAppearance=new CGFappearance("textures/pyramid.jpg",GL_REPEAT, GL_REPEAT);
	shader=new CGFshader("shaders/texshader.vert","shaders/texshader.frag");

	setUpdatePeriod(30);
}

void DemoScene::update(long t)
{
	shader->bind();
	shader->update(t/400.0);
	shader->unbind();
	
}
	
void DemoScene::display() 
{

	// ---- BEGIN Background, camera and axis setup
	
	// Clear image and depth buffer everytime we update the scene
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	// Initialize Model-View matrix as identity (no transformation
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Apply transformations corresponding to the camera position relative to the origin
	CGFscene::activeCamera->applyView();

	// Draw (and update) light
	light0->draw();

	// Draw axis
	axis.draw();


	// ---- END Background, camera and axis setup


	// ---- BEGIN feature demos

	// Simple object
	//materialAppearance->apply();
	obj->draw();

	// textured object

	glTranslatef(0,4,0);
	//textureAppearance->apply();
	obj->draw();

	// shader object

	glTranslatef(0,4,0);
	//shader->bind();
	obj->draw();
	//shader->unbind();


	// ---- END feature demos

	// We have been drawing in a memory area that is not visible - the back buffer, 
	// while the graphics card is showing the contents of another buffer - the front buffer
	// glutSwapBuffers() will swap pointers so that the back buffer becomes the front buffer and vice-versa
	glutSwapBuffers();
}

DemoScene::~DemoScene()
{
	delete(shader);
	delete(textureAppearance);
	delete(materialAppearance);
	delete(obj);
	delete(light0);
}