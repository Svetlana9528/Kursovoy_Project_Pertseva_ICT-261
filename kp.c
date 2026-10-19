#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <math.h>

int main()
{
    setlocale(LC_ALL, ".UTF8");

    // 5. Контрольный пример
    printf("Контрольный пример: X = 77.50 => Q = %.2f\n\n", 2.0f * (77.5f - 77.5f) + 50.0f);

    float x, q, q_prev, diff;
    float sum_inc = 0, min_inc = 1000.0f, max_inc = 0.0f;

    puts("Введите по очереди измерения активности катализатора:");

    // Запускаем цикл на 40 измерений, как указано в таблице (N = 40)
    for (int i = 1; i <= 40; i++)
    {
        printf("Измерение %d: x = ", i);
        scanf("%f", &x);

        // 1. 
        if (x < 65) {
            q = 6.0f * sqrtf(fabsf(x - 64.0f)) + 5.0f;
        }
        else if (x <= 90) {
            q = 2.0f * (x - 77.5f) + 50.0f;
        }
        else {
            q = 0.25f * powf(x - 90.0f, 2) + 55.0f;
        }

        printf("-> Повышение показания Q = %.2f\n", q);

        // 2. Оперативный контроль (|Q - 50| > 10)
        if (fabsf(q - 50.0f) > 10.0f) {
            puts("   [Статус]: Критическое отклонение!");
        }
        else {
            puts("   [Статус]: Норма.");
        }

        // 3. Статистика приростов строго для первых 15 измерений (Q[1..15])
        if (i > 1 && i <= 15) {
            diff = fabsf(q - q_prev);
            sum_inc += diff;
            if (diff < min_inc) min_inc = diff;
            if (diff > max_inc) max_inc = diff;
        }

        q_prev = q; // запоминаем текущее Q для следующего шага
    }

    // Вывод статистики в самом конце программы
    puts("\n--- Статистика для первых 15 измерений ---");
    printf("Средний прирост: %f\n", sum_inc / 14.0f);
    printf("Минимальный прирост: %f\n", min_inc);
    printf("Максимальный прирост: %f\n", max_inc);

    return 0;
}
