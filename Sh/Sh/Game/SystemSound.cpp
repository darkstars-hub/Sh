#include "SystemSound.h"

sh::SystemSound& sh::SystemSound::Singleton(void) {
    static sh::SystemSound object;
    return object;
}

void sh::SystemSound::PlayDecide(void) {
    if (this->decide_.IsPlay()) {
        return;
    } // if
    decide_.Play();
}

void sh::SystemSound::PlayCancel(void) {
    if (this->cancel_.IsPlay()) {
        return;
    } // if
    cancel_.Play();
}

void sh::SystemSound::PlayStart(void) {
    if (this->start_.IsPlay()) {
        return;
    } // if
    start_.Play();
}

sh::SystemSound::~SystemSound() {
    this->Release();
}

void sh::SystemSound::PlaySelect(void) {
    if (this->select_.IsPlay()) {
        return;
    } // if
    select_.Play();
}

bool sh::SystemSound::Load(void) {
    if (!this->select_.Load("../sounds/system/se_maoudamashii_system49.ogg")) {
        std::cerr << "failed to load system sound" << std::endl;
        TRACE;
        return false;
    } // if
    if (!this->decide_.Load("../sounds/system/se_maoudamashii_system37.ogg")) {
        std::cerr << "failed to load system sound" << std::endl;
        TRACE;
        return false;
    } // if
    if (!this->cancel_.Load("../sounds/system/se_maoudamashii_system05.ogg")) {
        std::cerr << "failed to load system sound" << std::endl;
        TRACE;
        return false;
    } // if
    if (!this->start_.Load("../sounds/system/se_maoudamashii_system09.ogg")) {
        std::cerr << "failed to load system sound" << std::endl;
        TRACE;
        return false;
    } // if

    double effect_volume = 0.2;
#ifdef _DEBUG
    this->select_.SetGain(effect_volume);
    this->decide_.SetGain(effect_volume);
    this->cancel_.SetGain(effect_volume);
    this->start_.SetGain( effect_volume);
#endif // _DEBUG

    return true;
}
void sh::SystemSound::Release(void) {
    this->select_.Release();
    this->decide_.Release();
    this->cancel_.Release();
    this->start_.Release();
}