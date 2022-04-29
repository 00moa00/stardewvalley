#include "NpcMove.h"

NpcMove::NpcMove() 
	:
	MoveRenderer_(nullptr),
	MoveCollision_(nullptr)
{
}

NpcMove::~NpcMove() 
{
}

void NpcMove::Start()
{
	MoveRenderer_ = CreateRenderer();
}

void NpcMove::Update()
{
}

void NpcMove::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
}

void NpcMove::CreateNPCMoveCollision(std::string _CollName)
{
	MoveCollision_ = CreateCollision(_CollName, {48,48});
}

void NpcMove::SetNPCMoveImageAndIdex(std::string _FileName, int _Index)
{
	//MoveRenderer_->SetImage(_FileName);
	//MoveRenderer_->SetIndex(_Index);

	MoveRenderer_->SetImage("Empty.bmp");
	//MoveRenderer_->SetIndex(_Index);
}

bool NpcMove::CheckCollNPC()
{
	return (MoveCollision_->CollisionResult("NPC", ColList, CollisionType::Rect, CollisionType::Rect));
}
