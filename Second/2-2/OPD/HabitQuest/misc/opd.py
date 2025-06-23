import matplotlib.pyplot as plt
from matplotlib.patches import Patch

def draw_final_gantt():
    # Широкий формат (16x8) для лучшего отображения
    fig, ax = plt.subplots(figsize=(16, 8))
    
    # Данные этапов (в порядке СВЕРХУ ВНИЗ)
    phases = [
        {
            "name": "5. Деплой",
            "start": 10,
            "end": 12,
            "color": "#ff8a65",
            "details": "• Настройка сервера\n• Развертывание\n• Пилотный запуск"
        },
        {
            "name": "4. Тестирование",
            "start": 7,
            "end": 11,
            "color": "#ffd54f",
            "details": "• Модульное тестирование\n• Интеграционное тестирование\n• Юзер-тесты"
        },
        {
            "name": "3. Геймификация",
            "start": 4,
            "end": 8,
            "color": "#aed581",
            "details": "• Система баллов\n• Статистика\n• Мотивационные механики"
        },
        {
            "name": "2. Разработка",
            "start": 1,
            "end": 7,
            "color": "#4db6ac",
            "details": "• Трекер сна\n• Тренировочный ассистент\n• Интеграция модулей"
        },
        {
            "name": "1. Проектирование",
            "start": 0,
            "end": 2,
            "color": "#4fc3f7",
            "details": "• Анализ требований\n• Проектирование БД\n• Определение API"
        }
    ]
    
    # Рисуем этапы (сверху вниз)
    for i, phase in enumerate(phases):
        duration = phase["end"] - phase["start"]
        ax.barh(phase["name"], duration, 
                left=phase["start"], color=phase["color"], 
                height=0.6, edgecolor='black', alpha=0.8)
        
        # Подписи внутри блоков
        ax.text(phase["start"] + duration/2, i, 
                phase["details"], 
                ha='center', va='center', 
                fontsize=9, color='black')

    # Настройка осей
    ax.set_xlim(0, 12)
    ax.set_xticks(range(0, 13))
    ax.set_xticklabels([f"Неделя {i}" if i > 0 else "" for i in range(0, 13)], 
                      rotation=45, ha='right')
    
    # Легенда справа сверху
    legend_elements = [
        Patch(facecolor='#4fc3f7', edgecolor='black', label='1. Проектирование'),
        Patch(facecolor='#4db6ac', edgecolor='black', label='2. Разработка'),
        Patch(facecolor='#aed581', edgecolor='black', label='3. Геймификация'),
        Patch(facecolor='#ffd54f', edgecolor='black', label='4. Тестирование'),
        Patch(facecolor='#ff8a65', edgecolor='black', label='5. Деплой')
    ]
    ax.legend(handles=legend_elements, loc='upper right', 
              bbox_to_anchor=(1.0, 1.0), framealpha=1)

    # Обновлённое название диаграммы
    ax.set_title("Разработка телеграм-бота HabitQuest", 
                pad=20, fontsize=16, fontweight='bold')

    # Чистый дизайн
    ax.grid(axis='x', linestyle=':', alpha=0.4)
    ax.spines['top'].set_visible(False)
    ax.spines['right'].set_visible(False)

    plt.tight_layout()
    plt.savefig('habitquest_development_gantt.png', dpi=150, bbox_inches='tight')
    print("График сохранен как 'habitquest_development_gantt.png'")

if __name__ == "__main__":
    draw_final_gantt()