#ifndef PARSER_H_
#define PARSER_H_

#include <iostream>
#include <string>
#include <map>
#include <list>
#include <cassert>
#include "tinyXML/tinyxml.h"


using namespace std;

typedef struct{
	string name;
	map<string,string> attr;
}elem;
typedef list<elem*> Elems;

typedef struct {
	elem* root;
	Elems* elems;

}elemContainer;
typedef list<elemContainer*> ElemContainers;

typedef struct {
	elem* root;
	Elems* elems;
	ElemContainers* elemCs;

}bigElemContainer;
typedef list<bigElemContainer*> BigElemContainers;





class LSFParser {
private:
	TiXmlDocument* doc;
	TiXmlElement* lsfE;
	TiXmlElement* globalsE;
	TiXmlElement* camerasE;
	TiXmlElement* lightingE;
	TiXmlElement* appearancesE;
	TiXmlElement* graphE;

	//helper functions
	elem*  getElem(TiXmlElement*);
	//if filter is true it will skip siblings with childs
	Elems*  getElems(TiXmlElement*, bool);
	//if filter is true  then skip childless elements
	ElemContainers* getElemContainers(TiXmlElement* , bool );
	BigElemContainers* getBigElemContainers(TiXmlElement*);
public:
	//opens opens file and instantiates TiXml*
	LSFParser(string file );

	//returns a list of globals and their attributes
	Elems* getGlobals();

	//returns a list of cameras
		//if a camera is perspective then childelements will be
		//converted to attr. ex: elem->attr["fromx"] ...
	bigElemContainer* getCameras();

	//returns a list of lighting configurations
		//elem who's name is "config" refers to the attr of lighting
		// other elems refer to childless childs expl: <ambient r="1" g="1" b="1" a="0" />
	elemContainer* getLightingConfig();

	//returns an array of array elemcontainers identified by an id
	ElemContainers* getLights();

	//returns an array of appearances each with their own elems
	ElemContainers* getAppearences();

	//returns the graph's root id node
	string getGraphRootId();

	//returns array of nodes in graph
	BigElemContainers* getGraphNodes();

};


#endif /* PARSER_H_ */
