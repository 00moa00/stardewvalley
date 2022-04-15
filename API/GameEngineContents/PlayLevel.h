#pragma once
#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineSound.h>


#include "TileData.h"
#include "RendererData.h"

#include "PlayerEnergyBar.h"
#include "PlayerEnergyFrame.h"
#include "MainUI.h"

#include "BackGround.h"

#include "Player.h"
#include "Inventory.h"
#include "Items.h"
#include "Mouse.h"

#include <list>


// Ό³Έν :
class PlayLevel : public GameEngineLevel
{
public:
	static Player* MainPlayer_;
	static Inventory* MainInventory_;

	// constrcuter destructer
	PlayLevel();
	~PlayLevel();

	// delete Function
	PlayLevel(const PlayLevel& _Other) = delete;
	PlayLevel(PlayLevel&& _Other) noexcept = delete;
	PlayLevel& operator=(const PlayLevel& _Other) = delete;
	PlayLevel& operator=(PlayLevel&& _Other) noexcept = delete;

protected:

	//void LevelChangeStart() override;
	void LevelChangeEnd() override;

	MainUI* MainUI_;
	//std::map<int, Items*> MapObject_;

	//Inventory* Inventory_;

	Player* Player_;
	//Inventory* Inventory_;
	PlayerEnergyBar* PlayerEnergyBar_;
	PlayerEnergyFrame* PlayerEnergyFrame_;
	BackGround* BackGround_;
	BackGround* BackGroundFront_;

private:

};

