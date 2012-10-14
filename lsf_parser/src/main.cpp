#include <iostream>
#include "parser.h"
#include "primitives.h"
#include "Graph.h"
#include <exception>

#include "cgf/CGFapplication.h"
#include "DemoScene.h"

using namespace std;


int main(int argc, char*argv[]){

  LSFParser a = LSFParser("ster.lsf");

  //elem *sph;
  BigElemContainers* cena = a.getGraphNodes();
  //bool check = true;
  string ID = a.getGraphRootId();
  Graph *g = new Graph();

 g->getGraph(cena,ID);


  CGFapplication app = CGFapplication();

  try {
      app.init(&argc, argv);

      app.setScene(new DemoScene());
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

  //BigElemContainers* esf = a.getGraphNodes();
  /*
  BigElemContainers* esf = a.getGraphNodes();
  elem *sph;
  bool check = true;
  for(BigElemContainers::iterator it = esf->begin(); it != esf->end() && check; it++)
    for(ElemContainers::iterator ecit = (*it)->elemCs->begin(); ecit != (*it)->elemCs->end() && check; ecit++ )
      if((*ecit)->root->name == "children")
        for(Elems::iterator eit = (*ecit)->elems->begin(); eit != (*ecit)->elems->end() && check; eit++ )
          if((*eit)->name == "sphere"){
              obj=new Sphere(*eit);
              check = false;
              break;
          }*/

}




