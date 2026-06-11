package main

import (
	"fmt"
)

// Кастомный тип для удобства
type State int

// В общем, состояний сделал 2, ибо цена товара так-то 2 монеты, а значит всё, что больше
// есть возвращение в исходное состояние (товар куплен - вернулись назад) + выдача сдачи
const (
	S0 State = iota // 0 рублей (см. что такое iota в Go)
	S1              // 1 рубль
)

// Выход, как один из зависимых параметров в Мили-автомате
// Тут, по сути, просто булево отмечаем факт покупки + выдаём сдачу
type Output struct {
	GiveProduct bool
	Change      int
}

// Структурка вендингового автомата
type VendingMachine struct {
	state State
}

// Конструктор для нового автомата
func NewMachine() *VendingMachine {
	return &VendingMachine{state: S0}
}

// Функция, которая обрабатывает второй зависимый параметр - вход (тут мы вставляем монетку)
// Здесь просто обрабатываем буквально КАЖДЫЙ кейс связанный с сотсояниями и входами
func (vm *VendingMachine) InsertCoin(coin int) Output {
	var result Output

	switch vm.state {

	case S0:
		switch coin {
		case 1:
			vm.state = S1
			return Output{false, 0}
		case 2:
			vm.state = S0
			return Output{true, 0}
		case 5:
			vm.state = S0
			return Output{true, 3}
		case 10:
			vm.state = S0
			return Output{true, 8}
		}

	case S1:
		switch coin {
		case 1:
			vm.state = S0
			return Output{true, 0}
		case 2:
			vm.state = S0
			return Output{true, 1}
		case 5:
			vm.state = S0
			return Output{true, 4}
		case 10:
			vm.state = S0
			return Output{true, 9}
		}
	}

	return result
}

func main() {
	// Алгоритм примерно таков:
	// 1. Создаём новый автомат
	// 2. Генерим слайс тестовых значений
	// 3. Итерируемся по монеткам разных номиналов (вставляем их в автомат)
	// 4. Последовательно выводим результаты (факты продажи + сумму сдачи)

	vm := NewMachine()

	inputs := []int{1, 1, 5, 2, 10}

	for _, coin := range inputs {
		out := vm.InsertCoin(coin)

		fmt.Printf("Вход: %d → ", coin)

		if !out.GiveProduct {
			fmt.Println("ничего не делать")
		} else if out.Change == 0 {
			fmt.Println("выдать товар")
		} else {
			fmt.Printf("выдать товар + сдача %d\n", out.Change)
		}
	}
}
