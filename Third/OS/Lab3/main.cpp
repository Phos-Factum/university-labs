#include <chrono>
#include <iostream>
#include <mutex>
#include <random>
#include <semaphore>
#include <thread>

// Количество философов и вилок.
constexpr const size_t N = 5;

enum class State 
{
    THINKING = 0,  // Философ думает.
    HUNGRY = 1,    // Философ пытается взять вилку.
    EATING = 2,    // Философ ест.
};

// Массив для отслеживания состояния both_forks_available всех философов.
State state[N];

// Мьютекс для критической области (взятие и освобождение вилок).
std::mutex critical_region_mtx;

// Мьютекс для критической области (вывод статуса философа).
std::mutex output_mtx;

void print_philosophers_status() 
{
    std::lock_guard<std::mutex> lk(output_mtx);
    for (size_t i = 0; i < N; ++i) 
    {
        std::cout << "Философ" << i + 1 << ":";
        switch (state[i]) 
        {
            case State::THINKING:
                std::cout << " думает ";
                break;
            case State::HUNGRY:
                std::cout << " голоден";
                break;
            case State::EATING:
                std::cout << " ест    ";
                break;
        }
        if (i < N - 1) 
        {
            std::cout << " | ";
        }
    }
    std::cout << std::endl;
}


size_t inline left(size_t i) 
{  
    // Количество соседей слева от философа i, у которых можно взять обе вилки.
    return (i - 1 + N) % N; // N добавляется в случае, если i - 1 меньше нуля.
}

size_t inline right(size_t i) 
{  
    // Количество соседей справа от философа i, у которых можно взять обе вилки.
    return (i + 1) % N;
}

// Массив бинарных семафоров, один семафор для каждого философа.
// Заблокированный семафор означает, что философ i забрал (заблокировал) две вилки.
std::binary_semaphore both_forks_available[N]
{
    std::binary_semaphore{0}, std::binary_semaphore{0},
    std::binary_semaphore{0}, std::binary_semaphore{0},
    std::binary_semaphore{0}
};

size_t my_rand(size_t min, size_t max) 
{
    static std::mt19937 rnd(std::time(nullptr));
    return std::uniform_int_distribution<>(min, max)(rnd);
}

void test(size_t i)
// Если философ i голоден и оба соседа не едят, тогда есть. 
{ 
    // i: номер философа, от 0 до N - 1.
    if (state[i] == State::HUNGRY &&
        state[left(i)] != State::EATING &&
        state[right(i)] != State::EATING) 
    {
        state[i] = State::EATING;

        // Вилки больше не нужны.
        both_forks_available[i].release(); 
    }
}

void think(size_t i) 
{
    size_t duration = my_rand(400, 800);
    state[i] = State::THINKING;
    print_philosophers_status();
    std::this_thread::sleep_for(std::chrono::milliseconds(duration));
}

void take_forks(size_t i)
{
    {
        std::lock_guard<std::mutex> lk{critical_region_mtx};
        state[i] = State::HUNGRY;
        print_philosophers_status();
        test(i);
    }
    both_forks_available[i].acquire();
}

void eat(size_t i)
{
    size_t duration = my_rand(400, 800);
    state[i] = State::EATING;
    print_philosophers_status();
    std::this_thread::sleep_for(std::chrono::milliseconds(duration));
}

void put_forks(size_t i) 
{ 
    // Войти в критическую область.
    std::lock_guard<std::mutex> lk{critical_region_mtx};

    // Философ i закончил есть.
    state[i] = State::THINKING;

    // Проверить, может ли левый сосед есть.
    test(left(i));

    // Проверить, может ли правый сосед есть.
    test(right(i));
    
    // Покинуть критическую область.
}

void philosopher(size_t i)
{  
    // Вечный цикл.
    while (true) 
    {
        // Философ думает.
        think(i);

        // Взять две вилки или заблокировать.
        take_forks(i);

        // Есть.
        eat(i);

        // Положить вилки обратно на стол и проверить, могут ли соседи есть.
        put_forks(i);
    }
}

int main() {
    // [&] означает, что все переменные вне последующего лямбда-выражения захватываются по ссылке.
    
    std::jthread t0([&] { philosopher(0); });
    std::jthread t1([&] { philosopher(1); });
    std::jthread t2([&] { philosopher(2); });
    std::jthread t3([&] { philosopher(3); });
    std::jthread t4([&] { philosopher(4); });
}
