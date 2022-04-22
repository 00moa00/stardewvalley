#pragma once
#include "GameEngineContents//Items.h"

// Ό³Έν :
class Bean
{
public:
	// constrcuter destructer
	Bean();
	~Bean();

	// delete Function
	Bean(const Bean& _Other) = delete;
	Bean(Bean&& _Other) noexcept = delete;
	Bean& operator=(const Bean& _Other) = delete;
	Bean& operator=(Bean&& _Other) noexcept = delete;

protected:

private:

};

