#ifndef SH_SCORE_H
#define SH_SCORE_H

#include <memory>
#include <array>

#include "Vector2.h"
#include "Rectangle.h"
#include "Texture.h"
#include "ResourceManager.h"

namespace sh {
class Score {
public:
    Score();
    ~Score();
    Score(const Score& rhs) = default;
    Score& operator=(const Score& rhs) = default;
    Score(Score&& rhs) noexcept = default;
    Score& operator= (Score&& rhs) noexcept = default;

    void AddScore(const int score);
    void AddPosition(const sh::Vector2 position);

    bool Initialize(sh::ResourceManager& r);
    bool Update(void);
    bool Render(void);
private:
    std::weak_ptr<sh::Texture> texture_;
    int score_;
    int count_score_;
    bool is_counted_;
    std::array<sh::Rectangle, 10> number_rectangles_;
    bool used_clear_scene_;
    sh::Vector2 position_;
};
}
#endif // !SH_SCORE_H