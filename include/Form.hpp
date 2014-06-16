#ifndef FORM_HPP
#define FORM_HPP
#include <SFML/Window.hpp>
#include <SFML/Audio/Music.hpp>
#include <TGUI/TGUI.hpp>
#include <Resources.h>
namespace My
{
class Form
{
public:
    Form(sf::RenderWindow& window);
    bool Run();
    virtual ~Form();
protected:
private:
    sf::RenderWindow& r_Window;
    tgui::Gui m_Gui;
    tgui::AnimatedPicture::Ptr ptr_AniBack;
    tgui::Button::Ptr ptr_BtnStart;
    tgui::Button::Ptr ptr_BtnExit;
};
}
#endif // FORM_HPP
