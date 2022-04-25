#pragma once
#include "Items.h"
// Ό³Έν :

enum class TREETOP
{
	INIT,
	CRUSH
};


class TreeTop : public Items
{
public:
	static TreeTop* MainTreeTop;

	// constrcuter destructer
	TreeTop();
	~TreeTop();

	// delete Function
	TreeTop(const TreeTop& _Other) = delete;
	TreeTop(TreeTop&& _Other) noexcept = delete;
	TreeTop& operator=(const TreeTop& _Other) = delete;
	TreeTop& operator=(TreeTop&& _Other) noexcept = delete;

private:

	void Start() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	
public:
	void SetInitAnimation() override;
	void SetCrushAnimation() override;

private:
	TREETOP TreeTopState_;

public:


};



