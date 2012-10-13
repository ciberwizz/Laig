/*
 * graph.h
 *
 *  Created on: Oct 10, 2012
 *      Author: ster
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include "GraphNode.h"
#include "parser.h"
#include <list>
#include "cgf/CGFappearance.h"
#include "cgf/CGFobject.h"



class Graph
{
private:
	list<GraphNode*> nodes;
	GraphNode *root;
	list<CGFappearance*> appearances;
	list<CGFobject*> objects;
	//map<id_grpah, appearence_id>
	//map< id_node, list<node_ref> >
public:
	Graph();
  /*
   * run through elements
   * 	create graphnode
   * 	if elemnt nAMe is Id then is root!
   * 	put id in node
   * 	set transformations
   * 	set appeeareref map
   * 	run through child
   * 		if noderef then add to map
   * 		else -primitive- create CGFobj and set to node and list
   * 	push to nodes
   *
   * copy noderef* to each graph node
   *
   */
  void getGraph(BigElemContainers* bec, bool check, string ID);
  virtual ~Graph(){};
};

#endif /* GRAPH_H_ */

