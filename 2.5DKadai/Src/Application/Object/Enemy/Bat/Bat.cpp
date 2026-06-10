#include "Bat.h"

void Bat::Init()
{
	//バットデータロード
	DataLoad("Bat");

	//座標
	m_pos = {};
	//移動量
	m_move = { 1,0,0 };
	//移動スピード
	m_speed = 0.1f;
	
	//アニメーション用
	m_anim = 0;
	//サイズ（反転用）
	m_scale = { -1,1,1 };

	//初期アニメーションはFly
	UVRectControl((int)BatAnimType::Fly);

	//アニメーション終了時共通処理
	m_commonanimfinishdaction = [this]() {
		UVRectControl((int)BatAnimType::Fly);
		};

}

void Bat::Update()
{
	switch (m_statepattern)
	{
	case EnemyStatePattern::Start:
		break;
	case EnemyStatePattern::Loop:
		m_move.Normalize();
		m_pos += m_move * m_speed;
		break;
	case EnemyStatePattern::Death:
		break;
	default:
		break;
	}

	//アニメーション
	UVRectControlUpdate();

	Math::Matrix mscale = Math::Matrix::CreateScale(m_scale);
	Math::Matrix mtrans = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = mscale * mtrans;
}

void Bat::DrawLit()
{
	Math::Color color = { 5,5,5,1 };
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_polygon, m_mWorld, color);
}


void Bat::UVRectControl(int _animtype, std::function<void()> _action)
{
	//上書き不可なら実行しない
	if (!m_overwritable)return;

	//共通初期化
	EnemyBase::UVRectControlInit();

	m_animtype = (BatAnimType)_animtype;

	m_animid = m_animidkeep[_animtype];

	switch (m_animtype)
	{
	case BatAnimType::Fly:
		m_animtime = 30;
		m_loopmax = 999;

		//上書き可能
		m_overwritable = true;
		break;
	case BatAnimType::AnimNum:
		break;
	default:
		break;
	}

	//共通
	m_animmax = m_animid.size();
	m_animcnt = m_loopmax;

	if (_action)
	{
		m_action = _action;
	}

	m_animflg = true;
}
