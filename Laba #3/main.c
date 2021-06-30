#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#define N 100

void solution(int **arr, int n , int m, int res[])
{
    int i, j, k;
    for(i = 0; i < n; ++i)
    {
        k = 0;
        for(j = 0; j < m; ++j)
        {
            if(arr[i][j] < 0)
                ++k;
        }
        res[i] = k;
    }
}

void array_creation_c(int **arr, int n, int m)
{
    int i, j, k;
    for(i = 0; i < n; ++i)                        // выделение памяти на строки и заполнение массива
    {
        k = 0;
        while(k < 1)
        {
            arr[i] = (int*)malloc(m*sizeof(int));
            if(arr == NULL)
            {
                printf("Error!");
                continue;
            }
            ++k;
        }

        for(j = 0; j < m; ++j)
        {
            printf("arr[%d][%d] = ", i, j);
            scanf("%d", &arr[i][j]);
        }
    }
}

void array_creation_f(int **arr, int n, int m)
{
    FILE *file1;
    file1 = fopen("in2.txt", "r");
    int i, j, k;
    for(i = 0; i < n; ++i)                        // выделение памяти на строки и заполнение массива
    {
        k = 0;
        while(k < 1)
        {
            arr[i] = (int*)malloc(m*sizeof(int));
            if(arr == NULL)
            {
                printf("Error!");
                continue;
            }
            ++k;
        }

        for(j = 0; j < m; ++j)
        {
           fscanf(file1, "%d", &(arr[i][j]));
        }
    }
    fclose(file1);
}

void array_creation(int **arr, int n, int m, int k, int res[])
{
    int i = 0, j;
    while(i < 1)                                  // Выделение памяти для массива указателей
    {
        arr = (int**)malloc(n*sizeof(int*));
        if(arr == NULL)
        {
            printf("Error!");
            continue;
        }
        ++i;
    }

    if(k == 1)
        array_creation_c(arr, n, m);
    else
        array_creation_f(arr, n, m);

    for(i = 0; i < n; ++i)                         // вывод массива на экран
    {
        for(j = 0; j < m; ++j)
        {
            printf("%5d", arr[i][j]);
        }
        printf("\n");
    }

    solution(arr, n , m, res);

        for(i = 0; i < n; ++i)
        {
            free(arr[i]);
        }
        free(arr);
}

void console_output(int n, int res[]) // Вывод результата в консоль
{
    int i;
    for(i = 0; i < n; ++i)
    {
        printf("%s%d%s%d\n", "Number of negative elements in a row ", i+1," : ",res[i]);
    }
}

void write_to_file(int n, int res[]) // Вывод результата в файл
{
    FILE *file2;
    file2 = fopen("out.txt", "w");
    int i;
    for(i = 0; i < n; ++i)
    {
        fprintf(file2,"%s%d%s%d\n", "Number of negative elements in a row ", i+1," : ",res[i]);
    }
    fclose(file2);
}

int main()
{
    FILE *file;
    int **arr, n, m, k, j, i = 1, res[N];
    printf("Hello!\n");
    while(i == 1)
    {
        printf("Where to get data? 0 - from file, 1 - from console\n"); // Спрашиваем у пользователя, откуда читать данные
        scanf("%d", &k);
        if(k == 0)
        {
            file = fopen("in.txt", "r");
            fscanf(file,"%d", &n);
            fscanf(file,"%d", &m);
            fclose(file);
        }
        else
        {
            printf("n: ");
            scanf("%d", &n);
            printf("m: ");
            scanf("%d", &m);
        }

        array_creation(arr, n, m, k, res);

        printf("Where do you want to output data? 0 - in file, 1 - in console\n"); // Куда сохранять результат
        scanf("%d", &j);
        if(j == 0)
            write_to_file(n, res);
        else
            console_output(n, res);

        if(k == 0)
            break;
        printf("\nDo you want to repeat the input?");
        scanf("%d", &i);
    }
    printf("Good bye!");
    return 0;
}
