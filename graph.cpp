#include <iostream>
#include <iomanip>
#include "graph.h"

//�������� �����
Graph* createGraph() {
    Graph* graph = new Graph();
    graph->vertices = NULL;
    graph->vertex_count = 0;
    return graph;
}

//����������� ����� ����� ��������� ���������
void freeGraph(Graph* graph) {
    for (int i = 0; i < graph->vertex_count; i++) {
        Edge* current_edge = graph->vertices[i].edges;
        while (current_edge != nullptr) {
            Edge* next_edge = current_edge->next;
            delete current_edge;
            current_edge = next_edge;
        }
    }

    delete[] graph->vertices;
    delete graph;
}


void freeEdges(Graph* graph) {
    for (int i = 0; i < graph->vertex_count; i++) {
        Vertex* vertex = &(graph->vertices[i]);

        Edge* currentEdge = vertex->edges;
        while (currentEdge != NULL) {
            Edge* nextEdge = currentEdge->next;
            delete currentEdge;
            currentEdge = nextEdge;
        }

        vertex->edges = NULL;
    }
}

//���������� �������
void addVertex(Graph* graph, const string name, string status_msg) {
    if (findVertexIndex(graph, name) != -1) {
        status_msg = "������: ������� � ����� ������ ��� ����������.\n";
        return;
    }

    graph->vertices = (Vertex*)realloc(graph->vertices, (graph->vertex_count + 1) * sizeof(Vertex));
    Vertex* new_vertex = &(graph->vertices[graph->vertex_count]);
    new_vertex->name = name;
    new_vertex->edges = nullptr;
    graph->vertex_count++;
    status_msg = "������� ���������.\n";
}


// �������� �������
void removeVertex(Graph* graph, const string name, string status_msg) {
    int vertexIndex = findVertexIndex(graph, name);

    if (vertexIndex == -1) {
        status_msg = "������: ������� � ��������� ������ �� �������.\n";
        return;
    }

    // �������� ���� �����, ��������� � ������ ��������
    Vertex* vertex = &(graph->vertices[vertexIndex]);

    Edge* currentEdge = vertex->edges;
    while (currentEdge != NULL) {
        int destinationIndex = currentEdge->destination;
        Vertex* destinationVertex = &(graph->vertices[destinationIndex]);

        Edge* prevEdge = NULL;
        Edge* destEdge = destinationVertex->edges;
        while (destEdge != NULL) {
            if (destEdge->destination == vertexIndex) {
                if (prevEdge == NULL) {
                    destinationVertex->edges = destEdge->next;
                }
                else {
                    prevEdge->next = destEdge->next;
                }
                free(destEdge);
                break;
            }
            prevEdge = destEdge;
            destEdge = destEdge->next;
        }

        Edge* nextEdge = currentEdge->next;
        free(currentEdge);
        currentEdge = nextEdge;
    }

    // ����� ������ ����� ��������� ������� �����
    for (int i = vertexIndex; i < graph->vertex_count - 1; i++) {
        graph->vertices[i] = graph->vertices[i + 1];
    }

    graph->vertex_count--;

    status_msg = "������� �������.\n";
}

// ���������� ����� ����� ���������
void addEdge(Graph* graph, const string source_name, const string destination_name, int rating, string status_msg) {
    int source_index = findVertexIndex(graph, source_name);
    int destination_index = findVertexIndex(graph, destination_name);

    if (rating < -10 || rating > 10) {
        status_msg = "������: ������� ������������ �������� ��������.\n";
        return;
    }

    if (source_index == -1 || destination_index == -1) {
        status_msg = "������: ��������� ������� �� �������.\n";
        return;
    }

    Vertex* source_vertex = &(graph->vertices[source_index]);
    Vertex* destination_vertex = &(graph->vertices[destination_index]);

    // ��������, ���������� �� ��� ����� ����� ���������
    Edge* edge = source_vertex->edges;
    while (edge != NULL) {
        if (edge->destination == destination_index) {
            status_msg = "������: ����� ��� ���������� ����� ���������.\n";
            return;
        }
        edge = edge->next;
    }

    Edge* new_edge = (Edge*)malloc(sizeof(Edge));
    new_edge->destination = destination_index;
    new_edge->rating = rating;
    new_edge->next = NULL;

    // ���������� ����� � ������ ��������� �������-���������
    if (source_vertex->edges == NULL) {
        source_vertex->edges = new_edge;
    }
    else {
        Edge* current_edge = source_vertex->edges;
        while (current_edge->next != NULL) {
            current_edge = current_edge->next;
        }
        current_edge->next = new_edge;
    }

    // ���������� ����� � ������ ��������� �������-����������
    Edge* new_reverse_edge = (Edge*)malloc(sizeof(Edge));
    new_reverse_edge->destination = source_index;
    new_reverse_edge->rating = rating;
    new_reverse_edge->next = NULL;

    if (destination_vertex->edges == NULL) {
        destination_vertex->edges = new_reverse_edge;
    }
    else {
        Edge* current_reverse_edge = destination_vertex->edges;
        while (current_reverse_edge->next != NULL) {
            current_reverse_edge = current_reverse_edge->next;
        }
        current_reverse_edge->next = new_reverse_edge;
    }

    status_msg = "����� ����� ��������� ���������.\n";
}

// �������� ����� ����� ���������
void removeEdge(Graph* graph, const string name1, const string name2, string status_msg) {
    int index1 = findVertexIndex(graph, name1);
    int index2 = findVertexIndex(graph, name2);

    if (index1 == -1 || index2 == -1) {
        status_msg = "������: ��������� ������� �� �������.\n";
        return;
    }

    Vertex* vertex1 = &(graph->vertices[index1]);
    Vertex* vertex2 = &(graph->vertices[index2]);

    Edge* prev_edge1 = NULL;
    Edge* current_edge1 = vertex1->edges;
    while (current_edge1 != NULL && current_edge1->destination != index2) {
        prev_edge1 = current_edge1;
        current_edge1 = current_edge1->next;
    }

    Edge* prev_edge2 = NULL;
    Edge* current_edge2 = vertex2->edges;
    while (current_edge2 != NULL && current_edge2->destination != index1) {
        prev_edge2 = current_edge2;
        current_edge2 = current_edge2->next;
    }

    if (current_edge1 == NULL || current_edge2 == NULL) {
        status_msg = "������: ����� ����� ���������� ��������� �� ����������.\n";
        return;
    }

    // �������� ����� �� ������ ��������� ������� 1
    if (prev_edge1 == NULL) {
        vertex1->edges = current_edge1->next;
    }
    else {
        prev_edge1->next = current_edge1->next;
    }

    // �������� ����� �� ������ ��������� ������� 2
    if (prev_edge2 == NULL) {
        vertex2->edges = current_edge2->next;
    }
    else {
        prev_edge2->next = current_edge2->next;
    }

    free(current_edge1);
    free(current_edge2);

    status_msg = "����� �������.\n";
}

// �������������� ����� ����� ���������
void editEdge(Graph* graph, const string name1, const string name2, int newRating, string status_msg) {
    int index1 = findVertexIndex(graph, name1);
    int index2 = findVertexIndex(graph, name2);

    if (index1 == -1 || index2 == -1) {
        status_msg = "������: ��������� ������� �� �������.\n";
        return;
    }

    Edge* edge1 = findEdge(graph->vertices[index1].edges, index2);
    Edge* edge2 = findEdge(graph->vertices[index2].edges, index1);

    if (edge1 == NULL || edge2 == NULL) {
        status_msg = "������: ����� ����� ���������� ��������� �� ����������.\n";
        return;
    }

    edge1->rating = newRating;
    edge2->rating = newRating;

    status_msg = "����� ���������������.\n";
}

// �������������� �������
void editVertex(Graph* graph, const string name, const string newName, string status_msg) {
    int vertexIndex = findVertexIndex(graph, name);

    if (vertexIndex == -1) {
        status_msg = "������: ��������� ������� �� �������.\n";
        return;
    }

    if (findVertexIndex(graph, newName) != -1) {
        status_msg = "������: ������� � ����� ������ ��� ����������.\n";
        return;
    }

    graph->vertices[vertexIndex].name = newName;
    status_msg = "������� ���������������.\n";
}

//����� �����
void printGraph(Graph* graph) {
    cout << "������� ���������:\n" << "         ";

    for (int i = 0; i < graph->vertex_count; i++) {
        cout << left << setw(10) << graph->vertices[i].name << endl;
    }

    cout << endl;

    for (int i = 0; i < graph->vertex_count; i++) {
        cout << left << setw(10) << graph->vertices[i].name << endl;

        for (int j = 0; j < graph->vertex_count; j++) {
            Edge* edge = findEdge(graph->vertices[i].edges, j);
            if (edge != NULL) {
                cout << left << setw(10) << edge->rating << endl;
            }
            else {
                cout << left << setw(10) << "-" <<  endl;
            }
        }

        cout << endl;
    }
}

// ������� ������ ����� � ������
void breadthFirstSearch(Graph* graph, const string name, int maxHandshakes, string status_msg) {
    // ������� ��������� ������� � ������ name
    int startVertexIndex = findVertexIndex(graph, name);

    if (startVertexIndex == -1) {
        status_msg = "������: ��������� ������� �� �������.\n";
        return;
    }

    bool* visited = (bool*)malloc(graph->vertex_count * sizeof(bool));
    memset(visited, false, graph->vertex_count * sizeof(bool));

    int* handshakeCount = (int*)malloc(graph->vertex_count * sizeof(int));
    memset(handshakeCount, 0, graph->vertex_count * sizeof(int));

    cout << "�������� �����, � �������� " << graph->vertices[startVertexIndex].name << " ������, �� ����� ��� ����� " << maxHandshakes << " �����������:\n";

    visited[startVertexIndex] = true;
    handshakeCount[startVertexIndex] = 0;
    cout << graph->vertices[startVertexIndex].name << endl;

    // �������� ����� ������ �����������
    for (int handshake = 1; handshake <= maxHandshakes; handshake++) {
        cout << "����������� " << handshake << ":";
        bool handshakeFound = false;

        for (int i = 0; i < graph->vertex_count; i++) {
            // ���� ������� ���� �������� �� ���������� �����������
            if (visited[i] && handshakeCount[i] == handshake - 1) {
                Edge* edge = graph->vertices[i].edges;

                while (edge != NULL) {
                    // ���� �������� ������� ��� �� ��������
                    if (!visited[edge->destination]) {
                        visited[edge->destination] = true;
                        handshakeCount[edge->destination] = handshake;
                        cout << graph->vertices[edge->destination].name << endl;
                        handshakeFound = true;
                    }

                    edge = edge->next;
                }
            }
        }
        if (!handshakeFound) {
            break;
        }
    }

    free(visited);
    free(handshakeCount);
}

// ����� ����������� ���� � ����� � �������������� ��������� ��������
void shortestPath(Graph* graph, const string startName, const string endName) {
    int startIndex = findVertexIndex(graph, startName);
    int endIndex = findVertexIndex(graph, endName);

    // ��������, ������� �� ��������� �������
    if (startIndex == -1 || endIndex == -1) {
        cout << "������: ��������� ������� �� �������.\n";
        return;
    }

    bool* visited = (bool*)malloc(graph->vertex_count * sizeof(bool));
    memset(visited, false, graph->vertex_count * sizeof(bool));

    int* distance = (int*)malloc(graph->vertex_count * sizeof(int));
    for (int i = 0; i < graph->vertex_count; i++) {
        distance[i] = INT_MAX;
    }

    int* previous = (int*)malloc(graph->vertex_count * sizeof(int));
    memset(previous, -1, graph->vertex_count * sizeof(int));

    distance[startIndex] = 0;

    for (int i = 0; i < graph->vertex_count; i++) {
        int minDistance = INT_MAX;
        int currentVertexIndex = -1;

        // ������� ������� � ����������� ����������� �� ������������ ������
        for (int j = 0; j < graph->vertex_count; j++) {
            if (!visited[j] && distance[j] < minDistance) {
                minDistance = distance[j];
                currentVertexIndex = j;
            }
        }

        if (currentVertexIndex == -1) {
            break;
        }

        visited[currentVertexIndex] = true;
        Vertex* currentVertex = &(graph->vertices[currentVertexIndex]);
        Edge* edge = currentVertex->edges;

        while (edge != NULL) {
            int neighborIndex = edge->destination;

            // �������� �� ������������� ���������
            if (!visited[neighborIndex] && edge->rating > 0) {
                int newDistance = distance[currentVertexIndex] + edge->rating;

                if (newDistance < distance[neighborIndex]) {
                    distance[neighborIndex] = newDistance;
                    previous[neighborIndex] = currentVertexIndex;
                }
            }

            edge = edge->next;
        }
    }

    // ��������, ��� �� ������ ���������� ����
    if (distance[endIndex] == INT_MAX) {
        cout << "���������� ���� ����� ��������� �� ������.\n";
    }
    else {
        cout << "���������� ���� ����� ���������: ";

        int* path = (int*)malloc(graph->vertex_count * sizeof(int));
        int pathLength = 0;
        int currentVertexIndex = endIndex;

        // ���������� ���� �� �������� ������� � ���������
        while (currentVertexIndex != -1) {
            path[pathLength] = currentVertexIndex;
            pathLength++;
            currentVertexIndex = previous[currentVertexIndex];
        }

        // ����� ����
        for (int i = pathLength - 1; i >= 0; i--) {
            cout << graph->vertices[path[i]].name;

            if (i > 0) {
                printf(" -> ");
            }
        }

        cout << "\n����������: " << distance[endIndex] << endl;

        free(path);
    }

    free(visited);
    free(distance);
    free(previous);
}

// ����� ����� �� ������� �������-����������
Edge* findEdge(Edge* edges, int destination) {
    Edge* current_edge = edges;
    while (current_edge != NULL) {
        if (current_edge->destination == destination) {
            return current_edge;
        }
        current_edge = current_edge->next;
    }
    return NULL;
}

//������� ������ ������� 
int findVertexIndex(Graph* graph, const string name) {
    for (int i = 0; i < graph->vertex_count; i++) {
        if (graph->vertices[i].name == name) {
            return i;
        }
    }
    return -1;
}

// ������� ������ ������� ����������� �����
void findConnectedComponents(Graph* graph) {
    bool* visited = (bool*)calloc(graph->vertex_count, sizeof(bool));
    int componentIndex = 1;

    printf("������� ���������� �����:\n");

    for (int i = 0; i < graph->vertex_count; i++) {
        if (!visited[i]) {
            cout << "����������" << componentIndex << ": ";
            dfs(graph, i, visited, componentIndex);
            cout << endl;
            componentIndex++;
        }
    }

    free(visited);
}

// ������� ��� ������ ����� � �������
void dfs(Graph* graph, int vertex, bool* visited, int componentIndex) {
    visited[vertex] = true;
    cout << graph->vertices[vertex].name;

    Edge* current_edge = graph->vertices[vertex].edges;
    while (current_edge != NULL) {
        int destination = current_edge->destination;
        int rating = current_edge->rating;

        if (!visited[destination] && rating > 0) {
            dfs(graph, destination, visited, componentIndex);
        }
        current_edge = current_edge->next;
    }
}
