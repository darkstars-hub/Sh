//!---------------------------------------------------------
//! @file SceneResult.cpp
//! @brief ゲームのリザルトシーン
//! @author name
//! @date 2019/10/30
//!---------------------------------------------------------


#include "SceneResult.h"

#include "Application.h"

sh::SceneResult::SceneResult()
    : super() {
    this->Initialize();
}
sh::SceneResult::~SceneResult() {
}

sh::SCENE_NO sh::SceneResult::GetSceneNo(void) const noexcept {
    return sh::SCENE_NO::RESULT;
}

bool sh::SceneResult::Initialize() {
    super::texture_->Load(
        "../textures/scene_result.png");
    super::sound_->Load(
        "../sounds/bgm_maoudamashii_cyber05.ogg");
    sound_->SetLoop(true);
    sound_->SetGain(0.01);
    sound_->Play();
    return true;
}
bool sh::SceneResult::Update(void) {
    super::ChangeSceneFade(sh::SCENE_NO::TITLE);

    auto pad = sh::Application::GetInstance().GetGamePad();
    if (pad->IsPress(GamePadInfo::BUTTON_START)) {
        is_change_ = true;
        puts("Press result");
    } // if
    return true;
}
bool sh::SceneResult::Render(void) {
    super::texture_->Render(
        0.0f, 0.0f);
    super::RenderFade();
    return true;
}