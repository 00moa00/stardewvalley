#pragma once
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineActor.h>
// Ό³Έν :
class MapColl : public GameEngineActor
{
public:
	// constrcuter destructer
	MapColl();
	~MapColl();

	// delete Function
	MapColl(const MapColl& _Other) = delete;
	MapColl(MapColl&& _Other) noexcept = delete;
	MapColl& operator=(const MapColl& _Other) = delete;
	MapColl& operator=(MapColl&& _Other) noexcept = delete;

	GameEngineImage* GetImage() {
		return MapColImage_;
	}

	GameEngineImage* MapColImage_;

protected:
	void Start() override;
private:

};

