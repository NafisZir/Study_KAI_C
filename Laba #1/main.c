#include <stdio.h>

void solution2(int arr[], float *sum, float *pos, int n)
{
    FILE *file3;
    file3 = fopen("in2.txt", "r");
    float g;
    int i;
    for(i=0; i < n; ++i)
        fscanf(file3, "%d", &(arr[i]));
    fclose(file3);
    for(i = 0; i < n; ++i)
    {
        g = arr[i];
        *sum = *sum + g;
        *pos = *pos + 1/g;
    }
    *pos = 1/(*pos);
}

void solution(int n, float *sum, float *pos) // Функция решает задание
{
   int i = 1;
   float c;
   while(i <= n)
   {
       printf("%s %d %s", "Enter capacitor capacitance ", i , " : ");
       scanf("%f", &c);
       *sum = *sum + c;
       *pos = *pos + 1/c;
       ++i;
   }
    *pos = 1/(*pos);
}

int read_from_console() // Чтение данных из консоли
{
    int n;
    printf("Enter: ");
    scanf("%d", &n);
    return n;
}

void console_output(float sum, float pos) // Вывод результата в консоль
{
    printf("%s %f\n", "The capacitor volume in parallel connection is ", sum);
    printf("%s %f\n", "The capacitor volume in series connection is ", pos);
}

void write_to_file(float sum, float pos) // Вывод результата в файл
{
    FILE *file2;
    file2 = fopen("out.txt", "w");
    fprintf(file2, "%s %f\n", "The capacitor capacitance in parallel connection is ", sum);
    fprintf(file2, "%s %f\n", "The capacitor capacitance in series connection is ", pos);
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

main ()
{
    int arr[100];
    int k, n, j, i = 1;
    printf("Hello!\n");
    while(i == 1)
    {
       float pos = 0.0, sum = 0.0;
       printf("Where to get data? 0 - from file, 1 - from console\n"); // Спрашиваем у пользователя, откуда читать данные
        scanf("%d", &k);
        if(k == 0)
            n = capture_from_file();
        else
            n = read_from_console();


        if(k == 0)
            solution2(arr, &sum, &pos, n);
        else
            solution(n, &sum, &pos);


        printf("Where do you want to output data? 0 - in file, 1 - in console\n"); // Куда сохранять результат
        scanf("%d", &j);
        if(j == 0)
            write_to_file(sum, pos);
        else
            console_output(sum, pos);


        if(k == 0)
            break;
        printf("\nDo you want to repeat the input?");
        scanf("%d", &i);
    }
    printf("Good bye!");
    return 0;
}
