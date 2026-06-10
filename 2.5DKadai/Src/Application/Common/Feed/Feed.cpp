#include "Feed.h"
#include"../CommonAsset/CommonAsset.h"

void C_Feed::Release()
{
}

void C_Feed::FeedInInit(float time)
{
	if (m_state != NoFeed)return;

	m_alpha = 1.0f;
	m_delta = 1.0f / time;
	m_state = FeedIn;

	m_feedflg = true;

	m_finishpattern = nullptr;
}

void C_Feed::FeedOutInit(float time, function<void()> finishpattern)
{
	if (m_state != NoFeed)return;

	m_alpha = 0.0f;
	m_delta = 1.0f / time;
	m_state = FeedOut;

	m_feedflg = true;

	m_finishpattern = finishpattern;
}
void C_Feed::Update()
{
	if (!m_feedflg) { return; }

	if (m_state == FeedIn)
	{
		m_alpha -= m_delta;
		if (m_alpha <= 0.0f)
		{
			FeedEnd();
		}
	}

	if (m_state == FeedOut)
	{
		m_alpha += m_delta;
		if (m_alpha >= 1.0f)
		{
			FeedEnd();
		}
	}

	m_mat = Math::Matrix::CreateTranslation(0, 0, 0);
}
void C_Feed::DrawSprite()
{
	if (!m_feedflg) { return; }

	Math::Color color = { 0, 0, 0, m_alpha };
	KdShaderManager::Instance().m_spriteShader.SetMatrix(m_mat);
	KdShaderManager::Instance().m_spriteShader.DrawTex(ASSET.GetWhiteBackTex(), 0, 0, ASSET.GetWhiteBackRect(), &color);
}

void C_Feed::FeedEnd()
{
	m_alpha = 0.0f;

	m_state = NoFeed;

	//処理が入っていたら
	if (m_finishpattern)
	{
		m_finishpattern();
	}
}
