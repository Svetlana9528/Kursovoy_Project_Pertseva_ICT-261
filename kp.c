// Курсовой проект: Система автоматизированного мониторинга химического реактора. Вариант №28

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <stdbool.h>

#define X_BREAK_1 65.0f
#define X_BREAK_2 90.0f
#define Q_NOMINAL 50.0f
#define Q_MAX_DEV 10.0f
#define TOTAL_MEASUREMENTS 40

#define STATE_NORMAL 0
#define STATE_ALARM 1

void print_welcome(void);
void run_verification_tests(void);
bool read_x(int index, float* x);
float calc_q(float x);
int check_state(float q);
void print_state(int state, float q);

int main(void)
{
    int i = 0;
    float x = 0.0f, q = 0.0f;

    setlocale(LC_ALL, ".UTF8");

    run_verification_tests();
    print_welcome();

    for (i = 1; i <= TOTAL_MEASUREMENTS; i++)
    {
        if (!read_x(i, &x)) {
            printf("   [Ошибка ввода]: Недопустимые символы. Повторите ввод для измерения %d.\n", i);
            i--;
            continue;
        }

        q = calc_q(x);
        print_state(check_state(q), q);
    }

    return 0;
}

void print_welcome(void) {
    puts("======================================================================");
    puts(" СИСТЕМА АВТОМАТИЗИРОВАННОГО МОНИТОРИНГА ХИМИЧЕСКОГО РЕАКТОРА ");
    puts(" Назначение: Оперативный контроль стабильности процесса по показателю Q");
    puts("======================================================================\n");
}

void run_verification_tests(void) {
    float test_x = 77.5f;
    float expected_q = 50.0f;
    float actual_q = calc_q(test_x);

    if (fabsf(actual_q - expected_q) < 0.0001f) {
        printf("[Автотест верификации]: УСПЕШНО (X = %.1f -> Q = %.1f)\n\n", test_x, actual_q);
    }
    else {
        printf("[Автотест ОШИБКА]: Сбой верификации.\n\n");
    }
}

bool read_x(int index, float* x) {
    printf("Измерение [%d/%d] -> Введите x: ", index, TOTAL_MEASUREMENTS);
    if (scanf("%f", x) != 1) {
        while (getchar() != '\n');
        return false;
    }
    return true;
}

float calc_q(float x) {
    if (x < X_BREAK_1) {
        return 6.0f * sqrtf(fabsf(x - 64.0f)) + 5.0f;
    }
    else if (x <= X_BREAK_2) {
        return 2.0f * (x - 77.5f) + 50.0f;
    }
    else {
        return 0.25f * powf(x - 90.0f, 2) + 55.0f;
    }
}

int check_state(float q) {
    if (fabsf(q - Q_NOMINAL) > Q_MAX_DEV) return STATE_ALARM;
    return STATE_NORMAL;
}

void print_state(int state, float q) {
    printf("   Результат вычисления: Q = %.2f\n", q);
    if (state == STATE_ALARM) {
        puts("   [ТЕКУЩИЙ СТАТУС]: Критическое отклонение!");
    }
    else {
        puts("   [ТЕКУЩИЙ СТАТУС]: Норма.");
    }
}
