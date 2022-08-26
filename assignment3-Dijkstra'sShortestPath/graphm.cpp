#include "graphm.h"

/*
	Constructor
	Purpose:	set value to initialize nodes, other nodes that is not used will be assign to infinity
				set visited to all false; set all path to 0
*/
GraphM::GraphM()
{
	size = 0;									//set default size

	//initialize values to infinity, all visited path to false
	for (int i = 0; i < kMAX_NODES_M; i++)
	{
		for (int j = 0; j < kMAX_NODES_M; j++)
		{
			C[i][j] = kPOSITIVE_MAX_M;;			//cost matrix

			//store visited value, dist, and path
			T[i][j].visited = false;
			T[i][j].dist = kPOSITIVE_MAX_M;
			T[i][j].path = 0;
		}
	}
}

//purpose: build the graph node and the edges matrix
void GraphM::buildGraph(ifstream& stream)
{
	//the first line is the size
	stream >> size;

	//following are the node description
	string desc;
	getline(stream, desc);

	//initialize node value
	for (int i = 1; i <= size; i++)
	{
		nodeList[i].setData(stream);
	}

	//initialize dist; stop when hit 0
	int from, to, dist;
	while (stream >> from >> to >> dist && from != 0)
		C[from][to] = dist;
}

//assign edge to connect to nodes. Return true if successfully added, else false
bool GraphM::insertEdge(int from, int to, int dist)
{
	//only positive dist
	if(dist < 0)
		return false;

	//dist of itself = 0
	if (dist != 0 && from == to)
		return false;

	//"from" value must be greater than 1 and in range of the size
	if (from > size || from < 1)
		return false;

	//same thing with "to" value
	if (to > size || to < 1)
		return false;
	
	//assigning dist to the edge
	C[from][to] = dist;
	//also find shortest path
	findShortestPath();
	return true;
}

//remove an edge between two nodes, return true if successful, else false
bool GraphM::removeEdge(int from, int to)
{
	//"from" value must be greater than 1 and in range of the size
	if(from > size || from < 1)
		return false;

	//same thing with "to" value
	if (to > size || to < 1)
		return false;

	//assign new edge
	C[from][to] = kPOSITIVE_MAX_M;
	//update shortest path
	findShortestPath();
	return true;
}

//find shortest path between two nodes; TableType T update shortest path information
void GraphM::findShortestPath()
{
	int e;														//keep edge value
	int minDist;												//keep min dist value

	//since the order to read matrix is row - column => T[row][column]
	for (int source = 1; source <= size; source++)
	{
		T[source][source].dist = 0;								//shortest path to itself is 0
		T[source][source].visited = true;

		//temp shortest path based on origin
		for (int i = 1; i <= size; i++)
		{
			//if the path exist
			if (C[source][i] != kPOSITIVE_MAX_M);
			{
				T[source][i].dist = C[source][i];
				T[source][i].path = source;
			}
		}

		//keep finding shortest path for each adjacent to e
		for (;;)
		{
			e = 0;												//reset edge each time
			minDist = kPOSITIVE_MAX_M;							//temp minimum distance

			//check source node edge
			for (int o = 1; o <= size; o++)
			{
				//get smallest source's edge
				if (!T[source][o].visited)
				{
					if (C[source][o] < minDist)
					{
						minDist = C[source][o];
						e = o;
					}
				}
			}

			//source's edges haven't visit
			if (e != 0)
			{
				T[source][e].visited = true;					//mark as visited
				for (int p = 1; p <= size; p++)
				{
					//make sure node is unvisited
					if (!T[source][p].visited)
					{
						//make sure path exist
						if (C[e][p] != kPOSITIVE_MAX_M)
						{
							//make sure not to repeat node
							if (e != p)
							{
								//compare to get smallest path
								if (T[source][e].dist + C[e][p] < T[source][p].dist)
								{
									//replace it
									T[source][p].dist = T[source][e].dist + C[e][p];
									//assign previous path
									T[source][p].path = e;
								}
							}
						}
					}
				}
			}
			else
				break;
		}
	}
}

//display all possible paths by calling cout
void GraphM::displayAll()
{
	//Title for each column
	cout << "Description" << setw(18) << "From Node" << setw(10) << "To Node" << setw(13) << "Dijkstra's" << setw(9) << "Path" << endl;

	//from node
	for (int from = 1; from <= size; from++) 
	{
		//from node name
		cout << nodeList[from] << endl << endl;
		//to node
		for (int to = 1; to <= size; to++) {

			//exclude itself path
			if (from != to) 
			{
				// Using T table to get the shortest path
				if (T[from][to].dist != 0) 
				{
					cout << setw(25) << from;            //from node
					cout << setw(10) << to;              //to node

					//from node to to node)
					if (T[from][to].dist == kPOSITIVE_MAX_M) 
					{
						cout << setw(10) << "----" << endl;
					}

					//multiple paths from from node to to node
					else 
					{
						cout << setw(10) << T[from][to].dist;
						cout << setw(13);

						//find shortest path
						nodeShortestPath(from, to);
						cout << endl;
					}
				}
			}
		}
	}
}

//display only the shortest path by calling cout
void GraphM::display(int from, int to)
{
	//keep path in range
	if (from > size || to > size || from <= 0 || to <= 0) 
	{
		cout << setw(5) << from << setw(11) << to; 
		cout << setw(9) << "----" << endl;
		return;
	}

	//else path in range
	else 
	{
		cout << setw(5) << from << setw(11) << to;

		//if path exist between two nodes
		if (T[from][to].dist != kPOSITIVE_MAX_M) 
		{
			//print shorest path
			cout << setw(9) << T[from][to].dist << setw(14);

			//print shortest path node number
			nodeShortestPath(from, to);
			cout << endl;

			//print out shortest path name
			nodeDataName(from, to);
		}

		//path not exist
		else
			cout << setw(9) << "----" << endl;
		cout << endl;
	}
}

//print the shortest node path
void GraphM::nodeShortestPath(int from, int to)
{
	//exit if path is not exist
	if (T[from][to].dist == kPOSITIVE_MAX_M)
		return;

	//else if path is current path
	else if (from == to) 
	{
		// print it
		cout << to << " ";
		return;
	}

	// if path exist, find it recursively
	else 
	{
		int nodeNo = to;							// keep previous node's number
		nodeShortestPath(from, T[from][to].path);

		// print out path
		cout << nodeNo << " ";
	}
}

void GraphM::nodeDataName(int from, int to) 
{
	//exit if path is not exist
	if (T[from][to].dist == kPOSITIVE_MAX_M) 
	{
		return;
	}

	//else if path is current path
	else if (from == to) 
	{
		// print out name of path
		cout << nodeList[to] << endl << endl;
		return;
	}

	//else path exist, find it recursively
	else 
	{
		nodeDataName(from, T[from][to].path);

		// print out name path
		cout << nodeList[to] << endl << endl;
	}
}