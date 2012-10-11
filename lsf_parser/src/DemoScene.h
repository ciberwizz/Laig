#ifndef DEMOSCENE_H
#define DEMOSCENE_H

#include "cgf/CGFscene.h"
#include "cgf/CGFshader.h"

class DemoScene : public CGFscene
{
public:
	void init();
	void display();
	void update(long t);
	~DemoScene();
private:
	CGFlight* light0;
	CGFobject* obj;
	CGFappearance* materialAppearance;
	CGFappearance* textureAppearance;
	CGFshader* shader;
};

#endif