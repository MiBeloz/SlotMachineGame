#include "finishstate.h"


FinishState::FinishState(
    std::vector<Button>& buttons,
    std::vector<Reel>& reels,
    std::vector<Label>& labels,
    ScoreLabel& scoreLabel,
    const std::function<void()>& nextStateFunction)
    :
    AbstractState(buttons, reels, labels, scoreLabel, nextStateFunction)
{}

void FinishState::enter() {
    std::thread t([this](){
        for (size_t i = 0; i < m_reels.size(); ++i) {
            while (m_reels[i].isSpining()) {
                continue;
            }
        }
        update();
    });
    t.detach();
}

void FinishState::update() {
    std::vector<size_t> res;
    for (size_t i = 0; i < m_reels.size(); ++i) {
        res.push_back(m_reels[i].getSymbolId());
    }

    std::vector<size_t> symbolsCount(res.size());
    for (size_t i = 0; i < symbolsCount.size(); ++i) {
        for (size_t j = 0; j < res.size(); ++j) {
            if (res[j] == i + 1) {
                symbolsCount[i] += 1;
            }
        }
    }

    bool win = false;
    int points = 0;
    for (size_t i = 0; i < symbolsCount.size(); ++i) {
        if (symbolsCount[i] == 5) {
            win = true;
            points = 800;
            break;
        }
        else if (symbolsCount[i] == 4) {
            win = true;
            points = 500;
            break;
        }
        else if (symbolsCount[i] == 3) {
            win = true;
            points = 300;
            break;
        }
        else {
            points = -300;
        }
    }
    m_scoreLabel.addPoints(points);
    m_labels[Labels::statusBar].setText(std::to_string(points));

    if (!win) {
        m_labels[Labels::win_loss].setText("LOSS :(");
    }
    else {
        m_labels[Labels::win_loss].setText("WIN!!!");
    }

    if (m_nextStateFunction) {
        m_nextStateFunction();
    }
}

void FinishState::end() {
    m_buttons[Buttons::start].reset();
    m_buttons[Buttons::stop].reset();
}
