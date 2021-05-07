//!---------------------------------------------------------
//! @file ActorState.h
//! @brief Actorが持つ値もまとめたもの
//!        インナークラスや構造体でもいいかも
//! @author name
//! @date 2019/11/06
//!---------------------------------------------------------


#ifndef SH_ACTOR_STATE_H
#define SH_ACTOR_STATE_H


#include <memory>
#include <vector>
#include <array>

#include "Actor.h"
#include "Motion.h"
#include "Weapon.h"
#include "NormalGun.h"
#include "ThreeWayGun.h"
#include "CircleGun.h"
#include "RandomGun.h"
#include "Mine.h"
#include "HitPoint.h"
#include "WeaponEnergy.h"


namespace sh {
class ActorState {
public:
    ActorState();


    std::shared_ptr<sh::Weapon> GetWeapon(int botton);
    sh::Motion* GetMotion(void);
    std::shared_ptr<sh::HitPoint> GetHp(void);
    std::shared_ptr<sh::WeaponEnergy> GetMp(void);

    void AddUser(sh::Actor& user);
    void MakeWeapons(
        const WeaponType a,
        const WeaponType b,
        const WeaponType x,
        const WeaponType y);

    void Load(sh::ResourceManager& container);
    void Initialize(int hp);
    void Update(void);
    void Render(void);
private:
    sh::Motion motion_;
    std::array<std::shared_ptr<sh::Weapon>, 4> weapons_;
    std::shared_ptr<sh::HitPoint> hp_;
    std::shared_ptr<sh::WeaponEnergy> mp_;
};
}
#endif // !SH_ACTOR_STATE_H