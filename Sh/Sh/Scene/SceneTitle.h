//!---------------------------------------------------------
//! @file SceneTitle.h
//! @brief ゲームのタイトルシーン
//! Gameのstd::unique_ptr<sh::Scene>の
//! インスタンスはこれで生成される
//! @author name
//! @date 2019/10/30
//!---------------------------------------------------------


#ifndef SH_SCENE_TITLE_H
//!---------------------------------------------------------
//! @def SH_SCENE_TITLE_H
//! @brief include gurad
//!---------------------------------------------------------
#define SH_SCENE_TITLE_H

#include "Scene.h"

namespace sh {
class SceneTitle : public sh::Scene {
    using super = sh::Scene;
public:
    SceneTitle();
    virtual ~SceneTitle();
    SceneTitle(const SceneTitle& rhs) = delete;
    SceneTitle& operator=(const SceneTitle& rhs) = delete;
    SceneTitle(SceneTitle&& rhs) = delete;
    SceneTitle& operator= (SceneTitle&& rhs) = delete;

    virtual sh::SCENE_NO GetSceneNo(void) const noexcept override;

    virtual bool Initialize(void) override;
    virtual bool Update(void) override;
    virtual bool Render(void) override;

    //virtual void AcquireResource(sh::ResourceManager& container)override {}
private:
    int signal_count_;
    const int signal_count_max_;
};
}
#endif SH_SCENE_TITLE_H