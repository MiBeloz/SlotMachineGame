#include "slotmachinegame.h"


SlotMachineGame::SlotMachineGame(const sf::VideoMode& videoMode, const sf::Font& font, const sf::Texture& backgroundTexture, std::vector<Symbol>& symbols) {
    m_window.create(videoMode, "Slot Machine Game");
    m_background.setTexture(backgroundTexture);

    m_buttons.push_back(Button("Start", font, 24, sf::Vector2f(50, 440), sf::Vector2f(150, 50)));
    m_buttons.push_back(Button("Stop", font, 24, sf::Vector2f(50, 500), sf::Vector2f(150, 50)));

    for (int i = 0; i < REELS_COUNT; ++i) {
        m_reels.push_back(Reel(symbols, sf::Vector2f(75 + i * 105, 10)));
    }

    m_labels.push_back(Label("", font, 100, sf::Vector2f(350, 350)));
    m_labels.push_back(Label("", font, 30, sf::Vector2f(350, 500)));
    m_scoreLabel = std::make_unique<ScoreLabel>("$", font, 24, sf::Vector2f(50, 560));

    m_currentStateIndex = 0;
    auto nextStateFunction = [&]{
        m_states[m_currentStateIndex]->end();
        ++m_currentStateIndex;
        if (m_currentStateIndex >= m_states.size()) {
            m_currentStateIndex = 0;
        }
        m_states[m_currentStateIndex]->enter();
    };

    m_states.emplace_back(std::make_unique<StartState>(m_buttons, m_reels, m_labels, *m_scoreLabel, nextStateFunction));
    m_states.emplace_back(std::make_unique<SpinState>(m_buttons, m_reels, m_labels, *m_scoreLabel, nextStateFunction));
    m_states.emplace_back(std::make_unique<FinishState>(m_buttons, m_reels, m_labels, *m_scoreLabel, nextStateFunction));
    m_states[m_currentStateIndex]->enter();
}

void SlotMachineGame::show() {
    sf::Clock clock;
    while (m_window.isOpen()) {
        sf::Event event;
        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                m_window.close();
            }
            m_states[m_currentStateIndex]->handleEvent(event, m_window);
        }

        m_window.clear();

        float deltaTime = clock.restart().asSeconds();
        for (auto& reel : m_reels) {
            reel.update(deltaTime);
        }

        m_window.draw(m_background);
        for (const auto& reel : std::as_const(m_reels)) {
            reel.draw(m_window);
        }
        m_buttons[Buttons::start].draw(m_window);
        m_buttons[Buttons::stop].draw(m_window);
        for (const auto& label : std::as_const(m_labels)) {
            label.draw(m_window);
        }
        m_scoreLabel->draw(m_window);

        m_window.display();
    }
}
