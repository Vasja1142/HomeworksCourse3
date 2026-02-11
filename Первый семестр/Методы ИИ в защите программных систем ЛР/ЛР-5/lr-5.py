import tkinter as tk
from tkinter import messagebox, filedialog
import random

def encode_hamming(data_bits):
    """Кодирует биты по методу Хэмминга (3,1): 0->000, 1->111"""
    encoded = ""
    for bit in data_bits:
        if bit == '0':
            encoded += '000'
        elif bit == '1':
            encoded += '111'
        else:
            # Проверка на биты проводится до вызова этой функции
            pass
    return encoded

def decode_hamming(encoded_bits):
    """Декодирует 3 бита обратно в 1, исправляя ошибки голосованием"""
    if len(encoded_bits) % 3 != 0:
        raise ValueError("Длина зашифрованной строки должна быть кратна 3.")
    decoded = ""
    for i in range(0, len(encoded_bits), 3):
        triplet = encoded_bits[i:i+3]
        if len(triplet) < 3:
            raise ValueError("Найден неполный триплет в конце строки.")
        ones = triplet.count('1')
        zeros = triplet.count('0')
        if ones > zeros:
            decoded += '1'
        else:
            decoded += '0'
    return decoded

def text_to_binary(text):
    """Преобразует текст в бинарную строку (UTF-8 -> байты -> бинарные биты)"""
    # Кодируем текст в байты с помощью UTF-8
    byte_data = text.encode('utf-8')
    # Преобразуем каждый байт в бинарное представление (8 бит) и объединяем
    binary_string = ''.join(format(byte, '08b') for byte in byte_data)
    return binary_string

def binary_to_text(binary_string):
    """Преобразует бинарную строку обратно в текст"""
    try:
        if len(binary_string) % 8 != 0:
            raise ValueError("Длина бинарной строки должна быть кратна 8.")

        text_bytes = bytearray()
        for i in range(0, len(binary_string), 8):
            byte_str = binary_string[i:i+8]
            byte_val = int(byte_str, 2)
            text_bytes.append(byte_val)

        # Декодируем с заменой ошибок
        return text_bytes.decode('utf-8', errors='replace')

    except Exception as e:
        # На случай любой непредвиденной ошибки — возвращаем пустую строку
        print(f"Ошибка при декодировании бинарных данных: {e}")
        return ""  # Всегда возвращаем строку

def add_noise(binary_string, error_rate=0.01):
    """Добавляет шум в бинарную строку."""
    noisy_string = list(binary_string)
    num_bits = len(noisy_string)
    num_errors = int(num_bits * error_rate)
    error_indices = random.sample(range(num_bits), num_errors)
    for idx in error_indices:
        noisy_string[idx] = '1' if noisy_string[idx] == '0' else '0'
    return ''.join(noisy_string)

def on_encode_file():
    """Кнопка: Выбрать файл -> Закодировать -> Сохранить"""
    input_path = filedialog.askopenfilename(title="Выберите текстовый файл для кодирования")
    if not input_path:
        return

    try:
        # 1. Прочитать текст из файла
        with open(input_path, 'r', encoding='utf-8') as f:
            text_data = f.read()

        # 2. Преобразовать в бинарный формат
        binary_data = text_to_binary(text_data)

        # 3. Закодировать Хэммингом
        encoded_data = encode_hamming(binary_data)

        # 4. Добавить шум
        noisy_encoded_data = add_noise(encoded_data)

        # 5. Сформировать имя для зашифрованного файла
        output_path = input_path.rsplit('.', 1)[0] + '_encoded.ham'

        # 6. Сохранить зашифрованные (с шумом) бинарные данные
        with open(output_path, 'w', encoding='ascii') as f:
            f.write(noisy_encoded_data)

        messagebox.showinfo("Успех", f"Файл закодирован и сохранён как:\n{output_path}")

    except Exception as e:
        messagebox.showerror("Ошибка кодирования", f"{str(e)}")

def on_decode_file():
    """Кнопка: Выбрать файл (.ham) -> Декодировать -> Сохранить"""
    input_path = filedialog.askopenfilename(
        title="Выберите файл для декодирования",
        filetypes=[("Hamming files", "*.ham"), ("All files", "*.*")]
    )
    if not input_path:
        return

    try:
        # 1. Прочитать зашифрованные (с шумом) бинарные данные из файла
        with open(input_path, 'r', encoding='ascii') as f:
            noisy_encoded_data = f.read().strip()

        # 2. Проверить формат
        if not all(c in '01' for c in noisy_encoded_data):
             raise ValueError("Файл должен содержать только 0 и 1.")
        if len(noisy_encoded_data) % 3 != 0:
             raise ValueError("Длина данных должна быть кратна 3.")

        # 3. Декодировать Хэммингом (исправление ошибок)
        decoded_binary = decode_hamming(noisy_encoded_data)

        # 4. Преобразовать в текст
        decoded_text = binary_to_text(decoded_binary)

        # 5. Сформировать имя для декодированного файла
        output_path = input_path.rsplit('.', 1)[0] + '_decoded.txt'

        # 6. Сохранить восстановленный текст
        with open(output_path, 'w', encoding='utf-8') as f:
            f.write(decoded_text)

        messagebox.showinfo("Успех", f"Файл декодирован и сохранён как:\n{output_path}")

    except ValueError as e:
        messagebox.showerror("Ошибка декодирования", f"{str(e)}")
    except Exception as e:
        messagebox.showerror("Ошибка декодирования", f"{str(e)}")

# --- Создание окна ---
root = tk.Tk()
root.title("Хэмминг (3,1) - Файлы")

tk.Label(root, text="Выберите файл и нажмите кнопку:").pack(pady=10)

btn_frame = tk.Frame(root)
btn_frame.pack(pady=5)

btn_encode = tk.Button(btn_frame, text="Кодировать Файл", command=on_encode_file)
btn_encode.pack(side=tk.LEFT, padx=5)

btn_decode = tk.Button(btn_frame, text="Декодировать Файл", command=on_decode_file)
btn_decode.pack(side=tk.LEFT, padx=5)

root.mainloop()