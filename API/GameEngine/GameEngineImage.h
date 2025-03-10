#pragma once
#include <GameEngineBase/GameEngineNameObject.h>
#include <GameEngineBase/GameEngineMath.h>
#include <Windows.h>
#include <vector>

// ���� :
class GameEngineImage : public GameEngineNameObject
{
public:
	// constrcuter destructer
	GameEngineImage();
	~GameEngineImage();

	// delete Function
	GameEngineImage(const GameEngineImage& _Other) = delete;
	GameEngineImage(GameEngineImage&& _Other) noexcept = delete;
	GameEngineImage& operator=(const GameEngineImage& _Other) = delete;
	GameEngineImage& operator=(GameEngineImage&& _Other) noexcept = delete;

	bool Create(float4 _Scale);
	bool Create(HDC _DC);

	bool Load(const std::string& _Path);

	inline float4 GetScale()
	{
		return float4(static_cast<float>(Info_.bmWidth), static_cast<float>(Info_.bmHeight));
	}

	inline HDC ImageDC()
	{
		return ImageDC_;
	}

	// BitBlt
	void BitCopy(GameEngineImage* _Other);
	void BitCopy(GameEngineImage* _Other, const float4& _CopyPos);
	void BitCopyCenter(GameEngineImage* _Other, const float4& _CopyPos);
	void BitCopyCenterPivot(GameEngineImage* _Other, const float4& _CopyPos, const float4& _CopyPivot);
	void BitCopyBot(GameEngineImage* _Other, const float4& _CopyPos);
	void BitCopyBotPivot(GameEngineImage* _Other, const float4& _CopyPos, const float4& _CopyPivot);
	void BitCopy(GameEngineImage* _Other, const float4& _CopyPos,
		const float4& _CopyScale,
		const float4& _OtherPivot);

	// Trans
	void TransCopy(GameEngineImage* _Other, const float4& _CopyPos,
		const float4& _CopyScale,
		const float4& _OtherPivot, const float4& _OtherScale, unsigned int _TransColor);


	void AlphaCopy(GameEngineImage* _Other, const float4& _CopyPos,
		const float4& _CopyScale,
		const float4& _OtherPivot, const float4& _OtherScale, unsigned int _TransColor);


	void PlgCopy(GameEngineImage* _Other, const float4& _CopyPos,
		const float4& _CopyScale,
		const float4& _OtherPivot, const float4& _OtherScale, float _Angle, GameEngineImage* _Filter);


	void Cut(const float4& _CutSize);

	void CutCount(int _x, int _y);

	bool IsCut()
	{
		return 0 != CutPivot_.size();
	}

	float4 GetCutPivot(size_t _Index)
	{
		return CutPivot_[_Index];
	}

	float4 GetCutScale(size_t _Index)
	{
		return CutScale_[_Index];
	}

	void Cut(const float4& _CutScale, const float4& _CutPos)
	{
		CutScale_.push_back(_CutScale);
		CutPivot_.push_back(_CutPos);
	}


	inline int GetImagePixel(const float4& _Pos)
	{
		return GetImagePixel(_Pos.ix(), _Pos.iy());
	}

	int GetImagePixel(int _x, int _y);

protected:


private:
	HDC ImageDC_;
	HBITMAP BitMap_;
	HBITMAP OldBitMap_;
	BITMAP Info_;

	std::vector<float4> CutPivot_;
	std::vector<float4> CutScale_;


	void ImageScaleCheck();
};

