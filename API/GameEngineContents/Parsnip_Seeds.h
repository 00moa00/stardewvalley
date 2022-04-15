#pragma once
#include "Items.h"

// Ό³Έν :
class Parsnip_Seeds : public Items
{
public:
	// constrcuter destructer
	Parsnip_Seeds();
	~Parsnip_Seeds();

	// delete Function
	Parsnip_Seeds(const Parsnip_Seeds& _Other) = delete;
	Parsnip_Seeds(Parsnip_Seeds&& _Other) noexcept = delete;
	Parsnip_Seeds& operator=(const Parsnip_Seeds& _Other) = delete;
	Parsnip_Seeds& operator=(Parsnip_Seeds&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update() override;
};

