#include "StageSelectScene.h"
#include"../../Object/Ui/StageSelectSceneUi/StageSelectSceneUi.h"

void StageSelectScene::Event()
{
	//カメラ処理
	Math::Vector3 camPos = { 0,0,-50 };
	Math::Matrix transmat = Math::Matrix::CreateTranslation(camPos);
	Math::Matrix mat = transmat;

	m_camera->SetCameraMatrix(mat);
}

void StageSelectScene::Init()
{
	//カメラの初期化
	m_camera = std::make_unique<KdCamera>();

	std::shared_ptr<StageSelectSceneUi> stageselectui = std::make_shared<StageSelectSceneUi>();
	m_objList.push_back(stageselectui);
}
