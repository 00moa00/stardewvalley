#pragma once
#include <GameEngineBase/GameEngineRandom.h>

#include "Items.h"
#include "TreeTop.h"
// Ό³Έν :
class TreeBottom : public Items
{
public:
	// constrcuter destructer
	TreeBottom();
	~TreeBottom();

	// delete Function
	TreeBottom(const TreeBottom& _Other) = delete;
	TreeBottom(TreeBottom&& _Other) noexcept = delete;
	TreeBottom& operator=(const TreeBottom& _Other) = delete;
	TreeBottom& operator=(TreeBottom&& _Other) noexcept = delete;

private:

	void Start() override;
	void Update() override;


private:
	Items* TreeTop_;


public:
	void TreeOff() override;

};

