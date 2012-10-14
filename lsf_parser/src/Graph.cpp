/*
 * graph.cpp
 *
 *  Created on: Oct 10, 2012
 *      Author: ster
 */

#include "Graph.h"
#include <sstream>


Graph::Graph(){
  nodes = list<GraphNode*>();
  root = NULL;
  appearances = list<CGFappearance*>();
  objects = list<CGFobject*>();
  node_children = map< string, list<string>* >();
}

void Graph::getGraph(BigElemContainers* bec, string ID)
{
  //Creat CGFobject
  CGFobject * obj = NULL;
  int i = 0;
  //Parse BigElemContainers
  for (BigElemContainers::iterator it = bec->begin(); it != bec->end(); it++)
    {
      //Create nem Graphnode
      GraphNode * n = new GraphNode();

      //List that will contain the children's Ids
      list<string> * children = new list<string>();

      //Node to be scanned
      string nodeName = (*it)->root->attr["id"];
      n->setId(nodeName);


      //Parse ElemContainers
      for (ElemContainers::iterator ecit = (*it)->elemCs->begin();
          ecit != (*it)->elemCs->end(); ecit++)
        {
          string temp = (*ecit)->root->name;

          //If ElemContainers is transforms
          if(temp == "transforms")
            {
              for (Elems::iterator eit = (*ecit)->elems->begin();
                  eit != (*ecit)->elems->end(); eit++)
                {
                  //If we want to do a rotation
                  if((*eit)-> name == "rotate")
                    {
                      /*       cout << (*eit)-> name << endl;
                      cout << "Angle: " << (*eit)->attr["angle"] << endl;
                      cout << "Axis: " << (*eit)->attr["axis"] << endl;*/

                      //Conversion of parameter "angle" from string to int
                      istringstream angle((*eit)->attr["angle"]);
                      int angleInt;
                      angle >> angleInt;

                      //Do the actual rotation
                      n->rotate((*eit)->attr["axis"], angleInt);
                    }

                  //If we want to do a translation
                  if((*eit)-> name == "translate")
                    {
                      /*     cout << (*eit)-> name << endl;
                      cout << "X: " << (*eit)->attr["x"] << endl;
                      cout << "Y: " << (*eit)->attr["y"] << endl;
                      cout << "z: " << (*eit)->attr["z"] << endl;*/

                      //Conversion of parameters
                      stringstream x1;
                      double X;
                      x1 << (*eit)->attr["x"];
                      x1 >> X;

                      stringstream y1;
                      double Y;
                      y1 << (*eit)->attr["y"];
                      y1 >> Y;

                      stringstream z1;
                      double Z;
                      z1 << (*eit)->attr["z"];
                      z1 >> Z;

                      //Do the actual translation
                      n->translate(X,Y,Z);
                    }
                  //If we want to scale the object
                  if((*eit)-> name == "scale")
                    {/*
                      cout << (*eit)-> name << endl;
                      cout << "X: " << (*eit)->attr["x"] << endl;
                      cout << "Y: " << (*eit)->attr["y"] << endl;
                      cout << "z: " << (*eit)->attr["z"] << endl;*/

                      //Conversion of parameters
                      stringstream x1;
                      double X;
                      x1 << (*eit)->attr["x"];
                      x1 >> X;

                      stringstream y1;
                      double Y;
                      y1 << (*eit)->attr["y"];
                      y1 >> Y;

                      stringstream z1;
                      double Z;
                      z1 << (*eit)->attr["z"];
                      z1 >> Z;

                      //Do the actual translation
                      n->scale(X,Y,Z);
                    }
                }
            }
          else
            {
              for (Elems::iterator eit = (*ecit)->elems->begin();
                  eit != (*ecit)->elems->end(); eit++)
                {
                  if((*eit)-> name == "noderef")
                    {
                      children->push_back((*eit)->attr["id"]);
                    }
                  else
                    {

                      if((*eit)-> name == "sphere")
                        {
                          obj = new Sphere((*eit));
                        }
                      if((*eit)-> name == "cylinder")
                        {
                          obj = new Sphere((*eit));
                        }
                      if((*eit)-> name == "torus")
                        {
                          obj = new Sphere((*eit));
                        }
                      if((*eit)-> name == "triangle")
                        {
                          obj = new Sphere((*eit));
                        }
                      if((*eit)-> name == "rectangle")
                        {
                          obj = new Sphere((*eit));
                        }
                    }
                  //Set the GraphNode object
                  n->setCGFobject(obj);
                }
            }

          //Run through Childless elements
          for (Elems::iterator it_elems = (*it)->elems->begin(); it_elems != (*it)->elems->end(); it_elems++)
            {
              //  cout << "da fuq: " << (*it_elems)-> name << endl;
              if((*it_elems)-> name == "appearanceref")
                {
                  //   cout << "Atributos: " << (*it_elems)->attr["id"] << endl;
                  //  n->setCGFobject((*it_elems)->attr["id"]);
                  break;
                }
            }

          i++;
        }

      //Insert Graphnode into nodes list
      nodes.push_back(n);

      //Create map entry for node
      node_children[n->getId()] = children;
    }

}





