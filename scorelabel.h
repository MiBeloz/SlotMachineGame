#ifndef SCORELABEL_H
#define SCORELABEL_H

#include "label.h"


class ScoreLabel final : public Label {
public:
    explicit ScoreLabel(const std::string& text, const sf::Font& font, unsigned int fontSize, const sf::Vector2f& position);

    ~ScoreLabel() {}

    void draw(sf::RenderWindow& window) const override;

    void addPoints(size_t points);

    void reset();

private:
    int m_score;
};

#endif // SCORELABEL_H
