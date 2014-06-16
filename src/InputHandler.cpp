#include "InputHandler.hpp"
using namespace My;
InputHandler::InputHandler(sf::RenderWindow& window, My::Player& player, sf::Time& deltaTime)
	: r_Window(window)
	, r_Player(player)
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
	, a_Idle(!a_kD && !a_kA && !a_kW && !a_kSpace && !a_kJ)
	, t_Delta(deltaTime)
{

}
InputHandler::~InputHandler()
{
	//m_callSys.clearAllConnections();
	//m_actMap.clearActions();
	//m_actMap.clearEvents();
}
void InputHandler::LoadBindings()
{
    m_actMap["exit"] = a_wExit || a_kEscape;
    m_actMap["walkL"] = a_kA;
    m_actMap["walkR"] = a_kD;
    m_actMap["punch"] = a_kJ;
	//m_actMap["idle"] = a_Idle;
	m_actMap["jump"] = (a_kW || a_kSpace);
	m_actMap["setVSyncON"] = a_kF1;
	m_actMap["setVSyncOFF"] = a_kF2;
	m_actMap["setFPS30"] = a_kF3;
	m_actMap["setFPS60"] = a_kF4;
	m_actMap["setFPSunlimited"] = a_kF5;
    m_callSys.connect("exit", std::bind(&sf::Window::close, &r_Window));
	m_callSys.connect("walkL", std::bind(&Player::GoLeft, &r_Player, std::ref(t_Delta)));
	m_callSys.connect("walkR", std::bind(&Player::GoRight, &r_Player, std::ref(t_Delta)));
	m_callSys.connect("punch", std::bind(&Player::Punch, &r_Player));
	//m_callSys.connect("idle", std::bind(&Player::Idle, &r_Player));
	m_callSys.connect("jump", std::bind(&Player::StartJump, &r_Player));
	m_callSys.connect("setVSyncOn", std::bind(&sf::RenderWindow::setVerticalSyncEnabled, &r_Window, true)); ///< \bug setVerticalSyncEnabled is not set to true
	m_callSys.connect("setVSyncOff", std::bind(&sf::RenderWindow::setVerticalSyncEnabled, &r_Window, false)); ///< \bug setVerticalSyncEnable is not set to false
	m_callSys.connect("setFPS30", std::bind(&sf::RenderWindow::setFramerateLimit, &r_Window, 30));
	m_callSys.connect("setFPS60", std::bind(&sf::RenderWindow::setFramerateLimit, &r_Window, 60));
	m_callSys.connect("setFPSunlimited", std::bind(&sf::RenderWindow::setFramerateLimit, &r_Window, 0));
}
void InputHandler::UpdateAndInvoke()
{
    m_actMap.update(r_Window);
    m_actMap.invokeCallbacks(m_callSys, &r_Window);
}
