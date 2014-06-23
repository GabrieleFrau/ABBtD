#include <Physics.hpp>
using namespace My;
Physics::Physics(sf::Vector2f Velocity, sf::Vector2f Acceleration, unsigned int Floor)
    : m_Vel(Velocity)
    , m_Acc(Acceleration)
    , m_Floor(Floor)
{

}
Physics::~Physics()
{
}
sf::Vector2f Physics::NextPosition(sf::Vector2f prevPosition, sf::Time& delta)
{
    //sf::err() << prevPosition.y << "  delta  " << delta.asSeconds() << "\n";
    if (InAir(prevPosition.y) || m_Vel.y != 0)
    {
        prevPosition.y += m_Vel.y * delta.asSeconds();
        m_Vel.y += m_Acc.y * delta.asSeconds();
        //sf::err() << prevPosition.y << " " << m_Vel.y << "\n";
    }
    return prevPosition;
}
void Physics::Impulse(sf::Vector2f Impulse)
{
    m_Vel -= Impulse;
}
bool Physics::InAir(float y)
{
    return (y < m_Floor);
}
sf::Vector2f Physics::GetAccel()
{
    return m_Acc;
}
sf::Vector2f Physics::GetVelocity()
{
    return m_Vel;
}
float Physics::GetFloor()
{
    return m_Floor;
}
void Physics::ResetVelocity()
{
    m_Vel.y = 0;
}
void Physics::SetFloor(unsigned int floor)
{
    m_Floor = floor;
}
