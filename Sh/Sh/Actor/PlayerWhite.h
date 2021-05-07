//!---------------------------------------------------------
//! @file PlayerWhite.h
//! @brief プレイヤーのクラス
//! @author name
//! @date 2019/01/10
//!---------------------------------------------------------


#ifndef SH_PLAYER_WHITE_H
#define SH_PLAYER_WHITE_H

#include "Player.h"

namespace sh {
class PlayerWhite final : public sh::Player {
    using super = sh::Player;
public:
    PlayerWhite() = default;
    PlayerWhite(int type);
    virtual ~PlayerWhite();
    PlayerWhite(const PlayerWhite& rhs) = delete;
    PlayerWhite& operator=(const PlayerWhite& rhs) = delete;
    PlayerWhite(PlayerWhite&& rhs) = delete;
    PlayerWhite& operator= (PlayerWhite&& rhs) = delete;

    virtual bool Initialize(void)override;
protected:
};
}
#endif // !SH_PLAYER_WHITE_H