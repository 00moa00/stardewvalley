#include "Player.h"

Player* Player::Inst_ = new Player();

Player::Player() 
	:
	PlayerShirts_(nullptr)
{
}

Player::~Player() 
{
}

void Player::init()
{
	PlayerShirts_ = CreateActor<PlayerShirts>(0);

}

void Player::update()
{
}

void Player::release()
{
}
