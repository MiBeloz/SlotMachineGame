#include "scorelabel.h"


ScoreLabel::ScoreLabel(const std::string &text, const sf::Font &font, unsigned int fontSize, const sf::Vector2f &position) :
    Label(text, font, fontSize, position), m_score(0) {}

void ScoreLabel::draw(sf::RenderWindow &window) const {
    sf::Text scoreText = m_text;
    std::string text = m_text.getString() + std::to_string(m_score);
    scoreText.setString(text);
    window.draw(scoreText);
}

void ScoreLabel::addPoints(size_t points) {
    const std::lock_guard<std::mutex> lock(m_mutex);
    m_score += points;
}

void ScoreLabel::reset() {
    const std::lock_guard<std::mutex> lock(m_mutex);
    m_score = 0;
}
