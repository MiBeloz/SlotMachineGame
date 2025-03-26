#ifndef FINISHSTATE_H
#define FINISHSTATE_H

#include <thread>

#include "abstractstate.h"


class FinishState : public AbstractState {
public:
    explicit FinishState(
        std::vector<std::unique_ptr<Button>>& buttons,
        std::vector<std::unique_ptr<Reel>>& reels,
        std::vector<std::unique_ptr<Label>>& labels,
        std::unique_ptr<ScoreLabel>& scoreLabel,
        const std::function<void()>& nextStateFunction);

    void enter() override;

    void update() override;

    void end() override;

    void handleEvent(const sf::Event& event, const sf::RenderWindow& window) override {}
};

#endif // FINISHSTATE_H
