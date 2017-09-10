/*!
 * @brief	�A�j���[�^�[�N���X�B
 */


#include "tkEngine/tkEnginePrecompile.h"
#include "tkEngine/graphics/animation/tkAnimation.h"

namespace tkEngine{

	CAnimation::CAnimation()
	{
	}
	CAnimation::~CAnimation()
	{
	}
	void CAnimation::Init(CSkinModelData& skinModelData, CAnimationClip* animClipList[], int numAnimClip)
	{
		TK_ASSERT(animClipList != nullptr, "animClipList��NULL�ł��B");
		m_skeleton = &skinModelData.GetSkeleton();
		for (int i = 0; i < numAnimClip; i++) {
			m_animationClips.push_back(animClipList[i]);
		}
		for (auto& ctr : m_animationPlayController) {
			ctr.Init(m_skeleton);
		}
		
		Play(0);
	}
	/*!
	 * @brief	���[�J���|�[�Y�̍X�V�B
	 */
	void CAnimation::UpdateLocalPose(float deltaTime)
	{
		m_interpolateTime += deltaTime;
		if (m_interpolateTime >= 1.0f) {
			//��Ԋ����B
			//���݂̍ŏI�A�j���[�V�����R���g���[���ւ̃C���f�b�N�X���J�n�C���f�b�N�X�ɂȂ�B
			m_startAnimationPlayController = GetLastAnimationControllerIndex();
			m_numAnimationPlayController = 1;
			m_interpolateTime = 1.0f;
		}
		for (int i = 0; i < m_numAnimationPlayController-1; i++) {
			int index = GetAnimationControllerIndex(m_startAnimationPlayController, i );
			m_animationPlayController[index].Update(deltaTime);
		}
		//�Ō�̃|�[�Y�����i�߂Ă����B
		int lastIndex = GetLastAnimationControllerIndex();
		m_animationPlayController[lastIndex].Update(deltaTime);
		
	}
	/*!
	 * @brief	�O���[�o���|�[�Y�̍X�V�B
	 */
	void CAnimation::UpdateGlobalPose()
	{
		//�O���[�o���|�[�Y�v�Z�p�̃��������X�^�b�N����m�ہB
		int numBone = m_skeleton->GetNumBones();
		CMatrix* globalPose = (CMatrix*)alloca(sizeof(CMatrix) * numBone);
		for (int i = 0; i < numBone; i++) {
			globalPose[i] = CMatrix::Identity;
		}
		//�O���[�o���|�[�Y���v�Z���Ă����B
		int startIndex = m_startAnimationPlayController;
		for (int i = 0; i < m_numAnimationPlayController; i++) {
			int index = GetAnimationControllerIndex(startIndex, i);
			float intepolateRate = m_animationPlayController[index].GetInterpolateRate();
			const auto& localBoneMatrix = m_animationPlayController[index].GetBoneLocalMatrix();
			for (int boneNo = 0; boneNo < numBone; boneNo++) {
				for (int x = 0; x < 4; x++) {
					for (int y = 0; y < 4; y++) {
						globalPose[boneNo].m[x][y] = 
							globalPose[boneNo].m[x][y] * (1.0f - intepolateRate) 
							+ localBoneMatrix[boneNo].m[x][y] * intepolateRate;
					}
				}
				
			}
		}
		//�O���[�o���|�[�Y���X�P���g���ɔ��f�����Ă����B
		for (int boneNo = 0; boneNo < numBone; boneNo++) {
			m_skeleton->SetBoneLocalMatrix(
				boneNo,
				globalPose[boneNo]
			);
		}
		
		//�ŏI�A�j���[�V�����ȊO�͕�Ԋ������Ă����珜�����Ă����B
		int numAnimationPlayController = m_numAnimationPlayController;
		for (int i = 1; i < m_numAnimationPlayController; i++) {
			int index = GetAnimationControllerIndex(startIndex, i);
			if (m_animationPlayController[index].GetInterpolateRate() > 0.99999f) {
				//��Ԃ��I����Ă���̂ŃA�j���[�V�����̊J�n�ʒu��O�ɂ���B
				m_startAnimationPlayController = index;
				numAnimationPlayController = m_numAnimationPlayController - i;
			}
		}
		m_numAnimationPlayController = numAnimationPlayController;
	}
	/*!
	* @brief	�A�j���[�V������i�߂�B
	*@param[in]	deltaTime		�A�j���[�V������i�߂鎞��(�P�ʁF�b)�B
	*/
	void CAnimation::Update(float deltaTime)
	{
		if (m_numAnimationPlayController == 0) {
			return;
		}
		//���[�J���|�[�Y�̍X�V������Ă����B
		UpdateLocalPose(deltaTime);
		
		//�O���[�o���|�[�Y���v�Z���Ă����B
		UpdateGlobalPose();
	}
}