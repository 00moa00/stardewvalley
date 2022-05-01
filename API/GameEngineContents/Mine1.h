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

// Ό³Έν :
class Mine1 : public GameEngineLevel
{
public:
	// constrcuter destructer
	Mine1();
	~Mine1();

	// delete Function
	Mine1(const Mine1& _Other) = delete;
	Mine1(Mine1&& _Other) noexcept = delete;
	Mine1& operator=(const Mine1& _Other) = delete;
	Mine1& operator=(Mine1&& _Other) noexcept = delete;

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

