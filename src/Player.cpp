#include "Player.hpp"
using namespace My;
Player::Player(ResourceHandler& res)
	: sf::Sprite(*res.GetTextures(), sf::IntRect(56, 132, 52, 96))
	, p_Other(nullptr)
	, b_Attack(*res.GetAttack())
	, m_Floor(0)
	, m_Acceleration(0, 1600.f) //weigth
	, m_Velocity(0, 0)
	, m_InAir(false)
{

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
	m_Floor = floor;
    this->setPosition(x,y);
	a_WalkPointingLeft.addFrame(1.f, rectIdleR);
	a_WalkPointingLeft.addFrame(1.f, rectWalk1R);
	a_WalkPointingLeft.addFrame(1.f, rectWalk2R);
	a_WalkPointingLeft(*this, 0.f);
	a_WalkPointingRight.addFrame(1.f, mirror(rectIdleR));
	a_WalkPointingRight.addFrame(1.f, mirror(rectWalk1R));
	a_WalkPointingRight.addFrame(1.f, mirror(rectWalk2R));
	a_WalkPointingRight(*this, 0.f);
	a_PunchLeft.addFrame(1.f, rectIdleR);
	a_PunchLeft.addFrame(1.f, rectPunch1R);
	a_PunchLeft.addFrame(1.f, rectPunch2R);
	a_PunchLeft.addFrame(1.f, rectPunch1R);
	a_PunchLeft.addFrame(1.f, rectIdleR);
	a_PunchLeft(*this, 0.f);
	a_PunchRight.addFrame(1.f, mirror(rectIdleR));
	a_PunchRight.addFrame(1.f, mirror(rectPunch1R));
	a_PunchRight.addFrame(1.f, mirror(rectPunch2R));
	a_PunchRight.addFrame(1.f, mirror(rectPunch1R));
	a_PunchRight.addFrame(1.f, mirror(rectIdleR));
	a_PunchRight(*this, 0.f);
	a_IdleLeft.addFrame(1.f, mirror(rectIdleR));
	a_IdleLeft.addFrame(1.f, mirror(rectIdleR));
	a_IdleLeft(*this, 0.f);
	a_IdleRight.addFrame(1.f, rectIdleR);
	a_IdleRight.addFrame(1.f, rectIdleR);
	a_IdleRight(*this, 0.f);
	m_Animator.addAnimation("walkR", a_WalkPointingRight, sf::seconds(0.5f));
	m_Animator.addAnimation("walkL", a_WalkPointingLeft, sf::seconds(0.5f));
	m_Animator.addAnimation("punchL", a_PunchLeft, sf::seconds(0.1f));
	m_Animator.addAnimation("punchR", a_PunchRight, sf::seconds(0.1f));
	m_Animator.addAnimation("idleL", a_IdleLeft, sf::seconds(0.2f));
	m_Animator.addAnimation("idleR", a_IdleRight, sf::seconds(0.2f));
    s_Attack.setBuffer(b_Attack);
}
void Player::UpdateAndAnimate(sf::Time& delta)
{
	m_Animator.update(delta);
	m_Animator.animate(*this);
	if (getPosition().y + getTextureRect().height < m_Floor || m_InAir)
	{
		m_InAir = true;
		sf::Vector2f pos(0.f, getPosition().y);
		pos.y += m_Velocity.y * delta.asSeconds();
		m_Velocity.y += m_Acceleration.y * delta.asSeconds();
		Player::move(0, pos.y - getPosition().y);
		if (getPosition().y + getTextureRect().height > m_Floor)
		{
			Player::setPosition(getPosition().x, static_cast<float>(m_Floor) - getTextureRect().height);
			m_Velocity.y = 0;
			m_InAir = false;
		}
		else
			sf::err() << getPosition().y + getTextureRect().height << " > " << m_Floor << "\n";
	}
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
void Player::go(float x, float y)
{
	Player::move(x, y);
	if (Player::getPosition().x < GetOtherPlayerPosition().x)
	{
		if (!m_Animator.isPlayingAnimation())
			m_Animator.playAnimation("walkL");
	}
	else
	{
		if (!m_Animator.isPlayingAnimation())
			m_Animator.playAnimation("walkR");
	}

}
sf::IntRect Player::mirror(sf::IntRect rect)
{
	rect.left += rect.width;
	rect.width = -rect.width;
	return rect;
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
void Player::Punch()
{
	sf::err() << "punch!\n";
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
	sf::err() << "JUMP!\n";
	m_Velocity.y -= 400.f;
	m_InAir = true;
}
sf::Vector2f Player::GetOtherPlayerPosition()
{
	assert(p_Other != nullptr);
	return p_Other->getPosition();
}
sf::Vector2f Player::GetAccel()
{
	return m_Acceleration;
}
sf::Vector2f Player::GetVelocity()
{
	return m_Velocity;
}
bool Player::IsInAir()
{
	return m_InAir;
}