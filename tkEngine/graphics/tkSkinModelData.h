/*!
 *@brief	�X�L�����f���f�[�^
 */
#ifndef _TKSKINMODELDATA_H_
#define _TKSKINMODELDATA_H_


namespace tkEngine{
	struct D3DXFRAME_DERIVED : public D3DXFRAME {
		D3DXMATRIX	CombinedTransformationMatrix;	//�����ςݍs��B
	};
	struct D3DXMESHCONTAINER_DERIVED : public D3DXMESHCONTAINER {
		LPDIRECT3DTEXTURE9* ppTextures;
		LPD3DXMESH pOrigMesh;
		LPD3DXATTRIBUTERANGE pAttributeTable;
		DWORD NumAttributeGroups;
		DWORD NumInfl;
		LPD3DXBUFFER pBoneCombinationBuf;
		D3DXMATRIX** ppBoneMatrixPtrs;
		D3DXMATRIX* pBoneOffsetMatrices;
		DWORD NumPaletteEntries;
		bool UseSoftwareVP;
		DWORD iAttributeSW;
	};
	class CAnimation;
	/*!
	 *@brief	�X�L�����f���f�[�^
	 */
	class CSkinModelData{
	public:
		/*!
		 *@brief	�R���X�g���N�^�B
		 */
		CSkinModelData();
		/*!
		 *@brief	�f�X�g���N�^�B
		 */
		~CSkinModelData();
		/*!
		 * @brief	���f���f�[�^�����[�h�B
		 *@param[in]	filePath	�t�@�C���p�X�B
		 *@param[out]	anim		�A�j���[�V�����t�����f���f�[�^�̏ꍇ�A�A�j���[�V�����N���X���\�z����܂��B
		 */
		void LoadModelData( const char* filePath, CAnimation* anim );
		/*!
		 * @brief	�C���X�^���V���O�`�悪�s����悤�ɐݒ�B
		 *@param[in]	numInstance			�C���X�^���X�̐��B
		 *@param[in]	vertexBufferStride	���_�o�b�t�@�̃X�g���C�h�B�C���X�^���X�`��Ŏg�p�����X�g���[���P�̒��_�o�b�t�@�̃X�g���C�h�ł��B
		 */
		void SetupInstancingDraw( int numInstance, int vertexBufferStride );
		/*!
		* @brief	���f���f�[�^�̃N���[�����쐬�B
		* @details
		*	�X�P���g���͐V�����쐬����A���b�V���f�[�^�͋��ʂ̂��̂��g�p����܂��B
		*@param[in]		modelData		���f���f�[�^�B
		*/
		void CloneModelData( const CSkinModelData& modelData, CAnimation* anim);
		/*!
		* @brief	�����[�X�B
		*/
		void Release();
		LPD3DXFRAME GetFrameRoot()
		{
			return m_frameRoot;
		}
		//�e�X�g�B
		void SetupOutputAnimationRegist(LPD3DXFRAME frame, ID3DXAnimationController* animCtr);
		/*!
		* @brief	�{�[���s����X�V�B
		*/
		void UpdateBoneMatrix( const CMatrix& matWorld );
	private:
		/*!
		* @brief	�X�P���g���̃N���[�����쐬�B
		*@param[out]	dstFrame		�N���[����̃X�P���g���̊i�[��B
		*@param[in]		srcFrame		�N���[�����̃X�P���g���B
		*/
		void CloneSkeleton(LPD3DXFRAME& dstFrame, LPD3DXFRAME srcFrame);
			/*!
			* @brief	�X�P���g���̃N���[�����폜�B
			*@param[in]	frame		�폜����X�P���g���B
			*/
			void DeleteCloneSkeleton(LPD3DXFRAME frame);
	private:
		LPD3DXFRAME					m_frameRoot;		//�t���[�����[�g�B
		ID3DXAnimationController*	m_animController;	//�A�j���[�V�����R���g���[���B
		bool						m_isClone;			//�N���[���H
	};
}

#endif //_TKSKINMODELDATA_H_
