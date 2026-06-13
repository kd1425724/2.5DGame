#include "Num.h"
#include"../../Common/CommonAsset/CommonAsset.h"

void Num::SetNumInfo(UINT _num, Math::Vector3 _startpos, Math::Vector3 _scale,
	Math::Color _color, bool _maxdigitsflg, int _maxdigits)
{
	m_num = _num;
	m_pos = _startpos;
	m_scale = _scale;
	m_color = _color;
	m_maxdigitsflg = _maxdigitsflg;
	m_maxdigits = _maxdigits;
}

void Num::DrawSprite()
{
	Math::Matrix s;
	Math::Matrix t;
	Math::Matrix mat;

	Math::Rectangle Srect = ASSET.GetNumRect();

	// 0対策（0の場合は0のみ表示）
	if (m_num == 0)
	{
		s = Math::Matrix::CreateScale(m_scale);
		t = Math::Matrix::CreateTranslation(m_pos);
		mat = s * t;

		Math::Rectangle rect = { (long)m_num * Srect.width,Srect.y,Srect.width,Srect.height };

		KdShaderManager::Instance().m_spriteShader.SetMatrix(mat);
		KdShaderManager::Instance().m_spriteShader.DrawTex(ASSET.GetNumTex(), 0, 0, &rect, &m_color);

		for (int i = 1; i < m_maxdigits; i++)
		{
			Math::Vector3 pos = m_pos;
			pos.x -= Srect.width * m_scale.x * i;

			s = Math::Matrix::CreateScale(m_scale);
			t = Math::Matrix::CreateTranslation(pos);
			mat = s * t;

			Math::Rectangle rect = { 0 * Srect.width,Srect.y,Srect.width,Srect.height };

			KdShaderManager::Instance().m_spriteShader.SetMatrix(mat);
			KdShaderManager::Instance().m_spriteShader.DrawTex(ASSET.GetNumTex(), 0, 0, &rect, &m_color);
		}

		return;
	}

	std::vector<int> digits;

	UINT num = m_num;

	//numが０になるまでループ
	while (num > 0)
	{
		digits.push_back(num % 10);
		num /= 10;
	}

	if (m_maxdigitsflg)
	{
		//最大桁数まで０代入
		while (digits.size() < m_maxdigits)
		{
			digits.push_back(0);
		}
	}

	for (int i = 0; i < digits.size(); i++)
	{
		Math::Vector3 pos = m_pos;
		pos.x -= Srect.width * m_scale.x * i*10;

		s = Math::Matrix::CreateScale(m_scale);
		t = Math::Matrix::CreateTranslation(pos);
		mat = s * t;

		Math::Rectangle rect = { digits[i] * Srect.width,Srect.y,Srect.width,Srect.height };

		KdShaderManager::Instance().m_spriteShader.SetMatrix(mat);
		KdShaderManager::Instance().m_spriteShader.DrawTex(ASSET.GetNumTex(), 0, 0, &rect, &m_color);
	}

	KdShaderManager::Instance().m_spriteShader.SetMatrix(Math::Matrix::Identity);
}
