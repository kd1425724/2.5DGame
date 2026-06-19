#pragma once
#include "../../UiBase.h"

class Result : public UiBase
{
public:

	enum ResultType
	{
		Clear,
		GameOver
	};

	Result() {}
	~Result() override {}

	void Init() override;
	void DrawSprite() override;

private:

	ResultType m_result = Clear;

	std::shared_ptr<KdTexture> m_clearTex;
	std::shared_ptr<KdTexture> m_gameOverTex;
};