#pragma once
#include "Items.h"

// Ό³Έν :

class BadTop : public Items
{
public:
	// constrcuter destructer
	BadTop();
	~BadTop();

	// delete Function
	BadTop(const BadTop& _Other) = delete;
	BadTop(BadTop&& _Other) noexcept = delete;
	BadTop& operator=(const BadTop& _Other) = delete;
	BadTop& operator=(BadTop&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};


