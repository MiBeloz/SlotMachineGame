#ifndef FINISHSTATE_H
#define FINISHSTATE_H

#include <thread>

#include "abstractstate.h"


class FinishState : public AbstractState {
public:
    explicit FinishState(
        std::vector<Button>& buttons,
        std::vector<Reel>& reels,
        std::vector<Label>& labels,
        ScoreLabel& scoreLabel,
        const std::function<void()>& nextStateFunction);

    void enter() override;

    void update() override;

    void end() override;

    void handleEvent(const sf::Event& event, const sf::RenderWindow& window) override {}
};

#endif // FINISHSTATE_H
