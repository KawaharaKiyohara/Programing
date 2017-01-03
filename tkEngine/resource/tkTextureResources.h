/*!
 *@brief	�e�N�X�`���̃��\�[�X�N���X�B
 */
#pragma once

namespace tkEngine{
	/*!
	 *@brief	���\�[�X�N���X�B
	 */
	class CTextureResources {
	private:
		CTextureResources();
		~CTextureResources();
	public:
		/*!
		 *@brief	�e�N�X�`�������[�h�B
		 *@param[in]	filePath		�t�@�C���p�X�B
		 */
		CTexture* Load( const char* filePath );
		/*!
		*@brief	����B
		*/
		void Release();
	private:
		friend class CEngine;
		std::map<int, CTexture*>	textureMap;
	};
}
