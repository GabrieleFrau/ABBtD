#ifndef INPUTHANDLER_HPP
#include <SFML/Graphics/RenderWindow.hpp>
#include <Thor/Input.hpp>
#include <Player.hpp>
namespace My
{
class InputHandler
{
public:
    InputHandler(sf::RenderWindow& window, My::Player& player, sf::Time& deltaTime);
    ~InputHandler();
    void LoadBindings();
    void UpdateAndInvoke();
private:
    sf::RenderWindow& r_Window;
    My::Player& r_Player;
    thor::Action a_wExit, a_kEscape, a_kD, a_kA, a_kJ, a_kW, a_kSpace, a_kF1, a_kF2, a_kF3, a_kF4, a_kF5;
    sf::Time& t_Delta;
    thor::ActionMap<std::string> m_actMap;
    thor::ActionMap<std::string>::CallbackSystem m_callSys;
};
}
#define INPUTHANDLER_HPP
#endif
