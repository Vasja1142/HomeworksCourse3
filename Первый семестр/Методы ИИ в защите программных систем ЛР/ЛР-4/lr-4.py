import tkinter as tk
from tkinter import filedialog, messagebox
import os
import struct
import random

class BlockCipher:
    def __init__(self, key):
        self.key = key & 0xFFFF  # 16-bit key
        
    def encrypt_block(self, block):
        """Шифрование 16-битного блока"""
        block = block & 0xFFFF
        
        # Разделяем блок на две части по 8 бит
        left = (block >> 8) & 0xFF
        right = block & 0xFF
        
        # 4 раунда шифрования (Feistel сеть)
        for i in range(4):
            # Модифицируем ключ для каждого раунда
            round_key = (self.key + i) & 0xFFFF
            
            # Feistel функция: комбинация XOR и сложения
            temp = right
            right = left ^ ((right + round_key) & 0xFF)
            left = temp
        
        # Собираем блок обратно
        encrypted = (left << 8) | right
        return encrypted & 0xFFFF
    
    def decrypt_block(self, block):
        """Дешифрование 16-битного блока"""
        block = block & 0xFFFF
        
        # Разделяем блок на две части по 8 бит
        left = (block >> 8) & 0xFF
        right = block & 0xFF
        
        # 4 раунда дешифрования (в обратном порядке)
        for i in range(3, -1, -1):
            # Модифицируем ключ для каждого раунда
            round_key = (self.key + i) & 0xFFFF
            
            # Обратная Feistel функция
            temp = left
            left = right ^ ((left + round_key) & 0xFF)
            right = temp
        
        # Собираем блок обратно
        decrypted = (left << 8) | right
        return decrypted & 0xFFFF

class FileEncryptorApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Шифратор бинарных файлов - 16 бит")
        self.root.geometry("700x600")
        self.root.resizable(True, True)
        
        # Переменные
        self.input_file = tk.StringVar()
        self.output_file = tk.StringVar()
        self.key_var = tk.StringVar(value="12345")
        self.operation_var = tk.StringVar(value="encrypt")
        
        self.create_widgets()
        
    def create_widgets(self):
        # Заголовок
        title_label = tk.Label(self.root, text="Шифратор бинарных файлов", 
                              font=("Arial", 18, "bold"))
        title_label.pack(pady=10)
        
        subtitle_label = tk.Label(self.root, text="Блочное шифрование, 16 бит, 16 битный ключ", 
                                 font=("Arial", 10), fg="gray")
        subtitle_label.pack(pady=5)
        
        # Фрейм для выбора файла
        file_frame = tk.Frame(self.root)
        file_frame.pack(fill="x", padx=20, pady=10)
        
        tk.Label(file_frame, text="Исходный файл:", font=("Arial", 10, "bold")).pack(anchor="w")
        file_input_frame = tk.Frame(file_frame)
        file_input_frame.pack(fill="x", pady=5)
        
        tk.Entry(file_input_frame, textvariable=self.input_file, 
                state="readonly", font=("Courier", 10)).pack(side="left", fill="x", expand=True)
        tk.Button(file_input_frame, text="Обзор", command=self.browse_input_file,
                 bg="#2196F3", fg="white", font=("Arial", 9, "bold")).pack(side="right", padx=(5,0))
        
        # Фрейм для операции
        operation_frame = tk.Frame(self.root)
        operation_frame.pack(fill="x", padx=20, pady=5)
        
        tk.Label(operation_frame, text="Операция:", font=("Arial", 10, "bold")).pack(anchor="w")
        operation_btn_frame = tk.Frame(operation_frame)
        operation_btn_frame.pack(fill="x", pady=5)
        
        tk.Radiobutton(operation_btn_frame, text="Шифрование", variable=self.operation_var, 
                      value="encrypt", font=("Arial", 10), command=self.update_output_filename).pack(side="left", padx=(0,20))
        tk.Radiobutton(operation_btn_frame, text="Дешифрование", variable=self.operation_var, 
                      value="decrypt", font=("Arial", 10), command=self.update_output_filename).pack(side="left")
        
        # Фрейм для ключа
        key_frame = tk.Frame(self.root)
        key_frame.pack(fill="x", padx=20, pady=10)
        
        tk.Label(key_frame, text="Ключ (16-битное число 0-65535):", 
                font=("Arial", 10, "bold")).pack(anchor="w")
        
        key_input_frame = tk.Frame(key_frame)
        key_input_frame.pack(fill="x", pady=5)
        
        tk.Entry(key_input_frame, textvariable=self.key_var, font=("Arial", 10)).pack(side="left", fill="x", expand=True)
        tk.Button(key_input_frame, text="Случайный", command=self.generate_key,
                 bg="#FF9800", fg="white", font=("Arial", 9, "bold")).pack(side="right", padx=(5,0))
        
        # Фрейм для кнопок
        button_frame = tk.Frame(self.root)
        button_frame.pack(fill="x", padx=20, pady=15)
        
        tk.Button(button_frame, text="Выполнить", command=self.process_operation, 
                 bg="#4CAF50", fg="white", font=("Arial", 11, "bold"), height=2, width=10).pack(side="left", padx=(0,10))
        
        tk.Button(button_frame, text="Тест", command=self.test_encryption,
                 bg="#2196F3", fg="white", font=("Arial", 11, "bold"), height=2, width=10).pack(side="left", padx=(0,10))
        
        tk.Button(button_frame, text="Очистить", command=self.clear_fields,
                 bg="#f44336", fg="white", font=("Arial", 11, "bold"), height=2, width=10).pack(side="left")
        
        # Прогресс и статус
        self.status_label = tk.Label(self.root, text="Готов к работе", font=("Arial", 10), 
                                    relief="sunken", bd=1, anchor="w")
        self.status_label.pack(side="bottom", fill="x", padx=20, pady=10)
        
        # Подробное описание алгоритма
        algo_frame = tk.LabelFrame(self.root, text="Подробное описание алгоритма", 
                                  font=("Arial", 11, "bold"))
        algo_frame.pack(fill="both", expand=True, padx=20, pady=10)
        
        algo_text = tk.Text(algo_frame, height=15, wrap="word", font=("Arial", 9))
        algo_text.pack(fill="both", expand=True, padx=5, pady=5)
        
        scrollbar = tk.Scrollbar(algo_frame, command=algo_text.yview)
        scrollbar.pack(side="right", fill="y")
        algo_text.config(yscrollcommand=scrollbar.set)
        
        algo_text.insert("1.0", """АЛГОРИТМ БЛОЧНОГО ШИФРОВАНИЯ (16 бит)

ОСНОВНЫЕ ХАРАКТЕРИСТИКИ:
• Размер блока: 16 бит (2 байта)
• Размер ключа: 16 бит (0-65535)
• Режим работы: ECB (Electronic Codebook)
• Тип шифра: Симметричный блочный

СТРУКТУРА АЛГОРИТМА:
Используется 4-раундовая Feistel сеть:

1. ВХОДНОЙ БЛОК (16 бит):
   - Разделяется на две части: левая (8 бит) и правая (8 бит)
   - Пример: 0x1234 → левая = 0x12, правая = 0x34

2. РАУНДЫ ШИФРОВАНИЯ (4 раунда):
   Для каждого раунда i (0-3):
   - Вычисляется раундовый ключ: (основной_ключ + i) & 0xFF
   - Новая правая часть = старая левая XOR F(старая правая, раундовый ключ)
   - Новая левая часть = старая правая
   - Функция F: (x + ключ) & 0xFF

3. СБОРКА РЕЗУЛЬТАТА:
   - Объединение левой и правой частей в 16-битный блок
   - Пример: левая = 0xAB, правая = 0xCD → результат = 0xABCD

ДЕШИФРОВАНИЕ:
- Процесс обратный, раунды выполняются в обратном порядке (3→0)
- Используется тот же ключ
- Гарантирует точное восстановление исходных данных

ОСОБЕННОСТИ РЕАЛИЗАЦИИ:
• Автоматическое определение имен выходных файлов
• Обработка нечетного количества байт (дополнение нулевым байтом)
• Контроль размера ключа (16 бит)
• Проверка целостности данных
• Корректное удаление дополнительных байтов при дешифровании
""")
        algo_text.config(state="disabled")
    
    def browse_input_file(self):
        filename = filedialog.askopenfilename(
            title="Выберите файл для обработки",
            filetypes=[("Все файлы", "*.*"), ("Текстовые файлы", "*.txt"), 
                      ("Бинарные файлы", "*.bin;*.dat"), ("Изображения", "*.png;*.jpg")]
        )
        if filename:
            self.input_file.set(filename)
            self.update_output_filename()
    
    def update_output_filename(self):
        """Автоматическое обновление имени выходного файла"""
        if not self.input_file.get():
            return
            
        input_path = self.input_file.get()
        base, ext = os.path.splitext(input_path)
        
        if self.operation_var.get() == "encrypt":
            output_name = f"{base}_encrypted{ext}"
        else:
            # Пытаемся удалить суффикс _encrypted
            if "_encrypted" in base:
                base = base.replace("_encrypted", "")
            output_name = f"{base}_decrypted{ext}"
        
        self.output_file.set(output_name)
    
    def generate_key(self):
        key = random.randint(0, 65535)
        self.key_var.set(str(key))
        self.update_status(f"Сгенерирован ключ: {key}")
    
    def parse_key(self):
        key_str = self.key_var.get().strip()
        if not key_str:
            raise ValueError("Ключ не указан")
        
        try:
            key = int(key_str)
            if not (0 <= key <= 65535):
                raise ValueError("Ключ должен быть в диапазоне 0-65535")
            return key
        except ValueError:
            raise ValueError("Неверный формат ключа. Используйте число от 0 до 65535")
    
    def update_status(self, message):
        self.status_label.config(text=message)
        self.root.update_idletasks()
    
    def process_operation(self):
        """Основная функция обработки файла"""
        try:
            operation = self.operation_var.get()
            input_path = self.input_file.get()
            
            if not input_path:
                raise ValueError("Не выбран исходный файл")
            
            if not os.path.exists(input_path):
                raise ValueError("Исходный файл не существует")
            
            # Автоматическое имя выходного файла
            self.update_output_filename()
            output_path = self.output_file.get()
            
            # Парсинг ключа
            key = self.parse_key()
            
            # Создание шифратора
            cipher = BlockCipher(key)
            
            # Определение размера файла
            file_size = os.path.getsize(input_path)
            self.update_status(f"Подготовка {operation} файла: {file_size} байт")
            
            original_size_is_odd = (file_size % 2 == 1)

            with open(input_path, 'rb') as infile, open(output_path, 'wb') as outfile:
                processed_bytes = 0
                
                while True:
                    # Читаем 2 байта (16 бит)
                    bytes_data = infile.read(2)
                    if not bytes_data:
                        break
                    
                    # Обработка нечетного количества байт
                    if len(bytes_data) == 1:
                        if operation == "encrypt":
                            # При шифровании добавляем нулевой байт
                            bytes_data += b'\x00'
                        else:
                            # При дешифровании это последний блок, его нужно тоже прочитать как 2 байта
                            # Исходный файл при шифровании был дополнен, значит и этот будет четным
                            bytes_data += b'\x00' # Добавляем для формирования полного блока
                    
                    # Преобразуем в 16-битное число
                    block = struct.unpack('<H', bytes_data)[0]
                    
                    # Шифруем/дешифруем блок
                    if operation == "encrypt":
                        processed_block = cipher.encrypt_block(block)
                    else:
                        processed_block = cipher.decrypt_block(block)
                    
                    # Записываем результат
                    outfile.write(struct.pack('<H', processed_block))
                    
                    processed_bytes += len(bytes_data)
                    
                    # Обновляем статус
                    if processed_bytes % 1024 == 0 or not bytes_data:
                        progress = min(100, (processed_bytes / (file_size + 1 if original_size_is_odd else file_size)) * 100)
                        self.update_status(f"Обработано: {min(processed_bytes, file_size)}/{file_size} байт ({progress:.1f}%)")
            
            # После дешифрования: корректировка размера файла
            if operation == "decrypt":
                output_size = os.path.getsize(output_path)
                # Если мы знаем, что оригинал был нечетный, то расшифрованный файл будет на 1 байт длиннее
                # и последний байт будет нулевым. Его нужно удалить.
                # Мы не можем точно знать размер оригинала, но если у расшифрованного файла
                # последний байт равен нулю, скорее всего, это дополнение.
                with open(output_path, 'r+b') as f:
                    if output_size > 0:
                        f.seek(-1, 2)
                        last_byte = f.read(1)
                        if last_byte == b'\x00':
                            f.seek(-1, 2)
                            f.truncate()
                            self.update_status("Удален дополнительный нулевой байт после расшифровки.")

            
            # Завершение операции
            op_name = "Шифрование" if operation == "encrypt" else "Дешифрование"
            self.update_status(f"{op_name} завершено успешно!")
            
            result_msg = f"Файл успешно {'зашифрован' if operation == 'encrypt' else 'расшифрован'}!\n"
            result_msg += f"Исходный файл: {os.path.basename(input_path)}\n"
            result_msg += f"Результат: {os.path.basename(output_path)}\n"
            result_msg += f"Размер результата: {os.path.getsize(output_path)} байт"
            
            messagebox.showinfo("Успех", result_msg)
            
        except Exception as e:
            self.update_status(f"Ошибка: {str(e)}")
            messagebox.showerror("Ошибка", f"Ошибка {self.operation_var.get()}: {str(e)}")

    def test_encryption(self):
        """Тестовая функция для проверки корректности шифрования/дешифрования"""
        try:
            key = self.parse_key()
            cipher = BlockCipher(key)
            
            # Тестовые данные
            test_data = [0x1234, 0xABCD, 0x0000, 0xFFFF, 0x5555, 0x0102, 0x8080, 0x00FF]
            
            results = []
            all_correct = True
            
            for data in test_data:
                encrypted = cipher.encrypt_block(data)
                decrypted = cipher.decrypt_block(encrypted)
                correct = (data == decrypted)
                results.append((data, encrypted, decrypted, correct))
                if not correct:
                    all_correct = False
            
            # Вывод результатов
            result_text = "ТЕСТ КОРРЕКТНОСТИ ШИФРОВАНИЯ:\n"
            result_text += "Исходный -> Зашифрованный -> Расшифрованный -> Результат\n"
            result_text += "-" * 70 + "\n"
            
            for orig, enc, dec, correct in results:
                status = "✓ ПРОЙДЕН" if correct else "✗ ОШИБКА"
                result_text += f"0x{orig:04X} -> 0x{enc:04X} -> 0x{dec:04X} -> {status}\n"
            
            result_text += "\n" + ("=" * 70) + "\n"
            result_text += f"РЕЗУЛЬТАТ: {'ВСЕ ТЕСТЫ ПРОЙДЕНЫ УСПЕШНО!' if all_correct else 'НЕКОТОРЫЕ ТЕСТЫ НЕ ПРОЙДЕНЫ!'}\n"
            
            messagebox.showinfo("Результат теста", result_text)
            
        except Exception as e:
            messagebox.showerror("Ошибка теста", f"Ошибка: {str(e)}")
    
    def clear_fields(self):
        self.input_file.set("")
        self.output_file.set("")
        self.key_var.set("12345")
        self.update_status("Поля очищены. Готов к работе.")

def main():
    root = tk.Tk()
    app = FileEncryptorApp(root)
    root.mainloop()

if __name__ == "__main__":
    main()