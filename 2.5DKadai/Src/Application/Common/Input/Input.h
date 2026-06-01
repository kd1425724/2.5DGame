#pragma once

enum class PlayerKeyType
{
	Attack,
	Jump,
	Skill,
	PlayerKeyNum
};
enum class PlayerKeyDefaultType
{
    Attack	= 'Z',
    Jump	= 'X',
	Skill	= 'C',
};

enum class UserKeyType
{
    Top ,
    Bottom ,
    Left ,
    Right,
    ZKey ,
    ESCAPE,
    UserKeyNum
};
enum class UserKeyDefaultType
{
    Top = VK_UP,
    Bottom = VK_DOWN,
    Left = VK_LEFT,
    Right = VK_RIGHT,
    ZKey = 'Z',
    ESCAPE=VK_ESCAPE,
};

enum class DebugKeyType
{
    Pkey,   //レーザーに変更
    Okey,   //バリアーに変更
    Ikey,   //敵生成に変更
    Ukey,   //リザルトへ
    ZEROKey,  //ボスを倒す
    NINEKey,  //プレイヤーの死亡フラグをONOFF
    DebugKeyNum,
};
enum class DebugKeyDefaultType
{
    Pkey='P',   //レーザーに変更
    Okey='O',   //バリアーに変更
    Ikey='I',   //敵生成に変更
    Ukey='U',   //次のシーンへ
    ZEROKey = '0',  //ボスを倒す
    NINEKey = '9',  //プレイヤーの死亡フラグをONOFF
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
	EditorKeyNum,
};
enum class EditorKeyDefaultType
{
	ModeChangeKey	= VK_F1,
	SelectKey		= VK_LBUTTON,
	UpKey			= VK_UP,
	DownKey			= VK_DOWN,
	LeftKey			= VK_LEFT,
	RightKey		= VK_RIGHT,
	CreateKey		= '1',
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

    SHORT GetUserKey(UserKeyType userkeytype)
    {
        return GetAsyncKeyState(m_userkey[(int)userkeytype]) & 0x8000;
    }

    bool GetUserKeyFlg(UserKeyType userkeytype)
    {
        return m_userkeyflg[(int)userkeytype];
    }

    SHORT GetDebugKey(DebugKeyType debugkeytype)
    {
        if (!m_olldebugkeyflg)return false;

        return GetAsyncKeyState(m_debugkey[(int)debugkeytype]) & 0x8000;
    }

    bool GetDebugKeyFlg(DebugKeyType debugkeytype)
    {
		if (!m_olldebugkeyflg)return false;

        return m_debugkeyflg[(int)debugkeytype];
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


    //デバッグキー
    int m_debugkey[(int)DebugKeyType::DebugKeyNum] = { 0 };
    bool m_debugkeyflg[(int)DebugKeyType::DebugKeyNum] = { false };

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