// LL-парсер (рекурсивный спуск), т.к. идём слева направо и используем функции (рекурсивные)
// для предсказания следующего токена (т.к. идём слева направо). LL тупо понятнее))
// По сути это парсер для распознавания грамматика 2 типа по Хомскому с помощью
// нисходящего LL-анализа (рекурсивного спуска).
package main

import (
	"fmt"
	"regexp"
)

// Аналогично структура токенов
type Token struct {
	Type  string
	Value string
}

// Аналогично правила для лексера))
var tokenPatterns = []struct {
	Type  string
	Regex *regexp.Regexp
}{
	{"keyword", regexp.MustCompile(`\bfor\b`)},
	{"operator", regexp.MustCompile(`==|!=|<=|>=|[+\-*/=<>]`)},
	{"int", regexp.MustCompile(`\b\d+\b`)},
	{"identifier", regexp.MustCompile(`[A-Za-z_][A-Za-z0-9_]*`)},
	{"separator", regexp.MustCompile(`[{}()]`)},
	{"whitespace", regexp.MustCompile(`\s+`)},
}

// Грамматика лексера - РЕГУЛЯРНАЯ
// Та же самая функция для лексического анализа с помощью лексера
func lexer(input string) []Token {
	var tokens []Token

	for len(input) > 0 {
		matched := false

		for _, p := range tokenPatterns {
			loc := p.Regex.FindStringIndex(input)

			if loc != nil && loc[0] == 0 {
				value := input[loc[0]:loc[1]]

				if p.Type != "whitespace" {
					tokens = append(tokens, Token{p.Type, value})
				}

				input = input[loc[1]:]
				matched = true
				break
			}
		}

		if !matched {
			input = input[1:]
		}
	}

	return tokens
}

// Грамматика парсера - КОНТЕКСТНО-СВОБОДНАЯ
// Структура парсера, которая хранит текущее состояние парсера (токен и позицию)
type Parser struct {
	tokens []Token
	pos    int
}

// current: возвращает текущий токен
func (p *Parser) current() Token {
	if p.pos >= len(p.tokens) {
		return Token{"EOF", ""}
	}
	return p.tokens[p.pos]
}

// eat: проверяет токен, а так же двигает указатель (если тип и значение совпадает)
func (p *Parser) eat(expectedType string, expectedValue string) bool {
	t := p.current()

	if t.Type == expectedType && (expectedValue == "" || t.Value == expectedValue) {
		p.pos++
		return true
	}
	return false
}

// --- Разбор грамматики (она, к слову, контекстно-свободная) ---
//
// Тут вообще нужно понимать, что мы будем "съедать" по токену и в случае получения
// неожиданного значения - бракуем всю конструкцию, ибо она не валидна.
// К слову, LL-парсер тут потому, что мы начали с S-правила (стартового) и идём по токенам вниз.
//
// S → for COND BODY
func (p *Parser) parseS() bool {
	if !p.eat("keyword", "for") {
		return false
	}
	return p.parseCOND() && p.parseBODY()
}

// COND → identifier operator identifier | identifier operator int
func (p *Parser) parseCOND() bool {
	if !p.eat("identifier", "") {
		return false
	}

	if !p.eat("operator", "") {
		return false
	}

	if p.eat("identifier", "") || p.eat("int", "") {
		return true
	}

	return false
}

// BODY → { STMT }
func (p *Parser) parseBODY() bool {
	if !p.eat("separator", "{") {
		return false
	}

	if !p.parseSTMT() {
		return false
	}

	if !p.eat("separator", "}") {
		return false
	}

	return true
}

// STMT → identifier = EXPR
func (p *Parser) parseSTMT() bool {
	if !p.eat("identifier", "") {
		return false
	}

	if !p.eat("operator", "=") {
		return false
	}

	return p.parseEXPR()
}

// EXPR -> identifier operator EXPR
func (p *Parser) parseEXPR() bool {

	// первый элемент (y или 10)
	if p.eat("identifier", "") || p.eat("int", "") {

		// проверяем есть ли продолжение: + ... (типо рекурсия)
		if p.eat("operator", "+") {
			return p.parseEXPR()
		}

		return true
	}

	return false
}

// Точка входа и пример цикла с предусловием, в теле которого реализуем подобие инкремента (только сумма)
func main() {
	code := `for x > y { y = y + 1 }`

	tokens := lexer(code)

	fmt.Println("TOKENS:")
	for _, t := range tokens {
		fmt.Printf("%-10s : %s\n", t.Type, t.Value)
	}

	parser := Parser{tokens: tokens}

	// Собственно, выводим вердикт парсера по итогам работы программы
	if parser.parseS() && parser.pos == len(tokens) {
		fmt.Println("\nVALID: строка соответствует грамматике")
	} else {
		fmt.Println("\nINVALID: ошибка синтаксиса")
	}
}

// S, COND, STMT - нетерминальные символы, абстрактные названия (кроме S - это аксиома :D)
// Грамматика описывает язык, а парсер уже распознаёт, принадлежит ли строка языку
// Это LL
