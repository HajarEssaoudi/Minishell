#!/bin/bash

# Couleurs pour l'affichage
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Variables globales
MINISHELL_PATH="./minishell"
TEST_COUNT=0
PASS_COUNT=0
FAIL_COUNT=0

# Fonction pour afficher les résultats
print_result() {
    local test_name="$1"
    local expected="$2"
    local actual="$3"
    local status="$4"
    
    TEST_COUNT=$((TEST_COUNT + 1))
    
    if [ "$status" = "PASS" ]; then
        echo -e "${GREEN}[PASS]${NC} $test_name"
        PASS_COUNT=$((PASS_COUNT + 1))
    else
        echo -e "${RED}[FAIL]${NC} $test_name"
        echo -e "  Expected: $expected"
        echo -e "  Got:      $actual"
        FAIL_COUNT=$((FAIL_COUNT + 1))
    fi
}

# Fonction pour tester une commande
test_command() {
    local test_name="$1"
    local command="$2"
    local expected_output="$3"
    local check_exit_code="${4:-false}"
    
    # Créer un fichier temporaire avec la commande
    echo "$command" > temp_cmd.txt
    echo "exit" >> temp_cmd.txt
    
    # Exécuter minishell avec redirection
    if [ "$check_exit_code" = "true" ]; then
        timeout 5s $MINISHELL_PATH < temp_cmd.txt > temp_output.txt 2>&1
        exit_code=$?
        actual_output=$(cat temp_output.txt | head -n -1)  # Enlever la dernière ligne (prompt)
    else
        timeout 5s $MINISHELL_PATH < temp_cmd.txt > temp_output.txt 2>&1
        actual_output=$(cat temp_output.txt | head -n -1)
    fi
    
    # Nettoyer les fichiers temporaires
    rm -f temp_cmd.txt temp_output.txt
    
    # Comparer les résultats
    if [ "$actual_output" = "$expected_output" ]; then
        print_result "$test_name" "$expected_output" "$actual_output" "PASS"
    else
        print_result "$test_name" "$expected_output" "$actual_output" "FAIL"
    fi
}

# Fonction pour tester avec bash comme référence
test_with_bash() {
    local test_name="$1"
    local command="$2"
    
    # Test avec bash
    bash_output=$(echo "$command" | bash 2>&1 | head -n -1)
    bash_exit=$?
    
    # Test avec minishell
    echo "$command" > temp_cmd.txt
    echo "exit" >> temp_cmd.txt
    timeout 5s $MINISHELL_PATH < temp_cmd.txt > temp_output.txt 2>&1
    minishell_exit=$?
    minishell_output=$(cat temp_output.txt | head -n -1)
    
    rm -f temp_cmd.txt temp_output.txt
    
    if [ "$bash_output" = "$minishell_output" ]; then
        print_result "$test_name" "$bash_output" "$minishell_output" "PASS"
    else
        print_result "$test_name" "$bash_output" "$minishell_output" "FAIL"
    fi
}

# Vérifier si minishell existe
check_minishell() {
    if [ ! -f "$MINISHELL_PATH" ]; then
        echo -e "${RED}Erreur: minishell non trouvé à $MINISHELL_PATH${NC}"
        echo "Assurez-vous de compiler votre minishell avec 'make' avant de lancer le test"
        exit 1
    fi
    
    if [ ! -x "$MINISHELL_PATH" ]; then
        echo -e "${RED}Erreur: minishell n'est pas exécutable${NC}"
        exit 1
    fi
}

echo -e "${BLUE}=== TESTER MINISHELL 42 ===${NC}\n"

check_minishell

echo -e "${YELLOW}--- Tests des commandes de base ---${NC}"

# Tests echo
test_command "echo simple" "echo Hello World" "Hello World"
test_command "echo avec option -n" "echo -n Hello" "Hello"
test_command "echo vide" "echo" ""
test_command "echo avec quotes" 'echo "Hello World"' "Hello World"
test_command "echo avec single quotes" "echo 'Hello World'" "Hello World"

# Tests pwd
echo -e "\n${YELLOW}--- Tests pwd ---${NC}"
current_dir=$(pwd)
test_command "pwd" "pwd" "$current_dir"

# Tests cd et pwd
echo -e "\n${YELLOW}--- Tests cd ---${NC}"
mkdir -p test_dir
echo "$MINISHELL_PATH" > temp_test.sh
echo "cd test_dir" >> temp_test.sh
echo "pwd" >> temp_test.sh
echo "cd .." >> temp_test.sh
echo "pwd" >> temp_test.sh
echo "exit" >> temp_test.sh

expected_cd_output="$current_dir/test_dir
$current_dir"

timeout 5s $MINISHELL_PATH < temp_test.sh > temp_cd_output.txt 2>&1
actual_cd_output=$(cat temp_cd_output.txt | head -n -2 | tail -n 2)

if [ "$actual_cd_output" = "$expected_cd_output" ]; then
    print_result "cd et pwd" "$expected_cd_output" "$actual_cd_output" "PASS"
else
    print_result "cd et pwd" "$expected_cd_output" "$actual_cd_output" "FAIL"
fi

rm -f temp_test.sh temp_cd_output.txt
rmdir test_dir

# Tests export et env
echo -e "\n${YELLOW}--- Tests des variables d'environnement ---${NC}"
test_command "export nouvelle variable" "export TEST_VAR=hello" ""

# Tests unset
test_command "unset variable" "unset PATH" ""

# Tests des pipes
echo -e "\n${YELLOW}--- Tests des pipes ---${NC}"
test_with_bash "pipe simple" "echo hello | cat"
test_with_bash "pipe avec grep" "echo -e 'line1\nline2\nline1' | grep line1"

# Tests des redirections
echo -e "\n${YELLOW}--- Tests des redirections ---${NC}"

# Créer un fichier de test
echo "test content" > test_input.txt

# Test redirection output
echo "$MINISHELL_PATH" > temp_redir.sh
echo "echo 'test output' > test_output.txt" >> temp_redir.sh
echo "exit" >> temp_redir.sh

timeout 5s $MINISHELL_PATH < temp_redir.sh > /dev/null 2>&1

if [ -f "test_output.txt" ] && [ "$(cat test_output.txt)" = "test output" ]; then
    print_result "redirection output >" "test output" "$(cat test_output.txt 2>/dev/null || echo 'file not found')" "PASS"
else
    print_result "redirection output >" "test output" "$(cat test_output.txt 2>/dev/null || echo 'file not found')" "FAIL"
fi

# Test redirection append
echo "$MINISHELL_PATH" > temp_redir.sh
echo "echo 'appended' >> test_output.txt" >> temp_redir.sh
echo "exit" >> temp_redir.sh

timeout 5s $MINISHELL_PATH < temp_redir.sh > /dev/null 2>&1

expected_append="test output
appended"

if [ -f "test_output.txt" ] && [ "$(cat test_output.txt)" = "$expected_append" ]; then
    print_result "redirection append >>" "$expected_append" "$(cat test_output.txt)" "PASS"
else
    print_result "redirection append >>" "$expected_append" "$(cat test_output.txt 2>/dev/null || echo 'file not found')" "FAIL"
fi

# Test redirection input
echo "$MINISHELL_PATH" > temp_redir.sh
echo "cat < test_input.txt" >> temp_redir.sh
echo "exit" >> temp_redir.sh

timeout 5s $MINISHELL_PATH < temp_redir.sh > temp_input_result.txt 2>&1
actual_input=$(cat temp_input_result.txt | head -n -1)

if [ "$actual_input" = "test content" ]; then
    print_result "redirection input <" "test content" "$actual_input" "PASS"
else
    print_result "redirection input <" "test content" "$actual_input" "FAIL"
fi

# Nettoyage
rm -f temp_redir.sh test_output.txt test_input.txt temp_input_result.txt

# Tests des quotes et expansion
echo -e "\n${YELLOW}--- Tests des quotes et variables ---${NC}"
test_command "expansion variable HOME" 'echo $HOME' "$HOME"
test_command "single quotes (pas d'expansion)" 'echo '$HOME'' '$HOME'
test_command "double quotes avec expansion" "echo \"\$HOME\"" "$HOME"

# Tests de gestion d'erreurs
echo -e "\n${YELLOW}--- Tests de gestion d'erreurs ---${NC}"
test_command "commande inexistante" "commandeinexistante" "commandeinexistante: command not found"
test_command "cd vers répertoire inexistant" "cd /repertoire/inexistant" "cd: /repertoire/inexistant: No such file or directory"

# Tests des signaux (basique)
echo -e "\n${YELLOW}--- Tests des signaux ---${NC}"
echo "Test des signaux (Ctrl+C, Ctrl+D) à faire manuellement"
echo "Le minishell doit gérer Ctrl+C sans quitter et Ctrl+D pour quitter proprement"

# Tests des built-ins
echo -e "\n${YELLOW}--- Tests des built-ins ---${NC}"
test_command "exit" "exit 0" ""

# Résumé des tests
echo -e "\n${BLUE}=== RÉSUMÉ DES TESTS ===${NC}"
echo -e "Total des tests: $TEST_COUNT"
echo -e "${GREEN}Réussis: $PASS_COUNT${NC}"
echo -e "${RED}Échoués: $FAIL_COUNT${NC}"

if [ $FAIL_COUNT -eq 0 ]; then
    echo -e "\n${GREEN}🎉 Tous les tests sont passés! Votre minishell semble fonctionner correctement.${NC}"
else
    echo -e "\n${YELLOW}⚠️  Il y a encore quelques problèmes à résoudre.${NC}"
fi

echo -e "\n${BLUE}Note: Ce tester couvre les fonctionnalités de base. Testez aussi manuellement:${NC}"
echo "- Les signaux (Ctrl+C, Ctrl+\\, Ctrl+D)"
echo "- Les heredocs (<<)"
echo "- Les pipes multiples"
echo "- Les cas complexes de quotes et d'expansion"
echo "- Les variables d'environnement personnalisées"

exit $FAIL_COUNT