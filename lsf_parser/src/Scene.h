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
	//light
	float ambient[4];
	//polygon
	string polygMode;
	string polygShading;
	//culling
	string frontFaceOrder;
	string cullFace;
	bool cullEnabled;

	list<Light *> lights;

	Graph *graph;
public:
	Scene(Elems*);
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
