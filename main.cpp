#include <cstdlib>
#include <ctime>
#include "Maze.h"
#include "AStarPathfinder.h"

int main() {
      // Инициализация генератора случайных чисел текущим временем
    // Это нужно для получения разных лабиринтов при каждом запуске
    srand(static_cast<unsigned>(time(0)));

    // Создание лабиринта и его генерация от стартовой позиции (1, 1)
    Maze maze;
    maze.generate(1, 1);

    // Создание объекта поиска пути и запуск поиска от (1,1) до (HEIGHT-2, WIDTH-2)
    // Это почти правый нижний угол, но на 1 клетку отступаем, чтобы не упереться в границу
    AStarPathfinder pathfinder(maze);
    pathfinder.findPath(1, 1, HEIGHT - 2, WIDTH - 2);

    // Повторный вывод лабиринта после завершения анимации
    // (финальное состояние с нарисованным маршрутом)
    maze.print();
    return 0;
}
