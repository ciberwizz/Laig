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
  node_appearance = map< string, string >();
  looks = map<string, appearence*>();
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
      //Variable where the appearance of this node will be stored
      string appearance = "";

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
                        {cout << "entrei no cylinder\n";
                        obj = new Cylinder((*eit));
                        cout << "criei cylinder\n";
                        }
                      if((*eit)-> name == "torus")
                        {
                          obj = new Torus((*eit));
                        }
                      if((*eit)-> name == "triangle")
                        {
                          obj = new Triangle((*eit));
                        }
                      if((*eit)-> name == "rectangle")
                        {
                          obj = new Rectangle((*eit));
                        }
                      n->setCGFobject(obj);
                      obj = NULL;
                    }
                  //Set the GraphNode object

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
                  node_appearance[n->getId()] = (*it_elems)->attr["id"];
                }
            }

          i++;
        }

      //Insert Graphnode into nodes list
      nodes.push_back(n);

      if(n->getId() == ID)
        {
          root = n;
        }

      //Create map entry for node
      node_children[n->getId()] = children;
    }

  //Now to populate the world!
  populateChildren();
}

GraphNode* Graph::getRoot()
{
  return root;
}

void Graph::populateChildren()
{
  map< string, list<string>* >::iterator map_it;
  list<GraphNode*>::iterator gn;
  list<GraphNode*>::iterator gnk;
  list<string>::iterator cit;

  //Go through map node_children
  for(map_it = node_children.begin(); map_it != node_children.end(); map_it++)
    {
      //Find node in graphnode list
      for(gn=nodes.begin(); gn!=nodes.end(); gn++)
        {
          //  cout << "Size: " << nodes.size() << endl;
          //find node reference in map and add the noderefs to the graphnode children
          if((*gn)->getId() == map_it->first)
            {
              //iterate through the node refs
              for(cit = map_it->second->begin(); cit != map_it->second->end(); cit++)
                {
                  //find the node with the same id as noderef
                  for(gnk=nodes.begin(); gnk!=nodes.end(); gnk++)
                    {
                      if( (*gnk)->getId() == *cit)
                        {
                          //add it to the children list
                          (*gn)->addChild(*gnk);
                        }
                      //children = map_it->second;
                    }
                }

            }
        }
    }
}

void Graph::setNodeAppearance()
{
  map< string, string >::iterator it;
  map<string, appearence*>::iterator itapp;
  list<GraphNode*>::iterator it_graphnode;

  //node_appearance has <idNode,idAppea..
  for(it = node_appearance.begin(); it != node_appearance.end(); it++)
    {
      map<string, appearence*>::iterator look_it = looks.find(it->second);
      if( look_it != looks.end()){
          //found an appearence correesponding to an node
          // lets find the node to insert
          it_graphnode = nodes.begin();
          for(; it_graphnode != nodes.end() ; it_graphnode++){
              if(it->first == (*it_graphnode)->getId()){
                  (*it_graphnode)->setAppearance(look_it->second);
                  break;
              }
          }
      }

    }
}

//Fill looks map
void Graph::setAppID(ElemContainers* elcs)
{
  ElemContainers::iterator it;

  for(it = elcs->begin(); it != elcs->end() ; it++)
    {
      looks[(*it)->root->attr["id"]] = new appearence((*it)->elems);
    }
  this->setNodeAppearance();
}





