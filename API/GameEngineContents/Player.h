#pragma once

#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRendererTileMap.h>

#include "RendererData.h"
#include"TileData.h"
#include "PlayerData.h"
#include "Hoe.h"
#include "Mouse.h"
#include "Inventory.h"
#include "GameData.h"

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

enum class TILE_CHANGE
{
	INIT= 0,
	THIS_CHECK ,
	LEFT_CHECK,
	RIGHT_CHECK,


};

//class PlayerMove;

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

	float4 CameraPos_;

	//void moveX();
	//void moveY();



public:

	//Inventory* GetInventory() {
	//	return Inventory_;
	//}


	//void SetInventory(Inventory* i) {
	//	Inventory_ = i;
	//}

	void PlayerDataSave();
	TOOLTYPE CurrentItemType();

	void SetSpeed(float f) 
	{
		Speed_ = f;
	}

	void SetObjectColl(bool b) 
	{
		ObjectColl_ = b;
	}


	bool GetObjectColl() 
	{
		return ObjectColl_;
	}

	void SetCurrentLevel(std::string s) 
	{
		CurrentLevel_ = s;
	}

	void SetPrevLevel(std::string s) 
	{
		PrevLevel_ = s;
	}

	float4 GetCurrentDir()
	{
		return MoveDir_;
	}


	inline void SetTileMap(GameEngineRendererTileMap* _TileMap)
	{
		TileMap_ = _TileMap;
	}
	
	PLAYER_UPDATE GetPlayerState()
	{
		return PlayerState_;
	}

	bool GetUsingAxe()
	{
		return UsingAxe_;
	}

	void SetUsingAxe(bool b)
	{
		UsingAxe_ = b;
	}

	void CopyList(std::list <Items*> _OtherList)
	{
		std::copy(_OtherList.begin(), _OtherList.end(), std::back_inserter(MapObject_));
	}


	GameEngineRenderer* Renderer() {
		return PlayerRenderer_;
	}

	GameEngineImage* CollImage() {
		return MapColImage_;
	}


private:
	float MapSizeX_;
	float MapSizeY_;
	float AnimationFrame_;
	float Speed_;
	float Energy_;
	float4 MoveDir_;
	float4 MovePrevDir_;

	bool FarmingArea_;
	bool ObjectColl_;
	bool UsingAxe_;
	bool UsingPickaxe_;

	std::vector<GameEngineCollision*> ColList;
	std::map<int, FarmTile*> TileList_;

	GameEngineRenderer* PlayerRenderer_;
	GameEngineCollision* PlayerCollider_;
	GameEngineRendererTileMap* TileMap_;
	GameEngineImage* MapColImage_;

	Items* CurrentItem_;
	TOOLTYPE CurrentItemType_;

	TILE_CHANGE TileChangeState_;
	PLAYER_UPDATE PlayerState_;
	TILE_COLL TileState_;


	Mouse* Mouse_;
	Hoe* Hoe_;
	Inventory* Inventory_;

	static std::string CurrentLevel_;
	static std::string PrevLevel_;

	std::list<Items*> MapObject_;
	std::list<Items*>::iterator Iter;

private:


	bool isStop();
	bool isMove();

	void SetDirAnimation();
	void DirAnimationChange();
	void SetCamera();

	void PlayerWalk();
	void PlayerDirCheck();
	float4 PlayerCollCheckPos();
	void ChangeLevel();
	void SetPlayerStartPos();
	void CollInit();
	void CheckTool();

	//Å¸ÀÏ
	void CreateDirtTile();
	void CreateWaterTile();
	void ChangeTile();
	void ObjectTileColl();
	void CrushWood();

	std::string GetCurrentLevel()
	{
		return GetLevel()->GetNameConstRef();
	}


	float GetEnergy() {
		return Energy_;
	}

	void SetPlayerSpeed(float f) {
		Speed_ = f;
	}

	float GetPlayerSpeed() {
		return Speed_;
	}


	std::string GetDirString();

	void SubEnergy() {
		Energy_ -= 3.0f * GameEngineTime::GetDeltaTime();
	}


	bool PlayerMouseClickCollision() {

		return (PlayerCollider_->CollisionResult("MouseCursor", ColList, CollisionType::Rect, CollisionType::Rect))
			&& (Mouse_->isMouseClick());
	}

	bool MoveFarmCollision() {

		return (PlayerCollider_->CollisionResult("MoveFarm", ColList, CollisionType::Rect, CollisionType::Rect));
	}

	bool MoveHouseCollision() {

		return (PlayerCollider_->CollisionResult("MoveHouse", ColList, CollisionType::Rect, CollisionType::Rect));
	}


	bool MoveBusStopCollision() {

		return (PlayerCollider_->CollisionResult("MoveBusStop", ColList, CollisionType::Rect, CollisionType::Rect));
	}


	bool MoveTownCollision() {

		return (PlayerCollider_->CollisionResult("MoveTown", ColList, CollisionType::Rect, CollisionType::Rect));
	}


	bool MoveBackForestCollision() {

		return (PlayerCollider_->CollisionResult("MoveForest", ColList, CollisionType::Rect, CollisionType::Rect));
	}

};

