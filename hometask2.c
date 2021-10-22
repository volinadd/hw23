
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>



int main(void)
{
    int n;
    int i, j;
   
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
        else if (('0' <= c ) || (c == '9')) {
            graph[row][col] = c - '0';
            col++;
        }
    }
    int a;

    int check = 0;

    for (int i = 0; i < n; ++i)
    {
        a = 0;
        for (int j = 0; j < n; ++j)
        {
            if (graph[i][j] ==1)
            {
                a++;
            }
        }
        if (a > 2)
        {
            printf("is not a simple cycle\n");
            check = 1;
            break;
        }
    }
    if (check == 0)
    {
        printf("is a simple cycle\n");
    }


  
        

    FILE *gr = fopen("graph.dot", "w");
    fprintf(gr, "graph D {\n");
    for (int i = 0; i < n; i++) {
        fprintf(gr, "%d\n", i + 1);
        for (int j = i; j < n; j++) 
            for (int k = 0; k < graph[i][j]; k++) {
                fprintf(gr, "\t");
                fprintf(gr, "%d", i + 1);
                fprintf(gr, " -- ");
                fprintf(gr, "%d", j + 1);
                fprintf(gr, "\n");
            }
    }
    fprintf(gr, "}");
    fclose(gr);
    system("dot -Tpdf graph.dot -o graph.pdf");
        
    return 0;
}

