#include "StardewValley.h"

#include "MyFarmLevel.h"
#include "TitleLevel.h"
#include "MyHouseLevel.h"
#include "BusStopLevel.h"
#include "TownLevel.h"
#include "SeedShopLevel.h"
#include "SaloonLevel.h"
#include "BackForestLevel.h"
#include "MineLevel.h"
#include "MinePoint.h"
#include "Mine1.h"
#include "Mine2.h"
#include "Mine3.h"
#include "Mine4.h"

#include "CustomData.h"

#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineSound.h>

#include <vector>


StardewValley::StardewValley()
{
}

StardewValley::~StardewValley()
{
}

void StardewValley::GameInit()
{


	//------< 윈도우 초기화 >------------------------------------------------------------------

	GameEngineWindow::GetInst().SetWindowScaleAndPosition({ 100, 100 }, { 1280, 720 });

	//------< 키입력 초기화 >------------------------------------------------------------------

	if (false == GameEngineInput::GetInst()->IsKey("MoveUp"))
	{
		GameEngineInput::GetInst()->CreateKey("MoveLeft", 'A');
		GameEngineInput::GetInst()->CreateKey("MoveRight", 'D');
		GameEngineInput::GetInst()->CreateKey("MoveUp", 'W');
		GameEngineInput::GetInst()->CreateKey("MoveDown", 'S');

		GameEngineInput::GetInst()->CreateKey("Enter", VK_RETURN);
		GameEngineInput::GetInst()->CreateKey("OpenMenu", 'E');

		GameEngineInput::GetInst()->CreateKey("LeftClick", MK_LBUTTON);
		GameEngineInput::GetInst()->CreateKey("RightClick", MK_RBUTTON);

		GameEngineInput::GetInst()->CreateKey("DebugRendereChange", 'R');
		GameEngineInput::GetInst()->CreateKey("TimeAdd", 'T');

		GameEngineInput::GetInst()->CreateKey("MoveShopLevel", '1');
		GameEngineInput::GetInst()->CreateKey("MoveTown", '2');

		GameEngineInput::GetInst()->CreateKey("KeyLeft", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("KeyRight", VK_RIGHT);
		GameEngineInput::GetInst()->CreateKey("KeyUp", VK_UP);
		GameEngineInput::GetInst()->CreateKey("KeyDown", VK_DOWN);

	}

	//----------------------------------------------------------------------------------------------
	//------< 사운드 현재 디렉토리 >------------------------------------------------------------------
	//----------------------------------------------------------------------------------------------

	{


		GameEngineDirectory ResourcesDir;
		ResourcesDir.MoveParent("API");
		ResourcesDir.Move("Resources");
		ResourcesDir.Move("Sound");


		//------< 사운드 파일 찾기 >------------------------------------------------------------------
		
		std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile();

		for (size_t i = 0; i < AllImageFileList.size(); i++)
		{
			GameEngineSound::LoadRes(AllImageFileList[i].GetFullPath());
		}

	}


	//----------------------------------------------------------------------------------------------
	//------< Player >------------------------------------------------------------------------------
	//----------------------------------------------------------------------------------------------

	{

		GameEngineDirectory ResourcesDir;
		ResourcesDir.MoveParent("API");
		ResourcesDir.Move("Resources");
		ResourcesDir.Move("Sprite");
		ResourcesDir.Move("Player");


		//------< 이미지 파일 찾기 >------------------------------------------------------------------

		std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("Bmp");

		for (size_t i = 0; i < AllImageFileList.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
		}

		//------< 이미지 Cut >------------------------------------------------------------------

		//================================
		//     플레이어 바디
		//================================
		GameEngineImage* PlayerBody0 = GameEngineImageManager::GetInst()->Find("PlayerBody0.bmp");
		PlayerBody0->Cut({ 48, 96 });

		//================================
		//     플레이어 헤어
		//================================
		GameEngineImage* PlayerHair0 = GameEngineImageManager::GetInst()->Find("PlayerHair0.bmp");
		PlayerHair0->Cut({ 48, 96 });

		GameEngineImage* PlayerHair1 = GameEngineImageManager::GetInst()->Find("PlayerHair1.bmp");
		PlayerHair1->Cut({ 70, 96 });

		GameEngineImage* PlayerHair2 = GameEngineImageManager::GetInst()->Find("PlayerHair2.bmp");
		PlayerHair2->Cut({ 70, 96 });

		//================================
		//     플레이어 손
		//================================
		GameEngineImage* PlayerHand0 = GameEngineImageManager::GetInst()->Find(CustomData::GetInst()->GetHandFileName());
		PlayerHand0->Cut({ 48, 96 });

		GameEngineImage* PlayerHand1 = GameEngineImageManager::GetInst()->Find("PlayerHand1.bmp");
		PlayerHand1->Cut({ 48, 96 });

		GameEngineImage* PlayerHand2 = GameEngineImageManager::GetInst()->Find("PlayerHand2.bmp");
		PlayerHand2->Cut({ 48, 96 });

		GameEngineImage* PlayerHand3 = GameEngineImageManager::GetInst()->Find("PlayerHand3.bmp");
		PlayerHand3->Cut({ 48, 96 });

		GameEngineImage* PlayerHand4 = GameEngineImageManager::GetInst()->Find("PlayerHand4.bmp");
		PlayerHand4->Cut({ 48, 96 });

		//================================
		//     플레이어 바지
		//================================	
		GameEngineImage* PlayerPants0 = GameEngineImageManager::GetInst()->Find(CustomData::GetInst()->GetPantsFileName());
		PlayerPants0->Cut({ 48, 96 });

		GameEngineImage* PlayerPants1 = GameEngineImageManager::GetInst()->Find("PlayerPants1.bmp");
		PlayerPants1->Cut({ 48, 96 });


		//================================
		//     플레이어 셔츠
		//================================
		GameEngineImage* PlayerShirt0 = GameEngineImageManager::GetInst()->Find(CustomData::GetInst()->GetShirtsFileName());
		PlayerShirt0->Cut({ 48, 96 });

		GameEngineImage* PlayerShirt1 = GameEngineImageManager::GetInst()->Find("PlayerShirt1.bmp");
		PlayerShirt1->Cut({ 48, 96 });

		GameEngineImage* PlayerShirt2 = GameEngineImageManager::GetInst()->Find("PlayerShirt2.bmp");
		PlayerShirt2->Cut({ 48, 96 });

		GameEngineImage* PlayerShirt3 = GameEngineImageManager::GetInst()->Find("PlayerShirt3.bmp");
		PlayerShirt3->Cut({ 48, 96 });

		GameEngineImage* PlayerShirt4 = GameEngineImageManager::GetInst()->Find("PlayerShirt4.bmp");
		PlayerShirt4->Cut({ 48, 96 });



		//================================
		//     플레이어 호미 250	150
		//================================
		GameEngineImage* PlayerHoeRight = GameEngineImageManager::GetInst()->Find("hoe_right.bmp");
		PlayerHoeRight->Cut({ 250, 150 });

		GameEngineImage* PlayerHoeLeft = GameEngineImageManager::GetInst()->Find("hoe_left.bmp");
		PlayerHoeLeft->Cut({ 250, 150 });


		GameEngineImage* PlayerHoeFront = GameEngineImageManager::GetInst()->Find("hoe_front.bmp");
		PlayerHoeFront->Cut({ 250, 150 });

		GameEngineImage* PlayerHoeBack = GameEngineImageManager::GetInst()->Find("hoe_back.bmp");
		PlayerHoeBack->Cut({ 250, 150 });


		//================================
		//     플레이어 도끼 250	150
		//================================
		GameEngineImage* PlayerAxeRight = GameEngineImageManager::GetInst()->Find("axe_right.bmp");
		PlayerAxeRight->Cut({ 250, 150 });

		GameEngineImage* PlayerAxeLeft = GameEngineImageManager::GetInst()->Find("axe_left.bmp");
		PlayerAxeLeft->Cut({ 250, 150 });

		GameEngineImage* PlayerAxeFront = GameEngineImageManager::GetInst()->Find("axe_front.bmp");
		PlayerAxeFront->Cut({ 250, 150 });

		GameEngineImage* PlayerAxeBack = GameEngineImageManager::GetInst()->Find("axe_back.bmp");
		PlayerAxeBack->Cut({ 250, 150 });



		//================================
		//     플레이어 곡괭이 250	150
		//================================
		GameEngineImage* PlayerPiRight = GameEngineImageManager::GetInst()->Find("pickaxe_right.bmp");
		PlayerPiRight->Cut({ 250, 150 });

		GameEngineImage* PlayerPiLeft = GameEngineImageManager::GetInst()->Find("pickaxe_left.bmp");
		PlayerPiLeft->Cut({ 250, 150 });

		GameEngineImage* PlayerPiFront = GameEngineImageManager::GetInst()->Find("pickaxe_front.bmp");
		PlayerPiFront->Cut({ 250, 150 });

		GameEngineImage* PlayerPiBack = GameEngineImageManager::GetInst()->Find("pickaxe_back.bmp");
		PlayerPiBack->Cut({ 250, 150 });


		//================================
		//     플레이어 물 250	150
		//================================
		GameEngineImage* PlayeWaterRight = GameEngineImageManager::GetInst()->Find("wateringcan_right.bmp");
		PlayeWaterRight->Cut({ 250, 150 });

		GameEngineImage* PlayerWaterLeft = GameEngineImageManager::GetInst()->Find("wateringcan_left.bmp");
		PlayerWaterLeft->Cut({ 250, 150 });

		GameEngineImage* PlayerWaterFront = GameEngineImageManager::GetInst()->Find("wateringcan_front.bmp");
		PlayerWaterFront->Cut({ 250, 150 });

		GameEngineImage* PlayerWaterBack = GameEngineImageManager::GetInst()->Find("wateringcan_back.bmp");
		PlayerWaterBack->Cut({ 250, 150 });


		//================================
		//     플레이어 칼 250	150
		//================================
		GameEngineImage* Swoard_right = GameEngineImageManager::GetInst()->Find("Swoard_right.bmp");
		Swoard_right->Cut({ 250, 150 });

		GameEngineImage* Swoard_Left = GameEngineImageManager::GetInst()->Find("Swoard_Left.bmp");
		Swoard_Left->Cut({ 250, 150 });

		GameEngineImage* Swoard_front = GameEngineImageManager::GetInst()->Find("Swoard_front.bmp");
		Swoard_front->Cut({ 250, 150 });

		GameEngineImage* Swoard_back = GameEngineImageManager::GetInst()->Find("Swoard_back.bmp");
		Swoard_back->Cut({ 250, 150 });

		//================================
		//     플레이어 툴 48 96
		//================================
		GameEngineImage* PlayerTool = GameEngineImageManager::GetInst()->Find("tools.bmp");
		PlayerTool->Cut({ 48, 96 });

		//================================
		//    칼 56 56
		//================================
		GameEngineImage* weapons = GameEngineImageManager::GetInst()->Find("weapons.bmp");
		weapons->Cut({ 48, 48 });

		//------< 커스텀용 >------------------------------------------------------------------

		GameEngineImage * BodySheet = GameEngineImageManager::GetInst()->Find("BodySheet.bmp");
		BodySheet->Cut({ 48, 96 });

		GameEngineImage* PantsSheet = GameEngineImageManager::GetInst()->Find("PantsSheet.bmp");
		PantsSheet->Cut({ 48, 96 });

		GameEngineImage* HandSheet = GameEngineImageManager::GetInst()->Find("HandSheet.bmp");
		HandSheet->Cut({ 48, 96 });

		GameEngineImage* hairSheet = GameEngineImageManager::GetInst()->Find("hairSheet.bmp");
		hairSheet->Cut({ 48, 96 });

		GameEngineImage* ShirtsSheet = GameEngineImageManager::GetInst()->Find("ShirtsSheet.bmp");
		ShirtsSheet->Cut({ 48, 96 });


		//------< 무기 >------------------------------------------------------------------



	}


	//----------------------------------------------------------------------------------------------
	//------< Title >-------------------------------------------------------------------------------
	//----------------------------------------------------------------------------------------------
	
	{

		GameEngineDirectory ResourcesDir;
		ResourcesDir.MoveParent("API");
		ResourcesDir.Move("Resources");
		ResourcesDir.Move("Sprite");
		ResourcesDir.Move("Title");


		//------< 이미지 파일 찾기 >------------------------------------------------------------------

		std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("Bmp");

		for (size_t i = 0; i < AllImageFileList.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
		}

		//------< 이미지 Cut >------------------------------------------------------------------


		//================================
		//     타이틀 메뉴 148 116
		//================================
		GameEngineImage* TitleMenuButtons = GameEngineImageManager::GetInst()->Find("TitleMenuButtons.bmp");
		TitleMenuButtons->Cut({ 222, 174 });


		//================================
		//     로고
		//================================
		GameEngineImage* logo_Sheet = GameEngineImageManager::GetInst()->Find("logo_Sheet.bmp");
		logo_Sheet->Cut({ 800, 369 });

		//================================
		//    타이틀 새
		//================================
		GameEngineImage* TitleBird = GameEngineImageManager::GetInst()->Find("TitleBird.bmp");
		TitleBird->Cut({ 78, 78 });


	}

	//----------------------------------------------------------------------------------------------
	//------< UI >----------------------------------------------------------------------------------
	//----------------------------------------------------------------------------------------------


	{


		GameEngineDirectory ResourcesDir;
		ResourcesDir.MoveParent("API");
		ResourcesDir.Move("Resources");
		ResourcesDir.Move("Sprite");
		ResourcesDir.Move("UI");


		//------< 이미지 파일 찾기 >------------------------------------------------------------------

		std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("Bmp");

		for (size_t i = 0; i < AllImageFileList.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
		}

		//------< 이미지 Cut >------------------------------------------------------------------

		//================================
		//		숫자 폰트 블랙
		//================================
		GameEngineImage* Font = GameEngineImageManager::GetInst()->Find("font_colored.bmp");
		Font->Cut({ 12, 21 });

		//================================
		//		숫자 폰트 화이트
		//================================
		GameEngineImage* WhiteFont = GameEngineImageManager::GetInst()->Find("font_colored_White.bmp");
		WhiteFont->Cut({ 15, 21 });

		//================================
		//		영문 폰트
		//================================
		GameEngineImage* EnFont = GameEngineImageManager::GetInst()->Find("Font.bmp");
		EnFont->Cut({ 48, 46 });
		
		//================================
		//		영문 폰트2
		//================================
		GameEngineImage* font_ver2 = GameEngineImageManager::GetInst()->Find("font_ver2.bmp");
		font_ver2->Cut({ 20, 40 });

		//================================
		//		요일
		//================================
		GameEngineImage* Week_Sheet = GameEngineImageManager::GetInst()->Find("Week_Sheet.bmp");
		Week_Sheet->Cut({ 42, 26 });

		//================================
		//		꽃
		//================================
		GameEngineImage* Flower = GameEngineImageManager::GetInst()->Find("Flower.bmp");
		Flower->Cut({ 48, 55 });

		//================================
		//		꽃
		//================================
		GameEngineImage* FlowerAnimation1 = GameEngineImageManager::GetInst()->Find("FlowerAnimation1.bmp");
		FlowerAnimation1->Cut({ 48, 55 });

		//================================
		//		뒤로가기 버튼
		//================================
		GameEngineImage* Back = GameEngineImageManager::GetInst()->Find("Back.bmp");
		Back->Cut({ 132, 54 });
	}


	//----------------------------------------------------------------------------------------------
	//------< Furniture >---------------------------------------------------------------------------
	//----------------------------------------------------------------------------------------------

	{


		GameEngineDirectory ResourcesDir;
		ResourcesDir.MoveParent("API");
		ResourcesDir.Move("Resources");
		ResourcesDir.Move("Sprite");
		ResourcesDir.Move("Furniture");


		//------< 이미지 파일 찾기 >------------------------------------------------------------------

		std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("Bmp");

		for (size_t i = 0; i < AllImageFileList.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
		}

		//------< 이미지 Cut >------------------------------------------------------------------

	}



	//----------------------------------------------------------------------------------------------
	//------< Object >------------------------------------------------------------------------------
	//----------------------------------------------------------------------------------------------

	{

		GameEngineDirectory ResourcesDir;
		ResourcesDir.MoveParent("API");
		ResourcesDir.Move("Resources");
		ResourcesDir.Move("Sprite");
		ResourcesDir.Move("Obejct");

		//------< 이미지 파일 찾기 >------------------------------------------------------------------

		std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("Bmp");

		for (size_t i = 0; i < AllImageFileList.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
		}

		//------< 이미지 Cut >------------------------------------------------------------------



		//================================
		//     봄 아이템 48 48
		//================================
		GameEngineImage* SpringObjects = GameEngineImageManager::GetInst()->Find("springobjects.bmp");
		SpringObjects->Cut({ 48, 48 });


		//================================
		//    땅
		//================================
		GameEngineImage* HoeDirt = GameEngineImageManager::GetInst()->Find("hoeDirt.bmp");
		HoeDirt->Cut({ 48, 48 });


		//================================
		//    씨앗
		//================================
		GameEngineImage* crops = GameEngineImageManager::GetInst()->Find("crops.bmp");
		crops->Cut({ 48, 96 });


		//================================
		//		OakTree
		//================================
		GameEngineImage* OakTree = GameEngineImageManager::GetInst()->Find("Oak_Tree_AnimaionSheet.bmp");
		OakTree->Cut({ 152, 240 });

		//================================
		//		MapleTree
		//================================
		GameEngineImage* MapleTree = GameEngineImageManager::GetInst()->Find("Maple_Tree_AnimationSheet.bmp");
		MapleTree->Cut({ 152, 228 });

		//================================
		//		MahoganyTree
		//================================
		GameEngineImage* MahoganyTree = GameEngineImageManager::GetInst()->Find("Mahogany_Tree_AnimaionSheet.bmp");
		MahoganyTree->Cut({ 152, 238 });

		//================================
		//		FineTree
		//================================
		GameEngineImage* FineTree = GameEngineImageManager::GetInst()->Find("Fine_Tree_AnimaionSheet.bmp");
		FineTree->Cut({ 152, 246 });

		//================================
		//		Giftbox
		//================================
		GameEngineImage* Giftbox = GameEngineImageManager::GetInst()->Find("Giftbox.bmp");
		Giftbox->Cut({ 48, 96 });

		//================================
		//		Box
		//================================
		GameEngineImage* BoxOpen = GameEngineImageManager::GetInst()->Find("BoxOpen.bmp");
		BoxOpen->Cut({ 90, 75 });

		GameEngineImage* BoxClose = GameEngineImageManager::GetInst()->Find("BoxClose.bmp");
		BoxClose->Cut({ 90, 75 });

	}


	//----------------------------------------------------------------------------------------------
	//------< NPC >--------------------------------------------------------------------------------
	//----------------------------------------------------------------------------------------------

	{

		//------< 이미지 현재 디렉토리 >------------------------------------------------------------------

		GameEngineDirectory ResourcesDir;
		ResourcesDir.MoveParent("API");
		ResourcesDir.Move("Resources");
		ResourcesDir.Move("Sprite");
		ResourcesDir.Move("NPC");


		//------< 이미지 파일 찾기 >------------------------------------------------------------------

		std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("Bmp");

		for (size_t i = 0; i < AllImageFileList.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
		}

		//------< 이미지 Cut >------------------------------------------------------------------

		GameEngineImage* characterMoveSheet = GameEngineImageManager::GetInst()->Find("characterMoveSheet.bmp");
		characterMoveSheet->Cut({ 48, 48 });

		GameEngineImage* Pierre = GameEngineImageManager::GetInst()->Find("Pierre.bmp");
		Pierre->Cut({ 48, 96 });

		GameEngineImage* Pierre_Portrait = GameEngineImageManager::GetInst()->Find("Pierre_Portrait.bmp");
		Pierre_Portrait->Cut({ 192, 192 });

		GameEngineImage* Lewis = GameEngineImageManager::GetInst()->Find("Lewis.bmp");
		Lewis->Cut({ 48, 96 });

		GameEngineImage* Lewis_Portrait = GameEngineImageManager::GetInst()->Find("Lewis_Portrait.bmp");
		Lewis_Portrait->Cut({ 192, 192 });

		GameEngineImage* Name_Sheet = GameEngineImageManager::GetInst()->Find("Name_Sheet.bmp");
		Name_Sheet->Cut({ 170, 50 });

		GameEngineImage* Penny = GameEngineImageManager::GetInst()->Find("Penny.bmp");
		Penny->Cut({ 48, 96 });

		GameEngineImage* Penny__Portrait = GameEngineImageManager::GetInst()->Find("Penny__Portrait.bmp");
		Penny__Portrait->Cut({ 192, 192 });


		GameEngineImage* Gus = GameEngineImageManager::GetInst()->Find("Gus.bmp");
		Gus->Cut({ 48, 96 });

		GameEngineImage* Gus_Portrait = GameEngineImageManager::GetInst()->Find("Gus_Portrait.bmp");
		Gus_Portrait->Cut({ 192, 192 });

	}


	//----------------------------------------------------------------------------------------------
	//------< Shop >--------------------------------------------------------------------------------
	//----------------------------------------------------------------------------------------------
	{


		GameEngineDirectory ResourcesDir;
		ResourcesDir.MoveParent("API");
		ResourcesDir.Move("Resources");
		ResourcesDir.Move("Sprite");
		ResourcesDir.Move("Shop");

		//------< 이미지 파일 찾기 >------------------------------------------------------------------

		std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("Bmp");

		for (size_t i = 0; i < AllImageFileList.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
		}

		//------< 이미지 Cut >------------------------------------------------------------------

	}


	//----------------------------------------------------------------------------------------------
	//------< Map >--------------------------------------------------------------------------------
	//----------------------------------------------------------------------------------------------

	{


		GameEngineDirectory ResourcesDir;
		ResourcesDir.MoveParent("API");
		ResourcesDir.Move("Resources");
		ResourcesDir.Move("Sprite");
		ResourcesDir.Move("Map");

		//------< 이미지 파일 찾기 >------------------------------------------------------------------

		std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("Bmp");

		for (size_t i = 0; i < AllImageFileList.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
		}

		//------< 이미지 Cut >------------------------------------------------------------------



	}
	

	//----------------------------------------------------------------------------------------------
	//------< Effect >-----------------------------------------------------------------------------
	//----------------------------------------------------------------------------------------------

	{


		GameEngineDirectory ResourcesDir;
		ResourcesDir.MoveParent("API");
		ResourcesDir.Move("Resources");
		ResourcesDir.Move("Sprite");
		ResourcesDir.Move("GameAnimation");

		//------< 이미지 파일 찾기 >------------------------------------------------------------------

		std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("Bmp");

		for (size_t i = 0; i < AllImageFileList.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
		}

		//------< 이미지 Cut >------------------------------------------------------------------

		//================================
		//		KiraAnimation
		//================================
		GameEngineImage* KiraAnimation = GameEngineImageManager::GetInst()->Find("KiraAnimation.bmp");
		KiraAnimation->Cut({ 48, 48 });

		//================================
		//		WaterAni
		//================================
		GameEngineImage* WateringCanAnimations = GameEngineImageManager::GetInst()->Find("WateringCanAnimations.bmp");
		WateringCanAnimations->Cut({ 48, 48 });


		//================================
		//		DirtAnimations
		//================================
		GameEngineImage* DirtAnimations = GameEngineImageManager::GetInst()->Find("DirtAnimations.bmp");
		DirtAnimations->Cut({ 48, 48 });

		//================================
		//		StoneAnimationsSheet
		//================================
		GameEngineImage* StoneAnimationsSheet = GameEngineImageManager::GetInst()->Find("StoneAnimationsSheet.bmp");
		StoneAnimationsSheet->Cut({ 48, 48 });

		//================================
		//		WoodAnimationsSheet
		//================================
		GameEngineImage* WoodAnimationsSheet = GameEngineImageManager::GetInst()->Find("WoodAnimationsSheet.bmp");
		WoodAnimationsSheet->Cut({ 48, 48 });


	}


	//----------------------------------------------------------------------------------------------
	//------< Monster >-----------------------------------------------------------------------------
	//----------------------------------------------------------------------------------------------

	{
		GameEngineDirectory ResourcesDir;
		ResourcesDir.MoveParent("API");
		ResourcesDir.Move("Resources");
		ResourcesDir.Move("Sprite");
		ResourcesDir.Move("Monster");


		//------< 이미지 파일 찾기 >------------------------------------------------------------------

		std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("Bmp");

		for (size_t i = 0; i < AllImageFileList.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
		}

		//------< 이미지 Cut >------------------------------------------------------------------

		//================================
		//		WoodAnimationsSheet
		//================================
		GameEngineImage* StoneGolem = GameEngineImageManager::GetInst()->Find("StoneGolem.bmp");
		StoneGolem->Cut({ 48, 72 });


		//================================
		//		WoodAnimationsSheet
		//================================
		GameEngineImage* ArmoredBug = GameEngineImageManager::GetInst()->Find("ArmoredBug.bmp");
		ArmoredBug->Cut({ 48, 60 });

	}





	//----------------------------------------------------------------------------------------------
	//------< Sprite >-----------------------------------------------------------------------------
	//----------------------------------------------------------------------------------------------

	{
		GameEngineDirectory ResourcesDir;
		ResourcesDir.MoveParent("API");
		ResourcesDir.Move("Resources");
		ResourcesDir.Move("Sprite");

		//------< 이미지 파일 찾기 >------------------------------------------------------------------

		std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("Bmp");

		for (size_t i = 0; i < AllImageFileList.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
		}

		//------< 이미지 Cut >------------------------------------------------------------------

	}




	//------< 레벨 등록 >------------------------------------------------------------------

	CreateLevel<TitleLevel>("TitleLevel");
	CreateLevel<MyHouseLevel>("MyHouseLevel");
	CreateLevel<MyFarmLevel>("MyFarmLevel");
	CreateLevel<BusStopLevel>("BusStopLevel");
	CreateLevel<TownLevel>("TownLevel");
	CreateLevel<SaloonLevel>("SaloonLevel");

	CreateLevel<SeedShopLevel>("SeedShopLevel");
	CreateLevel<BackForestLevel>("BackForestLevel");
	CreateLevel<MineLevel>("MineLevel");
	CreateLevel<MinePoint>("MinePoint");
	CreateLevel<Mine1>("Mine1");
	CreateLevel<Mine2>("Mine2");
	CreateLevel<Mine3>("Mine3");
	CreateLevel<Mine4>("Mine4");



	ChangeLevel("TitleLevel");


}

void StardewValley::GameLoop()
{
}
void StardewValley::GameEnd()
{
	CustomData::Destroy();
}
