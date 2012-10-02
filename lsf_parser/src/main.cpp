#include <iostream>
#include "parser.h"

using namespace std;


int main(){

	LSFParser a = LSFParser("ster.lsf");

	//teste getElems
	cout << "\n---------getGlobals------------";
	a.getGlobals();

	cout <<"\n\n\n\n\n----------getAppearences--------";
	//teste getElemContainers
	a.getAppearences();

	cout <<"\n\n\n\n\n----------getCameras------------";
	a.getCameras();

	cout <<"\n\n\n\n\n----------getLightingConfig-----";
	a.getLightingConfig();

	cout <<"\n\n\n\n\n----------getLights-------------";
	a.getLights();

	cout <<"\n\n\n\n\n ---------graphrouteid " << a.getGraphRootId();

	cout <<"\n\n\n\n\n----------getnodes-------------";
	a.getGraphNodes();

	return 0;

}




