#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/tkSkinModel.h"
#include "tkEngine/graphics/tkSkinModelData.h"
#include "tkEngine/graphics/tkEffect.h"

namespace tkEngine{
	extern UINT                 g_NumBoneMatricesMax;
	extern D3DXMATRIXA16*       g_pBoneMatrices ;
	namespace {
		void DrawMeshContainer(
			IDirect3DDevice9* pd3dDevice, 
			LPD3DXMESHCONTAINER pMeshContainerBase, 
			LPD3DXFRAME pFrameBase,
			ID3DXEffect* pEffect,
			D3DXMATRIX* viewMatrix,
			D3DXMATRIX* projMatrix
		)
		{
			D3DXMESHCONTAINER_DERIVED* pMeshContainer = (D3DXMESHCONTAINER_DERIVED*)pMeshContainerBase;
			D3DXFRAME_DERIVED* pFrame = (D3DXFRAME_DERIVED*)pFrameBase;
			UINT iAttrib;
			LPD3DXBONECOMBINATION pBoneComb;

			D3DXMATRIXA16 matTemp;
			D3DCAPS9 d3dCaps;
			pd3dDevice->GetDeviceCaps(&d3dCaps);
			D3DXMATRIX viewProj;
			D3DXMatrixMultiply(&viewProj, viewMatrix, projMatrix);
			if (pMeshContainer->pSkinInfo != NULL)
			{
				//�X�L�����L��B
				//�X�L�����Ȃ��B
				pBoneComb = reinterpret_cast<LPD3DXBONECOMBINATION>(pMeshContainer->pBoneCombinationBuf->GetBufferPointer());
				for (iAttrib = 0; iAttrib < pMeshContainer->NumAttributeGroups; iAttrib++)
				{
					// first calculate all the world matrices
					for (DWORD iPaletteEntry = 0; iPaletteEntry < pMeshContainer->NumPaletteEntries; ++iPaletteEntry)
					{
						DWORD iMatrixIndex = pBoneComb[iAttrib].BoneId[iPaletteEntry];
						if (iMatrixIndex != UINT_MAX)
						{
							D3DXMatrixMultiply(
								&g_pBoneMatrices[iPaletteEntry],
								&pMeshContainer->pBoneOffsetMatrices[iMatrixIndex],
								pMeshContainer->ppBoneMatrixPtrs[iMatrixIndex]
							);
							//D3DXMatrixMultiply(&g_pBoneMatrices[iPaletteEntry], &matTemp, &g_matView);
						}
					}
					pEffect->SetMatrix("g_mViewProj", &viewProj);
					pEffect->SetMatrixArray("g_mWorldMatrixArray", g_pBoneMatrices, pMeshContainer->NumPaletteEntries);
					pEffect->SetFloat("g_numBone", pMeshContainer->NumInfl);
					// �f�B�t���[�Y�e�N�X�`���B
					pEffect->SetTexture("g_diffuseTexture", pMeshContainer->ppTextures[pBoneComb[iAttrib].AttribId]);

					// �{�[�����B
					pEffect->SetInt("CurNumBones", pMeshContainer->NumInfl - 1);

					pEffect->SetTechnique("DiffuseLight");
					pEffect->Begin(0, D3DXFX_DONOTSAVESTATE);
					pEffect->BeginPass(0);
					// draw the subset with the current world matrix palette and material state
					pMeshContainer->MeshData.pMesh->DrawSubset(iAttrib);
					pEffect->EndPass();
					pEffect->End();

				}
			}
			else {
				
			}
		}
		void DrawFrame(
			IDirect3DDevice9* pd3dDevice, 
			LPD3DXFRAME pFrame, 
			ID3DXEffect* pEffect, 
			D3DXMATRIX* viewMatrix, 
			D3DXMATRIX* projMatrix)
		{
			LPD3DXMESHCONTAINER pMeshContainer;

			pMeshContainer = pFrame->pMeshContainer;
			while (pMeshContainer != NULL)
			{
				DrawMeshContainer(
					pd3dDevice, 
					pMeshContainer, 
					pFrame, 
					pEffect,
					viewMatrix,
					projMatrix
					);

				pMeshContainer = pMeshContainer->pNextMeshContainer;
			}

			if (pFrame->pFrameSibling != NULL)
			{
				DrawFrame(
					pd3dDevice, 
					pFrame->pFrameSibling, 
					pEffect,
					viewMatrix,
					projMatrix
					);
			}

			if (pFrame->pFrameFirstChild != NULL)
			{
				DrawFrame(
					pd3dDevice, 
					pFrame->pFrameFirstChild, 
					pEffect,
					viewMatrix,
					projMatrix
					);
			}
		}
	}
	CSkinModel::CSkinModel() :
		m_skinModelData(nullptr)
	{
		m_pEffect = EffectManager().LoadEffect("Assets/presetShader/skinModel.fx");
	}
	CSkinModel::~CSkinModel()
	{

	}
	void CSkinModel::Draw(CRenderContext& renderContext, const CMatrix& viewMatrix, const CMatrix& projMatrix)
	{
		if (m_skinModelData) {
			//�e�X�g
			m_skinModelData->GetAnimationController()->AdvanceTime(1.0f / 60.0f, NULL);
			m_skinModelData->UpdateBoneMatrix(CMatrix::Identity);	//�{�[���s����X�V�B
			renderContext.DrawSkinModel(this, viewMatrix, projMatrix);
		}
	}
	void CSkinModel::ImmidiateDraw(LPDIRECT3DDEVICE9 pd3ddevice, D3DXMATRIX* viewMatrix, D3DXMATRIX* projMatrix)
	{
		if (m_skinModelData) {
			DrawFrame(
				pd3ddevice, 
				m_skinModelData->GetFrameRoot(), 
				m_pEffect->GetD3DXEffect(),
				viewMatrix,
				projMatrix
				);
		}
	}
}