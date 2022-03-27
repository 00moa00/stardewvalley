#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class TitleCloud : public GameEngineActor
{
public:
	// constrcuter destructer
	TitleCloud();
	~TitleCloud();

	// delete Function
	TitleCloud(const TitleCloud& _Other) = delete;
	TitleCloud(TitleCloud&& _Other) noexcept = delete;
	TitleCloud& operator=(const TitleCloud& _Other) = delete;
	TitleCloud& operator=(TitleCloud&& _Other) noexcept = delete;

protected:
	void Start() override;

	void Render() override;
	void Update() override;


private:


};

