#ifndef SCENE_H
#define SCENE_H

#include "cgf/CGFscene.h"
#include "cgf/CGFshader.h"

class Scene : public CGFscene
{
public:
	void init();
	void display();
	void update(long t);
	~Scene();
private:
	CGFlight* light0;
	CGFobject* obj;
	CGFappearance* materialAppearance;
	CGFappearance* textureAppearance;
	CGFshader* shader;
};

#endif
