#include "Npc.h"
#include "Player.h"
#include "TileData.h"
#include "NpcMove.h"
#include "RendererData.h"

Npc::Npc() 
	:
	Speed_(80.f),
	WaitTimer_(0.f),
	MoveDir_(float4::DOWN),
	PrevDir_(float4::ZERO),
	DialogueUpdate_(false),
	NpcUpdateState_(NPC_STATE::INIT),
	NpcRenderer_(nullptr),
	NpcCollider_(nullptr),
	PersonalCollider_(nullptr)

{
	ArrAnimationName[static_cast<int>(NPC_STATE::INIT)] = "INIT";
	ArrAnimationName[static_cast<int>(NPC_STATE::WALK)] = "WALK";
	ArrAnimationName[static_cast<int>(NPC_STATE::WALK_WAIT)] = "INIT";

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


void Npc::LoadPennyMoveFlag()
{
	char MapOject[TOWN_CHIP_NUM_Y][TOWN_CHIP_NUM_X] =
	{
		 #include "Map/Town_PennyMove.txt",
	};


	for (int y = 0; y < TOWN_CHIP_NUM_Y; y++)
	{
		for (int x = 0; x < TOWN_CHIP_NUM_X; x++)
		{
			const char chip = MapOject[y][x];
			if (chip < 0) continue;

			const float4 pos = {
				x * CHIP_SIZE + CHIP_SIZE * 0.5f,
				y * CHIP_SIZE + CHIP_SIZE * 0.5f,
			};

			NPC_MOVE_FLAG TileState_ = static_cast<NPC_MOVE_FLAG>(chip);
			std::vector<NpcMove*>::iterator ThisIter;


			//const float4 IndexPos = {
			//  x * CHIP_SIZE ,
			//  y * CHIP_SIZE,
			//};


			switch (TileState_)
			{
			case NPC_MOVE_FLAG::PENNY_RIGHT:

				MoveFlagList_.push_back(GetLevel()->CreateActor<NpcMove>(static_cast<int>(PLAYLEVEL::OBJECT)));

				ThisIter = --MoveFlagList_.end();
				(*ThisIter)->CreateNPCMoveCollision("PennyRight");
				(*ThisIter)->SetPosition(pos);
				(*ThisIter)->SetNPCMoveImageAndIdex("characterMoveSheet.bmp", static_cast<int>(NPC_MOVE_FLAG::PENNY_RIGHT ));
				
				break;

			case NPC_MOVE_FLAG::PENNY_LEFT:

				MoveFlagList_.push_back(GetLevel()->CreateActor<NpcMove>(static_cast<int>(PLAYLEVEL::OBJECT)));

				ThisIter = --MoveFlagList_.end();
				(*ThisIter)->CreateNPCMoveCollision("PennyLeft");
				(*ThisIter)->SetPosition(pos);
				(*ThisIter)->SetNPCMoveImageAndIdex("characterMoveSheet.bmp", static_cast<int>(NPC_MOVE_FLAG::PENNY_LEFT));

				break;

			case NPC_MOVE_FLAG::PENNY_UP:

				MoveFlagList_.push_back(GetLevel()->CreateActor<NpcMove>(static_cast<int>(PLAYLEVEL::OBJECT)));

				ThisIter = --MoveFlagList_.end();
				(*ThisIter)->CreateNPCMoveCollision("PennyUp");
				(*ThisIter)->SetPosition(pos);
				(*ThisIter)->SetNPCMoveImageAndIdex("characterMoveSheet.bmp", static_cast<int>(NPC_MOVE_FLAG::PENNY_UP));

				break;

			case NPC_MOVE_FLAG::PENNY_DOWN:

				MoveFlagList_.push_back(GetLevel()->CreateActor<NpcMove>(static_cast<int>(PLAYLEVEL::OBJECT)));

				ThisIter = --MoveFlagList_.end();
				(*ThisIter)->CreateNPCMoveCollision("PennyDown");
				(*ThisIter)->SetPosition(pos);
				(*ThisIter)->SetNPCMoveImageAndIdex("characterMoveSheet.bmp", static_cast<int>(NPC_MOVE_FLAG::PENNY_DOWN));

				break;

			case NPC_MOVE_FLAG::PENNY_WAIT:

				MoveFlagList_.push_back(GetLevel()->CreateActor<NpcMove>(static_cast<int>(PLAYLEVEL::OBJECT)));

				ThisIter = --MoveFlagList_.end();
				(*ThisIter)->CreateNPCMoveCollision("PennyWait");
				(*ThisIter)->SetPosition(pos);
				(*ThisIter)->SetNPCMoveImageAndIdex("characterMoveSheet.bmp", static_cast<int>(NPC_MOVE_FLAG::PENNY_WAIT));

				break;

			}


		}
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

