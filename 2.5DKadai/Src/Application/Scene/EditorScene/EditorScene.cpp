#include "EditorScene.h"

#include "../../main.h"
#include "../../Scene/SceneManager.h"

#include"../../Object/Ground/GameGround/GameGround.h"

void EditorScene::Init(KdWindow& window)
{
	m_window = &window;
}

void EditorScene::Update()
{
	static bool oldState = false;

	bool nowState = (GetAsyncKeyState(VK_F1) & 0x8000);

	if (nowState && !oldState)
	{
		m_editMode = !m_editMode;
	}

	oldState = nowState;
}

void EditorScene::Draw()
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

void EditorScene::DrawMainWindow()
{
	ImGui::Begin("EditorScene");

	ImGui::Text("FPS : %d",
		Application::Instance().GetNowFPS());

	ImGui::Separator();

	ImGui::Checkbox("Hierarchy", &m_showHierarchy);
	ImGui::Checkbox("Inspector", &m_showInspector);

	ImGui::End();

	if (ImGui::Button("Create Ground"))
	{
		auto obj = std::make_shared<GameGround>();

		obj->Init();

		SceneManager::Instance().AddObject(obj);

		m_selectObj = obj;
	}
}

void EditorScene::DrawHierarchy()
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

void EditorScene::DrawInspector()
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