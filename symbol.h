#ifndef SYMBOL_H
#define SYMBOL_H

#include <SFML/Graphics.hpp>


class Symbol {
public:
    explicit Symbol(size_t id, const sf::Texture& texture);

    Symbol(const Symbol& other) = default;

    Symbol(Symbol&& other) noexcept;

    Symbol& operator=(const Symbol& other) = default;

    Symbol& operator=(Symbol&& other) noexcept;

    const sf::Sprite& getSprite() const;

    sf::Sprite& getSprite();

    size_t getId() const;

private:
    size_t m_id;
    sf::Sprite m_sprite;
};

#endif // SYMBOL_H
