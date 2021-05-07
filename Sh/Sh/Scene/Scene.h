//!---------------------------------------------------------
//! @file Scene.h
//! @brief 各シーンクラスの基底クラス
//! @author name
//! @date 2019/10/30
//!---------------------------------------------------------

#ifndef SH_SCENE_H
//!---------------------------------------------------------
//! @def SH_SCENE_H
//! @brief include gurad
//!---------------------------------------------------------
#define SH_SCENE_H

#include <iostream>
#include <memory>

#include "Helper.h"
#include "Rectangle.h"
#include "Graphics.h"
#include "Texture.h"
#include "SoundBuffer.h"
#include "ResourceManager.h"
#include "SystemSound.h"
#include "Score.h"


namespace sh {
enum class SCENE_NO {
    NONE,
    TITLE,
    SELECT,
    LOAD,
    GAME,
    CLEAR,
    OVER,
    RESULT,
    SCENE_COUNT
};
class Scene {
public:
    Scene();
    //Scene(sh::GameStart select);
    virtual ~Scene();
    Scene(const Scene& rhs) = default;
    Scene& operator=(const Scene& rhs) = default;
    Scene(Scene&& rhs) = default;
    Scene& operator= (Scene&& rhs) = default;

    bool IsEnd(void) const noexcept;
    SCENE_NO GetNextScene(void) const noexcept;
    virtual SCENE_NO GetSceneNo(void) const noexcept = 0;

    virtual bool Initialize(void) = 0;
    virtual bool Update(void) = 0;
    virtual bool Render(void) = 0;
    virtual bool Release(void);

    virtual void AcquireResource(sh::ResourceManager& container);
    virtual void ChangeSceneFade(const SCENE_NO next_scene);
    virtual void RenderFade(void);
    virtual void Fade(void);
    virtual void ChangeScene(const SCENE_NO next_scene);
    
    virtual void SetScore(std::unique_ptr<sh::Score> score);
    virtual std::unique_ptr<sh::Score> GetScore(void);
protected:
    bool is_end_;
    SCENE_NO next_scene_;
    std::shared_ptr<sh::Texture> texture_;
    std::shared_ptr<sh::SoundBuffer> sound_;

    int alpha_;
    bool is_change_;
};
}
#endif // !SH_SCENE_H