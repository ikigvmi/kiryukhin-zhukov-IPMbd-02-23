#include "AStarPathfinder.h"
#include <queue>
#include <map>
#include <cmath>
#include <thread>
#include <chrono>
#include <iostream>

// Конструктор принимает ссылку на лабиринт
AStarPathfinder::AStarPathfinder(Maze& m) : maze(m) {}

// Манхэттенское расстояние как эвристика
float AStarPathfinder::heuristic(int x1, int y1, int x2, int y2) {
    return std::abs(x1 - x2) + std::abs(y1 - y2);
}

// Алгоритм A*: находит путь и визуализирует его
void AStarPathfinder::findPath(int startX, int startY, int goalX, int goalY) {
    // Компаратор для приоритетной очереди — выбирает узел с наименьшим f()
    auto cmp = [](Node* a, Node* b) { return a->f() > b->f(); };
    std::priority_queue<Node*, std::vector<Node*>, decltype(cmp)> openList(cmp);

    // Храним указатели на все созданные узлы (чтобы потом удалить)
    std::map<std::pair<int, int>, Node*> allNodes;

    // Стартовый узел
    Node* start = new Node{startX, startY, 0, heuristic(startX, startY, goalX, goalY), nullptr};
    openList.push(start);
    allNodes[{startX, startY}] = start;

    // Основной цикл A*
    while (!openList.empty()) {
        Node* current = openList.top();
        openList.pop();

        // Если достигли цели — строим путь и анимируем
        if (current->x == goalX && current->y == goalY) {
            while (current) {
                maze.markPath(current->x, current->y); // отмечаем путь

                // Очищаем экран и рисуем лабиринт
                std::cout << "\x1B[2J\x1B[H"; // ANSI очистка экрана
                maze.print();

                std::this_thread::sleep_for(std::chrono::milliseconds(100)); // задержка
                current = current->parent; // идем к предыдущему узлу
            }
            break;
        }

        // Проверка соседей (в 4 направлениях)
        for (int i = 0; i < 4; ++i) {
            int nx = current->x + dx[i];
            int ny = current->y + dy[i];

            if (!maze.isWalkable(nx, ny)) continue; // игнорируем стены

            float newG = current->g + 1;
            auto key = std::make_pair(nx, ny);

            // Если узел ещё не был создан или найден более короткий путь
            if (allNodes.find(key) == allNodes.end() || newG < allNodes[key]->g) {
                Node* neighbor = new Node{nx, ny, newG, heuristic(nx, ny, goalX, goalY), current};
                allNodes[key] = neighbor;
                openList.push(neighbor);
            }
        }
    }

    // Очистка всех узлов из памяти
    for (auto& pair : allNodes)
        delete pair.second;
}
