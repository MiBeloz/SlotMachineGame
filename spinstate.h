#ifndef SPINSTATE_H
#define SPINSTATE_H

#include <random>
#include <thread>
#include <atomic>

#include "abstractstate.h"


#define SECONDS_TO_STOP 10

class SpinState : public AbstractState {
public:
    explicit SpinState(
        std::vector<std::unique_ptr<Button>>& buttons,
        std::vector<std::unique_ptr<Reel>>& reels,
        std::vector<std::unique_ptr<Label>>& labels,
        std::unique_ptr<ScoreLabel>& scoreLabel,
        const std::function<void()>& nextStateFunction);

    void enter() override;

    void update() override;

    void end() override;

    void handleEvent(const sf::Event& event, const sf::RenderWindow& window) override;

    static int getRandomNumber(int min, int max);

private:
    sf::Clock m_clock;
    std::atomic<bool> stop_flag;
};

#endif // SPINSTATE_H
