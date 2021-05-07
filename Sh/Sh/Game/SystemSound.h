//!---------------------------------------------------------
//! @file SystemSound.h
//! @brief �Q�[���̒��Ŗ炷�����Ǘ�����
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
    //! Game.cpp�ŌĂяo��
    bool Load(void);
    //! �f�X�g���N�^�ŌĂяo��
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