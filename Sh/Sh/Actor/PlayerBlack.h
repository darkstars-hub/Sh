//!---------------------------------------------------------
//! @file PlayerBlack.h
//! @brief プレイヤーのクラス
//! @author name
//! @date 2019/01/10
//!---------------------------------------------------------


#ifndef SH_PLAYER_BLACK_H
#define SH_PLAYER_BLACK_H

#include "Player.h"

namespace sh {
class PlayerBlack final : public sh::Player {
    using super = sh::Player;
public:
    PlayerBlack() = default;
    PlayerBlack(int type);
    virtual ~PlayerBlack();
    PlayerBlack(const PlayerBlack& rhs) = delete;
    PlayerBlack& operator=(const PlayerBlack& rhs) = delete;
    PlayerBlack(PlayerBlack&& rhs) = delete;
    PlayerBlack& operator= (PlayerBlack&& rhs) = delete;

    virtual bool Initialize(void)override;
protected:
};
}
#endif // !SH_PLAYER_BLACK_H