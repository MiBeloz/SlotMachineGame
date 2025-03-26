#include <utility>

#include "finishstate.h"


FinishState::FinishState(
    std::vector<std::unique_ptr<Button>>& buttons,
    std::vector<std::unique_ptr<Reel>>& reels,
    std::vector<std::unique_ptr<Label>>& labels,
    std::unique_ptr<ScoreLabel>& scoreLabel,
    const std::function<void()>& nextStateFunction)
    :
    AbstractState(buttons, reels, labels, scoreLabel, nextStateFunction)
{}

void FinishState::enter() {
    std::thread t([this](){
        for (const auto& reel : std::as_const(m_reels)) {
            while (reel->isSpining()) {
                continue;
            }
        }
        update();
    });
    t.detach();
}

void FinishState::update() {
    std::vector<size_t> res;
    for (const auto& reel : std::as_const(m_reels)) {
        res.push_back(reel->getSymbolId());
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
    for (const auto& symbolCount : std::as_const(symbolsCount)) {
        if (symbolCount == 5) {
            win = true;
            points = 800;
            break;
        }
        else if (symbolCount == 4) {
            win = true;
            points = 500;
            break;
        }
        else if (symbolCount == 3) {
            win = true;
            points = 300;
            break;
        }
        else {
            points = -300;
        }
    }
    m_scoreLabel->addPoints(points);
    m_labels[Labels::statusBar]->setText(std::to_string(points));

    if (!win) {
        m_labels[Labels::win_loss]->setText("LOSS :(");
    }
    else {
        m_labels[Labels::win_loss]->setText("WIN!!!");
    }

    if (m_nextStateFunction) {
        m_nextStateFunction();
    }
}

void FinishState::end() {
    m_buttons[Buttons::start]->reset();
    m_buttons[Buttons::stop]->reset();
}
