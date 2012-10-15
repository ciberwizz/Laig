#ifndef SCENE_H
#define SCENE_H

#include "cgf/CGFscene.h"
#include "cgf/CGFshader.h"
#include "parser.h"
#include "Graph.h"
#include "Light.h"

class Scene : public CGFscene
{
private:
//globals
	float background[4];
	//polygon
	string polygMode;
	string polygShading;
	//culling
	string frontFaceOrder;
	string cullFace;
	bool cullEnabled;

//lighting config
	bool doublesided;
	bool local;
	bool enabled;
	float ambient[4];

	list<Light *> lights;
	CGFlight* light0;

	Graph *graph;
public:
	//params: globals, lightingconfig
	Scene(Elems*,elemContainer*);
	void addLight(Light *);
	//includes adding cgfobgjects
	void setGraph(Graph *);
	void addCGFcamera(CGFcamera*);

	void init();
	void display();
	void update(long t);
	virtual ~Scene();
private:

};

#endif
