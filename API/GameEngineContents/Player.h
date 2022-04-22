#pragma once

#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRendererTileMap.h>
#include <GameEngineBase/GameEngineRandom.h>

#include "RendererData.h"
#include "TileData.h"
#include "PlayerData.h"
#include "GameData.h"

#include "Hoe.h"
#include "Mouse.h"
#include "Inventory.h"
#include "Font.h"
#include "PlayerHandItem.h"
#include "Parsnip_Crops.h"
#include "DropStone.h"
#include "DropWood.h"
#include "Shop.h"
#include "Crops.h"

#include <list>
#include <map>
#include <algorithm>
#include <iterator>

enum class TILE_STATE 
{
	HOE_DIRT_CREATE,
	HOE_DIRT_WATER,
};

class FarmTile : public Tile
{
public:
	TILE_STATE TileState_;

	Tile* GetTile() 
	{
		return this;
	}

	TILE_STATE GetTileState() 
	{
		return TileState_;
	}

	void SetTileState(TILE_STATE _state) 
	{
		TileState_ = _state;
	}
};


class Inventory;
class Player : public GameEngineActor
{

public:
	static Player* MainPlayer;
	static PlayerHandItem* PlayerHandItem_;

	// constrcuter destructer
	Player();
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

private:

	void Start() override;
	void Update() override;
	void Render() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

private:

	const char* ArrAnimationName[static_cast<int>(PLAYER_UPDATE::MAX)];

	int Money_;

	float MapSizeX_;
	float MapSizeY_;
	float AnimationFrame_;
	float Speed_;
	float Energy_;

	float4 MoveDir_;
	float4 MovePrevDir_;
	float4 CameraPos_;

	bool FarmingArea_;
	bool ObjectColl_;
	bool UsingAxe_;
	bool UsingPickaxe_;
	bool isShopping_;

	GameEngineRenderer* PlayerRenderer_;
	GameEngineCollision* PlayerCollider_;

	GameEngineRendererTileMap* DirtTileMap_;
	GameEngineRendererTileMap* WetTileMap_;

	GameEngineImage* MapColImage_;

	Mouse* Mouse_;
	Hoe* Hoe_;

	GameEngineRandom RandomItemCount;
	GameEngineRandom RandomItemPosX;
	GameEngineRandom RamdomItemPosY;

	TOOLTYPE CurrentItemType_;

	PLAYER_SHOPPING PlayerShoppingState_;
	PLAYER_UPDATE PlayerState_;
	TILE_COLL TileState_;
	USE_TOOL UseToolState_;


	static std::string CurrentLevel_;
	static std::string PrevLevel_;


	std::vector<GameEngineCollision*> ColList;

	std::map<int, FarmTile*> DirtList_;
	std::map<int, FarmTile*> WetDirtList_;

	std::map<int, Crops*> SeedList_;

	std::map<int, Items*> MapObject_;
	std::map<int, Items*>::iterator Iter;


public:

	//------< 공개 함수 >------------------------------------------------------------------


	//================================
	//     Getter
	//================================

	bool GetObjectColl();
	bool GetisShopping();

	float GetEnergy();
	int GetMoney();

	std::string GetCurrentLevel();

	TOOLTYPE CurrentItemType();
	PLAYER_SHOPPING GetPlayerShoppingState();
	bool GetPlayerShoppingStateShopping();
	PLAYER_UPDATE GetPlayerState();
	Inventory* GetInventroy();
	GameEngineRenderer* Renderer();
	GameEngineImage* CollImage();


	//================================
	//    Setter
	//================================

	void SetResetPlayerHandItem();

	void SubMoney(int _Money);
	void AddMoney(int _Money);

	void SetisShopping(bool b);
	void SetObjectColl(bool b);
	void SetCurrentLevel(std::string s);

	void SetPrevLevel(std::string s);
	void SetDirtTileMap(GameEngineRendererTileMap* _TileMap);
	void SetWetTileMap(GameEngineRendererTileMap* _TileMap);


	//================================
	//    Etc
	//================================

	void CopyList(std::map<int, Items*> _OtherList);


private:

	//------< 비공개 함수 >------------------------------------------------------------------


	//================================
	//    업데이트, 체크, 체인지
	//================================
	void PlayerShopping();

	void SetCamera();
	void SetPlayerStartPos();

	void ChangeLevel();
	void ChangeHandItem();

	void CollInit();
	void CheckTool();

	// 메인 업데이트 함수
	void PlayerUpdate();

	//================================
	//    플레이어 기본
	//================================

	bool isStop();
	bool isMove();
	void PlayerWalk();
	void PlayerDirCheck();
	void SubEnergy();
	void SetPlayerHandItemPos();

	//================================
	//   애니메이션
	//================================

	void SetDirAnimation();
	void DirAnimationChange();
	std::string GetDirString();


	//================================
	//   충돌, 타일
	//================================
	
	float4 PlayerCollCheckPos();

	void CreateDirtTile();
	void CreateWaterTile();
	void ChangeDirtTile();
	void ChangeWetDirtTile();

	void ObjectTileColl();
	void CrushWood();
	void CrushStone();
	void CrushTree();


	//------< 마우스, 충돌 관련 >------------------------------------------------------------------


	bool PlayerMouseClickCollision();

	bool MoveFarmCollision();
	bool MoveHouseCollision();
	bool MoveBusStopCollision();
	bool MoveTownCollision();
	bool MoveShopCollision();
	bool MoveBackForestCollision();

	bool MouseClickAndColl();

	//------< 씨앗 생성 >------------------------------------------------------------------

	void CreateSeed();

	template<typename Actor>
	Actor* CreateSeedActor()
	{
		Actor* Item = GetLevel()->CreateActor<Actor>(static_cast<int>(PLAYLEVEL::SEED));
		return Item;
	}

	template<typename Actor>
	Actor* CreateMiniActor()
	{
		Actor* Item = GetLevel()->CreateActor<Actor>(static_cast<int>(PLAYLEVEL::SEED));
		return Item;
	}

};

