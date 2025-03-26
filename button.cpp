#include "button.h"


Button::Button(
    const std::string& text,
    const sf::Font& font,
    unsigned int fontSize,
    const sf::Vector2f& position,
    const sf::Vector2f& size)
    :
    m_isClicked(false), m_enabled(true)
{
    m_shape.setSize(size);
    m_label.setFont(font);
    m_label.setString(text);
    m_label.setCharacterSize(fontSize);
    m_label.setFillColor(sf::Color::Black);
    setPosition(position);
}

void Button::setPosition(const sf::Vector2f& position) {
    const std::lock_guard<std::mutex> lock(m_mutex);
    m_shape.setPosition(position);
    sf::FloatRect textBounds = m_label.getGlobalBounds();

    float textX = position.x + (m_shape.getSize().x - textBounds.width) / 2 - textBounds.left;
    float textY = position.y + (m_shape.getSize().y - textBounds.height) / 2 - textBounds.top;

    m_label.setPosition(textX, textY);
}

void Button::setEnabled(bool enabled) {
    const std::lock_guard<std::mutex> lock(m_mutex);
    m_enabled = enabled;
    if (m_enabled) {
        m_shape.setFillColor(LightGray);
        m_label.setFillColor(sf::Color::Black);
    }
    else {
        m_shape.setFillColor(Gray);
        m_label.setFillColor(DarkGray);
    }
}

bool Button::isEnabled() const {
    return m_enabled;
}

void Button::draw(sf::RenderWindow& window) const {
    window.draw(m_shape);
    window.draw(m_label);
}

bool Button::isMouseOver(const sf::RenderWindow& window) const {
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    return m_shape.getGlobalBounds().contains(mousePos);
}

bool Button::isClicked() const {
    return m_isClicked;
}

void Button::reset() {
    const std::lock_guard<std::mutex> lock(m_mutex);
    m_isClicked = false;
    m_enabled = true;
}

void Button::handleEvent(const sf::Event& event, const sf::RenderWindow& window) {
    const std::lock_guard<std::mutex> lock(m_mutex);
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        if (isMouseOver(window) && isEnabled()) {
            m_isClicked = true;
        }
    }

    if (event.type == sf::Event::MouseMoved && isEnabled()) {
        if (isMouseOver(window)) {
            m_shape.setFillColor(sf::Color(LightGray.r + 25, LightGray.g + 25, LightGray.b + 25));
        }
        else {
            m_shape.setFillColor(LightGray);
        }
    }
}
