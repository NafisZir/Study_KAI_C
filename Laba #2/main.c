#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.14159265
#define condition 0.25
#define N 1000

int solution(float arr[N], int n)
{
    int i, k = 2;
    float r, a = 0.01;
    for(i = 0; i<n; ++i)
    {
        printf("%f\n", a);
        arr[i] = a;
        r = (a + k) * (PI / 180.0);
        a = sin(r);
        ++k;
    }
    int j = 2, result = 0, s = 1;
    i = 0;
    while(i<n)
    {
        if(arr[i] < condition)
            result += 1;
        i = ((int) pow(j, s)) - 1;
        ++s;
    }
    return result;
}

int read_from_console() // Чтение данных из консоли
{
    int n;
    printf("Enter: ");
    scanf("%d", &n);
    return n;
}

void console_output(int result) // Вывод результата в консоль
{
    printf("Result: %d\n", result);
}

void write_to_file(int result) // Вывод результата в файл
{
    FILE *file2;
    file2 = fopen("out.txt", "w");
    fprintf(file2, "%s%d", "Result: ", result);
    fclose(file2);
}

int capture_from_file() // Чтение данных из файла
{
    int n;
    FILE *file;
    file = fopen("in.txt", "r");
    fscanf(file, "%d", &n);
    fclose(file);
    return n;
}

int main ()
{
    int x, n, y, z = 1, result;
    float arr[N];
    printf("Hello!\n");
    while(z == 1)
    {
        printf("Where to get data? 0 - from file, 1 - from console\n"); // Спрашиваем у пользователя, откуда читать данные
        scanf("%d", &x);
        if(x == 0)
            n = capture_from_file();
        else
            n = read_from_console();

        result = solution(arr, n);

        printf("Where do you want to output data? 0 - in file, 1 - in console\n"); // Куда сохранять результат
        scanf("%d", &y);
        if(y == 0)
            write_to_file(result);
        else
            console_output(result);

        if(x == 0)
            break;
        printf("\nDo you want to repeat the input?");
        scanf("%d", &z);
    }
    printf("Good bye!");
    return 0;
}
