#pragma once

#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRendererTileMap.h>

#include "RendererData.h"
#include "TileData.h"
#include "PlayerData.h"
#include "Hoe.h"
#include "Mouse.h"
#include "Inventory.h"
#include "GameData.h"
#include "Font.h"

#include <list>
#include <map>
#include <algorithm>
#include <iterator>

enum class TILE_STATE {
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
	static Inventory* MainInventory;

	// constrcuter destructer
	Player();
	~Player();

protected:
	void Start() override;
	void Update() override;
	void Render() override;
	void LevelChangeStart() override;
	void LevelChangeEnd() override;

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

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


	GameEngineRenderer* PlayerRenderer_;
	GameEngineCollision* PlayerCollider_;
	GameEngineRendererTileMap* TileMap_;
	GameEngineImage* MapColImage_;

	Items* CurrentItem_;
	TOOLTYPE CurrentItemType_;

	PLAYER_UPDATE PlayerState_;
	TILE_COLL TileState_;
	USE_TOOL UseToolState_;

	//Font* Font_;
	Mouse* Mouse_;
	Hoe* Hoe_;
	Inventory* Inventory_;

	static std::string CurrentLevel_;
	static std::string PrevLevel_;


	std::vector<GameEngineCollision*> ColList;
	std::map<int, FarmTile*> TileList_;
	std::list<Items*> MapObject_;
	std::list<Items*>::iterator Iter;


public:

	//------< 공개 함수 >------------------------------------------------------------------


	//================================
	//     Getter
	//================================

	bool GetObjectColl();
	std::string GetCurrentLevel();

	PLAYER_UPDATE GetPlayerState();

	float GetEnergy();
	int GetMoney();

	GameEngineRenderer* Renderer();
	GameEngineImage* CollImage();


	//================================
	//    Setter
	//================================

	void SetObjectColl(bool b);
	void SetCurrentLevel(std::string s);

	TOOLTYPE CurrentItemType();
	void SetPrevLevel(std::string s);
	void SetTileMap(GameEngineRendererTileMap* _TileMap);

	//================================
	//    Etc
	//================================

	void CopyList(std::list <Items*> _OtherList);



private:

	//------< 비공개 함수 >------------------------------------------------------------------

	void SetCamera();
	void ChangeLevel();

	//================================
	//    업데이트, 체크
	//================================

	void SetPlayerStartPos();
	void CollInit();
	void CheckTool();

	void PlayerUpdate();

	//================================
	//    플레이어 기본
	//================================

	bool isStop();
	bool isMove();
	void PlayerWalk();
	void PlayerDirCheck();
	void SubEnergy();

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
	void ChangeTile();
	void ObjectTileColl();
	void CrushWood();


private:

	//------< 마우스, 충돌 관련 >------------------------------------------------------------------


	bool PlayerMouseClickCollision();

	bool MoveFarmCollision();
	bool MoveHouseCollision();
	bool MoveBusStopCollision();
	bool MoveTownCollision();
	bool MoveBackForestCollision();

};

