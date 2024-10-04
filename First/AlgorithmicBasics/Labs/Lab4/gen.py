import random

# Генерируем список из 1000 случайных чисел
numbers = [random.randint(1, 100000) for _ in range(100)]

# Записываем числа в файл
with open("numbers.txt", "w") as file:
    for number in numbers:
        file.write(str(number) + "\n")