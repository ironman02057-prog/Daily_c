#include <stdio.h>

int main(void)
{
    char choice;
    float basic, da, ta, hra, total;

    printf("Enter Role (m=Manager, s=Supervisor, o=Attendant): ");
    scanf(" %c", &choice);

    switch (choice)
    {
        case 'm':
        case 'M':
            basic = 40000;
            da = basic * 0.03f;
            ta = basic * 0.02f;
            hra = basic * 0.0005f;
            break;

        case 's':
        case 'S':
            basic = 30000;
            da = basic * 0.025f;
            ta = basic * 0.017f;
            hra = basic * 0.0027f;
            break;

        case 'o':
        case 'O':
            basic = 15000;
            da = basic * 0.01f;
            ta = basic * 0.009f;
            hra = basic * 0.001f;
            break;

        default:
            printf("Invalid choice\n");
            return 1;
    }

    total = basic + da + ta - hra;

    printf("\nBasic: %.2f\nDA: %.2f\nTA: %.2f\nHRA: %.2f\nTotal Salary: %.2f\n", basic, da, ta, hra, total);

    return 0;
}