/*
 * Light.h
 *
 *  Created on: Oct 13, 2012
 *      Author: ciberwizz
 */

#ifndef LIGHT_H_
#define LIGHT_H_

#include "cgf/CGFlight.h"
#include "parser.h"

class Light {
private:
	//TODO static initial..
	CGFlight *light;
	unsigned int id;
	string name_id;
	const float* exponent;
	bool enabled;
public:
	Light(unsigned int lightid, elemContainer * elc);
	void draw();
	CGFlight* getCGFlight();
	unsigned int getId();
	string getName();
	bool isEnabled();
	virtual ~Light();
};

#endif /* LIGHT_H_ */
