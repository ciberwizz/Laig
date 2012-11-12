/*
 * Vehicle.h
 */

#ifndef VEHICLE_H_
#define VEHICLE_H_

#include "cgf/CGFobject.h"
#include "primitives.h"
#include "Patch.h"

class Vehicle: public CGFobject {
private:
	Cylinder* thruster;
	Rectangle body;
	Patch* nose;
	Triangle* wing_top;
	Triangle* wing_bottom;
	Triangle* rudder_left;
	Triangle* rudder_right;
public:
	Vehicle();
	void draw();

	virtual ~Vehicle();
};

#endif /* VEHICLE_H_ */
