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
#include "Npc.h"

#include <vector>
#include <map>
#include <algorithm>
#include <iterator>

enum class TILE_STATE 
{
	HOE_DIRT_CREATE,
	HOE_DIRT_WATER,
	CLEAR,
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
	static Mouse* MainMouse_;
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
	const char* ArrAnimationToolName[static_cast<int>(PLAYER_UPDATE::MAX)];

	int Money_;
	int Energy_;

	float MapSizeX_;
	float MapSizeY_;
	float AnimationFrame_;
	float Speed_;

	float4 MoveDir_;
	float4 CameraPos_;

	bool FarmingArea_;
	bool ObjectColl_;
	bool isShopping_;
	bool isEvent_;

	GameEngineRenderer* PlayerBodyRenderer_;
	GameEngineRenderer* PlayerPantsRenderer_;
	GameEngineRenderer* PlayerShirtsRenderer_;
	GameEngineRenderer* PlayerHairRenderer_;
	GameEngineRenderer* PlayerHandRenderer_;


	GameEngineRenderer* ToolRenderer_;
	GameEngineCollision* PlayerCollider_;

	GameEngineRendererTileMap* DirtTileMap_;
	GameEngineRendererTileMap* WetTileMap_;

	GameEngineImage* MapColImage_;

	//Mouse* Mouse_;

	TOOLTYPE CurrentItemType_;

	PLAYER_SHOPPING PlayerShoppingState_;
	PLAYER_UPDATE PlayerState_;
	TILE_COLL TileState_;
	USE_TOOL UseToolState_;


	static std::string CurrentLevel_;
	static std::string PrevLevel_;


	std::map<int, FarmTile*> DirtList_;
	std::map<int, FarmTile*> WetDirtList_;
	std::map<int, Crops*> SeedList_;

	std::map<int, Items*> MapObject_;
	std::map<std::string, Npc*> NpcList_;

	std::vector<GameEngineCollision*> ColList;
	std::map<int, Items*>::iterator Iter;


public:

	//------< 공개 함수 >------------------------------------------------------------------


	//================================
	//     Getter
	//================================

	float4 GetMoveDir();

	int GetMoney();

	int GetEnergy();

	bool GetObjectColl();
	bool GetisShopping();
	bool FindWetDirt(int _Index);
	bool GetPlayerShoppingStateShopping();

	std::string GetCurrentLevel();

	Items* GetCurrentItem();
	TOOLTYPE CurrentItemType();
	PLAYER_SHOPPING GetPlayerShoppingState();
	PLAYER_UPDATE GetPlayerState();
	Inventory* GetInventroy();
	GameEngineRenderer* Renderer();
	GameEngineImage* CollImage();

	//================================
	//    Setter
	//================================

	void SetResetPlayerHandItem();

	bool SubMoney(int _Money);
	void AddMoney(int _Money);

	void SetisShopping(bool b);
	void SetObjectColl(bool b);
	void SetCurrentLevel(std::string s);

	void SetPrevLevel(std::string s);
	void SetDirtTileMap(GameEngineRendererTileMap* _TileMap);
	void SetWetTileMap(GameEngineRendererTileMap* _TileMap);

	void DeleteSeedList(int _Index);

	void SetPlayerDirDown();
	void SetisEvent(bool _Flag);

	//================================
	//    Etc
	//================================

	void CopyList(std::map<int, Items*> _OtherList);
	void CopyList(std::map<std::string, Npc*> _OtherList);

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

	void CheckTool();

	void NpcCollCheck();

	// 메인 업데이트 함수
	void PlayerUpdate();
	void LevelInit();

	//================================
	//    플레이어 기본
	//================================

	bool isStop();
	bool isMove();
	void PlayerWalk();
	void PlayerDirCheck();
	void SetPlayerHandItemPos();
	void SubEnergy(int _Energy);

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
	void CreateWaterEffet();

	void ChangeDirtTile();
	void ChangeWetDirtTile();

	void CrushWood();
	void CrushStone();
	void CrushTree();

	void GetItem();
	void CheckShippingBox();

	void harvestingCrops();

	void ClearWetDirtTile();

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


};

