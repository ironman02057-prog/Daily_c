#include <stdio.h>
int main()
{
  char letter;
  printf("Enter a letter: ");
  scanf(" %c", &letter);
  printf("The next letter is: %c\n", letter + 1);
  return 0;
}