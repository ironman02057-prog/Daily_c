#include <stdio.h>

int main(void)
{
    int year;

    printf("Enter year: ");
    scanf("%d", &year);

    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        printf("Leap Year\n");
    else
        printf("Not Leap Year\n");

    return 0;
}
