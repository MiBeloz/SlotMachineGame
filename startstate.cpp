#include "startstate.h"


StartState::StartState(
    std::vector<std::unique_ptr<Button>>& buttons,
    std::vector<std::unique_ptr<Reel>>& reels,
    std::vector<std::unique_ptr<Label>>& labels,
    std::unique_ptr<ScoreLabel>& scoreLabel,
    const std::function<void()>& nextStateFunction)
    :
    AbstractState(buttons, reels, labels, scoreLabel, nextStateFunction)
{}

void StartState::enter() {
    m_buttons[Buttons::start]->setEnabled(true);
    m_buttons[Buttons::stop]->setEnabled(false);
}

void StartState::update() {
    if (m_nextStateFunction) {
        m_nextStateFunction();
    }
}

void StartState::end() {
    m_buttons[Buttons::start]->reset();
    m_buttons[Buttons::stop]->reset();
    m_labels[Labels::win_loss]->clear();
    m_labels[Labels::statusBar]->clear();
}

void StartState::handleEvent(const sf::Event& event, const sf::RenderWindow& window) {
    m_buttons[Buttons::start]->handleEvent(event, window);
    if (m_buttons[Buttons::start]->isClicked()) {
        update();
    }
}
