#ifndef SH_COLOR_H
#define SH_COLOR_H

namespace sh {


class Color {
public:
    int red_, green_, blue_, alpha_;
    Color()
        : red_(0),
        green_(0),
        blue_(0),
        alpha_(0){
    }
    Color(int r,int g, int b, int a)
        : red_(r),
        green_(g),
        blue_(b),
        alpha_(a){
        if (red_ > 255) {
            red_ = 255;
        } // if
        else if (red_ < 0) {
            red_ = 0;
        } // else if
        if (green_ > 255) {
            green_ = 255;
        } // if
        else if (green_ < 0) {
            green_ = 0;
        } // else if
        if (blue_ > 255) {
            blue_ = 255;
        } // if
        else if (blue_ < 0) {
            blue_ = 0;
        } // else if
        if (alpha_ > 255) {
            alpha_ = 255;
        } // if
        else if (alpha_ < 0) {
            alpha_ = 0;
        } // else if
    }
    ~Color() {
    }
};
}
#endif // !SH_COLOR_H