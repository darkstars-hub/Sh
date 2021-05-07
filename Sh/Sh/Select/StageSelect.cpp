#include "StageSelect.h"

#include "Application.h"
#include "SystemSound.h"

sh::StageSelect::StageSelect() :
    stage_scale_(0.25f),
    stage_1_(std::make_shared<sh::Texture>()),
    stage_2_(std::make_shared<sh::Texture>()),
    stage_3_(std::make_shared<sh::Texture>()),
    stage_rect_1_(),
    select_1_(false),
    stage_rect_2_(),
    select_2_(false),
    stage_rect_3_(),
    select_3_(false){
}

int sh::StageSelect::GetSelectNumber(void) {
    if (select_1_) {
        return 1;
    } // if
    if (select_2_) {
        return 2;
    } // if
    if (select_3_) {
        return 3;
    } // if

    return 0;
}

void sh::StageSelect::Initialize(void) {
    stage_1_->Load("../textures/pipo-bg001.png");
    stage_2_->Load("../textures/pipo-bg003.png");
    stage_3_->Load("../textures/pipo-bg005.png");


    auto rect = sh::Rectangle(0.0f,
                              0.0f,
                              sh::kWindowWidth,
                              sh::kWindowHeight);
    auto size_x = rect.GetWidth() * stage_scale_;
    auto size_y = rect.GetHeight() * stage_scale_;
    auto space = 50.0f;
    auto frame = 5.0f;
    stage_rect_1_ = sh::Rectangle(size_x * 1 + space * 0 - (size_x * 0.5f) - frame,
                                  350.0f - (size_y * 0.5f) - frame,
                                  size_x * 1 + space * 0 + (size_x * 0.5f) + frame,
                                  350.0f + (size_y * 0.5f) + frame);

    stage_rect_2_ = sh::Rectangle(size_x * 2 + space * 1 - (size_x * 0.5f) - frame,
                                  350.0f - (size_y * 0.5f) - frame,
                                  size_x * 2 + space * 1 + (size_x * 0.5f) + frame,
                                  350.0f + (size_y * 0.5f) + frame);

    stage_rect_3_ = sh::Rectangle(size_x * 3 + space * 2 - (size_x * 0.5f) - frame,
                                  350.0f - (size_y * 0.5f) - frame,
                                  size_x * 3 + space * 2 + (size_x * 0.5f) + frame,
                                  350.0f + (size_y * 0.5f) + frame);
}
void sh::StageSelect::Update(const sh::Rectangle cursor_rect) {
    auto pad = sh::Application::GetInstance().GetGamePad();


    if (pad->IsPress(sh::GamePadInfo::BUTTON_A)) {
        if (stage_rect_1_.CollisionRectangle(cursor_rect)) {
            if (!select_1_) {
                sh::SystemSound::Singleton().PlayDecide();
            } // if
            select_1_ = true;
            select_2_ = false;
            select_3_ = false;
        } // if
        if (stage_rect_2_.CollisionRectangle(cursor_rect)) {
            if (!select_2_) {
                sh::SystemSound::Singleton().PlayDecide();
            } // if
            select_1_ = false;
            select_2_ = true;
            select_3_ = false;
        } // if
        if (stage_rect_3_.CollisionRectangle(cursor_rect)) {
            if (!select_3_) {
                sh::SystemSound::Singleton().PlayDecide();
            } // if
            select_1_ = false;
            select_2_ = false;
            select_3_ = true;
        } // if
    } // if

    if (pad->IsPress(sh::GamePadInfo::BUTTON_B)) {
        select_1_ = false;
        select_2_ = false;
        select_3_ = false;
        sh::SystemSound::Singleton().PlayCancel();
    } // if
}

void sh::StageSelect::Render(const sh::Rectangle cursor_rect) {
    if (sh::Rectangle().CollisionRectangle(cursor_rect)) {
        puts("");
    } // if


    if (stage_rect_1_.CollisionRectangle(cursor_rect) || select_1_) {
        auto g = sh::Graphics();
        auto c = sh::Color(222, 222, 22, 222);
        g.DrawRectangle(stage_rect_1_, c);
    } // if
    if (stage_rect_2_.CollisionRectangle(cursor_rect) || select_2_) {
        auto g = sh::Graphics();
        auto c = sh::Color(222, 222, 22, 222);
        g.DrawRectangle(stage_rect_2_, c);
    } // if
    if (stage_rect_3_.CollisionRectangle(cursor_rect) || select_3_) {
        auto g = sh::Graphics();
        auto c = sh::Color(222, 222, 22, 222);
        g.DrawRectangle(stage_rect_3_, c);
    } // if


    auto rect = sh::Rectangle(0.0f,
                              0.0f,
                              sh::kWindowWidth,
                              sh::kWindowHeight);
    auto size = rect.GetWidth() * stage_scale_;
    auto space = 50.0f;

    stage_1_->Render(space * 0 + size * 1, 350.0f,
                     0.0f, rect,
                     stage_scale_);

    stage_2_->Render(space * 1 + size * 2, 350.0f,
                     0.0f, rect,
                     stage_scale_);
    stage_3_->Render(space * 2 + size * 3, 350.0f,
                     0.0f, rect,
                     stage_scale_);
}
void sh::StageSelect::Release(void) {
    stage_1_->Release();
    stage_2_->Release();
    stage_3_->Release();
}