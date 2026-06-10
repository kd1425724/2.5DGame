#include "Input.h"
#include"../Info/Info.h"
void C_Input::Release()
{

}
void C_Input::Init()
{
	//マウス座標
	mouse = { 0,0 };

	//クリックフラグ
	m_mouseclickflg = false;

	for (int i = 0; i < (int)PlayerKeyType::PlayerKeyNum; i++)
	{
		m_playerkeyflg[i] = false;
		m_oldplayerkeyflg[i] = false;
	}

	for (int i = 0; i < (int)UserKeyType::UserKeyNum; i++)
	{
		m_userkeyflg[i] = false;
	}

	for (int i = 0; i < (int)DebugKeyType::DebugKeyNum; i++)
	{
		m_debugkeyflg[i] = false;
	}

	//デフォルトキーセット
	PlayerDefaultKeySet();
	UserDefaultKeySet();
	DebugDefaultKeySet();
	EditorDefaultKeySet();
}
void C_Input::Update(HWND hwnd)
{
	//マウスホイールの値をリセット
	m_mouseWheel = 0;

	//プレイヤーキーのフラグ更新
	for (int i = 0; i < (int)PlayerKeyType::PlayerKeyNum; i++)
	{
		m_oldplayerkeyflg[i] = m_playerkeyflg[i];
		m_playerkeyflg[i] =(GetAsyncKeyState(m_playerkey[i]) & 0x8000);
	}

	//エディターキーのフラグ更新
	for (int i = 0; i < (int)EditorKeyType::EditorKeyNum; i++)
	{
		m_oldeditorkeyflg[i] = m_editorkeyflg[i];
		m_editorkeyflg[i] = (GetAsyncKeyState(m_editorkey[i]) & 0x8000);
	}

	//アドレス渡しでマウス座標取得
	GetMousePos(&mouse, hwnd);

	//クリックフラグ
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		m_mouseclickflg = true;
	}
	else
	{
		m_mouseclickflg = false;
	}

	for (int i = 0; i < (int)UserKeyType::UserKeyNum; i++)
	{
		if (GetAsyncKeyState(m_userkey[i]) & 0x8000)
		{
			m_userkeyflg[i] = true;
		}
		else
		{
			m_userkeyflg[i] = false;
		}
	}

	for (int i = 0; i < (int)DebugKeyType::DebugKeyNum; i++)
	{
		if (GetAsyncKeyState(m_debugkey[i])&0x8000)
		{
			m_debugkeyflg[i] = true;
		}
		else
		{
			m_debugkeyflg[i] = false;
		}
	}
}
void C_Input::Draw()
{
}


void C_Input::PlayerDefaultKeySet()
{
	static const int num = (int)PlayerKeyType::PlayerKeyNum;

	int defaultkey[num] = { (int)PlayerKeyDefaultType::Attack,
						(int)PlayerKeyDefaultType::Jump,
						(int)PlayerKeyDefaultType::Skill};

	for (int i = 0; i < num; i++)
	{
		m_playerkey[i] = defaultkey[i];
	}
}

void C_Input::UserDefaultKeySet()
{
	static const int num = (int)UserKeyType::UserKeyNum;

	int defaultkey[num] = { (int)UserKeyDefaultType::Top,
						(int)UserKeyDefaultType::Bottom,
						(int)UserKeyDefaultType::Left,
						(int)UserKeyDefaultType::Right,
						(int)UserKeyDefaultType::ZKey,
						(int)UserKeyDefaultType::ESCAPE};

	for (int i = 0; i < num; i++)
	{
		m_userkey[i] = defaultkey[i];
	}
}

void C_Input::DebugDefaultKeySet()
{
	static const int num = (int)DebugKeyType::DebugKeyNum;

	int defaultkey[num] = { (int)DebugKeyDefaultType::Pkey,
						(int)DebugKeyDefaultType::Okey,
						(int)DebugKeyDefaultType::Ikey,
						(int)DebugKeyDefaultType::Ukey,
						(int)DebugKeyDefaultType::ZEROKey,
						(int)DebugKeyDefaultType::NINEKey};

	for (int i = 0; i < num; i++)
	{
		m_debugkey[i] = defaultkey[i];
	}
}

void C_Input::EditorDefaultKeySet()
{
	static const int num = (int)EditorKeyType::EditorKeyNum;

	int defaultkey[num] = { (int)EditorKeyDefaultType::ModeChangeKey,
						(int)EditorKeyDefaultType::SelectKey,
						(int)EditorKeyDefaultType::UpKey,
						(int)EditorKeyDefaultType::DownKey,
						(int)EditorKeyDefaultType::LeftKey,
						(int)EditorKeyDefaultType::RightKey,
						(int)EditorKeyDefaultType::CreateKey,
						(int)EditorKeyDefaultType::DeleteKey,
						(int)EditorKeyDefaultType::CtrlKey };

	for (int i = 0; i < num; i++)
	{
		m_editorkey[i] = defaultkey[i];
	}
}

void C_Input::GetMousePos(POINT* mousePos, HWND hwnd)
{
	//ディスプレイ上のマウス座標を取得(PC画面の左上が(0,0))
	GetCursorPos(mousePos);

	//指定のウィンドウ基準のマウス座標に変換(実行画面の左上が(0,0))
	ScreenToClient(hwnd, mousePos);

	//マウスの座標系を実行ウィンドウの座標系(中心が 0 , 0)に補正
	mousePos->x -= INFO.ScrWidth / 2;
	mousePos->y -= INFO.ScrHeight / 2;
	mousePos->y *= -1;
}
