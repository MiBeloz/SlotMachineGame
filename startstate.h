#ifndef STARTSTATE_H
#define STARTSTATE_H

#include "abstractstate.h"


class StartState : public AbstractState {
public:
    explicit StartState(
        std::vector<Button>& buttons,
        std::vector<Reel>& reels,
        std::vector<Label>& labels,
        ScoreLabel& scoreLabel,
        const std::function<void()>& nextStateFunction);

    void enter() override;

    void update() override;

    void end() override;

    void handleEvent(const sf::Event& event, const sf::RenderWindow& window) override;
};

#endif // STARTSTATE_H
