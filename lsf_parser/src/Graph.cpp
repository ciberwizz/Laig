/*
 * graph.cpp
 *
 *  Created on: Oct 10, 2012
 *      Author: ster
 */

#include "Graph.h"
#include <sstream>

/*	string id;
	double transformations[16];
	CGFobject * obj;
	CGFappearance * tex;
	CGFappearance * material;
	list<GraphNode *> children;*/

Graph::Graph(){
	nodes = list<GraphNode*>();
	root = NULL;
	appearances = list<CGFappearance*>();
	objects = list<CGFobject*>();
}

void Graph::getGraph(BigElemContainers* bec, bool check, string ID)
{
	//Percorre Nos
	for (BigElemContainers::iterator it = bec->begin(); it != bec->end() && check; it++)
	{
		GraphNode * n = new GraphNode();

		for (ElemContainers::iterator ecit = (*it)->elemCs->begin();
				ecit != (*it)->elemCs->end() && check; ecit++)
		{
			string temp = (*ecit)->root->name;

			//If ElemContainers is transforms
			if(temp == "transforms")
			{
				for (Elems::iterator eit = (*ecit)->elems->begin();
						eit != (*ecit)->elems->end() && check; eit++)
				{
					//If we want to do a rotation
					if((*eit)-> name == "rotate")
					{
						cout << (*eit)-> name << endl;
						cout << "Angle: " << (*eit)->attr["angle"] << endl;
						cout << "Axis: " << (*eit)->attr["axis"] << endl;

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
						cout << (*eit)-> name << endl;
						cout << "X: " << (*eit)->attr["x"] << endl;
						cout << "Y: " << (*eit)->attr["y"] << endl;
						cout << "z: " << (*eit)->attr["z"] << endl;

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
					{
						cout << (*eit)-> name << endl;
						cout << "X: " << (*eit)->attr["x"] << endl;
						cout << "Y: " << (*eit)->attr["y"] << endl;
						cout << "z: " << (*eit)->attr["z"] << endl;

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



			/*
					//Listar os putos
					for (Elems::iterator eit = (*ecit)->elems->begin();
							eit != (*ecit)->elems->end() && check; eit++)
					{
						//Adidionar puto a lista de putos
						GraphNode *child = new GraphNode();
						child->setId((*eit)->attr["id"]);*/


			/* if ((*it)->root->attr["id"] == ID)
				   		{
				   			n->setId(ID);
				   		}*/

		}
	}

}



