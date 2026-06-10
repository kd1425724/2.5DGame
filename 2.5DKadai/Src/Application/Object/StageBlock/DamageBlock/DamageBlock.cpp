#include "DamageBlock.h"

void DamageBlock::Init()
{
	if (!m_model)return;

	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape
	(
		"DamageBlockColision",
		m_model,
		KdCollider::TypeDamage
	);
}