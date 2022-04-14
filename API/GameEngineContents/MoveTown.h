#pragma once
#include "Items.h"
// Ό³Έν :
class MoveTown : public Items
{
public:
	// constrcuter destructer
	MoveTown();
	~MoveTown();

	// delete Function
	MoveTown(const MoveTown& _Other) = delete;
	MoveTown(MoveTown&& _Other) noexcept = delete;
	MoveTown& operator=(const MoveTown& _Other) = delete;
	MoveTown& operator=(MoveTown&& _Other) noexcept = delete;

protected:

private:
	void Start() override;

};

