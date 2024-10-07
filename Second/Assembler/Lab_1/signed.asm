; signed.asm

section .text
global signed_calc

signed_calc:
    ; Параметры:
    ; rdi - d_signed (16-bit), rsi - a_signed (8-bit), rdx - b_signed (8-bit)

    ; Расчёт числителя: 2 * d_signed - 96 / a_signed
    movsx rdi, di              ; Загрузить 16-битное signed значение d_signed и расширить до 64 бит
    movsx rsi, sil             ; Загрузить 8-битное signed значение a_signed и расширить до 64 бит
    mov rax, rdi               ; rax = d_signed
    shl rax, 1                 ; rax = 2 * d_signed

    ; Проверка деления на 0
    cmp rsi, 0                 
    je division_by_zero_error   ; Если a_signed == 0, переход на обработчик ошибки

    mov rbx, 96
    cqo                        ; Подготовка к делению
    idiv rsi                   ; 96 / a_signed (rsi - 64-битное значение)
    sub rax, rbx               ; 2 * d_signed - 96 / a_signed

    ; Сохраняем результат числителя
    push rax

    ; Расчёт знаменателя: 34 / b_signed - a_signed + 1
    mov rax, 34
    movsx rdx, dl              ; Загрузить 8-битное signed значение b_signed и расширить до 64 бит

    ; Проверка деления на 0
    cmp rdx, 0                 
    je division_by_zero_error   ; Если b_signed == 0, переход на обработчик ошибки

    cqo                        ; Подготовка к делению
    idiv rdx                   ; 34 / b_signed
    sub rax, rsi               ; 34 / b_signed - a_signed
    add rax, 1                 ; +1

    ; Возвращаем числитель и знаменатель через rax и rdx
    pop rdx                    ; rdx = числитель
    ret

division_by_zero_error:
    ; Обработка ошибки деления на 0
    ; Можно, например, установить флаг ошибки или вернуть 0
    xor rax, rax               ; Устанавливаем rax = 0 как признак ошибки
    ret


