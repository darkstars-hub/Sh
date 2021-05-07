//!---------------------------------------------------------
//! @file Player.h
//! @brief プレイヤーのクラス
//!        いろんなプレイヤーの継承元
//! @author name
//! @date 2019/11/06
//!---------------------------------------------------------


#ifndef SH_PLAYER_H
#define SH_PLAYER_H

#include <vector>

#include "Actor.h"
#include "Helper.h"
#include "Graphics.h"
#include "Texture.h"
#include "Animation.h"
#include "Weapon.h"
#include "ActorState.h"

namespace sh {
class Player : public sh::Actor {
    using super = sh::Actor;
public:
    Player();
    virtual ~Player();
    Player(const Player& rhs) = delete;
    Player& operator=(const Player& rhs) = delete;
    Player(Player&& rhs) = delete;
    Player& operator= (Player&& rhs) = delete;

    virtual int GetPlayerType(void) const noexcept;
    virtual sh::Rectangle GetRectangle(void) const noexcept;

    virtual bool Initialize(void)override;
    virtual bool Update(void) override;
    virtual bool Render(void) override;
    virtual bool Release(void) override;

    virtual void Damage(const int damage_value)override;
    virtual void AcquireTexture(sh::ResourceManager& container)  override;
    virtual bool IsEquipmentBarrier(void);
protected:
    std::weak_ptr<sh::Texture> texture_;
    std::weak_ptr<sh::Texture> core_;
    
    sh::Animation               animation_;
    //!被弾した場合一定時間攻撃を受け付けない
    const int                   damage_interval_max_;
    int                         damage_interval_;
    sh::ActorState status_;
    float mp_coefficient_;
    int player_type_;
    virtual void UseWeapon(std::shared_ptr <sh::Weapon> weapon);
};
}
#endif // !SH_PLAYER_H