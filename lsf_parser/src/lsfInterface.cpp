

#include "lsfInterface.h"
#include <iostream>
#include "Scene.h"

using namespace std;
void lsfInterface::iniGUI(){


}

void lsfInterface::processKeyboard(unsigned char k, int x, int y){
	switch( k ){

	case 'v':
		((Scene *)this->scene)->cam++;
		break;
	case 'l':
		((Scene *)this->scene)->light++;
		break;
	}
}

lsfInterface::~lsfInterface() {}

