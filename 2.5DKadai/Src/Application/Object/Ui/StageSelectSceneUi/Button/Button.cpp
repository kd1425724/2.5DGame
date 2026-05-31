#include"Button.h"
#include"../../../../Common/Input/Input.h"
#include"../../../../Common/CommonAPI.h"
#include"../../../../Common/CommonAsset/CommonAsset.h"
#include"../../../../Scene/SceneManager.h"

void StageSelectButton::Release()
{
	m_buttontex->reset();
	m_buttonframetex->reset();
}

void StageSelectButton::Init()
{
	FILE* fp;

	if (fopen_s(&fp, "Asset/Data/ObjectData/ButtonData/StageSelectButtonData.csv", "r") == 0)
	{
		char dummy[255];

		//画像座標
		Math::Vector2 pos[(int)StageSelectButtonInfo::ButtonNum] = {};

		//画像
		int id = {};
		
		fgets(dummy, 255, fp);				//1行飛ばす

		for (int i = 0; i < (int)StageSelectButtonInfo::ButtonNum; i++)
		{
			fscanf_s(fp, "%*[^,],%d,%f,%f", &id, &pos[i].x, &pos[i].y);

			KdSquarePolygon poly;
			KdSquarePolygon fpoly;

			switch (id)
			{
			case 0:
				poly.SetMaterial("Asset/Textures/Common/Feed/WhiteBack.png");
				fpoly.SetMaterial("");
				break;
			case 1:
				break;
			case 2:
				break;
			default:
				break;
			}
			poly.SetMaterial("");

			m_buttontex[i]->SetMaterial(poly.GetMaterial());
			m_buttonframetex[i]->SetMaterial(fpoly.GetMaterial());

			COMMONAPI.CreateButton(pos[i], { 0,0,600,600 }, { 0.3f,0.3f },
				m_buttontex[i], { 1,1,1,1 },
				m_buttonframetex[i]);
		}

		fclose(fp);
	}

	COMMONAPI.SetAction((int)StageSelectButtonInfo::Stage1,[]()
		{
			SceneManager::Instance().SetNextScene(SceneManager::SceneType::Game);
		});
}
void StageSelectButton::Update()
{

	if (Inp.GetUserKey(UserKeyType::Left) && !Inp.GetUserKeyFlg(UserKeyType::Left))
	{
		if (m_button == StageSelectButtonInfo::Stage1)
		{
			m_button = (StageSelectButtonInfo)((int)m_button + 2);
		}
		else
		{
			m_button = (StageSelectButtonInfo)((int)m_button - 1);
		}
	}
	if (Inp.GetUserKey(UserKeyType::Bottom) && !Inp.GetUserKeyFlg(UserKeyType::Right))
	{
		if (m_button == StageSelectButtonInfo::Back)
		{
			m_button = (StageSelectButtonInfo)((int)m_button - 2);
		}
		else
		{
			m_button = (StageSelectButtonInfo)((int)m_button + 1);
		}
	}

	if (Inp.GetUserKey(UserKeyType::ZKey) && Inp.GetUserKeyFlg(UserKeyType::ZKey))
	{
		COMMONAPI.ButtonExecute((int)m_button);
	}
}

void StageSelectButton::DrawSprite()
{
	COMMONAPI.CreateButtonDrawSprite();
	COMMONAPI.IsOnTopButtonDraw((int)m_button);
}

