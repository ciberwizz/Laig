#include "Light.h"
#include <sstream>
#include <GL/glut.h>

Light::Light(unsigned int lightid, elemContainer * elc) {

//	<light id="primary" enabled="true">
//		<location x="0" y="5" z="0" />
//		<ambient r="1" g="1" b="1" a="0" />
//		<diffuse r="1" g="1" b="1" a="0" />
//		<specular r="1" g="1" b="1" a="0" />
//		<!-- No caso de uma ser uma spotlight, incluir os dados abaixo; se for uma omnilight, omitir -->
//		<spot angle="45" exponent="2" dirx="45" diry="45" dirz="45" />
//	</light>

	float pos[4];
	float direct[4];
	float ambient[4];
	float diffuse[4];
	float specular[4];
	float angle;
	this->name_id = elc->root->attr["id"];
	this->id = lightid;



	//just initializing
	this->exponent  = new const float(-1.0);

	Elems::iterator it = elc->elems->begin();

	for(; it != elc->elems->end(); it++) {
		stringstream ss;


		if( (*it)->name == "location") {
			ss << (*it)->attr["x"]; ss >> pos[0];
			ss << (*it)->attr["y"]; ss >> pos[1];
			ss << (*it)->attr["z"]; ss >> pos[2];

			//1 -> if its not a spot 0 if it is.
			pos[3] = 1.0;

		} else if( (*it)->name == "ambient") {
			ss << (*it)->attr["r"]; ss >> ambient[0];
			ss << (*it)->attr["g"]; ss >> ambient[1];
			ss << (*it)->attr["b"]; ss >> ambient[2];
			ss << (*it)->attr["a"]; ss >> ambient[3];

		} else if( (*it)->name == "diffuse") {
			ss << (*it)->attr["r"]; ss >> diffuse[0];
			ss << (*it)->attr["g"]; ss >> diffuse[1];
			ss << (*it)->attr["b"]; ss >> diffuse[2];
			ss << (*it)->attr["a"]; ss >> diffuse[3];

		} else if( (*it)->name == "specular") {
			ss << (*it)->attr["r"]; ss >> specular[0];
			ss << (*it)->attr["g"]; ss >> specular[1];
			ss << (*it)->attr["b"]; ss >> specular[2];
			ss << (*it)->attr["a"]; ss >> specular[3];

		} else if( (*it)->name == "spot") {
			float i;
			ss << (*it)->attr["angle"]; ss >> angle;
			ss << (*it)->attr["exponent"]; ss >> i;
			delete this->exponent;
			this->exponent = new const float(i);
			ss << (*it)->attr["dirx"]; ss >> direct[0];
			ss << (*it)->attr["diry"]; ss >> direct[1];
			ss << (*it)->attr["dirz"]; ss >> direct[2];

			//this is a spot light
			pos[3] = 1.0;
		}

		delete *it;

	}

	delete elc;

	//after getting what is needed create the f#$% light
	this->light = new CGFlight(lightid,pos,direct);

	if( elc->root->attr["enabled"] == "true") {
		this->enabled = true;
		this->light->enable();
	}
	else {
		this->enabled = false;
		this->light->disable();
	}

	this->light->setAmbient(ambient);
	this->light->setSpecular(specular);
	this->light->setAngle(angle);

	if( (*this->exponent) > 0.0 ) {
			glLightfv( this->id, GL_SPOT_EXPONENT, this->exponent );
		}
}


void Light::draw(){

	if(this->enabled)
		this->light->draw();
}

CGFlight* Light::getCGFlight(){
	return this->light;
}

unsigned int Light::getId(){
	return this->id;
}

string Light::getName(){
	return this->name_id;
}

bool Light::isEnabled(){
	return this->enabled;
}

Light::~Light() {
	delete this->light;
	delete this->exponent;
}

