#include <stdio.h>
int main()
{
  int m;
  printf("Enter marks: ");
  scanf("%d", &m);
  if (m >= 90)
    printf("A Grade\n");
  else if (m >= 80)
    printf("B Grade\n");
  else if (m >= 70)
    printf("C Grade\n");
  else
    printf("F Grade\n");
  return 0;
}