#include "Player.h"
#include "TreeTop.h"
#include "MainUI.h"
#include "StoneEffect.h"
#include "WoodEffect.h"
#include "WateringCanEffect.h"

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
		Length = float4(0.0f, 24.0f);
	}
	if (float4::RIGHT.CompareInt2D(MoveDir_))
	{
		Length = float4(24.0f, 0.0f);
	}
	if (float4::LEFT.CompareInt2D(MoveDir_))
	{
		Length = float4(-24.0f, 0.0f);
	}
	if (float4::UP.CompareInt2D(MoveDir_))
	{
		Length = float4(0.0f, -24.0f);
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


	std::map<int, FarmTile*>::iterator FindDirtIter = DirtList_.find(ChangeIndex);
	std::map<int, FarmTile*>::iterator EndDirtIter = DirtList_.end();


	//해당 땅이 이미 젖어있다면 + 땅이 파져있지 않으면 패스

	if (FindIter != EndIter && FindDirtIter == EndDirtIter)
	{
		return;
	}

	if(FindIter == EndIter && FindDirtIter != EndDirtIter)
	{
	

		FarmTile* Tile = WetTileMap_->CreateTile<FarmTile>(static_cast<int>(Pos.x / CHIP_SIZE), static_cast<int>(Pos.y / CHIP_SIZE)
			, "hoeDirt.bmp",static_cast<int>(TILE_DIRT::BASIC_WET), (int)PLAYLEVEL::WETDIRT);
		Tile->TileState_ = TILE_STATE::HOE_DIRT_WATER;

		WetDirtList_.insert(std::make_pair(ChangeIndex, Tile));


	}


}

void Player::CreateWaterEffet()
{
	float4 Pos = PlayerCollCheckPos();
	float MarginX = 0;

	if (MoveDir_ .CompareInt2D(float4::RIGHT))
	{
		MarginX = 24.f;
	}

	if (MoveDir_.CompareInt2D(float4::LEFT))
	{
		MarginX = -24.f;
	}


	WateringCanEffect* WateringCanEffect_ = GetLevel()->CreateActor<WateringCanEffect>(static_cast<int>(PLAYLEVEL::BOTTOM_EFFECT));
	WateringCanEffect_->SetPosition({ Pos.x + MarginX, Pos.y});

	if (GetCurrentLevel() == "MyHouseLevel")
	{
		WateringCanEffect_->GetRenderer()->CameraEffectOff();
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


	//땅이 파져 있지 않으면, 이미 씨앗이 있으면
	if (FindDirtIter == EndDirtIter || FindSeedIter != EndSeedIter)
	{
		return;
	}


	//해당 땅이 파져있으면 씨앗을 심는다.
	if (FindDirtIter != EndDirtIter)
	{

		//TODO: 핸드 아이템의 타입에 따라서 초기화.
		
		GetCurrentItem()->SubItemCount();

		Crops* seed = GetCurrentItem()->CreateCrops();
			
		float4 TileSize_ = { 48.f, 48.f };
		float4 WorldPos = TileSize_;

		WorldPos.x *= static_cast<int>(Pos.x / CHIP_SIZE);
		WorldPos.y *= static_cast<int>(Pos.y / CHIP_SIZE);

		WorldPos += TileSize_.Half();

		//seed->GetRenderer()->SetPivot({ WorldPos.x, WorldPos.y - 24.f });
		seed->SetTileFindIndex(ChangeIndex);
		seed->SetPosition({ WorldPos.x, WorldPos.y - 24.f });

		SeedList_.insert(std::make_pair(ChangeIndex, seed));

	}


}

void Player::harvestingCrops()
{
	float4 Pos = PlayerCollCheckPos();

	TileIndex Index = WetTileMap_->GetTileIndex({ Pos.x , Pos.y });
	int ChangeIndex = Index.X + (Index.Y * FARM_CHIP_NUM_Y);

	std::map<int, Crops*>::iterator FindSeedIter = SeedList_.find(ChangeIndex);
	std::map<int, Crops*>::iterator EndSeedIter = SeedList_.end();


	//씨앗이 없으면, 씨앗이 아직 수확가능 상태가 아니라면
	if (FindSeedIter == EndSeedIter || FindSeedIter->second->GetisHarvest() == false)
	{
		return;
	}

	if (MainMouse_->isMouseClick())
	{
		FindSeedIter->second->DropCropsInMap();

		SeedList_.erase(ChangeIndex);
		//FindSeedIter->second->Death();
	}

}

void Player::CrushWood()
{

	for (Iter = MapObject_.begin(); Iter != MapObject_.end(); ++Iter) {

		if (Iter->second->ItemCheck(PlayerCollCheckPos(), GetScale()) == true)
		{
			if (Iter->second->GetItemType() == ITEMTYPE::WOOD)

			{

				WoodEffect* StoneAnimation_ = GetLevel()->CreateActor<WoodEffect>();
				StoneAnimation_->SetParticlesPosition({ Iter->second->GetPosition().x , Iter->second->GetPosition().y });

				//아이템 드랍
				Iter->second->DropItemInMap();

				//해당 아이템 삭제
				Iter->second->Death();
				MapObject_.erase(Iter);

				//스테이트 초기화
				TileState_ = TILE_COLL::INIT;
				PlayerState_ = PLAYER_UPDATE::INIT;

				//이터레이터 초기화
				Iter = MapObject_.begin();
			}

			else
			{
				return;
			}

			//도끼질을 했다면 기력 감소
			SubEnergy(2.f);
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

		if (Iter->second->ItemCheck(PlayerCollCheckPos(), GetScale()) == true)
		{
			if (Iter->second->GetItemType() == ITEMTYPE::STONE)
			{

				StoneEffect* StoneAnimation_ = GetLevel()->CreateActor<StoneEffect>();
				StoneAnimation_->SetParticlesPosition({ Iter->second->GetPosition().x ,   Iter->second->GetPosition().y });

				//아이템 드랍
				Iter->second->DropItemInMap();

				//해당 아이템 삭제
				Iter->second->Death();
				Player::MapObject_.erase(Iter);

				//스테이트 초기화
				TileState_ = TILE_COLL::INIT;
				PlayerState_ = PLAYER_UPDATE::INIT;

				//이터레이터 초기화
				Iter = Player::MapObject_.begin();
			}

			else
			{
				return;
			}

			//곡괭이질을 했다면 체력 감소
			SubEnergy(2.f);

		}

		else
		{
			PlayerState_ = PLAYER_UPDATE::INIT;
		}

	}

}

void Player::CrushTree()
{

	for (Iter = Player::MapObject_.begin(); Iter != Player::MapObject_.end(); ++Iter)
	{

		if (Iter->second->ItemCheck(PlayerCollCheckPos(), GetScale()) == true
			&& Iter->second->GetItemType() == ITEMTYPE::TREE)
		{
			WoodEffect* StoneAnimation_ = GetLevel()->CreateActor<WoodEffect>();
			StoneAnimation_->SetParticlesPosition({ Iter->second->GetPosition().x , Iter->second->GetPosition().y });

			//나무가 살아있다
			if (Iter->second->GetDamage() > 0)
			{
				//데미지를 깎으면서 애니메이션 변경
				Iter->second->SubDamage();
				Iter->second->SetCrushAnimation();


				//나무의 데미지가 2면 Top 제거(해당 업데이트 함수)와 나무조각 드랍
				if (Iter->second->GetDamage() == 2)
				{
				}

				//스테이트 초기화
				TileState_ = TILE_COLL::INIT;
				PlayerState_ = PLAYER_UPDATE::INIT;

				return;
			}

			//나무의 데미지가 0이면 (주둥이까지 삭제)
			else
			{
				//드랍 아이템
				Iter->second->DropItemInMap();

				//해당 아이템 삭제
				Iter->second->Death();
				Player::MapObject_.erase(Iter);

				//스테이트 초기화
				TileState_ = TILE_COLL::INIT;
				PlayerState_ = PLAYER_UPDATE::INIT;


				//이터레이터 초기화
				Iter = Player::MapObject_.begin();

			}
			//도끼질을 했다면 기력 감소
			SubEnergy(2.f);

		}

		//빈 땅을 찍어눌렀다면
		else
		{
			PlayerState_ = PLAYER_UPDATE::INIT;
		}

	}
}

void Player::GetItem()
{

	std::map<int, Items*>::iterator GetItemIter = MapObject_.begin();


	for (; GetItemIter != MapObject_.end(); ++GetItemIter) {

		if (GetItemIter->second->ItemCheck(PlayerCollCheckPos(), GetScale()) == true
			&& GetItemIter->second->GetItemType() == ITEMTYPE::GETITEM
			&& MainMouse_->isMouseClick() == true
			&& GetCurrentItem()->GetItemType() != ITEMTYPE::TOOL)
		{
			//이벤트용이 아닌 아이템을 습득하는 일이 있다면 예외 설정 해야함
			GetItemIter->second->ItemCollPlayer();
			MapObject_.erase(GetItemIter);
			GetItemIter = MapObject_.begin();
		}

		else
		{
			PlayerState_ = PLAYER_UPDATE::INIT;

		}
	}
}

void Player::CheckShippingBox()
{
	std::map<int, Items*>::iterator ShippingIter = MapObject_.begin();

	if (GetCurrentLevel() == "MyFarmLevel")
	{
		for (; ShippingIter != MapObject_.end(); ++ShippingIter) {

			if (ShippingIter->second->ItemCheck(PlayerCollCheckPos(), GetScale()) == true
				&& ShippingIter->second->GetItemType() == ITEMTYPE::SHIPPINGBOX)
			{
				//이벤트용이 아닌 아이템을 습득하는 일이 있다면 예외 설정 해야함
				ShippingIter->second->ItemCollPlayer();
			}

			else
			{
				ShippingIter->second->ItemCollFalsePlayer();
			}
		}
	}
}

void Player::ClearWetDirtTile()
{
	if (WetDirtList_.empty() == false)
	{
		if (MainUI::MainMainUI->DayOver() == true)
		{
			WetTileMap_->DeleteTile();
			WetDirtList_.erase(WetDirtList_.begin(), WetDirtList_.end());
		}
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