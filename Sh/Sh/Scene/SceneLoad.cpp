//!---------------------------------------------------------
//! @file SceneLoad.cpp
//! @brief ゲームのクリアシーン
//! @author name
//! @date 2019/10/30
//!---------------------------------------------------------


#include "SceneLoad.h"

#include "Application.h"

void WarpFunc(std::promise<int> p, sh::ResourceManager& r) {
    r.Load();
    p.set_value(0);
}

sh::SceneLoad::SceneLoad(sh::GameStart select)
    : super(),
    loaded_(false),
    player_select_(select.select_chara),
    load_texture_(),
    animation_(),
    resource_manager_(),
    load_thread_() {
    //this->Initialize();
}
sh::SceneLoad::~SceneLoad() {
}

sh::SCENE_NO sh::SceneLoad::GetSceneNo(void) const noexcept {
    return sh::SCENE_NO::LOAD;
}

bool sh::SceneLoad::Initialize(void) {
    super::texture_->Load("../textures/scene_load.png");

    switch (player_select_) {
        case 1:
            load_texture_.Load(
                "../textures/pipo-halloweenchara2016_20.png");
            break;
        case 2:
            load_texture_.Load(
                "../textures/pipo-halloweenchara2016_21.png");
            break;
        case 3:
            load_texture_.Load(
                "../textures/pipo-halloweenchara2016_22.png");
            break;
        case 4:
            load_texture_.Load(
                "../textures/pipo-halloweenchara2016_23.png");
            break;
        default:
            break;
    } // switch

    float size = 32.0f;
    auto anime = sh::MakeAnime{ size, size, 4, 1 };
    animation_.MakeAnimation(anime);

    /*
    load_thread_ = std::thread([&]() {
        resource_manager_->Load();
    });
    load_thread_.join();
    */

    resource_manager_->Load();
    return true;
}
bool sh::SceneLoad::Update(void) {
    super::ChangeSceneFade(sh::SCENE_NO::GAME);
    animation_.Update();

    auto pad = sh::Application::GetInstance().GetGamePad();
    if (pad->IsPress(GamePadInfo::BUTTON_START)) {
        loaded_ = true;
        puts("Press clear");
    } // if

    // シーン遷移
    if (loaded_) {
        is_change_ = true;
    } // if

    return true;
}
bool sh::SceneLoad::Render(void) {
    auto g = sh::Graphics();
    g.DrawRectangle(sh::Rectangle(
        0.0f,
        0.0f,
        sh::kWindowWidth,
        sh::kWindowHeight),
        sh::Color(0, 0, 0, 255));

    super::texture_->Render(0.0f, 0.0f);

    float width = (float)load_texture_.GetWidth();
    float height = (float)load_texture_.GetHeight();
    load_texture_.Render(
        sh::kWindowWidth - width,
        height,
        0,
        animation_.GetRectangle());

    super::RenderFade();
    return true;
}

bool sh::SceneLoad::Release(void) {
    super::Release();

    load_texture_.Release();

    return true;
}

void sh::SceneLoad::AcquireResource(sh::ResourceManager& container) {
    resource_manager_ = &container;
}

/*
void sh::SceneLoad::WarpFunc(std::promise<int> p) {
    resource_manager_->Load();
    p.set_value(0);
}
*/
