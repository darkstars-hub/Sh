//!---------------------------------------------------------
//! @file SceneGame.h
//! @brief 実際のゲームシーン
//! ステージやアクターが作られて動く
//! stage => player => enemy => collision
//! @author name
//! @date 2019/10/30
//!---------------------------------------------------------


#ifndef SH_SCENE_GAME_H
//!---------------------------------------------------------
//! @def SH_SCENE_GAME_H
//! @brief include gurad
//!---------------------------------------------------------
#define SH_SCENE_GAME_H

#include "Scene.h"

//#include <fstream>
#include <vector>
#include <deque>
#include <array>
#include <memory>

#include "GameStart.h"
#include "ResourceManager.h"
#include "SoundManager.h"
#include "EffectManager.h"
#include "BulletManager.h"
#include "Stage.h"
#include "Player.h"
#include "EventListener.h"
#include "Score.h"
/*
#include "GameLogo.h"
*/
#include "EventMessenger.h"


namespace sh {
class SceneGame : public sh::Scene {
    using super = sh::Scene;
public:
    //SceneGame();
    SceneGame(sh::GameStart select);
    virtual ~SceneGame();
    SceneGame(const SceneGame& rhs) = delete;
    SceneGame& operator=(const SceneGame& rhs) = delete;
    SceneGame(SceneGame&& rhs) = delete;
    SceneGame& operator= (SceneGame&& rhs) = delete;

    virtual sh::SCENE_NO GetSceneNo(void) const noexcept override;

    virtual bool Initialize(void) override;
    virtual bool Update(void) override;
    virtual bool Render(void) override;
    virtual bool Release(void) override;
    virtual void AcquireResource(sh::ResourceManager& container)override;
    virtual std::unique_ptr<sh::Score> GetScore(void);
private:
    std::unique_ptr<sh::Stage> stage_;
    
    sh::ResourceManager* resource_manager_;
    sh::SoundManager sound_manager_;
    sh::EffectManager effect_manager_;
    sh::BulletManager bullet_manager_;
    
    //! 処理内でキャストしたい
    std::shared_ptr<sh::Player> player_;

    static const int enemy_count_ = 20;
    std::array<sh::Enemy*, enemy_count_> enemys_;

    std::unique_ptr< sh::Score> score_;
    /*
    sh::GameLogo logo_; 
    */
    sh::EventListener* listener_;

    void GameEnd(void);
    bool game_effect_show_;
    int game_effect_count_;
    int game_effect_count_max_;
    int select_stage_;
};
}
#endif SH_SCENE_GAME_H