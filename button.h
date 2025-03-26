#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <mutex>


class Button {
public:
    explicit Button(const std::string& text,
                    const sf::Font& font,
                    unsigned int fontSize,
                    const sf::Vector2f& position,
                    const sf::Vector2f& size = sf::Vector2f(150, 50));

    virtual ~Button() {}

    Button(const Button& other) = delete;
    Button(Button&& other) noexcept = delete;
    Button& operator=(const Button& other) = delete;
    Button& operator=(Button&& other) noexcept = delete;

    void setPosition(const sf::Vector2f& position);

    void setEnabled(bool enabled);

    bool isEnabled() const;

    void draw(sf::RenderWindow& window) const;

    virtual bool isMouseOver(const sf::RenderWindow& window) const;

    bool isClicked() const;

    void reset();

    virtual void handleEvent(const sf::Event& event, const sf::RenderWindow& window);

protected:
    sf::RectangleShape m_shape;
    sf::Text m_label;
    bool m_isClicked;
    bool m_enabled;

    std::mutex m_mutex;

    static inline const sf::Color LightGray = sf::Color(225, 225, 225);
    static inline const sf::Color DarkGray = sf::Color(120, 120, 120);
    static inline const sf::Color Gray = sf::Color(204, 204, 204);
};

#endif // BUTTON_H
