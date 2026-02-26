#!/bin/bash

MINISHELL=./minishell
TMP_MINI=$(mktemp)
TMP_BASH=$(mktemp)
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

# Liste des cas de test
TESTS=(
  "echo hello"
  "ls -l"
  "echo 'hello world'"
  "echo \"hello world\""
  "echo \$HOME"
  "echo \$UNDEFINED_VAR"
  "ls | grep minishell"
  "echo hello > testfile && cat testfile"
  "cat < testfile"
  "cat << EOF\nhello\nEOF"
  "echo \"\$USER\"abc"
  "echo 'it'\''s ok'"
  "    ls    -a   "
  "echo hello | cat | wc -l"
  "> out.txt"
  "echo \"unterminated"
)

echo "🧪 Démarrage des tests de parsing..."

for TEST in "${TESTS[@]}"; do
  # Préparation : remplacer les '\n' par vrais sauts de ligne pour les heredocs
  CMD=$(echo -e "$TEST")

  echo -n "Test: \"$CMD\" ... "

  # Exécution minishell
  echo -e "$CMD" | $MINISHELL > "$TMP_MINI" 2>&1
  # Exécution bash
  echo -e "$CMD" | bash > "$TMP_BASH" 2>&1

  # Comparaison
  if diff -q "$TMP_MINI" "$TMP_BASH" >/dev/null; then
    echo -e "${GREEN}OK${NC}"
  else
    echo -e "${RED}KO${NC}"
    echo "--- 💡 Commande : $CMD"
    echo "--- 🔎 bash    :"
    cat "$TMP_BASH"
    echo "--- 🐚 minishell :"
    cat "$TMP_MINI"
    echo ""
  fi
done

# Nettoyage
rm "$TMP_MINI" "$TMP_BASH"

