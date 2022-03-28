#pragma once
#include <GameEngine/GameEngineActor.h>

// 데이터만 따로 싱글톤 사용하기? 레벨이 다른 곳에서 사용.?

class PlayerCustomBoard : public GameEngineActor
{
public:
	// constrcuter destructer
	PlayerCustomBoard();
	~PlayerCustomBoard();

	// delete Function
	PlayerCustomBoard(const PlayerCustomBoard& _Other) = delete;
	PlayerCustomBoard(PlayerCustomBoard&& _Other) noexcept = delete;
	PlayerCustomBoard& operator=(const PlayerCustomBoard& _Other) = delete;
	PlayerCustomBoard& operator=(PlayerCustomBoard&& _Other) noexcept = delete;

protected:

private:
	GameEngineRenderer* PlayerCustomBoard_;

	void Start() override;
	void Update() override;
	void Render() override;
};


