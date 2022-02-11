#include "WinMain.h"
#include "Scene.h"
#include "Scenetitle.h"

//각 씬의 클래스 선언
SceneTitle sceneTitle;

//클래스 구조체
Scene* scene_tbl[] = {
	&sceneTitle,
};

Scene* pScene;
Scene* pNext;

//메인 함수

int main() {
	
	setScene(SCENE_TITLE);

	//게임 루프
	while (true) {

		//씬 변경 처리
		pScene = pNext;
		pNext = nullptr;
		pScene->init();
	}

	pScene->update();
	pScene->render();
}

void setScene(int _scene) {

	pNext = scene_tbl[_scene];

}