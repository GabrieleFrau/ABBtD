#ifndef GAME_HPP
#define GAME_HPP
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <Thor/Graphics.hpp>
#include <Thor/Animation.hpp>
#include <Thor/Input.hpp>
#include <Resources.h>
#include <Form.hpp>
#include <ResourceHandler.hpp>
#include <Player.hpp>
#include <InputHandler.hpp>
class Game
{
public:
    Game();
    virtual ~Game();
    int Run();
protected:
private:
    void ResourceLoad();
    void PopulateMap();
    sf::RenderWindow w_Window;
    sf::Font f_Font;
    My::ResourceHandler m_Resource;
    My::Form m_Form;
    My::Player m_Player1,m_Player2;
    sf::Time m_DeltaTime;
    My::InputHandler m_Input;
};
#endif // GAME_HPP
