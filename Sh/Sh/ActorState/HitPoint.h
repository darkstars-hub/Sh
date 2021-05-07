//!---------------------------------------------------------
//! @file HitPoint.h
//! @brief PlayerÇ‚EnemyÇ™éùÇ¬
//! @author name
//! @date 2019/11/03
//!---------------------------------------------------------

#ifndef SH_HIT_POINT_H
#define SH_HIT_POINT_H

#include <memory>

#include "Texture.h"
#include "Animation.h"

namespace sh {
class HitPoint {
public:
    HitPoint();
    ~HitPoint();
    HitPoint(const HitPoint& rhs) = delete;
    HitPoint(HitPoint&& rhs) = delete;

    void SetTexture(const std::shared_ptr<sh::Texture> texture);

    bool Initialize(int init_value);
    bool Update(void);
    bool Render(float x, float y) const;

    int GetValue(void) const noexcept;
    bool Damage(const int damage_value);
private:
    int value_;
    std::weak_ptr<sh::Texture> texture_;
    std::unique_ptr<sh::Animation> animation_;

    void MakeAnimation(void);
};
}
#endif // !SH_HIT_POINT_H