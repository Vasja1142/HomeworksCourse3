import tkinter as tk
from tkinter import filedialog, messagebox, scrolledtext
import os
import random
import base64
import hashlib
from cryptography.fernet import Fernet, InvalidToken

# --- Функции для генерации простых чисел ---

def is_prime(n, k=10):
    """
    Тест Миллера-Рабина на простоту числа.
    n: число для проверки
    k: количество раундов для повышения точности
    """
    if n < 2:
        return False
    if n == 2 or n == 3:
        return True
    if n % 2 == 0:
        return False

    d, s = n - 1, 0
    while d % 2 == 0:
        d //= 2
        s += 1

    for _ in range(k):
        a = random.randint(2, n - 2)
        x = pow(a, d, n)
        if x == 1 or x == n - 1:
            continue
        for _ in range(s - 1):
            x = pow(x, 2, n)
            if x == n - 1:
                break
        else:
            return False
    return True

def generate_prime(bits):
    """Генерирует простое число с заданной разрядностью."""
    while True:
        p = random.getrandbits(bits)
        # Убедимся, что число имеет нужную длину и нечетное
        p |= (1 << bits - 1) | 1
        if is_prime(p):
            return p

# --- Основной класс приложения ---

class CryptoApp:
    def __init__(self, master):
        self.master = master
        self.master.title("Шифрование методом Диффи-Хеллмана")
        self.master.geometry("800x700")
        self.filepath = None

        # --- GUI элементы ---
        main_frame = tk.Frame(master, padx=10, pady=10)
        main_frame.pack(fill=tk.BOTH, expand=True)

        # Фрейм для управления файлами
        file_frame = tk.LabelFrame(main_frame, text="Управление файлами", padx=10, pady=10)
        file_frame.pack(fill=tk.X, pady=5)

        self.btn_select = tk.Button(file_frame, text="Выбрать файл", command=self.select_file)
        self.btn_select.pack(side=tk.LEFT, padx=5)

        self.lbl_filepath = tk.Label(file_frame, text="Файл не выбран", bg="white", relief="sunken", width=60)
        self.lbl_filepath.pack(side=tk.LEFT, fill=tk.X, expand=True, padx=5)

        # Фрейм для действий
        actions_frame = tk.LabelFrame(main_frame, text="Действия", padx=10, pady=10)
        actions_frame.pack(fill=tk.X, pady=5)

        self.btn_encrypt = tk.Button(actions_frame, text="Зашифровать", command=self.encrypt_file, state=tk.DISABLED)
        self.btn_encrypt.pack(side=tk.LEFT, padx=5, pady=5)

        self.btn_decrypt = tk.Button(actions_frame, text="Расшифровать", command=self.decrypt_file, state=tk.DISABLED)
        self.btn_decrypt.pack(side=tk.LEFT, padx=5, pady=5)
        
        # Фрейм для объяснения алгоритма
        explanation_frame = tk.LabelFrame(main_frame, text="Пояснение алгоритма Диффи-Хеллмана", padx=10, pady=10)
        explanation_frame.pack(fill=tk.BOTH, expand=True, pady=10)

        self.txt_explanation = scrolledtext.ScrolledText(explanation_frame, wrap=tk.WORD, height=15, font=("Arial", 11))
        self.txt_explanation.pack(fill=tk.BOTH, expand=True)
        self.txt_explanation.insert(tk.END, self.get_explanation_text())
        self.txt_explanation.config(state=tk.DISABLED)

    def get_explanation_text(self):
        return """
Алгоритм обмена ключами Диффи-Хеллмана позволяет двум сторонам (назовем их Алиса и Боб) получить общий секретный ключ, обмениваясь информацией по незащищенному каналу. Этот ключ затем можно использовать для симметричного шифрования данных.

ВАЖНО: Сам по себе алгоритм Диффи-Хеллмана не шифрует данные, а только помогает безопасно выработать общий секрет. В этом приложении полученный секрет используется как ключ для надежного AES шифрования.

Процесс выработки общего ключа:

1. Публичные параметры:
   - Алиса и Боб договариваются о двух числах, которые не являются секретными:
     - p: очень большое простое число (модуль).
     - g: целое число, первообразный корень по модулю p (основание).

2. Генерация секретных ключей:
   - Алиса генерирует свой секретный ключ — случайное простое число 'x'. Она держит его в тайне.
   - Боб генерирует свой секретный ключ — случайное простое число 'y'. Он также держит его в тайне.
   (В этом приложении оба ключа 'x' и 'y' генерируются локально для демонстрации).

3. Вычисление и обмен открытыми ключами:
   - Алиса вычисляет свой открытый ключ 'A' по формуле: A = g^x mod p
   - Боб вычисляет свой открытый ключ 'B' по формуле: B = g^y mod p
   - Алиса и Боб обмениваются своими открытыми ключами (A и B) по сети. Злоумышленник может их перехватить.

4. Вычисление общего секрета:
   - Алиса, получив от Боба ключ B, вычисляет общий секрет 'S' по формуле: S = B^x mod p
   - Боб, получив от Алисы ключ A, вычисляет общий секрет 'S' по формуле: S = A^y mod p

Магия в том, что оба результата будут одинаковыми:
S = (g^y mod p)^x mod p = (g^x mod p)^y mod p = g^(xy) mod p

Теперь у Алисы и Боба есть идентичный секретный ключ 'S', который не передавался по сети в открытом виде. Злоумышленник, зная g, p, A и B, не может легко вычислить 'S', так как для этого ему нужно решить задачу дискретного логарифмирования (найти 'x' из A=g^x mod p), что для больших чисел является очень сложной задачей.

5. Шифрование файла:
   - Полученный общий секрет 'S' преобразуется в ключ фиксированной длины (например, с помощью хэш-функции SHA-256).
   - Этим ключом с помощью симметричного алгоритма (в данном случае AES) шифруется содержимое файла.
        """

    def select_file(self):
        self.filepath = filedialog.askopenfilename(
            title="Выберите текстовый файл",
            filetypes=(("Текстовые файлы", "*.txt"), ("Все файлы", "*.*"))
        )
        if self.filepath:
            self.lbl_filepath.config(text=self.filepath)
            self.btn_encrypt.config(state=tk.NORMAL)
            if self.filepath.endswith(".enc"):
                self.btn_decrypt.config(state=tk.NORMAL)
            else:
                self.btn_decrypt.config(state=tk.DISABLED)
        else:
            self.lbl_filepath.config(text="Файл не выбран")
            self.btn_encrypt.config(state=tk.DISABLED)
            self.btn_decrypt.config(state=tk.DISABLED)
            
    def derive_key(self, shared_secret):
        """Преобразует числовой секрет в ключ для Fernet."""
        # Хэшируем числовой секрет, чтобы получить 32-байтный ключ
        sha256 = hashlib.sha256()
        sha256.update(str(shared_secret).encode('utf-8'))
        # Fernet требует ключ в кодировке base64
        return base64.urlsafe_b64encode(sha256.digest())

    def encrypt_file(self):
        if not self.filepath:
            messagebox.showerror("Ошибка", "Сначала выберите файл.")
            return

        try:
            with open(self.filepath, 'r', encoding='utf-8') as f:
                content = f.read()
            if len(content) < 256:
                messagebox.showerror("Ошибка", "Файл должен содержать не менее 256 символов.")
                return
        except Exception as e:
            messagebox.showerror("Ошибка чтения файла", f"Не удалось прочитать файл: {e}")
            return
            
        # 1. Генерация публичных параметров
        p = generate_prime(256) # Модуль 
        g = 5 # Основание (часто используемое простое число)

        # 2. Генерация секретных ключей x и y
        x = generate_prime(256) # Секретный ключ "Алисы"
        y = generate_prime(256) # Секретный ключ "Боба"
        
        # 3. Вычисление открытых ключей
        A = pow(g, x, p)
        B = pow(g, y, p)
        
        # 4. Вычисление общего секрета
        shared_secret = pow(B, x, p)
        
        # 5. Шифрование файла
        key = self.derive_key(shared_secret)
        fernet = Fernet(key)
        encrypted_content = fernet.encrypt(content.encode('utf-8'))
        
        # Сохранение зашифрованного файла и файла с ключами
        encrypted_filepath = self.filepath + ".enc"
        key_filepath = self.filepath + ".key"
        
        with open(encrypted_filepath, 'wb') as f:
            f.write(encrypted_content)
            
        # Для расшифровки нам понадобятся p, g, A и секретный ключ Боба 'y'
        # В реальной системе 'y' хранился бы у Боба, а Алиса отправила бы ему 'A'
        with open(key_filepath, 'w') as f:
            f.write(f"{p}\n")
            f.write(f"{g}\n")
            f.write(f"{A}\n") # Открытый ключ Алисы
            f.write(f"{y}\n") # Секретный ключ Боба
            
        messagebox.showinfo("Успех", f"Файл успешно зашифрован!\nСохранен как: {encrypted_filepath}\nКлюч сохранен в: {key_filepath}")

    def decrypt_file(self):
        if not self.filepath or not self.filepath.endswith(".enc"):
            messagebox.showerror("Ошибка", "Выберите файл с расширением .enc для расшифровки.")
            return
            
        key_filepath = self.filepath.replace(".enc", ".key")
        if not os.path.exists(key_filepath):
            messagebox.showerror("Ошибка", f"Файл ключа не найден: {key_filepath}")
            return

        try:
            with open(key_filepath, 'r') as f:
                p = int(f.readline().strip())
                g = int(f.readline().strip())
                A = int(f.readline().strip())
                y = int(f.readline().strip())
        except Exception as e:
            messagebox.showerror("Ошибка", f"Не удалось прочитать файл ключа: {e}")
            return

        # Пересчитываем общий секрет с точки зрения "Боба"
        shared_secret = pow(A, y, p)
        key = self.derive_key(shared_secret)
        fernet = Fernet(key)

        try:
            with open(self.filepath, 'rb') as f:
                encrypted_content = f.read()
            
            decrypted_content = fernet.decrypt(encrypted_content)
            
            decrypted_filepath = self.filepath.replace(".enc", ".dec.txt")
            with open(decrypted_filepath, 'w', encoding='utf-8') as f:
                f.write(decrypted_content.decode('utf-8'))
                
            messagebox.showinfo("Успех", f"Файл успешно расшифрован!\nСохранен как: {decrypted_filepath}")

        except InvalidToken:
            messagebox.showerror("Ошибка", "Ошибка расшифровки. Ключ неверный или данные повреждены.")
        except Exception as e:
            messagebox.showerror("Ошибка", f"Произошла ошибка: {e}")


if __name__ == "__main__":
    root = tk.Tk()
    app = CryptoApp(root)
    root.mainloop()