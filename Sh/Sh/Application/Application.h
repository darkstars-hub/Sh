//!---------------------------------------------------------
//! @file Application.h
//! @brief main.cpp����Ăяo�����B��̃N���X
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
    //! @brief : �V���O���g���C���X�^���X���擾
    //! @detail : GetGamePad(void),GetGame(void)���Ăяo������
    //! @param : [in](void) none
    //! @return : Application�̐ÓI�ȃC���X�^���X
    //!-----------------------------------------------------
    static sh::Application& GetInstance(void);
    //!-----------------------------------------------------
    //! @fn : Run(void)
    //! @brief : ���C�����[�v
    //! @detail : �Q�[���̒��ɂ���S�Ă̏����͂��̒��ōs��
    //! @param : [in](void) none
    //! @return : ����ɏI�������ꍇ�͂O��Ԃ�
    //!-----------------------------------------------------
    int Run(void);

    std::shared_ptr<sh::GamePad>
        GetGamePad(void) const noexcept;
    std::shared_ptr<sh::Game>
        GetGame(void) const noexcept;
private:
    //!-----------------------------------------------------
    //! @brief : constructor
    //! @detail : �V���O���g���ׂ̈ɉB���Ă���
    //! @param : [in](void) none
    //! @return : none
    //!-----------------------------------------------------
    Application();
    //!-----------------------------------------------------
    //! @brief : destructor
    //! @detail : Application�Ŋ��蓖�Ă�ꂽ�������͂����ŉ������
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

    //! 1 / fps �ŏ���
    double fps_;

#ifdef _DEBUG
public:
#endif // !_DEBUG
    //! glfw�����������Ă���E�C���h�E�����
    GLFWwindow* window_;
#ifdef _DEBUG
private:
#endif // !_DEBUG

    //! port audio �̏������A�I���̈�
    PaError audio_;
    //! ���͏����͂��̕ϐ����o�R����
    std::shared_ptr<sh::GamePad> game_pad_;
    //! ���̃v���O�����̃Q�[������
    std::shared_ptr<sh::Game> game_;
};
}
#endif // !SH_APPLICATION_H