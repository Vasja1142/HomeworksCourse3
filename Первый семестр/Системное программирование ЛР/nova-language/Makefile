# Makefile для компилятора языка Nova

# Имя итогового файла компилятора
TARGET = nova_compiler

# Исходные файлы
BISON_SRC = nova.y
FLEX_SRC = nova.l

# Генерируемые файлы
C_SRC = nova.tab.c lex.yy.c
HEADERS = nova.tab.h

# Флаги компилятора C (можно добавить -Wall для отображения всех предупреждений)
CC = gcc
CFLAGS = 

# Правило по умолчанию (выполняется при вызове make)
all: $(TARGET)

# Сборка итогового компилятора из C-файлов
$(TARGET): $(C_SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(C_SRC)

# Генерация C-кода парсера из Bison
nova.tab.c nova.tab.h: $(BISON_SRC)
	bison -d $(BISON_SRC)

# Генерация C-кода лексера из Flex
lex.yy.c: $(FLEX_SRC) nova.tab.h
	flex $(FLEX_SRC)

# Очистка проекта (удаление всех созданных файлов)
clean:
	rm -f $(TARGET) $(C_SRC) $(HEADERS) output.c app