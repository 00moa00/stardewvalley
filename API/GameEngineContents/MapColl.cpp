#include "MapColl.h"
#include "GameData.h"
MapColl::MapColl() 
{
}

MapColl::~MapColl() 
{
}

void MapColl::Start()
{

	SetPosition({0, 0});
	MapColImage_ = GameEngineImageManager::GetInst()->Find("FarmBack_Coll.bmp");
}

