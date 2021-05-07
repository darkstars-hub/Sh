//!---------------------------------------------------------
//! @file SceneSelect.cpp
//! @brief ゲームのクリアシーン
//! @author name
//! @date 2019/10/30
//!---------------------------------------------------------


#include "SceneSelect.h"

#include "Application.h"

sh::SceneSelect::SceneSelect()
    : super(),
    select_corsor_(),
    select_logo_(),
    chara_select_(),
    stage_select_(),
    chara_number_(0),
    stage_number_(0) {
    this->Initialize();
}
sh::SceneSelect::~SceneSelect() {
}

sh::SCENE_NO sh::SceneSelect::GetSceneNo(void) const noexcept {
    return sh::SCENE_NO::SELECT;
}

sh::GameStart sh::SceneSelect::GetSelectNumber(void) {
    return sh::GameStart({ chara_number_, stage_number_ });
}

bool sh::SceneSelect::Initialize(void) {
    super::texture_->Load(
        "../textures/scene_select.png");
    super::sound_->Load(
        "../sounds/bgm_maoudamashii_cyber04.ogg");
    sound_->SetLoop(true);
    sound_->SetGain(0.1);

    sound_->Play();

    select_corsor_.Initialize();
    select_logo_.Initialize();
    chara_select_.Initialize();
    stage_select_.Initialize();
    return true;
}
bool sh::SceneSelect::Update(void) {
    super::ChangeSceneFade(sh::SCENE_NO::GAME);

    select_corsor_.Update();
    this->CollisionLogo();

    auto rect = select_corsor_.GetRectangle();
    select_logo_.Update(rect);
    chara_select_.Update(rect);
    stage_select_.Update(rect);


    chara_number_ = chara_select_.GetSelectNumber();
    stage_number_ = stage_select_.GetSelectNumber();


    // シーン遷移
    auto pad = sh::Application::GetInstance().GetGamePad();
    if (sh::Application::GetInstance().GetGamePad()->IsPress(sh::GamePadInfo::BUTTON_A)) {
        if (select_corsor_.OnStartLogo() &&
            chara_number_ != 0 &&
            stage_number_ != 0) {
            sh::SystemSound::Singleton().PlayStart();
            is_change_ = true;
            puts("Press select");
        } // if

        if (chara_number_ == 0 ||
            stage_number_ == 0) {
            sh::SystemSound::Singleton().PlayCancel();
        } // if
    } // if
    return true;
}
bool sh::SceneSelect::Render(void) {
    super::texture_->Render(
        0.0f, 0.0f);

    auto cursor_rect = select_corsor_.GetRectangle();
    select_logo_.Render(cursor_rect);
    stage_select_.Render(cursor_rect);
    chara_select_.Render();
    select_corsor_.Render();

    super::RenderFade();
    return true;
}

bool sh::SceneSelect::Release(void) {
    super::Release();
    select_corsor_.Release();
    select_logo_.Release();
    chara_select_.Release();
    stage_select_.Release();
    return true;
}

void sh::SceneSelect::CollisionLogo(void) {
    auto start_rect = select_logo_.GetRectangle();
    auto cursor_rect = select_corsor_.GetRectangle();

    if (cursor_rect.CollisionRectangle(start_rect)) {
        select_corsor_.SetOnStartLogo(true);
    } // if
    else {
        select_corsor_.SetOnStartLogo(false);
    } // if
}