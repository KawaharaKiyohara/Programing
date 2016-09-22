#pragma once
class ICollider;

//���̏��B
struct RigidBodyInfo {
	RigidBodyInfo() :
		collider(NULL),
		mass(0.0f)
	{
		pos = CVector3::Zero;
		rot = CQuaternion::Identity;
	}
	CVector3 pos;				//���W�B
	CQuaternion rot;			//��]�B
	ICollider* collider;		//�R���C�_�[�B
	float mass;					//���ʁB

};
//���̃N���X�B
class RigidBody
{
	btRigidBody*			rigidBody;		//���́B
	btDefaultMotionState*	myMotionState;	//���[�V�����X�e�[�g�B
public:
	RigidBody();
	~RigidBody();
	void Release();
	void Create(RigidBodyInfo& rbInfo);
	btRigidBody* GetBody()
	{
		return rigidBody;
	}
};

