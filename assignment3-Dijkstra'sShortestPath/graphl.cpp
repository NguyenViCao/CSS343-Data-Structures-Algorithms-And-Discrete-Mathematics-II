#include "graphl.h"

//Constructor
//Purpose: set all cost to infinity, all visited flase
GraphL::GraphL()
{
	size = 0;
	for (int i = 1; i < kMAX_NODES_L; i++)
	{
		nodeList[i].head = nullptr;
		nodeList[i].data = nullptr;
		nodeList[i].visited = false;
	}
}

//Destructor
//Purpose: clear the graph by calling makeEmpty() helper method
GraphL::~GraphL()
{
	makeEmpty();
}

//Purpose: build the graph of nodes, adjacent matrix of edges between nodes by reading 
//			from input text file
void GraphL::buildGraph(ifstream& stream)
{
	//first line is the size
	stream >> size;

	//keep reading, next is the node description
	string node;
	getline(stream, node);

	//initialize the node data
	for (int i = 1; i <= size; i++)
	{
		getline(stream, node);
		nodeList[i].data = new NodeData(node);
	}

	//read the nodes that are connected
	int from, to;
	while (stream >> from >> to && from != 0)
	{
		//read first node
		if (nodeList[from].head == nullptr)
			nodeList[from].head = new EdgeNode{ to, nullptr };	//this node is not connected
		else
			nodeList[from].head = new EdgeNode{ to, nodeList[from].head };
	}
}

void GraphL::displayGraph()
{
	cout << endl << "Graph:" << endl;

	// pointer value to go through the list
	EdgeNode* current = nullptr;
	for (int i = 1; i <= size; i++) 
	{
		// print the data
		cout << "Node" << i << setw(9) << " " << *nodeList[i].data << endl << endl;
		current = nodeList[i].head;

		// print the adjacencs
		while (current != nullptr) 
		{
			cout << setw(6) << "edge" << setw(3) << i << setw(3) << current->adjcNode << endl;
			current = current->next;
		}
	}
}

//Purpose: display the path by using depthFirstSearch method
void GraphL::depthFirstSearch()
{
	cout << endl;
	cout << "Depth-First Search order: ";
	
	//starts from the first node
	for (int i = 1; i <= size; i++)
	{
		//if node is not visited
		if (!nodeList[i].visited)
			depthFirstSearchHelper(i);
	}
	cout << endl;
}

//destructor helper to reset the graph to its original
void GraphL::makeEmpty()
{
	//a temporary point to traverse through the list
	EdgeNode* tmp = nullptr;

	//delete every nodes
	for (int i = 1; i <= size; i++)
	{
		//delete node's data
		delete nodeList[i].data;
		nodeList[i].data = nullptr;

		//set node visited to false
		nodeList[i].visited = false;

		//delete the edges
		while (nodeList[i].head != nullptr)
		{
			//let the tmp pointer to hold the head pointer value
			tmp = nodeList[i].head;
			//traverse to next node
			nodeList[i].head = nodeList[i].head->next;
			//delete the tmp
			delete tmp;
			tmp = nullptr;
		}
	}
}

//DFS helper method
void GraphL::depthFirstSearchHelper(int n)
{
	//print the node
	cout << setw(3) << n;
	
	//mark this node as visited
	nodeList[n].visited = true;

	//temporary value for traversing through the list
	EdgeNode* current = nodeList[n].head;

	//start from parent node
	while (current != nullptr) 
	{
		//if node is not visited
		if(!nodeList[current->adjcNode].visited) 
		{
			// keep traversing recursively
			depthFirstSearchHelper(current->adjcNode);
		}
		// next node
		current = current->next;
	}
}