import random

# Генерируем список из 1000 случайных чисел
numbers = [random.randint(1, 100000) for _ in range(10000)]

# Записываем числа в файл
with open("numbers3.txt", "w") as file:
    for number in numbers:
        file.write(str(number) + "\n")