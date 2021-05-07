//!---------------------------------------------------------
//! @file PlayerPurple.h
//! @brief プレイヤーのクラス
//! @author name
//! @date 2019/01/10
//!---------------------------------------------------------


#ifndef SH_PLAYER_PURPLE_H
#define SH_PLAYER_PURPLE_H

#include "Player.h"

#include "Circle.h"

namespace sh {
class PlayerPurple final : public sh::Player {
    using super = sh::Player;
public:
    PlayerPurple(int type);
    virtual ~PlayerPurple();
    PlayerPurple(const PlayerPurple& rhs) = delete;
    PlayerPurple& operator=(const PlayerPurple& rhs) = delete;
    PlayerPurple(PlayerPurple&& rhs) = delete;
    PlayerPurple& operator= (PlayerPurple&& rhs) = delete;

    sh::Circle GetBarrierCircle(void);
    virtual bool IsEquipmentBarrier(void) override;

    virtual bool Initialize(void)override;
    virtual bool Update(void) override;

    void BarrierRender(void);
private:
    sh::Texture barrier_texture_;
    bool use_barrier_;
};
}
#endif // !SH_PLAYER_PURPLE_H