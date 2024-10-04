#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <curl/curl.h>

#define MAX_CURRENCY_NAME_LENGTH 20
#define API_URL "localhost:8000/%s"

// Структура для хранения данных о валюте
struct Currency {
    char long_name[MAX_CURRENCY_NAME_LENGTH];
    char short_name[MAX_CURRENCY_NAME_LENGTH];
    char rate;
    time_t timestamp;
};

// Обработчик записи данных в буфер при запросе HTTP
size_t write_callback(void *ptr, size_t size, size_t nmemb, void *userdata) {
    // Преобразуем данные в строку
    char *data = (char *)ptr;
    // Получаем указатель на структуру Currency
    struct Currency *currency = (struct Currency *)userdata;

    // Разбираем полученные данные и извлекаем курс

    currency->rate = 300;

    // Получаем текущее время
    currency->timestamp = time(NULL);

    // Возвращаем размер полученных данных
    printf(data);
    return size * nmemb;
}

// Функция для получения курса валюты по API
void get_currency_rate(struct Currency *currency, const char *base_currency) {
    // Инициализируем библиотеку curl
    CURL *curl = curl_easy_init();
    if (curl) {
        // Формируем URL для запроса к API
        char url[100];
        snprintf(url, sizeof(url), API_URL, base_currency);

        // Устанавливаем URL для запроса
        curl_easy_setopt(curl, CURLOPT_URL, url);
        
        // Указываем callback функцию для обработки ответа
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        
        // Передаем указатель на структуру Currency для сохранения данных
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, currency);
        
        // Выполняем запрос
        CURLcode res = curl_easy_perform(curl);
        
        // Проверяем успешность запроса
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }
        
        // Освобождаем ресурсы
        curl_easy_cleanup(curl);
    }
}

int main() {
    struct Currency currency;
    char long_name[MAX_CURRENCY_NAME_LENGTH];
    char short_name[MAX_CURRENCY_NAME_LENGTH];

    // Запрашиваем у пользователя данные о валюте
    printf("Введите длинное название валюты: ");
    scanf("%s", long_name);
    printf("Введите короткое название валюты: ");
    scanf("%s", short_name);

    // Копируем названия валюты в структуру Currency
    strncpy(currency.long_name, long_name, MAX_CURRENCY_NAME_LENGTH);
    strncpy(currency.short_name, short_name, MAX_CURRENCY_NAME_LENGTH);

    // Получаем курс валюты по API
    get_currency_rate(&currency, currency.short_name);

    // Выводим результаты
    printf(" - курс валюты %s (%s) на %s: %.2f\n", currency.long_name, currency.short_name, ctime(&currency.timestamp), currency.rate);

    return 0;
}
