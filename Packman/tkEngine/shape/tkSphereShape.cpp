/*!
 *@brief	��
 */
#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/shape/tkSphereShape.h"
#include <vector>
namespace tkEngine {
	CSphereShape::CSphereShape()
	{
	}
	CSphereShape::~CSphereShape()
	{
	}
	void CSphereShape::Create(f32 radius, u32 grid, u32 color, bool hasNormal)
	{
		Release();
		m_isCreatePrimitive = true;
		//�C���f�b�N�X�o�b�t�@�̍쐬�B
		std::vector<u32>	indexBuffer;
		CreateIndexBuffer(indexBuffer, grid);
		if (hasNormal) {
			std::vector<SShapeVertex_PNC> vertexBuffer;
			CreateVertexPosition(vertexBuffer, radius, grid, color);
			//���_�}�[�W
			MergeVertex(vertexBuffer, indexBuffer, 0.1f );
			//�@�����v�Z�B
			u32 numPoly = indexBuffer.size() / 3;
			for (u32 i = 0; i < numPoly; i++) {
				u32 indexBase = i * 3;
				u32 vertNo_0 = indexBuffer.at(indexBase);
				u32 vertNo_1 = indexBuffer.at(indexBase+1);
				u32 vertNo_2 = indexBuffer.at(indexBase+2);
			}
		}
		else {
			//�|�W�V����+���W���_�o�b�t�@�̍쐬�B
			std::vector<SShapeVertex_PC> vertexBuffer;
			CreateVertexPosition(vertexBuffer, radius, grid, color);
			//���_�}�[�W
			MergeVertex(vertexBuffer, indexBuffer, 0.01f );
			
			//�v���~�e�B�u�̍쐬�B
			m_pPrimitive = new CPrimitive;
			m_pPrimitive->Create(
				CPrimitive::eTriangleList,
				vertexBuffer.size(),
				sizeof(SShapeVertex_PC),
				eVertexFormat_diffuse | eVertexFormat_xyzw,
				&vertexBuffer.at(0),
				indexBuffer.size(),
				eIndexFormat32,
				&indexBuffer.at(0)
			);
		}
	}
	void CSphereShape::CreateIndexBuffer(std::vector<u32>& indexBuffer, u32 grid)
	{
		//@todo �f�o�b�O�̂��߁B
		for (u32 i = 0; i < grid; i++) {
			u32 baseVertNo = (grid + 1) * i;
			u32 vertNo[3] = {
				baseVertNo ,
				baseVertNo + 1,
				baseVertNo + grid + 2
			};
			u32 vertNo2[3] = {
				baseVertNo + grid + 3,
				baseVertNo + grid + 2,
				baseVertNo + 2,
			};
			for (u32 k = 0; k < grid; k++) {
				if (k == 0) {
					indexBuffer.push_back(0);
					indexBuffer.push_back(vertNo[1]);
					indexBuffer.push_back(vertNo[2]);
					vertNo[0]++;
					vertNo[1]++;
				}
				else if (k == grid - 1) {
					/*indexBuffer.push_back(vertNo[1]);
					indexBuffer.push_back(vertNo[0]);
					indexBuffer.push_back(grid + 2);*/
					indexBuffer.push_back(vertNo[0]);
					indexBuffer.push_back(vertNo[1]);
					indexBuffer.push_back(vertNo[2]);
				}
				else if (k != 0) {
					indexBuffer.push_back(vertNo[0]++);
					indexBuffer.push_back(vertNo[1]++);
					indexBuffer.push_back(vertNo[2]++);

					indexBuffer.push_back(vertNo2[0]++);
					indexBuffer.push_back(vertNo2[1]++);
					indexBuffer.push_back(vertNo2[2]++);
				}

			}
		}
	}
	template<class TVertex>
	void CSphereShape::CreateVertexPosition(std::vector<TVertex>& vertexBuffer, f32 radius, u32 grid, u32 color)
	{
		u32 numVertex = (grid + 1)*(grid + 1);
		vertexBuffer.reserve(numVertex);
		//���̌`��̍쐬�B
		f32 deltaAngle = 2.0f * CMath::PI / grid;
		f32 deltaAngle2 = CMath::PI / grid;
		for (u32 i = 0; i < grid + 1; i++)
		{
			float y_angle = deltaAngle * i;
			for (u32 k = 0; k < grid + 1; k++)
			{
				CVector3 t(0.0f, 0.0f, 0.0f);
				//X������̉�]�B
				float z_angle = deltaAngle2 * k;
				t.y = sin(z_angle);
				t.z = cos(z_angle);
				//Z������̉�]�B
				t.x = t.y * -sin(y_angle);
				t.y = t.y * cos(y_angle);
				t.Scale(radius);
				TVertex vtx;
				vtx.pos[0] = t.x;
				vtx.pos[1] = t.y;
				vtx.pos[2] = t.z;
				vtx.pos[3] = 1.0f;
				vtx.color = color;
				vertexBuffer.push_back(vtx);
			}
		}
	}
}