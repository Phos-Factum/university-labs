; unsigned.asm

section .text
global unsigned_calc

unsigned_calc:
    ; Параметры:
    ; rdi - d_unsigned (16-bit), rsi - a_unsigned (8-bit), rdx - b_unsigned (8-bit)

    ; Расчёт числителя: 2 * d_unsigned - 96 / a_unsigned
    movzx rdi, di              ; Загрузить 16-битное unsigned значение d_unsigned и расширить до 64 бит
    movzx rsi, sil             ; Загрузить 8-битное unsigned значение a_unsigned и расширить до 64 бит
    mov rax, rdi               ; rax = d_unsigned
    shl rax, 1                 ; rax = 2 * d_unsigned

    ; Проверка деления на 0
    cmp rsi, 0                 
    je division_by_zero_error   ; Если a_unsigned == 0, переход на обработчик ошибки

    mov rbx, 96
    xor rdx, rdx               ; Очистить RDX перед unsigned делением
    div rsi                    ; 96 / a_unsigned
    sub rax, rbx               ; 2 * d_unsigned - 96 / a_unsigned

    ; Сохраняем результат числителя
    push rax

    ; Расчёт знаменателя: 34 / b_unsigned - a_unsigned + 1
    mov rax, 34
    movzx rdx, dl              ; Загрузить 8-битное unsigned значение b_unsigned и расширить до 64 бит

    ; Проверка деления на 0
    cmp rdx, 0                 
    je division_by_zero_error   ; Если b_unsigned == 0, переход на обработчик ошибки

    xor rdx, rdx               ; Очистить RDX перед unsigned делением
    div rdx                    ; 34 / b_unsigned
    sub rax, rsi               ; 34 / b_unsigned - a_unsigned
    add rax, 1                 ; +1

    ; Возвращаем числитель и знаменатель через rax и rdx
    pop rdx                    ; rdx = числитель
    ret

division_by_zero_error:
    ; Обработка ошибки деления на 0
    xor rax, rax               ; Устанавливаем rax = 0 как признак ошибки
    ret

