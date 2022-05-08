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

// Ό³Έν :
class Mine2 : public GameEngineLevel
{
public:
	// constrcuter destructer
	Mine2();
	~Mine2();

	// delete Function
	Mine2(const Mine2& _Other) = delete;
	Mine2(Mine2&& _Other) noexcept = delete;
	Mine2& operator=(const Mine2& _Other) = delete;
	Mine2& operator=(Mine2&& _Other) noexcept = delete;

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

private:
	void LoadMapObject();

};

