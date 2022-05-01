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

	std::map<int, Items*> MapObject_;

private:
	void LoadMapObject();

};

