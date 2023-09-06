#include "graph.h"
#include <iostream>

using namespace std;

//Функция вывода меню программы
void printMenu(string status_msg) {
    cout << "=============Меню=============\n\n";
    cout << "1. Добавить вершину\n";
    cout << "2. Удалить вершину\n";
    cout << "3. Добавить ребро\n";
    cout << "4. Удалить ребро\n";
    cout << "5. Редактировать ребро\n";
    cout << "6. Редактировать вершину\n";
    cout << "7. Вывести граф\n";
    cout << "8. Обход графа\n";
    cout << "9. Поиск кратчайшего пути\n";
    cout << "0. Связные компоненты графа\n";
    cout << "x. Выход\n";
    cout << "\n================================\n";
    cout << status_msg << endl;
    cout << "Введите номер выбранного пункта: ";
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
            cout << "Введите имя вершины: ";
            cin >> name1;
            addVertex(graph, name1, status_msg);
            system("cls");
            break;
        case '2':
            cout << "Введите имя вершины: ";
            cin >> name1;
            removeVertex(graph, name1, status_msg);
            system("cls");
            break;
        case '3':
            cout << "Введите имя первой вершины: ";
            cin >> name1;
            cout << "Введите имя второй вершины: ";
            cin >> name2;
            cout << "Введите рейтинг ребра: ";
            cin >> rating;
            addEdge(graph, name1, name2, rating, status_msg);
            system("cls");
            break;
        case '4':
            cout << "Введите имя первой вершины: ";
            cin >> name1;
            cout << "Введите имя второй вершины: ";
            cin >> name2;
            removeEdge(graph, name1, name2, status_msg);
            system("cls");
            break;
        case '5':
            cout << "Введите имя первой вершины: ";
            cin >> name1;
            cout << "Введите имя второй вершины: ";
            cin >> name2;
            cout << "Введите новый рейтинг ребра: ";
            cin >> rating;
            editEdge(graph, name1, name2, rating, status_msg);
            system("cls");
            break;
        case '6':
            cout << "Введите имя вершины: ";
            cin >> name1;
            cout << "Введите новое имя вершины: ";
            cin >> newName;
            editVertex(graph, name1, newName, status_msg);
            system("cls");
            break;
        case '7':
            system("cls");
            printGraph(graph);
            break;
        case '8':
            cout << "Введите имя вершины: ";
            cin >> name1;
            cout << "Введите максимальное количество рукопожатий: ";
            cin >> maxHandshakes;
            system("cls");
            breadthFirstSearch(graph, name1, maxHandshakes, status_msg);
            break;
        case '9':
            cout << "Введите имя начальной вершины: ";
            cin >> name1;
            cout << "Введите имя конечной вершины: ";
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
            cout << "Выход.\n";
            exit(0);
        default:
            status_msg = "Ошибка: некорректный номер пункта меню.\n";
            system("cls");
            break;
        }
    }

    return 0;
}
