//!---------------------------------------------------------
//! @file Application.cpp
//! @brief main.cppから呼び出される唯一のクラス
//! @author name
//! @date 2019/10/30
//!---------------------------------------------------------


#include "Application.h"


sh::Application::Application()
    : fps_(60.0f),
    window_(),
    audio_(),
    game_pad_(std::make_shared<sh::GamePad>()),
    game_(std::make_shared<sh::Game>()) {

    // initialize glfw
    if (::glfwInit() == GL_FALSE) {
        std::cerr << "failed to initialize glfw" << std::endl;
        TRACE;
    } // if
    ::glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    ::glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    ::glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    // create window
    window_ = ::glfwCreateWindow(sh::kWindowWidth,
                                 sh::kWindowHeight,
                                 sh::kWindowTitle,
                                 nullptr,
                                 nullptr);



    // make context
    if (window_ == nullptr) {
        ::glfwTerminate();
        std::cerr << "failed to create window" << std::endl;
        TRACE;
    } // if
    ::glfwMakeContextCurrent(window_);
    ::glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    ::glfwSwapInterval(1);

    // initialize portaudio
    audio_ = ::Pa_Initialize();
    if (audio_ != paNoError) {
        std::cerr << "failed to initialize portaudio" << std::endl;
        std::cerr << "error : " << ::Pa_GetErrorText(audio_) << std::endl;
        TRACE;
    } // if
}
sh::Application::~Application() {
   // game resource release
    if (!game_->Release()) {
        std::cerr << "failed to release game" << std::endl;
        TRACE;
        //return -1;
    } // if


     // terminate portaudio
    audio_ = ::Pa_Terminate();
    if (audio_ != paNoError) {
        std::cerr << "failed to terminate portaudio" << std::endl;
        std::cerr << "error : " << ::Pa_GetErrorText(audio_) << std::endl;
        ::Pa_Terminate();
        TRACE;
    } // if

    // terminate glfw
    ::glfwDestroyWindow(window_);
    ::glfwTerminate();
}

sh::Application& sh::Application::GetInstance(void) {
    static sh::Application object;
    return object;
}
std::shared_ptr<sh::GamePad> sh::Application::GetGamePad(void) const noexcept {
    return this->game_pad_;
}
std::shared_ptr<sh::Game> sh::Application::GetGame(void) const noexcept {
    return this->game_;
}

int sh::Application::Run(void) {
    // 1秒に60回処理を行う
    static double current_time = 0;
    static double last_time = 0;
    static double elapsed_time = 0;
    glfwSetTime(0.0);

    // game initialize
    if (!game_->Initialize()) {
        std::cerr << "failed to initialize game" << std::endl;
        TRACE;
        return -1;
    } // if
    
    // check
    assert(window_);
    assert(game_);

    // mainloop
    while (!::glfwWindowShouldClose(window_)) {

        // 1秒に60回処理を行う
        current_time = ::glfwGetTime();
        elapsed_time = current_time - last_time;
        if (elapsed_time >= 1.0 / fps_) {
            // clear value
            ::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
            ::glLoadIdentity();
            ::glMatrixMode(GL_PROJECTION);
            ::glColor3d(1.0, 1.0, 1.0);
            game_pad_->StateUpdate();

            // game
            if (!game_->Update()) {
                std::cerr << "failed to update game" << std::endl;
                TRACE;
                return -1;
            } // if
            //::glEnable(GL_TEXTURE_2D);
            //::glEnable(GL_BLEND);
            if (!game_->IsEnd() && !game_->Render()) {
                std::cerr << "failed to render game" << std::endl;
                TRACE;
                return -1;
            } // if

            // for next frame
            ::glfwSwapBuffers(window_);
            ::glfwPollEvents();
            last_time = ::glfwGetTime();


            if (game_->IsEnd()) {
                puts("exit game");
                break;
            } // if
        } // if
    } // while
    return 0;
}