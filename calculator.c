#include <stdio.h>

int main()
{
  float number1, number2;
  char operator;

  printf("Enter an operator (+, -, *, /): ");
  scanf(" %c", &operator);

  printf("Enter two numbers: ");
  scanf("%f %f", &number1, &number2);

  switch (operator)
  {
  case '+':
    printf("Result = %.2f\n", number1 + number2);
    break;
  case '-':
    printf("Result = %.2f\n", number1 - number2);
    break;
  case '*':
    printf("Result = %.2f\n", number1 * number2);
    break;
  case '/':
    if (number2 == 0)
      printf("Cannot divide by zero.\n");
    else
      printf("Result = %.2f\n", number1 / number2);
    break;
  default:
    printf("Invalid operator.\n");
  }

  return 0;
}
