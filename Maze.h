#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <iostream>

// Размеры лабиринта по умолчанию
constexpr int WIDTH = 21;
constexpr int HEIGHT = 21;

// Класс Maze отвечает за генерацию и хранение структуры лабиринта
class Maze {
private:
    // grid — матрица символов ('#' — стена, ' ' — проход, '0' — путь)
    std::vector<std::vector<char>> grid;

    // visited — матрица флагов посещения для генерации
    std::vector<std::vector<bool>> visited;

    // Направления движения: вниз, вверх, вправо, влево (двигаемся на 2 клетки)
    const int dx[4] = {0, 0, 2, -2};
    const int dy[4] = {2, -2, 0, 0};

    // Проверка, находится ли точка внутри границ лабиринта
    bool isInBounds(int x, int y) const;

public:
    Maze();
    void generate(int startX, int startY); // Генерация лабиринта с указанной стартовой точки
    bool isWalkable(int x, int y) const;   // Проверка, можно ли пройти по клетке
    void markPath(int x, int y);           // Отметить клетку как часть пути
    void print() const;                    // Напечатать лабиринт

    friend class AStarPathfinder; // Доступ к приватным данным для поиска пути
};

#endif
