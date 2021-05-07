#include "WeaponEnergy.h"

sh::WeaponEnergy::WeaponEnergy() :
    value_(0),
    limit_max_(100),
    overheat_(false),
    overheat_time_(0),
    overheat_time_limit_max_(60),
    energy_texture_(),
    frame_texture_ (){
}

sh::WeaponEnergy::~WeaponEnergy() {
}

void sh::WeaponEnergy::SetFrameTexture(const std::shared_ptr<sh::Texture> texture) {
    this->frame_texture_ = texture;
}
void sh::WeaponEnergy::SetEnegryTexture(const std::shared_ptr<sh::Texture> texture) {
    this->energy_texture_ = texture;
}

bool sh::WeaponEnergy::Initialize(void) {
    value_ = 0;
    overheat_ = false;
    return true;
}

bool sh::WeaponEnergy::Update(void) {
    overheat_time_--;
    if (overheat_time_ < 0) {
        overheat_time_ = 0;
        overheat_ = false;
    } // if
    
    if (!overheat_) {
        value_++;
        if (value_ >= limit_max_) {
            value_ = limit_max_;
        } // if
    } // if

    return true;
}

bool sh::WeaponEnergy::Render(void) {
    if (auto r = energy_texture_.lock()) {
        sh::Rectangle rect(
            0, 0, 532 * (value_ * 0.01f), 64);
        r->Render(248.0f, 4.0f, rect);
    } // if
    if (auto r = frame_texture_.lock()) {
        if (overheat_time_ % 2 == 0) {
            r->Render(0.0f, -40.0f);
        } // if
    } // if

    return true;
}


int sh::WeaponEnergy::GetValue(void) const noexcept {
    return this->value_;
}

bool sh::WeaponEnergy::IsOverHeat(void) const noexcept {
    return this->overheat_;
}

void sh::WeaponEnergy::Use(const int cost) {
    value_ -= cost;
    if (value_ <= 0) {
        value_ = 0;
        overheat_ = true;
        overheat_time_ = overheat_time_limit_max_;
    } // if
}