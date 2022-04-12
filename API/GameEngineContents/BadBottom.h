#pragma once
#include "Items.h"

// Ό³Έν :
class BadBottom : public Items
{
public:
	// constrcuter destructer
	BadBottom();
	~BadBottom();

	// delete Function
	BadBottom(const BadBottom& _Other) = delete;
	BadBottom(BadBottom&& _Other) noexcept = delete;
	BadBottom& operator=(const BadBottom& _Other) = delete;
	BadBottom& operator=(BadBottom&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

