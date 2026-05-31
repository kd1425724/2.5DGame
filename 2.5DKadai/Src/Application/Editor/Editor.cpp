#include "Editor.h"

#include "../main.h"
#include "../Scene/SceneManager.h"

#include"../Object/Ground/GameGround/GameGround.h"

void Editor::Init(KdWindow& window)
{
	m_window = &window;
}

void Editor::Update()
{
	static bool oldState = false;

	bool nowState = (GetAsyncKeyState(VK_F1) & 0x8000);

	if (nowState && !oldState)
	{
		m_editMode = !m_editMode;
	}

	oldState = nowState;

	MouseDragMoveUpdate();
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

void Editor::DrawMainWindow()
{
	ImGui::Begin("Editor");

	ImGui::Text("FPS : %d",
		Application::Instance().GetNowFPS());

	ImGui::Separator();

	ImGui::Checkbox("Hierarchy", &m_showHierarchy);
	ImGui::Checkbox("Inspector", &m_showInspector);

	if (ImGui::Button("Create Ground"))
	{
		auto obj = std::make_shared<GameGround>();

		obj->Init();

		SceneManager::Instance().AddObject(obj);

		m_selectObj = obj;
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
		ImGui::PushID(id);

		bool selected =
			(!m_selectObj.expired() &&
				m_selectObj.lock() == obj);

		char name[64];
		sprintf_s(name, "Object %d", id);

		if (ImGui::Selectable(name, selected))
		{
			m_selectObj = obj;
		}

		ImGui::PopID();

		id++;
	}

	ImGui::End();

	/*ImGui::Begin("Hierarchy");

	auto& objList =
		SceneManager::Instance().GetObjList();

	int id = 0;

	for (auto& obj : objList)
	{
		ImGui::PushID(id++);

		bool selected =
			(!m_selectObj.expired() &&
				m_selectObj.lock() == obj);

		if (ImGui::Selectable("GameObject", selected))
		{
			m_selectObj = obj;
		}

		ImGui::PopID();
	}

	ImGui::End();*/
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
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		POINT pt;

		GetCursorPos(&pt);

		ScreenToClient(
			Application::Instance().GetWindowHandle(),
			&pt
		);

		Math::Vector3 rayPos;
		Math::Vector3 rayDir;
		float rayRange;

		cam->GenerateRayInfoFromClientPos(
			pt,
			rayPos,
			rayDir,
			rayRange
		);

		// Y=0平面との交点
		if (fabs(rayDir.y) > 0.0001f)
		{
			float t = -rayPos.y / rayDir.y;

			Math::Vector3 hitPos =
				rayPos + rayDir * t;

			obj->SetPos(hitPos);
		}
	}
}
