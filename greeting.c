#include <stdio.h>
int main()
{
  char name[50]; // A place to store text
  printf("What is your name? ");
  scanf("%s", name); // No & needed for text arrays!
  printf("Hello %s! Welcome to C programming.\n", name);
  return 0;
}
