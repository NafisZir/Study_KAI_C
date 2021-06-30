#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#define N 100

 void solution(int n, char *str, char result[])
 {
     int start = 0, j = 0, quantity = 0, i = 0, s;

     for(i = 0; i < n; ++i)
     {
         result[i] = '\0';
     }
     for(i = 0; i < n; ++i)
     {
         if(i == (n-1))
         {
             for(start; start < n; ++start)
             {
                 result[j] = str[start];
                 ++j;
             }
         }

         if(str[i] == '(')
         {
             s = i;
             for(start; start < s; ++start)
             {
                 result[j] = str[start];
                 ++j;
             }
             while(str[i] != ')')
             {
                 ++i;
             }
             start = (i+1);
         }
     }
 }


int read_from_file(int n, char *str, int *len) // функция получения данных из файла
{
    FILE *file;
    int i = 0;
    char arr[10];
    char arr2[10];

    fflush(stdin);
    printf("Enter file name[in.txt]: ");
    fgets(arr, 9, stdin);
    fflush(stdin);
    if(arr[0] != '\n')
    {
        while(arr[i] != '\n') // убираем \n из строки
        {
            arr2[i] = arr[i];
            ++i;
        }
        arr2[i] = '\0';
        file = fopen(arr2, "r");
    }
    else
    {
        file = fopen("in.txt", "r");
    }

    char c = fgetc(file);
    while (c != EOF)
    {
        str[(*len)++] = c; // заносим в строку новый символ

        // если реальный размер больше размера контейнера, то увеличим его размер
        if (*len >= n)
        {
            n *= 2; // увеличиваем ёмкость строки в два раза
            str = (char*) realloc(str, n * sizeof(char)); // создаём новую строку с увеличенной ёмкостью
        }

        c = fgetc(file); // считываем следующий символ
    }

    str[*len] = '\0';
    fclose(file);

    return str;
}

int read_from_console(int n, char *str, int *len)
{
    fflush(stdin);
    printf("Enter: ");
    char c = getchar();

    while (c != '\n')
    {
        str[(*len)++] = c;

        if (*len >= n)
        {
            n *= 2; // увеличиваем ёмкость строки в два раза
            str = (char*) realloc(str, n * sizeof(char)); // создаём новую строку с увеличенной ёмкостью
        }

        c = getchar(); // считываем следующий символ
    }

    str[*len] = '\0'; // завершаем строку символом конца строки

    return str; // возвращаем указатель на считанную строку
}

void console_output(char result[]) // Вывод результата в консоль
{
    printf("%s\n", result);
}

void write_to_file(char result[]) // Вывод результата в файл
{
    FILE *file2;
    int i = 0;
    char arr[10];
    char arr2[10];

    fflush(stdin);
    printf("Enter file name[out.txt]: ");
    fgets(arr, 9, stdin);
    fflush(stdin);
    if(arr[0] != '\n')
    {
        while(arr[i] != '\n') // убираем \n из строки
        {
            arr2[i] = arr[i];
            ++i;
        }
        arr2[i] = '\0';
        file2 = fopen(arr2, "w");
    }
    else
    {
        file2 = fopen("out.txt", "w");
    }

    fprintf(file2,"%s", result);
    fclose(file2);
}

int main()
{
    int  i = 1;
    char *str;
    printf("Hello!\n");
    while(i == 1)
    {
        int n = 1, len = 0, q = 0, k, j;
        while(q == 0)
        {
            str = (char*)malloc(n*sizeof(char));
            if(str == NULL)
            {
                printf("Error!");
                continue;
            }
            ++q;
        }
        printf("Where to get data? 0 - from file, 1 - from console\n"); // Спрашиваем у пользователя, откуда читать данные
        scanf("%d", &k);
        if(k == 0)
            str = read_from_file(n, str, &len);
        else
            str = read_from_console(n, str, &len);

        char result[len];
        solution(len, str, result);

        free(str);

        printf("Where do you want to output data? 0 - in file, 1 - in console\n"); // Куда сохранять результат
        scanf("%d", &j);
        if(j == 0)
            write_to_file(result);
        else
            console_output(result);

        if(k == 0)
            break;
        printf("\nDo you want to repeat the input?");
        scanf("%d", &i);
    }
    printf("Good bye!");
    return 0;
}
