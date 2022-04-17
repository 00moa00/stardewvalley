#pragma once
#include"PlayLevel.h"

// Ό³Έν :
class ShopLevel : public PlayLevel
{
public:
	// constrcuter destructer
	ShopLevel();
	~ShopLevel();

	// delete Function
	ShopLevel(const ShopLevel& _Other) = delete;
	ShopLevel(ShopLevel&& _Other) noexcept = delete;
	ShopLevel& operator=(const ShopLevel& _Other) = delete;
	ShopLevel& operator=(ShopLevel&& _Other) noexcept = delete;

	void Loading() override;
	void Update() override;
	void LevelChangeStart() override;

protected:



private:
	void LoadMapObject();

	float Time;

	std::map<int, Items*> MapObject_;
	std::map<int, Items*>::iterator Iter;

};

