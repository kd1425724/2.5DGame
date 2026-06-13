#pragma once
	
class BaseStageBlock:public KdGameObject
{
public:
	BaseStageBlock(){}
	 ~BaseStageBlock()override{}

	void Init()override;
	void Update()override;
	void DrawLit()override;

	static std::unordered_map<std::string, std::shared_ptr<KdModelData>> s_modelTable;

	//SetAssetしてからInit
	void SetAsset(const std::string& modelname)override
	{
		auto& model = s_modelTable[modelname];

		if (!model)
		{
			model = std::make_shared<KdModelData>();

			std::string path =
				"Asset/Models/Object/Stage/" +
				modelname + "/" + modelname + ".gltf";

			model->Load(path);
		}

		m_model = model;
	}

	void OnHit(KdGameObject* _other)override;

protected:
	std::shared_ptr<KdModelData> m_model;

private:





};

