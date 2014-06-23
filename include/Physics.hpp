#ifndef PHYSICS_HPP
#define PHYSICS_HPP
#include <SFML/Graphics.hpp>
namespace My
{
class Physics
{
public:
    Physics(sf::Vector2f Velocity, sf::Vector2f Acceleration, unsigned int Floor);
    virtual ~Physics();
    sf::Vector2f NextPosition(sf::Vector2f prevPosition, sf::Time& delta);
    void Impulse(sf::Vector2f Impulse);
    void SetFloor(unsigned int Floor);
    sf::Vector2f GetAccel();
    sf::Vector2f GetVelocity();
    float GetFloor();
    void ResetVelocity();
    bool InAir(float y);
private:
    sf::Vector2f m_Vel;
    sf::Vector2f m_Acc;
    unsigned int m_Floor;
    bool m_inAir;
};
}
#endif
