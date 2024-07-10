// FILE_NAME.C
// made by rikko
#define MAX_NAME_LENGTH 30

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>

typedef struct
{
  char name[MAX_NAME_LENGTH];
  uint16_t age;
  double wage;
  // deleted = '*' -> deleted
  bool deleted;
} Person;

typedef struct Archive
{
  Person p[30];
  long counter;
} Archive;

// Global variable object
Archive list;

// vars to save time in case of rewritting
const char *FILE_NAME = "archive.bin";
const uint16_t MAX_LEADERBOARD_NUM = 5;

// regex script to clear the screen in powershell
#define clrscr() printf("\e[1;1H\e[2J")

// EXTRA FUNCTIONS

void read_name(char *message, Person *p)
{
  puts(message);
  fgets(p->name, MAX_NAME_LENGTH, stdin);
}

void read_age(const char *message, Person *p)
{
  puts(message);
  scanf(" %hu", &p->age);
}

void read_wage(const char *message, Person *p)
{
  puts(message);
  scanf(" %lf", &p->wage);
}

FILE *create_fhandle(const char *fail_message, const char *mode)
{
  FILE *fh;
  if ((fh = fopen(FILE_NAME, mode)) == NULL)
  {
    puts(fail_message);
    fclose(fh);
  }

  return fh;
}

static inline void Insert(Person p)
{
  list.p[list.counter++] = p;
};

static inline void Inic()
{
  list.counter = 0;
}

void search_name()
{
  char user_input[30];
  puts("Input your search term:");
  fgets(user_input, 30, stdin);

  for (int i = 0; i <= list.counter; i++)
    if (memcmp(user_input, list.p[i].name, MAX_NAME_LENGTH) == 0)
    {
      printf("%s was found and has %hu years old!", user_input, list.p[i].age);
      break;
    }
}

void show_leaderboard(const char *message)
{
  puts(message);

  for (int i = 0; i < list.counter; i++)
    if (i < MAX_LEADERBOARD_NUM && !list.p[i].deleted)
      printf("%d | %s", i, list.p[i].name, list.p[i].age);
}

// Displays the full reg content
void show_full_list()
{
  if (list.counter == 0)
  {
    puts("The list is empty!");
    return;
  }

  // read and print the whole group of people
  for (int i = 0; i < list.counter; i++)
    printf("%ld - %15s [ %3hu y.o | makes %6.2lf | Banned:%d ]\n", i, list.p[i].name, list.p[i].age, list.p[i].wage, list.p[i].deleted);
}

// reads data from file
void data_Load(const char *fail_message)
{
  FILE *file_stream = create_fhandle(fail_message, "rb");

  fread(&list, sizeof(Archive), 1, file_stream);

  fclose(file_stream);
  // printf("Data read: %zu \n", read_data);
}

// writes data back to the file
void data_Save()
{
  FILE *file_stream = create_fhandle(NULL, "w+b");

  if (list.counter > 0)
    fwrite(&list, sizeof(Archive), 1, file_stream);

  fclose(file_stream);
  // printf("Data written: %zu \n", written_data);
}
void register_insert()
{
  Person p;

  read_name("Name: ", &p);

  read_age("Age: ", &p);

  read_wage("Wage: ", &p);

  p.deleted = false;

  Insert(p);
}

// MAIN MENU
void register_change(const char *message_fail)
{
  long id;
  // In order to reference the user
  show_full_list(list);

  if (list.counter == 0)
  {
    puts(message_fail);
    return;
  }

  puts("\nwhich one you want to Edit? 0 - Back");
  scanf(" %lu", &id);
  Person *p = &(list.p[id]);

  // Create a copy of the register
  char option = -1;

  puts("1. Nome");
  puts("2. Age");
  puts("3. Wage");
  puts("4. Status\n");

  option = fgetc(stdin);

  // Edit the created copy
  switch (option)
  {
  case '1':
    read_name("New Name:", p);
    break;
  case '2':
    read_age("New Age:", p);
    break;
  case '3':
    read_wage("New Wage: ", p);
    break;
  case '4':
    // User delete / recover
    p->deleted = !p->deleted;
    break;
  default:
    return;
  }
  data_Save();
  // retrieve back the data
};

void register_delete(const char *fail_message)
{
  // loads player board
  show_full_list("\nTop most cute:");

  long id;
  if ((scanf(" %ld", &id)) == 0)
    puts(fail_message);

  list.p[id].deleted = true;
};

void register_search(const Archive *archive)
{
  while (true)
  {
    char escolha = -1;

    puts("1. Search by age interval");
    puts("2. Search by name");
    puts("0. Go back");

    scanf(" %c%*c", &escolha);
    getchar();

    switch (escolha)
    {
    case '1':
      // Ask the data to the user brother, not 0 0
      // search_age_interval(0, 0, file_stream);
      break;
    case '2':
      search_name(archive);
      break;
    case '0':
      break;
    default:
      puts("input invalido");
    }
  }
}

// MENU 5
// void search_age_interval(const int from, const int to, FILE *file_stream)
// {
//   puts("listar registo!");
// }

int main()
{
  Inic();
  data_Load("Failed to load");

  char escolha = -1;

  while (true)
  {
    show_leaderboard("Welcome!");
    printf("\nTheres %ld registers in the list\n"
           "\n1. Insert Register\n"
           "2. Change Register\n"
           "3. Delete Register\n"
           "4. Full Reg. list\n"
           "5. Search\n"
           "0. Exit\n",
           list.counter);

    scanf(" %c%*c", &escolha);

    switch (escolha)
    {
    case '1':
      register_insert();
      break;
    case '2':
      register_change("Failed trying to change data!");
      break;
    case '3':
      register_delete("Failed trying to delete data!");
      break;
    case '4':
      show_full_list();
      break;
    case '5':
      // void search_register(FILE *list)
      break;
    case '0':
      data_Save("DATA SAVE FAILED");
      return 0;
    default:
      puts("Invalid input");
    }
  }
}
