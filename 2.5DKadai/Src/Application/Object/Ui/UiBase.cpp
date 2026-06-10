#include "UiBase.h"

//継承先で上書きしなければ実行される処理
void UiBase::DrawSprite()
{
	if (!m_tex)return;

	KdShaderManager::Instance().m_spriteShader.SetMatrix(m_mWorld);
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_tex,0,0);
}
