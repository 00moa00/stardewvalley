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
class Mine4 : public GameEngineLevel
{
public:
	// constrcuter destructer
	Mine4();
	~Mine4();

	// delete Function
	Mine4(const Mine4& _Other) = delete;
	Mine4(Mine4&& _Other) noexcept = delete;
	Mine4& operator=(const Mine4& _Other) = delete;
	Mine4& operator=(Mine4&& _Other) noexcept = delete;

private:
	void Loading() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _NextLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

private:

	BackGround* BackGround_;
	BackGround* BackGroundFront_;

	std::map<int, Items*> MapObject_;

private:
	void LoadMapObject();
};

