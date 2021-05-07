//!---------------------------------------------------------
//! @file Weapon.h
//! @brief プレイヤーが持つ
//!        各武器の基底クラス
//! @author name
//! @date 2019/11/06
//!---------------------------------------------------------


#ifndef SH_WEAPON_H
#define SH_WEAPON_H

#include "Actor.h"
#include "Bullet.h"
#include "BulletFactory.h"
#include "EventListener.h"
#include "EventMessenger.h"

namespace sh {
enum class WeaponType {
    NONE,
    NORMAL_GUN,
    THREE_WAY_GUN,
    CIRCLE_GUN,
    RANDOM_GUN,
    MINE,
};
class Weapon {
public:
    Weapon();
    virtual ~Weapon();
    Weapon(const Weapon& rhs) = delete;
    Weapon& operator=(const Weapon& rhs) = delete;
    Weapon(Weapon&& rhs) = delete;
    Weapon& operator= (Weapon&& rhs) = delete;

    virtual void SetShotPower(const int value);
    virtual void SetShotIntervalMax(const int value);
    virtual void AddUser(Actor& user) final;
    virtual int GetCost(void) = 0;
    virtual sh::BulletType GetBulletType(void) const noexcept;

    virtual bool CanShot(void);
    virtual void AddWait(int value);
    virtual void ResetWait(void);
    virtual void AddBullet(int value);

    virtual void Update(void);
    virtual void Fire(void) = 0;
    virtual void ChangeBulletType(const BulletType type);
protected:
    Actor* user_;
    int shot_interval_ ;
    int shot_interval_max_;
    int cost_;
    Vector2 power_;
    sh::EventListener* listener_;
    // int bullet_count_
    sh::BulletType bullet_type_;
    int bullet_count_;

    virtual void SendSoundEvent(void);
    virtual void SendEvent(const sh::EventID id, const sh::Vector2 position, const float angle, const sh::Vector2 speed);
};
}
#endif // !SH_WEAPON_H