#!/bin/bash

# Full script de pruebas automáticas para tu minishell
MINISHELL="./minishell"

# Limpiar ficheros generados
rm -f test.txt result.txt sorted.txt numbers.txt echo_test.txt

# Función para ejecutar un test
run_test() {
    local description="$1"
    local input="$2"
    local expected="$3"

    # Ejecutar la shell con input por here string para evitar problemas con heredoc
    output=$($MINISHELL <<< "$input" | sed '/^minishell\$ /d' | sed '/^$/d')

    echo "----------------------------------------"
    echo "Test: $description"
    echo "Command: $input"
    echo "Result: $output"
    echo "Expected: $expected"

    if [[ "$output" == "$expected" ]]; then
        echo "✅ PASS"
    else
        echo "❌ FAIL"
    fi
}

# -----------------------------
# TESTS
# -----------------------------

# 1. Redirección de salida >
run_test "Salida >" "echo hola > test.txt
cat test.txt" "hola"

# 2. Redirección de entrada <
echo "hola" > test.txt
run_test "Entrada <" "cat < test.txt" "hola"

# 3. Append >>
echo "hola" > test.txt
run_test "Append >>" "echo mundo >> test.txt
cat test.txt" "hola
mundo"

# 4. Combinación de redirecciones
echo -e "hola\nmundo" > test.txt
run_test "Redirección combinada" "cat < test.txt | grep mundo > result.txt
cat result.txt" "mundo"

# 5. Mezcla de pipes y redirecciones
echo -e "hola\nmundo" > test.txt
run_test "Pipe + redirección" "cat < test.txt | grep hola > result.txt
cat result.txt" "hola"

echo -e "1\n2\n3" > numbers.txt
run_test "Pipe + sort >" "cat < numbers.txt | sort > sorted.txt
cat sorted.txt" "1
2
3"

# 6. Variables de entorno
run_test "Variables de entorno" "export VAR1=prueba
echo \$VAR1
unset VAR1
echo \$VAR1
env | grep VAR1" "prueba"

# 7. Built-ins cd, pwd, export, unset, env, exit
# cd y pwd
run_test "cd y pwd" "pwd
cd ..
pwd" "$(pwd)
$(dirname $(pwd))"

# export y unset
run_test "export/unset PATH" "export PATH=/usr/bin
echo \$PATH
unset PATH
echo \$PATH" "/usr/bin"

# env sin argumentos
run_test "env sin args" "env | grep SHELL" "SHELL=/bin/bash"

# 8. Combinaciones complejas
echo "hola" > test.txt
run_test "echo + grep >" "echo hola | grep h > test.txt
cat test.txt" "hola"

run_test "cat < test.txt | wc -c" "cat < test.txt | wc -c" "5"

run_test "export VAR=test && echo \$VAR" "export VAR=test
echo \$VAR" "test"

# 9. Comprobación de errores incompletos (manual)
echo "----------------------------------------"
echo "Manual check required for incomplete commands:"
echo "  - ls |"
echo "  - cat <"
echo "Because heredoc/<<< cannot reproduce interactive syntax errors reliably."
echo "Test manually in minishell to ensure correct error messages."

# Limpiar ficheros temporales
rm -f test.txt result.txt sorted.txt numbers.txt echo_test.txt
