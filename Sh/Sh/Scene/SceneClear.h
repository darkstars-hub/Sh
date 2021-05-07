//!---------------------------------------------------------
//! @file SceneClear.h
//! @brief ゲームのクリアシーン
//! @author name
//! @date 2019/10/30
//!---------------------------------------------------------


#ifndef SH_SCENE_CLEAR_H
//!---------------------------------------------------------
//! @def SH_SCENE_CLEAR_H
//! @brief include gurad
//!---------------------------------------------------------
#define SH_SCENE_CLEAR_H


#include "Scene.h"

#include "ResourceManager.h"
#include "Score.h"

namespace sh {
class SceneClear final : public sh::Scene {
    using super = sh::Scene;
public:
    SceneClear(int score);
    virtual ~SceneClear();
    SceneClear(const SceneClear& rhs) = delete;
    SceneClear& operator=(const SceneClear& rhs) = delete;
    SceneClear(SceneClear&& rhs) = delete;
    SceneClear& operator= (SceneClear&& rhs) = delete;

    virtual sh::SCENE_NO GetSceneNo(void) const noexcept override;

    virtual bool Initialize(void) override;
    virtual bool Update(void) override;
    virtual bool Render(void) override;

    virtual void AcquireResource(sh::ResourceManager& container)override;
    virtual void SetScore(std::unique_ptr<sh::Score> score) override;
private:
    sh::ResourceManager* resource_manager_;
    std::unique_ptr<sh::Score> score_;
    int score_value_;
};
}
#endif SH_SCENE_CLEAR_H