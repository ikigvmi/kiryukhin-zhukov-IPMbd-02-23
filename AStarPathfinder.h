#ifndef ASTARPATHFINDER_H
#define ASTARPATHFINDER_H

#include "Maze.h"

// Структура узла для A* поиска
struct Node {
    int x, y;      // координаты
    float g, h;    // g — путь от старта, h — эвристика до цели
    Node* parent;  // ссылка на родителя (для восстановления пути)

    // Суммарная стоимость: f = g + h
    float f() const { return g + h; }
};

// Класс AStarPathfinder реализует алгоритм A* для поиска пути по лабиринту
class AStarPathfinder {
private:
    Maze& maze;

    // Направления движения: вверх, вниз, влево, вправо
    const int dx[4] = {0, 0, 1, -1};
    const int dy[4] = {1, -1, 0, 0};

    // Эвристическая функция — манхэттенское расстояние
    float heuristic(int x1, int y1, int x2, int y2);

public:
    AStarPathfinder(Maze& m);
    void findPath(int startX, int startY, int goalX, int goalY); // поиск пути и анимация
};

#endif
