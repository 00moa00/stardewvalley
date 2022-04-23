#include "Pierre.h"

Pierre* Pierre::MainPierre = nullptr;

Pierre::Pierre() 
{
}

Pierre::~Pierre() 
{
}

void Pierre::Start()
{
	NpcRenderer_ = CreateRenderer("Pierre.bmp");
	NpcRenderer_->SetIndex(0);
}

void Pierre::Update()
{
}

void Pierre::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainPierre = this;
}

void Pierre::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
}
