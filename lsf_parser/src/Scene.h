#ifndef SCENE_H
#define SCENE_H

#include "cgf/CGFscene.h"
#include "cgf/CGFshader.h"
#include "parser.h"

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

public:
	Scene(Elems*);
	void init();
	void display();
	void update(long t);
	~Scene();
private:

};

#endif
