//!---------------------------------------------------------
//! @file SoundBuffer.cpp
//! @brief 音声を読み込み出力するクラス
//! @author name
//! @date 2019/10/30
//!---------------------------------------------------------


#include "SoundBuffer.h"

sh::SoundBuffer::SoundBuffer()
    : data_(new SoundData()),
    error_(),
    stream_() {
}
sh::SoundBuffer::~SoundBuffer() {
    _ASSERT_EXPR(!stream_,
                 L"ストリームが閉じられていません");
}

int sh::SoundBuffer::Callback(
    const void* input_buffer, void* output_buffer,
    unsigned long frame_per_buffer, const PaStreamCallbackTimeInfo* time_info,
    PaStreamCallbackFlags status_flags, void* user_data) {

    int* output = (int*)output_buffer;
    SoundData* data = (SoundData*)user_data;

    if (data->is_loop_ && data->position_ > data->infomation_.frames) {
        data->position_ = 0;
    } // if
    if (!data->is_loop_ && data->position_ > data->infomation_.frames) {
        return paComplete;
    } // if
    ::sf_seek(data->file_, data->position_, SF_SEEK_SET);
    ::sf_readf_int(data->file_, output, frame_per_buffer);
    for (unsigned int i = 0; i < frame_per_buffer * data->infomation_.channels; i++) {
        output[i] = (int)(output[i] * data->gain_);
    } // for
    data->position_ += frame_per_buffer;

    auto x =
        sizeof(status_flags) +
        sizeof(time_info) +
        sizeof(input_buffer);
    ++x;
    return paContinue;
}

void sh::SoundBuffer::SetGain(double gain) {
    this->data_->gain_ = gain;
}

void sh::SoundBuffer::SetLoop(bool is_loop) {
    this->data_->is_loop_ = is_loop;
}

void sh::SoundBuffer::SetPosition(int position) {
    this->data_->position_ = position;
}

bool sh::SoundBuffer::Load(const char* path) {
    data_->position_ = 0;
    data_->infomation_.format = SF_FORMAT_OGG;
    data_->file_ = ::sf_open(path, SFM_READ, &data_->infomation_);
    if (!data_->file_) {
        std::cerr << "failed to oepned file" << std::endl;
        return 1;
    } // if

    PaStreamParameters output_paramaters;
    output_paramaters.device = ::Pa_GetDefaultOutputDevice();
    output_paramaters.channelCount = data_->infomation_.channels;
    output_paramaters.sampleFormat = paInt32;
    output_paramaters.suggestedLatency = ::Pa_GetDeviceInfo(output_paramaters.device)->defaultHighOutputLatency;
    output_paramaters.hostApiSpecificStreamInfo = NULL;
    error_ = ::Pa_OpenStream(
        &stream_,
        NULL,
        &output_paramaters,
        data_->infomation_.samplerate,
        paFramesPerBufferUnspecified,
        paNoFlag,
        Callback,
        data_);
    if (error_ != paNoError) {
        std::cerr << "failed to  opened stream" << std::endl;
        std::cerr << "error : " << ::Pa_GetErrorText(error_) << std::endl;
        //::Pa_Terminate();
        TRACE;
        return false;
    } // if
    return true;
}

bool sh::SoundBuffer::IsPlay(void) {
    if (::Pa_IsStreamActive(stream_)) {
        return true;
    } // if
    else if (!::Pa_IsStreamActive(stream_) && data_->is_loop_) {
        return false;
    } // else if

    if (!::Pa_IsStreamActive(stream_) && !data_->is_loop_) {
        if (data_->position_ > data_->infomation_.frames) {
            ::Pa_StopStream(stream_);
            //data_->position_ = 0;
            return false;
        } // if
    } // if
    return false;
}

void sh::SoundBuffer::Play(void) {
    if (!::Pa_IsStreamActive(stream_)) {
        data_->position_ = 0;
        ::Pa_StartStream(stream_);
    } // if
}

void sh::SoundBuffer::Stop(void) {
    if (!::Pa_IsStreamStopped(stream_)) {
        ::Pa_StopStream(stream_);
    } // if
}

bool sh::SoundBuffer::Release(void) {
    if (!::Pa_IsStreamActive(stream_)) {
        ::Pa_AbortStream(stream_);
        stream_ = NULL;
        delete data_;
        data_ = nullptr;
        return true;
    } // if


    if (!::Pa_IsStreamStopped(stream_)) {
        ::Pa_StopStream(stream_);
    } // if
    error_ = ::Pa_CloseStream(stream_);
    if (error_ != paNoError) {
        std::cerr << "failed to  close stream" << std::endl;
        std::cerr << "portaudio error : " << Pa_GetErrorText(error_) << std::endl;
        TRACE;
        return false;
    } // if
    stream_ = NULL;
    delete data_;
    data_ = nullptr;

    return false;
}