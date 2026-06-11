package main

import (
	"fmt"
	"regexp"
)

// Структурка конкретного токена, у которого есть тип и лексема (для таблички)
type Token struct {
	Type  string
	Value string
}

// Здесь описан набор правила для лексера (к типу привязана регулярка)
var tokenPatterns = []struct {
	Type  string
	Regex *regexp.Regexp
}{
	// В общем-то, список таких правил (неполный, лишь примерный)
	// Тут есть имена токенов, соотнесённые с примерами их значений
	{"comment", regexp.MustCompile(`//.*|/\*[\s\S]*?\*/`)},
	{"keyword", regexp.MustCompile(`\b(func|var|const|if|else|for|return|package|import|type|struct|interface|go|defer|map|range)\b`)},
	{"float", regexp.MustCompile(`\b\d+\.\d+\b`)},
	{"int", regexp.MustCompile(`\b\d+\b`)},
	{"string", regexp.MustCompile(`"[^"]*"`)},
	{"operator", regexp.MustCompile(`:=|==|!=|<=|>=|[+\-*/=<>]`)},
	{"separator", regexp.MustCompile(`[()\[\]{},;]`)},
	{"identifier", regexp.MustCompile(`[A-Za-z_][A-Za-z0-9_]*`)},
	{"whitespace", regexp.MustCompile(`\s+`)},
	// regexep.MustCompile тут компилирует регулярку в объект и выдаёт ошибку, если не вышло
}

// lexer: функция, превращающая строку в массив токенов
func lexer(input string) []Token {
	var tokens []Token

	// Читаем input до тех пор, пока он не пустой (matched - флаг, нашли ли токен или нет)
	for len(input) > 0 {
		matched := false

		// Перебираем каждый паттерн (тип токена)
		for _, pattern := range tokenPatterns {
			loc := pattern.Regex.FindStringIndex(input) // поиск совпадения

			if loc != nil && loc[0] == 0 { // проверка начала строки
				value := input[loc[0]:loc[1]] // извлечение значения (срез строки с токеном)

				if pattern.Type != "whitespace" {
					// !! Вот тут токен добавляется по шаблону структурки токена - в таблицу
					tokens = append(tokens, Token{
						Type:  pattern.Type,
						Value: value,
					})
				}

				input = input[loc[1]:]
				matched = true
				break
			}
		}

		if !matched {
			// Если символ не распознан — пропускаем!
			input = input[1:]
		}
	}

	return tokens
}

// Наш энтрипойнт, тут пример кода для анализа.
// Запускаем лексер и красивенько выводим таблицу токенов
func main() {
	code := `package main

func main() {
	var x = 10
	if x > 5 {
		fmt.Println("Hello")
	}
}`

	tokens := lexer(code)

	for _, t := range tokens {
		fmt.Printf("%-12s : %s\n", t.Type, t.Value)
	}
}
