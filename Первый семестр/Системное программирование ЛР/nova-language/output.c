#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
void print_int(int x) { printf("%d\n", x); }
void print_double(double x) { printf("%.2f\n", x); }
void print_string(char* x) { printf("%s\n", x); }
#define print_any(x) _Generic((x), int: print_int, double: print_double, char*: print_string)(x)
void fill_fibonacci_range(int *arr, int start_idx, int end_idx) {
    int f[1000]; f[0] = 0; f[1] = 1;
    for(int i=2; i<=end_idx; i++) f[i] = f[i-1] + f[i-2];
    int arr_i = 0;
    for(int i=start_idx; i<=end_idx; i++) arr[arr_i++] = f[i];
}
void file_write(char* filename, char* text) {
    FILE *f = fopen(filename, "w");
    if (f) { fprintf(f, "%s\n", text); fclose(f); printf("[LOG] File created: %s\n", filename); }
    else { printf("[ERROR] Write failed: %s\n", filename); }
}
void file_append(char* filename, char* text) {
    FILE *f = fopen(filename, "a");
    if (f) { fprintf(f, "%s\n", text); fclose(f); printf("[LOG] Data appended: %s\n", filename); }
    else { printf("[ERROR] Append failed: %s\n", filename); }
}
int random_int(int min, int max) { return min + rand() % (max - min + 1); }
int get_int() { char buf[100]; printf("> "); fflush(stdout); if (!fgets(buf, 100, stdin)) exit(0); return atoi(buf); }
double get_float() { char buf[100]; printf("> "); fflush(stdout); if (!fgets(buf, 100, stdin)) exit(0); return strtod(buf, NULL); }
char* get_str() { char buf[256]; printf("> "); fflush(stdout); if (!fgets(buf, 256, stdin)) exit(0); buf[strcspn(buf, "\n")] = 0; return strdup(buf); }
void get_list(int *arr, int max_size) {
    char buf[1024]; printf("> "); fflush(stdout);
    if (!fgets(buf, 1024, stdin)) exit(1); buf[strcspn(buf, "\n")] = 0;
    char *token = strtok(buf, " "); int i = 0;
    while (token != NULL && i < max_size) { arr[i++] = atoi(token); token = strtok(NULL, " "); }
}

int calc_metric(int val, int coef) {
	int res = val * coef;
	return res;
}

int main() {
	srand(time(NULL));
	print_any("==============================================");
	print_any(" SYSTEM: AUTOMATED DATA ANALYSIS (DEBUG MODE) ");
	print_any("==============================================");
	print_any("[INPUT] Введите ID оператора (String):");
	char *operator_id = get_str();
	print_any("[INIT] Генерация модели (Тип List)...");
	print_any("       Вызов встроенной функции fibonacci(1, 8)");
	int load_factors[100];
	fill_fibonacci_range(load_factors, 1, 8);
	print_any("[INPUT] Введите порог тревоги (Int), например 100:");
	int threshold = get_int();
	file_write("system_log.txt", "--- START OF LOG ---");
	print_any("[SYSTEM] Запуск цикла обработки (WHILE i < 5)...");
	int steps = 5;
	int i = 0;
	while (i < steps) {
	print_any("----------------------------------------------");
	print_any("[LOOP] Итерация №:");
	print_any(i);
	int sensor_val = random_int(10, 30);
	print_any("[DATA] 1. Значение датчика:");
	print_any(sensor_val);
	int current_factor = load_factors[i];
	print_any("[DATA] 2. Коэффициент:");
	print_any(current_factor);
	int metric = calc_metric(sensor_val, current_factor);
	print_any("[CALC] 3. Метрика:");
	print_any(metric);
	print_any("[LOGIC] 4. Проверка условия...");
	if (metric > threshold) {
	print_any("        -> STATUS: CRITICAL");
	file_append("system_log.txt", "ALERT: Threshold exceeded");
	} else {
	print_any("        -> STATUS: NORMAL");
	file_append("system_log.txt", "INFO: System stable");
	}
	i = i + 1;
	}
	print_any("----------------------------------------------");
	print_any("[MATH] Расчет эффективности (Float):");
	double base_efficiency = 100.0;
	double degradation = 0.55;
	double final_eff = base_efficiency * degradation;
	print_any(final_eff);
	print_any("==============================================");
	print_any("   ПРОГРАММА ЗАВЕРШЕНА.                       ");
	print_any("==============================================");

	return 0;
}
