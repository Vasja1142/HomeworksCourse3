import numpy as np
import matplotlib.pyplot as plt

# Создаем сетку точек
x = np.linspace(-2, 3, 400)
y = np.linspace(-2, 3, 400)
X, Y = np.meshgrid(x, y)

# Уравнение кривой: (x² + y² - 1) + 6*(x-1)*(y-1) = 0
Z = (X**2 + Y**2 - 1) + 6 * (X - 1) * (Y - 1)

# Построение контурного графика (уровень 0)
plt.figure(figsize=(8, 8))
plt.contour(X, Y, Z, levels=[0], colors='black', linewidths=2)
plt.scatter(1.5, 0.5, color='blue', s=30, label='Точка (1.5, 0.5)')
plt.axhline(0, color='black', linewidth=1)
plt.axvline(0, color='black', linewidth=1)
plt.grid(True, alpha=0.9)
plt.xlabel('X')
plt.ylabel('Y')
plt.title('Морфинг 2 прямых и окружности')
plt.legend()
plt.axis('equal')
plt.show()