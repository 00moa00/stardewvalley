#pragma once
#include "Items.h"
// Ό³Έν :
class TreeTop : public Items
{
public:
	// constrcuter destructer
	TreeTop();
	~TreeTop();

	// delete Function
	TreeTop(const TreeTop& _Other) = delete;
	TreeTop(TreeTop&& _Other) noexcept = delete;
	TreeTop& operator=(const TreeTop& _Other) = delete;
	TreeTop& operator=(TreeTop&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;

private:

};

