/*
*  autor: Benjamin Valdes Aguirre
*  fecha: Diciembre 2020
*  programa: act 4.1 Implementacion Grafos
*  desc: estos programas son solciones parciales a algunos de
*  las actividades planteadas en el curso TC1031
*
*
*  Extiende este archivo para completar tu soución.
*/

#ifndef Graph_H_
#define Graph_H_

#include <string>
#include <stdio.h>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <algorithm>

using namespace std;


class Graph {
private:
		int edgesList;
		int edgesMat;
		int nodes;
    	vector<int> *adjList;
		int *adjMatrix;
		//vector<Type> *vect = new vector<Type>
		void addAdjList(int u, int v);
		void dfsHelper(int inicial, int meta, stack<int> &s, list<int> &visited, vector<vector<int>> &paths);
        void bfsHelper(int inicial, int meta, queue<int> &q, list<int> &visited, vector<vector<int>> &paths);
        string printPaths(vector<vector<int>> &paths, int inicial, int meta);
        string printVisited(list<int> visited);

public:
		void loadGraphMat(string, int, int);
		Graph(int);
		Graph();
		void addEdgeAdjMatrix(int, int);
		string printAdjMat();
		string printAdjMat_clean();
		bool contains(list<int>, int);
		void sortAdjList();
		string DFS(int inicial, int meta);
        string BFS(int inicial, int meta);
		void loadGraphList(string file, int n, int m);
		string printAdjList();
};

void Graph::loadGraphList(string file, int n, int m) {
    adjList = new vector<int> [n];
    nodes = n;

    string line;
    ifstream lee(file);
    int u, v;
    if (lee.is_open()) {
        while (getline(lee, line)) {
            u = stoi(line.substr(1,1));
            v = stoi(line.substr(4,1));
            addAdjList(u, v);
        }
        lee.close();
    }
    else {
        cout << "Unable to open file" << endl;
    }
}

void Graph::loadGraphMat(string name, int a, int b){
	adjMatrix = new int [a*b];
	nodes = a;
	for (int i = 0; i < a*b; i++)
		adjMatrix[i] = 0;
		string line;
		ifstream lee (name);
		int u, v;
		if (lee.is_open()){
			while (getline(lee, line)){
				u = stoi(line.substr(1,1));
				v = stoi(line.substr(4,1));
				addEdgeAdjMatrix(u,v);
			}
			lee.close(); // Closes the file
		} else {
			cout << "Unable to open file";
		}
}

Graph::Graph() {
	edgesList = edgesMat = 0;
}

Graph::Graph(int n) {
	nodes = n;
	adjList = new vector<int>[nodes];
	adjMatrix = new int [nodes*nodes];
	for (int i = 0; i < nodes*nodes; i++)
		adjMatrix[i] = 0;
	edgesList = edgesMat = 0;
}

void Graph::addEdgeAdjMatrix(int u, int v){
	adjMatrix[u*nodes+v] = 1;
	adjMatrix[v*nodes+u] = 1;
	edgesMat++;
}

void Graph::addAdjList(int u, int v) {
    adjList[u].push_back(v);
    adjList[v].push_back(u);
    edgesList++;
}


string Graph::printAdjList(){
	  stringstream aux;
		for (int i = 0; i < nodes; i++){
	        aux << "vertex "
	             << i << " :";
	        for (int j = 0; j < adjList[i].size(); j ++){
							 aux << " " << adjList[i][j];
					}
	        aux << " ";
    }
		return aux.str();

}


string Graph::printAdjMat(){
	stringstream aux;
	for (int i = 0; i < nodes; i++){
	   for (int j = 0; j < nodes; j++){
			 aux << adjMatrix[i*nodes+j] << " ";
		 }
  }
	return aux.str();
}

string Graph::printAdjMat_clean(){
	stringstream aux;
	aux << "\n nodes \t|";
	for (int i = 0; i < nodes; i++){
			aux << "\t" << i ;
	}
	aux << "\n";
	for (int i = 0; i < nodes; i++){
			aux << "__________";
	}
	aux << "\n";
	for (int i = 0; i < nodes; i++){
		 aux << i << "\t|";
	   for (int j = 0; j < nodes; j++){
			 aux << "\t" << adjMatrix[i*nodes+j];
		 }
	   aux << "\n";
  }
	return aux.str();
}

void Graph::sortAdjList() {
    for (int i = 0; i < nodes; i ++) {
        sort(adjList[i].begin(), adjList[i].end());
    }
}


string Graph::DFS(int inicial, int meta) {
    stringstream aux;
    stack <int> s;
    list <int> visited;
    vector<vector<int>> paths(nodes, vector<int>(1, -1));
    s.push(inicial);
    dfsHelper(inicial, meta, s, visited, paths);
    aux << printVisited(visited);
    aux << printPaths(paths, inicial, meta);
    return aux.str();
}

void Graph::dfsHelper(int inicial, int meta, stack<int> &s, list<int> &visited, vector<vector<int>> &paths) {
    if (inicial == meta) {
        printVisited(visited);
    }
    else if (s.empty()) {
        cout << " node not found";
    }
    else {
        inicial = s.top();
        s.pop();
        visited.push_back(inicial);
        for (int i = 0; i < adjList[inicial].size(); i++) {
            if (!contains(visited, adjList[inicial][i])) {
                s.push(adjList[inicial][i]);
                paths[adjList[inicial][i]][0] = inicial;
            }
        }
        dfsHelper(inicial, meta, s, visited, paths);
    }
}

string Graph::BFS(int inicial, int meta) {
    stringstream aux;
    queue<int> q;
    list<int> visited;
    vector<vector<int>> paths(nodes, vector<int>(0));
    q.push(inicial);
    bfsHelper(inicial, meta, q, visited, paths);
    aux << printVisited(visited);
    aux << printPaths(paths, inicial, meta);
    return aux.str();
}

void Graph::bfsHelper(int inicial, int meta, queue<int> &q, list<int> &visited, vector<vector<int>> &paths) {
    stringstream aux;
    if (inicial == meta) {
        printVisited(visited);
    }
    else if (q.empty()) {
        aux << " node not found";
    }
    else {
        inicial = q.front();
        q.pop();
        visited.push_back(inicial);
        for (int i = 0; i < adjList[inicial].size(); i++) {
            if (!contains(visited, adjList[inicial][i])) {
                q.push(adjList[inicial][i]);
                paths[adjList[inicial][i]].push_back(inicial);
            }
        }
        bfsHelper(inicial, meta, q, visited, paths);
    }
}

string Graph::printVisited(list<int> visited) {
    stringstream aux;
    aux << "visited: ";
    while (!visited.empty()) {
        aux << visited.front() << " ";
        visited.pop_front();
    }
    return aux.str();
}

bool Graph::contains(list<int> visited, int data) {
    list<int>::iterator it;
    it = find(visited.begin(), visited.end(), data);
    if (it != visited.end()) {
        return true;
    }
    else {
        return false;
    }
}

string Graph::printPaths(vector<vector<int>> &paths, int inicial, int meta) {
    stringstream aux;
    int node = paths[meta][0];
    stack<int> reverse;
    reverse.push(meta);
    aux << "path:";
    while (node != inicial) {
        reverse.push(node);
        node = paths[node][0];
    }
    reverse.push(inicial);
    while (!reverse.empty()) {
        aux << " " << reverse.top();
        reverse.pop();
    }
    return aux.str();
}


#endif /* Graph_H_ */
