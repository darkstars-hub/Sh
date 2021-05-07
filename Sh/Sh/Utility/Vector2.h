#ifndef SH_VECTOR2_H
#define SH_VECTOR2_H
namespace sh {
class Vector2 {
public:
    float x_, y_;
    Vector2()
        : x_(0),
        y_(0) {
    }
    Vector2(float x, float y)
        : x_(x),
        y_(y) {
    }

    Vector2(const Vector2& vector)= default;
    sh::Vector2& operator =(const sh::Vector2& vector)=default;

    /*
    Vector2(const Vector2& vector)
        : x_(vector.x_),
        y_(vector.y_) {
    }

    sh::Vector2& operator =(const sh::Vector2& vector) {
        this->x_ = vector.x_;
        this->y_ = vector.y_;
        return *this;
    }
    */
    bool operator ==(const sh::Vector2& vector) const {
        return this->x_ == vector.x_ &&
            this->y_ == vector.y_;
    }
    bool operator !=(const sh::Vector2& vector) const {
        return this->x_ != vector.x_ ||
            this->y_ != vector.y_;
    }

    void Zero() {
        this->x_ = 0.0f;
        this->y_ = 0.0f;
    }
    sh::Vector2 operator-() const {
        return sh::Vector2(-this->x_, -this->y_);
    }

    sh::Vector2 operator +(const sh::Vector2& vector) const {
        return sh::Vector2(this->x_ + vector.x_, this->y_ + vector.y_);
    }
    sh::Vector2 operator -(const sh::Vector2& vector) const {
        return sh::Vector2(this->x_ - vector.x_, this->y_ - vector.y_);
    }
    sh::Vector2& operator+=(const sh::Vector2& vector) {
        this->x_ += vector.x_;
        this->y_ += vector.y_;
        return *this;
    }
    sh::Vector2& operator-=(const sh::Vector2& vector) {
        this->x_ -= vector.x_;
        this->y_ -= vector.y_;
        return *this;
    }
};

}
#endif // !SH_VECTOR2_H
