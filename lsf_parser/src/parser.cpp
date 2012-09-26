#include <iostream>
#include <cassert>
#include "tinyxml.h"

using namespace std;


int main(){
	TiXmlDocument * doc;
	doc=new TiXmlDocument( "lsf.lsf");
	bool loadOkay = doc->LoadFile();

	cout << "loadfile: "<< loadOkay;

	TiXmlElement * lsfE = doc->FirstChildElement();
	assert(lsfE != NULL);

	TiXmlElement * globalsE = lsfE->FirstChildElement("globals");
	assert(globalsE != NULL);

	TiXmlElement * camerasE = lsfE->FirstChildElement("cameras");
	assert(camerasE != NULL);

	TiXmlElement * lightingE = lsfE->FirstChildElement("lighting");
	assert(lightingE != NULL);

	TiXmlElement * appearancesE = lsfE->FirstChildElement("appearances");
	assert(appearancesE != NULL);

	TiXmlElement * graphE = lsfE->FirstChildElement("graph");
	assert(graphE != NULL);

}
