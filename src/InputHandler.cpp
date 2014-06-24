#include "InputHandler.hpp"
using namespace My;
InputHandler::InputHandler(sf::RenderWindow& window, My::Player& player1, My::Player& player2, sf::Time& deltaTime)
    : r_Window(window)
    , r_Player1(player1)
    , r_Player2(player2)
    , a_wExit(sf::Event::Closed)
    , a_kEscape(sf::Keyboard::Escape, thor::Action::PressOnce)
    , a_kD(sf::Keyboard::D, thor::Action::Hold)
    , a_kA(sf::Keyboard::A, thor::Action::Hold)
    , a_kJ(sf::Keyboard::J, thor::Action::PressOnce)
    , a_kW(sf::Keyboard::W, thor::Action::PressOnce)
    , a_kSpace(sf::Keyboard::Space, thor::Action::PressOnce)
    , a_kF1(sf::Keyboard::F1, thor::Action::PressOnce)
    , a_kF2(sf::Keyboard::F2, thor::Action::PressOnce)
    , a_kF3(sf::Keyboard::F3, thor::Action::PressOnce)
    , a_kF4(sf::Keyboard::F4, thor::Action::PressOnce)
    , a_kF5(sf::Keyboard::F5, thor::Action::PressOnce)
    , a_kUp(sf::Keyboard::Up, thor::Action::PressOnce)
    , a_kDown(sf::Keyboard::Down, thor::Action::PressOnce)
    , a_kLeft(sf::Keyboard::Left, thor::Action::Hold)
    , a_kRight(sf::Keyboard::Right, thor::Action::Hold)
    , a_kCtrl(sf::Keyboard::RControl, thor::Action::PressOnce)
    , t_Delta(deltaTime)
{

}
InputHandler::~InputHandler()
{
    m_callSys.clearAllConnections();
    m_actMap.clearActions();
    m_actMap.clearEvents();
}
void InputHandler::LoadBindings()
{
    m_actMap["exit"] = a_wExit || a_kEscape;
    m_actMap["walkL1"] = a_kA;
    m_actMap["walkR1"] = a_kD;
    m_actMap["punch1"] = a_kJ;
    m_actMap["jump1"] = (a_kW || a_kSpace);
    m_actMap["walkL2"] = a_kLeft;
    m_actMap["walkR2"] = a_kRight;
    m_actMap["punch2"] = a_kCtrl;
    m_actMap["jump2"] = a_kUp;
    m_actMap["setVSyncON"] = a_kF1;
    m_actMap["setVSyncOFF"] = a_kF2;
    m_actMap["setFPS30"] = a_kF3;
    m_actMap["setFPS60"] = a_kF4;
    m_actMap["setFPSunlimited"] = a_kF5;
    m_callSys.connect("exit", std::bind(&sf::RenderWindow::close, &r_Window));
    m_callSys.connect("walkL1", std::bind(&Player::GoLeft, &r_Player1, std::ref(t_Delta)));
    m_callSys.connect("walkR1", std::bind(&Player::GoRight, &r_Player1, std::ref(t_Delta)));
    m_callSys.connect("punch1", std::bind(&Player::Punch, &r_Player1));
    m_callSys.connect("jump1", std::bind(&Player::StartJump, &r_Player1));
    m_callSys.connect("walkL2", std::bind(&Player::GoLeft, &r_Player2, std::ref(t_Delta)));
    m_callSys.connect("walkR2", std::bind(&Player::GoRight, &r_Player2, std::ref(t_Delta)));
    m_callSys.connect("punch2", std::bind(&Player::Punch, &r_Player2));
    m_callSys.connect("jump2", std::bind(&Player::StartJump, &r_Player2));
    m_callSys.connect("setVSyncOn", std::bind(&sf::RenderWindow::setVerticalSyncEnabled, &r_Window, true)); ///< \bug setVerticalSyncEnabled is not set to true
    m_callSys.connect("setVSyncOff", std::bind(&sf::RenderWindow::setVerticalSyncEnabled, &r_Window, false)); ///< \bug setVerticalSyncEnable is not set to false
    m_callSys.connect("setFPS30", std::bind(&sf::RenderWindow::setFramerateLimit, &r_Window, 30));
    m_callSys.connect("setFPS60", std::bind(&sf::RenderWindow::setFramerateLimit, &r_Window, 60));
    m_callSys.connect("setFPSunlimited", std::bind(&sf::RenderWindow::setFramerateLimit, &r_Window, 0));
}
void InputHandler::RemoveBindings()
{
    m_callSys.clearAllConnections();
}
void InputHandler::UpdateAndInvoke()
{
    m_actMap.update(r_Window);
    m_actMap.invokeCallbacks(m_callSys, &r_Window);
}
