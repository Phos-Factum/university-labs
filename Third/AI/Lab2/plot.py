import matplotlib.pyplot as plt

# --- Входные данные ---
triangle = [(0, 0), (4, 0), (2, 3)]
circle_center = (2, 1)
radius = 1.5

# Точки пересечения (из вывода в Prolog)
points = [
    (3.118033988749895, 0.0),
    (0.8819660112501051, 0.0),
    (3.483085376098501, 0.775371935852248),
    (2.363068470055345, 2.4553972949169824),
    (1.6369315299446552, 2.455397294916983),
    (0.5169146239014986, 0.7753719358522478)
]

# --- Рисуем треугольник ---
x_tri, y_tri = zip(*triangle)
plt.plot((*x_tri, x_tri[0]), (*y_tri, y_tri[0]), 'b-', label='Треугольник')

# --- Рисуем окружность ---
circle = plt.Circle(circle_center, radius, color='r', fill=False, label='Окружность')
plt.gca().add_patch(circle)

# --- Рисуем точки пересечения ---
x_pts, y_pts = zip(*points)
plt.scatter(x_pts, y_pts, color='g', zorder=5, label='Точки пересечения')

# --- Отрисовка центра окружности ---
plt.scatter(*circle_center, color='black', marker='x', label='Центр')

# --- Оформление ---
plt.axis('equal')
plt.grid(True)
plt.legend()
plt.title('Пересечение треугольника и окружности')
plt.savefig("triangle_circle.png", dpi=200)
print("Сохранено: triangle_circle.png")

