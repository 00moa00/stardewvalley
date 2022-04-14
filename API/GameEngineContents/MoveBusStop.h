#pragma once
#include "Items.h"
// Ό³Έν :
class MoveBusStop : public Items
{
public:
	// constrcuter destructer
	MoveBusStop();
	~MoveBusStop();

	// delete Function
	MoveBusStop(const MoveBusStop& _Other) = delete;
	MoveBusStop(MoveBusStop&& _Other) noexcept = delete;
	MoveBusStop& operator=(const MoveBusStop& _Other) = delete;
	MoveBusStop& operator=(MoveBusStop&& _Other) noexcept = delete;

protected:

private:
	void Start() override;

};

