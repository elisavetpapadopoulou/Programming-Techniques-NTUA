/*
 * cycle.cpp
 *
 *  Created on: 8 May 2021
 *      Author: elisa
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;

class Graph {
public:
	Graph(int V);
	~Graph();
	void addEdge(int u, int v);
	bool cycle(vector<int> &path) const;

private:
	int Vertices;
	list<int> *nodes;
	enum state { UNVISITED, SEEN, VISITED };

	void dfs(int u, vector<int> &path, vector<state> &status, bool &flag) const {
		unsigned int j=0;
		if (flag == true) return;
		status.at(u) = SEEN;
		path.push_back(u);

		//else {
			for(int v: nodes[u]) {
				if(status.at(v) == UNVISITED) {
					if (flag == true) return;
					dfs(v, path, status, flag);
					if (flag == true) return;
					status.at(u) = VISITED;
					if (!path.empty())
						path.pop_back();
				}
				else if (status.at(v) == SEEN) {
					for(j=0; j<path.size(); j++) {
						if (path.at(j) == v) {
							if (j != 0)
								path.erase(path.begin(), path.begin()+j);
							flag = true;
							return;
						}
					}
				}
			//}
		}
	}
};



Graph::Graph(int V) {
	Vertices = V;
	nodes = new list<int>[V];
}

Graph::~Graph() {
	//delete []nodes;
}

void Graph::addEdge(int u, int v) {
	list<int>::iterator i;
	i = find(nodes[u].begin(), nodes[u].end(), v);
	if (i == nodes[u].end())
		nodes[u].push_back(v);
}

bool Graph::cycle(vector<int> &path) const {
	bool flag = false;
	vector<state> status(Vertices);
	for(int i =0; i<Vertices; i++) {
		status.at(i) = UNVISITED;
	}
	for(int i=0; i<Vertices; i++) {
		if(status.at(i) == UNVISITED) {
			dfs(i, path, status, flag);
			status[i] = VISITED;
			if (flag == true) return true;
			else {
				path.clear();
			}

		}
	}
	path.clear();
	return false;
}

#ifndef CONTEST
int main() {
	int V, E;

    /*cin >> V >> E;

	for (int i = 0; i < E; ++i) {
		int u, v;
		cin >> u >> v;
		g.addEdge(u, v);
	}*/

	/*V = 7;
	Graph g(V);
	g.addEdge(0, 1);
	g.addEdge(0, 2);
	g.addEdge(1, 2);
	g.addEdge(2, 3);
	g.addEdge(3, 4);
	g.addEdge(4, 0);
	g.addEdge(4, 6);
	g.addEdge(1, 5);
	g.addEdge(5, 6); //test 1
*/
	/*V = 4;
	E = 5;
	Graph g(V);
	g.addEdge(0, 1);
	g.addEdge(0, 2);
	g.addEdge(1, 3);
	g.addEdge(2, 3);
	g.addEdge(0, 3); // test 2 */

	V = 6;
	E = 5;
	Graph g(V);
	g.addEdge(0, 1);
	g.addEdge(0, 2);
	g.addEdge(3, 4);
	g.addEdge(4, 5);
	g.addEdge(5, 3); //test 3


	/*V=10;
	Graph g(V);
	g.addEdge(0, 1);
	g.addEdge(6, 2);
	g.addEdge(0, 6);
	g.addEdge(3, 1);
	g.addEdge(4, 6);
	g.addEdge(4, 5);
	g.addEdge(5, 1);
	g.addEdge(7, 1);
	g.addEdge(9, 2);
	g.addEdge(5, 6);
	g.addEdge(8, 9);
	g.addEdge(8, 3);
	g.addEdge(0, 3);
	g.addEdge(7, 4);
	g.addEdge(8, 6);
	g.addEdge(7, 3);
	g.addEdge(3, 4);
	g.addEdge(0, 4);
	g.addEdge(5, 9);
	g.addEdge(3, 5);
*/
	vector<int> path;
	bool c = g.cycle(path);
	if (c) {
		cout << "CYCLE: ";
		for (unsigned int i = 0; i < path.size(); ++i)
			cout << path[i] << (i == path.size()-1 ? "\n" : " ");
	}
	else {
		cout << "NO CYCLE" << endl;
		for (unsigned int i = 0; i < path.size(); i++)
			cout << path[i] << (i == path.size()-1 ? "\n" : " ");
	 }
}
#endif
