/*
 * graph.h
 *
 *  Created on: Oct 10, 2012
 *      Author: ster
 */

#ifndef GRAPH_H_
#define GRAPH_H_
#include "parser.h"
#include <list>
#include "cgf/CGFappearance.h"
#include "cgf/CGFobject.h"
/*
 *
 */
class Graph
{
public:
  Graph(){};
  void getGraph(BigElemContainers* bec, bool check, string ID);
  virtual ~Graph(){};
};

class GraphNode {
private:
	CGFobject * obj;
	CGFappearance * tex;
	CGFappearance * material;
	list<GraphNode *> children;

public:
	GraphNode(CGFobject * o, CGFappearance * _tex, CGFappearance * m)
		{ obj = o; tex = _tex; material =m; this->children = list<GraphNode *>();};
	void addChild( GraphNode * g) { this->children.push_back(g);};
	//TODO funcoes....
};
#endif /* GRAPH_H_ */

