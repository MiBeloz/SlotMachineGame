#include "label.h"


Label::Label(const std::string& text, const sf::Font& font, unsigned int fontSize, const sf::Vector2f& position) {
    m_text.setString(text);
    m_text.setFont(font);
    m_text.setCharacterSize(fontSize);
    m_text.setPosition(position);
}

void Label::draw(sf::RenderWindow& window) const {
    window.draw(m_text);
}

void Label::setText(const std::string& text) {
    m_text.setString(text);
}

void Label::clear() {
    m_text.setString("");
}
