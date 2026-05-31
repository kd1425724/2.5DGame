#pragma once

class CommonAsset
{
public:

	//フェード用
	std::shared_ptr<KdTexture> GetWhiteBackTex() { return m_whitebacktex; }
	Math::Rectangle* GetWhiteBackRect() { return &m_whitebackrect; }

	//プレイヤー
	//std::shared_ptr<KdSquarePolygon> GetPlayerPoly() { return m_playerpoly; }
	Math::Vector2 GetPlayerRect() { return m_playerrect; }

	//数字
	std::shared_ptr<KdSquarePolygon> GetNumPoly() { return m_numpoly; }

	//ステージセレクト説明画像
	//std::shared_ptr<KdSquarePolygon> GetStage1DescriptionPoly() { return m_Stage1DescriptionPoly; }

private:

	//フェード用
	std::shared_ptr<KdTexture> m_whitebacktex;
	Math::Rectangle m_whitebackrect = { 0,0,1280,720 };
	//プレイヤー
	//std::shared_ptr<KdSquarePolygon> m_playerpoly;
	//分割数
	Math::Vector2 m_playerrect;

	//数字
	std::shared_ptr<KdSquarePolygon> m_numpoly;
	//分割数
	Math::Vector2 m_numrect = { 10,1 };

	//ステージセレクト説明画像
	//std::shared_ptr<KdSquarePolygon> m_Stage1DescriptionPoly;

	//シングルトン
private:

	CommonAsset();
	~CommonAsset();

public:

	static CommonAsset& GetInstans()
	{
		static CommonAsset instans;
		return instans;
	}
};
//共通テクスチャ
#define ASSET CommonAsset::GetInstans()
