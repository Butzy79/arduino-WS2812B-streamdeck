@echo off
setlocal

echo ==========================================
echo Elgato Plugin
echo ==========================================

REM =====================================================
REM PROJECT ROOT PATHS
REM =====================================================

set "ROOT=C:\Users\livet\Documents\arduino-WS2812B-streamdeck"
set "ELGPLG=C:\Users\livet\AppData\Roaming\Elgato\StreamDeck\Plugins"

REM =====================================================
REM DEBUG (optional but useful)
REM =====================================================

echo ROOT = %ROOT%
echo ELGPLG = %ELGPLG%
echo.

REM =====================================================
REM COPY DDS FILES (INCLUDING SUBFOLDERS)
REM =====================================================

echo.
echo Copying Plugins files for...
del /F /Q "%ELGPLG%\com.butzy79.serial-usb-commander2.sdPlugin\*.*"
for /D %%D in ("%ELGPLG%\com.butzy79.serial-usb-commander2.sdPlugin\*") do rmdir /S /Q "%%D"

robocopy "%ROOT%\serial-usb-commander2\com.butzy79.serial-usb-commander2.sdPlugin" "%ELGPLG%\\com.butzy79.serial-usb-commander2.sdPlugin" *.* /S /COPY:DAT /R:1 /W:1

echo.

REM =====================================================
REM DONE
REM =====================================================

echo.
echo ==========================================
echo DEPLOY COMPLETED SUCCESSFULLY
echo ==========================================
