import math
import numpy as np
import matplotlib.pyplot as plt
from scipy.special import factorial

# Функция для вычисления вероятности
def compute_probability(a, v):
    numerator = (a**v) / factorial(v, exact=False)
    denominator = sum((a**k) / factorial(k, exact=False) for k in range(v + 1))
    return numerator / denominator

# Определим диапазоны значений a и v
a_values = np.arange(0.1, 1.1, 0.1)  # a от 0.1 до 1
v_values = range(1, 11)              # v от 1 до 10
v_values1 = range(5, 51, 5)          # v от 5 до 50 с шагом 5
v_values2 = range(20, 201, 20)       # v от 20 до 200 с шагом 20

p_values = []
p_values1 = []
p_values2 = []

New = [0.091, 0.016, 0.004, 2.49*10**(-4), 3.346*10**(-4), 2.199*10**(-4), 0, 0, 0, 0]
New1 = [0]*10
New2 = [0]*10

# Вычислим и выведем вероятности для каждого значения a и v
# Для v от 1 до 10
for i, a in enumerate(a_values):
    v = v_values[i]
    p = compute_probability(a, v)
    p_values.append(p)
    print(f'a = {a:.1f}, v = {v}, p = {p:.6f}')

# Для v от 5 до 50 с шагом 5
for i, a in enumerate(a_values):
    v1 = v_values1[i]
    p1 = compute_probability(a, v1)
    p_values1.append(p1)
    print(f'a = {a:.1f}, v1 = {v1}, p1 = {p1:.6f}')

# Для v от 20 до 200 с шагом 20
for i, a in enumerate(a_values):
    v2 = v_values2[i]
    p2 = compute_probability(a, v2)
    p_values2.append(p2)
    print(f'a = {a:.1f}, v2 = {v2}, p2 = {p2:.6f}')

# Построение первого графика
plt.figure(figsize=(10, 6))
plt.plot(v_values, p_values, marker='o', label='v от 1 до 10 (аналитический)')
plt.plot(v_values, New, marker='x', label='v от 1 до 10 (модель)')  # Добавляем новую линию для сравнения
plt.xlabel('Количество обслуживающих устройств (v)')
plt.ylabel('Вероятность потерь (p)')
plt.title('Зависимость вероятности потерь (v от 1 до 10)')
plt.grid(True)
plt.legend()
plt.show()

# Построение второго графика
plt.figure(figsize=(10, 6))
plt.plot(v_values1, p_values1, marker='o', label='v от 5 до 50 с шагом 5 (аналитический)')
plt.plot(v_values, New1, marker='x', label='v от 1 до 10 (модель)')  # Добавляем новую линию для сравнения
plt.xlabel('Количество обслуживающих устройств (v)')
plt.ylabel('Вероятность потерь (p)')
plt.title('Зависимость вероятности потерь (v от 5 до 50 с шагом 5)')
plt.grid(True)
plt.legend()
plt.show()

# Построение третьего графика
plt.figure(figsize=(10, 6))
plt.plot(v_values2, p_values2, marker='o', label='v от 20 до 200 с шагом 20 (аналитический)')
plt.plot(v_values, New2, marker='x', label='v от 1 до 10 (модель)')  # Добавляем новую линию для сравнения
plt.xlabel('Количество обслуживающих устройств (v)')
plt.ylabel('Вероятность потерь (p)')
plt.title('Зависимость вероятности потерь (v от 20 до 200 с шагом 20)')
plt.grid(True)
plt.legend()
plt.show()