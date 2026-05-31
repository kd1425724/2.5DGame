#pragma once

enum class TextureAngle
{
	Top,
	Bottom,
	Left,
	Right
};

class C_CommonAPI
{
public:
	~C_CommonAPI(){}

	//画面外判定
	bool OutOfScreen(Math::Vector2 pos, Math::Vector2 radius){}
	
	//画面外判定
	bool OutOfScreenPlusMargin(Math::Vector2 pos, Math::Vector2 radius){}
	
	
	//画像向き調整
	float GetTextureAngleAdjustment(TextureAngle angle);

	//数字描画用
	//startpos...一の位
	void NumDraw(int num, Math::Vector2 startpos, Math::Vector2 scale, Math::Color color = { 1.0f,1.0f,1.0f,1.0f }, bool maxdigitsflg = false, int maxdigits = 0);

	//指定しているindexのactionを実行
	void ButtonExecute(int index);
	void IsOnTopButtonDraw(int index);

	void CreateButton(
		Math::Vector2 pos,
		Math::Rectangle rect,
		Math::Vector2 scale,
		std::shared_ptr<KdSquarePolygon> tex,
		Math::Color color,
		std::shared_ptr<KdSquarePolygon> frametex);

	void SetAction(int index,std::function<void()> action);

	void CreateButtonUpdate();
	void CreateButtonDrawSprite();

	void Clear();

private:

	struct Button
	{
		Math::Vector2 pos = { 0, 0 };
		Math::Rectangle rect = { 0, 0, 0, 0 };
		Math::Vector2 radius = { 0, 0 };
		Math::Vector2 scale = { 1, 1 };
		Math::Color color = {};

		std::shared_ptr<KdSquarePolygon> tex = nullptr;

		Math::Matrix transMat = Math::Matrix::Identity;
		Math::Matrix scaleMat = Math::Matrix::Identity;
		Math::Matrix mat = Math::Matrix::Identity;

		// フレーム用
		Math::Vector2 framescale = { 1, 1 };
		Math::Matrix framescalemat = Math::Matrix::Identity;
		Math::Matrix framemat = Math::Matrix::Identity;
		std::shared_ptr<KdSquarePolygon> frametex = nullptr;

		// 上に乗っているか
		bool GetIsOnTop();

		// 何をするか
		std::function<void()> action = nullptr;
	};


	// ===== UIスプライト =====
	std::vector<Button> m_button;

	//画面外判定余剰分
	const float margin = 500.0f;


//シングルトン
private:
	C_CommonAPI(){}

public:

	static C_CommonAPI& GetInstans()
	{
		static C_CommonAPI instans;
		return instans;
	}
};
//共通関数
#define COMMONAPI C_CommonAPI::GetInstans()
