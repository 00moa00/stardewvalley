#pragma once
#include "PlayLevel.h"

// Ό³Έν :
class TownLevel : public PlayLevel
{
public:
	// constrcuter destructer
	TownLevel();
	~TownLevel();

	// delete Function
	TownLevel(const TownLevel& _Other) = delete;
	TownLevel(TownLevel&& _Other) noexcept = delete;
	TownLevel& operator=(const TownLevel& _Other) = delete;
	TownLevel& operator=(TownLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _NextLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

private:
	void LoadMapObject();


	BackGround* BackGround_;
	BackGround* BackGroundFront_;

	std::map<int, Items*> MapObject_;
	std::map<int, Items*>::iterator Iter;
};

