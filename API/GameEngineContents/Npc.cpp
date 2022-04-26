#include "Npc.h"
#include "Player.h"

Npc::Npc() 
	:
	MoveDir_(float4::DOWN),
	DialogueUpdate_(false),
	NpcUpdateState_(NPC_STATE::INIT),
	NpcRenderer_(nullptr),
	NpcCollider_(nullptr),
	PersonalCollider_(nullptr)

{
	ArrAnimationName[static_cast<int>(NPC_STATE::INIT)] = "INIT";
	ArrAnimationName[static_cast<int>(NPC_STATE::WALK)] = "WALK";
}

Npc::~Npc() 
{
}

void Npc::OpenDialogue()
{
}

void Npc::DirAnimationChange()
{
	NpcRenderer_->ChangeAnimation(GetDirString() + ArrAnimationName[static_cast<int>(NpcUpdateState_)]);
}

std::string Npc::GetDirString()
{
	if (MoveDir_.CompareInt2D(float4::DOWN))
	{
		return "FRONT_";
	}

	else if (MoveDir_.CompareInt2D(float4::UP))
	{
		return "BACK_";
	}

	else if (MoveDir_.CompareInt2D(float4::LEFT))
	{
		return "LEFT_";
	}

	else if (MoveDir_.CompareInt2D(float4::RIGHT))
	{
		return "RIGHT_";
	}

	return "";
}

bool Npc::ForAwayPlayer()
{
	float4 Dir = Player::MainPlayer->GetPosition() - this->GetPosition();
	float Check = Dir.Len2D();

	if (Check >= 200)
	{
		return true;
	}
	else
	{
		return false;
	}

}


bool Npc::NPCCheck(const float4 pos, const float4 scale)
{
	int OtherLeft = pos.ix() - scale.hix();
	int OtherRight = pos.ix() + scale.hix();
	int OtherTop = pos.iy() - scale.hiy();
	int OtherBottom = pos.iy() + scale.hiy();

	//	GameEngineRect DebugRect;


	if (GetRight() < OtherLeft)
	{
		return false;
	}

	if (OtherRight < GetLeft())
	{
		return false;
	}

	if (GetBottom() < OtherTop)
	{
		return false;
	}

	if (OtherBottom < GetTop())
	{
		return false;
	}

	return true;
}

