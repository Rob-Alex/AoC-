#!/usr/bin/env bash
set -euo pipefail

DAY=""

while [[ $# -gt 0 ]]; do
  case "$1" in
    --day|-d)
      DAY="$2"
      shift 2
      ;;
    *)
      echo "Unknown arg: $1"
      exit 1
      ;;
  esac
done

if [[ -z "$DAY" ]]; then
  # default: this ueses the current day (1–25) but 2025 is only 12 days...
  DAY=$(date +%d)
fi

# normalizes to two digits
DAY=$(printf "%02d" "$DAY")

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
SRC_DIR="$ROOT_DIR/src"
INPUT_DIR="$ROOT_DIR/inputs"

CPP_FILE="$SRC_DIR/day${DAY}.cpp"
INPUT_FILE="$INPUT_DIR/day${DAY}.txt"

mkdir -p "$SRC_DIR" "$INPUT_DIR"

if [[ -e "$CPP_FILE" ]]; then
  echo "Source file $CPP_FILE already exists, not overwriting."
else
  cat > "$CPP_FILE" <<EOF
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  printf("Day ${DAY}");
    // Part 1:


    // Part 2:


    return 0;
}
EOF
  echo "Created $CPP_FILE"
fi

if [[ ! -e "$INPUT_FILE" ]]; then
  touch "$INPUT_FILE"
  echo "Created $INPUT_FILE"
fi

echo "USe build and run:"
echo "  make DAY=${DAY} run"

