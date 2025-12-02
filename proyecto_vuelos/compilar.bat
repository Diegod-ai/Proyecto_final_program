@echo off
chcp 65001 >nul
echo =========================================
echo   COMPILANDO SISTEMA DE VUELOS
echo =========================================
echo.

REM Verificar que existen los archivos fuente
if not exist "src\main.c" (
    echo ERROR: No se encuentra src\main.c
    echo Asegurese de ejecutar este script desde la raiz del proyecto
    pause
    exit /b 1
)

REM Crear directorio bin si no existe
if not exist bin mkdir bin

REM Compilar
echo Compilando archivos...
gcc -Wall -Wextra -o bin\programa.exe src\main.c src\vuelos.c src\pasajeros.c

REM Verificar resultado
if %ERRORLEVEL% EQU 0 (
    echo.
    echo =========================================
    echo   [OK] COMPILACION EXITOSA
    echo =========================================
    echo.
    echo Ejecutable creado en: bin\programa.exe
    echo.
    echo Para ejecutar:
    echo   bin\programa.exe
    echo.
    echo O hacer doble clic en: bin\programa.exe
    echo.
) else (
    echo.
    echo =========================================
    echo   [ERROR] FALLO EN COMPILACION
    echo =========================================
    echo.
    echo Revise los errores mostrados arriba
    echo.
)

pause