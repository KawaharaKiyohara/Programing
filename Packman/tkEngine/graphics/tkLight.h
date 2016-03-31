/*!
 *@brief	���C�g
 */

#ifndef _TKLIGHT_H_
#define _TKLIGHT_H_

namespace tkEngine {
	/*!
	 *@brief	���C�g
	 */
	class CLight{
	public:
		static const u32 NUM_DIFFUSE_LIGHT = 4;
	public:
		CLight()
		{
			for( u32 i = 0; i < NUM_DIFFUSE_LIGHT; i++ ){
				m_diffuseLightDirection[i] = CVector3::AxisX;
				m_diffuseLightColor[i].Set( 0.0f, 0.0f, 0.0f, 0.0f );
			}
			m_ambientLight.Set( 0.1f, 0.1f, 0.1f );
		}
		/*!
		 *@brief	�f�B�t���[�Y���C�g�̌�����ݒ�B
		 *@param[in]	no				���C�g�̔ԍ��B
		 *@param[in]	lightDirection	���C�g�̕����B
		 */
		void SetDiffuseLightDirection( u32 no, const CVector3 lightDirection )
		{
			TK_ASSERT( no < NUM_DIFFUSE_LIGHT, "error");
			m_diffuseLightDirection[no] = lightDirection;
		}
		/*!
		 *@brief	�f�B�t���[�Y���C�g�̌������擾�B
		 *@param[in]	no		���C�g�̔ԍ��B
		 *@return	���C�g�̌����B
		 */
		const CVector3& GetDiffuseLightDirection( u32 no ) const
		{
			return m_diffuseLightDirection[no];
		}
		/*!
		 *@brief	�f�B�t���[�Y���C�g�̃J���[��ݒ�B
		 *@param[in]	no			���C�g�̔ԍ��B
		 *@param[in]	lightColor	���C�g�̃J���[�B
		 */
		void SetDiffuseLightColor( u32 no, const CVector4& lightColor )
		{
			TK_ASSERT( no < NUM_DIFFUSE_LIGHT, "error" );
			m_diffuseLightColor[no] = lightColor;
		}
		/*!
		 *@brief	�f�B�t���[�Y���C�g�̃J���[���擾�B
		 */
		const CVector4& GetDiffuseLightColor( u32 no ) const
		{
			TK_ASSERT( no < NUM_DIFFUSE_LIGHT, "error" );
			return m_diffuseLightColor[no];
		}
		/*!
		 *@brief	�������擾�B
		 */
		const CVector3& GetAmbientLight() const
		{
			return m_ambientLight;
		}
		/*!
		 *@brief	������ݒ�B
		 */
		void SetAmbinetLight( const CVector3& ambient )
		{
			m_ambientLight;
		}
	private:
		CVector3		m_diffuseLightDirection[NUM_DIFFUSE_LIGHT];		//!<�f�B�t���[�Y���C�g�̌����B
		CVector4		m_diffuseLightColor[NUM_DIFFUSE_LIGHT];			//!<�f�B�t���[�Y���C�g�̃J���[(x:R�����Ay:G�����Az:B�����Aw:�X�y�L�����̋���)�B
		CVector3		m_ambientLight;									//!<�A���r�G���g���C�g�B
	};
}
#endif // _TKLIGHT_H_