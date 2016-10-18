/*!
 * @brief	�����N���X�B
 */

#pragma once

#include "tkEngine/Sound/tkWaveFile.h"

namespace tkEngine{
	/*!
	 * @brief	�����N���X�B
	 */
	class CSoundSource : public IGameObject {
	public:
		/*!
		 * @brief	�R���X�g���N�^�B
		 */
		CSoundSource();
		/*!
		 * @brief	�f�X�g���N�^�B
		 */
		~CSoundSource();
		/*!
		 * @brief	�������B
		 *@details
		 * �����V���b�g�Đ������̏������B
		 *@param[in]	filePath	�t�@�C���p�X�B�Ή����Ă���t�@�C���t�H�[�}�b�g(*.wave)
		 */
		void Init( char* filePath );
		/*!
		* @brief	�������B
		*@details
		* �X�g���[�~���O�Đ������̏������B
		*@param[in]	filePath		�t�@�C���p�X�B�Ή����Ă���t�@�C���t�H�[�}�b�g(*.wave)
		*@param[in] ringBufferSize	�����O�o�b�t�@�̃T�C�Y�B
		*@param[in]	bufferSize		�X�g���[�~���O�̍ő�o�b�t�@�����O�T�C�Y�B
		*/
		void InitStreaming(char* filePath, unsigned int ringBufferSize = 3 * 1024 * 1024, unsigned int bufferingSize = 1024 * 512);
		/*!
		* @brief	�J���B
		*/
		void Release();
		/*!
		* @brief	�Đ��B
		*@param[in]	isLoop		���[�v�Đ��t���O�B
		*/
		void Play(bool isLoop);
		/*!
		* @brief	�X�V�B
		*@param[in]	isLoop		���[�v�Đ��t���O�B
		*/
		void Update() override;
		/*!
		* @brief	�{�����[����ݒ�B
		*@param[in]	vol		�{�����[���B
		*/
		void SetVolume(float vol)
		{
			m_sourceVoice->SetVolume(vol);
		}
	private:
		void UpdateStreaming();
		void Play(char* buff, unsigned int bufferSize);
		/*!
		* @brief	�X�g���[�~���O�o�b�t�@�����O�̊J�n�B
		*/
		void StartStreamingBuffring();
	private:
		enum EnStreamingStatus {
			enStreamingBuffering,	//�o�b�t�@�����O���B
			enStreamingQueueing,	//�L���[�C���O���B
		};
		CWaveFile				m_waveFile;					//!<�g�`�f�[�^�B
		std::unique_ptr<char[]>	m_buffer;					//!<�g�`�f�[�^��ǂݍ��ރo�b�t�@�B
		IXAudio2SourceVoice*	m_sourceVoice = nullptr;	//!<�\�[�X�{�C�X�B
		bool					m_isLoop = false;			//!<���[�v�t���O�B
		bool					m_isPlaying = false;		//!<�Đ����t���O�B
		bool					m_isStreaming = false;		//!<�X�g���[�~���O�Đ��H
		unsigned int			m_streamingBufferSize = 0;	//!<�X�g���[�~���O�p�̃o�b�t�@�����O�T�C�Y�B
		unsigned int			m_currentBufferingSize = 0;	//!<���݂̃o�b�t�@�����O�̃T�C�Y�B
		unsigned int			m_readStartPos = 0;			//!<�ǂݍ��݊J�n�ʒu�B
		unsigned int			m_ringBufferSize = 0;		//!<�����O�o�b�t�@�̃T�C�Y�B
		EnStreamingStatus		m_streamingState = enStreamingBuffering;	//!<�X�g���[�~���O�X�e�[�^�X�B
	};
}
