#pragma once
#include "Items.h"
// Ό³Έν :
class EmptyItem : public Items
{
public:
	// constrcuter destructer
	EmptyItem();
	~EmptyItem();

	// delete Function
	EmptyItem(const EmptyItem& _Other) = delete;
	EmptyItem(EmptyItem&& _Other) noexcept = delete;
	EmptyItem& operator=(const EmptyItem& _Other) = delete;
	EmptyItem& operator=(EmptyItem&& _Other) noexcept = delete;


private:
	void Start() override;

};

