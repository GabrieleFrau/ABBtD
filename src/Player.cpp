#include "Player.hpp"
using namespace My;
Player::Player(ResourceHandler& res)
    : sf::Sprite(*res.GetTextures(), sf::IntRect(56, 132, 52, 96))
    , Arm(sf::Vector2f(20,5))
    , HPbar(sf::Vector2f(200,20))
    , HP(100)
    , punched(false)
    , p_Other(nullptr)
    , b_Attack(*res.GetAttack())
    , b_Jump(*res.GetJump())
    , m_Physics(sf::Vector2f(0,0),sf::Vector2f(0,1600.f),0)
{
    Arm.setFillColor(sf::Color(0,80,0));
}
Player::~Player()
{
}
void Player::Init(sf::Vector2f position = sf::Vector2f(0.f,0.f), unsigned int floor = 0)
{
    Player::Init(position.x, position.y, floor);
}
void Player::SetOtherPlayer(Player* player)
{
    p_Other = player;
}
void Player::Init(float x = 0, float y = 0, unsigned int floor = 0)
{
    m_Physics.SetFloor(floor);
    setPosition(x,y);
    a_WalkPointingLeft.addFrame(1.f, rectL_IDLE);
    a_WalkPointingLeft.addFrame(1.f, rectL_WALK1);
    a_WalkPointingLeft.addFrame(1.f, rectL_WALK2);
    a_WalkPointingLeft.addFrame(1.f, rectL_WALK1);
    a_WalkPointingLeft.addFrame(1.f, rectL_IDLE);
    a_WalkPointingLeft(*this, 0.f);
    a_WalkPointingRight.addFrame(1.f, rectR_IDLE);
    a_WalkPointingRight.addFrame(1.f, rectR_WALK1);
    a_WalkPointingRight.addFrame(1.f, rectR_WALK2);
    a_WalkPointingRight.addFrame(1.f, rectR_WALK1);
    a_WalkPointingRight.addFrame(1.f, rectR_IDLE);
    a_WalkPointingRight(*this, 0.f);
    a_PunchLeft.addFrame(1.f, rectL_IDLE);
    a_PunchLeft.addFrame(1.f, rectL_PUNCH);
    a_PunchLeft.addFrame(1.f, rectL_IDLE);
    a_PunchLeft(*this, 0.f);
    a_PunchRight.addFrame(1.f, rectR_IDLE);
    a_PunchRight.addFrame(1.f, rectR_PUNCH);
    a_PunchRight.addFrame(1.f, rectR_IDLE);
    a_PunchRight(*this, 0.f);
    a_IdleLeft.addFrame(1.f, rectL_IDLE);
    a_IdleLeft(*this, 0.f);
    a_IdleRight.addFrame(1.f, rectR_IDLE);
    a_IdleRight(*this, 0.f);
    m_Animator.addAnimation("walkR", a_WalkPointingRight, sf::seconds(.5f));
    m_Animator.addAnimation("walkL", a_WalkPointingLeft, sf::seconds(.5f));
    m_Animator.addAnimation("punchL", a_PunchLeft, sf::seconds(0.1f));
    m_Animator.addAnimation("punchR", a_PunchRight, sf::seconds(0.1f));
    m_Animator.addAnimation("idleL", a_IdleLeft, sf::seconds(0.2f));
    m_Animator.addAnimation("idleR", a_IdleRight, sf::seconds(0.2f));
    s_Attack.setBuffer(b_Attack);
    s_Attack.setAttenuation(1.f);
    s_Attack.setMinDistance(100.f);
    //s_Jump.setBuffer(b_Jump);
    //s_Jump.setAttenuation(100.f);
    //s_Jump.setMinDistance(100.f);
}
void Player::UpdateAndAnimate(sf::Time& delta)
{
    m_Animator.update(delta);
    m_Animator.animate(*this);
    sf::Vector2f pos = m_Physics.NextPosition(getPosition(), delta);
    move(0, pos.y - getPosition().y);
    if(!m_Physics.InAir(getPosition().y + getTextureRect().height))
    {
        setPosition(getPosition().x, static_cast<float>(m_Physics.GetFloor() - getTextureRect().height));
        m_Physics.ResetVelocity();
    }
    if(getPosition().x < p_Other->getPosition().x)
        Arm.setPosition(getPosition().x + getTextureRect().width, getPosition().y + getTextureRect().height/5);
    else
        Arm.setPosition(getPosition().x - Arm.getSize().x, getPosition().y + getTextureRect().height/5);
    assert(p_Other != nullptr);
    if(IsPunching())
    {
        if(Arm.getGlobalBounds().intersects(p_Other->getGlobalBounds()) && !punched)
        {
            HitUpperBody();
            sf::err()<<"Other player hit\n";
        }
    }
    else
        punched = false;
    s_Attack.setPosition(getPosition().x, getPosition().y, 0.f);
    s_Jump.setPosition(getPosition().x, getPosition().y, 0.f);
}
void Player::Idle()
{
    if (Player::getPosition().x < GetOtherPlayerPosition().x)
    {
        if (!m_Animator.isPlayingAnimation())
            m_Animator.playAnimation("idleR");
    }
    else
    {
        if (!m_Animator.isPlayingAnimation())
            m_Animator.playAnimation("idleL");
    }
    sf::err() << "Idle.." << "\n";
}
void Player::hit(int damage)
{
    HP -= damage;
    sf::Vector2f newsize(HPbar.getSize().x - (damage * 2), HPbar.getSize().y);
    HPbar.setSize(newsize);
    punched = true;
}
void Player::HitUpperBody()
{
    hit(20);
}
void Player::HitMidBody()
{
    hit(10);
}
void Player::HitLowerBody()
{
    hit(5);
}
void Player::go(float x, float y)
{
    move(x, y);
    if (Player::getPosition().x < GetOtherPlayerPosition().x)
    {
        if (!m_Animator.isPlayingAnimation())
            m_Animator.playAnimation("walkR");
    }
    else
    {
        if (!m_Animator.isPlayingAnimation())
            m_Animator.playAnimation("walkL");
    }

}
void Player::GoLeft(sf::Time& delta)
{
    //sf::err() << delta.asSeconds() << "\n";
    Player::go(-200.f * delta.asSeconds(), 0);
}
void Player::GoRight(sf::Time& delta)
{
    //sf::err() << delta.asSeconds() << "\n";
    Player::go(200.f * delta.asSeconds(), 0);
}
bool Player::IsPunching()
{
    if(m_Animator.isPlayingAnimation())
    {
        std::string tmp(m_Animator.getPlayingAnimation());
        return (tmp.compare("punchL") == 0 || tmp.compare("punchR") == 0);
    }
    return false;
}
void Player::Punch()
{
    //sf::err() << "punch!\n";
    if (Player::getPosition().x < GetOtherPlayerPosition().x)
    {
        //if (!m_Animator.isPlayingAnimation())
        m_Animator.playAnimation("punchR");
    }
    else
    {
        //if (!m_Animator.isPlayingAnimation())
        m_Animator.playAnimation("punchL");
    }
    s_Attack.play();
}
void Player::StartJump()
{
    if(!m_Physics.InAir(getPosition().y + getTextureRect().height))
        m_Physics.Impulse(sf::Vector2f(0,700));
    //s_Jump.play();
}
sf::Vector2f Player::GetOtherPlayerPosition()
{
    assert(p_Other != nullptr);
    return p_Other->getPosition();
}
sf::Vector2f Player::GetAccel()
{
    return m_Physics.GetAccel();
}
sf::Vector2f Player::GetVelocity()
{
    return m_Physics.GetVelocity();
}
