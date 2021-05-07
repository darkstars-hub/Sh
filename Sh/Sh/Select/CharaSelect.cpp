#include "CharaSelect.h"

#include "Application.h"

sh::CharaSelect::CharaSelect() :
    resource_manager_(nullptr),
    icon_size_(32.0f),
    player_scale_(5.0f),
    player_white_(nullptr),
    player_black_(nullptr),
    player_blue_(nullptr),
    player_purple_(nullptr),
    white_icon_(),
    black_icon_(),
    blue_icon_(),
    purple_icon_() {
}

int sh::CharaSelect::GetSelectNumber(void) {
    if (white_icon_.IsSelect()) {
        return 1;
    } // if
    if (black_icon_.IsSelect()) {
        return 2;
    } // if
    if (blue_icon_.IsSelect()) {
        return 3;
    } // if
    if (purple_icon_.IsSelect()) {
        return 4;
    } // if

    return 0;
}

void sh::CharaSelect::Initialize(sh::ResourceManager& resource_manager) {
    /*
    player_white_->Load("../textures/pipo-halloweenchara2016_20.png");
    player_black_->Load("../textures/pipo-halloweenchara2016_21.png");
    player_blue_->Load("../textures/pipo-halloweenchara2016_22.png");
    player_purple_->Load("../textures/pipo-halloweenchara2016_23.png");
    */
    player_white_ = resource_manager.GetTexture(sh::TextureFileID::PLAYER_TEXTURE_WHITE);
    player_black_ = resource_manager.GetTexture(sh::TextureFileID::PLAYER_TEXTURE_BLACK);
    player_blue_ = resource_manager.GetTexture(sh::TextureFileID::PLAYER_TEXTURE_BLUE);
    player_purple_ = resource_manager.GetTexture(sh::TextureFileID::PLAYER_TEXTURE_PURPLE);

    auto anime = sh::MakeAnime{ icon_size_, icon_size_, 4, 1 };
    auto select_anime = sh::MakeAnime{ icon_size_, icon_size_, 1, 3 };

    white_icon_.MakeAnimation(anime, select_anime);
    white_icon_.Initialize({ 200.0f,550.0f }, player_white_, 3.0f);

    black_icon_.MakeAnimation(anime, select_anime);
    black_icon_.Initialize({ 400.0f,550.0f }, player_black_, 3.0f);

    blue_icon_.MakeAnimation(anime, select_anime);
    blue_icon_.Initialize({ 600.0f,550.0f }, player_blue_, 3.0f);

    purple_icon_.MakeAnimation(anime, select_anime);
    purple_icon_.Initialize({ 800.0f,550.0f }, player_purple_, 3.0f);
}

void sh::CharaSelect::Initialize(void) {
    player_white_ = std::make_shared<sh::Texture>();
    player_black_ = std::make_shared<sh::Texture>();
    player_blue_ = std::make_shared<sh::Texture>();
    player_purple_ = std::make_shared<sh::Texture>();

    player_white_->Load("../textures/pipo-halloweenchara2016_20.png");
    player_black_->Load("../textures/pipo-halloweenchara2016_21.png");
    player_blue_->Load("../textures/pipo-halloweenchara2016_22.png");
    player_purple_->Load("../textures/pipo-halloweenchara2016_23.png");

    auto anime = sh::MakeAnime{ icon_size_, icon_size_, 4, 1 };
    auto select_anime = sh::MakeAnime{ icon_size_, icon_size_, 1, 3 };

    white_icon_.MakeAnimation(anime, select_anime);
    white_icon_.Initialize({ 200.0f,550.0f }, player_white_, 3.0f);

    black_icon_.MakeAnimation(anime, select_anime);
    black_icon_.Initialize({ 400.0f,550.0f }, player_black_, 3.0f);

    blue_icon_.MakeAnimation(anime, select_anime);
    blue_icon_.Initialize({ 600.0f,550.0f }, player_blue_, 3.0f);

    purple_icon_.MakeAnimation(anime, select_anime);
    purple_icon_.Initialize({ 800.0f,550.0f }, player_purple_, 3.0f);
}
void sh::CharaSelect::Update(const sh::Rectangle cursor_rect) {
    white_icon_.Update(cursor_rect);
    if (white_icon_.IsSelect()) {
        black_icon_.SetSelected(false);
        blue_icon_.SetSelected(false);
        purple_icon_.SetSelected(false);
    } // if

    black_icon_.Update(cursor_rect);
    if (black_icon_.IsSelect()) {
        white_icon_.SetSelected(false);
        blue_icon_.SetSelected(false);
        purple_icon_.SetSelected(false);
    } // if

    blue_icon_.Update(cursor_rect);
    if (blue_icon_.IsSelect()) {
        white_icon_.SetSelected(false);
        black_icon_.SetSelected(false);
        purple_icon_.SetSelected(false);
    } // if

    purple_icon_.Update(cursor_rect);
    if (purple_icon_.IsSelect()) {
        white_icon_.SetSelected(false);
        black_icon_.SetSelected(false);
        blue_icon_.SetSelected(false);
    } // if
}
void sh::CharaSelect::Render(void) {
    white_icon_.Render();
    black_icon_.Render();
    blue_icon_.Render();
    purple_icon_.Render();
}
void sh::CharaSelect::Release(void) {
    player_white_->Release();
    player_black_->Release();
    player_blue_->Release();
    player_purple_->Release();
}