#include <stdio.h>
int main()
{
  int length, breadth;
  printf("Enter length and breadth: ");
  scanf("%d %d", &length, &breadth);
  printf("Area: %d\n", length * breadth);
  return 0;
}