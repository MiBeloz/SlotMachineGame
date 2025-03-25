#include <SFML/Graphics.hpp>

#include "slotmachinegame.h"


int main() {
    sf::Font font;
    if (!font.loadFromFile("resources/segoepr.ttf")) {
        return -1;
    }

    std::vector<sf::Texture> symbolTextures;
    for (size_t i = 1; i <= 5; ++i) {
        sf::Texture texture;
        if (!texture.loadFromFile("resources/symbol" + std::to_string(i) + ".png")) {
            return -1;
        }
        symbolTextures.push_back(texture);
    }

    std::vector<Symbol> symbols;
    for (size_t i = 0; i < symbolTextures.size(); ++i) {
        symbols.push_back(Symbol(i + 1, symbolTextures[i]));
    }

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("resources/background.png")) {
        return -1;
    }

    SlotMachineGame game(sf::VideoMode(800, 600), font, backgroundTexture, symbols);
    game.show();

    return 0;
}
