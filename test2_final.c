#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>

int main(void)
{
    int n;

    printf("Enter the number of nodes\n");

    scanf("%d", &n);

    int **graph;

    graph = (int**) malloc(n * sizeof(int*));

    for (int i = 0; i < n; ++i)
    {
        graph[i] = (int*) malloc(n * sizeof (int));
    }

    printf("Enter the adjacency matrix:\n");
    char c;
    int row = 0, col = 0, line_counter = 0;
    c = getchar(); // skip the \n after dimension input
    while (line_counter < n) {
        c = getchar();
        if (c == '\n') {
            line_counter++;
            row++;
            col = 0;
            continue;
        }
        else if ((c == '0') || (c == '1')) {
            graph[row][col] = c - '0';
            col++;
        }
    }

    
    int a;
    bool flag = true;

    for (int i = 0; (i < n) && flag; ++i)
    {
        a = 0;
        for (int j = 0; j < n; ++j)
        {
            if (graph[i][j] ==1) {
                a++;
                if (a > 2) 
                    flag = false;
            }
        }
        if (a == 1)
            flag = false;
    }

    if (flag)
        printf("is a simple cycle\n");
    else
        printf("is not a simple cycle\n");


    FILE* dotfile = fopen("./graph.dot", "w+"); // Создание файла формата .dot для записи ребер графа
    fputs("graph hometask2 {\n", dotfile); // Написание первой строчки в файле

    for (int i = 0;i < n; ++i) {
        fprintf(dotfile, "\t%d\n", i + 1);
        for (int j = i; j < n; ++j)
            if (graph[i][j] == 1) // Если мы находим в матрице смежности единицу (т.е. есть связть между вершинами)
                fprintf(dotfile, "\t%d -- %d\n", i+1, j+1); // Записываем связь в созданный файл;
    }

    fputs("}", dotfile); // Конец кода
    fclose(dotfile); // Закрытие файла
    system("dot -Tpdf graph.dot -o graph.pdf"); // Creating a graphic visualization using a .pdf file
     
    for(int i = 0; i < n; ++i) 
        free(graph[i]);
        
    return 0;
}