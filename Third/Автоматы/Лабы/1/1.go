package main

import (
	"fmt"
	"math/rand"
	"strings"
	"time"
)

func main() {
	rand.Seed(time.Now().UnixNano())

	// Начинаем с аксиомы S
	word := "S"

	// Применяем правила, пока есть нетерминалы
	for strings.Contains(word, "S") || strings.Contains(word, "A") {
		word = applyRule(word)
		fmt.Printf("Промежуточный результат: %s\n", word)
	}

	fmt.Printf("\nИтоговое слово языка: %s\n", word)
}

// applyRule: функция применения грамматического правила
func applyRule(word string) string {
	// Ищем нетерминалы и применяем правила
	for i := 0; i < len(word); i++ {
		if word[i] == 'S' {
			// Правило: S → AA
			return word[:i] + "AA" + word[i+1:]
		}

		if word[i] == 'A' {
			// Случайный выбор между правилами:
			// A → aAb  или  A → ab
			if rand.Intn(2) == 0 {
				return word[:i] + "aAb" + word[i+1:]
			} else {
				return word[:i] + "ab" + word[i+1:]
			}
		}
	}

	return word
}
