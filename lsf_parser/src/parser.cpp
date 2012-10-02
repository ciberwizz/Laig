#include <iostream>
#include <string>
#include <map>
#include <list>
#include <cassert>
#include "tinyXML/tinyxml.h"
#include "tinyXML/tinystr.h"

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





class LSFScene {
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
	Elems*  getElems(TiXmlElement*, bool filter);
	ElemContainers* getElemContainers(TiXmlElement* te, bool filter);
	BigElemContainers* getBigElemContainers(TiXmlElement*);
public:
	//opens opens file and instantiates TiXml*
	LSFScene(string file );

	//returns a list of globals and their attributes
	Elems* getGlobals();

	//returns a list of cameras
		//if a camera is perspective then childelements will be
		//converted to attr. ex: elem->attr["fromx"] ...
	BigElemContainers* getCameras();

	//returns a list of lighting configurations
		//elem who's name is "config" refers to the attr of lighting
		// other elems refer to childless childs expl: <ambient r="1" g="1" b="1" a="0" />
	Elems* getLightingConfig();

	//returns an array of array elemcontainers identified by an id
	ElemContainers* getLights();

	//returns an array of appearances each with their own elems
	ElemContainers* getAppearences();

	//returns the graph's root id node
	string getGraphRootId();

	//returns array of nodes in graph
	BigElemContainers* getGraphNodes();

};




int main(){

	LSFScene a = LSFScene("ster.lsf");
	//teste getElems
	a.getGlobals();
	//teste getElemContainers
	a.getAppearences();




}





/*

	TiXmlDocument * doc;
	TiXmlElement * lsfE;
	TiXmlElement * globalsE;
	TiXmlElement * camerasE;
	TiXmlElement * lightingE;
	TiXmlElement * appearancesE;
	TiXmlElement * graphE;
*/

//opens opens file and instanciates TiXml*
LSFScene::LSFScene(string file ){

	this->doc=new TiXmlDocument( "ster.lsf");
	bool loadOkay = doc->LoadFile();

	cout << "loadfile: "<< loadOkay;

	this->lsfE = doc->FirstChildElement();
	assert(this->lsfE != NULL);

	this->globalsE = lsfE->FirstChildElement("globals");
	assert(this->globalsE != NULL);

	this->camerasE = lsfE->FirstChildElement("cameras");
	assert(this->camerasE != NULL);

	this->lightingE = lsfE->FirstChildElement("lighting");
	assert(this->lightingE != NULL);

	this->appearancesE = lsfE->FirstChildElement("appearances");
	assert(this->appearancesE != NULL);

	this->graphE = lsfE->FirstChildElement("graph");
	assert(this->graphE != NULL);
}


//typedef struct{
//	string name;
//	map<string,string> attr;
//}elem;
//typedef list<elem*> Elems;
//

elem*  LSFScene::getElem(TiXmlElement* te){
	elem* el = new elem;

	el->name = te->Value();
	cout << ">\n<" << el->name;

	el->attr = map<string,string>();

	//save it's attributes
	for( TiXmlAttribute* at = te->FirstAttribute() ; at != NULL ; at = at->Next() ) {
		el->attr[at->Name()] = at->Value();
		cout << " " <<at->Name() <<"=\"" << el->attr[at->Name()] <<"\"";

	}

	return el;
}

//returns a list of elements
	//if filter is true it will skip siblings with childs
Elems*  LSFScene::getElems(TiXmlElement* te, bool filter=false){
	Elems* els =new Elems();
	while(te!= NULL){

		if(filter)
			if(!te->NoChildren())
				continue;

		els->push_back(getElem(te));
		te = te->NextSiblingElement();
	}

	if(els->size() > 0)
		return els;
	else {
		delete els;
		return NULL;
	}
}

//typedef struct {
//	elem root;
//	Elems elems;
//
//}elemContainer;
//typedef list<elemContainer*> ElemContainers;
//
//typedef struct {
//	elem root;
//	Elems elems;
//	ElemContainers elemCs;
//
//}bigElemContainer;
//typedef list<bigElemContainer*> BigElemContainers;
////////////////////////////////////////////////////

//return a list of elemcontainers
	//if filter is true  then skip childless elements
ElemContainers* LSFScene::getElemContainers(TiXmlElement* te, bool filter=false){
	ElemContainers* elcs = new ElemContainers();

	for(; te != NULL; te = te->NextSiblingElement()){

		if(te->NoChildren())
			continue;

		elemContainer * elc = new elemContainer;

		elc->root = getElem(te);
		elc->elems = getElems(te->FirstChildElement());

		elcs->push_back(elc);
	}

	if(elcs->size() > 0)
		return elcs;
	else {
		delete elcs;
		return NULL;
	}
}

BigElemContainers* LSFScene::getBigElemContainers(TiXmlElement* te){
	BigElemContainers *belcs = new BigElemContainers();

	for(; te != NULL; te = te->NextSiblingElement()){

		bigElemContainer* belc = new bigElemContainer;

	
		belc->root = getElem(te);

		belc->elems = getElems(te,true);
		belc->elemCs = getElemContainers(te,true);

		belcs->push_back(belc);


	}

	if(belcs->size() >0)
		return belcs;
	else {
		delete belcs;
		return NULL;
	}

}



//returns an array of globals and their attributes
Elems* LSFScene::getGlobals(){

	Elems* els= getElems( this->globalsE->FirstChildElement());


	return els;
}

//returns an array of cameras
	//if a camera is perpective then childelements will be
	//converted to attr. ex: elem->attr["fromx"] ...
BigElemContainers* LSFScene::getCameras(){
	return NULL;
}

//returns lighting configurations
	//elem who's name is "config" refers to the attr of lighting
	// other elems refer to childless childs expl: <ambient r="1" g="1" b="1" a="0" />
Elems* LSFScene::getLightingConfig(){
	return NULL;
}

//returns an array of array elemcontainers identified by an id
ElemContainers* LSFScene::getLights(){
	return NULL;
}

//returns an array of appearances each with their own elems
ElemContainers* LSFScene::getAppearences(){
	ElemContainers *elcs = getElemContainers(this->appearancesE->FirstChildElement());

	return elcs;
}

//returns the graph's root id node
string LSFScene::getGraphRootId(){
	return "";
}

//returns array of nodes in graph
BigElemContainers* LSFScene::getGraphNodes(){
	return NULL;
}





