#pragma once
#include"../BaseScene/BaseScene.h"

class EditorScene
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

private:

	EditorScene() {}
	~EditorScene() {}

public:

	static EditorScene& Instance()
	{
		static EditorScene instance;
		return instance;
	}
};

#define EDITOR EditorScene::Instance()