#include "Player.h"
#include "TreeTop.h"

//******************************************************************************
//
//
//		타일 관련 함수 구현부
//
//
//******************************************************************************

float4 Player::PlayerCollCheckPos()
{
	float4 Length = MoveDir_;

	if (float4::DOWN.CompareInt2D(MoveDir_))
	{
		Length += float4(0.0f, 24.0f);
	}
	if (float4::RIGHT.CompareInt2D(MoveDir_))
	{
		Length += float4(24.0f, 0.0f);
	}
	if (float4::LEFT.CompareInt2D(MoveDir_))
	{
		Length += float4(-24.0f, 0.0f);
	}
	if (float4::UP.CompareInt2D(MoveDir_))
	{
		Length += float4(0.0f, -24.0f);
	}

	float4 Pos = { GetPosition().x + Length.x, GetPosition().y + Length.y };

	return Pos;

}


void Player::CreateDirtTile()
{
	
	float4 Pos = PlayerCollCheckPos();


	TileIndex Index = DirtTileMap_->GetTileIndex({ Pos.x , Pos.y });
	int ChangeIndex = Index.X + (Index.Y * FARM_CHIP_NUM_Y);

	std::map<int, FarmTile*>::iterator FindIter = DirtList_.find(ChangeIndex);
	std::map<int, FarmTile*>::iterator EndIter = DirtList_.end();

	std::map<int, Items*>::iterator ObjectFindIter = MapObject_.find(ChangeIndex);
	std::map<int, Items*>::iterator ObjectEndIter = MapObject_.end();

	
	// 해당 땅이 이미 파져있다면 새로운 타일맵을 생성하지 않음

	if (FindIter != EndIter || ObjectFindIter != ObjectEndIter)
	{
			return;
		
	}

	else {
		FarmTile* Tile = DirtTileMap_->CreateTile<FarmTile>(static_cast<int>(Pos.x / CHIP_SIZE), static_cast<int>(Pos.y / CHIP_SIZE)
			, "hoeDirt.bmp", static_cast<int>(TILE_DIRT::BASIC), (int)PLAYLEVEL::DIRT);
		Tile->TileState_ = TILE_STATE::HOE_DIRT_CREATE;

		//Index = TileMap_->GetTileIndex({ Pos.x , Pos.y });
		//ChangeIndex = Index.X + (Index.Y * FARM_CHIP_NUM_Y);

		DirtList_.insert(std::make_pair(ChangeIndex, Tile));
	}
	//delete Tile;
}



void Player::CreateWaterTile()
{

	float4 Pos = PlayerCollCheckPos();


	TileIndex Index = WetTileMap_->GetTileIndex({ Pos.x , Pos.y });
	int ChangeIndex = Index.X + (Index.Y * FARM_CHIP_NUM_Y);

	std::map<int, FarmTile*>::iterator FindIter = WetDirtList_.find(ChangeIndex);
	std::map<int, FarmTile*>::iterator EndIter = WetDirtList_.end();


	std::map<int, FarmTile*>::iterator FindDIrtIter = DirtList_.find(ChangeIndex);
	std::map<int, FarmTile*>::iterator EndDIrtIter = DirtList_.end();


	//해당 땅이 이미 젖어있다면 + 땅이 파져있지 않으면 패스

	if (FindIter != EndIter && FindDIrtIter == EndDIrtIter)
	{
		return;
	}

	if(FindIter == EndIter && FindDIrtIter != EndDIrtIter)
	{
		FarmTile* Tile = WetTileMap_->CreateTile<FarmTile>(static_cast<int>(Pos.x / CHIP_SIZE), static_cast<int>(Pos.y / CHIP_SIZE)
			, "hoeDirt.bmp",static_cast<int>(TILE_DIRT::BASIC_WET), (int)PLAYLEVEL::WETDIRT);
		Tile->TileState_ = TILE_STATE::HOE_DIRT_WATER;

		WetDirtList_.insert(std::make_pair(ChangeIndex, Tile));
	}


}

void Player::CreateSeed()
{

	float4 Pos = PlayerCollCheckPos();

	TileIndex Index = WetTileMap_->GetTileIndex({ Pos.x , Pos.y });
	int ChangeIndex = Index.X + (Index.Y * FARM_CHIP_NUM_Y);

	std::map<int, FarmTile*>::iterator FindDirtIter = DirtList_.find(ChangeIndex);
	std::map<int, FarmTile*>::iterator EndDirtIter = DirtList_.end();

	std::map<int, Crops*>::iterator FindSeedIter = SeedList_.find(ChangeIndex);
	std::map<int, Crops*>::iterator EndSeedIter = SeedList_.end();


	//땅에 아무것도 없으면, 이미 씨앗이 있으면
	if (FindDirtIter == EndDirtIter&& FindSeedIter!= EndSeedIter)
	{
		return;
	}


	//해당 땅이 파져있으면 씨앗을 심는다.
	if (FindDirtIter != EndDirtIter)
	{

		//TODO: 핸드 아이템의 타입에 따라서 초기화.

		Inventory::MainInventory->GetCurrentItem()->SubItemCount();
		//PlayerHandItem_->SubItemCount();

		Crops* seed = CreateSeedActor<Parsnip_Growing>();

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

		if (Iter->second->IsWall(PlayerCollCheckPos(), GetScale(), MoveDir_) == true)
		{
			
			int Count = RandomItemCount.RandomInt(1, 5);
 			for (int i = 0; i < Count; ++i)
			{
				Items* MiniItem = nullptr;

				if (Iter->second->GetItemNameConstRef() == "SmallWood1"
					|| Iter->second->GetItemNameConstRef() == "SmallWood2")
				{
					MiniItem = CreateSeedActor<MiniWood>();
				}

				else
				{
					return;
				}

				float4 Pos;
				Pos.x = RandomItemPosX.RandomFloat(-30.f, 30.f);
				Pos.y = RamdomItemPosY.RandomFloat(-30.f, 30.f);

				MiniItem->SetPosition({ Iter->second->GetPosition().x + Pos.x, Iter->second->GetPosition().y + Pos.y });
				MiniItem->SetMoveFlag(true);
			}


			Iter->second->Death();
			MapObject_.erase(Iter);

			TileState_ = TILE_COLL::INIT;
			Speed_ = 150.f;
			PlayerState_ = PLAYER_UPDATE::INIT;

			Iter = MapObject_.begin();

		}

		else
		{
			PlayerState_ = PLAYER_UPDATE::INIT;
		}


	}
}

void Player::CrushStone()
{

	for (Iter = MapObject_.begin(); Iter != MapObject_.end(); ++Iter) {

		if (Iter->second->IsWall(PlayerCollCheckPos(), GetScale(), MoveDir_) == true)
		{

			int Count = RandomItemCount.RandomInt(1, 5);
			for (int i = 0; i < Count; ++i)
			{
				Items* MiniItem = nullptr;

				if (Iter->second->GetItemNameConstRef() == "SmallStone")
				{
					MiniItem = CreateSeedActor<MiniStone>();
				}

				else
				{
					return;
				}

				float4 Pos;
				Pos.x = RandomItemPosX.RandomFloat(-30.f, 30.f);
				Pos.y = RamdomItemPosY.RandomFloat(-30.f, 30.f);

				MiniItem->SetPosition({ Iter->second->GetPosition().x + Pos.x, Iter->second->GetPosition().y + Pos.y });
				MiniItem->SetMoveFlag(true);
			}


			Iter->second->Death();
			MapObject_.erase(Iter);

			TileState_ = TILE_COLL::INIT;
			Speed_ = 150.f;
			PlayerState_ = PLAYER_UPDATE::INIT;

			Iter = MapObject_.begin();

		}

		else
		{
			PlayerState_ = PLAYER_UPDATE::INIT;
		}


	}


}


void Player::CrushTree()
{

	for (Iter = MapObject_.begin(); Iter != MapObject_.end(); ++Iter) {

		if (Iter->second->IsWall(PlayerCollCheckPos(), GetScale(), MoveDir_) == true)
		{
			if (Iter->second->GetItemNameConstRef() == "Maple_Tree"
				|| Iter->second->GetItemNameConstRef() == "Fine_Tree"
				|| Iter->second->GetItemNameConstRef() == "Oak_Tree"
				|| Iter->second->GetItemNameConstRef() == "Mahogany_Tree"
				)
			{

				//나무의 데미지가 0이상이면 SubDamage
				if (Iter->second->GetDamage() > 0)
				{

					Iter->second->SubDamage();
					Iter->second->SetCrushAnimation();


					//나무의 데미지가 2이상이면 Top 제거와 나무조각 드랍

					if (Iter->second->GetDamage() == 2)
					{

						int Count = RandomItemCount.RandomInt(1, 5);
						Items* MiniItem;
						for (int i = 0; i < Count; ++i)
						{
							MiniItem = CreateSeedActor<MiniWood>();

							float4 Pos;
							Pos.x = RandomItemPosX.RandomFloat(-60.f, 60.f);
							Pos.y = RamdomItemPosY.RandomFloat(-60.f, 60.f);

							MiniItem->SetPosition({ Iter->second->GetPosition().x + Pos.x, Iter->second->GetPosition().y + Pos.y });
							MiniItem->SetMoveFlag(true);

						}
					}

					Speed_ = 150.f;
					TileState_ = TILE_COLL::INIT;
					PlayerState_ = PLAYER_UPDATE::INIT;

					return;
				}

				//나무의 데미지가 0이면 (주둥이까지 삭제)
				else
				{
					int Count = RandomItemCount.RandomInt(1, 5);
					Items* MiniItem;
					for (int i = 0; i < Count; ++i)
					{
						MiniItem = CreateSeedActor<MiniWood>();

						float4 Pos;
						Pos.x = RandomItemPosX.RandomFloat(-60.f, 60.f);
						Pos.y = RamdomItemPosY.RandomFloat(-60.f, 60.f);

						MiniItem->SetPosition({ Iter->second->GetPosition().x + Pos.x, Iter->second->GetPosition().y + Pos.y });
						MiniItem->SetMoveFlag(true);

					}

					Iter->second->TreeOff();
					MapObject_.erase(Iter);

					Speed_ = 150.f;
					TileState_ = TILE_COLL::INIT;
					PlayerState_ = PLAYER_UPDATE::INIT;

					Iter = MapObject_.begin();

				}
			}

		}

		//빈 땅을 찍어눌렀다면
		else
		{
			Speed_ = 150.f;
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

			if (Iter->second->GetItemType() == ITEMTYPE::FALG)
			{
				continue;
			}
		

			if (Iter->second->IsWall(PlayerCollCheckPos(), GetScale(), MoveDir_) == true) 
			{
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

		if (Iter->second->IsWall(PlayerCollCheckPos(), GetScale(), MoveDir_) == false) {
			
			Speed_ = 150.f;
			//Player_->SetBreakY(false);

			Iter = MapObject_.begin();
			TileState_ = TILE_COLL::NOTACT;
		}

		break;

	}

}


void Player::ChangeDirtTile()
{

	std::map<int, FarmTile*>::iterator EndIter = DirtList_.end();



	for (int i = 0; i < FARM_CHIP_NUM_X * FARM_CHIP_NUM_Y; ++i)
	{

		std::map<int, FarmTile*>::iterator FindLeftIter = DirtList_.find(i - 1);
		std::map<int, FarmTile*>::iterator FindThisIter = DirtList_.find(i);
		std::map<int, FarmTile*>::iterator FindRightIter = DirtList_.find(i + 1);
		std::map<int, FarmTile*>::iterator FindTopIter = DirtList_.find(i - FARM_CHIP_NUM_Y);
		std::map<int, FarmTile*>::iterator FindBottomIter = DirtList_.find(i + FARM_CHIP_NUM_Y);


		//현재 찾으려는 타일이 땅에 없으면 패스
		if (FindThisIter == EndIter) continue;



		//------< 위 아래 아무것도 없을때 x축, 원라인 >------------------------------------------------------------------

		if (FindTopIter == EndIter && FindBottomIter == EndIter)
		{
			//===================================================
			//   case 1 왼쪽 타일은 없는데 오른쪽 타일은 있는경우
			//===================================================

			if (FindLeftIter == EndIter && FindRightIter != EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::W_LINE_LEFT));

			}

			//===================================================
			//   case 2 왼쪽타일은 있는데 오른쪽 타일은 없는경우
			//===================================================

			if (FindLeftIter != EndIter && FindRightIter == EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::W_LINE_RIGHT) );

			}

			//===================================================
			//   case 3 왼쪽 오른쪽 둘 다 있는 경우
			//===================================================

			if (FindLeftIter != EndIter && FindRightIter != EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::W_LINE_MIDDLE) );

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
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::H_LINE_TOP) );

			}


			//===================================================
			//   case 2 위쪽타일은 있는데 아래쪽 타일은 없는경우
			//===================================================

			if (FindTopIter != EndIter && FindBottomIter != EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::H_LINE_MIDDLE) );

			}


			//===================================================
			//   case 3 위쪽 아래쪽 둘 다 있는 경우
			//===================================================

			if (FindTopIter != EndIter && FindBottomIter == EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::H_LINE_BOTTOM) );

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
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::LEFT_TOP) );

			}


			//===================================================
			//   case 2 왼쪽타일은 있는데 오른쪽 타일은 없는경우
			//===================================================

			if (FindLeftIter != EndIter && FindRightIter == EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::RIGHT_TOP) );

			}


			//===================================================
			//   case 3 왼쪽 오른쪽 둘 다 있는 경우
			//===================================================
			if (FindLeftIter != EndIter && FindRightIter != EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::MIDDLE_TOP) );

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
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::LEFT_BOTTOM) );

			}


			//===================================================
			//   case 2 왼쪽타일은 있는데 오른쪽 타일은 없는경우
			//===================================================

			if (FindLeftIter != EndIter && FindRightIter == EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::RIGHT_BOTTOM) );

			}


			//===================================================
			//   case 3 왼쪽 오른쪽 둘 다 있는 경우
			//===================================================
			if (FindLeftIter != EndIter && FindRightIter != EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::MIDDLE_BOTTOM) );

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
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::LEFT_MIDDLE) );

			}


			//===================================================
			//   case 2 왼쪽타일은 있는데 오른쪽 타일은 없는경우
			//===================================================

			if (FindLeftIter != EndIter && FindRightIter == EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::RIGHT_MIDDLE) );

			}


			//===================================================
			//   case 3 왼쪽 오른쪽 둘 다 있는 경우
			//===================================================
			if (FindLeftIter != EndIter && FindRightIter != EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::MIDDLE_MIDDLE) );

			}

		}

		//------< 사방에 아무것도 없다면 >------------------------------------------------------------------

		if (FindLeftIter == EndIter && FindRightIter == EndIter && FindTopIter == EndIter && FindBottomIter == EndIter)
		{
			FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::BASIC) );

		}

		//------< 이모든것에 속하지 않는다 >------------------------------------------------------------------

		//if (FindLeftIter == EndIter || FindRightIter == EndIter || FindTopIter == EndIter || FindBottomIter == EndIter)
		//{
		//	return;

		//}

	}


}


void Player::ChangeWetDirtTile()
{

	std::map<int, FarmTile*>::iterator EndIter = WetDirtList_.end();


	for (int i = 0; i < FARM_CHIP_NUM_X * FARM_CHIP_NUM_Y; ++i)
	{

		std::map<int, FarmTile*>::iterator FindLeftIter = WetDirtList_.find(i - 1);
		std::map<int, FarmTile*>::iterator FindThisIter = WetDirtList_.find(i);
		std::map<int, FarmTile*>::iterator FindRightIter = WetDirtList_.find(i + 1);
		std::map<int, FarmTile*>::iterator FindTopIter = WetDirtList_.find(i - FARM_CHIP_NUM_Y);
		std::map<int, FarmTile*>::iterator FindBottomIter = WetDirtList_.find(i + FARM_CHIP_NUM_Y);


		//현재 찾으려는 타일이 땅에 없으면 패스
		if (FindThisIter == EndIter) continue;



		//------< 위 아래 아무것도 없을때 x축, 원라인 >------------------------------------------------------------------

		if (FindTopIter == EndIter && FindBottomIter == EndIter)
		{
			//===================================================
			//   case 1 왼쪽 타일은 없는데 오른쪽 타일은 있는경우
			//===================================================

			if (FindLeftIter == EndIter && FindRightIter != EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::W_LINE_LEFT_WET));
				
			}

			//===================================================
			//   case 2 왼쪽타일은 있는데 오른쪽 타일은 없는경우
			//===================================================

			if (FindLeftIter != EndIter && FindRightIter == EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::W_LINE_RIGHT_WET));

			}

			//===================================================
			//   case 3 왼쪽 오른쪽 둘 다 있는 경우
			//===================================================

			if (FindLeftIter != EndIter && FindRightIter != EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::W_LINE_MIDDLE_WET));

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
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::H_LINE_TOP_WET));

			}


			//===================================================
			//   case 2 위쪽타일은 있는데 아래쪽 타일은 없는경우
			//===================================================

			if (FindTopIter != EndIter && FindBottomIter != EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::H_LINE_MIDDLE_WET));

			}


			//===================================================
			//   case 3 위쪽 아래쪽 둘 다 있는 경우
			//===================================================

			if (FindTopIter != EndIter && FindBottomIter == EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::H_LINE_BOTTOM_WET));

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
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::LEFT_TOP_WET));

			}


			//===================================================
			//   case 2 왼쪽타일은 있는데 오른쪽 타일은 없는경우
			//===================================================

			if (FindLeftIter != EndIter && FindRightIter == EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::RIGHT_TOP_WET));

			}


			//===================================================
			//   case 3 왼쪽 오른쪽 둘 다 있는 경우
			//===================================================
			if (FindLeftIter != EndIter && FindRightIter != EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::MIDDLE_TOP_WET));

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
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::LEFT_BOTTOM_WET));

			}


			//===================================================
			//   case 2 왼쪽타일은 있는데 오른쪽 타일은 없는경우
			//===================================================

			if (FindLeftIter != EndIter && FindRightIter == EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::RIGHT_BOTTOM_WET));

			}


			//===================================================
			//   case 3 왼쪽 오른쪽 둘 다 있는 경우
			//===================================================
			if (FindLeftIter != EndIter && FindRightIter != EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::MIDDLE_BOTTOM_WET));

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
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::LEFT_MIDDLE_WET));

			}


			//===================================================
			//   case 2 왼쪽타일은 있는데 오른쪽 타일은 없는경우
			//===================================================

			if (FindLeftIter != EndIter && FindRightIter == EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::RIGHT_MIDDLE_WET));

			}


			//===================================================
			//   case 3 왼쪽 오른쪽 둘 다 있는 경우
			//===================================================
			if (FindLeftIter != EndIter && FindRightIter != EndIter)
			{
				FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::MIDDLE_MIDDLE_WET));

			}

		}

		//------< 사방에 아무것도 없다면 >------------------------------------------------------------------

		if (FindLeftIter == EndIter && FindRightIter == EndIter && FindTopIter == EndIter && FindBottomIter == EndIter)
		{
			FindThisIter->second->GetRenderer()->SetIndex(static_cast<int>(TILE_DIRT::BASIC_WET));

		}

		//------< 이모든것에 속하지 않는다 >------------------------------------------------------------------

		//if (FindLeftIter == EndIter || FindRightIter == EndIter || FindTopIter == EndIter || FindBottomIter == EndIter)
		//{
		//	return;

		//}

	}

}