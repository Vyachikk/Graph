#include "graph.h"
#include <iostream>

using namespace std;

//������� ������ ���� ���������
void printMenu(string status_msg) {
    cout << "=============����=============\n\n";
    cout << "1. �������� �������\n";
    cout << "2. ������� �������\n";
    cout << "3. �������� �����\n";
    cout << "4. ������� �����\n";
    cout << "5. ������������� �����\n";
    cout << "6. ������������� �������\n";
    cout << "7. ������� ����\n";
    cout << "8. ����� �����\n";
    cout << "9. ����� ����������� ����\n";
    cout << "0. ������� ���������� �����\n";
    cout << "x. �����\n";
    cout << "\n================================\n";
    cout << status_msg << endl;
    cout << "������� ����� ���������� ������: ";
}

int main() {
    string status_msg = "";

    setlocale(LC_ALL, "Rus");

    Graph* graph = createGraph();

    char choice;
    string name1;
    string name2;
    int rating;
    int maxHandshakes;
    string newName;

    while (true) {
        
        printMenu(status_msg);
        status_msg = "";
        cin >> choice;

        switch (choice) {
        case '1':
            cout << "������� ��� �������: ";
            cin >> name1;
            addVertex(graph, name1, status_msg);
            system("cls");
            break;
        case '2':
            cout << "������� ��� �������: ";
            cin >> name1;
            removeVertex(graph, name1, status_msg);
            system("cls");
            break;
        case '3':
            cout << "������� ��� ������ �������: ";
            cin >> name1;
            cout << "������� ��� ������ �������: ";
            cin >> name2;
            cout << "������� ������� �����: ";
            cin >> rating;
            addEdge(graph, name1, name2, rating, status_msg);
            system("cls");
            break;
        case '4':
            cout << "������� ��� ������ �������: ";
            cin >> name1;
            cout << "������� ��� ������ �������: ";
            cin >> name2;
            removeEdge(graph, name1, name2, status_msg);
            system("cls");
            break;
        case '5':
            cout << "������� ��� ������ �������: ";
            cin >> name1;
            cout << "������� ��� ������ �������: ";
            cin >> name2;
            cout << "������� ����� ������� �����: ";
            cin >> rating;
            editEdge(graph, name1, name2, rating, status_msg);
            system("cls");
            break;
        case '6':
            cout << "������� ��� �������: ";
            cin >> name1;
            cout << "������� ����� ��� �������: ";
            cin >> newName;
            editVertex(graph, name1, newName, status_msg);
            system("cls");
            break;
        case '7':
            system("cls");
            printGraph(graph);
            break;
        case '8':
            cout << "������� ��� �������: ";
            cin >> name1;
            cout << "������� ������������ ���������� �����������: ";
            cin >> maxHandshakes;
            system("cls");
            breadthFirstSearch(graph, name1, maxHandshakes, status_msg);
            break;
        case '9':
            cout << "������� ��� ��������� �������: ";
            cin >> name1;
            cout << "������� ��� �������� �������: ";
            cin >> name2;
            system("cls");
            shortestPath(graph, name1, name2);
            break;
        case '0':
            system("cls");
            findConnectedComponents(graph);
            break;
        case 'x':
            freeGraph(graph);
            freeEdges(graph);
            cout << "�����.\n";
            exit(0);
        default:
            status_msg = "������: ������������ ����� ������ ����.\n";
            system("cls");
            break;
        }
    }

    return 0;
}
