#!/bin/bash
# full_test_heredoc.sh
# Automated heredoc tests for minishell

MINISHELL="./minishell"

# Helper to run a test
run_test() {
    local description="$1"
    local input="$2"
    local expected="$3"

    # Run minishell with heredoc input
    output=$($MINISHELL <<EOF
$input
exit
EOF
)

    # Clean prompts and empty lines
    clean_output=$(echo "$output" | sed '/^minishell\$ /d' | sed '/^$/d')

    echo "----------------------------------------"
    echo "Test: $description"
    echo "Command: $input"
    echo "Result: $clean_output"
    echo "Expected: $expected"

    if [[ "$clean_output" == "$expected" ]]; then
        echo "✅ PASS"
    else
        echo "❌ FAIL"
    fi
}

# -----------------------------
# TESTS
# -----------------------------

# 1. Simple heredoc
run_test "Simple heredoc" "cat <<EOT
hello
world
EOT" "hello
world"

# 2. Heredoc into a file
run_test "Heredoc into file" "cat <<EOF > test.txt
line1
line2
EOF
cat test.txt" "line1
line2"

# 3. Heredoc with variable expansion
run_test "Heredoc with variable" "VAR=42
cat <<EOF
value is \$VAR
EOF" "value is 42"

# 4. Heredoc with empty lines
run_test "Heredoc with empty lines" "cat <<EOF
first

third
EOF" "first

third"

# 5. Heredoc with delimiter immediately
run_test "Immediate delimiter" "cat <<EOF
EOF" ""

# 6. Multiple heredocs in single command
run_test "Multiple heredocs" "cat <<A <<B
hello
A
world
B" "hello
world"

# 7. Early end with Ctrl-D simulation (here we simulate by ending input early)
run_test "Early end heredoc" "cat <<EOF
line1
line2" "line1
line2"

# Cleanup
rm -f test.txt
