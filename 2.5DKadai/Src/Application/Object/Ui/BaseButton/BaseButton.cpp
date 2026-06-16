#include "BaseButton.h"

void BaseButton::Init()
{
	m_scale = { 1.2f,1.2f,1.2f };

	m_pos = {};
	m_basepos = {};
	m_rot = {};

	m_mWorld = Math::Matrix::Identity;

	m_action = nullptr;

	m_model = nullptr;
}

void BaseButton::PreUpdate()
{
	m_selectflg = false;
}

void BaseButton::Update()
{
	if (!m_selectflg)
	{
		/*SetSize(1.3f);

		m_time = 0;

		Math::Vector3 dir = {};

		dir = (m_basepos - m_pos);
		m_pos += dir * m_speed;*/
	}

	MatrixUpdate();
}

void BaseButton::DrawLit()
{
	if (!m_model)return;

	//デフォルト透明度
	Math::Color color = { 1,1,1,0.7f };

	if (m_selectflg)
	{
		//選択中透明度
		color = { 1,1,1,10 };
	}
	
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld, color);

}

void BaseButton::SelectUpdate()
{
	//選択中にする処理
	m_selectflg = true;

	SetSize(1.5f);

	m_time += 0.08f;

	Math::Vector3 pos = m_basepos;
	pos.y += sin(m_time
	) * 0.2f;

	m_pos = pos;
}

void BaseButton::ButtonLoad(const std::string & _filename, std::function<void()> _action)
{
	std::string path = "Asset/Models/Object/Button/" + _filename + "Block/" + _filename + "Block.gltf";

	m_model = std::make_shared<KdModelData>();
	m_model->Load(path);

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
