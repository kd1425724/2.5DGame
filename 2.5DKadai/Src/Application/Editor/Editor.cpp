#include "Editor.h"
#include"../Common/Input/Input.h"

#include "../main.h"
#include "../Scene/SceneManager.h"

#include"../Object/Ground/GameGround/GameGround.h"
#include"../Object/Player/Player.h"

void Editor::Init()
{
	//デバッグ用
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();

	//生成するオブジェクト追加
	m_createObjInfo.push_back({ "Ground",[]()
		{
			std::shared_ptr<GameGround> ground = std::make_shared<GameGround>();
			ground->Init();
			return ground;
		}});
	
	m_createObjInfo.push_back({ "Player", []() 
		{
			std::shared_ptr<Player> player = std::make_shared<Player>();
			player->Init();
			return player;
		}});
}

void Editor::Update()
{
	static bool oldState = false;

	bool nowState = (Inp.GetEditorKeyDown(EditorKeyType::ModeChangeKey));

	if (nowState && !oldState)
	{
		m_editMode = !m_editMode;
	}

	oldState = nowState;

	//マウスドラッグ更新
	MouseDragMoveUpdate();

	//カメラ更新
	CameraUpdate();

	//キーでの操作更新
	KeyUpdate();
}

void Editor::Draw()
{
	if (!m_editMode) return;


	DrawMainWindow();

	if (m_showHierarchy)
	{
		DrawHierarchy();
	}

	if (m_showInspector)
	{
		DrawInspector();
	}
}

void Editor::DebagDraw()
{
	auto obj = m_selectObj.lock();

	if (!obj) return;

	//選択中のオブジェクトの位置にBoxを表示
	m_pDebugWire->AddDebugBox(obj->GetMatrix(), { 1,1,1 }, {}, false, { 1,1,0,1 });

	// 早期リターン
	if (!m_pDebugWire)return;

	m_pDebugWire->Draw();
}

void Editor::LoadRoom(std::string _filename, int _InstanceId)
{
	FILE* fp = nullptr;

	std::string path = "Asset/Data/StageData/RoomData/" + std::string(_filename) + ".csv";

	fopen_s(&fp, path.c_str(), "r");

	if (!fp) return;

	char objName[256] = "";

	float x, y, z;

	while (fscanf_s(fp, "%255[^,],%f,%f,%f\n", objName, (unsigned)_countof(objName), &x, &y, &z) == 4)
	{
		for (auto& createInfo : m_createObjInfo)
		{
			if (createInfo.name == objName)
			{
				auto obj = createInfo.obj();

				obj->SetName(createInfo.name);

				obj->SetPos({ x,y,z });
				//部屋の番号セット
				obj->SetInstanceID(_InstanceId);
				SceneManager::Instance().AddObject(obj);

				break;
			}
		}
	}
}

void Editor::UnLoadRoom(int _InstanceId)
{
	auto& objList = SceneManager::Instance().GetObjList();

	for (auto& obj : objList)
	{
		//部屋の番号が同じオブジェクトを消去
		if (obj->GetInstanceID() == _InstanceId)
		{
			obj->SetExpired();
		}
	}
}

void Editor::DrawMainWindow()
{
	ImGui::Begin("Editor");

	ImGui::Text("FPS : %d",
		Application::Instance().GetNowFPS());

	///////////セーブ＆ロード//////////
	ImGui::Separator();
	//セーブボタン
	ImGui::InputText("FileName", m_filename, sizeof(m_filename));
	if (ImGui::Button("Save"))
	{
		Save();
	}
	ImGui::SameLine();
	//ロードボタン
	if (ImGui::Button("Load"))
	{
		Load();
	}
	ImGui::Separator();
	////////////////////////////////////


	//カメラの主導権変更
	ImGui::Checkbox(
		"Editor Camera",
		&m_editorCameraMode
	);
	
	//視点切り替えImGui
	ViewChange();
	
	ImGui::Checkbox("Hierarchy", &m_showHierarchy);
	ImGui::Checkbox("Inspector", &m_showInspector);


	for (auto objinfo : m_createObjInfo)
	{
		if (ImGui::Button(objinfo.name.c_str()))
		{
			auto obj = objinfo.obj();
			//オブジェクトの名前セット
			obj->SetName(objinfo.name);

			SceneManager::Instance().AddObject(obj);
			m_selectObj = obj;
		}
	}

	ImGui::End();
}

void Editor::DrawHierarchy()
{
	ImGui::Begin("Hierarchy");

	auto& objList = SceneManager::Instance().GetObjList();

	int id = 0;

	for (auto& obj : objList)
	{
		//ImguiにIDを割り振る
		ImGui::PushID(id);

		bool selected =(!m_selectObj.expired() &&m_selectObj.lock() == obj);

		char name[64];
		//オブジェクトの名前とIDを表示
		sprintf_s(name, "%s_%d",obj->GetName().c_str(), id);

		if (ImGui::Selectable(name, selected))
		{
			m_selectObj = obj;
		}

		//IDの割り振り終了
		ImGui::PopID();

		id++;
	}

	ImGui::End();
}

void Editor::DrawInspector()
{
	ImGui::Begin("Inspector");

	auto obj = m_selectObj.lock();

	if (!obj)
	{
		ImGui::Text("No Selection");
		ImGui::End();
		return;
	}

	Math::Vector3 pos = obj->GetPos();

	if (ImGui::DragFloat3("Position", &pos.x, 0.1f))
	{
		obj->SetPos(pos);
	}

	ImGui::Separator();

	ImGui::Text("1 Bloack +-2");

	//x座標
	ImGui::Text("PositionX");
	ImGui::SameLine();
	if (ImGui::Button("+##X"))
	{
		pos.x += 2.0f;
		obj->SetPos(pos);
	}
	ImGui::SameLine();
	if (ImGui::Button("-##X"))
	{
		pos.x -= 2.0f;
		obj->SetPos(pos);
	}

	//y座標
	ImGui::Text("PositionY");
	ImGui::SameLine();
	if (ImGui::Button("+##Y"))
	{
		pos.y += 2.0f;
		obj->SetPos(pos);
	}
	ImGui::SameLine();
	if (ImGui::Button("-##Y"))
	{
		pos.y -= 2.0f;
		obj->SetPos(pos);
	}

	//z座標
	ImGui::Text("PositionZ");
	ImGui::SameLine();
	if (ImGui::Button("+##Z"))
	{
		pos.z += 2.0f;
		obj->SetPos(pos);
	}
	ImGui::SameLine();
	if (ImGui::Button("-##Z"))
	{
		pos.z -= 2.0f;
		obj->SetPos(pos);
	}


	ImGui::Separator();

	//選択中のオブジェクトを消去
	if (ImGui::Button("Delete"))
	{
		obj->SetExpired();

		m_selectObj.reset();
	}

	ImGui::End();
}

void Editor::MouseDragMoveUpdate()
{
	auto obj = m_selectObj.lock();

	if (!obj) return;

	auto cam = SceneManager::Instance().GetCamera();

	if (!cam) return;

	if (ImGui::GetIO().WantCaptureMouse)
	{
		return;
	}

	// 左クリック中
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000&&GetAsyncKeyState(VK_SHIFT) & 0x8000)
	{
		POINT pt;

		GetCursorPos(&pt);

		ScreenToClient(Application::Instance().GetWindowHandle(),&pt);

		Math::Vector3 rayPos;
		Math::Vector3 rayDir;
		float rayRange = 0;

		cam->GenerateRayInfoFromClientPos(
			pt,
			rayPos,
			rayDir,
			rayRange
		);

		// Z=0平面との交点
		if (fabs(rayDir.z) > 0.0001f)
		{
			float t = -rayPos.z / rayDir.z;

			Math::Vector3 hitPos = rayPos + rayDir * t;

			Math::Vector3 pos = obj->GetPos();

			pos.x = hitPos.x;
			pos.y = hitPos.y;

			obj->SetPos(pos);
		}
	}
}

void Editor::CameraUpdate()
{
	if (!m_editorCameraMode) return;

	auto cam = SceneManager::Instance().GetCamera();

	if (!cam) return;

	// ----------------------
	// ホイールズーム
	// ----------------------

	m_cameraDistance -= Application::Instance().GetMouseWheelValue() *0.05f;

	/*if (m_cameraDistance < 3.0f)
	{
		m_cameraDistance = 3.0f;
	}*/

	// ----------------------
	// 右ドラッグ移動（視点移動）
	// ----------------------
	POINT pt;

	GetCursorPos(&pt);

	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
	{
		int dx = pt.x - m_oldMousePos.x;
		int dy = pt.y - m_oldMousePos.y;

		float moveSpeed = 0.05f;

		switch (m_viewType)
		{
		case EditorViewType::Front:
		case EditorViewType::Back:
			m_cameraPos.x -= dx * moveSpeed;
			m_cameraPos.y += dy * moveSpeed;
			break;

		case EditorViewType::Left:
		case EditorViewType::Right:
			m_cameraPos.z += dx * moveSpeed;
			m_cameraPos.y -= dy * moveSpeed;
			break;
		case EditorViewType::Top:
		case EditorViewType::Bottom:
			m_cameraPos.x -= dx * moveSpeed;
			m_cameraPos.z += dy * moveSpeed;
			break;
		}
	}

	m_oldMousePos = pt;


	Math::Vector3 camPos;
	Math::Vector3 camRot;

	//カメラの位置、角度調整
	switch (m_viewType)
	{
	case EditorViewType::Top:
		camPos = { m_cameraPos.x,m_cameraPos.y + m_cameraDistance,m_cameraPos.z };
		camRot = {  90.0f,0,0 };
		break;
	case EditorViewType::Bottom:
		camPos = { m_cameraPos.x,m_cameraPos.y - m_cameraDistance,m_cameraPos.z };
		camRot = {  -90.0f,0,0 };
		break;
	case EditorViewType::Front:
		camPos = { m_cameraPos.x,m_cameraPos.y,m_cameraPos.z - m_cameraDistance };
		camRot = { 0,0,0 };
		break;
	case EditorViewType::Back:
		camPos = { m_cameraPos.x,m_cameraPos.y,m_cameraPos.z + m_cameraDistance };
		camRot = { 0, 180.0f,0 };
		break;
	case EditorViewType::Left:
		camPos = { m_cameraPos.x - m_cameraDistance,m_cameraPos.y,m_cameraPos.z };
		camRot = { 0, 90.0f,0 };
		break;
	case EditorViewType::Right:
		camPos = { m_cameraPos.x + m_cameraDistance,m_cameraPos.y,m_cameraPos.z };
		camRot = { 0, -90.0f,0 };
		break;
	}


	//行列
	Math::Matrix rot = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(camRot.x)) * 
		Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(camRot.y)) * 
		Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(camRot.z));
	Math::Matrix trans = Math::Matrix::CreateTranslation(camPos);
	Math::Matrix camMat = rot * trans;

	cam->SetCameraMatrix(camMat);

}

void Editor::ViewChange()
{
	ImGui::Separator();

	if (ImGui::Button("Reset"))
	{
		m_viewType = EditorViewType::Front;
		m_cameraPos = { 0,0,-10 };
		m_cameraDistance = 0;
	}

	if (ImGui::Button("Top"))
	{
		m_viewType = EditorViewType::Top;
		m_cameraPos.y = 10.0f;
	}

	ImGui::SameLine();

	if (ImGui::Button("Bottom"))
	{
		m_viewType = EditorViewType::Bottom;
		m_cameraPos.y =-10.0f;
	}

	if (ImGui::Button("Front"))
	{
		m_viewType = EditorViewType::Front;
		m_cameraPos.z = -10.0f;
	}

	ImGui::SameLine();

	if (ImGui::Button("Back"))
	{
		m_viewType = EditorViewType::Back;
		m_cameraPos.z = 10.0f;
	}

	if (ImGui::Button("Left"))
	{
		m_viewType = EditorViewType::Left;
		m_cameraPos.x = -10.0f;
	}

	ImGui::SameLine();

	if (ImGui::Button("Right"))
	{
		m_viewType = EditorViewType::Right;
		m_cameraPos.x = 10.0f;
	}

	ImGui::Separator();
}

void Editor::KeyUpdate()
{
	//ImGuiIO& io = ImGui::GetIO();

	////Imguiを操作しているときはキー操作を受け付けない
	//if (io.WantCaptureMouse || io.WantCaptureKeyboard)
	//{
	//	return;
	//}

	if (Inp.GetEditorKeyDown(EditorKeyType::SelectKey))
	{
		POINT pt;

		GetCursorPos(&pt);

		ScreenToClient(
			Application::Instance().GetWindowHandle(),
			&pt
		);

		auto cam = SceneManager::Instance().GetCamera();

		if (!cam) return;

		Math::Vector3 rayPos;
		Math::Vector3 rayDir;
		float rayRange;

		cam->GenerateRayInfoFromClientPos(
			pt,
			rayPos,
			rayDir,
			rayRange
		);

		KdCollider::RayInfo ray;
		ray.m_pos = rayPos;
		ray.m_dir = rayDir;
		ray.m_range = rayRange;
		ray.m_type = KdCollider::TypeGround;

		float nearest = FLT_MAX;
		std::shared_ptr<KdGameObject> hitObj = nullptr;

		auto& objList = SceneManager::Instance().GetObjList();

		for (auto& obj : objList)
		{
			std::list<KdCollider::CollisionResult> ret;

			if (obj->Intersects(ray, &ret))
			{
				for (auto& r : ret)
				{
					if (r.m_overlapDistance < nearest)
					{
						nearest = r.m_overlapDistance;
						hitObj = obj;
					}
				}
			}
		}

		if (hitObj)
		{
			m_selectObj = hitObj;
		}
	}

	auto selectObj = m_selectObj.lock();

	if (!selectObj) return;

	Math::Vector3 pos = selectObj->GetPos();

	// ← →
	if (Inp.GetEditorKeyDown(EditorKeyType::LeftKey))
	{
		pos.x -= 2.0f;
		selectObj->SetPos(pos);
	}

	if (Inp.GetEditorKeyDown(EditorKeyType::RightKey))
	{
		pos.x += 2.0f;
		selectObj->SetPos(pos);
	}

	// ↑ ↓
	if (Inp.GetEditorKeyDown(EditorKeyType::UpKey))
	{
		pos.y += 2.0f;
		selectObj->SetPos(pos);
	}

	if (Inp.GetEditorKeyDown(EditorKeyType::DownKey))
	{
		pos.y -= 2.0f;
		selectObj->SetPos(pos);
	}

	// 選択中オブジェクト複製
	if (Inp.GetEditorKeyDown(EditorKeyType::CreateKey))
	{
		for (auto& createInfo : m_createObjInfo)
		{
			if (createInfo.name == selectObj->GetName())
			{
				auto newObj = createInfo.obj();

				newObj->SetName(createInfo.name);

				// 元オブジェクトと同じ位置
				newObj->SetPos(selectObj->GetPos());

				SceneManager::Instance().AddObject(newObj);

				// 複製したものを選択状態にするなら
				m_selectObj = newObj;

				break;
			}
		}
	}
}

void Editor::Save()
{
	FILE* fp = nullptr;

	//ファイルの名前
	std::string path = "Asset/Data/StageData/RoomData/" + std::string(m_filename) + ".csv";

	fopen_s(&fp, path.c_str(), "w");

	if (!fp) return;

	auto& objList = SceneManager::Instance().GetObjList();

	for (auto& obj : objList)
	{
		Math::Vector3 pos = obj->GetPos();

		fprintf(fp,
			"%s,%f,%f,%f\n",
			obj->GetName().c_str(),
			pos.x,
			pos.y,
			pos.z);
	}

	fclose(fp);
}

void Editor::Load()
{
	m_selectObj.reset();

	auto& objList = SceneManager::Instance().GetObjList();

	for (auto& obj : objList)
	{
		obj->SetExpired();
	}

	FILE* fp = nullptr;

	std::string path = "Asset/Data/StageData/RoomData/" + std::string(m_filename) + ".csv";

	fopen_s(&fp, path.c_str(), "r");

	if (!fp) return;

	char objName[256] = "";

	float x, y, z;

	while (
		fscanf_s(
			fp,
			"%255[^,],%f,%f,%f\n",
			objName,
			(unsigned)_countof(objName),
			&x,
			&y,
			&z
		) == 4
		)
	{
		for (auto& createInfo : m_createObjInfo)
		{
			if (createInfo.name == objName)
			{
				auto obj = createInfo.obj();

				obj->SetName(createInfo.name);

				obj->SetPos({ x,y,z });

				SceneManager::Instance().AddObject(obj);

				break;
			}
		}
	}

	fclose(fp);
}