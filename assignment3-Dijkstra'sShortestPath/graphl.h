#ifndef _GRAPHL_
#define _GRAPHL_

#include <iostream>
#include <iomanip>
#include "nodedata.h"

const int kPOSITIVE_MAX_L = 2147483647;				//upper bound of int
const int kMAX_NODES_L = 101;						//const type for the TC matrix

/*
	Class:		GraphL (part 2 of assignment 3)
	Purpose:	This class is use to find and display depth-first ordering to cout.
				With nodedata.h already included to get the costs and nodes
*/
class GraphL
{
public:
	GraphL();										//constructor
	~GraphL();										//destructor

	//methods
	void buildGraph(ifstream& stream);				//reads data from the input file, form the graph of node and adjacent matrix of edges
	void displayGraph();							//display the graph
	void depthFirstSearch();						//display the path by using depthFirstSearch method

private:
	//structure EdgeNode is use to store connected nodes
	struct EdgeNode
	{
		int adjcNode;
		EdgeNode* next;
	};
	//strucutre GraphNode use to store nodes
	struct GraphNode
	{
		EdgeNode* head;
		NodeData* data;
		bool visited;
	};

	GraphNode nodeList[kMAX_NODES_L];				//list of adjacent nodes
	int size;										//store the size of no. of nodes

	//private helper methods
	void makeEmpty();								//destructor helper method
	void depthFirstSearchHelper(int n);				//recursive helper method
};
#endif