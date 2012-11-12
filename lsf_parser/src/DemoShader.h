#ifndef _DEMO_SHADER_H_
#define _DEMO_SHADER_H_

#include "cgf/CGFshader.h"
#include "cgf/CGFtexture.h"
#include <stdlib.h>
#include <GL/glew.h>

using namespace std;

class DemoShader :public CGFshader
{
public:
	DemoShader();
	virtual void bind(void);
	~DemoShader(void);
	void setScale(float s);
	float normScale;
	int wireframe;

protected:
	CGFtexture * baseTexture;
	CGFtexture * secTexture;

	GLint baseImageLoc;
	GLint secImageLoc;

	GLint scaleLoc;
};

#endif // _DEMO_SHADER_H_
