#!/usr/bin/env bash
LOG_DIR=log
mkdir -p "$LOG_DIR"

VALID_LOG="$LOG_DIR/00_test_valid_map.log"
INVALID_LOG="$LOG_DIR/01_test_invalid_map.log"
NYAN_SUCCESS_LOG="$LOG_DIR/02_test_nyan_success.log"
NYAN_FAILED_LOG="$LOG_DIR/03_test_nyan_failed.log"
NYAN_AMBIGUOUS_LOG="$LOG_DIR/04_test_nyan_ambiguous.log"

: > "$VALID_LOG"
: > "$INVALID_LOG"
: > "$NYAN_SUCCESS_LOG"
: > "$NYAN_FAILED_LOG"
: > "$NYAN_AMBIGUOUS_LOG"

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

echo "===== NYAN: SUCCESS =====" | tee -a "$NYAN_SUCCESS_LOG"
find nyan_map/Success -name '*.cub' | sort | while read -r f; do
    run_test "$f" "$NYAN_SUCCESS_LOG"
done

echo "===== NYAN: FAILED =====" | tee -a "$NYAN_FAILED_LOG"
find nyan_map/Failed -name '*.cub' | sort | while read -r f; do
    run_test "$f" "$NYAN_FAILED_LOG"
done

echo "===== NYAN: AMBIGUOUS =====" | tee -a "$NYAN_AMBIGUOUS_LOG"
find nyan_map/Ambiguous -name '*.cub' | sort | while read -r f; do
    run_test "$f" "$NYAN_AMBIGUOUS_LOG"
done
