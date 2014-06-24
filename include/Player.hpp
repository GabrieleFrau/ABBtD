#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Audio.hpp>
#include <Thor/Animation.hpp>
#include <Thor/Resources.hpp>
#include <Resources.h>
#include <ResourceHandler.hpp>
#include <complex>
#include <Physics.hpp>
namespace My
{
const sf::IntRect rectL_IDLE(0,662,50,94);
const sf::IntRect rectL_PUNCH(0,284,50,94);
const sf::IntRect rectL_WALK1(0,568,50,94);
const sf::IntRect rectL_WALK2(0,94,50,94);
const sf::IntRect rectR_IDLE(0, 474, 50, 94);
const sf::IntRect rectR_PUNCH(0,188,50,94);
const sf::IntRect rectR_WALK1(0,380,50,94);
const sf::IntRect rectR_WALK2(0, 0, 50, 94);
using Animator = thor::Animator < sf::Sprite, std::string > ;
class Player : public sf::Sprite
{
public:
    Player(ResourceHandler& resourceHandler);
    ~Player();
    void SetOtherPlayer(Player& player);
    void Init(sf::Vector2f position, unsigned int floor);
    void Init(float x, float y, unsigned int floor);
    void Idle();
    void GoRight(sf::Time& delta);
    void GoLeft(sf::Time& delta);
    bool IsPunching();
    void Punch();
    void StartJump();
    Player* GetPointer();
    void UpdateAndAnimate(sf::Time& delta);
    bool HasLost();
    void HitUpperBody();
    void HitMidBody();
    void HitLowerBody();
    sf::Vector2f GetVelocity();
    sf::Vector2f GetAccel();
    sf::RectangleShape Arm;
    sf::RectangleShape HPbar;
private:
    void go(float x, float y);
    void hit(int damage);
    int HP;
    bool punched;
    sf::Vector2f GetOtherPlayerPosition();
    Player* p_Other;
    thor::FrameAnimation a_WalkPointingLeft;
    thor::FrameAnimation a_WalkPointingRight;
    thor::FrameAnimation a_PunchRight;
    thor::FrameAnimation a_PunchLeft;
    thor::FrameAnimation a_IdleRight;
    thor::FrameAnimation a_IdleLeft;
    thor::FrameAnimation a_Jump;
    sf::Sound s_Attack;
    sf::Sound s_Jump;
    sf::SoundBuffer b_Attack;
    sf::SoundBuffer b_Jump;
    Animator m_Animator;
    My::Physics m_Physics;

};
}
#endif // PLAYER_HPP
