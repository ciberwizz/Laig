#ifndef GRAPHNODE_H_
#define GRAPHNODE_H_

#include <list>
#include "cgf/CGFappearance.h"
#include "cgf/CGFobject.h"
#include <cmath>


class GraphNode {
private:
	string id;
	double transformations[16];
	CGFobject * obj;
	CGFappearance * appear;
	list<GraphNode *> children;
public:
	GraphNode();
	GraphNode(string, CGFobject * o, CGFappearance * m);

	void setId(string);
	string getId();

	void setCGFobject(CGFobject *);
	CGFobject* getCGFobject();

	void addChild(GraphNode * g);
	list<GraphNode *>::const_iterator getChildIterator();

	void setAppearance(CGFappearance*);

	CGFappearance* getAppearance() const;

	//transformation functions
	void translate(double, double, double);
	void scale(double, double, double);
	void rotate(string,double);

	void draw();

	virtual ~GraphNode();
};

//matrix operations
double* multMatrix(double*, double*);
double* createMatrixTranslate(double, double, double);
double* createMatrixScale(double, double, double);
double* createMatrixRotate(string,double);
double* createIdentityMatrix(double*);

#endif /* GRAPHNODE_H_ */
