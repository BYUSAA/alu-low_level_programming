#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "$0")/../.." && pwd)"
PROJECT_ROOT="$ROOT/Project_2"
RESULTS="$PROJECT_ROOT/test-results"
BUILD="$(mktemp -d)"
trap 'rm -rf "$BUILD"' EXIT
mkdir -p "$RESULTS"

P1="$PROJECT_ROOT/project_1_academic_analysis"
P2="$PROJECT_ROOT/project_2_text_mining"
P3="$PROJECT_ROOT/project_3_iot_monitoring"

echo "[1/6] Compiling Project 1..."
gcc -std=c99 -Wall -Wextra -Werror -pedantic "$P1/main.c" -o "$BUILD/academic_analysis"
echo "[2/6] Compiling Project 2..."
gcc -std=c99 -Wall -Wextra -Werror -pedantic "$P2/main.c" -o "$BUILD/text_mining"
echo "[3/6] Compiling Project 3..."
gcc -std=c99 -Wall -Wextra -Werror -pedantic "$P3/main.c" -o "$BUILD/iot_monitor"

echo "[4/6] Project 1 add/remove/summary..."
printf '1\n811299999\nSmoke Test Student\nC Programming\nnan\ninf\n-inf\n101\n88\n2\n7\n811299999\n9\n10\n' \
  | "$BUILD/academic_analysis" > "$RESULTS/project1.log"
test "$(grep -c "Grade must be a number from 0 to 100." "$RESULTS/project1.log")" -eq 4
grep -q "Student added." "$RESULTS/project1.log"
grep -q "Student removed." "$RESULTS/project1.log"
grep -q "ACADEMIC SUMMARY" "$RESULTS/project1.log"

echo "[5/6] Project 2 source-text/summary/address..."
{
  sed -n '/^It was/,$p' "$P2/source_text.txt"
  printf '.\n7\n8\n9\n'
} | "$BUILD/text_mining" > "$RESULTS/project2.log"
grep -Eq 'Input contains [1-9][0-9]+ words' "$RESULTS/project2.log"
grep -q "TEXT SUMMARY" "$RESULTS/project2.log"
grep -q "Text buffer address:" "$RESULTS/project2.log"
grep -q "Word statistics array:" "$RESULTS/project2.log"
grep -q "Selected word-stat entry:" "$RESULTS/project2.log"

echo "[6/6] Project 3 registration/callback/alert/removal..."
printf '1\n2001\nRoom Temperature Sensor\n1\n1\n2002\nWater Pressure Sensor\n2\n1\n2003\nBattery Monitor\n3\n5\n6\n7\n3\n2003\n2\n8\n' \
  | "$BUILD/iot_monitor" > "$RESULTS/project3.log"
grep -q "Simulating 10 readings" "$RESULTS/project3.log"
grep -q "callback: temperature_monitor" "$RESULTS/project3.log"
grep -q "callback: pressure_monitor" "$RESULTS/project3.log"
grep -q "callback: battery_monitor" "$RESULTS/project3.log"
grep -q "CUSTOM CALLBACK ALERT" "$RESULTS/project3.log"
grep -q "Device status set to ALERT" "$RESULTS/project3.log"
grep -q "Device removed." "$RESULTS/project3.log"
grep -q "IOT MONITORING SUMMARY" "$RESULTS/project3.log"

echo "All Project 2 smoke checks passed."
echo "Logs saved in Project_2/test-results/."
