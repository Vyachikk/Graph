#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>
#include <string>
using namespace std;

//Структура ребра
typedef struct Edge {
    int destination;
    int rating;
    struct Edge* next;
} Edge;

//Структура вершины
typedef struct Vertex {
    string name;
    Edge* edges;
} Vertex;

//Структура графа
typedef struct Graph {
    Vertex* vertices;
    int vertex_count;
} Graph;

Graph* createGraph();
void freeGraph(Graph* graph);
void freeEdges(Graph* graph);
void addVertex(Graph* graph, const string name, string status_msg);
void removeVertex(Graph* graph, const string name, string status_msg);
void addEdge(Graph* graph, const string name1, const string name2, int rating, string status_msg);
void removeEdge(Graph* graph, const string name1, const string name2, string status_msg);
void editEdge(Graph* graph, const string name1, const string name2, int rating, string status_msg);
void editVertex(Graph* graph, const string name, const string newName, string status_msg);
void printGraph(Graph* graph);
void breadthFirstSearch(Graph* graph, const string startVertexName, int maxHandshakes, string status_msg);
void shortestPath(Graph* graph, const string startVertexName, const string endVertexName);
int findVertexIndex(Graph* graph, const string name);
void dfs(Graph* graph, int vertexIndex, bool* visited, int componentIndex);
void findConnectedComponents(Graph* graph);
Edge* findEdge(Edge* edges, int destination);

#endif /* GRAPH_H */
