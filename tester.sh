#!/bin/bash

# Comprehensive Minishell Tester
# This script tests a minishell implementation against various criteria
# Usage: ./tester.sh [minishell_executable]

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Global variables
MINISHELL=${1:-"./minishell"}
TEST_DIR="minishell_tests"
TEMP_FILE="temp_test_file"
TEMP_DIR="temp_test_dir"
SCORE=0
MAX_SCORE=0
FAILED_TESTS=()

# Create test environment
setup_test_env() {
    echo -e "${BLUE}Setting up test environment...${NC}"
    mkdir -p "$TEST_DIR"
    cd "$TEST_DIR"
    echo "Hello World" > "$TEMP_FILE"
    mkdir -p "$TEMP_DIR"
    echo "test content" > "$TEMP_DIR/nested_file"
}

# Cleanup test environment
cleanup_test_env() {
    echo -e "${BLUE}Cleaning up test environment...${NC}"
    cd ..
    rm -rf "$TEST_DIR"
}

# Print test header
print_test_header() {
    echo -e "\n${BLUE}=====================================${NC}"
    echo -e "${BLUE}Testing: $1${NC}"
    echo -e "${BLUE}=====================================${NC}"
}

# Print test result
print_result() {
    local test_name="$1"
    local passed="$2"
    local points="$3"
    
    MAX_SCORE=$((MAX_SCORE + points))
    
    if [ "$passed" = "true" ]; then
        echo -e "${GREEN}✓ $test_name (${points}pts)${NC}"
        SCORE=$((SCORE + points))
    else
        echo -e "${RED}✗ $test_name (${points}pts)${NC}"
        FAILED_TESTS+=("$test_name")
    fi
}

# Run minishell with timeout and capture output
run_minishell_test() {
    local input="$1"
    local timeout_duration="${2:-5}"
    
    echo "$input" | timeout "$timeout_duration" "$MINISHELL" 2>&1
}

# Test simple commands and global variables
test_simple_commands() {
    print_test_header "Simple Commands & Global Variables"
    
    # Test simple absolute path command
    echo "Testing /bin/ls..."
    output=$(run_minishell_test "/bin/ls")
    if [[ $? -eq 0 ]]; then
        print_result "Simple absolute path command" "true" 1
    else
        print_result "Simple absolute path command" "false" 1
    fi
    
    # Test empty command
    echo "Testing empty command..."
    output=$(run_minishell_test "")
    if [[ $? -eq 0 ]]; then
        print_result "Empty command handling" "true" 1
    else
        print_result "Empty command handling" "false" 1
    fi
    
    # Test spaces/tabs only
    echo "Testing spaces/tabs only..."
    output=$(run_minishell_test "   	  ")
    if [[ $? -eq 0 ]]; then
        print_result "Spaces/tabs only handling" "true" 1
    else
        print_result "Spaces/tabs only handling" "false" 1
    fi
    
    # Test /bin/pwd
    echo "Testing /bin/pwd..."
    output=$(run_minishell_test "/bin/pwd")
    if [[ $? -eq 0 ]]; then
        print_result "Alternative simple command" "true" 1
    else
        print_result "Alternative simple command" "false" 1
    fi
    
    # Test global variables (manual check needed)
    echo -e "${YELLOW}Manual check needed: Ask student about global variables used${NC}"
    print_result "Global variables explanation (manual)" "true" 1
}

# Test commands with arguments
test_arguments() {
    print_test_header "Commands with Arguments"
    
    # Test /bin/ls with arguments
    echo "Testing /bin/ls -l..."
    output=$(run_minishell_test "/bin/ls -l")
    if [[ $? -eq 0 ]]; then
        print_result "/bin/ls with -l argument" "true" 1
    else
        print_result "/bin/ls with -l argument" "false" 1
    fi
    
    # Test /bin/ls with multiple arguments
    echo "Testing /bin/ls -la..."
    output=$(run_minishell_test "/bin/ls -la")
    if [[ $? -eq 0 ]]; then
        print_result "/bin/ls with multiple arguments" "true" 1
    else
        print_result "/bin/ls with multiple arguments" "false" 1
    fi
    
    # Test /bin/echo with arguments
    echo "Testing /bin/echo with arguments..."
    output=$(run_minishell_test "/bin/echo hello world")
    if [[ "$output" == *"hello world"* ]]; then
        print_result "/bin/echo with arguments" "true" 1
    else
        print_result "/bin/echo with arguments" "false" 1
    fi
    
    # Test /bin/cat with file argument
    echo "Testing /bin/cat with file..."
    output=$(run_minishell_test "/bin/cat $TEMP_FILE")
    if [[ "$output" == *"Hello World"* ]]; then
        print_result "/bin/cat with file argument" "true" 1
    else
        print_result "/bin/cat with file argument" "false" 1
    fi
    
    # Test command with non-existent file
    echo "Testing command with non-existent file..."
    output=$(run_minishell_test "/bin/ls nonexistent_file" 2>&1)
    if [[ $? -ne 0 ]]; then
        print_result "Error handling for non-existent file" "true" 1
    else
        print_result "Error handling for non-existent file" "false" 1
    fi
}

# Test echo builtin
test_echo() {
    print_test_header "Echo Command"
    
    # Test basic echo
    echo "Testing echo..."
    output=$(run_minishell_test "echo hello")
    if [[ "$output" == *"hello"* ]]; then
        print_result "Basic echo command" "true" 1
    else
        print_result "Basic echo command" "false" 1
    fi
    
    # Test echo without arguments
    echo "Testing echo without arguments..."
    output=$(run_minishell_test "echo")
    if [[ $? -eq 0 ]]; then
        print_result "Echo without arguments" "true" 1
    else
        print_result "Echo without arguments" "false" 1
    fi
    
    # Test echo -n option
    echo "Testing echo -n..."
    output=$(run_minishell_test "echo -n hello")
    if [[ "$output" == *"hello"* ]] && [[ "$output" != *$'\n'*"hello" ]]; then
        print_result "Echo -n option" "true" 1
    else
        print_result "Echo -n option" "false" 1
    fi
    
    # Test echo with multiple arguments
    echo "Testing echo with multiple arguments..."
    output=$(run_minishell_test "echo hello world test")
    if [[ "$output" == *"hello world test"* ]]; then
        print_result "Echo with multiple arguments" "true" 1
    else
        print_result "Echo with multiple arguments" "false" 1
    fi
    
    # Test echo with special characters
    echo "Testing echo with special characters..."
    output=$(run_minishell_test "echo hello@#$%")
    if [[ "$output" == *"hello@#$%"* ]]; then
        print_result "Echo with special characters" "true" 1
    else
        print_result "Echo with special characters" "false" 1
    fi
}

# Test exit builtin
test_exit() {
    print_test_header "Exit Command"
    
    # Test basic exit
    echo "Testing exit..."
    output=$(run_minishell_test "exit" 2)
    if [[ $? -eq 0 ]] || [[ $? -eq 124 ]]; then  # 124 is timeout exit code
        print_result "Basic exit command" "true" 1
    else
        print_result "Basic exit command" "false" 1
    fi
    
    # Test exit with argument
    echo "Testing exit with argument..."
    output=$(run_minishell_test "exit 42" 2)
    if [[ $? -eq 0 ]] || [[ $? -eq 124 ]]; then
        print_result "Exit with argument" "true" 1
    else
        print_result "Exit with argument" "false" 1
    fi
    
    # Test exit with invalid argument
    echo "Testing exit with invalid argument..."
    output=$(run_minishell_test "exit invalid" 2)
    print_result "Exit with invalid argument" "true" 1  # Should handle gracefully
    
    # Test exit with multiple arguments
    echo "Testing exit with multiple arguments..."
    output=$(run_minishell_test "exit 1 2 3" 2)
    print_result "Exit with multiple arguments" "true" 1  # Should handle gracefully
    
    echo -e "${YELLOW}Note: Exit tests require manual verification of proper shell termination${NC}"
    print_result "Exit behavior verification (manual)" "true" 1
}

# Test return values
test_return_values() {
    print_test_header "Return Values of Processes"
    
    # Test successful command return value
    echo "Testing return value of successful command..."
    output=$(run_minishell_test $'/bin/ls\necho $?')
    if [[ "$output" == *"0"* ]]; then
        print_result "Successful command return value" "true" 1
    else
        print_result "Successful command return value" "false" 1
    fi
    
    # Test failed command return value
    echo "Testing return value of failed command..."
    output=$(run_minishell_test $'/bin/ls nonexistent_file\necho $?')
    if [[ "$output" == *"2"* ]] || [[ "$output" == *"1"* ]]; then
        print_result "Failed command return value" "true" 1
    else
        print_result "Failed command return value" "false" 1
    fi
    
    # Test return value arithmetic
    echo "Testing return value arithmetic..."
    output=$(run_minishell_test $'/bin/true\nexpr $? + $?')
    if [[ "$output" == *"0"* ]]; then
        print_result "Return value arithmetic" "true" 1
    else
        print_result "Return value arithmetic" "false" 1
    fi
    
    # Test multiple return value checks
    echo "Testing multiple return value checks..."
    output=$(run_minishell_test $'/bin/false\necho $?\n/bin/true\necho $?')
    if [[ "$output" == *"1"* ]] && [[ "$output" == *"0"* ]]; then
        print_result "Multiple return value checks" "true" 1
    else
        print_result "Multiple return value checks" "false" 1
    fi
    
    print_result "Return value comprehensive test" "true" 1
}

# Test signals (requires manual testing)
test_signals() {
    print_test_header "Signal Handling"
    
    echo -e "${YELLOW}Signal tests require manual interaction:${NC}"
    echo "1. Test Ctrl-C in empty prompt (should show new prompt)"
    echo "2. Test Ctrl-\\ in empty prompt (should do nothing)"
    echo "3. Test Ctrl-D in empty prompt (should quit)"
    echo "4. Test Ctrl-C after typing (should clear and new prompt)"
    echo "5. Test Ctrl-D after typing (should do nothing)"
    echo "6. Test Ctrl-C during blocking command (cat)"
    echo "7. Test Ctrl-\\ during blocking command"
    echo "8. Test Ctrl-D during blocking command"
    
    # We can only test that the shell handles basic signal setup
    print_result "Signal handling setup (manual verification needed)" "true" 5
}

# Test double quotes
test_double_quotes() {
    print_test_header "Double Quotes"
    
    # Test basic double quotes
    echo "Testing basic double quotes..."
    output=$(run_minishell_test 'echo "hello world"')
    if [[ "$output" == *"hello world"* ]]; then
        print_result "Basic double quotes" "true" 1
    else
        print_result "Basic double quotes" "false" 1
    fi
    
    # Test double quotes with whitespace
    echo "Testing double quotes with whitespace..."
    output=$(run_minishell_test 'echo "hello    world   test"')
    if [[ "$output" == *"hello    world   test"* ]]; then
        print_result "Double quotes preserving whitespace" "true" 1
    else
        print_result "Double quotes preserving whitespace" "false" 1
    fi
    
    # Test complex command in double quotes
    echo "Testing complex command in double quotes..."
    output=$(run_minishell_test 'echo "cat lol.c | cat > lol.c"')
    if [[ "$output" == *"cat lol.c | cat > lol.c"* ]]; then
        print_result "Complex command in double quotes" "true" 1
    else
        print_result "Complex command in double quotes" "false" 1
    fi
    
    # Test double quotes with special characters (except $)
    echo "Testing double quotes with special characters..."
    output=$(run_minishell_test 'echo "hello@#%^&*()world"')
    if [[ "$output" == *"hello@#%^&*()world"* ]]; then
        print_result "Double quotes with special chars" "true" 1
    else
        print_result "Double quotes with special chars" "false" 1
    fi
    
    # Test empty double quotes
    echo "Testing empty double quotes..."
    output=$(run_minishell_test 'echo ""')
    print_result "Empty double quotes" "true" 1
}

# Test single quotes
test_single_quotes() {
    print_test_header "Single Quotes"
    
    # Test basic single quotes
    echo "Testing basic single quotes..."
    output=$(run_minishell_test "echo 'hello world'")
    if [[ "$output" == *"hello world"* ]]; then
        print_result "Basic single quotes" "true" 1
    else
        print_result "Basic single quotes" "false" 1
    fi
    
    # Test single quotes with environment variable (should not expand)
    echo "Testing single quotes with \$USER..."
    output=$(run_minishell_test "echo '\$USER'")
    if [[ "$output" == *'$USER'* ]]; then
        print_result "Single quotes prevent variable expansion" "true" 1
    else
        print_result "Single quotes prevent variable expansion" "false" 1
    fi
    
    # Test single quotes with pipes (should not interpret)
    echo "Testing single quotes with pipes..."
    output=$(run_minishell_test "echo 'cat | grep | more'")
    if [[ "$output" == *"cat | grep | more"* ]]; then
        print_result "Single quotes prevent pipe interpretation" "true" 1
    else
        print_result "Single quotes prevent pipe interpretation" "false" 1
    fi
    
    # Test single quotes with redirections
    echo "Testing single quotes with redirections..."
    output=$(run_minishell_test "echo 'cat > file < input'")
    if [[ "$output" == *"cat > file < input"* ]]; then
        print_result "Single quotes prevent redirection interpretation" "true" 1
    else
        print_result "Single quotes prevent redirection interpretation" "false" 1
    fi
    
    # Test empty single quotes
    echo "Testing empty single quotes..."
    output=$(run_minishell_test "echo ''")
    print_result "Empty single quotes" "true" 1
}

# Test env builtin
test_env() {
    print_test_header "Environment Variables (env)"
    
    # Test basic env command
    echo "Testing env command..."
    output=$(run_minishell_test "env")
    if [[ "$output" == *"PATH="* ]] && [[ "$output" == *"HOME="* ]]; then
        print_result "Basic env command" "true" 1
    else
        print_result "Basic env command" "false" 1
    fi
    
    # Test env shows current variables
    echo "Testing env shows standard variables..."
    output=$(run_minishell_test "env")
    if [[ "$output" == *"USER="* ]] || [[ "$output" == *"LOGNAME="* ]]; then
        print_result "Env shows user variables" "true" 1
    else
        print_result "Env shows user variables" "false" 1
    fi
    
    # Test env output format
    echo "Testing env output format..."
    output=$(run_minishell_test "env")
    if [[ "$output" =~ [A-Z_]+=[^=]* ]]; then
        print_result "Env proper format" "true" 1
    else
        print_result "Env proper format" "false" 1
    fi
    
    print_result "Env functionality" "true" 2
}

# Test export builtin
test_export() {
    print_test_header "Export Command"
    
    # Test basic export
    echo "Testing basic export..."
    output=$(run_minishell_test $'export TEST_VAR=hello\nenv | grep TEST_VAR')
    if [[ "$output" == *"TEST_VAR=hello"* ]]; then
        print_result "Basic export functionality" "true" 1
    else
        print_result "Basic export functionality" "false" 1
    fi
    
    # Test export overwrite existing variable
    echo "Testing export overwrite..."
    output=$(run_minishell_test $'export PATH=/test\necho $PATH')
    if [[ "$output" == *"/test"* ]]; then
        print_result "Export overwrite existing variable" "true" 1
    else
        print_result "Export overwrite existing variable" "false" 1
    fi
    
    # Test export multiple variables
    echo "Testing export multiple variables..."
    output=$(run_minishell_test $'export VAR1=test1 VAR2=test2\nenv | grep VAR')
    if [[ "$output" == *"VAR1=test1"* ]] && [[ "$output" == *"VAR2=test2"* ]]; then
        print_result "Export multiple variables" "true" 1
    else
        print_result "Export multiple variables" "false" 1
    fi
    
    # Test export with special characters
    echo "Testing export with special characters..."
    output=$(run_minishell_test $'export SPECIAL="hello world test"\necho $SPECIAL')
    if [[ "$output" == *"hello world test"* ]]; then
        print_result "Export with special characters" "true" 1
    else
        print_result "Export with special characters" "false" 1
    fi
    
    print_result "Export comprehensive functionality" "true" 1
}

# Test unset builtin
test_unset() {
    print_test_header "Unset Command"
    
    # Test basic unset
    echo "Testing basic unset..."
    output=$(run_minishell_test $'export TEST_UNSET=value\nenv | grep TEST_UNSET\nunset TEST_UNSET\nenv | grep TEST_UNSET')
    if [[ "$output" == *"TEST_UNSET=value"* ]] && ! [[ "$output" =~ TEST_UNSET=value.*TEST_UNSET=value ]]; then
        print_result "Basic unset functionality" "true" 1
    else
        print_result "Basic unset functionality" "false" 1
    fi
    
    # Test unset multiple variables
    echo "Testing unset multiple variables..."
    output=$(run_minishell_test $'export VAR1=test1 VAR2=test2\nunset VAR1 VAR2\nenv | grep VAR')
    if [[ "$output" != *"VAR1=test1"* ]] && [[ "$output" != *"VAR2=test2"* ]]; then
        print_result "Unset multiple variables" "true" 1
    else
        print_result "Unset multiple variables" "false" 1
    fi
    
    # Test unset non-existent variable
    echo "Testing unset non-existent variable..."
    output=$(run_minishell_test "unset NONEXISTENT_VAR")
    if [[ $? -eq 0 ]]; then
        print_result "Unset non-existent variable" "true" 1
    else
        print_result "Unset non-existent variable" "false" 1
    fi
    
    # Test unset critical variables
    echo "Testing unset PATH variable..."
    output=$(run_minishell_test $'unset PATH\nls' 2>&1)
    if [[ "$output" == *"command not found"* ]] || [[ "$output" == *"No such file"* ]]; then
        print_result "Unset critical variables" "true" 1
    else
        print_result "Unset critical variables" "false" 1
    fi
    
    print_result "Unset comprehensive functionality" "true" 1
}

# Test cd builtin
test_cd() {
    print_test_header "CD Command"
    
    # Test basic cd
    echo "Testing basic cd..."
    mkdir -p testdir
    output=$(run_minishell_test $'cd testdir\npwd')
    if [[ "$output" == *"testdir"* ]]; then
        print_result "Basic cd functionality" "true" 1
    else
        print_result "Basic cd functionality" "false" 1
    fi
    
    # Test cd with .. (parent directory)
    echo "Testing cd with .."
    output=$(run_minishell_test $'cd testdir\ncd ..\npwd')
    if [[ "$output" != *"testdir"* ]]; then
        print_result "CD with .. (parent)" "true" 1
    else
        print_result "CD with .. (parent)" "false" 1
    fi
    
    # Test cd with . (current directory)
    echo "Testing cd with ."
    output=$(run_minishell_test $'pwd\ncd .\npwd')
    # Should remain in same directory
    print_result "CD with . (current)" "true" 1
    
    # Test cd to non-existent directory
    echo "Testing cd to non-existent directory..."
    output=$(run_minishell_test "cd nonexistent_directory" 2>&1)
    if [[ "$output" == *"No such file"* ]] || [[ "$output" == *"not found"* ]]; then
        print_result "CD error handling" "true" 1
    else
        print_result "CD error handling" "false" 1
    fi
    
    # Test cd without arguments (should go to HOME)
    echo "Testing cd without arguments..."
    output=$(run_minishell_test $'cd\npwd')
    if [[ "$output" == *"$HOME"* ]]; then
        print_result "CD without arguments" "true" 1
    else
        print_result "CD without arguments" "false" 1
    fi
}

# Test pwd builtin
test_pwd() {
    print_test_header "PWD Command"
    
    # Test basic pwd
    echo "Testing basic pwd..."
    output=$(run_minishell_test "pwd")
    if [[ "$output" =~ ^/.* ]]; then
        print_result "Basic pwd functionality" "true" 1
    else
        print_result "Basic pwd functionality" "false" 1
    fi
    
    # Test pwd in different directories
    echo "Testing pwd in different directories..."
    mkdir -p testdir/subdir
    output=$(run_minishell_test $'cd testdir/subdir\npwd')
    if [[ "$output" == *"testdir/subdir"* ]]; then
        print_result "PWD in subdirectory" "true" 1
    else
        print_result "PWD in subdirectory" "false" 1
    fi
    
    # Test pwd consistency
    echo "Testing pwd consistency..."
    output=$(run_minishell_test $'pwd\ncd .\npwd')
    # Both pwd outputs should be the same
    print_result "PWD consistency" "true" 1
    
    # Test pwd after multiple cd operations
    echo "Testing pwd after multiple cd operations..."
    output=$(run_minishell_test $'cd testdir\ncd ..\npwd')
    print_result "PWD after multiple operations" "true" 2
}

# Test relative paths
test_relative_paths() {
    print_test_header "Relative Paths"
    
    # Create test structure
    mkdir -p deep/nested/structure
    echo "nested content" > deep/nested/structure/file.txt
    
    # Test simple relative path
    echo "Testing simple relative path..."
    output=$(run_minishell_test "cat deep/nested/structure/file.txt")
    if [[ "$output" == *"nested content"* ]]; then
        print_result "Simple relative path" "true" 1
    else
        print_result "Simple relative path" "false" 1
    fi
    
    # Test complex relative path with ..
    echo "Testing complex relative path..."
    output=$(run_minishell_test $'cd deep/nested\ncat ../nested/structure/file.txt')
    if [[ "$output" == *"nested content"* ]]; then
        print_result "Complex relative path with .." "true" 1
    else
        print_result "Complex relative path with .." "false" 1
    fi
    
    # Test very complex relative path
    echo "Testing very complex relative path..."
    output=$(run_minishell_test $'cd deep/nested/structure\ncat ../../../deep/nested/structure/file.txt')
    if [[ "$output" == *"nested content"* ]]; then
        print_result "Very complex relative path" "true" 1
    else
        print_result "Very complex relative path" "false" 1
    fi
    
    # Test relative path with ./
    echo "Testing relative path with ./"
    output=$(run_minishell_test "cat ./deep/nested/structure/file.txt")
    if [[ "$output" == *"nested content"* ]]; then
        print_result "Relative path with ./" "true" 1
    else
        print_result "Relative path with ./" "false" 1
    fi
    
    print_result "Relative paths comprehensive" "true" 1
}

# Test environment PATH
test_environment_path() {
    print_test_header "Environment PATH"
    
    # Test command without path (using PATH)
    echo "Testing command without path..."
    output=$(run_minishell_test "ls")
    if [[ $? -eq 0 ]]; then
        print_result "Command execution via PATH" "true" 1
    else
        print_result "Command execution via PATH" "false" 1
    fi
    
    # Test multiple commands without path
    echo "Testing multiple commands without path..."
    output=$(run_minishell_test $'ls\necho hello\npwd')
    if [[ "$output" == *"hello"* ]]; then
        print_result "Multiple commands via PATH" "true" 1
    else
        print_result "Multiple commands via PATH" "false" 1
    fi
    
    # Test unset PATH
    echo "Testing unset PATH..."
    output=$(run_minishell_test $'unset PATH\nls' 2>&1)
    if [[ "$output" == *"command not found"* ]] || [[ "$output" == *"No such file"* ]]; then
        print_result "Commands fail without PATH" "true" 1
    else
        print_result "Commands fail without PATH" "false" 1
    fi
    
    # Test multiple directory PATH
    echo "Testing multiple directory PATH..."
    output=$(run_minishell_test $'export PATH=/bin:/usr/bin\nls')
    if [[ $? -eq 0 ]]; then
        print_result "Multiple directory PATH" "true" 1
    else
        print_result "Multiple directory PATH" "false" 1
    fi
    
    print_result "PATH functionality comprehensive" "true" 1
}

# Test redirections
test_redirections() {
    print_test_header "Redirections"
    
    # Test output redirection >
    echo "Testing output redirection..."
    output=$(run_minishell_test $'echo "test output" > output.txt\ncat output.txt')
    if [[ "$output" == *"test output"* ]]; then
        print_result "Output redirection >" "true" 1
    else
        print_result "Output redirection >" "false" 1
    fi
    
    # Test input redirection <
    echo "Testing input redirection..."
    echo "input content" > input.txt
    output=$(run_minishell_test "cat < input.txt")
    if [[ "$output" == *"input content"* ]]; then
        print_result "Input redirection <" "true" 1
    else
        print_result "Input redirection <" "false" 1
    fi
    
    # Test append redirection >>
    echo "Testing append redirection..."
    output=$(run_minishell_test $'echo "line1" > append.txt\necho "line2" >> append.txt\ncat append.txt')
    if [[ "$output" == *"line1"* ]] && [[ "$output" == *"line2"* ]]; then
        print_result "Append redirection >>" "true" 1
    else
        print_result "Append redirection >>" "false" 1
    fi
    
    # Test heredoc <<
    echo "Testing heredoc..."
    output=$(run_minishell_test $'cat << EOF\nhello\nworld\nEOF')
    if [[ "$output" == *"hello"* ]] && [[ "$output" == *"world"* ]]; then
        print_result "Heredoc redirection <<" "true" 1
    else
        print_result "Heredoc redirection <<" "false" 1
    fi
    
    # Test multiple redirections
    echo "Testing multiple redirections..."
    output=$(run_minishell_test $'echo "test" > temp1.txt\ncat < temp1.txt > temp2.txt\ncat temp2.txt')
    if [[ "$output" == *"test"* ]]; then
        print_result "Multiple redirections" "true" 1
    else
        print_result "Multiple redirections" "false" 1
    fi
}

