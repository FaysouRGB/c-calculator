#!/bin/sh

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

run_test()
{
    local input="$1"
    local expected="$2"
    local arguments="$3"

    local result=$(echo "$input" | ./calculator $arguments)
    local code=$?

    if [ "$result" = "$expected" ] && [ $code -eq 0 ]; then
        echo -e "${GREEN}[OK]${NC} $input"
    else
        echo -e "${RED}[FAIL]${NC} $input = $result (expected $expected)"
    fi
}

run_error_test()
{
    local input="$1"
    local expected=$2
    local arguments="$3"

    echo "$input" | ./calculator $arguments > /dev/null 2>&1
    local code=$?

    if [ $code -eq $expected ]; then
        echo -e "${GREEN}[OK]${NC} $input"
    else
        echo -e "${RED}[FAIL]${NC} $input => ERROR $code (expected $expected)"
    fi
}

# Infix Tests
echo -e "\n[1/4] Running Infix Tests\n"
run_test "1 + 1" "2" ""
run_test "1 / -1" "-1" ""
run_test "5 * (2 ^ 2 + 3) + -1" "34" ""
run_test "42 * ----1" "42" ""
run_test "3 - 2 + (5 - 2) ^ 2" "10" ""
run_test "2 + 3 * 4" "14" ""
run_test "(2 + 3) * 4" "20" ""
run_test "2 ^ 3 ^ 2" "512" ""
run_test "10 % 3" "1" ""
run_test "10 / 3" "3" ""
run_test "1 + 2 * 3 - 4 / 2" "5" ""
run_test "1 + (2 * (3 - 4)) / 2" "0" ""
run_test "1 + 2 * (3 + 4) / 2 - 5" "3" ""
run_test "1 + 2 * 3 ^ 2" "19" ""
run_test "1 + 2 * (3 + 4 ^ 2)" "39" ""
run_test "1 + -2 * 3" "-5" ""
run_test "1 + 2 * -3" "-5" ""
run_test "1 + -2 * -3" "7" ""
run_test "1 + 2 * 3 + 4" "11" ""
run_test "1 + 2 * (3 + 4)" "15" ""
run_test "1 + (2 * 3) + 4" "11" ""
run_test "1 + 2 * 3 ^ 2 + 4" "23" ""
run_test "1 + 2 * (3 + 4 ^ 2) + 5" "44" ""

# RPN Tests
echo -e "\n[2/4] Running RPN Tests\n"
run_test "1 1 +" "2" "-rpn"
run_test "5 2 2 ^ 3 + *" "35" "-rpn"
run_test "3 4 2 * 1 5 - 2 3 ^ ^ / +" "3" "-rpn"
run_test "10 3 %" "1" "-rpn"
run_test "10 3 /" "3" "-rpn"
run_test "1 2 3 * + 4 2 / -" "5" "-rpn"
run_test "1 2 3 4 + * +" "15" "-rpn"
run_test "1 2 + 3 4 + *" "21" "-rpn"
run_test "2 3 ^ 4 5 + *" "72" "-rpn"
run_test "1 2 3 * + 4 5 - 6 * +" "1" "-rpn"

# Error Tests
echo -e "\n[3/4] Running Error Tests\n"
run_error_test "a 1 +" 1 "-rpn" # Invalid character
run_error_test "1 + 1" 1 "-rpn" # Infix expression in RPN mode
run_error_test "1 (+ 1)" 1 "" # Invalid parentheses
run_error_test "1 + 1)" 1 "" # Mismatched parentheses
run_error_test "2 ^ -1" 1 "" # Negative exponent (if not supported)
run_error_test "1 + 1 / 0" 1 "" # Division by zero
run_error_test "1 + 1" 1 "-sushi" # Invalid argument
run_error_test "1 +" 1 "" # Incomplete expression
run_error_test "1 2 3 +" 1 "-rpn" # Incomplete RPN expression
run_error_test "1 + * 2" 1 "" # Invalid operator sequence
run_error_test "1 + 2 *" 1 "" # Incomplete expression
run_error_test "1 + (2 * 3" 1 "" # Mismatched parentheses
run_error_test "1 + 2 * 3)" 1 "" # Mismatched parentheses
run_error_test "1 + 2 * 3 +" 1 "" # Incomplete expression
run_error_test "1 + 2 * 3 + 4 5" 1 "" # Extra operand

# Stress Tests
echo -e "\n[4/4] Running Stress Tests\n"
run_test "999999999 + 1" "1000000000" ""
run_test "2 ^ 30" "1073741824" ""
run_test "2 ^ 31 - 1" "2147483647" ""
run_test "1000000000 / 2" "500000000" ""
run_test "1000000000 % 7" "6" ""
run_test "1 + 2 * (3 + 4 ^ 5) / 6 - 7 % 8" "336" ""
run_test "1 + 2 * 3 ^ (4 + 5) / 6 - 7 % 8" "6555" ""
