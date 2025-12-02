#!/bin/bash

# Остановка скрипта при любой ошибке
set -e

INPUT_FILE="input.txt"
OUTPUT_C="output.c"
COMPILER="./nova_compiler"
APP="./app"

echo "--- [1] Сборка компилятора (через make) ---"
make

echo "--- [2] Трансляция Nova -> C ---"
# Проверяем, существует ли входной файл
if [ ! -f "$INPUT_FILE" ]; then
    echo "Ошибка: Файл $INPUT_FILE не найден!"
    exit 1
fi

# Запускаем твой компилятор
$COMPILER $INPUT_FILE > $OUTPUT_C
echo "Успешно! Создан $OUTPUT_C"

echo "--- [3] Компиляция полученного C-кода ---"
gcc $OUTPUT_C -o $APP
echo "Успешно! Создан исполняемый файл $APP"

echo "--- [4] ЗАПУСК ПРОГРАММЫ ---"
echo "============================"
$APP
echo "============================"