//!---------------------------------------------------------
//! @file SceneOver.h
//! @brief ゲームオーバーシーン
//! @author name
//! @date 2019/10/30
//!---------------------------------------------------------


#ifndef SH_SCENE_OVER_H
//!---------------------------------------------------------
//! @def SH_SCENE_OVER_H
//! @brief include gurad
//!---------------------------------------------------------
#define SH_SCENE_OVER_H

#include "Scene.h"

namespace sh {
class SceneOver : public sh::Scene {
    using super = sh::Scene;
public:
    SceneOver();
    virtual ~SceneOver();
    SceneOver(const SceneOver& rhs) = delete;
    SceneOver& operator=(const SceneOver& rhs) = delete;
    SceneOver(SceneOver&& rhs) = delete;
    SceneOver& operator= (SceneOver&& rhs) = delete;

    virtual sh::SCENE_NO GetSceneNo(void) const noexcept override;

    virtual bool Initialize(void) override;
    virtual bool Update(void) override;
    virtual bool Render(void) override;

    //virtual void AcquireResource(sh::ResourceManager& container)override {}

};
}
#endif SH_SCENE_OVER_H