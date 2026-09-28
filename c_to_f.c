#include <stdio.h>
int main()
{
  float c, f;
  printf("Enter Celsius: ");
  scanf("%f", &c);
  f = (c * 9.0 / 5.0) + 32; // using 9.0 forces float math
  printf("Fahrenheit: %f\n", f);
  return 0;
}