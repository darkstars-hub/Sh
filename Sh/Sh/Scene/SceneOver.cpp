//!---------------------------------------------------------
//! @file SceneOver.cpp
//! @brief ゲームオーバーシーン
//! @author name
//! @date 2019/10/30
//!---------------------------------------------------------


#include "SceneOver.h"

#include "Application.h"

sh::SceneOver::SceneOver()
    : super() {
    this->Initialize();
}
sh::SceneOver::~SceneOver() {
}

sh::SCENE_NO sh::SceneOver::GetSceneNo(void) const noexcept {
    return sh::SCENE_NO::OVER;
}

bool sh::SceneOver::Initialize() {
    super::texture_->Load(
        "../textures/scene_over.png");
    super::sound_->Load(
        "../sounds/bgm_maoudamashii_cyber03.ogg");
    sound_->SetLoop(false);
    sound_->SetGain(0.1);
    sound_->Play();
    return true;
}
bool sh::SceneOver::Update(void) {
    super::ChangeSceneFade(sh::SCENE_NO::TITLE);

    auto pad = sh::Application::GetInstance().GetGamePad();
    if (pad->IsPress(GamePadInfo::BUTTON_START)) {
        is_change_ = true;
        puts("Press over");
    } // if
    return true;
}
bool sh::SceneOver::Render(void) {
    super::texture_->Render(
    0.0f, 0.0f);
    super::RenderFade();
    return true;
}