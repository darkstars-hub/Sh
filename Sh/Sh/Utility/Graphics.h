#ifndef SH_GRAPHICS_H
#define SH_GRAPHICS_H

#include "GLFW/glfw3.h"
#if defined(APIENTRY)
#undef APIENTRY
#endif // defined(APIENTRY)

#include "Helper.h"

#include "Line.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Color.h"


namespace sh {

class Graphics {
public:
    Graphics() {
    }
    ~Graphics() {
    }

    void DrawLine(const Line& line, const sh::Color& color) {
        auto l = line;
        ::glEnable(GL_TEXTURE_2D);
        ::glEnable(GL_BLEND);
        ::glBindTexture(GL_TEXTURE_2D, 0);

        ::glPushMatrix();
        ::glTranslated(0.0, 0.0, 0.0);
        ::glColor4f(color.red_ / 255.0f,
                    color.green_ / 255.0f,
                    color.blue_ / 255.0f,
                    color.alpha_ / 255.0f);
        ::glLineWidth(1.0);
        ::glBegin(GL_LINES);

        ::glVertex2d(l.start_x_, l.start_y_);
        ::glVertex2d(l.end_x_, l.end_y_);

        ::glClearColor(1.0, 1.0, 1.0, 1.0);
        ::glEnd();
        ::glPopMatrix();
        ::glDisable(GL_TEXTURE_2D);
    }

    void DrawRectangle(const Rectangle& rectangle, const sh::Color& color) {
        auto r = rectangle;
        ::glEnable(GL_TEXTURE_2D);
        ::glEnable(GL_BLEND);
        ::glBindTexture(GL_TEXTURE_2D, 0);

        ::glPushMatrix();
        ::glTranslated(0.0, 0.0, 0.0);
        ::glColor4f(color.red_ / 255.0f, 
                    color.green_ / 255.0f, 
                    color.blue_ / 255.0f,
                    color.alpha_ / 255.0f);
        ::glBegin(GL_POLYGON);

        ::glTexCoord2d(0.0, 0.0);
        ::glVertex2d(r.left_, r.top_);
        ::glTexCoord2d(1.0, 0.0);
        ::glVertex2d(r.right_, r.top_);
        ::glTexCoord2d(1.0, 1.0);
        ::glVertex2d(r.right_, r.bottom_);
        ::glTexCoord2d(0.0, 1.0);
        ::glVertex2d(r.left_, r.bottom_);

        ::glClearColor(1.0, 1.0, 1.0, 1.0);
        ::glEnd();
        ::glPopMatrix();
        ::glDisable(GL_TEXTURE_2D);
    }

    void DrawCircle(const Circle& circle, const sh::Color& color) {
        auto c = circle;
        ::glEnable(GL_TEXTURE_2D);
        ::glEnable(GL_BLEND);
        ::glBindTexture(GL_TEXTURE_2D, 0);

        ::glPushMatrix();
        ::glTranslated(c.x_, c.y_, 0.0);
        ::glColor4f(color.red_ / 255.0f,
                    color.green_ / 255.0f,
                    color.blue_ / 255.0f,
                    color.alpha_ / 255.0f);
        ::glBegin(GL_LINES);

        float rate, x, y;
        int n = 100;
        for (int i = 0; i < n; i++) {
            rate = static_cast<float>(i) / static_cast<float>(n);
            x = c.radius_ * std::cosf(2.0f * kPi * rate);
            y = c.radius_ * std::sinf(2.0f * kPi * rate);
            ::glVertex2f(x, y);
        } // for

        ::glClearColor(1.0, 1.0, 1.0, 1.0);
        ::glEnd();
        ::glPopMatrix();
        ::glDisable(GL_TEXTURE_2D);
    }
};
}
#endif // !SH_GRAPHICS_H
