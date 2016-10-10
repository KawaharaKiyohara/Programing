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