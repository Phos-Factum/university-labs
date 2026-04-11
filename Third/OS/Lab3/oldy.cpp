#include <chrono>
#include <iostream>
#include <random>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// Количество философов и вилок.
constexpr const size_t N = 5;

enum class State
{
    THINKING = 0, // Философ думает.
    HUNGRY = 1,   // Философ пытается взять вилку.
    EATING = 2,   // Философ ест.
};

// Массив для отслеживания состояния всех философов.
State state[N];

// Мьютекс для критической области (взятие и освобождение вилок).
pthread_mutex_t critical_region_mtx = PTHREAD_MUTEX_INITIALIZER;

// Мьютекс для критической области (вывод статуса философа).
pthread_mutex_t output_mtx = PTHREAD_MUTEX_INITIALIZER;

void print_philosophers_status()
{
    pthread_mutex_lock(&output_mtx);
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
            std::cout << " ест ";
            break;
        }
        if (i < N - 1)
        {
            std::cout << " | ";
        }
    }
    std::cout << std::endl;
    pthread_mutex_unlock(&output_mtx);
}

size_t inline left(size_t i)
{
    // Левый сосед философа i
    return (i - 1 + N) % N;
}

size_t inline right(size_t i)
{
    // Правый сосед философа i
    return (i + 1) % N;
}

// Массив семафоров POSIX, один семафор для каждого философа.
sem_t both_forks_available[N];

size_t my_rand(size_t min, size_t max)
{
    static std::mt19937 rnd(std::time(nullptr));
    return std::uniform_int_distribution<>(min, max)(rnd);
}

void test(size_t i)
{
    // Если философ i голоден и оба соседа не едят, тогда есть.
    if (state[i] == State::HUNGRY &&
        state[left(i)] != State::EATING &&
        state[right(i)] != State::EATING)
    {
        state[i] = State::EATING;
        // Разблокируем семафор - философ может есть
        sem_post(&both_forks_available[i]);
    }
}

void think(size_t i)
{
    size_t duration = my_rand(400, 800);
    state[i] = State::THINKING;
    print_philosophers_status();
    usleep(duration * 1000); // usleep принимает микросекунды
}

void take_forks(size_t i)
{
    pthread_mutex_lock(&critical_region_mtx);
    state[i] = State::HUNGRY;
    print_philosophers_status();
    test(i);
    pthread_mutex_unlock(&critical_region_mtx);
    
    // Ждем, пока семафор разрешит есть
    sem_wait(&both_forks_available[i]);
}

void eat(size_t i)
{
    size_t duration = my_rand(400, 800);
    state[i] = State::EATING;
    print_philosophers_status();
    usleep(duration * 1000);
}

void put_forks(size_t i)
{
    pthread_mutex_lock(&critical_region_mtx);
    state[i] = State::THINKING;
    
    // Проверить, может ли левый сосед есть.
    test(left(i));
    
    // Проверить, может ли правый сосед есть.
    test(right(i));
    
    pthread_mutex_unlock(&critical_region_mtx);
}

void* philosopher(void* arg)
{
    size_t i = reinterpret_cast<size_t>(arg);
    
    // Вечный цикл.
    while (true)
    {
        // Философ думает.
        think(i);
        
        // Взять две вилки или заблокировать.
        take_forks(i);
        
        // Есть.
        eat(i);
        
        // Положить вилки обратно на стол.
        put_forks(i);
    }
    return nullptr;
}

int main() {
    // Инициализируем семафоры
    for (size_t i = 0; i < N; ++i) {
        sem_init(&both_forks_available[i], 0, 0); // 0 - не разделяемый между процессами
    }
    
    // Создаем потоки
    pthread_t threads[N];
    for (size_t i = 0; i < N; ++i) {
        pthread_create(&threads[i], nullptr, philosopher, reinterpret_cast<void*>(i));
    }
    
    // Ждем завершения потоков (хотя они бесконечные)
    for (size_t i = 0; i < N; ++i) {
        pthread_join(threads[i], nullptr);
    }
    
    // Уничтожаем семафоры
    for (size_t i = 0; i < N; ++i) {
        sem_destroy(&both_forks_available[i]);
    }
    
    return 0;
}
