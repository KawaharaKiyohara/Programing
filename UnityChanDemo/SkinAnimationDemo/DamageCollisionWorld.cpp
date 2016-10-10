/*!
 * @brief	�G�A�v���C���[�Ƀ_���[�W��^����R���W�������[���h�B
 */

#include "stdafx.h"
#include "DamageCollisionWorld.h"

DamageCollisionWorld::DamageCollisionWorld()
{
}

DamageCollisionWorld::~DamageCollisionWorld()
{
}
/*!
*@brief	�_���[�W�R���W�����Əd�Ȃ��Ă��邩���ׂ�B
*/
const DamageCollisionWorld::Collision* DamageCollisionWorld::FindOverlappedDamageCollision(EnAttr attr, const CVector3& pos, float radius) const
{
	for (auto& collision : collisions) {
		if (collision.attr == attr) {
			float t = collision.radius + radius;
			CVector3 diff;
			diff.Subtract(collision.position, pos);
			if (diff.LengthSq() < t * t) {
				//���������B
				return &collision;
			}
		}
	}
	return nullptr;
}
void DamageCollisionWorld::Update()
{
	std::list<Collision>::iterator it = collisions.begin();
	while(it != collisions.end()){
		it->time += GameTime().GetFrameDeltaTime();
		if(it->time > it->life){
			//���S�B
			it = collisions.erase(it);
		}else{
			it++;
		}
	}
}