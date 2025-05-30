#include "Maze.h"
#include <stack>
#include <algorithm>
#include <random>

// Конструктор: инициализирует сетку лабиринта символами '#' и массив visited значениями false
Maze::Maze() {
    grid = std::vector<std::vector<char>>(HEIGHT, std::vector<char>(WIDTH, '#'));
    visited = std::vector<std::vector<bool>>(HEIGHT, std::vector<bool>(WIDTH, false));
}

// Проверка, что координаты (x, y) находятся в пределах границ лабиринта
bool Maze::isInBounds(int x, int y) const {
    return x >= 0 && x < HEIGHT && y >= 0 && y < WIDTH;
}

// Генерация лабиринта методом DFS с возвратом
void Maze::generate(int startX, int startY) {
    std::stack<std::pair<int, int>> stack;
    stack.push({startX, startY});
    visited[startX][startY] = true;
    grid[startX][startY] = ' '; // Начальная клетка — проход

    std::random_device rd;
    std::mt19937 g(rd()); // генератор случайных чисел

    while (!stack.empty()) {
        auto [x, y] = stack.top();
        std::vector<int> dirs = {0, 1, 2, 3};
        std::shuffle(dirs.begin(), dirs.end(), g); // случайный порядок направлений

        bool moved = false;
        for (int i : dirs) {
            int nx = x + dx[i]; // новое направление
            int ny = y + dy[i];

            if (isInBounds(nx, ny) && !visited[nx][ny]) {
                // отмечаем новую клетку как посещённую
                visited[nx][ny] = true;
                grid[nx][ny] = ' ';

                // удаляем стену между текущей и новой клеткой
                grid[x + dx[i] / 2][y + dy[i] / 2] = ' ';

                // продолжаем путь
                stack.push({nx, ny});
                moved = true;
                break;
            }
        }

        // если некуда идти — откатываемся назад
        if (!moved) stack.pop();
    }
}

// Проверка, можно ли пройти по заданной клетке (т.е. она не стена)
bool Maze::isWalkable(int x, int y) const {
    return isInBounds(x, y) && grid[x][y] == ' ';
}

// Отметить путь на карте (для анимации и отрисовки)
void Maze::markPath(int x, int y) {
    grid[x][y] = '0'; // путь обозначается нулём
}

// Отображение лабиринта в терминал
void Maze::print() const {
    for (const auto& row : grid) {
        for (char c : row)
            std::cout << c;
        std::cout << '\n';
    }
}
