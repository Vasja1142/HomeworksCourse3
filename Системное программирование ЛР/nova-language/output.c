#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define print_any(x) _Generic((x), \
    int: printf("%d\n", x), \
    double: printf("%.2f\n", x), \
    char*: printf("%s\n", x) \
)

int get_int() {
    char buf[100];
    printf("> ");
    fflush(stdout);
    if (!fgets(buf, 100, stdin)) exit(1);
    char *end;
    long val = strtol(buf, &end, 10);
    if (end == buf || (*end != '\n' && *end != 0)) { printf("Ошибка: Ожидалось целое число!\n"); exit(1); }
    return (int)val;
}

double get_float() {
    char buf[100];
    printf("> ");
    fflush(stdout);
    if (!fgets(buf, 100, stdin)) exit(1);
    char *end;
    double val = strtod(buf, &end);
    if (end == buf || (*end != '\n' && *end != 0)) { printf("Ошибка: Ожидалось дробное число!\n"); exit(1); }
    return val;
}

char* get_str() {
    char buf[256];
    printf("> ");
    fflush(stdout);
    if (!fgets(buf, 256, stdin)) exit(1);
    buf[strcspn(buf, "\n")] = 0;
    return strdup(buf);
}

void get_list(int *arr, int max_size) {
    char buf[1024];
    printf("> ");
    fflush(stdout);
    if (!fgets(buf, 1024, stdin)) exit(1);
    buf[strcspn(buf, "\n")] = 0;
    char *token = strtok(buf, " ");
    int i = 0;
    while (token != NULL && i < max_size) {
        arr[i++] = atoi(token);
        token = strtok(NULL, " ");
    }
}

int main() {
	printf("%s\n", "--- ТЕСТ ЯЗЫКА NOVA ---");
	printf("%s\n", "1. Тест строк. Введите имя:");
	char *name = get_str();
	printf("%s\n", "Привет, ");
	print_any(name);
	printf("%s\n", "2. Тест дробных чисел (FLOAT). Введите радиус круга:");
	double r = get_float();
	double pi = 3.14;
	double area = r * r * pi;
	printf("%s\n", "Площадь круга:");
	print_any(area);
	printf("%s\n", "3. Тест условий (IF/ELSE). Введите число:");
	int x = get_int();
	if (x > 10) {
	printf("%s\n", "Число больше 10");
	} else {
	printf("%s\n", "Число меньше или равно 10");
	}
	printf("%s\n", "4. Тест простого цикла (LOOP). Повторим 3 раза:");
	for(int _i=0; _i < (int)(3); _i++) {
	printf("%s\n", "Это цикл loop");
	}
	printf("%s\n", "5. Тест цикла с условием (WHILE). Обратный отсчет от:");
	int count = get_int();
	while (count > 0) {
	print_any(count);
	count = count - 1;
	}
	printf("%s\n", "6. Тест массивов (LIST). Введите не менее 2 чисел через пробел:");
	int arr[100] = {0};
	get_list(arr, 100);
	printf("%s\n", "Второй элемент:");
	int val = arr[1];
	print_any(val);

	return 0;
}
