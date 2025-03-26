#ifndef ABSTRACTSTATE_H
#define ABSTRACTSTATE_H

#include <SFML/Graphics.hpp>
#include <functional>
#include <memory>

#include "button.h"
#include "reel.h"
#include "scorelabel.h"


enum Buttons {
    start,
    stop
};

enum Labels {
    win_loss,
    statusBar
};

class AbstractState {
public:
    explicit AbstractState(
        std::vector<std::unique_ptr<Button>>& buttons,
        std::vector<std::unique_ptr<Reel>>& reels,
        std::vector<std::unique_ptr<Label>>& labels,
        std::unique_ptr<ScoreLabel>& scoreLabel,
        const std::function<void()>& nextStateFunction)
        :
        m_buttons(buttons),
        m_reels(reels),
        m_labels(labels),
        m_scoreLabel(scoreLabel),
        m_nextStateFunction(nextStateFunction)
    {}

    virtual ~AbstractState() {}

    AbstractState(const AbstractState&) = delete;
    AbstractState(AbstractState&&) noexcept = delete;
    AbstractState& operator=(const AbstractState&) = delete;
    AbstractState& operator=(AbstractState&&) noexcept = delete;

    virtual void enter() = 0;
    virtual void update() = 0;
    virtual void end() = 0;
    virtual void handleEvent(const sf::Event& event, const sf::RenderWindow& window) = 0;

protected:
    std::vector<std::unique_ptr<Button>>& m_buttons;
    std::vector<std::unique_ptr<Reel>>& m_reels;
    std::vector<std::unique_ptr<Label>>& m_labels;
    std::unique_ptr<ScoreLabel>& m_scoreLabel;
    std::function<void()> m_nextStateFunction;
};

#endif // ABSTRACTSTATE_H
