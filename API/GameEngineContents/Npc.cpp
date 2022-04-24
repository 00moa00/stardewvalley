#include "Npc.h"

Npc::Npc() 
	:
	DialogueUpdate_(false)
{
}

Npc::~Npc() 
{
}

void Npc::OpenDialogue()
{
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

