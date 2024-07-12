#!/bin/bash

# Определяем массив
array=(10 -2 -3 8 -11 -7)

# 1) Находим номер максимального по модулю элемента массива
max_abs_index=-1
max_abs=0
for (( i=0; i<${#array[@]}; i++ )); do
    abs_value=${array[i]#-}  # Получаем модуль числа
    if (( abs_value > max_abs )); then
        max_abs=$abs_value
        max_abs_index=$i
    fi
done

# 2) Находим сумму элементов массива, расположенных после первого положительного элемента
sum=0
positive_found=false
for (( i=0; i<${#array[@]}; i++ )); do
    if (( ${array[i]} > 0 )); then
        positive_found=true
    elif $positive_found; then
        (( sum += ${array[i]} ))
    fi
done

# Выводим результаты
echo "Номер максимального по модулю элемента массива: $max_abs_index"
echo "Сумма элементов массива после первого положительного элемента: $sum"
