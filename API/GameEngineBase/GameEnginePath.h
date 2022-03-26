#pragma once
#include <filesystem>

// TODO : filesystem
//Fstram : 파일의 데이터를 읽어내지만 그 외에 파일에 관한 정보 (파일 이름, 위치 등)에 관한
//데이터를 수정할 수 없다.

//fileSysytem : 파일에 관한 정보에 대한 접근을 도와주나, 파일 자체를 읽는 일은 수행하지 않는다.

// 하드 디스크 어딘가에 있는 파일을 찾고싶다면 filesystem , 읽고싶다면 fstream 사용


class GameEnginePath
{
public:
	// constrcuter destructer
	GameEnginePath();
	GameEnginePath(const std::filesystem::path& _Path);
	~GameEnginePath();

	// delete Function
	GameEnginePath(const GameEnginePath& _Other) = delete;
	GameEnginePath(GameEnginePath&& _Other) noexcept = delete;
	GameEnginePath& operator=(const GameEnginePath& _Other) = delete;
	GameEnginePath& operator=(GameEnginePath&& _Other) noexcept = delete;

	void SetCurrentPath();

	bool IsExits();

	std::string GetExtension();

	std::string GetFileName();

	std::string GetFullPath();

protected:
	std::filesystem::path Path_;

private:
};

