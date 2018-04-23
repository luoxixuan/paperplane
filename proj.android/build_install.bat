rd /s/q C:\prj\PaperPlane\proj.android\bin
call cocos_compile.bat
cd C:\prj\PaperPlane\proj.android
call build_apk.bat
cd C:\prj\PaperPlane\proj.android\bin
rename PaperPlane-debug.apk PaperPlane.apk
cd ..
call install_apk.bat
pause