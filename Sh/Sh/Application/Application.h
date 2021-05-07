//!---------------------------------------------------------
//! @file Application.h
//! @brief main.cppから呼び出される唯一のクラス
//! @author name
//! @date 2019/10/29
//!---------------------------------------------------------


#ifndef SH_APPLICATION_H
//!---------------------------------------------------------
//! @def SH_APPLICATION_H
//! @brief include gurad
//!---------------------------------------------------------
#define SH_APPLICATION_H


#include <cassert>
#include <iostream>
#include <memory>

#include "GLFW/glfw3.h"
#if defined(APIENTRY)
#undef APIENTRY
#endif // defined(APIENTRY)
#include "portaudio/portaudio.h"


#include "Helper.h"
#include "GamePad.h"
#include "Game.h"
#include "Camera.h"


namespace sh {
class Application {
public:
    //!-----------------------------------------------------
    //! @fn : GetInstance(void)
    //! @brief : シングルトンインスタンスを取得
    //! @detail : GetGamePad(void),GetGame(void)を呼び出すため
    //! @param : [in](void) none
    //! @return : Applicationの静的なインスタンス
    //!-----------------------------------------------------
    static sh::Application& GetInstance(void);
    //!-----------------------------------------------------
    //! @fn : Run(void)
    //! @brief : メインループ
    //! @detail : ゲームの中にある全ての処理はこの中で行う
    //! @param : [in](void) none
    //! @return : 正常に終了した場合は０を返す
    //!-----------------------------------------------------
    int Run(void);

    std::shared_ptr<sh::GamePad>
        GetGamePad(void) const noexcept;
    std::shared_ptr<sh::Game>
        GetGame(void) const noexcept;
private:
    //!-----------------------------------------------------
    //! @brief : constructor
    //! @detail : シングルトンの為に隠している
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    Application();
    //!-----------------------------------------------------
    //! @brief : destructor
    //! @detail : Applicationで割り当てわれたメモリはここで解放する
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    ~Application();
    //!-----------------------------------------------------
    //! @brief : copy constructor
    //! @detail : it was deleted
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    Application(const Application& rhs) = delete;
    //!-----------------------------------------------------
    //! @brief : copy assignment operator
    //! @detail : it was deleted
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    Application& operator=(const Application& rhs) = delete;
    //!-----------------------------------------------------
    //! @brief : move constructor
    //! @detail : it was deleted
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    Application(Application&& rhs) = delete;
    //!-----------------------------------------------------
    //! @brief : move assignment operator
    //! @detail : it was deleted
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    Application& operator= (Application&& rhs) = delete;

    //! 1 / fps で処理
    double fps_;

#ifdef _DEBUG
public:
#endif // !_DEBUG
    //! glfwを初期化してからウインドウを作る
    GLFWwindow* window_;
#ifdef _DEBUG
private:
#endif // !_DEBUG

    //! port audio の初期化、終了の為
    PaError audio_;
    //! 入力処理はこの変数を経由する
    std::shared_ptr<sh::GamePad> game_pad_;
    //! このプログラムのゲーム部分
    std::shared_ptr<sh::Game> game_;
};
}
#endif // !SH_APPLICATION_H