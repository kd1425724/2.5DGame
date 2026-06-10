#pragma once

class Editor
{
public:

	void Init();
	void Update();
	void Draw();

	bool IsEditMode() const
	{
		return m_editMode;
	}

	//エディターがカメラの主導権を持っているかを取得
	bool IsEditorCameraMode() const
	{
		return m_editorCameraMode;
	}
	//エディター中オブジェクトの更新をするかどうか
	bool IsObjectUpdateMode()const
	{
		return m_objectupdatemode;
	}

	void DebagDraw();

private:

	//セーブロード
	//Imgui用
	void Save();
	void Load();

	//ファイルの名前設定用
	char m_filename[256] = "";

	// デバッグ情報クラス
	std::unique_ptr<KdDebugWireFrame> m_pDebugWire = nullptr;
	
	void DrawMainWindow();
	void DrawHierarchy();
	void DrawInspector();

	//生成するオブジェクト情報
	struct CreateObjectInfo
	{
		std::string name;
		std::function<std::shared_ptr<KdGameObject>()> obj;
	};
	//pushback（登録）する際↓を設定する
	//name	...オブジェクトの名前
	//obj	...生成するオブジェクトを返すラムダ式
	std::vector<CreateObjectInfo> m_createObjInfo;

	//選択中オブジェクト
	std::weak_ptr<KdGameObject> m_selectObj;

	bool m_editMode = true;

	bool m_objectupdatemode = false;

	bool m_showHierarchy = true;
	bool m_showInspector = true;

	bool m_dragMove = false;

	//マウスで移動更新
	void MouseDragMoveUpdate();

	//カメラの主導権変更用
	bool m_editorCameraMode = false;
	//カメラ更新
	void CameraUpdate();

	//カメラ
	enum class EditorViewType
	{
		Perspective,    // 自由視点
		Front,			//前視点
		Back,			//後視点
		Left,			//左視点
		Right,			//右視点
		Top,			//上視点
		Bottom,			//下視点
	};
	EditorViewType m_viewType = EditorViewType::Front;

	//視点切り替え
	void ViewChange();

	// エディタカメラ
	Math::Vector3 m_cameraPos = { 0,0,-10 };
	float m_cameraDistance = 0.0f;

	// ドラッグ用
	POINT m_oldMousePos = {};

	//キーでの操作
	void KeyUpdate();

	float m_onemovenum = 1;


private:


	Editor() {}
	~Editor() {}

public:

	static Editor& Instance()
	{
		static Editor instance;
		return instance;
	}
};

#define EDITOR Editor::Instance()