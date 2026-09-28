#include <stdio.h>
int main()
{
  float p, r, t, si;
  printf("Enter Principal,Rate,Time: ");
  scanf("%f %f %f", &p, &r, &t);
  si = (p * r * t) / 100;
  printf("simple interest: %f\n", si);
  return 0;
}