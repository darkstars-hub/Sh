//!---------------------------------------------------------
//! @file Helper.h
//! @brief 
//! @author name
//! @date 2019/10/30
//!---------------------------------------------------------

#ifndef SH_HELPER_H
//!---------------------------------------------------------
//! @def SH_HELPER_H
//! @brief include gurad
//!---------------------------------------------------------
#define SH_HELPER_H

#include <crtdbg.h>
#include <iostream>
#include <random>

#include <Windows.h>

#include "Vector2.h"

#define SAFE_DELETE(x) if(x){delete x; x = nullptr;}
#define DEBUG_PRINT(arg, ...)
#define TRACE

#if defined(_DEBUG)
#undef DEBUG_PRINT
#undef TRACE 
#define DEBUG_PRINT(arg, ...)\
{TCHAR str[256]; \
::sprintf_s(str, arg, __VA_ARGS__); \
::OutputDebugString(str);}
#define TRACE \
DEBUG_PRINT("%s %s %d \n", __FILE__, __func__, __LINE__);
#endif // defined (_DEBUG)



namespace sh {
constexpr const char* kWindowTitle = "sh";
constexpr int kWindowWidth = 1024;
constexpr int kWindowHeight = 768;
constexpr int kWindowPositionX = 100;
constexpr int kWindowPositionY = 100;

constexpr float kPi = 3.14159f;

inline float ToRadian(float degree) {
    return degree * (kPi / 180.0f);
};
inline float ToDegree(float radian) {
    return radian * (180.0f / kPi);
}

inline int GenerateRandom(int min, int max) {
    std::random_device seed;
    std::mt19937 engine(seed());
    std::uniform_int_distribution<> random(min, max);
    return random(engine);
}

inline void Rotate(float& pos_x, float& pos_y, const float angle,
                   const float center_x, const float center_y) {
    float rad = kPi * angle / 180.0f;

    float axis_x = pos_x - center_x;
    float axis_y = pos_y - center_y;

    float translate_x = (axis_x)*std::cosf(rad) - (axis_y)*std::sinf(rad);
    float translate_y = (axis_x)*std::sinf(rad) + (axis_y)*std::cosf(rad);

    pos_x = center_x + translate_x;
    pos_y = center_y + translate_y;
};
inline void Rotate(Vector2& pos, const float angle, const Vector2 center) {
    Rotate(pos.x_,pos.y_,
           angle,
           center.x_,center.y_);
};
}
#endif // !SH_HELPER_H