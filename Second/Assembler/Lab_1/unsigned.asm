section .data
    msg_error db "Ошибка: деление на ноль", 10, 0
    format db "%llu", 0         ; Формат для вывода

section .bss
    numerator resq 1            ; Числитель (64 бита)
    denominator resq 1          ; Знаменатель (64 бита)
    result resq 1               ; Результат (64 бита)

section .text
    extern printf
    extern scanf
    global calc_unsigned_expression

calc_unsigned_expression:
    ; Входные данные: a (unsigned char), b (unsigned char), d (unsigned int)
    ; Подготовка для работы
    movzx rax, byte [rdi]       ; Загружаем a (unsigned char)
    test rax, rax                ; Проверка a на 0
    jz divide_by_zero            ; Если a == 0, переход на обработку деления на ноль

    movzx rbx, byte [rsi]       ; Загружаем b (unsigned char)
    test rbx, rbx                ; Проверка b на 0
    jz divide_by_zero            ; Если b == 0, переход на обработку деления на ноль

    mov rdx, dword [rdx]        ; Загружаем d (unsigned int)
    shl rdx, 1                   ; 2 * d
    mov rax, 96                  ; Загружаем 96
    xor rdx, rdx                 ; Обнуляем rdx для деления
    mov rax, 96                  ; Загружаем 96 (перезапись rax, убираем лишнюю строку)
    div rax                      ; 96 / a
    sub rdx, rax                 ; 2 * d - (96 / a)

    ; Знаменатель: (34 / b) - a + 1
    mov rax, 34                  ; Загружаем 34
    xor rdx, rdx                 ; Обнуляем rdx для деления
    movzx rbx, byte [rsi]        ; Заносим b снова
    xor rdx, rdx                 ; Обнуляем rdx перед делением
    div rbx                      ; 34 / b
    sub rax, rdi                 ; (34 / b) - a
    add rax, 1                   ; +1

    test rax, rax                ; Проверка на 0 в знаменателе
    jz divide_by_zero            ; Если знаменатель равен 0, переход на обработку деления на ноль

    ; Деление
    mov rdx, rdx                 ; Восстанавливаем числитель (предыдущий результат)
    cqo                           ; Расширяем rdx:rax для деления
    mov rax, [numerator]         ; Загружаем числитель для деления
    div rax                      ; Делим числитель на знаменатель

    ; Сохранение результатов
    mov [numerator], rdx        ; Сохраняем числитель (64 бита)
    mov [denominator], rax       ; Сохраняем знаменатель (64 бита)
    mov [result], rax            ; Сохраняем результат (64 бита)

    ret

divide_by_zero:
    mov rdi, msg_error          ; Сообщение об ошибке
    call printf                  ; Вывод сообщения
    xor rax, rax                 ; Возвращаем 0 в случае ошибки
    ret

