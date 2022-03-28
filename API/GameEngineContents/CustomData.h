#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineImageManager.h>

// 설명 : 싱글톤

class CustomData 
{
private:
	static CustomData* Inst_;

public:
	inline static CustomData& GetInst()
	{
		return *Inst_;
	}

	static void Destroy()
	{
		if (nullptr != Inst_)
		{
			delete Inst_;
			Inst_ = nullptr;
		}
	}


public:
	// constrcuter destructer
	CustomData();
	~CustomData();

	// delete Function
	CustomData(const CustomData& _Other) = delete;
	CustomData(CustomData&& _Other) noexcept = delete;
	CustomData& operator=(const CustomData& _Other) = delete;
	CustomData& operator=(CustomData&& _Other) noexcept = delete;

	unsigned int HairIndex_;
	unsigned int ShirtsIndex_;
	unsigned int PantsIndex_;
	bool MoveLock_;


	void SetMoveFlag(bool b) {
		MoveLock_ = b;
	}

	bool GetMoveFlag() {
		return MoveLock_;
	}


	inline void SubHairIndex() {
		--HairIndex_;
		//TODO : renderer 포인터 사용해서 최대수로 등록하기
		// 함수없음................................요청?
		if (HairIndex_ <= 0) HairIndex_ = 0;
	}

	inline void SubShirtsIndex() {
		--ShirtsIndex_;
		if (ShirtsIndex_ <= 0) ShirtsIndex_ = 0;
	}

	inline void SubPantsIndex() {
		--PantsIndex_;
		if (PantsIndex_ <= 0) PantsIndex_ = 0;
	}


	inline void AddHairIndex() {
		++HairIndex_;
		//TODO : 최대수 설정하기
	}

	inline void AddShirtsIndex() {
		++ShirtsIndex_;
	}

	inline void AddPantsIndex() {
		++PantsIndex_;
	}


	inline void SetHairIndex(const unsigned int i) {
		HairIndex_ = i;
	}

	inline void SetShirtsIndex(const unsigned int i) {
		ShirtsIndex_ = i;
	}

	inline void SetPantsIndex(const unsigned int i) {
		PantsIndex_ = i;
	}

	inline const unsigned int GetHairIndex() {
		return HairIndex_;
	}

	inline const unsigned int GetShirtsIndex() {
		return ShirtsIndex_;
	}

	inline unsigned int GetPantsIndex() {
		return PantsIndex_;
	}



protected:

private:

};

