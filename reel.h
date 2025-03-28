#ifndef REEL_H
#define REEL_H

#include <SFML/Graphics.hpp>
#include <mutex>

#include "symbol.h"


class Reel final {
public:
    explicit Reel(std::vector<Symbol>& symbols, const sf::Vector2f& position);

    ~Reel() {}

    Reel(const Reel&) = delete;
    Reel(Reel&&) noexcept = delete;
    Reel& operator=(const Reel&) = delete;
    Reel& operator=(Reel&&) noexcept = delete;

    void spin(float speed = 2000.0f);

    void stop(float decelerationTime = 1.0f);

    void update(float deltaTime);

    void draw(sf::RenderWindow& window) const;

    bool isSpining() const;

    size_t getSymbolId() const;

private:
    std::vector<Symbol> m_symbols;
    sf::Vector2f m_position;

    bool m_spining;
    float m_offset;
    float m_speed;
    float m_decelerationTime;
    float m_remainingDecelerationTime;
    bool m_isDecelerating;
    float m_initialSpeed;
    float m_centerY;

    size_t m_symbolId;

    std::mutex m_mutex;

    void transparencyControl(Symbol& symbol);
};

#endif // REEL_H
