#!/usr/bin/env bash
LOG_DIR=log
mkdir -p "$LOG_DIR"

VALID_LOG="$LOG_DIR/00_test_valid_map.log"
INVALID_LOG="$LOG_DIR/01_test_invalid_map.log"

: > "$VALID_LOG"
: > "$INVALID_LOG"

run_test() {
    FILE=$1
    LOGFILE=$2

    echo "==================================" | tee -a "$LOGFILE"
    echo "=== $FILE ===" | tee -a "$LOGFILE"
    echo "==================================" | tee -a "$LOGFILE"

    valgrind --leak-check=full --quiet --error-exitcode=1 \
        ./autotest "$FILE" 2>&1 | tee -a "$LOGFILE"

    echo "" | tee -a "$LOGFILE"
}

echo "===== VALID MAPS =====" | tee -a "$VALID_LOG"
for f in maps/valid/*.cub; do
    run_test "$f" "$VALID_LOG"
done

echo "===== INVALID MAPS =====" | tee -a "$INVALID_LOG"
for f in maps/invalid/*.cub; do
    run_test "$f" "$INVALID_LOG"
done
