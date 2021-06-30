#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <malloc.h>
#include <string.h>

#define N 20

struct person_data
{
    char name[N];
    char post[N];
    char place[N];
};
struct people
{
    struct person_data data;
    struct people *next;
};

void list_node_swap(struct people *p1, struct people *p2)
{
    struct person_data tmp = p1->data;
    p1->data = p2->data;
    p2->data = tmp;
}
void sort(struct people *p)
{
    int sorted = 1;
    do {
        sorted = 1;
        for (struct people *current = p; current != NULL; current = current->next)
        {
            if (current->next)
            {
                if (strcmp(current->data.name, current->next->data.name) > 0)
                {
                    list_node_swap(current, current->next);
                    sorted = 0;
                }
            }
        }
    } while (!sorted);
}

void setDefaultValue(struct people *p)
{
    int i;
    char D_name[N] = "Tahir";
    char D_post[N] = "programmer";
    char D_place[N] = "Moskow";
    while(p != NULL)
    {
        for(i = 0; i < N; ++i)
        {
            p->data.name[i] = D_name[i];
            p->data.post[i] = D_post[i];
            p->data.place[i] = D_place[i];
        }
        p = p->next;
    }
}

void write_to_file(struct people *p)
{
    FILE *file;
    file = fopen("table.txt", "w");
    while(p != NULL)
    {
        fprintf(file, "%s %s %s\n", p->data.name, p->data.post, p->data.place);
        p = p->next;
    }
    fclose(file);
}

void add_field(struct people *p)
{
  struct people *temp, *p2;
  temp = (struct people*)malloc(sizeof(struct people));
  p2 = p->next; // сохранение указателя на следующий узел
  p->next = temp; // предыдущий узел указывает на создаваемый
  printf("Введите имя: ");
  scanf("%s", temp->data.name);
  printf("Введите должность: ");
  scanf("%s", temp->data.post);
  printf("Введите место проживание: ");
  scanf("%s", temp->data.place);
  temp->next = p2;
  printf("\n"); // созданный узел указывает на следующий элемент
}

struct people *search_element(struct people *p, char n[])
{
    while(p != NULL)
    {
        if(strcmp(p->data.name,n) == 0)
            break;
        p = p->next;
    }
    return p;
}

void output_table(struct people *p)
{
     printf("Имя         должность     место проживание\n");
     while(p != NULL)   // пока не конец стека
     {
           printf("%s %15s %15s\n", p->data.name, p->data.post, p->data.place);
           p = p->next; // продвижение по списку
     }
     printf("\n");
}

void create(struct people **q)
{
    FILE *file;
    file = fopen("table.txt", "r");
    struct people *tmp, *s;
    int i = 0;
    tmp = *q;
    while(i != 1)
    {
        i = 1;
        if(*q == NULL)
        {
            *q = malloc(sizeof(struct people));
            tmp = *q;
        }
        else
        {
            while(tmp->next != NULL)
            {
                tmp = tmp->next;
            }
            tmp->next = malloc(sizeof(struct people));
            s = tmp;
            tmp = tmp->next;
        }

        if(fscanf (file, "%s%s%s", &(tmp->data.name), &(tmp->data.post), &(tmp->data.place)) != EOF)
        {
            i = 0;
        }
        tmp->next = NULL;
    }
    s->next = NULL;
}

int main()
{
    setlocale(LC_ALL, "Rus");

    int n, *p, i = 1;
    char name[15];
    struct people *head = NULL; // адрес, указывающий на голову стека
    create(&head);
    p = head;
    output_table(head);
    printf("1) Присвоение всем элементам предустановенных значений.\n");
    printf("2) Печать всех элементов в отсортированном виде.\n");
    printf("3) Добавить новый элемент после заданного. Элемент задан значением информационного поля.\n");

    while(i == 1)
    {
        printf("Какую функцию выбираете?\n");
        scanf("%d", &n);
        if(n == 1)
        {
            setDefaultValue(head);
            write_to_file(head);
            output_table(head);
        }

        if(n == 2)
        {
            sort(head);
            output_table(head);
        }

        if(n == 3)
        {
            printf("Введите имя: ");
            scanf("%s", name);
            p = search_element(head, name);
            add_field(p);
            write_to_file(head);
        }
        printf("Хотите продолжить или выйти (1/0)?\n");
        scanf("%d", &i);
    }
    printf("Приятно было поработать)");
    free(head);
    return 0;
}
