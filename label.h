#ifndef LABEL_H
#define LABEL_H

#include <SFML/Graphics.hpp>


class Label {
public:
    explicit Label(const std::string& text, const sf::Font& font, unsigned int fontSize, const sf::Vector2f& position);

    virtual ~Label() {}

    Label(const Label&) = default;
    Label(Label&&) noexcept = default;
    Label& operator=(const Label&) = default;
    Label& operator=(Label&&) noexcept = default;

    virtual void draw(sf::RenderWindow& window) const;

    void setText(const std::string& text);

    void clear();

protected:
    sf::Text m_text;
};

#endif // LABEL_H
