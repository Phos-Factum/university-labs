; calc.asm

section .data
    signed_result dq 0          ; Результат signed выражения
    signed_numerator dq 0       ; Числитель signed выражения
    signed_denominator dq 0     ; Знаменатель signed выражения
    
    unsigned_result dq 0        ; Результат unsigned выражения
    unsigned_numerator dq 0      ; Числитель unsigned выражения
    unsigned_denominator dq 0    ; Знаменатель unsigned выражения

section .text
    global signed_unsigned_calc

; Вход: 
; rdi = d, rsi = a, rdx = b
; Для signed:
; eax - тип (0 - unsigned, 1 - signed)

signed_unsigned_calc:
    ; Сохранение регистров
    push rbx
    push rbp

    ; Проверка знаковости данных
    cmp eax, 1
    je calc_signed

calc_unsigned:
    ; Ветвь для unsigned данных

    ; Числитель: (2 * d_unsigned - 96 / a_unsigned)
    mov rax, rsi            ; a_unsigned
    test rax, rax           ; Проверка на 0
    jz div_by_zero_error    ; Если a_unsigned == 0, ошибка
    mov rbx, 96
    xor rdx, rdx            ; Обнуление rdx для деления
    div rax                 ; 96 / a_unsigned
    mov rcx, rax            ; Сохранение результата деления в rcx

    mov rax, rdi            ; d_unsigned
    shl rax, 1              ; 2 * d_unsigned
    sub rax, rcx            ; (2 * d_unsigned - 96 / a_unsigned)
    mov [unsigned_numerator], rax ; Сохранение числителя

    ; Знаменатель: (34 / b_unsigned - a_unsigned + 1)
    mov rax, rdx            ; b_unsigned
    test rax, rax           ; Проверка на 0
    jz div_by_zero_error    ; Если b_unsigned == 0, ошибка
    mov rbx, 34
    xor rdx, rdx            ; Обнуление rdx для деления
    div rax                 ; 34 / b_unsigned
    sub rax, rsi            ; - a_unsigned
    add rax, 1              ; + 1
    mov [unsigned_denominator], rax ; Сохранение знаменателя

    ; Проверка деления на 0
    cmp rax, 0
    je div_by_zero_error

    ; Результат
    mov rdx, [unsigned_numerator]
    mov rax, rdx            ; Загружаем числитель в rax
    xor rdx, rdx            ; Обнуление rdx перед делением
    mov rbx, [unsigned_denominator] ; Получаем знаменатель
    cmp rbx, 0              ; Проверяем, не ноль ли он
    je div_by_zero_error
    div rbx                 ; Деление
    mov [unsigned_result], rax
    jmp end_calc

calc_signed:
    ; Ветвь для signed данных

    ; Числитель: (2 * d_signed - 96 / a_signed)
    mov rax, rsi            ; a_signed
    test rax, rax           ; Проверка на 0
    jz div_by_zero_error    ; Если a_signed == 0, ошибка
    mov rbx, 96
    xor rdx, rdx            ; Обнуление rdx для деления
    idiv rax                ; 96 / a_signed
    mov rcx, rax            ; Сохранение результата деления в rcx

    mov rax, rdi            ; d_signed
    shl rax, 1              ; 2 * d_signed
    sub rax, rcx            ; (2 * d_signed - 96 / a_signed)
    mov [signed_numerator], rax ; Сохранение числителя

    ; Знаменатель: (34 / b_signed - a_signed + 1)
    mov rax, rdx            ; b_signed
    test rax, rax           ; Проверка на 0
    jz div_by_zero_error    ; Если b_signed == 0, ошибка
    mov rbx, 34
    xor rdx, rdx            ; Обнуление rdx для деления
    idiv rax                ; 34 / b_signed
    sub rax, rsi            ; - a_signed
    add rax, 1              ; + 1
    mov [signed_denominator], rax ; Сохранение знаменателя

    ; Проверка деления на 0
    cmp rax, 0
    je div_by_zero_error

    ; Результат
    mov rdx, [signed_numerator]
    mov rax, rdx            ; Загружаем числитель в rax
    xor rdx, rdx            ; Обнуление rdx перед делением
    mov rbx, [signed_denominator] ; Получаем знаменатель
    cmp rbx, 0              ; Проверяем, не ноль ли он
    je div_by_zero_error
    idiv rbx                ; Деление
    mov [signed_result], rax

end_calc:
    ; Восстановление регистров
    pop rbp
    pop rbx
    ret

div_by_zero_error:
    mov rax, -1
    jmp end_calc

