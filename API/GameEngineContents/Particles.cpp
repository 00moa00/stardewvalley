#include "Particles.h"

Particles::Particles() 

{
}

Particles::~Particles() 
{
}

void Particles::Start()
{
	AnimationRenderer_ = CreateRenderer("WoodParticle1.bmp");
}

void Particles::Update()
{
	switch (AnimationState_)
	{
	case ANIMATION_STATE::INIT:

		PrePosition_ = this->GetPosition();
		AnimationState_ = ANIMATION_STATE::MOVE;


		break;
	case ANIMATION_STATE::MOVE:

		MoveDir_ += float4::DOWN * GameEngineTime::GetDeltaTime() * 800.0f;
		SetMove(MoveDir_ * GameEngineTime::GetDeltaTime());

		if (this->GetPosition().y > PrePosition_.y)
		{
			AnimationState_ = ANIMATION_STATE::MOVE_END;

		}

		break;
	case ANIMATION_STATE::MOVE_END:

		this->Death();

		break;
	default:
		break;
	}
	
}

