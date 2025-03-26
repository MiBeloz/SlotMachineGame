#ifndef STARTSTATE_H
#define STARTSTATE_H

#include "abstractstate.h"


class StartState : public AbstractState {
public:
    explicit StartState(
        std::vector<std::unique_ptr<Button>>& buttons,
        std::vector<std::unique_ptr<Reel>>& reels,
        std::vector<std::unique_ptr<Label>>& labels,
        std::unique_ptr<ScoreLabel>& scoreLabel,
        const std::function<void()>& nextStateFunction);

    void enter() override;

    void update() override;

    void end() override;

    void handleEvent(const sf::Event& event, const sf::RenderWindow& window) override;
};

#endif // STARTSTATE_H
