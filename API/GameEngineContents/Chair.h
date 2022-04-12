#pragma once
#include "Items.h"

// Ό³Έν :
class Chair : public Items
{
public:
	// constrcuter destructer
	Chair();
	~Chair();

	// delete Function
	Chair(const Chair& _Other) = delete;
	Chair(Chair&& _Other) noexcept = delete;
	Chair& operator=(const Chair& _Other) = delete;
	Chair& operator=(Chair&& _Other) noexcept = delete;

protected:
	void Start() override;
private:

};

