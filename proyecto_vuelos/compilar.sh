#!/bin/bash

echo "========================================="
echo "  COMPILANDO SISTEMA DE VUELOS"
echo "========================================="
echo ""

# Verificar que existen los archivos fuente
if [ ! -f "src/main.c" ]; then
    echo "ERROR: No se encuentra src/main.c"
    echo "Asegúrese de ejecutar este script desde la raíz del proyecto"
    exit 1
fi

# Crear directorio bin si no existe
mkdir -p bin

# Compilar
echo "Compilando archivos..."
gcc -Wall -Wextra -o bin/programa src/main.c src/vuelos.c src/pasajeros.c

# Verificar resultado
if [ $? -eq 0 ]; then
    echo ""
    echo "========================================="
    echo "  ✓ COMPILACIÓN EXITOSA"
    echo "========================================="
    echo ""
    echo "Ejecutable creado en: bin/programa"
    echo ""
    echo "Para ejecutar:"
    echo "  ./bin/programa"
    echo ""
    
    # Dar permisos de ejecución
    chmod +x bin/programa
else
    echo ""
    echo "========================================="
    echo "  ✗ ERROR EN COMPILACIÓN"
    echo "========================================="
    echo ""
    echo "Revise los errores mostrados arriba"
    echo ""
    exit 1
fi