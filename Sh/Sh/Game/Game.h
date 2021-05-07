//!---------------------------------------------------------
//! @file Game.h
//! @brief ÉQÅ[ÉÄïîï™ Application::Run(void)ÇÃíÜÇ≈é¿çsÇ≥ÇÍÇÈ
//! @author name
//! @date 2019/10/30
//!---------------------------------------------------------


#ifndef SH_GAME_H
//!---------------------------------------------------------
//! @def SH_GAME_H
//! @brief include gurad
//!---------------------------------------------------------
#define SH_GAME_H

#include <memory>

#include "Helper.h"
#include "GamePad.h"
#include "Camera.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "GameStart.h"

namespace sh {
class Game {
public:
    Game();
    ~Game();
    Game(const Game& rhs) = delete;
    Game& operator=(const Game& rhs) = delete;
    Game(Game&& rhs) = delete;
    Game& operator= (Game&& rhs) = delete;

    bool IsEnd(void) const noexcept;
    void End(void);

    bool Initialize(void);
    bool Update(void);
    bool Render(void);
    bool Release(void);

    std::shared_ptr<sh::Camera> GetCamera(void) const;
private:
    bool is_end_;
    std::shared_ptr<sh::Camera> camera_;
    std::unique_ptr<sh::Scene> scene_;
   //sh::Scene* scene_;
    sh::GameStart selected_numbers_;
    std::shared_ptr<sh::ResourceManager> r;
};
}
#endif // !SH_GAME_H