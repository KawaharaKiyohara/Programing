echo on
@rem �T���v���̊e�t�H���_��tkEngine�ւ̃V���{���b�N�����N���쐬����B
@set CURRENT_DIR=%~dp0

pushd %CURRENT_DIR%
@rem GameTemplate�ɃV���{���b�N�����N���쐬����B
mklink /D .\GameTemplate\tkEngine .\tkEngine
mklink /D .\GameTemplate\tkTools .\tkTools

@call .\Sample\setup.bat

@popd
@echo "�Z�b�g�A�b�v�I��"

@pause