rem Visual studio�̃r���h�̃|�X�g�r���h�X�e�b�v�̃o�b�`�t�@�C���B
pushd ..\\Game\\
rem dds�t�@�C����Resource�̉��ɃR�s�[�B
xcopy /Y /D *.dds .\Resource\*

rem Assets�t�H���_����Resource�t�H���_�ɂ������ƃR�s�[�B
rem �摜�t�@�C����fbx�̓R�s�[����Ȃ���I�I�I
xcopy /Y /D /I /S .\Assets .\Resource /EXCLUDE:..\tkTools\exlcude.txt
popd
