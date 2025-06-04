#!/bin/bash

if [ $# -ne 5 ]; then
  echo "Usage: $0 N_PHILOSOPHERS TIME_TO_DIE TIME_TO_EAT TIME_TO_SLEEP MEALS_REQUIRED"
  exit 1
fi

N="$1"
MEALS_REQUIRED="$5"
ok=true
COLOR_R="\033[31m"
COLOR_G="\033[32m"
C_RESET="\033[0m"

./philo_bonus "$@" > .log

for ((i = 1; i <= N; i++)); do
  COUNT=$(grep "Philosopher $i" .log | grep "is eating" | wc -l)
  if [ "$COUNT" -lt "$MEALS_REQUIRED" ]; then
    ok=false
  fi
  echo "Philosopher $i has eaten $COUNT times"
done

# rm -f .log

if [ "$ok" = true ]; then
  echo -e "${COLOR_G} [OK]${C_RESET}"
else
  echo -e "${COLOR_R} [KO]${C_RESET}"
fi