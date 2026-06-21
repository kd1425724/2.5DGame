#pragma once

enum class PlayerKeyType
{
	Jump,
	Plunge,
	Left,
	Right,
	PlayerKeyNum
};


enum class UserKeyType
{
    Top ,
    Bottom ,
    Left ,
    Right,
    DecisionKey ,
    ESCAPE,
    UserKeyNum
};

enum class DebugKeyType
{
	PKey,
	IKey,
	LKey,
	ZEROKey,
	NINEKey,
    DebugKeyNum,
};


enum class EditorKeyType
{
	ModeChangeKey,
	SelectKey,
	UpKey,
	DownKey,
	LeftKey,
	RightKey,
	CreateKey,
	DeleteKey,
	CtrlKey,
	EditorKeyNum,
};


class C_Input
{
public:
 
    void Init();
    void Update(HWND hwnd);
    void Draw();

    void GetMousePos(POINT* mousePos, HWND hwnd);

    POINT GetMousePos() { return mouse; }

    bool GetClickFlg() { return m_mouseclickflg; }

   /* SHORT GetPlayerKey(PlayerKeyType playerkeytype)
    {
        return GetAsyncKeyState(m_playerkey[(int)playerkeytype]) & 0x8000;
    }*/

    bool GetPlayerKey(PlayerKeyType playerkeytype)
    {
        return m_playerkeyflg[(int)playerkeytype];
    }

    bool GetPlayerKeyDown(PlayerKeyType type)
    {
        return m_playerkeyflg[(int)type] &&
            !m_oldplayerkeyflg[(int)type];
    }

    bool GetPlayerKeyUp(PlayerKeyType type)
    {
        return !m_playerkeyflg[(int)type] &&
            m_oldplayerkeyflg[(int)type];
    }

    bool GetUserKey(UserKeyType _userkeytype)
    {
        return m_userkeyflg[(int)_userkeytype];
    }

    bool GetUserKeyDown(UserKeyType type)
    {
        return m_userkeyflg[(int)type] &&
            !m_olduserkeyflg[(int)type];
    }

	bool GetUserKeyUp(UserKeyType type)
	{
		return !m_userkeyflg[(int)type] &&
			m_olduserkeyflg[(int)type];
	}

	bool GetDebugKey(DebugKeyType _debugkeytype)
	{
		return m_debugkeyflg[(int)_debugkeytype];
	}

	bool GetDebugKeyDown(DebugKeyType type)
	{
		return m_debugkeyflg[(int)type] &&
			!m_olddebugkeyflg[(int)type];
	}

	bool GetDebugKeyUp(DebugKeyType type)
	{
		return !m_debugkeyflg[(int)type] &&
			m_olddebugkeyflg[(int)type];
	}

	//エディターのキー
	bool GetEditorKey(EditorKeyType editorkeytype)
	{
		return m_editorkeyflg[(int)editorkeytype];
	}

	bool GetEditorKeyDown(EditorKeyType type)
	{
		return m_editorkeyflg[(int)type] &&
			!m_oldeditorkeyflg[(int)type];
	}

	bool GetEditorKeyUp(EditorKeyType type)
	{
		return !m_editorkeyflg[(int)type] &&
			m_oldeditorkeyflg[(int)type];
	}


    void PlayerDefaultKeySet();
    void UserDefaultKeySet();
    void DebugDefaultKeySet();
	void EditorDefaultKeySet();

private:
	enum class PlayerKeyDefaultType
	{
		Jump =VK_UP,
		Plunge = VK_DOWN,
		Left=VK_LEFT,
		Right=VK_RIGHT,
	};
	enum class UserKeyDefaultType
	{
		Top = VK_UP,
		Bottom = VK_DOWN,
		Left = VK_LEFT,
		Right = VK_RIGHT,
		DecisionKey = VK_RETURN,
		ESCAPE = VK_ESCAPE,
	};

	enum class DebugKeyDefaultType
	{
		PKey = 'P',	  //タイトルに戻る
		IKey='I',		//ゴールのみのステージへ
		LKey='L',		//プレイヤーダメージ無効
		ZEROKey = '0',  //GameOverへ
		NINEKey = '9',  //Clearへ

	};
	enum class EditorKeyDefaultType
	{
		ModeChangeKey = VK_F1,
		SelectKey = VK_LBUTTON,
		UpKey = VK_UP,
		DownKey = VK_DOWN,
		LeftKey = VK_LEFT,
		RightKey = VK_RIGHT,
		CreateKey = 'U',
		DeleteKey = VK_DELETE,
		CtrlKey = VK_CONTROL
	};

	void Release();

    // ===== マウス =====
    POINT mouse = { 0, 0 };
    bool m_mouseclickflg = false;

	float m_mouseWheel = 0;

    // ===== キー =====
    int m_playerkey[(int)PlayerKeyType::PlayerKeyNum] = { 0 };
    bool m_playerkeyflg[(int)PlayerKeyType::PlayerKeyNum] = { false };
    bool m_oldplayerkeyflg[(int)PlayerKeyType::PlayerKeyNum] = { false };

    //ユーザーキー
    int m_userkey[(int)UserKeyType::UserKeyNum] = { 0 };
    bool m_userkeyflg[(int)UserKeyType::UserKeyNum] = { false };
    bool m_olduserkeyflg[(int)UserKeyType::UserKeyNum] = { false };

    //デバッグキー
    int m_debugkey[(int)DebugKeyType::DebugKeyNum] = { 0 };
    bool m_debugkeyflg[(int)DebugKeyType::DebugKeyNum] = { false };
    bool m_olddebugkeyflg[(int)DebugKeyType::DebugKeyNum] = { false };

    //デバッグキーが使えるかどうかのフラグ
	bool m_olldebugkeyflg = false;

	//エディターキー
	int m_editorkey[(int)EditorKeyType::EditorKeyNum] = { 0 };
	bool m_editorkeyflg[(int)EditorKeyType::EditorKeyNum] = { false };
	bool m_oldeditorkeyflg[(int)EditorKeyType::EditorKeyNum] = { false };

private:
	C_Input() { Init(); }
    ~C_Input(){ Release(); }

public:
    static C_Input& GetInstans()
    {
        static C_Input instans;
        return instans;
    }
};

#define Inp C_Input::GetInstans()