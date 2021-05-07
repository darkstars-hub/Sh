//!---------------------------------------------------------
//! @file SceneSelect.h
//! @brief プレイヤー、ステージ選択シーン
//! @author name
//! @date 2019/10/30
//!---------------------------------------------------------


#ifndef SH_SCENE_SELECT_H
//!---------------------------------------------------------
//! @def SH_SCENE_SELECT_H
//! @brief include gurad
//!---------------------------------------------------------
#define SH_SCENE_SELECT_H

#include "Scene.h"

#include "GameStart.h"
#include "SelectCursor.h"
#include "CharaSelect.h"
#include "StageSelect.h"
#include "SelectLogo.h"

namespace sh {
class SceneSelect final : public sh::Scene {
    using super = sh::Scene;
public:
    SceneSelect();
    virtual ~SceneSelect();
    SceneSelect(const SceneSelect& rhs) = delete;
    SceneSelect& operator=(const SceneSelect& rhs) = delete;
    SceneSelect(SceneSelect&& rhs) = delete;
    SceneSelect& operator= (SceneSelect&& rhs) = delete;
    
    virtual sh::SCENE_NO GetSceneNo(void) const noexcept override;

    sh::GameStart GetSelectNumber(void);

    virtual bool Initialize(void) override;
    virtual bool Update(void) override;
    virtual bool Render(void) override;
    virtual bool Release(void) override;

    //virtual void AcquireResource(sh::ResourceManager& container)override {}
private:
    sh::SelectCursor select_corsor_;
    sh::SelectLogo select_logo_;
    sh::CharaSelect chara_select_;
    sh::StageSelect stage_select_;

    int chara_number_;
    int stage_number_;

    void CollisionLogo(void);
};
}
#endif SH_SCENE_SELECT_H