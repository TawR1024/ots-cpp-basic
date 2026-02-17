#include "Ball.hpp"

#include <cmath>

Ball::Ball (const Velocity velocity, const Point center, double radius, const Color color)
{
    this->velocity = velocity;
    this->center   = center;
    this->radius   = radius;
    this->color    = color;
}
/**
 * Задает скорость объекта
 * @param velocity новое значение скорости
 */
void Ball::setVelocity (const Velocity& velocity) { this->velocity = velocity; }

/**
 * @return скорость объекта
 */
Velocity Ball::getVelocity () const { return this->velocity; }

/**
 * @brief Выполняет отрисовку объекта
 * @details объект Ball абстрагирован от конкретного
 * способа отображения пикселей на экране. Он "знаком"
 * лишь с интерфейсом, который предоставляет Painter
 * Рисование выполняется путем вызова painter.draw(...)
 * @param painter контекст отрисовки
 */
void Ball::draw (Painter& painter) const { painter.draw (this->center, this->radius, this->color); }

/**
 * Задает координаты центра объекта
 * @param center новый центр объекта
 */
void Ball::setCenter (const Point& center) { this->center = center; }

/**
 * @return центр объекта
 */
Point Ball::getCenter () const { return this->center; }

/**
 * @brief Возвращает радиус объекта
 * @details обратите внимание, что метод setRadius()
 * не требуется
 */
double Ball::getRadius () const { return this->radius; }

/**
 * @brief Возвращает массу объекта
 * @details В нашем приложении считаем, что все шары
 * состоят из одинакового материала с фиксированной
 * плотностью. В этом случае масса в условных единицах
 * эквивалентна объему: PI * radius^3 * 4. / 3.
 */
double Ball::getMass () const { return std::pow (this->radius, 3) * M_PI * 4 / 3; }
