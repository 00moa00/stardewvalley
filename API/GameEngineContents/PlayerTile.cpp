#include "Player.h"

//******************************************************************************
//
//
//		타일 관련 함수 구현부
//
//
//******************************************************************************



void Player::CreateDirtTile()
{
	
	float4 Pos = PlayerCollCheckPos();


	TileIndex Index = TileMap_->GetTileIndex({ Pos.x , Pos.y });
	int ChangeIndex = Index.X + (Index.Y * FARM_CHIP_NUM_Y);

	std::map<int, FarmTile*>::iterator FindIter = TileList_.find(ChangeIndex);
	std::map<int, FarmTile*>::iterator EndIter = TileList_.end();

	//찾아서 타일맵이 이미 형성되어 있다면 + 그게 그냥 판 땅이라면, 새로운 타일맵을 생성하지 않음

	if (FindIter != EndIter)
	{
		if (FindIter->second->GetTileState() == TILE_STATE::HOE_DIRT_CREATE)
		{
			return;
		}
	}

	else {
		FarmTile* Tile = TileMap_->CreateTile<FarmTile>(static_cast<int>(Pos.x / CHIP_SIZE), static_cast<int>(Pos.y / CHIP_SIZE)
			, "hoeDirt.bmp", 0, (int)PLAYLEVEL::SEED);
		Tile->TileState_ = TILE_STATE::HOE_DIRT_CREATE;

		//Index = TileMap_->GetTileIndex({ Pos.x , Pos.y });
		//ChangeIndex = Index.X + (Index.Y * FARM_CHIP_NUM_Y);

		TileList_.insert(std::make_pair(ChangeIndex, Tile));
	}
	//delete Tile;
}



void Player::CreateWaterTile()
{

	float4 Pos = PlayerCollCheckPos();

	TileIndex Index = TileMap_->GetTileIndex({ Pos.x , Pos.y });
	int ChangeIndex = Index.X + (Index.Y * FARM_CHIP_NUM_Y);

	std::map<int, FarmTile*>::iterator FindIter = TileList_.find(ChangeIndex);
	std::map<int, FarmTile*>::iterator EndIter = TileList_.end();


	//땅에 아무것도 없다면
	if (FindIter == EndIter)
	{
		return;
	}


	//호미질을 한 땅이면 스테이트를 변경
	if (FindIter->second->GetTileState() == TILE_STATE::HOE_DIRT_CREATE)
	{
		FindIter->second->SetTileState(TILE_STATE::HOE_DIRT_WATER);
	}


}

void Player::CreateSeed()
{


	float4 Pos = PlayerCollCheckPos();

	TileIndex Index = TileMap_->GetTileIndex({ Pos.x , Pos.y });
	int ChangeIndex = Index.X + (Index.Y * FARM_CHIP_NUM_Y);

	std::map<int, FarmTile*>::iterator FindDirtIter = TileList_.find(ChangeIndex);
	std::map<int, FarmTile*>::iterator EndDirtIter = TileList_.end();

	std::map<int, Items*>::iterator FindSeedIter = SeedList_.find(ChangeIndex);
	std::map<int, Items*>::iterator EndSeedIter = SeedList_.end();


	//땅에 아무것도 없으면, 이미 씨앗이 있으면
	if (FindDirtIter == EndDirtIter&& FindSeedIter!= EndSeedIter)
	{
		return;
	}


	//해당 땅이 파져있으면 씨앗을 심는다.
	if (FindDirtIter != EndDirtIter)
	{
		Items* seed = CreateSeedActor<Parsnip_Growing>();

		float4 TileSize_ = { 48.f, 48.f };
		float4 WorldPos = TileSize_;

		WorldPos.x *= static_cast<int>(Pos.x / CHIP_SIZE);
		WorldPos.y *= static_cast<int>(Pos.y / CHIP_SIZE);

		WorldPos += TileSize_.Half();

		seed->GetRenderer()->SetPivot({ WorldPos.x, WorldPos.y - 24.f });
		SeedList_.insert(std::make_pair(ChangeIndex, seed));

	}


}


void Player::CrushWood()
{

	for (Iter = MapObject_.begin(); Iter != MapObject_.end(); ++Iter) {

		if ((*Iter)->IsWall(PlayerCollCheckPos(), GetScale(), MoveDir_) == true)
		{
			(*Iter)->Death();
			TileState_ = TILE_COLL::INIT;
			Speed_ = 150.f;
			PlayerState_ = PLAYER_UPDATE::INIT;

		}

		else
		{
			PlayerState_ = PLAYER_UPDATE::INIT;
		}


	}
}


void Player::ObjectTileColl()
{
	float4 Pos = PlayerCollCheckPos();

	switch (TileState_)
	{
	case TILE_COLL::INIT:
		Iter = MapObject_.begin();
		TileState_ = TILE_COLL::NOTACT;

		break;

	case TILE_COLL::NOTACT:


		for (; Iter != MapObject_.end(); ++Iter) {

			if ((*Iter)->IsWall(PlayerCollCheckPos(), GetScale(), MoveDir_) == true) {
				Speed_ = 0.f;

				TileState_ = TILE_COLL::COll;
				break;
			}

		}

		if (Iter == MapObject_.end()) {
			Iter = MapObject_.begin();
		}
		break;

	case TILE_COLL::COll:

		if ((*Iter)->IsWall(PlayerCollCheckPos(), GetScale(), MoveDir_) == false) {
			Speed_ = 150.f;
			//Player_->SetBreakY(false);

			Iter = MapObject_.begin();
			TileState_ = TILE_COLL::NOTACT;
		}

		break;

	}

}


void Player::ChangeTile()
{

	//위치 초기화
	//std::map<int, FarmTile*>::iterator StartIter = TileList_.begin();
	std::map<int, FarmTile*>::iterator EndIter = TileList_.end();



	for (int i = 0; i < FARM_CHIP_NUM_X * FARM_CHIP_NUM_Y; ++i)
	{

		std::map<int, FarmTile*>::iterator FindLeftIter = TileList_.find(i - 1);
		std::map<int, FarmTile*>::iterator FindThisIter = TileList_.find(i);
		std::map<int, FarmTile*>::iterator FindRightIter = TileList_.find(i + 1);
		std::map<int, FarmTile*>::iterator FindTopIter = TileList_.find(i - FARM_CHIP_NUM_Y);
		std::map<int, FarmTile*>::iterator FindBottomIter = TileList_.find(i + FARM_CHIP_NUM_Y);


		//현재 찾으려는 타일이 땅에 없으면 패스
		if (FindThisIter == EndIter) continue;

		int Water = 0;

		//찾은 땅에 물을 뿌렸다면
		if (FindThisIter->second->GetTileState() == TILE_STATE::HOE_DIRT_WATER)
		{
			Water = 4;
		}
		else if (FindThisIter->second->GetTileState() == TILE_STATE::HOE_DIRT_CREATE)
		{
			Water = 0;
		}


		//------< 위 아래 아무것도 없을때 x축, 원라인 >------------------------------------------------------------------

		if (FindTopIter == EndIter && FindBottomIter == EndIter)
		{
			//===================================================
			//   case 1 왼쪽 타일은 없는데 오른쪽 타일은 있는경우
			//===================================================

			if (FindLeftIter == EndIter && FindRightIter != EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::W_LINE_LEFT) + Water);

			}

			//===================================================
			//   case 2 왼쪽타일은 있는데 오른쪽 타일은 없는경우
			//===================================================

			if (FindLeftIter != EndIter && FindRightIter == EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::W_LINE_RIGHT) + Water);

			}

			//===================================================
			//   case 3 왼쪽 오른쪽 둘 다 있는 경우
			//===================================================

			if (FindLeftIter != EndIter && FindRightIter != EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::W_LINE_MIDDLE) + Water);

			}


		}

		//------< 양 옆 아무것도 없을때 y축, 원라인 >------------------------------------------------------------------

		if (FindLeftIter == EndIter && FindRightIter == EndIter)
		{

			//===================================================
			//   case 1 위쪽 타일은 없는데 아래쪽 타일은 있는경우
			//===================================================

			if (FindTopIter == EndIter && FindBottomIter != EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::H_LINE_TOP) + Water);

			}


			//===================================================
			//   case 2 위쪽타일은 있는데 아래쪽 타일은 없는경우
			//===================================================

			if (FindTopIter != EndIter && FindBottomIter != EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::H_LINE_MIDDLE) + Water);

			}


			//===================================================
			//   case 3 위쪽 아래쪽 둘 다 있는 경우
			//===================================================

			if (FindTopIter != EndIter && FindBottomIter == EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::H_LINE_BOTTOM) + Water);

			}

		}


		//------< 아래는 있는데 위가 없을경우 >------------------------------------------------------------------


		if (FindTopIter == EndIter && FindBottomIter != EndIter)
		{

			//===================================================
			//   case 1 왼쪽 타일은 없는데 오른쪽 타일은 있는경우
			//===================================================
			if (FindLeftIter == EndIter && FindRightIter != EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::LEFT_TOP) + Water);

			}


			//===================================================
			//   case 2 왼쪽타일은 있는데 오른쪽 타일은 없는경우
			//===================================================

			if (FindLeftIter != EndIter && FindRightIter == EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::RIGHT_TOP) + Water);

			}


			//===================================================
			//   case 3 왼쪽 오른쪽 둘 다 있는 경우
			//===================================================
			if (FindLeftIter != EndIter && FindRightIter != EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::MIDDLE_TOP) + Water);

			}


		}

		//------< 위는 있는데 아래는 없는 경우 >------------------------------------------------------------------

		if (FindTopIter != EndIter && FindBottomIter == EndIter)
		{

			//===================================================
			//   case 1 왼쪽 타일은 없는데 오른쪽 타일은 있는경우
			//===================================================
			if (FindLeftIter == EndIter && FindRightIter != EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::LEFT_BOTTOM) + Water);

			}


			//===================================================
			//   case 2 왼쪽타일은 있는데 오른쪽 타일은 없는경우
			//===================================================

			if (FindLeftIter != EndIter && FindRightIter == EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::RIGHT_BOTTOM) + Water);

			}


			//===================================================
			//   case 3 왼쪽 오른쪽 둘 다 있는 경우
			//===================================================
			if (FindLeftIter != EndIter && FindRightIter != EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::MIDDLE_BOTTOM) + Water);

			}

		}


		//------< 위아래 둘다 있는 경우 >------------------------------------------------------------------

		if (FindTopIter != EndIter && FindBottomIter != EndIter)
		{

			//===================================================
			//   case 1 왼쪽 타일은 없는데 오른쪽 타일은 있는경우
			//===================================================
			if (FindLeftIter == EndIter && FindRightIter != EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::LEFT_MIDDLE) + Water);

			}


			//===================================================
			//   case 2 왼쪽타일은 있는데 오른쪽 타일은 없는경우
			//===================================================

			if (FindLeftIter != EndIter && FindRightIter == EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::RIGHT_MIDDLE) + Water);

			}


			//===================================================
			//   case 3 왼쪽 오른쪽 둘 다 있는 경우
			//===================================================
			if (FindLeftIter != EndIter && FindRightIter != EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::MIDDLE_MIDDLE) + Water);

			}

		}

		//------< 사방에 아무것도 없다면 >------------------------------------------------------------------

		if (FindLeftIter == EndIter && FindRightIter == EndIter && FindTopIter == EndIter && FindBottomIter == EndIter)
		{
			FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::BASIC) + Water);

		}

		//------< 이모든것에 속하지 않는다 >------------------------------------------------------------------

		//if (FindLeftIter == EndIter || FindRightIter == EndIter || FindTopIter == EndIter || FindBottomIter == EndIter)
		//{
		//	return;

		//}

	}


}
