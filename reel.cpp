#include <limits>

#include "reel.h"


Reel::Reel(std::vector<Symbol>& symbols, const sf::Vector2f& position) :
    m_symbols(symbols),
    m_position(position),
    m_spining(false),
    m_offset(0),
    m_speed(0),
    m_decelerationTime(0),
    m_remainingDecelerationTime(0),
    m_isDecelerating(false),
    m_initialSpeed(0)
{
    int symbolHeight = symbols[0].getSprite().getTexture()->getSize().y;
    m_centerY = position.y + 1.5f * symbolHeight;

    for (size_t i = 0; i < symbols.size(); ++i) {
        m_symbols[i].getSprite().setPosition(position.x, position.y + i * symbolHeight);
    }

    for (auto& symbol : m_symbols) {
        float spriteCenterY = symbol.getSprite().getPosition().y + symbol.getSprite().getGlobalBounds().height / 2.0f;
        float distanceToCenter = std::abs(spriteCenterY - m_centerY);

        float alpha = 255.0f * (1.0f - distanceToCenter / (m_symbols[0].getSprite().getGlobalBounds().height * 1.5f));
        alpha = std::clamp(alpha, 0.0f, 255.0f);
        symbol.getSprite().setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(alpha)));
    }
}

void Reel::spin(float speed) {
    m_spining = true;
    m_speed = speed;
    m_isDecelerating = false;
}

void Reel::stop(float decelerationTime) {
    if (m_spining && !m_isDecelerating) {
        m_isDecelerating = true;
        m_initialSpeed = m_speed;
        m_decelerationTime = decelerationTime;
        m_remainingDecelerationTime = decelerationTime;
    }
}

void Reel::update(float deltaTime) {
    if (m_spining) {
        if (m_isDecelerating) {
            m_remainingDecelerationTime -= deltaTime;

            if (m_remainingDecelerationTime > 0 && m_remainingDecelerationTime > 0.2f) {
                float t = m_remainingDecelerationTime / m_decelerationTime;
                m_speed = m_initialSpeed * t;
            }
            else if (m_remainingDecelerationTime > 0 && m_remainingDecelerationTime < 0.2f) {
                size_t m_closestSymbolIndex = 0;
                float minDistance = std::numeric_limits<float>::max();

                for (size_t i = 0; i < m_symbols.size(); ++i) {
                    float spriteCenterY = m_symbols[i].getSprite().getPosition().y + m_symbols[i].getSprite().getGlobalBounds().height / 2.0f;
                    float distanceToCenter = std::abs(spriteCenterY - m_centerY);

                    if (distanceToCenter < minDistance) {
                        minDistance = distanceToCenter;
                        m_closestSymbolIndex = i;
                    }
                }

                float closestSymbolCenterY = m_symbols[m_closestSymbolIndex].getSprite().getPosition().y +
                                             m_symbols[m_closestSymbolIndex].getSprite().getGlobalBounds().height / 2.0f;

                if (std::abs(m_centerY - closestSymbolCenterY) < 1.0f) {
                    m_speed = 0;
                    m_spining = false;
                    m_isDecelerating = false;
                    m_symbolId = m_symbols[m_closestSymbolIndex].getId();
                }
                else {
                    m_remainingDecelerationTime += deltaTime;
                    float t = m_remainingDecelerationTime / m_decelerationTime;
                    m_speed = m_initialSpeed * t;
                }
            }
        }

        m_offset += m_speed * deltaTime;

        if (m_offset >= m_symbols[0].getSprite().getGlobalBounds().height) {
            m_offset = 0;

            Symbol lastSymbol = m_symbols.back();
            m_symbols.pop_back();
            m_symbols.insert(m_symbols.begin(), lastSymbol);

            float symbolHeight = m_symbols[0].getSprite().getGlobalBounds().height;
            for (size_t i = 0; i < m_symbols.size(); ++i) {
                if (i == 0) {
                    m_symbols[i].getSprite().setPosition(m_position.x, m_position.y - symbolHeight / 2);
                }
                else {
                    m_symbols[i].getSprite().setPosition(m_position.x, m_position.y + (i - 0.5f) * symbolHeight);
                }
            }
        }

        for (auto& symbol : m_symbols) {
            symbol.getSprite().move(0, m_speed * deltaTime);

            float spriteCenterY = symbol.getSprite().getPosition().y + symbol.getSprite().getGlobalBounds().height / 2.0f;
            float distanceToCenter = std::abs(spriteCenterY - m_centerY);

            float alpha = 255.0f * (1.0f - distanceToCenter / (m_symbols[0].getSprite().getGlobalBounds().height * 1.5f));
            alpha = std::clamp(alpha, 0.0f, 255.0f);
            symbol.getSprite().setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(alpha)));
        }
    }
}

void Reel::draw(sf::RenderWindow& window) const {
    for (size_t i = 0; i < m_symbols.size(); ++i) {
        window.draw(m_symbols[i].getSprite());
    }
}

bool Reel::isSpining() const {
    return m_spining;
}

size_t Reel::getSymbolId() const {
    return m_symbols[0].getId();;
}
