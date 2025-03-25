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

Button::Button(Button&& other) noexcept :
    m_shape(std::move(other.m_shape)),
    m_label(std::move(other.m_label)),
    m_isClicked(other.m_isClicked),
    m_enabled(other.m_enabled)
{
    other.m_isClicked = false;
    other.m_enabled = true;
}

Button& Button::operator=(Button&& other) noexcept {
    if (this != &other) {
        m_shape = std::move(other.m_shape);
        m_label = std::move(other.m_label);
        m_isClicked = other.m_isClicked;
        m_enabled = other.m_enabled;
        other.m_isClicked = false;
        other.m_enabled = true;
    }
    return *this;
}

void Button::setPosition(const sf::Vector2f& position) {
    m_shape.setPosition(position);
    sf::FloatRect textBounds = m_label.getGlobalBounds();

    float textX = position.x + (m_shape.getSize().x - textBounds.width) / 2 - textBounds.left;
    float textY = position.y + (m_shape.getSize().y - textBounds.height) / 2 - textBounds.top;

    m_label.setPosition(textX, textY);
}

void Button::setEnabled(bool enabled) {
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
    m_isClicked = false;
    m_enabled = true;
}

void Button::handleEvent(const sf::Event& event, const sf::RenderWindow& window) {
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
