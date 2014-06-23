#include "Game.hpp"
Game::Game()
    : w_Window(sf::VideoMode(800,600), "Another byte bites dust - MENU", sf::Style::Default)
    , m_Form(w_Window)
    , m_Player(m_Resource)
    , m_Input(w_Window, m_Player, m_DeltaTime)
{
    f_Font.loadFromFile(RESOURCE_FONT_PATH);
    m_Resource.Load();
}
Game::~Game()
{
}
int Game::Run()
{
    if(m_Form.Run())
    {
        w_Window.create(sf::VideoMode(800,600), "Another byte bites dust - GAME", sf::Style::Titlebar);
        m_Input.LoadBindings();
        w_Window.setKeyRepeatEnabled(false);
        sf::Listener::setPosition(static_cast<float>(w_Window.getSize().x / 2), 0.f, 0);
        sf::Listener::setDirection(0, 0, 0);
        sf::Listener::setGlobalVolume(100);
        sf::Text menuText("F1: VSYNC ON\tF2: VSYNC OFF\t F3: FPS to 30\tF4: FPS to 60\tF5: unlimited FPS", f_Font, 10);
        sf::Text fpsText;
        fpsText.setPosition(menuText.getPosition().x, menuText.getPosition().y + menuText.getCharacterSize() * 1.5f);
        fpsText.setFont(f_Font);
        sf::Text physxText;
        physxText.setPosition(fpsText.getPosition().x, fpsText.getPosition().y + fpsText.getCharacterSize() * 1.5f);
        physxText.setFont(f_Font);

        sf::Vector2f rectSize(static_cast<float>(w_Window.getSize().x), static_cast<float>(w_Window.getSize().y / 3));
        sf::RectangleShape rect(rectSize);
        sf::Texture texMonitor;
        texMonitor.loadFromFile(RESOURCE_MONITOR);
        rect.setTexture(&texMonitor, true);
        rect.setPosition(0.f, static_cast<float>(rectSize.y * 2));
        sf::Sprite background;
        sf::Texture texBackground;
        texBackground.loadFromFile(RESOURCE_BACKGROUND);
        background.setTexture(texBackground);

        m_Player.Init(static_cast<float>(w_Window.getSize().x / 2 - 200), 0.f, rect.getPosition().y);
        My::Player dummy(m_Resource);
        dummy.Init(static_cast<float>(w_Window.getSize().x / 2 + 200), 0.f, rect.getPosition().y);
        m_Player.SetOtherPlayer(&dummy);
        dummy.SetOtherPlayer(&m_Player);
        unsigned int fps = 0;


        sf::Clock fpsClock;
        sf::Clock clock;

        while (w_Window.isOpen())
        {
            m_DeltaTime = clock.restart();
            m_Input.UpdateAndInvoke();
            m_Player.UpdateAndAnimate(m_DeltaTime);
            dummy.UpdateAndAnimate(m_DeltaTime);
#ifdef DEBUG
            std::string acc(std::to_string(m_Player.GetAccel().y));
            std::string vel(std::to_string(m_Player.GetVelocity().y));
            std::string del(std::to_string(m_DeltaTime.asSeconds()));
#endif
            physxText.setString("Base Acceleration(px/s): " + acc + "\nAcceleration(px/s): " + vel + "\nDelta time: " + del);
            w_Window.clear(sf::Color::Blue);
            w_Window.draw(background);
            w_Window.draw(rect);
#ifdef DEBUG
            {
                w_Window.draw(menuText);
                w_Window.draw(fpsText);
                w_Window.draw(physxText);
            }
#endif
            w_Window.draw(m_Player);
            w_Window.draw(dummy);
            w_Window.display();
            ++fps;
            if (fpsClock.getElapsedTime().asMilliseconds() >= 1000)
            {
                fpsText.setColor((fps < 30) ? (sf::Color::Red) : (fps < 60) ? (sf::Color::Yellow) : (sf::Color::Green));
                fpsText.setString(std::to_string(fps));
                fps = 0;
                fpsClock.restart();
            }
        }
    }
    return 0;
}
