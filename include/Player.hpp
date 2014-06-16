#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Audio.hpp>
#include <Thor/Animation.hpp>
#include <Thor/Resources.hpp>
#include <Resources.h>
#include <ResourceHandler.hpp>
#include <complex>
namespace My
{
	const sf::IntRect rectIdleR(304, 0, 50, 94);
	const sf::IntRect rectWalk1R(80, 0, 77, 94);
	const sf::IntRect rectWalk2R(159, 0, 77, 94);
	const sf::IntRect rectPunch1R(238, 0, 64, 94);
	const sf::IntRect rectPunch2R(0, 0, 78, 94);
	using Animator = thor::Animator < sf::Sprite, std::string > ;
	class Player : public sf::Sprite
	{
	public:
		Player(ResourceHandler& resourceHandler);
		~Player();
		void SetOtherPlayer(Player* player);
		void Init(sf::Vector2f position, unsigned int floor);
		void Init(float x, float y, unsigned int floor);
		void Idle();
		void GoRight(sf::Time& delta);
		void GoLeft(sf::Time& delta);
		void Punch();
		void StartJump();
		void UpdateAndAnimate(sf::Time& delta);
		sf::Vector2f GetVelocity();
		sf::Vector2f GetAccel();
		bool IsInAir();
	private:
		void go(float x, float y);
		sf::IntRect mirror(sf::IntRect rect);
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
		sf::SoundBuffer b_Attack;
		Animator m_Animator;
		unsigned int m_Floor;
		sf::Vector2f m_Acceleration;
		sf::Vector2f m_Velocity;
		bool m_InAir;
	};
}
#endif // PLAYER_HPP
