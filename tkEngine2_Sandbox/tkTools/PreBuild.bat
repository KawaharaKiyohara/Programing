rem Visual studio�̃r���h�̃v���r���h�X�e�b�v�̃o�b�`�t�@�C���B
pushd ..\\Game\\Resource\\
rem dds�t�@�C����Resource�̉��ɃR�s�[�B

mkDir .\\modelData > NUL 2>&1
if errorlevel 1 goto NEXT1
:NEXT1

mkDir .\\sprite > NUL 2>&1
if errorlevel 1 goto NEXT2
:NEXT2
popd
exit 0
