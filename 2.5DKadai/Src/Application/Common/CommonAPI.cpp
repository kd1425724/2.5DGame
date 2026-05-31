#include "CommonAPI.h"
#include"CommonAsset/CommonAsset.h"

void C_CommonAPI::Clear()
{
	m_button.clear();
}


//bool C_CommonAPI::OutOfScreen(Math::Vector2 pos, Math::Vector2 radius)
//{
//	//画面外に出たら
//	if (pos.x + radius.x < -INFO.ScrWidth / 2 || pos.x - radius.x> INFO.ScrWidth / 2 ||
//		pos.y + radius.y < -INFO.ScrHeight / 2 || pos.y - radius.y> INFO.ScrHeight / 2)
//	{
//		return true;
//	}
//
//	return false;
//}
//
//bool C_CommonAPI::OutOfScreenPlusMargin(Math::Vector2 pos, Math::Vector2 radius)
//{
//	//画面外に出たら
//	if (pos.x + radius.x + margin < -INFO.ScrWidth / 2 || pos.x - radius.x - margin> INFO.ScrWidth / 2 ||
//		pos.y + radius.y + margin < -INFO.ScrHeight / 2 || pos.y - radius.y - margin > INFO.ScrHeight / 2)
//	{
//		return true;
//	}
//
//	return false;
//}
//
float C_CommonAPI::GetTextureAngleAdjustment(TextureAngle angle)
{
	switch (angle)
	{
	case TextureAngle::Top:
		return -DirectX::XM_PIDIV2;

	case TextureAngle::Bottom:
		return	DirectX::XM_PIDIV2;

	case TextureAngle::Left:
		return  DirectX::XM_PI;
		
	case TextureAngle::Right:
		return 0.0f;
		
	default:
		return 0.0f;
		break;
	}
}

void C_CommonAPI::NumDraw(int num, Math::Vector2 startpos, Math::Vector2 scale, Math::Color color, bool maxdigitsflg, int maxdigits)
{
	Math::Matrix s;
	Math::Matrix t;
	Math::Matrix mat;

	//マイナスなら強制＋に
	if (num < 0)
	{
		num = abs(num);
	}

	//数字間隔
	float Srect = 32.0f;

	// 0対策（0の場合は0のみ表示）
	if (num == 0)
	{
		s = Math::Matrix::CreateScale(scale.x, scale.y, 1);
		t = Math::Matrix::CreateTranslation(startpos.x, startpos.y, 0);
		mat = s * t;

		
		KdShaderManager::Instance().m_StandardShader.DrawPolygon(*ASSET.GetNumPoly(), mat, color);
		for (int i = 1; i < maxdigits; i++)
		{
			Math::Vector2 pos = startpos;
			pos.x -= Srect * scale.x * i;

			s = Math::Matrix::CreateScale(scale.x, scale.y, 1);
			t = Math::Matrix::CreateTranslation(pos.x, pos.y, 0);
			mat = s * t;
			
			ASSET.GetNumPoly()->SetUVRect(num);

			KdShaderManager::Instance().m_StandardShader.DrawPolygon(*ASSET.GetNumPoly(), mat, color);
		}

		return;
	}

	std::vector<int> digits;

	//numが０になるまでループ
	while (num > 0)
	{
		digits.push_back(num % 10);
		num /= 10;
	}

	if (maxdigitsflg)
	{
		//最大桁数まで０代入
		while (digits.size() < maxdigits)
		{
			digits.push_back(0);
		}
	}

	for (int i = 0; i < digits.size(); i++)
	{
		Math::Vector2 pos = startpos;
		pos.x -= Srect * scale.x * i;

		s = Math::Matrix::CreateScale(scale.x, scale.y, 1);
		t = Math::Matrix::CreateTranslation(pos.x, pos.y, 0);
		mat = s * t;

		ASSET.GetNumPoly()->SetUVRect(num);

		KdShaderManager::Instance().m_StandardShader.DrawPolygon(*ASSET.GetNumPoly(), mat, color);
	}
}

void C_CommonAPI::CreateButton(Math::Vector2 pos, Math::Rectangle rect, Math::Vector2 scale, std::shared_ptr<KdSquarePolygon> tex, 
	Math::Color color, std::shared_ptr<KdSquarePolygon> frametex)
{
	Button d;
	d.pos = pos;
	d.rect = rect;
	d.scale = { scale.x, scale.y };
	d.radius = { d.rect.width * scale.x,d.rect.height * scale.y };
	d.color = color;
	d.tex = tex;

	d.scaleMat = Math::Matrix::CreateScale(d.scale.x, d.scale.y, 1);
	d.transMat = Math::Matrix::CreateTranslation(d.pos.x, d.pos.y, 1);
	d.mat = d.scaleMat * d.transMat;

	//フレーム用
	d.framescale = { d.rect.width * d.scale.x / d.rect.width,
		d.rect.height * d.scale.y / d.rect.height };
	d.frametex = frametex;

	d.framescalemat = Math::Matrix::CreateScale(d.framescale.x, d.framescale.y, 1);
	d.framemat = d.framescalemat * d.transMat;

	m_button.push_back(d);
}

void C_CommonAPI::SetAction(int index, std::function<void()> action)
{
	//範囲外なら処理しない
	if (index < 0 || index >= static_cast<int>(m_button.size()))
	{
		return;
	}

	if (action)
	{
		m_button[index].action = action;
	}
}

void C_CommonAPI::CreateButtonUpdate()
{
	for (int i = 0; i < m_button.size(); i++)
	{
		m_button[i].scaleMat = Math::Matrix::CreateScale(m_button[i].scale.x, m_button[i].scale.y, 1);
		m_button[i].transMat = Math::Matrix::CreateTranslation(m_button[i].pos.x, m_button[i].pos.y, 1);
		m_button[i].mat = m_button[i].scaleMat * m_button[i].transMat;

		m_button[i].framescalemat = Math::Matrix::CreateScale(m_button[i].framescale.x, m_button[i].framescale.y, 1);
		m_button[i].framemat = m_button[i].framescalemat * m_button[i].transMat;
	}
}

void C_CommonAPI::CreateButtonDrawSprite()
{
	for (int i = 0; i < m_button.size(); i++)
	{
		Math::Matrix mat = m_button[i].mat;

		KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_button[i].tex, mat, m_button[i].color);
	}
}
void C_CommonAPI::ButtonExecute(int index)
{
	//範囲外なら処理しない
	if (index < 0 || index >= static_cast<int>(m_button.size()))
	{
		return;
	}

	//SOUND.SetPlaySE(SEType::DecisionSE);

	//生成時に入れたアクションを実行
	m_button[index].action();
}

void C_CommonAPI::IsOnTopButtonDraw(int index)
{
	//範囲外なら処理しない
	if (index < 0 || index >= static_cast<int>(m_button.size()))
	{
		return;
	}

	Math::Matrix mat = m_button[index].framemat;

	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_button[index].frametex, mat, m_button[index].color);
}

