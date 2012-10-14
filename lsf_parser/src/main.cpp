#include <iostream>
#include "parser.h"
#include "primitives.h"
#include "Graph.h"
#include <exception>
#include "cgf/CGFapplication.h"
#include "DemoScene.h"
#include "appearence.h"
#include "Light.h"
#include "Scene.h"
using namespace std;


int main(int argc, char*argv[]){

	LSFParser a = LSFParser("ster.lsf");

	/*
	 * Testing Scene plus globals
	 */

	cout << "\nTesting how Scene takes globals\n";
	Scene sc = Scene(a.getGlobals(), a.getLightingConfig());
	cout << "it ate all of them! RUN!!\n";

	/*****************************************************************************/

	/*
	 * testing appearence class
	 */
	map<string, appearence*> looks = map<string, appearence*>();

	cout << "going to get appear..\n";
	ElemContainers* elcs = a.getAppearences();
	for(ElemContainers::iterator it = elcs->begin() ; it != elcs->end() ; it++ ) {
		looks[(*it)->root->attr["id"]] = new appearence((*it)->elems);
	}
	cout << "just got the freaking appear...\n";

	/**************************************************************************/

	/*
	 * Testing Lights
	 */
	cout << "\n\n\nTime to Test Lights!\n";
	//testing lights
	a.getLightingConfig(); //TODO é necessario tratar desta bosta!
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

	cout << "Lights Tested!\n";

	/*****************************************************************************/



	//elem *sph;
	BigElemContainers* cena = a.getGraphNodes();
	//bool check = true;
	string ID = a.getGraphRootId();

	Graph *g = new Graph();
	 g->getGraph(cena,ID);
	 g->setAppID(a.getAppearences());
	 g->setNodeAppearance();

	//TODO NOT DRAWING
	sc.setGraph(g);
	CGFapplication app = CGFapplication();

	try {
		app.init(&argc, argv);

		app.setScene(&sc);
		app.setInterface(new CGFinterface());
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




