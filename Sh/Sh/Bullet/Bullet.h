#ifndef SH_BULLET_H
#define SH_BULLET_H

#include <memory>

#include "Object.h"
#include "Helper.h"
#include "Vector2.h"
#include "Animation.h"
#include "Graphics.h"
#include "Texture.h"
#include "Actor.h"

namespace sh {
enum class BulletState {
    NONE,
    MOVE,
    HIT,
    COUNT
};
enum class BulletColor {
    RED,
    ORANGE,
    YELLOW,
    LIGHT_GREEN,
    GREEN,
    SKY_BLUE,
    BLUE,
    LIGHT_PURPLE,
    PURPLE,
    PINK,
    WHITE,
    BLACK,

    COUNT
};
enum class BulletType {
    Bullet,
    Bomb,
    Beam,
    BeamShooting,
    Homing,
    Through,
    Boomerang,
};
class Bullet : public sh::Object {
    using super = sh::Object;
public:
    Bullet();
    virtual ~Bullet();
    Bullet(const sh::Bullet& rhs) = default;
    Bullet& operator=(const sh::Bullet& rhs) = default;
    Bullet(Bullet&& rhs) = default;
    Bullet& operator= (Bullet&& rhs) = default;

    virtual void SetShow(const bool is_show);
    virtual void SetState(const BulletState state);
    virtual void SetTexture(std::shared_ptr<sh::Texture> texture);
    virtual sh::Rectangle  GetRectangle(void) const noexcept override;
    virtual int GetAttackValue(void) const noexcept;
    virtual sh::BulletType GetType(void) const noexcept;
    virtual BulletState GetState(void) const noexcept;

    virtual bool Initialize(void) override;
    virtual bool Update(void) override;
    virtual bool Render(void) override;
    virtual bool Release(void) override;

    virtual void Fire(const sh::Vector2  position, const float angle, const sh::Vector2  speed);
    //! BulletFactory‚ªŽg‚¤
    virtual bool MakeAnimation(sh::BulletColor color);
    virtual void Cliping(void);
protected:
    BulletState state_;
    sh::Vector2  speed_limit_;
    //std::weak_ptr<sh::Texture> texture_;
    std::shared_ptr<sh::Texture> texture_;
    sh::Animation current_animation_;
    sh::Animation move_animation_;
    sh::Animation hit_animation_;
    int attack_value_;
    sh::BulletType type_;
    float rect_offset_;
};
}
#endif // !SH_BULLET_H