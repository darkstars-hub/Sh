//!---------------------------------------------------------
//! @file SystemSound.h
//! @brief ゲームの中で鳴らす音を管理する
//! @author name
//! @date 2019/12/26
//!---------------------------------------------------------


#ifndef SH_SYSTEM_SOUND_H
#define SH_SYSTEM_SOUND_H

#include "Helper.h"
#include "SoundBuffer.h"

namespace sh {
class SystemSound {
public:
    //! Game.cppで呼び出す
    bool Load(void);
    //! デストラクタで呼び出す
    void Release(void);

    static sh::SystemSound& Singleton(void);
    
    void PlaySelect(void);
    void PlayDecide(void);
    void PlayCancel(void);
    void PlayStart(void);

    SystemSound(const SystemSound& rhs) = delete;
    SystemSound& operator=(const SystemSound& rhs) = delete;
    SystemSound(SystemSound&& rhs) = delete;
    SystemSound& operator= (SystemSound&& rhs) = delete;
private:
    SystemSound() = default;
    ~SystemSound();

    sh::SoundBuffer select_;
    sh::SoundBuffer decide_;
    sh::SoundBuffer cancel_;
    sh::SoundBuffer start_;
};
}
#endif // !SH_SYSTEM_SOUND_H