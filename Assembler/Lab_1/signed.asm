section .data
    msg_error db "Ошибка: деление на ноль", 10, 0
    format db "%lld", 0        ; Формат для вывода

section .bss
    numerator resq 1           ; Числитель (64 бита)
    denominator resq 1         ; Знаменатель (64 бита)
    result resq 1              ; Результат (64 бита)

section .text
    extern printf
    extern scanf
    global calc_signed_expression

calc_signed_expression:
    ; Входные данные: a (signed char), b (signed char), d (signed int)
    ; Подготовка для работы
    movsx rax, byte [rdi]       ; Загружаем a (signed char)
    test rax, rax                ; Проверка a на 0
    jz divide_by_zero            ; Если a == 0, переход на обработку деления на ноль

    movsx rbx, byte [rsi]       ; Загружаем b (signed char)
    test rbx, rbx                ; Проверка b на 0
    jz divide_by_zero            ; Если b == 0, переход на обработку деления на ноль

    movsx rcx, dword [rdx]      ; Загружаем d (signed int) в rcx
    shl rcx, 1                   ; 2 * d
    mov rax, 96                  ; Загружаем 96
    cqo                           ; Расширяем rax
    idiv rax                     ; 96 / a
    sub rcx, rax                 ; 2 * d - (96 / a)

    ; Знаменатель: (34 / b) - a + 1
    mov rax, 34                  ; Загружаем 34
    xor rdx, rdx                 ; Обнуляем rdx для деления
    movsx rbx, byte [rsi]        ; Заносим b снова
    idiv rbx                     ; 34 / b
    sub rax, rdi                 ; (34 / b) - a
    add rax, 1                   ; +1

    test rax, rax                ; Проверка на 0 в знаменателе
    jz divide_by_zero            ; Если знаменатель равен 0, переход на обработку деления на ноль

    ; Деление
    mov rdx, rcx                 ; Восстанавливаем числитель (2 * d - (96 / a))
    cqo                           ; Расширяем rdx:rax для деления
    idiv rax                     ; Делим числитель на знаменатель

    ; Сохранение результатов
    mov [numerator], rdx        ; Сохраняем числитель (64 бита)
    mov [denominator], rax       ; Сохраняем знаменатель (64 бита)
    mov [result], rax            ; Сохраняем результат (64 бита)

    ret

divide_by_zero:
    mov rdi, msg_error
    call printf                  ; Вывод сообщения
    xor rax, rax                 ; Возвращаем 0 в случае ошибки
    ret

