#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <limits.h> 
#define _CRT_SECURE_NO_WARNINGS

int minDistance(int dist[], bool sptSet[], int size) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < size; v++) {
        if (!sptSet[v] && dist[v] < min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

void printresult(int dist[], int size) {
    printf("\nВершина\t Расстояние от источника\n");
    for (int i = 0; i < size; i++) {
        printf("%d \t %d\n", i + 1, dist[i]);
    }
}

void dijkstra(int** graph, int src, int size) {
    int* dist = (int*)malloc(size * sizeof(int));  // Массив для хранения кратчайших расстояний
    bool* sptSet = (bool*)malloc(size * sizeof(bool));  // Массив для хранения включенных в дерево вершин

    for (int i = 0; i < size; i++) {
        dist[i] = INT_MAX;  // Расстояние до всех вершин как бесконечность
        sptSet[i] = false;  // Обхода не было
    }

    dist[src] = 0;  // Расстояние до самой себя равно 0

    for (int count = 0; count < size - 1; count++) {
        int u = minDistance(dist, sptSet, size);
        sptSet[u] = true;  // Добавляем вершину

        // Обновляем значения расстояний для смежных вершин
        for (int v = 0; v < size; v++) {
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    printresult(dist, size);
}

int safe_input() {
    int value;
    while (1) {
        if (scanf("%d", &value) != 1) {
            while (getchar() != '\n');  // Очищаем буфер ввода
            printf("Ошибка! Введите число: ");
        }
        else if (value < 0) {
            printf("Ошибка! Введите положительное значение: ");
        }
        else {
            break;  // Ввод корректен
        }
    }
    return value;
}


int main() {
    setlocale(LC_ALL, "");
    int touch, size, orientation, repeat = 1;
    int** graph;

    while (repeat == 1) {
        printf("Введите количество вершин графа: ");
        size = safe_input();
        if (size == 0) {
            printf("Ошибка! Количество вершин не может быть нулевым. Попробуйте снова.\n");
            continue;
        }

        graph = (int**)malloc(size * sizeof(int*));
        for (int i = 0; i < size; i++) {
            graph[i] = (int*)malloc(size * sizeof(int));
        }

        do {
            printf("Выберите заполнение матрицы расстояний:\n1.Самостоятельное заполнение\n2.Автоматическое заполнение\nНажмите на соответсвующую клавишу: ");
            touch = safe_input();
            if (touch != 1 && touch != 2) {
                printf("Ошибка! Пожалуйста, выберите 1 или 2.\n");
            }
        } while (touch != 1 && touch != 2);

        do {
            printf("\nВыберите ориентированность графа:\n1.Ориентированный\n2.Неориентированный\nНажмите на соответсвующую клавишу: ");
            orientation = safe_input();
            if (orientation != 1 && orientation != 2) {
                printf("Ошибка! Пожалуйста, выберите 1 или 2.\n");
            }
        } while (orientation != 1 && orientation != 2);

        if (touch == 1) {
            printf("Введите матрицу расстояний (вводите 0 для отсутствующих рёбер):\n");
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    printf("Вес ребра между вершинами %d и %d: ", i + 1, j + 1); 
                    graph[i][j] = safe_input();
                }
            }
        }

        else if (touch == 2) {
            srand(time(NULL));
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    if (i == j) {
                        graph[i][j] = 0;
                    }
                    else {
                        if (orientation == 2) {
                            graph[i][j] = rand() % 50 + 1;
                            graph[j][i] = graph[i][j]; // Если неориентированный граф
                        }
                        else {
                            graph[i][j] = rand() % 50 + 1;
                        }
                    }
                }
            }
        }
        else {
            printf("Ошибка выбора!\n");
            continue;
        }

        printf("\nМатрица расстояний:\n");
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                printf("%3d", graph[i][j]);
            }
            printf("\n");
        }

        int src;
        do {
            printf("Введите номер вершины-источника (от 1 до %d): ", size); 
            src = safe_input();

            if (src < 1 || src > size) {
                printf("Некорректный номер вершины. Допустимые значения: от 1 до %d\n", size);
                continue;
            }
        } while (src < 1 || src > size);

        dijkstra(graph, src - 1, size); 

        do {
            printf("Хотите выполнить алгоритм снова? (1 - да, 0 - нет): ");
            repeat = safe_input();
            if (repeat != 0 && repeat != 1) {
                printf("Ошибка! Пожалуйста, выберите 1 или 0.\n");
            }
        } while (repeat != 0 && repeat != 1);

        if (repeat == 0) {
            printf("Программа завершена.\n");
        }
    }

    return 0;
}
