//!---------------------------------------------------------
//! @file PlayerBlue.h
//! @brief プレイヤーのクラス
//! @author name
//! @date 2019/01/10
//!---------------------------------------------------------


#ifndef SH_PLAYER_BLUE_H
#define SH_PLAYER_BLUE_H

#include <vector>

#include "Player.h"

namespace sh {
class PlayerBlue final : public sh::Player {
    using super = sh::Player;
public:
    PlayerBlue(int type);
    virtual ~PlayerBlue();
    PlayerBlue(const PlayerBlue& rhs) = delete;
    PlayerBlue& operator=(const PlayerBlue& rhs) = delete;
    PlayerBlue(PlayerBlue&& rhs) = delete;
    PlayerBlue& operator= (PlayerBlue&& rhs) = delete;

    virtual bool Initialize(void)override;
    virtual bool Update(void)override;
};
}
#endif // !SH_PLAYER_BLUE_H