#pragma once

class Editor
{
public:

	void Init(KdWindow& window);

	void Update();

	void Draw();

	bool IsEditMode() const
	{
		return m_editMode;
	}

private:

	void DrawMainWindow();
	void DrawHierarchy();
	void DrawInspector();

	std::weak_ptr<KdGameObject> m_selectObj;

	KdWindow* m_window = nullptr;

	bool m_editMode = true;

	bool m_showHierarchy = true;
	bool m_showInspector = true;

	bool m_dragMove = false;

	//マウスで移動更新
	void MouseDragMoveUpdate();


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