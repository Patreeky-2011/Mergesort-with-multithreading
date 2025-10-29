#!/bin/bash
# Run functional correctness tests for parallel mergesort

EXEC=./test-mergesort
SEED=42

# ensure executable exists first
if [ ! -f "$EXEC" ]; then
  echo "error: $EXEC not found. please run 'make' first."
  exit 1
fi

# test sizes and cutoff levels
sizes=(2 10 1000 100000 1000000 100000000)
cutoffs=(0 1 2 3 4 5 6 7 8)

echo "RUNNING CORRECTNESS + PERFORMANCE TESTS"
for n in "${sizes[@]}"; do
  for c in "${cutoffs[@]}"; do
    echo -n "Test: n=$n cutoff=$c ... "
    output=$($EXEC "$n" "$c" "$SEED" 2>&1)
    if echo "$output" | grep -q "sorting failed"; then
      echo "FAILED | Output: $output"
    else
      echo "PASSED | Output: $output"
    fi
  done
done

echo -e "\nALL TESTS COMPLETE."
