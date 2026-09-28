#include <stdio.h>
int main()
{
  int n;
  printf("Enter number: ");
  scanf("%d", &n);
  if (n % 5 == 0 && n % 11 == 0)
    printf("Divisible\n");
  else
    printf("Not Divisible\n");
  return 0;
}
