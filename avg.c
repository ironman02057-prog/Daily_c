#include <stdio.h>
int main()
{
  float a, b, c;
  printf("Enter three numbers: ");
  scanf("%f %f %f", &a, &b, &c);
  printf("Average: %f\n", (a + b + c) / 3.0);
  return 0;
}
