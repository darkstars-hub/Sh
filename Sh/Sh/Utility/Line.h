#ifndef SH_LINE_H
#define SH_LINE_H

#include "Vector2.h"

namespace sh {

inline bool LineCollision(const Vector2 L1s, const Vector2 L1e,
                          const Vector2 L2s, const Vector2 L2e, Vector2* pt) {
    auto ta = (L2s.x_ - L2e.x_) * (L1s.y_ - L2s.y_) + (L2s.y_ - L2e.y_) * (L2s.x_ - L1s.x_);
    auto tb = (L2s.x_ - L2e.x_) * (L1e.y_ - L2s.y_) + (L2s.y_ - L2e.y_) * (L2s.x_ - L1e.x_);
    auto tc = (L1s.x_ - L1e.x_) * (L2s.y_ - L1s.y_) + (L1s.y_ - L1e.y_) * (L1s.x_ - L2s.x_);
    auto td = (L1s.x_ - L1e.x_) * (L2e.y_ - L1s.y_) + (L1s.y_ - L1e.y_) * (L1s.x_ - L2e.x_);

    auto v1 = Vector2(L1s.x_ - L2s.x_, L1s.y_ - L2s.y_);
    auto vA = Vector2(L1e.x_ - L1s.x_, L1e.y_ - L1s.y_);
    auto vB = Vector2(L2e.x_ - L2s.x_, L2e.y_ - L2s.y_);
    if (tc * td <= 0 && ta * tb <= 0) {
        auto fDeno = vA.x_ * vB.y_ - vA.y_ * vB.x_;
        auto t = (v1.y_ * vB.x_ - v1.x_ * vB.y_) / fDeno;

        pt->x_ = vA.x_ * t + L1s.x_;
        pt->y_ = vA.y_ * t + L1s.y_;

        return true;
    } // if
    return false;
}

class Line {
public:
    float start_x_, start_y_, end_x_, end_y_;
    Line()
        : start_x_(0),
        start_y_(0),
        end_x_(0),
        end_y_(0) {
    }
    Line(float start_x, float start_y, float end_x, float end_y)
        : start_x_(start_x),
        start_y_(start_y),
        end_x_(end_x),
        end_y_(end_y) {
    }
};

}
#endif // !SH_LINE_H
