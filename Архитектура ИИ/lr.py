import numpy as np
import random

# =================== КЛАСС СЕТИ ХЕММИНГА (ИСПРАВЛЕННЫЙ) ===================

class HammingNetwork:
    def __init__(self, prototypes, epsilon=0.1):
        """
        Полностью корректная и стабильная реализация сети Хемминга.
        """
        self.prototypes = np.array(prototypes, dtype=float)
        self.num_classes = len(prototypes)
        self.vector_length = len(prototypes[0])
        self.epsilon = epsilon

        # --- Слой сравнения (Feedforward Layer) ---
        # Веса в биполярном виде (-1, 1)
        self.W = 2 * self.prototypes - 1

        # --- Конкурентный слой (Recurrent MAXNET Layer) ---
        # Создаем матрицу тормозящих связей V
        self.V = np.ones((self.num_classes, self.num_classes)) * (-epsilon)
        np.fill_diagonal(self.V, 1.0)

    def predict(self, input_vector, max_iterations=100):
        """
        Предсказание класса с использованием правильного MAXNET.
        """
        # 1. Преобразуем входной вектор в биполярный вид (-1, 1)
        x_bipolar = 2 * np.array(input_vector) - 1

        # 2. Слой сравнения: вычисляем сходство
        similarity = np.dot(self.W, x_bipolar)
        
        # 3. Добавляем смещение
        y = similarity + self.vector_length
        
        # 4. Конкурентный слой (MAXNET)
        for _ in range(max_iterations):
            y_old = y.copy()
            y = np.dot(self.V, y)
            y = np.maximum(y, 0)
            
            if np.sum(np.abs(y - y_old)) < 1e-6:
                break
                
        winner_class = np.argmax(y)
        return winner_class, y

# =================== ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ ===================

def create_letter_patterns():
    """Создание эталонных паттернов букв A-E"""
    patterns = {
        'A': [0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1],
        'B': [1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0],
        'C': [0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1],
        'D': [1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0],
        'E': [1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1]
    }
    return patterns

def add_noise(pattern, noise_level=0.1):
    noisy_pattern = pattern.copy()
    num_flips = max(1, int(len(pattern) * noise_level))
    flip_positions = random.sample(range(len(pattern)), num_flips)
    for pos in flip_positions:
        noisy_pattern[pos] = 1 - noisy_pattern[pos]
    return noisy_pattern

def print_pattern(pattern, width=5, height=7):
    """Вывод паттерна в виде картинки в консоли"""
    for i in range(height):
        row = ""
        for j in range(width):
            pixel = pattern[i * width + j]
            row += "██" if pixel == 1 else "  "
        print(row)
    print()

def calculate_hamming_distance(vec1, vec2):
    return np.sum(np.array(vec1) != np.array(vec2))

# =================== ОСНОВНАЯ И ИНТЕРАКТИВНАЯ ЧАСТИ ===================

def main():
    print("🤖 Робот-почтальон v2.0: Финальная версия с картинками")
    print("=" * 55)
    
    patterns = create_letter_patterns()
    letters = list(patterns.keys())
    prototypes = [patterns[letter] for letter in letters]
    
    network = HammingNetwork(prototypes, epsilon=0.1)
    
    # Тестирование с оригинальными паттернами
    print("\n🔍 Тестирование с оригинальными паттернами:")
    print("-" * 45)
    for i, letter in enumerate(letters):
        result, activations = network.predict(prototypes[i])
        print(f"Буква {letter}: распознана как {letters[result]}")
        print(f"  Активации: {[f'{a:.2f}' for a in activations]}")
    
    # Тестирование с зашумленными паттернами (С КАРТИНКАМИ)
    print("\n💥 Тестирование с зашумленными паттернами:")
    print("-" * 45)
    
    all_tests = 0
    correct_tests = 0
    
    for noise_level in [0.1, 0.15, 0.2, 0.25]:
        print(f"\n🔊 Уровень шума: {noise_level*100:.0f}%")
        print("-" * 25)
        
        correct_for_noise = 0
        for i, letter in enumerate(letters):
            # Создаем зашумленный паттерн
            noisy_pattern = add_noise(patterns[letter], noise_level)
            
            # Распознаем его
            result, activations = network.predict(noisy_pattern)
            distance = calculate_hamming_distance(noisy_pattern, patterns[letter])
            
            # --- ВОТ ОН, ВЫВОД КАРТИНКИ ---
            print(f"\nОригинал: {letter}")
            print("Зашумленный паттерн:")
            print_pattern(noisy_pattern)
            print(f"Распознано как: {letters[result]}")
            print(f"Расстояние Хемминга до оригинала: {distance}")
            print(f"Активации: {[f'{a:.2f}' for a in activations]}")
            
            if letter == letters[result]:
                print("✅ Верно!")
                correct_for_noise += 1
                correct_tests += 1
            else:
                print("❌ ОШИБКА!")
            all_tests += 1
            print("-" * 15)
        
        print(f"\nТочность при шуме {noise_level*100:.0f}%: {correct_for_noise}/{len(letters)} ({correct_for_noise/len(letters)*100:.0f}%)")

    print(f"\n🎯 ОБЩАЯ ТОЧНОСТЬ: {correct_tests}/{all_tests} ({correct_tests/all_tests*100:.1f}%)")

def interactive_demo():
    """Улучшенная интерактивная игра: Где буква?"""
    print("\n🎮 Интерактивная игра: ГДЕ БУКВА? (Угадай по зашумленному изображению)")
    print("=" * 70)
    
    patterns = create_letter_patterns()
    letters = list(patterns.keys())
    prototypes = [patterns[letter] for letter in letters]
    network = HammingNetwork(prototypes, epsilon=0.1)
    
    alphabet = list("ABCDEFGHIJKLMNOPQRSTUVWXYZ")
    
    while True:
        # Случайно выберем букву
        true_letter_index = random.randint(0, len(letters)-1)
        true_letter = letters[true_letter_index]
        
        # Создадим ее зашумленную версию
        noise_level = random.uniform(0.1, 0.25)  # Случайный уровень шума
        noisy_pattern = add_noise(patterns[true_letter], noise_level)
        
        print("\n🔮 Попробуй угадать букву по образцу")
        print("Зашумленное изображение:")
        print_pattern(noisy_pattern)
        
        # Предскажем сеть
        predicted_idx, activations = network.predict(noisy_pattern)
        predicted_letter = letters[predicted_idx]
        
        # Предложим 3 варианта
        choices = []
        choices.append(true_letter)  # правильный
        
        # Добавим 2 случайных неправильных ответа
        while len(choices) < 3:
            wrong_letter = random.choice(letters)
            if wrong_letter != true_letter:
                choices.append(wrong_letter)
                
        random.shuffle(choices)
        
        print("\nВарианты ответов:")
        for i, opt in enumerate(choices):
            print(f"  {i+1}. {opt}")
            
        guess = input("Твой выбор (введи номер): ")
        
        if guess.isdigit() and int(guess) in range(1,4):
            chosen_letter = choices[int(guess)-1]
            
            print(f"\nВы выбрали: {chosen_letter}")
            print(f"Робот думает: {predicted_letter}")
            print(f"Правильно было: {true_letter}")
            
            if chosen_letter == true_letter:
                print("🎉 Верно!")
            else:
                print("❌ Неправильно, попробуй еще раз")
                
        else:
            print("Неверный ввод, давай еще разок!")
        
        if input("\nИграть ли ещё (да/нет)? ").strip().lower() != 'да':
            break
        
if __name__ == "__main__":
    main()
    interactive_demo()