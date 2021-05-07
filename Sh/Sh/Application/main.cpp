//!---------------------------------------------------------
//! @file main.cpp
//! @brief entry point
//! @author name
//! @date 2019/10/29
//!---------------------------------------------------------


#define SH_MAIN


#include <iostream>

#include "Application.h"


#if defined(_WIN64)
#pragma comment (lib, "../lib64/gl/OpenGL32.lib")
#pragma comment (lib, "../lib64/glfw/glfw3.lib")
#pragma comment (lib, "../lib64/portaudio/portaudio_x64.lib")
#pragma comment (lib, "../lib64/libsndfile/libsndfile-1.lib")
#pragma comment (lib, "../lib64/xinput/xinput.lib")
#if defined(_DEBUG)
#define AC_MAIN_64_D
#else
#define AC_MAIN_64
#endif // defined
#elif defined (_WIN32)
#pragma comment (lib, "../lib32/gl/OpenGL32.lib")
#pragma comment (lib, "../lib32/glfw/glfw3.lib")
#pragma comment (lib, "../lib32/portaudio/portaudio_x86.lib")
#pragma comment (lib, "../lib32/libsndfile/libsndfile-1.lib")
#pragma comment (lib, "../lib32/xinput/xinput.lib")
#if defined(_DEBUG)
#define AC_MAIN_32_D
#else
#define AC_MAIN_32
#endif // defined
#endif // defined(_WIN)


//int WINAPI WinMain(HINSTANCE instance, HINSTANCE prev, LPCSTR command_line, int show) {
int WINAPI WinMain(HINSTANCE instance, HINSTANCE prev, LPSTR command_line, int show) {
//int main(int argc, char* argv[]) {
    int result = 0;
    puts("program start\n");

    //std::cout << "argc : " << argc << std::endl;
    //std::cout << "argv : " << argv << std::endl;

    result = sh::Application::GetInstance().Run();

    puts("\nprogram end");
    return result;
}