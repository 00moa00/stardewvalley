#include "Npc.h"
#include "Player.h"
#include "TileData.h"
#include "NpcMove.h"
#include "RendererData.h"
#include "MainUI.h"

Npc::Npc() 
	:
	WaitCount_(0),
	Speed_(80.f),
	WaitTimer_(0.f),
	MoveDir_(float4::DOWN),
	PrevDir_(float4::ZERO),
	DialogueUpdate_(false),
	isWalking_(false),
	NpcUpdateState_(NPC_STATE::WAIT),
	NpcRenderer_(nullptr),
	NpcCollider_(nullptr),
	PersonalCollider_(nullptr)

{
	ArrAnimationName[static_cast<int>(NPC_STATE::WAIT)] = "INIT";
	ArrAnimationName[static_cast<int>(NPC_STATE::WALK)] = "WALK";
	ArrAnimationName[static_cast<int>(NPC_STATE::DIALOGUE_IDLE)] = "INIT";
	ArrAnimationName[static_cast<int>(NPC_STATE::DIALOGUE_WAIT)] = "INIT";
	ArrAnimationName[static_cast<int>(NPC_STATE::WAIT_COUNT)] = "INIT";

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
		 #include "Map/Town_PennyMove.txt"
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

void Npc::LoadLewisMoveFlag()
{

	char MapOject[TOWN_CHIP_NUM_Y][TOWN_CHIP_NUM_X] =
	{
		 #include "Map/Town_LewisMove.txt"
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
			case NPC_MOVE_FLAG::LEWIS_RIGHT:

				MoveFlagList_.push_back(GetLevel()->CreateActor<NpcMove>(static_cast<int>(PLAYLEVEL::OBJECT)));

				ThisIter = --MoveFlagList_.end();
				(*ThisIter)->CreateNPCMoveCollision("LewisRight");
				(*ThisIter)->SetPosition(pos);
				(*ThisIter)->SetNPCMoveImageAndIdex("characterMoveSheet.bmp", static_cast<int>(NPC_MOVE_FLAG::LEWIS_RIGHT));

				break;

			case NPC_MOVE_FLAG::LEWIS_LEFT:

				MoveFlagList_.push_back(GetLevel()->CreateActor<NpcMove>(static_cast<int>(PLAYLEVEL::OBJECT)));

				ThisIter = --MoveFlagList_.end();
				(*ThisIter)->CreateNPCMoveCollision("LewisLeft");
				(*ThisIter)->SetPosition(pos);
				(*ThisIter)->SetNPCMoveImageAndIdex("characterMoveSheet.bmp", static_cast<int>(NPC_MOVE_FLAG::LEWIS_LEFT));

				break;

			case NPC_MOVE_FLAG::LEWIS_UP:

				MoveFlagList_.push_back(GetLevel()->CreateActor<NpcMove>(static_cast<int>(PLAYLEVEL::OBJECT)));

				ThisIter = --MoveFlagList_.end();
				(*ThisIter)->CreateNPCMoveCollision("LewisUp");
				(*ThisIter)->SetPosition(pos);
				(*ThisIter)->SetNPCMoveImageAndIdex("characterMoveSheet.bmp", static_cast<int>(NPC_MOVE_FLAG::LEWIS_UP));

				break;

			case NPC_MOVE_FLAG::LEWIS_DOWN:

				MoveFlagList_.push_back(GetLevel()->CreateActor<NpcMove>(static_cast<int>(PLAYLEVEL::OBJECT)));

				ThisIter = --MoveFlagList_.end();
				(*ThisIter)->CreateNPCMoveCollision("LewisDown");
				(*ThisIter)->SetPosition(pos);
				(*ThisIter)->SetNPCMoveImageAndIdex("characterMoveSheet.bmp", static_cast<int>(NPC_MOVE_FLAG::LEWIS_DOWN));

				break;

			case NPC_MOVE_FLAG::LEWIS_WAIT:

				MoveFlagList_.push_back(GetLevel()->CreateActor<NpcMove>(static_cast<int>(PLAYLEVEL::OBJECT)));

				ThisIter = --MoveFlagList_.end();
				(*ThisIter)->CreateNPCMoveCollision("LewisWait");
				(*ThisIter)->SetPosition(pos);
				(*ThisIter)->SetNPCMoveImageAndIdex("characterMoveSheet.bmp", static_cast<int>(NPC_MOVE_FLAG::LEWIS_WAIT));

				break;

			}


		}
	}

}

void Npc::MoveCheck()
{
	if (MoveDown() == true)
	{
		MoveDir_ = float4::DOWN;
		NpcUpdateState_ = NPC_STATE::WALK;
	}

	if (MoveUp() == true)
	{
		MoveDir_ = float4::UP;
		NpcUpdateState_ = NPC_STATE::WALK;

	}

	if (MoveRight() == true)
	{
		MoveDir_ = float4::RIGHT;
		NpcUpdateState_ = NPC_STATE::WALK;

	}

	if (MoveLeft() == true)
	{
		MoveDir_ = float4::LEFT;
		NpcUpdateState_ = NPC_STATE::WALK;

	}

	if (MoveWait() == true)
	{
		MoveDir_ = float4::DOWN;
		NpcUpdateState_ = NPC_STATE::WAIT_COUNT;

	}
}

bool Npc::MoveRight()
{
	return false;
}

bool Npc::MoveLeft()
{
	return false;

}

bool Npc::MoveDown()
{
	return false;

}

bool Npc::MoveUp()
{
	return false;

}

bool Npc::MoveWait()
{
	return false;

}

void Npc::MoveUpdate()
{
	//대화중에는 멈춰
	if (DialogueUpdate_ == false)
	{
		MoveCheck();
	}

	switch (NpcUpdateState_)
	{
	case NPC_STATE::WAIT:

		isWalking_ = false;
		//플레이어와 멀어지면 원래 방향으로 리셋
		if (ForAwayPlayer() == true)
		{
			MoveDir_ = float4::DOWN;
		}

		break;
	case NPC_STATE::WALK:

		isWalking_ = true;
		SetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_);

		break;


	case NPC_STATE::DIALOGUE_IDLE:


		break;

	case NPC_STATE::DIALOGUE_WAIT:

		WaitTimer_ -= GameEngineTime::GetDeltaTime();

		if (WaitTimer_ < 0.f)
		{
			//걷던 중이면
			if (isWalking_ == true)
			{
				MoveDir_ = PrevDir_;
				NpcUpdateState_ = NPC_STATE::WALK;
				break;
			}

			//대기 중이었다면(서있던 상태였다면)
			if (isWalking_ == false)
			{
				NpcUpdateState_ = NPC_STATE::WAIT;
				break;
			}
		}

		break;
	case NPC_STATE::WAIT_COUNT:

		++WaitCount_;
		NpcUpdateState_ = NPC_STATE::WAIT;

		break;
	default:
		break;
	}

	DirAnimationChange();
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

