#ifndef LABEL_H
#define LABEL_H

#include <SFML/Graphics.hpp>
#include <mutex>


class Label {
public:
    explicit Label(const std::string& text, const sf::Font& font, unsigned int fontSize, const sf::Vector2f& position);

    virtual ~Label() {}

    Label(const Label&) = delete;
    Label(Label&&) noexcept = delete;
    Label& operator=(const Label&) = delete;
    Label& operator=(Label&&) noexcept = delete;

    virtual void draw(sf::RenderWindow& window) const;

    void setText(const std::string& text);

    void clear();

protected:
    sf::Text m_text;
    std::mutex m_mutex;
};

#endif // LABEL_H
