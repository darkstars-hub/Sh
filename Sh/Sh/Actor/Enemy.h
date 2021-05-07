//!---------------------------------------------------------
//! @file Enemy.h
//! @brief エネミーのクラス
//!        いろんなエネミーの継承元
//! @author name
//! @date 2019/11/06
//!---------------------------------------------------------


#ifndef SH_ENEMY_H
#define SH_ENEMY_H

#include <vector>

#include "Actor.h"
#include "Helper.h"
#include "Graphics.h"
#include "Texture.h"
#include "Animation.h"
#include "Weapon.h"
#include "ActorState.h"


namespace sh {
enum class EnemyType {
    NONE,
    CROWN,
    PURPLE_HAT,
    BLUE_HAT,
    YELLOW_HAT,
    BLACK_HAT,
    SKELETON,
    COUNT_MAX
};
class Enemy : public sh::Actor {
    using super = sh::Actor;
public:
    Enemy();
    virtual ~Enemy();
    Enemy(const Enemy& rhs) = delete;
    Enemy& operator=(const Enemy& rhs) = delete;
    Enemy(Enemy&& rhs) = delete;
    Enemy& operator= (Enemy&& rhs) = delete;

    virtual void SetShow(const bool b);
    virtual void SetTexture(std::shared_ptr<sh::Texture> texture);
    virtual sh::Rectangle GetRectangle(void) const noexcept;
    virtual sh::EnemyType GetEnemyType(void) const noexcept;

    virtual bool Initialize(void)override;
    virtual bool Update(void) override;
    virtual bool Render(void) override;
    virtual bool Release(void) override;

    virtual void Damage(const int damage_value)override;
    virtual void Start(const Vector2 position);

    //! 急ごしらえ
    virtual void SetUp(void);
protected:
    std::weak_ptr<sh::Texture> texture_;
    sh::Animation               animation_;
    sh::ActorState status_;
    float move_distance_;
    float exit_point_y_;
    sh::EnemyType enemy_type_;
    
    virtual void MemberUpdate(void);
    virtual void Move(void);
    virtual void Attack(void);
    virtual void Cliping(void);

    //! ボス用----------
    int move_count_ ;
    int attack_count_ ;
    struct DestPos {
        sh::Vector2 position;
        //bool is_set;
        DestPos* next;
    };
    std::array<DestPos,5> destinations_;
    DestPos current_position_;
    //! --------------
private:
    virtual void AcquireTexture(sh::ResourceManager& container)  override;
};
}
#endif // !SH_ENEMY_H