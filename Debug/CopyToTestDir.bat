rem "just copy files to test dir"
echo off
xcopy SoundSystem.dll "%1"
xcopy Logic.dll "%1"
xcopy PR_FLY.exe "%1"
pause;