class SquareEffect : public KdGameObject
{
public:

	void Init()override;
	void Update()override;
	void DrawEffect()override;
	void DrawBright()override;

	void SetVel(const Math::Vector3& vel)
	{
		m_vel = vel;
	}

	void SetLife(const int& life)
	{
		m_life = life;
	}

private:

	std::shared_ptr<KdSquarePolygon> m_polygon;

	Math::Vector3 m_vel;

	float m_alpha = 1;

	int m_life = 20;
};