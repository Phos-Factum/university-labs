package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

// Состояния автомата
const (
	Q0 = 0 // Начальное состояние
	Q1 = 1 // Один ноль в конце
	Q2 = 2 // Два нуля в конце (финальное)
)

func main() {
	reader := bufio.NewReader(os.Stdin)

	fmt.Println("=== Конечный автомат: слова, заканчивающиеся на '00' ===")
	fmt.Println("Введите слово из символов 0 и 1:")

	word, _ := reader.ReadString('\n')
	word = strings.TrimSpace(word)

	// Проверка на пустое слово
	if word == "" {
		fmt.Println("\nРезультат: НЕТ (пустое слово)")
		fmt.Println("Финальное состояние: q0")
		return
	}

	// Проверка, что слово содержит только 0 и 1
	for _, ch := range word {
		if ch != '0' && ch != '1' {
			fmt.Println("\nОшибка: слово должно содержать только 0 и 1!")
			return
		}
	}

	// Запускаем автомат
	finalState := runAutomaton(word)

	// Вывод результата
	fmt.Printf("\nВходное слово: %s\n", word)
	fmt.Printf("Финальное состояние: q%d\n", finalState)

	if finalState == Q2 {
		fmt.Println("Результат: ДА (слово принадлежит языку)")
	} else {
		fmt.Println("Результат: НЕТ (слово не принадлежит языку)")
	}
}

// runAutomaton: функция запуска автомата
func runAutomaton(word string) int {
	state := Q0 // Начинаем с начального состояния

	fmt.Println("\nПроцесс работы автомата:")
	fmt.Printf("Старт: q%d\n", state)

	for i, ch := range word {
		prevstate := state
		state = transition(state, ch)
		fmt.Printf("Символ %d ('%c'): q%d → q%d\n", i+1, ch, prevstate, state)
	}

	return state
}

// transition: функция переходов между состояниями
func transition(state int, ch rune) int {
	switch state {
	case Q0:
		if ch == '0' {
			return Q1 // Был q0, прочитали 0 → переходим в q1
		}
		return Q0 // Был q0, прочитали 1 → остаёмся в q0

	case Q1:
		if ch == '0' {
			return Q2 // Был q1, прочитали 0 → переходим в q2 (два нуля!)
		}
		return Q0 // Был q1, прочитали 1 → сбрасываемся в q0

	case Q2:
		if ch == '0' {
			return Q2 // Был q2, прочитали 0 → остаёмся в q2 (всё ещё два нуля в конце)
		}
		return Q0 // Был q2, прочитали 1 → сбрасываемся в q0
	}

	return Q0
}
