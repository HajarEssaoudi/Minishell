#!/bin/bash

# Script de test pour Minishell 42
# Remplace "bureau" par "Desktop" et "user42" par "madelha"

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

MINISHELL="./minishell"
TEST_COUNT=0
PASS_COUNT=0

echo -e "${BLUE}=== TEST MINISHELL 42 ===${NC}"
echo -e "${YELLOW}Utilisateur: madelha${NC}"
echo -e "${YELLOW}Prompt détecté: Minishell\$>${NC}"
echo ""

# Fonction pour tester une commande
test_command() {
    local test_name="$1"
    local command="$2"
    local expected_status="$3"
    
    TEST_COUNT=$((TEST_COUNT + 1))
    echo -e "${BLUE}Test $TEST_COUNT: $test_name${NC}"
    echo "Commande: $command"
    
    # Exécuter la commande dans minishell (filtrer le prompt)
    echo "$command" | $MINISHELL 2>/tmp/minishell_error | grep -v "Minishell\$>" > /tmp/minishell_output
    local minishell_status=$?
    
    # Ajouter les erreurs si présentes
    if [ -s /tmp/minishell_error ]; then
        grep -v "Minishell\$>" /tmp/minishell_error >> /tmp/minishell_output
    fi
    
    # Exécuter la même commande dans bash pour comparaison
    echo "$command" | bash > /tmp/bash_output 2>&1
    local bash_status=$?
    
    # Comparer les résultats
    if [ -n "$expected_status" ]; then
        if [ $minishell_status -eq $expected_status ]; then
            echo -e "${GREEN}✓ PASS${NC}"
            PASS_COUNT=$((PASS_COUNT + 1))
        else
            echo -e "${RED}✗ FAIL - Status attendu: $expected_status, obtenu: $minishell_status${NC}"
        fi
    else
        if diff /tmp/minishell_output /tmp/bash_output > /dev/null 2>&1; then
            echo -e "${GREEN}✓ PASS${NC}"
            PASS_COUNT=$((PASS_COUNT + 1))
        else
            echo -e "${RED}✗ FAIL - Sortie différente${NC}"
            echo "Minishell:"
            cat /tmp/minishell_output
            echo "Bash:"
            cat /tmp/bash_output
        fi
    fi
    echo ""
}

# Tests de base
echo -e "${YELLOW}=== TESTS DE BASE ===${NC}"

test_command "Echo simple" "echo Hello World"
test_command "Echo avec variable" "echo \$USER"
test_command "Echo avec PATH" "echo \$PATH"
test_command "PWD" "pwd"
test_command "ENV" "env | head -5"

# Tests de substitution de variables
echo -e "${YELLOW}=== TESTS DE VARIABLES ===${NC}"

test_command "Variable utilisateur" "echo \$USER"
test_command "Variable HOME" "echo \$HOME"
test_command "Variable inexistante" "echo \$NONEXISTENT"
test_command "Variable avec accolades" "echo \${USER}"
test_command "Exit status" "echo \$?"

# Tests de redirections
echo -e "${YELLOW}=== TESTS DE REDIRECTIONS ===${NC}"

test_command "Redirection sortie" "echo 'test' > /tmp/test_file && cat /tmp/test_file"
test_command "Redirection append" "echo 'ligne2' >> /tmp/test_file && cat /tmp/test_file"
test_command "Redirection entrée" "cat < /tmp/test_file"

# Tests de pipes
echo -e "${YELLOW}=== TESTS DE PIPES ===${NC}"

test_command "Pipe simple" "echo 'hello world' | cat"
test_command "Pipe avec grep" "echo -e 'ligne1\nligne2\nligne3' | grep ligne2"
test_command "Pipe multiple" "echo 'test' | cat | cat"

# Tests de commandes intégrées (builtins)
echo -e "${YELLOW}=== TESTS BUILTINS ===${NC}"

# Créer un répertoire de test
mkdir -p /tmp/minishell_test_Desktop
cd /tmp/minishell_test_Desktop

test_command "CD vers Desktop" "cd ~/Desktop && pwd"
test_command "CD retour" "cd - && pwd"
test_command "CD inexistant" "cd /nonexistent" 1

# Tests d'export et unset
test_command "Export variable" "export TEST_VAR=123 && echo \$TEST_VAR"
test_command "Unset variable" "unset TEST_VAR && echo \$TEST_VAR"

# Tests d'exit
test_command "Exit avec code" "exit 42" 42

# Tests de parsing complexes
echo -e "${YELLOW}=== TESTS DE PARSING ===${NC}"

test_command "Quotes simples" "echo 'Hello World'"
test_command "Quotes doubles" "echo \"Hello \$USER\""
test_command "Quotes mélangées" "echo \"Hello 'World'\""
test_command "Espaces multiples" "echo    hello    world"

# Tests d'erreurs
echo -e "${YELLOW}=== TESTS D'ERREURS ===${NC}"

test_command "Commande inexistante" "commandeInexistante" 127
test_command "Fichier inexistant" "cat fichier_inexistant" 1
test_command "Permission refusée" "cat /etc/shadow" 1

# Tests spécifiques à l'environnement madelha/Desktop
echo -e "${YELLOW}=== TESTS ENVIRONNEMENT MADELHA ===${NC}"

test_command "Utilisateur madelha" "whoami"
test_command "Chemin Desktop" "ls ~/Desktop | head -3"
test_command "Variable HOME madelha" "echo \$HOME | grep madelha"

# Tests de signaux (Ctrl+C simulation)
echo -e "${YELLOW}=== TESTS DE SIGNAUX ===${NC}"

echo -e "${BLUE}Ces tests nécessitent une interaction manuelle:${NC}"
echo ""

read -p "Voulez-vous tester les signaux interactivement? (y/n): " -n 1 -r
echo
if [[ $REPLY =~ ^[Yy]$ ]]; then
    test_interactive "Ctrl+C" "sleep 10 (puis appuyez sur Ctrl+C)"
    test_interactive "Ctrl+D" "(appuyez sur Ctrl+D pour quitter)"
    test_interactive "Ctrl+\\" "sleep 10 (puis appuyez sur Ctrl+\\)"
fi

# Nettoyage
rm -f /tmp/minishell_output /tmp/bash_output /tmp/test_file /tmp/minishell_error
rm -rf /tmp/minishell_test_Desktop

# Fonction pour tester interactivement (avec prompt visible)
test_interactive() {
    local test_name="$1"
    local command="$2"
    
    echo -e "${BLUE}Test interactif: $test_name${NC}"
    echo -e "${YELLOW}Tapez la commande suivante dans minishell:${NC}"
    echo -e "${GREEN}$command${NC}"
    echo ""
    echo "Appuyez sur Entrée pour lancer minishell..."
    read
    $MINISHELL
    echo ""
}

# Résultats finaux
echo -e "${BLUE}=== RÉSULTATS FINAUX ===${NC}"
echo -e "Tests passés: ${GREEN}$PASS_COUNT${NC}/$TEST_COUNT"

if [ $PASS_COUNT -eq $TEST_COUNT ]; then
    echo -e "${GREEN}🎉 Tous les tests sont passés!${NC}"
else
    echo -e "${RED}❌ Certains tests ont échoué${NC}"
fi

# Tests manuels recommandés
echo ""
echo -e "${YELLOW}=== TESTS MANUELS RECOMMANDÉS ===${NC}"
echo "Lancez ./minishell manuellement pour tester:"
echo "1. Vérifiez que le prompt 'Minishell\$>' s'affiche correctement"
echo "2. Testez l'historique avec les flèches haut/bas"
echo "3. Testez l'autocomplétion avec Tab"
echo "4. Testez les signaux (Ctrl+C, Ctrl+D, Ctrl+\\)"
echo "5. Testez avec des commandes longues et complexes"
echo "6. Testez les variables d'environnement personnalisées"
echo "7. Testez les pipes avec des commandes qui prennent du temps"
echo "8. Testez les redirections vers des fichiers sans permissions"
echo "9. Testez le comportement avec des commandes vides (juste Entrée)"
echo "10. Testez les espaces et tabulations en début/fin de commande"

echo ""
echo -e "${BLUE}Script terminé. Bonne chance pour votre évaluation! 🚀${NC}"