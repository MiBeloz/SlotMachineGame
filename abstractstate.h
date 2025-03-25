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
        std::vector<Button>& buttons,
        std::vector<Reel>& reels,
        std::vector<Label>& labels,
        ScoreLabel& scoreLabel,
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
    std::vector<Button>& m_buttons;
    std::vector<Reel>& m_reels;
    std::vector<Label>& m_labels;
    ScoreLabel& m_scoreLabel;
    std::function<void()> m_nextStateFunction;
};

#endif // ABSTRACTSTATE_H
