#include "Form.hpp"
using namespace My;
Form::Form(sf::RenderWindow &window)
    : r_Window(window)
    , m_Gui(r_Window)
    , ptr_AniBack(m_Gui)
    , ptr_BtnStart(m_Gui)
    , ptr_BtnExit(m_Gui)
{
    ptr_AniBack->setTransparency(100);
    ptr_AniBack->addFrame(RESOURCE_BACKGROUND_FRAME_1, sf::seconds(1));
    ptr_AniBack->addFrame(RESOURCE_BACKGROUND_FRAME_2, sf::seconds(1));
    ptr_AniBack->setLooping();
    ptr_AniBack->play();
    m_Gui.setGlobalFont(RESOURCE_FONT_PATH);
    ptr_BtnStart->load(RESOURCE_THEME_PATH);
    ptr_BtnStart->setPosition(m_Gui.getSize().x / 2 - m_Gui.getSize().x / 24, m_Gui.getSize().y / 3 - m_Gui.getSize().y / 24);
    ptr_BtnStart->setText("Start");
    ptr_BtnStart->setCallbackId(0);
    ptr_BtnStart->bindCallback(tgui::Button::LeftMouseClicked);
    ptr_BtnStart->setSize(m_Gui.getSize().x / 12, m_Gui.getSize().y / 12);
    ptr_BtnExit->load(RESOURCE_THEME_PATH);
    ptr_BtnExit->setPosition(m_Gui.getSize().x / 2 - m_Gui.getSize().x / 24, m_Gui.getSize().y / 2 - m_Gui.getSize().y / 24);
    ptr_BtnExit->setText("Exit");
    ptr_BtnExit->setCallbackId(1);
    ptr_BtnExit->bindCallback(tgui::Button::LeftMouseClicked);
    ptr_BtnExit->setSize(m_Gui.getSize().x / 12, m_Gui.getSize().y / 12);
}
Form::~Form()
{
    m_Gui.removeAllWidgets();
}
bool Form::Run()
{
    bool play = false;
    sf::Music music;
    music.openFromFile(RESOURCE_MAINTHEME);
    music.setPlayingOffset(sf::seconds(3.f));
    music.play();
    sf::Event event;
    tgui::Callback callback;
    while (r_Window.isOpen())
    {
        while (r_Window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                r_Window.close();
            else
                m_Gui.handleEvent(event);

        while (m_Gui.pollCallback(callback))
        {
            if (callback.id == 0)
            {
                play = true;
                r_Window.close();
            }
            else if (callback.id == 1)
                r_Window.close();
        }
        r_Window.clear();
        m_Gui.draw();
        r_Window.display();
    }
    return play;
}
