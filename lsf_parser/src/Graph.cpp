/*
 * graph.cpp
 *
 *  Created on: Oct 10, 2012
 *      Author: ster
 */

#include "Graph.h"


void Graph::getGraph(BigElemContainers* bec, bool check, string ID)
{
  for (BigElemContainers::iterator it = bec->begin(); it != bec->end() && check; it++)
    {

      if ((*it)->root->attr["id"] == ID)
        {
          cout << "Father: " << (*it)->root->attr["id"] << endl;
          {
            for (ElemContainers::iterator ecit = (*it)->elemCs->begin();
                ecit != (*it)->elemCs->end() && check; ecit++)
              {
                //   cout << (*ecit)->root->name << endl;
                {
                  for (Elems::iterator eit = (*ecit)->elems->begin();
                      eit != (*ecit)->elems->end() && check; eit++)
                    {
                      cout << "Children: " << (*eit)->attr["id"] << endl;
                    }
                }
              }
          }
        }
    }
}

