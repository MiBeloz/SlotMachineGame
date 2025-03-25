#ifndef SLOTMACHINEGAME_H
#define SLOTMACHINEGAME_H

#include <utility>

#include "startstate.h"
#include "spinstate.h"
#include "finishstate.h"


#define REELS_COUNT 5

class SlotMachineGame {
public:
    explicit SlotMachineGame(const sf::VideoMode& videoMode, const sf::Font& font, const sf::Texture& backgroundTexture, std::vector<Symbol>& symbols);

    SlotMachineGame(const SlotMachineGame&) = delete;
    SlotMachineGame(SlotMachineGame&&) noexcept = delete;
    SlotMachineGame& operator=(const SlotMachineGame&) = delete;
    SlotMachineGame& operator=(SlotMachineGame&&) noexcept = delete;

    void show();

private:
    sf::RenderWindow m_window;
    sf::Sprite m_background;
    std::vector<Button> m_buttons;
    std::vector<Reel> m_reels;
    std::vector<Label> m_labels;
    std::unique_ptr<ScoreLabel> m_scoreLabel;
    std::vector<std::unique_ptr<AbstractState>> m_states;
    size_t m_currentStateIndex;
};

#endif // SLOTMACHINEGAME_H
