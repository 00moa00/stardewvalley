#pragma once
#include "Items.h"

// Ό³Έν :
class Table : public Items
{
public:
	// constrcuter destructer
	Table();
	~Table();

	// delete Function
	Table(const Table& _Other) = delete;
	Table(Table&& _Other) noexcept = delete;
	Table& operator=(const Table& _Other) = delete;
	Table& operator=(Table&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

