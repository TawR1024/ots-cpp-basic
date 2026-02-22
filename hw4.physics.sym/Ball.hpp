#pragma once
#include "Painter.hpp"
#include "Point.hpp"
#include "Velocity.hpp"
#include "Color.hpp"

class Ball {
private:
    Velocity velocity;
    Point center;
    double radius;
    Color color;
    bool collidable;
    double mass; 
public:
    Ball() = default;
    Ball(const Velocity velocity, const Point center, double radius, const Color color, bool isCollidable);
    void setVelocity(const Velocity& velocity);
    Velocity getVelocity() const;
    void draw(Painter& painter) const;
    void setCenter(const Point& center);
    Point getCenter() const;
    double getRadius() const;
    double getMass() const;
    bool isCollidable() const;
};

inline std::istream& operator>>(std::istream& stream, Ball& ball) {
    Point center;
    double vx, vy;
    double radius;
    Color color;
    bool isCollidable;

    
    if (!(stream >> center)) return stream;

    
    if (!(stream >> vx >> vy)) return stream;

    
    if (!(stream >> color)) return stream;

   
    if (!(stream >> radius)) return stream;

   
    if (!(stream >> std::boolalpha >> isCollidable)) return stream;

    
    Velocity velocity(Point(vx, vy)); 
   
    ball = Ball(velocity, center, radius, color, isCollidable);

    return stream;
}