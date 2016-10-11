/*!
 * @brief	�G�A�v���C���[�Ƀ_���[�W��^����R���W�������[���h�B
 */

#pragma once

#include "tkEngine/shape/tkSphereShape.h"

#ifdef _DEBUG
#define DEBUG_DMG_COLLISION_DRAW
#else
#define DEBUG_DMG_COLLISION_DRAW
#endif
class DamageCollisionWorld : public IGameObject{
public:
	/*!
	* @brief	�����B
	*/
	enum EnAttr {
		enDamageToEnemy,		//�G�Ƀ_���[�W��^����R���W�����B
		enDamageToPlayer,		//�v���C���[�Ƀ_���[�W��^����R���W�����B
	};
	struct Collision {
		float radius;			//���a�B
		CVector3 position;		//���S�B
		float life;				//�����B
		float damage;			//�_���[�W�ʁB
		EnAttr attr;			//�����B
		float time;
#ifdef DEBUG_DMG_COLLISION_DRAW
		CSphereShape debugShape;
#endif
	};
	
	/*!
	 * @brief	�R���X�g���N�^�B
	 */
	DamageCollisionWorld();
	/*!
	 * @brief	�f�X�g���N�^�B
	 */
	~DamageCollisionWorld();
	/*!
	 * @brief	�R���W������ǉ��B
	 */
	void Add( 
		float radius, 
		const CVector3& pos, 
		float life, 
		float damage,
		EnAttr attr
	)
	{
		CollisionPtr colli = CollisionPtr(new Collision);
		colli->radius = radius;
		colli->position = pos;
		colli->life = life;
		colli->attr = attr;
		colli->time = 0.0f;
		colli->damage = damage;
		collisions.push_back(colli);
#ifdef DEBUG_DMG_COLLISION_DRAW
		colli->debugShape.Create(radius, 10, 0xFFFF0000, true);
#endif
	}
	void Start() override
	{

	}
	/*!
	 * @brief	�X�V�B
	 */
	void Update() override;
	/*!
	*@brief	�`��
	*/
	void Render(CRenderContext& renderContext) override;
	/*!
	*@brief	�d�Ȃ��Ă���_���[�W�R���W�������擾����B
	*/
	const Collision* FindOverlappedDamageCollision(EnAttr attr, const CVector3& pos, float radius) const;
private:
	typedef std::shared_ptr<Collision> CollisionPtr;
	std::list<CollisionPtr>		collisions;
#ifdef DEBUG_DMG_COLLISION_DRAW
	CLight					light;
#endif

};

extern DamageCollisionWorld* g_damageCollisionWorld;