!include MUI2.nsh

!define MUI_ICON "bitmaps\gagarin.ico"
!define MUI_HEADERIMAGE
!define MUI_HEADERIMAGE_BITMAP_NOSTRETCH
!define MUI_HEADERIMAGE_BITMAP "bitmaps\gagarin.bmp"
!define MUI_HEADERIMAGE_RIGHT

Unicode true

!define VERSION "1.2.1s"
!define APP_NAME "MultiRobotGAGARIN"
!define INST_FEATURES "brl"
BrandingText "${APP_NAME} Installer"
Name "${APP_NAME} v${VERSION}"
OutFile "${APP_NAME}v${VERSION}_${INST_FEATURES}.exe"
InstallDir "$PROGRAMFILES\${APP_NAME}"
!define ROBOT_FILE "MultiRobotGAGARIN_v1.2.1.s.ex4"
!define LENTA_FILE "MultiLentaGAGARIN_v1.2.ex4"
  
InstallDirRegKey HKCU "Software\${APP_NAME}" ""

RequestExecutionLevel admin

#Var StartMenuFolder

!insertmacro MUI_LANGUAGE "Russian"
!insertmacro MUI_PAGE_COMPONENTS
!insertmacro MUI_PAGE_DIRECTORY

!define MUI_STARTMENUPAGE_REGISTRY_ROOT "HKCU" 
!define MUI_STARTMENUPAGE_REGISTRY_KEY "Software\${APP_NAME}" 
!define MUI_STARTMENUPAGE_REGISTRY_VALUENAME "${APP_NAME}"
#!insertmacro MUI_PAGE_STARTMENU "Application" $StartMenuFolder
  
!insertmacro MUI_PAGE_INSTFILES


Section "Ribbon" Ribbon
  SetOutPath $INSTDIR
  CreateDirectory $INSTDIR\iconengines
  CreateDirectory $INSTDIR\bearer
  CreateDirectory $INSTDIR\translations
  CreateDirectory $INSTDIR\platforms
  CreateDirectory $INSTDIR\imageformats

  File /oname=iconengines\qsvgicon.dll "ribbon\iconengines\qsvgicon.dll"
  File /oname=bearer\qnativewifibearer.dll "ribbon\bearer\qnativewifibearer.dll"
  File /oname=bearer\qgenericbearer.dll "ribbon\bearer\qgenericbearer.dll"
  File "ribbon\Qt5Network.dll"
  File /oname=translations\qt_ru.qm "ribbon\translations\qt_ru.qm"
  File "ribbon\Qt5WebSockets.dll"
  File /oname=platforms\qwindows.dll "ribbon\platforms\qwindows.dll" 
  File "ribbon\settings.ini"
  File "ribbon\Qt5Widgets.dll"
  File /oname=imageformats\qwbmp.dll "ribbon\imageformats\qwbmp.dll" 
  File /oname=imageformats\qicns.dll "ribbon\imageformats\qicns.dll"
  File /oname=imageformats\qjpeg.dll "ribbon\imageformats\qjpeg.dll"
  File /oname=imageformats\qdds.dll "ribbon\imageformats\qdds.dll"
  File /oname=imageformats\qsvg.dll "ribbon\imageformats\qsvg.dll"
  File /oname=imageformats\qico.dll "ribbon\imageformats\qico.dll"
  File /oname=imageformats\qgif.dll "ribbon\imageformats\qgif.dll"
  File /oname=imageformats\qtiff.dll "ribbon\imageformats\qtiff.dll"
  File /oname=imageformats\qwebp.dll "ribbon\imageformats\qwebp.dll"
  File /oname=imageformats\qtga.dll "ribbon\imageformats\qtga.dll"
  File "ribbon\vcredist_x86.exe"
  File "ribbon\Qt5Svg.dll"
  File "ribbon\D3Dcompiler_47.dll"
  File "ribbon\Qt5Core.dll"
  File "ribbon\libEGL.dll"
  File "ribbon\Qt5Gui.dll"
  File "ribbon\opengl32sw.dll"
  File "ribbon\libGLESV2.dll"
  File "ribbon\rz_ribbon.exe"
  File "bitmaps\gagarin.ico"

  CreateShortcut "$DESKTOP\${APP_NAME}.lnk" "$INSTDIR\rz_ribbon.exe" "" "$INSTDIR\gagarin.ico"
  WriteUninstaller "$INSTDIR\Uninstall.exe"
  ExecWait '"$INSTDIR\vcredist_x86.exe" /quiet'

  CreateDirectory "$SMPROGRAMS\${APP_NAME}"
  CreateShortcut "$SMPROGRAMS\${APP_NAME}\${APP_NAME}.lnk" "$INSTDIR\rz_ribbon.exe" "" "$INSTDIR\gagarin.ico"
  CreateShortcut "$SMPROGRAMS\${APP_NAME}\Uninstall.lnk" "$INSTDIR\Uninstall.exe" "" "$INSTDIR\gagarin.ico"
SectionEnd

Section "MT4 Robot" Robot
  SetOutPath $INSTDIR
  File "robot\${ROBOT_FILE}"
  File "robot\${LENTA_FILE}"
  File seed_ex4.bat
  ClearErrors
  ExecWait "$INSTDIR\seed_ex4.bat"
#  ExecWait `for /f "tokens=*" %%a in ('dir "%AppData%\MetaQuotes\Terminal" /ad/b') do xcopy "$INSTDIR\${ROBOT_FILE}" /y "%AppData%\MetaQuotes\Terminal\%%a\MQL4\Experts\"`
  IfErrors 0 noError
   MessageBox MB_OK "Error occured during seeding the robot"
noError:
SectionEnd

Section "Uninstall"
  Delete "$INSTDIR\Uninstall.exe"
  Delete "$INSTDIR\iconengines\qsvgicon.dll"
  Delete "$INSTDIR\bearer\qnativewifibearer.dll"
  Delete "$INSTDIR\bearer\qgenericbearer.dll"
  Delete "$INSTDIR\Qt5Network.dll"
  Delete "$INSTDIR\translations\qt_ru.qm"
  Delete "$INSTDIR\Qt5WebSockets.dll"
  Delete "$INSTDIR\platforms\qwindows.dll"
  Delete "$INSTDIR\settings.ini"
  Delete "$INSTDIR\Qt5Widgets.dll"
  Delete "$INSTDIR\imageformats\qwbmp.dll"
  Delete "$INSTDIR\imageformats\qicns.dll"
  Delete "$INSTDIR\imageformats\qjpeg.dll"
  Delete "$INSTDIR\imageformats\qdds.dll"
  Delete "$INSTDIR\imageformats\qsvg.dll"
  Delete "$INSTDIR\imageformats\qico.dll"
  Delete "$INSTDIR\imageformats\qgif.dll"
  Delete "$INSTDIR\imageformats\qtiff.dll"
  Delete "$INSTDIR\imageformats\qwebp.dll"
  Delete "$INSTDIR\imageformats\qtga.dll"
  Delete "$INSTDIR\vcredist_x86.exe"
  Delete "$INSTDIR\Qt5Svg.dll"
  Delete "$INSTDIR\D3Dcompiler_47.dll"
  Delete "$INSTDIR\Qt5Core.dll"
  Delete "$INSTDIR\libEGL.dll"
  Delete "$INSTDIR\Qt5Gui.dll"
  Delete "$INSTDIR\opengl32sw.dll"
  Delete "$INSTDIR\libGLESV2.dll"
  Delete "$INSTDIR\rz_ribbon.exe"
  Delete "$INSTDIR\${ROBOT_FILE}"
  Delete "$INSTDIR\${LENTA_FILE}"
  Delete "$INSTDIR\seed_ex4.bat"
  Delete "$INSTDIR\gagarin.ico"
  Delete "$DESKTOP\${APP_NAME}.lnk"

  RMDir "$INSTDIR\iconengines"
  RMDir "$INSTDIR\bearer"
  RMDir "$INSTDIR\translations"
  RMDir "$INSTDIR\platforms"
  RMDir "$INSTDIR\imageformats"
  RMDir "$INSTDIR"

  Delete "$SMPROGRAMS\${APP_NAME}\Uninstall.lnk"
  Delete "$SMPROGRAMS\${APP_NAME}\${APP_NAME}.lnk"
  RMDir "$SMPROGRAMS\${APP_NAME}"
  
  DeleteRegKey /ifempty HKCU "Software\${APP_NAME}"
SectionEnd