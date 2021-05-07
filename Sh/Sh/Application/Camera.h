//!---------------------------------------------------------
//! @file Camera.h
//! @brief ゲーム内の視点位置を持つクラス
//! Gameクラスのメンバなる
//! @author name
//! @date 2019/10/30
//!---------------------------------------------------------


#ifndef SH_CAMERA_H
//!---------------------------------------------------------
//! @def SH_CAMERA_H
//! @brief include gurad
//!---------------------------------------------------------
#define SH_CAMERA_H


#include <memory>

#include "GLFW/glfw3.h"
#if defined(APIENTRY)
#undef APIENTRY
#endif // defined(APIENTRY)

#include "Helper.h"
#include "Vector2.h"

namespace sh {
class Camera {
public:
    Camera();
    ~Camera();
    Camera(const Camera& rhs) = delete;
    Camera& operator=(const Camera& rhs) = delete;
    Camera(Camera&& rhs) = delete;
    Camera& operator= (Camera&& rhs) = delete;

    sh::Vector2* GetViewPoint(void);
    float GetWindowTop(void) const noexcept;
    float GetWindowBottom(void) const noexcept;
    float GetWindowRight(void) const noexcept;
    float GetWindowLeft(void) const noexcept;

    void Update(void);
private:
    sh::Vector2 view_point_;
};
}
#endif // !SH_CAMERA_H