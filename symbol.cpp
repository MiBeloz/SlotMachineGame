#include "symbol.h"


Symbol::Symbol(size_t id, const sf::Texture& texture) : m_id(id) {
    m_sprite.setTexture(texture);
}

Symbol::Symbol(Symbol&& other) noexcept : m_id(other.m_id), m_sprite(std::move(other.m_sprite)) {
    other.m_id = 0;
}

Symbol& Symbol::operator=(Symbol&& other) noexcept {
    if (this != &other) {
        m_id = other.m_id;
        m_sprite = std::move(other.m_sprite);
        other.m_id = 0;
    }
    return *this;
}

const sf::Sprite& Symbol::getSprite() const {
    return m_sprite;
}

sf::Sprite& Symbol::getSprite() {
    return m_sprite;
}

size_t Symbol::getId() const {
    return m_id;
}
