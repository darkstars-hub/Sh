//!---------------------------------------------------------
//! @file SoundBuffer.h
//! @brief âπê∫Çì«Ç›çûÇ›èoóÕÇ∑ÇÈÉNÉâÉX
//! @author name
//! @date 2019/10/30
//!---------------------------------------------------------


#ifndef SH_SOUND_BUFFER_H
//!---------------------------------------------------------
//! @def SH_SOUND_BUFFER_H
//! @brief include gurad
//!---------------------------------------------------------
#define SH_SOUND_BUFFER_H

#include <iostream>

#include "portaudio/portaudio.h"
#include "libsndfile/sndfile.h"
#include "Helper.h"

namespace sh {
class SoundData {
public:
    SNDFILE* file_;
    SF_INFO infomation_;
    int position_;
    bool is_loop_;
    double gain_;
    SoundData()
        : file_(),
        infomation_(),
        position_(0),
        is_loop_(false),
        gain_(1.0) {
    }
    ~SoundData() {

    }
    SoundData(const SoundData& rhs) = delete;
    SoundData& operator=(const SoundData& rhs) = delete;
    SoundData(SoundData&& rhs) = delete;
    SoundData& operator=(SoundData&& rhs) = delete;
private:
};
class SoundBuffer {
public:
    SoundBuffer();
    ~SoundBuffer();
    SoundBuffer(const SoundBuffer& rhs) = delete;
    SoundBuffer& operator=(const SoundBuffer& rhs) = delete;
    SoundBuffer(SoundBuffer&& rhs) = delete;
    SoundBuffer& operator=(SoundBuffer&& rhs) = delete;

    static int Callback(const void* input_buffer, void* output_buffer,
                        unsigned long frame_per_buffer, const PaStreamCallbackTimeInfo* time_info,
                        PaStreamCallbackFlags status_flags, void* user_data);
    void SetGain(double gain);
    void SetLoop(bool is_loop);
    void SetPosition(int position);
    bool Load(const char* path);
    bool IsPlay(void);
    void Play(void);
    void Stop(void);
    bool Release(void);
private:
    SoundData* data_;
    PaStream* stream_;
    PaError error_;
};
}
#endif // !SH_SOUND_BUFFER_H

