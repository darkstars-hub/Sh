//!---------------------------------------------------------
//! @file Animation.h
//! @brief テクスチャに渡すRectangleクラスのvector
//! @author name
//! @date 2019/10/30
//!---------------------------------------------------------


#ifndef SH_ANIMATION_H
//!---------------------------------------------------------
//! @def SH_ANIMATION_H
//! @brief include gurad
//!---------------------------------------------------------
#define SH_ANIMATION_H

#include <vector>

#include "Helper.h"
#include "Vector2.h"
#include "Rectangle.h"

namespace sh {
struct MakeAnime {
    float width; 
    float height;
    int column_count;
    int row_count;
    sh::Vector2 offset;
};
class Animation {
public:
  Animation();
  ~Animation();
  Animation(const Animation& rhs) = default;
  Animation& operator=(const Animation& rhs) = default;
  Animation(Animation&& rhs) = default;
  Animation& operator= (Animation&& rhs) = default;

  void SetCurrentIndex(int index) ;
  void SetRate(int rate);
  sh::Rectangle GetRectangle() const;
  int GetCurrentIndex() const;
  int GetRate() const;

  bool IsEnd() const;
  void ResetRectangles();
  void MakeAnimation(const sh::MakeAnime make_animetion);
  void MakeAnimation(float width, float height, int column_count, int row_count,
                     sh::Vector2 offset = sh::Vector2());
  void PushRectangle(sh::Rectangle rectangle);
  
  bool Initialize();
  void Update();
private:
  std::vector<sh::Rectangle> rectangles_;
  unsigned int index_;
  unsigned int rate_;
  unsigned int count_;
};
}
#endif // !SH_ANIMATION_H