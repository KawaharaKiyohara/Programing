/*!
 *@brief	�V�F�[�_�[�̃`���[�g���A��00
 */
#include <d3d9.h>
#include <d3dx9effect.h>
#pragma warning( disable : 4996 ) 
#include <strsafe.h>
#pragma warning( default : 4996 )
#include <cstdlib>


LPD3DXFONT	pFont;	// �t�H���g�I�u�W�F�N�g

class CStopwatch {
public:
	/*!
	*@brief	�R���X�g���N�^�B
	*/
	CStopwatch()
	{
		freq = 0;
		end = 0;
		begin = 0;
		elapsed = 0.0;
		elapsedMill = 0.0;
		elapsedMicro = 0.0;
	}
	/*!
	*@brief	�f�X�g���N�^�B
	*/
	~CStopwatch()
	{
	}
	/*!
	*@brief	�v���J�n�B
	*/
	void Start()
	{
		::QueryPerformanceCounter((LARGE_INTEGER*)&begin);
	}
	/*!
	*@brief	�v���I��
	*/
	void Stop()
	{
		::QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
		::QueryPerformanceCounter((LARGE_INTEGER*)&end);
		elapsed = double(end - begin) / freq;
		elapsedMill = elapsedMicro * 1000.0;
		elapsedMicro = elapsedMill * 1000.0;
	}
	/*!
	*@brief	�o�ߎ��Ԃ��擾(�P��:�b)
	*/
	double GetElapsed() const
	{
		return elapsed;
	}
	/*!
	*@brief	�o�ߎ��Ԃ��擾(�P��:�~���b)
	*/
	double GetElapsedMillisecond() const
	{
		return elapsedMill;
	}
	/*!
	*@brief	�o�ߎ��Ԃ��擾(�P��:�}�C�N���b)
	*/
	double GetElapsedMicrosecond() const
	{
		return elapsedMicro;
	}
private:
	LONGLONG freq;
	LONGLONG end;
	LONGLONG begin;
	double elapsed;			//�o�ߎ���(�P�ʁF�b)
	double elapsedMill;		//�o�ߎ���(�P�ʁF�~���b)
	double elapsedMicro;	//�o�ߎ���(�P�ʁF�}�C�N���b)

};
//-----------------------------------------------------------------------------
// �O���[�o���ϐ��B
//-----------------------------------------------------------------------------
LPDIRECT3D9             g_pD3D = NULL;		
LPDIRECT3DDEVICE9       g_pd3dDevice = NULL;
ID3DXEffect*			g_pEffect = NULL;	

D3DXMATRIX				g_viewMatrix;		//�r���[�s��B�J�����s��Ƃ������B
D3DXMATRIX				g_projectionMatrix;	//�v���W�F�N�V�����s��B�r���[��Ԃ���ˉe��Ԃɕϊ�����s��B
D3DXMATRIX				g_worldMatrix;		//���[���h�s��B���f�����[�J����Ԃ���A���[���h��Ԃɕϊ�����s��B
D3DXMATRIX				g_rotationMatrix;	//��]�s��B�@�����񂷂��߂ɕK�v�Ȃ̂ŕʓr�p�ӁB

LPD3DXMESH				g_pMesh = NULL;
LPDIRECT3DTEXTURE9*	 	g_pMeshTextures = NULL; 	// Textures for our mesh
DWORD              	 	g_dwNumMaterials = 0L;   	// Number of mesh materials


static const int		LIGHT_NUM = 4;
D3DXVECTOR4 			g_diffuseLightDirection[LIGHT_NUM];	//���C�g�̕����B
D3DXVECTOR4				g_diffuseLightColor[LIGHT_NUM];		//���C�g�̐F�B
D3DXVECTOR4				g_ambientLight;						//����
//��������C���X�^���V���O�`��Ŏg���O���[�o���ϐ��B
IDirect3DVertexBuffer9* worldMatrixBuffer = NULL;			//���[���h�s��̃o�b�t�@�B
IDirect3DVertexDeclaration9* vertexDecl = NULL;			//���_��`�B
static const int NUM_TIGER = 5000;
D3DXMATRIX worldMatrix[NUM_TIGER];
/*!
 *@brief	�V�F�[�_�[�G�t�F�N�g�t�@�C��(*.fx)�����[�h�B
 */
void LoadEffectFile()
{
	LPD3DXBUFFER  compileErrorBuffer = NULL;
	//�V�F�[�_�[���R���p�C���B
	HRESULT hr = D3DXCreateEffectFromFile(
		g_pd3dDevice,
		"basic.fx",
		NULL,
		NULL,
#ifdef _DEBUG
		D3DXSHADER_DEBUG,
#else
		D3DXSHADER_SKIPVALIDATION,
#endif
		NULL,
		&g_pEffect,
		&compileErrorBuffer
		);
	if (FAILED(hr)) {
		MessageBox(NULL, (char*)(compileErrorBuffer->GetBufferPointer()), "error", MB_OK);
		std::abort();
	}
}
//-----------------------------------------------------------------------------
// Name: InitD3D()
// Desc: Initializes Direct3D
//-----------------------------------------------------------------------------
HRESULT InitD3D(HWND hWnd)
{
	// Create the D3D object.
	if (NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
		return E_FAIL;

	// Set up the structure used to create the D3DDevice
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	// Create the D3DDevice
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &g_pd3dDevice)))
	{
		return E_FAIL;
	}

	// Device state would normally be set here
	//�V�F�[�_�[�G�t�F�N�g�t�@�C���̃��[�h�B
	LoadEffectFile();

	D3DXCreateFont(
		g_pd3dDevice,				// Direct3D�f�o�C�X
		24,						// ����
		10,						// ��
		FW_REGULAR,				// �t�H���g�̑��� ����
		NULL,					// ����
		FALSE,					// �Α�
		SHIFTJIS_CHARSET,		// �����Z�b�g
		OUT_DEFAULT_PRECIS,		// �o�͐��x�͕���
		PROOF_QUALITY,			// �����i�����d��
		FIXED_PITCH | FF_SCRIPT,	// �s�b�`�ƃt�@�~��
		TEXT("�l�r�@�o�S�V�b�N"),	// �t�H���g��
		&pFont);					// ID3DXFont�|�C���^


	return S_OK;
}

/*!
 *@brief	�v���W�F�N�V�����s��̏������B
 */
void InitProjectionMatrix()
{
	for (int i = 0; i < NUM_TIGER; i++) {
		D3DXMatrixIdentity(&worldMatrix[i]);
		worldMatrix[i].m[3][0] = ((i % 30) - 15) * 1.0f;
		worldMatrix[i].m[3][1] = (i / 30) * 1.0f;
	}

	D3DXMatrixIdentity( &g_rotationMatrix );
	
	D3DXVECTOR3 vEyePt( 0.0f, 0.0f,-10.0f );
    D3DXVECTOR3 vLookatPt( 0.0f,0.0f, 0.0f );
    D3DXVECTOR3 vUpVec( 0.0f, 1.0f, 0.0f );
    D3DXMATRIXA16 matView;
    D3DXMatrixLookAtLH( &g_viewMatrix, &vEyePt, &vLookatPt, &vUpVec );
    
    D3DXMATRIXA16 matProj;
    D3DXMatrixPerspectiveFovLH( &g_projectionMatrix, D3DX_PI / 4, 1.0f, 1.0f, 100.0f );
}


//-----------------------------------------------------------------------------
// Name: Cleanup()
// Desc: Releases all previously initialized objects
//-----------------------------------------------------------------------------
VOID Cleanup()
{
	if (g_pMeshTextures != NULL) {
		for (int i = 0; i < g_dwNumMaterials; i++) {
			g_pMeshTextures[i]->Release();
		}
		delete[] g_pMeshTextures;
	}
	if (vertexDecl != NULL) {
		vertexDecl->Release();
	}
	if (worldMatrixBuffer != NULL) {
		worldMatrixBuffer->Release();
	}
	if (g_pMesh != NULL) {
		g_pMesh->Release();
	}
	if (g_pEffect != NULL) {
		g_pEffect->Release();
	}
	if (g_pd3dDevice != NULL)
		g_pd3dDevice->Release();

	if (g_pD3D != NULL)
		g_pD3D->Release();
}
/*!
 *@brief	���C�g���X�V�B
 */
void UpdateLight()
{
	g_diffuseLightDirection[0] = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
	
	//�f�B�t���[�Y���C�g�B
	g_diffuseLightColor[0] = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);

	//�����B
	g_ambientLight = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
}
/*!
*@brief	���[���h�s��𒸓_�o�b�t�@�ɃR�s�[�B
*/
void CopyWorldMatrixToVertexBuffer()
{
	D3DVERTEXBUFFER_DESC desc;
	worldMatrixBuffer->GetDesc(&desc);
	D3DXMATRIX* pData;
	worldMatrixBuffer->Lock(0, desc.Size, (void**)&pData, D3DLOCK_DISCARD);
	
	for (int i = 0; i < NUM_TIGER; i++) {
		
		*pData = worldMatrix[i];
		pData++;
	}
	worldMatrixBuffer->Unlock();
}
//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Draws the scene
//-----------------------------------------------------------------------------
VOID Render()
{
	CStopwatch sw;
	sw.Start();
	// Clear the backbuffer to a blue color
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	
	static int renderCount = 0;
	static bool isInstancing = true;
	if (SUCCEEDED(g_pd3dDevice->BeginScene()))
	{
		renderCount++;
		//���[���h�s����X�V�B
		static int renderCount = 0;
		renderCount++;
		D3DXMATRIXA16 rot;
		D3DXMatrixRotationY(&rot, renderCount / 50.0f);
		for (int i = 0; i < NUM_TIGER; i++) {
			//��]�������R�s�[�B
			memcpy(worldMatrix[i].m, rot.m, sizeof(float) * 12);
		}
		//���C�g���X�V
		UpdateLight();
		// Turn on the zbuffer
		g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
		
		//�V�F�[�_�[�K�p�J�n�B
		if (isInstancing) {
			g_pEffect->SetTechnique("SkinModelInstancing");
		}
		else {
			g_pEffect->SetTechnique("SkinModel");
		}
		g_pEffect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
		g_pEffect->BeginPass(0);

		//�萔���W�X�^�ɐݒ肷��J���[�B
		D3DXVECTOR4 color( 1.0f, 0.0f, 0.0f, 1.0f);
		
		//�r���[�s��̓]���B
		g_pEffect->SetMatrix("g_viewMatrix", &g_viewMatrix);
		//�v���W�F�N�V�����s��̓]���B
		g_pEffect->SetMatrix("g_projectionMatrix", &g_projectionMatrix);
		//��]�s���]���B
		g_pEffect->SetMatrix( "g_rotationMatrix", &g_rotationMatrix );
		//���C�g�̌�����]���B
		g_pEffect->SetVectorArray("g_diffuseLightDirection", g_diffuseLightDirection, LIGHT_NUM );
		//���C�g�̃J���[��]���B
		g_pEffect->SetVectorArray("g_diffuseLightColor", g_diffuseLightColor, LIGHT_NUM );
		//������ݒ�B
		g_pEffect->SetVector("g_ambientLight", &g_ambientLight);

		
		
		if (isInstancing) {
			
			g_pEffect->SetTexture("g_diffuseTexture", g_pMeshTextures[0]);

			//DrawSubset���g�p����ƃC���X�^���V���O�`�悪�s���Ȃ��̂�
			//g_pMesh���璸�_�o�b�t�@�A�C���f�b�N�X�o�b�t�@�����������Ă��āA���ڕ`�悷��B
			LPDIRECT3DVERTEXBUFFER9 vb;
			LPDIRECT3DINDEXBUFFER9 ib;
			g_pMesh->GetVertexBuffer(&vb);
			g_pMesh->GetIndexBuffer(&ib);
			
			DWORD fvf = g_pMesh->GetFVF();
			DWORD stride = D3DXGetFVFVertexSize(fvf);
			
			g_pd3dDevice->SetStreamSourceFreq(0, D3DSTREAMSOURCE_INDEXEDDATA | NUM_TIGER);
			g_pd3dDevice->SetStreamSourceFreq(1, D3DSTREAMSOURCE_INSTANCEDATA | 1);

			g_pd3dDevice->SetVertexDeclaration(vertexDecl);
			
			g_pd3dDevice->SetStreamSource(0, vb, 0, stride);							//���_�o�b�t�@���X�g���[��0�Ԗڂɐݒ�
			g_pd3dDevice->SetStreamSource(1, worldMatrixBuffer, 0, sizeof(D3DXMATRIX));	//���[���h�s��p�̃o�b�t�@���X�g���[��1�Ԗڂɐݒ�B
			//���[���h�s��𒸓_�o�b�t�@�ɃR�s�[�B
			CopyWorldMatrixToVertexBuffer();
			g_pd3dDevice->SetIndices(ib);
			g_pEffect->CommitChanges();						//���̊֐����Ăяo�����ƂŁA�f�[�^�̓]�����m�肷��B�`����s���O�Ɉ�񂾂��Ăяo���B
			g_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, g_pMesh->GetNumVertices(), 0, g_pMesh->GetNumFaces());
			vb->Release();
			ib->Release();
		}
		else {
			//�C���X�^���V���O����Ȃ��B
			//���[���h�s��̓]���B
			for (int i = 0; i < NUM_TIGER; i++) {
				g_pEffect->SetMatrix("g_worldMatrix", &worldMatrix[i]);
				// Meshes are divided into subsets, one for each material. Render them in
				// a loop
				for (DWORD matNo = 0; matNo < g_dwNumMaterials; matNo++)
				{
					g_pEffect->SetTexture("g_diffuseTexture", g_pMeshTextures[matNo]);
					g_pEffect->CommitChanges();						//���̊֐����Ăяo�����ƂŁA�f�[�^�̓]�����m�肷��B�`����s���O�Ɉ�񂾂��Ăяo���B
					// Draw the mesh subset
					g_pMesh->DrawSubset(matNo);
				}
			}
		}
        
		g_pEffect->EndPass();
		g_pEffect->End();
	
		// End the scene
		g_pd3dDevice->EndScene();
	}
	sw.Stop();
	char text[256];
	sprintf(text, "fps = %lf\n", 1.0f / sw.GetElapsed());
	
	RECT rc = {
		0,		// �����x���W
		0,		// �����y���W
		640,	// �E����x���W
		24		// �E����y���W
	};
	// �`��
	pFont->DrawText(
		NULL,							// NULL
		text,							// �`��e�L�X�g
		-1,								// �S�ĕ\��
		&rc,							// �\���͈�
		DT_LEFT,						// ����
		D3DCOLOR_XRGB(255, 255, 255)	// ���F
		);

	// Present the backbuffer contents to the display
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}




//-----------------------------------------------------------------------------
// Name: MsgProc()
// Desc: The window's message handler
//-----------------------------------------------------------------------------
LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		Cleanup();
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

/*!
 *@brief	X�t�@�C����ǂݍ���ŃW�I���g�����������B
 */
HRESULT InitGeometry()
{
    LPD3DXBUFFER pD3DXMtrlBuffer;

    // Load the mesh from the specified file
    if( FAILED( D3DXLoadMeshFromX( "Tiger.x", D3DXMESH_SYSTEMMEM,
                                   g_pd3dDevice, NULL,
                                   &pD3DXMtrlBuffer, NULL, &g_dwNumMaterials,
                                   &g_pMesh ) ) )
    {
        // If model is not in current folder, try parent folder
        if( FAILED( D3DXLoadMeshFromX( "..\\Tiger.x", D3DXMESH_SYSTEMMEM,
                                       g_pd3dDevice, NULL,
                                       &pD3DXMtrlBuffer, NULL, &g_dwNumMaterials,
                                       &g_pMesh ) ) )
        {
            MessageBox( NULL, "Could not find tiger.x", "Meshes.exe", MB_OK );
            return E_FAIL;
        }
    }
	//�@�������݂��邩���ׂ�B
	if ((g_pMesh->GetFVF() & D3DFVF_NORMAL) == 0) {
		//�@�����Ȃ��̂ō쐬����B
		ID3DXMesh* pTempMesh = NULL;

		g_pMesh->CloneMeshFVF(g_pMesh->GetOptions(),
			g_pMesh->GetFVF() | D3DFVF_NORMAL, g_pd3dDevice, &pTempMesh);

		D3DXComputeNormals(pTempMesh, NULL);
		g_pMesh->Release();
		g_pMesh = pTempMesh;

	}
	{
		//�C���X�^���V���O�`��p�̏������B
		D3DVERTEXELEMENT9 declElement[MAX_FVF_DECL_SIZE];
		g_pMesh->GetDeclaration(declElement);
		int elementIndex = 0;
		while (true) {
			if (declElement[elementIndex].Type == D3DDECLTYPE_UNUSED) {
				//�I�[�𔭌��B
				//��������C���X�^���V���O�p�̒��_���C�A�E�g�𖄂ߍ��ށB
				declElement[elementIndex]   = { 1,  0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 1 };  // WORLD 1�s��
				declElement[elementIndex+1] = { 1, 16, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 2 };  // WORLD 2�s��
				declElement[elementIndex+2] = { 1, 32, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 3 };  // WORLD 3�s��
				declElement[elementIndex+3] = { 1, 48, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 4 };  // WORLD 4�s��
				declElement[elementIndex+4] = D3DDECL_END();
				break;
			}
			elementIndex++;
		}
		//���_��`�̍쐬�B
		g_pd3dDevice->CreateVertexDeclaration(declElement, &vertexDecl);
		//���[���h�s��p�̃o�b�t�@�̍쐬�B
		g_pd3dDevice->CreateVertexBuffer(sizeof(D3DXMATRIX) * NUM_TIGER, 0, 0, D3DPOOL_MANAGED, &worldMatrixBuffer, 0);
	}
    // We need to extract the material properties and texture names from the 
    // pD3DXMtrlBuffer
    D3DXMATERIAL* d3dxMaterials = ( D3DXMATERIAL* )pD3DXMtrlBuffer->GetBufferPointer();
   
    g_pMeshTextures = new LPDIRECT3DTEXTURE9[g_dwNumMaterials];
    if( g_pMeshTextures == NULL )
        return E_OUTOFMEMORY;

    for( DWORD i = 0; i < g_dwNumMaterials; i++ )
    {
        g_pMeshTextures[i] = NULL;
        if( d3dxMaterials[i].pTextureFilename != NULL &&
            lstrlenA( d3dxMaterials[i].pTextureFilename ) > 0 )
        {
            // Create the texture
            if( FAILED( D3DXCreateTextureFromFileA( g_pd3dDevice,
                                                    d3dxMaterials[i].pTextureFilename,
                                                    &g_pMeshTextures[i] ) ) )
            {
                // If texture is not in current folder, try parent folder
                const CHAR* strPrefix = "..\\";
                CHAR strTexture[MAX_PATH];
                strcpy_s( strTexture, MAX_PATH, strPrefix );
                strcat_s( strTexture, MAX_PATH, d3dxMaterials[i].pTextureFilename );
                // If texture is not in current folder, try parent folder
                if( FAILED( D3DXCreateTextureFromFileA( g_pd3dDevice,
                                                        strTexture,
                                                        &g_pMeshTextures[i] ) ) )
                {
                    MessageBox( NULL, "Could not find texture map", "Meshes.exe", MB_OK );
                }
            }
        }
    }

    // Done with the material buffer
    pD3DXMtrlBuffer->Release();

    return S_OK;
}

//-----------------------------------------------------------------------------
// Name: wWinMain()
// Desc: The application's entry point
//-----------------------------------------------------------------------------
INT WINAPI wWinMain(HINSTANCE hInst, HINSTANCE, LPWSTR, INT)
{
	UNREFERENCED_PARAMETER(hInst);

	// Register the window class
	WNDCLASSEX wc =
	{
		sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
		"Shader Tutorial", NULL
	};
	RegisterClassEx(&wc);

	// Create the application's window
	HWND hWnd = CreateWindow("Shader Tutorial", "Shader Tutorial 00",
		WS_OVERLAPPEDWINDOW, 100, 100, 500, 500,
		NULL, NULL, wc.hInstance, NULL);

	// Initialize Direct3D
	if (SUCCEEDED(InitD3D(hWnd)))
	{
		// Create the vertex buffer
		if (SUCCEEDED(InitGeometry()))
		{
			ZeroMemory( g_diffuseLightDirection, sizeof(g_diffuseLightDirection) );
			ZeroMemory( g_diffuseLightColor, sizeof(g_diffuseLightColor) );
			
			InitProjectionMatrix();
			// Show the window
			ShowWindow(hWnd, SW_SHOWDEFAULT);
			UpdateWindow(hWnd);

			// Enter the message loop
			MSG msg;
			ZeroMemory(&msg, sizeof(msg));
			while (msg.message != WM_QUIT)
			{
				if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
				else
					Render();
			}
		}
	}

	UnregisterClass("Shader Tutorial", wc.hInstance);
	return 0;
}
