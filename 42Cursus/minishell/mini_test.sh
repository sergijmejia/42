#!/bin/bash

# Mini automated tests for your minishell
MINISHELL="./minishell"

# Clean generated files
rm -f test.txt result.txt sorted.txt numbers.txt

# Function to run a test
run_test() {
    local description="$1"
    local input="$2"
    local expected="$3"

    # Run the shell with heredoc
    output=$($MINISHELL <<EOF
$input
exit
EOF
)

    # Remove prompts and empty lines
    clean_output=$(echo "$output" | sed '/^minishell\$ /d' | sed '/^[[:space:]]*$/d')
    expected_clean=$(echo "$expected" | sed '/^[[:space:]]*$/d')

    echo "----------------------------------------"
    echo "Test: $description"
    echo "Comando: $input"
    echo "Resultado: $clean_output"
    echo "Esperado : $expected_clean"

    if [[ "$clean_output" == "$expected_clean" ]]; then
        echo "✅ PASS"
    else
        echo "❌ FAIL"
    fi
}

# -----------------------------
# TESTS
# -----------------------------

# 1. Redirection >
run_test "Salida >" "echo hola > test.txt
cat test.txt" "hola"

# 2. Redirection <
echo "hola" > test.txt
run_test "Entrada <" "cat < test.txt" "hola"

# 3. Append >>
echo "hola" > test.txt
run_test "Append >>" "echo mundo >> test.txt
cat test.txt" "hola
mundo"

# 4. Simple pipe
echo -e "1\n2\n3" > numbers.txt
run_test "Pipe simple" "cat numbers.txt | sort" "1
2
3"

# 5. Pipe + redirection
echo -e "hola\nmundo" > test.txt
run_test "Pipe + >" "cat < test.txt | grep mundo > result.txt
cat result.txt" "mundo"

# 6. Environment variables
run_test "Variables de entorno" "export VAR1=prueba
echo \$VAR1
unset VAR1
echo \$VAR1" "prueba"

# 7. Built-ins cd and pwd
run_test "cd y pwd" "pwd
cd ..
pwd" "$(pwd)
$(dirname $(pwd))"

# 8. Simple combination
run_test "Echo + grep" "echo hola | grep h" "hola"

# Clean temporary files
rm -f test.txt result.txt numbers.txt
