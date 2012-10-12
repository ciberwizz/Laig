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
public:
  Graph(){};
  void getGraph(BigElemContainers* bec, bool check, string ID);
  virtual ~Graph(){};
};

#endif /* GRAPH_H_ */

