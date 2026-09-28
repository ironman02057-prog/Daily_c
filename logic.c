#include <stdio.h>
int main()
{
  int age = 20, hasID = 1;
  printf("Can vote: %d\n", age >= 18 && hasID == 1); // 1
  return 0;
}
