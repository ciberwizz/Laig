#include <iostream>
#include "parser.h"
#include "primitives.h"
#include "Graph.h"
#include <exception>
#include "cgf/CGFapplication.h"
#include "Scene.h"
#include "appearence.h"
#include "Light.h"
#include "Scene.h"
#include "Cameras.h"
#include "lsfInterface.h"

using namespace std;


int main(int argc, char*argv[]){

  string parser = "";

  if(argc > 1){
      parser = argv[1];
  }
  else{
      parser = "ster.lsf";
  }

  cout << "********USAGE**********" << endl;
  cout << "Use v key to browse through the available perspectives...(if you get a black screen, go full screen)\n";
  cout << "Use l to switch off/on lights\n";
  cout << "Enjoy :)\n" << endl;

	LSFParser a = LSFParser(parser);

	Scene sc = Scene(a.getGlobals(), a.getLightingConfig());

	ElemContainers* elcs = new ElemContainers();

	a.getLightingConfig();
	map<string, Light*> luses = map<string, Light*>();
	elcs = a.getLights();
	int i=1;

	for(ElemContainers::iterator it = elcs->begin() ; it != elcs->end() ; it++ ) {
		//it cannot be after because (+it) will be deleted in Light constructer
		string id =(*it)->root->attr["id"];
		Light * l = new Light(i++, (*it));
		luses[id] = l;
		sc.addLight(l);
	}

	BigElemContainers* cena = a.getGraphNodes();
	string ID = a.getGraphRootId();

	Graph *g = new Graph();
	 g->getGraph(cena,ID);
	 g->setAppID(a.getAppearences());

	 //import graph
	sc.setGraph(g);

	//import cameras to scene
	bigElemContainer * b = a.getCameras();
	Cameras *c;
	if( b->elems != NULL)
		for(Elems::iterator it = b->elems->begin(); it != b->elems->end() ; it++)
		{
			c = new Cameras(*it);
			sc.addCGFcamera(c);
		}

	if( b->elemCs != NULL)
		for(ElemContainers::iterator it = b->elemCs->begin(); it!=b->elemCs->end(); it++ ){
			c = new Cameras(*it);
			sc.addCGFcamera(c);
		}
	c->setInitial(b->root);

	lsfInterface * cgf_interface =new lsfInterface(12);


	CGFapplication app = CGFapplication();

	try {
		app.init(&argc, argv);

		app.setScene(&sc);
		app.setInterface(cgf_interface);
		app.run();
	}
	catch(GLexception& ex) {
		cout << "Erro: " << ex.what();
		return -1;
	}
	catch(exception& ex) {
		cout << "Erro inesperado: " << ex.what();
		return -1;
	}

	return 0;

}




