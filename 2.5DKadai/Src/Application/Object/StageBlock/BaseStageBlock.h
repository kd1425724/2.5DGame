#pragma once
	
class BaseStageBlock:public KdGameObject
{
public:
	BaseStageBlock(){}
	 ~BaseStageBlock()override{}

	void Init()override;
	void Update()override;
	void DrawLit()override;

	//SetAssetしてからInit
	void SetAsset(const std::string& modelname)override
	{
		m_model = std::make_shared<KdModelData>();
		std::string path = "Asset/Models/Object/Stage/" + modelname + "/" + modelname + ".gltf";
		m_model->Load(path); 
	}

	virtual void OnPlayerHit(){}

protected:
	std::shared_ptr<KdModelData> m_model;

private:





};

