/*!
 * @brief	�L�[���́B
 */

#ifndef _TKKEYINPUT_H_ 
#define _TKKEYINPUT_H_ 

namespace tkEngine{
	class CKeyInput{
		enum EnKey{
			enKeyUp,
			enKeyDown,
			enKeyRight,
			enKeyLeft,
			enKeyNum,
		};
	public:
		/*!
		 * @brief	�R���X�g���N�^�B
		 */
		CKeyInput();
		/*!
		 * @brief	�f�X�g���N�^�B
		 */
		~CKeyInput();
		/*!
		 * @brief	�L�[���̍X�V�B
		 */
		void Update();
		/*!
		 * @brief	��L�[��������Ă���B
		 */
		bool IsUpPress() const
		{
			return m_keyPressFlag[enKeyUp];
		}
		/*!
		 * @brief	�E�L�[��������Ă���B
		 */
		bool IsRightPress() const
		{
			return m_keyPressFlag[enKeyRight];
		}
		/*!
		 * @brief	���L�[��������Ă���B
		 */
		bool IsLeftPress() const
		{
			return m_keyPressFlag[enKeyLeft];
		}
		/*!
		 * @brief	���L�[��������Ă���B
		 */
		bool IsDownPress() const
		{
			return m_keyPressFlag[enKeyDown];
		}
	private:
		bool	m_keyPressFlag[enKeyNum];
	};
}
#endif //_TKKEYINPUT_H_ 