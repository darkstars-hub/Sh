#ifndef SH_CIRCLE_H
#define SH_CIRCLE_H

#include <cmath>

#include "Vector2.h"

namespace sh {
class Circle {
public:
    float radius_, x_, y_;
    Circle()
        : radius_(0),
        x_(0),
        y_(0) {
    }
    Circle(float radius, float x, float y)
        : radius_(radius),
        x_(x),
        y_(y) {
    }
    Circle operator+(const sh::Vector2 vector) {
        return Circle(
            this->radius_,
            this->x_ + vector.x_,
            this->y_ + vector.y_);
    }
    Circle& operator+=(const sh::Vector2 vector) {
        this->x_ += vector.x_;
        this->y_ += vector.y_;
        return *this;
    }

    bool CollisionCircle(const Circle& circle) {
        return
            std::pow(this->x_ - circle.x_, 2.0) +
            std::pow(this->y_ - circle.y_, 2.0) <=
            std::pow(this->radius_ + circle.radius_, 2.0);
    }
    void Translate(const float x, const float y) {
        this->x_ += x;
        this->y_ += y;
    }
    void Translate(const sh::Vector2 vector) {
        this->x_ += vector.x_;
        this->y_ += vector.y_;
    }
};

}
#endif // !SH_CIRCLE_H