#pragma once
#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineSound.h>

#include "TileData.h"
#include "RendererData.h"

#include "PlayerEnergyFrame.h"
#include "MainUI.h"
#include "BackGround.h"
#include "Player.h"
#include "Inventory.h"
#include "Items.h"
#include "Npc.h"
#include "Mouse.h"
#include "PlayerHPFrame.h"

// 설명 :
class Mine3 : public GameEngineLevel
{
public:
	// constrcuter destructer
	Mine3();
	~Mine3();

	// delete Function
	Mine3(const Mine3& _Other) = delete;
	Mine3(Mine3&& _Other) noexcept = delete;
	Mine3& operator=(const Mine3& _Other) = delete;
	Mine3& operator=(Mine3&& _Other) noexcept = delete;

private:
	void Loading() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _NextLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

private:

	BackGround* BackGround_;
	BackGround* BackGroundFront_;

	GameEngineSoundPlayer BgmPlayer;

	std::map<int, Items*> MapObject_;
	std::map<std::string, Monster*> MonsterList_;	//검색할 일이 없으면 다른 자료 구조로 바꿀 예정

private:
	void LoadMapObject();

};

