#ifndef _GRAPHM_
#define _GRAPHM_

#include <iostream>
#include <iomanip>
#include "nodedata.h"

const int kPOSITIVE_MAX_M = 2147483647;				//upper bound of int
const int kMAX_NODES_M = 101;						//const type for the TC matrix

/*
	Class:		GraphM (part 1 of assignment 3)
	Purpose:	this class is used to read the input file, form the graph and calculate 
				the lowest cost path.
				with nodedata.h already included to get the costs and nodes
*/
class GraphM
{
public:
	//constructor
	GraphM();

	//Methods of GraphM class
	void buildGraph(ifstream& stream);				//reads data from the input file, form the graph of node and adjacent matrix of edges
	bool insertEdge(int from, int to, int dist);	//connect two nodes and assign weight to it
	bool removeEdge(int from, int to);				//delete a specific edge
	void findShortestPath();						//method to find the shortest path between two nodes
	void displayAll();								//display all possible paths by calling cout
	void display(int from, int to);					//display only the shortest path by calling cout

private:
	/*	Structure	TableType
		Purpose:	a table to keep the shortest distances and associated path info
	*/
	struct TableType
	{
		bool visited;								//keep the value to see if the node's been visited or not
		int dist;									//keep the shortest distance value
		int path;									//keep the path value
	};

	NodeData nodeList[kMAX_NODES_M];				//assign data for graph nodes
	int C[kMAX_NODES_M][kMAX_NODES_M];				//cost array as 2D array
	int size;										//number of nodes 
	TableType T[kMAX_NODES_M][kMAX_NODES_M];		//store the visited node and weight

	//private methods
	void nodeShortestPath(int from, int to);		//print the shortest node path
	void nodeDataName(int from, int to);			//print the nodes name of the shortest path
};
#endif