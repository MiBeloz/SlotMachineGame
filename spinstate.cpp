#include "spinstate.h"


SpinState::SpinState(
    std::vector<Button>& buttons,
    std::vector<Reel>& reels,
    std::vector<Label>& labels,
    ScoreLabel& scoreLabel,
    const std::function<void()>& nextStateFunction)
    :
    AbstractState(buttons, reels, labels, scoreLabel, nextStateFunction),
    stop_flag(false)
{}

void SpinState::enter() {
    m_buttons[Buttons::start].setEnabled(false);
    m_buttons[Buttons::stop].setEnabled(true);
    stop_flag = false;

    for (size_t i = 0; i < m_reels.size(); ++i) {
        m_reels[i].spin(getRandomNumber(1500, 2500));
    }

    m_clock.restart().asSeconds();
    std::thread t([this](){
        while (!stop_flag) {
            int elapsedSeconds = m_clock.getElapsedTime().asSeconds();
            if (elapsedSeconds > SECONDS_TO_STOP) {
                update();
                break;
            }

            m_labels[Labels::statusBar].setText("Autostop in " + std::to_string(SECONDS_TO_STOP - elapsedSeconds) + " seconds");
        }
    });
    t.detach();
}

void SpinState::update() {
    m_buttons[Buttons::start].setEnabled(false);
    m_buttons[Buttons::stop].setEnabled(false);
    stop_flag = true;
    for (size_t i = 0; i < m_reels.size(); ++i) {
        m_reels[i].stop(1.0f * (i + 1));
    }

    if (m_nextStateFunction) {
        m_nextStateFunction();
    }
}

void SpinState::end() {
    m_buttons[Buttons::start].reset();
    m_buttons[Buttons::stop].reset();
    m_labels[Labels::win_loss].clear();
    m_labels[Labels::statusBar].clear();
}

void SpinState::handleEvent(const sf::Event& event, const sf::RenderWindow& window) {
    m_buttons[Buttons::stop].handleEvent(event, window);
    if (m_buttons[Buttons::stop].isClicked()) {
        update();
    }
}

int SpinState::getRandomNumber(int min, int max) {
    static std::mt19937 mt{ std::random_device{}() };
    std::uniform_int_distribution<int> dist(min, max);
    return dist(mt);
}
