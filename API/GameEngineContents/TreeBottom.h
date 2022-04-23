#pragma once
#include <GameEngineBase/GameEngineRandom.h>

#include "Items.h"
#include "TreeTop.h"

enum class TREESTATE
{
	INIT,
	UPDATE,
	TREETOP_DIE
};

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
	void SetInitAnimation() override;
	void SetCrushAnimation() override;
	void DropItemInMap() override;

private:
	Items* SubRenderer;
	TREESTATE TreeState_;

public:
	void TreeOff() override;

};

