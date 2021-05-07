#ifndef SH_RECTANGLE_H
#define SH_RECTANGLE_H

#include <cmath>

#include "Vector2.h"
#include "Circle.h"
namespace sh {

class Rectangle {
public:
    float left_, top_, right_, bottom_;
    Rectangle()
        : left_(0),
        top_(0),
        right_(0),
        bottom_(0) {
    }
    //! constructor
    //! param : [in] left
    //! param : [in] top
    //! param : [in] right
    //! param : [in] bottom
    Rectangle(float left, float top, float right, float bottom)
        : left_(left),
        top_(top),
        right_(right),
        bottom_(bottom) {
    }
    Rectangle operator+(const sh::Vector2 vector) {
        return Rectangle(
            this->left_ + vector.x_,
            this->top_ + vector.y_,
            this->right_ + vector.x_,
            this->bottom_ + vector.y_);
    }
    Rectangle& operator+=(const sh::Vector2 vector) {
        this->left_ += vector.x_;
        this->top_ += vector.y_;
        this->right_ += vector.x_;
        this->bottom_ += vector.y_;
        return *this;
    }

    bool CollisionRectangle(const Rectangle& rectangle) {
        return
            (this->left_ < rectangle.right_) &&
            (rectangle.left_ < this->right_) &&
            (this->top_ < rectangle.bottom_) &&
            (rectangle.top_ < this->bottom_);
    }
    bool CollisionCircle(const Circle& circle) {
        float d;
        if (this->left_ <= circle.x_ && circle.x_ <= this->right_ &&
            this->top_ <= circle.y_ && circle.y_ <= this->bottom_) {
            return true;
        } // if

        if (std::abs(circle.x_ - this->left_) <= circle.radius_) {
            d = std::sqrtf(circle.radius_ * circle.radius_ -
                ((circle.x_ - this->left_) * (circle.x_ - this->left_)));
            if ((this->top_ <= circle.y_ + d && circle.y_ + d <= this->bottom_) || (this->top_ <= circle.y_ - d && circle.y_ - d <= this->bottom_)) {
                return true;
            } // if
        } // if
        if (std::abs(circle.x_ - this->right_) <= circle.radius_) {
            d = std::sqrtf(circle.radius_ * circle.radius_ -
                ((circle.x_ - this->right_) * (circle.x_ - this->right_)));
            if ((this->top_ <= circle.y_ + d && circle.y_ + d <= this->bottom_) || (this->top_ <= circle.y_ - d && circle.y_ - d <= this->bottom_)) {
                return true;
            } // if
        } // if
        if (std::abs(circle.y_ - this->top_) <= circle.radius_) {
            d = std::sqrtf(circle.radius_ * circle.radius_ -
                ((circle.y_ - this->top_) * (circle.y_ - this->top_)));
            if ((this->left_ <= circle.x_ + d && circle.x_ + d <= this->right_) || (this->left_ <= circle.x_ - d && circle.x_ - d <= this->right_)) {
                return true;
            } // if
        } // if
        if (std::abs(circle.y_ - this->bottom_) <= circle.radius_) {
            d = std::sqrtf(circle.radius_ * circle.radius_ -
                ((circle.y_ - this->bottom_) * (circle.y_ - this->bottom_)));
            if ((this->left_ <= circle.x_ + d && circle.x_ + d <= this->right_) || (this->left_ <= circle.x_ - d && circle.x_ - d <= this->right_)) {
                return true;
            } // if
        } // if
        return false;
    }
    void Translate(const float x, const float y) {
        this->left_ += x;
        this->top_ += y;
        this->right_ += x;
        this->bottom_ += y;
    }
    void Translate(const sh::Vector2 vector) {
        this->Translate(vector.x_, vector.y_);
    }
    void SetBound(const float left, const float top, const float right, const float bottom) {
        this->left_ = left;
        this->top_ = top;
        this->right_ = right;
        this->bottom_ = bottom;
    }
    float GetWidth(void) const {
        return this->right_ - this->left_;
    }
    float GetHeight(void) const {
        return this->bottom_ - this->top_;
    }
    void Expansion(const float value) {
        this->left_ -= value;
        this->top_ -= value;
        this->right_ += value;
        this->bottom_ += value;
    }
};
}
#endif // !SH_RECTANGLE_H
