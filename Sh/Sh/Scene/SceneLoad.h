//!---------------------------------------------------------
//! @file SceneLoad.h
//! @brief ì«Ç›çûÇ›ÉVÅ[Éì
//! @author name
//! @date 2019/01/15
//!---------------------------------------------------------


#ifndef SH_SCENE_LOAD_H
//!---------------------------------------------------------
//! @def SH_SCENE_LOAD_H
//! @brief include gurad
//!---------------------------------------------------------
#define SH_SCENE_LOAD_H

#include "Scene.h"

/*
#include <thread>
#define GLFW_EXPOSE_NATIVE_WIN32
#include "GLFW/glfw3native.h"
*/

#include <future>

#include "GameStart.h"
#include "Texture.h"
#include "Graphics.h"
#include "Animation.h"
#include "ResourceManager.h"

namespace sh {
class SceneLoad final : public sh::Scene {
    using super = sh::Scene;
public:
    SceneLoad() = default;
    SceneLoad(sh::GameStart select);
    virtual ~SceneLoad();
    SceneLoad(const SceneLoad& rhs) = delete;
    SceneLoad& operator=(const SceneLoad& rhs) = delete;
    SceneLoad(SceneLoad&& rhs) = delete;
    SceneLoad& operator= (SceneLoad&& rhs) = delete;

    virtual sh::SCENE_NO GetSceneNo(void) const noexcept override;

    virtual bool Initialize(void) override;
    virtual bool Update(void) override;
    virtual bool Render(void) override;
    virtual bool Release(void) override;
    
    virtual void AcquireResource(
        sh::ResourceManager& container)override;
private:
    bool loaded_;
    int player_select_;
    sh::Texture load_texture_;
    sh::Animation animation_;

    sh::ResourceManager*
        resource_manager_;

    std::thread load_thread_;

    //void WarpFunc(std::promise<int> p);
};
}
#endif SH_SCENE_LOAD_H