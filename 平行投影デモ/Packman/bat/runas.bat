@echo off
:RUNAS
whoami /PRIV | FIND "SeLoadDriverPrivilege" > NUL
IF not errorlevel 1 GOTO START
ECHO �����𑱍s����ɂ͊Ǘ��Ҍ������K�v�ł��B
ECHO �Ǘ��҃��[�h�ōċN�����܂�
START cmd.lnk /K "%0" %~d0 %~p0
exit
:START
CD /D %1\%2
