//!---------------------------------------------------------
//! @file SceneResult.h
//! @brief ゲームのリザルトシーン
//! @author name
//! @date 2019/10/30
//!---------------------------------------------------------


#ifndef SH_SCENE_RESULT_H
//!---------------------------------------------------------
//! @def SH_SCENE_RESULT_H
//! @brief include gurad
//!---------------------------------------------------------
#define SH_SCENE_RESULT_H

#include "Scene.h"


namespace sh {
class SceneResult : public sh::Scene {
    using super = sh::Scene;
public:
    SceneResult();
    virtual ~SceneResult();
    SceneResult(const SceneResult& rhs) = delete;
    SceneResult& operator=(const SceneResult& rhs) = delete;
    SceneResult(SceneResult&& rhs) = delete;
    SceneResult& operator= (SceneResult&& rhs) = delete;

    virtual sh::SCENE_NO GetSceneNo(void) const noexcept override;

    virtual bool Initialize(void) override;
    virtual bool Update(void) override;
    virtual bool Render(void) override;

    //virtual void AcquireResource(sh::ResourceManager& container)override {}

private:
};
}
#endif SH_SCENE_RESULT_H