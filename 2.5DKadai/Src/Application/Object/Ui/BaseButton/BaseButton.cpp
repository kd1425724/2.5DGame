#include "BaseButton.h"

void BaseButton::Init()
{
	m_pos = {};
	m_rot = {};

	m_mWorld = Math::Matrix::Identity;

	m_action = nullptr;
}

void BaseButton::PreUpdate()
{
	m_selectflg = false;
}

void BaseButton::Update()
{
	
}

void BaseButton::DrawLit()
{
	if (!m_model)return;

	//デフォルト透明度
	Math::Color color = { 1,1,1,0.8f };

	if (m_selectflg)
	{
		//選択中透明度
		color = { 1,1,1,1 };
	}
	
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld, color);

}

void BaseButton::SelectUpdate()
{
	//選択中にする処理
	m_selectflg = true;
}

void BaseButton::ButtonLoad(const std::string & _filename, std::function<void()> _action)
{
	//std::string path = "Asset/Models/Object/Button/" + _filename + "Button/" + _filename + "Button.gltf";
	std::string path = "Asset/Models/Object/Button/Block/Block.gltf";

	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Object/Button/Block/Block.gltf");

	m_name = _filename;

	if (_action)
	{
		m_action = _action;
	}
}

void BaseButton::Action()
{
	if (!m_action)return;

	m_action();
}
