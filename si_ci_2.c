#include <stdio.h>

int main()
{
  double p, r, t, n, a, ci;

  printf("Enter P, R%%, T, N: ");
  scanf("%lf %lf %lf %lf", &p, &r, &t, &n);

  r = r / 100.0;
  a = p * pow(1 + (r / n), n * t);
  ci = a - p;

  printf("\nAmount = %.2f\n", a);
  printf("Compound Interest = %.2f\n", ci);

  return 0;
}
