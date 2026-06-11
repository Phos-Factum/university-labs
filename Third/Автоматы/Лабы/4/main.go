package main

import (
	"fmt"
	"os"
	"regexp"
)

func main() {
	// Через аргументы как в скрипте сделаем обработку название файла для парсинга
	if len(os.Args) < 2 {
		fmt.Println("Использование: go run main.go file.html")
		return
	}

	fileName := os.Args[1]

	data, err := os.ReadFile(fileName)
	if err != nil {
		fmt.Println("Ошибка чтения файла:", err)
		return
	}

	// Регулярное выражение для телефонов (по стандарту телефонных номеров)
	re := regexp.MustCompile(`\(?\d{3}\)?[\s\-]?\d{3}[\s\-]?\d{2}[\s\-]?\d{2}`)

	phones := re.FindAllString(string(data), -1) // -1 это значит искать все совпадения в файлике

	if len(phones) == 0 {
		fmt.Println("Телефоны не найдены")
		return
	}

	fmt.Println("Найденные телефоны:")
	for _, phone := range phones {
		fmt.Println(phone)
	}
}
