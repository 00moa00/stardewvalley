#include "GameEnginePath.h"

GameEnginePath::GameEnginePath()
{
}

GameEnginePath::GameEnginePath(const std::filesystem::path& _Path)
	: Path_(_Path)
{

}

GameEnginePath::~GameEnginePath()
{
}

void GameEnginePath::SetCurrentPath()
{
	// 현재 폴더.
	Path_ = std::filesystem::current_path();
}

bool GameEnginePath::IsExits()
{

	// 해당 경로에 파일이 존재하는지 확인. 있다면 ture

	return std::filesystem::exists(Path_);
}

std::string GameEnginePath::GetExtension()
{

	//확장자 추출
	return Path_.extension().string();
}

std::string GameEnginePath::GetFileName()
{
	return Path_.filename().string();
}

std::string GameEnginePath::GetFullPath()
{
	return Path_.string();
}