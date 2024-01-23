#!/bin/bash

# Set the path to the test directory
TESTDIR=/test

# Create the test directory if it doesn't exist
mkdir -p ".$TESTDIR"

# Include the tests from the external file
source ./tests.sh

# Function to run a command and save the output
run_and_save() {
    TEST_NAME=$1
    COMMANDS=$2

    echo "Running command for $TEST_NAME"
    $COMMANDS > $TESTDIR/${TEST_NAME}_output
}

# Run the tests
for test_name in "${test_names[@]}"; do
    run_and_save $test_name "./minishell -c ${!test_name}"
done

# Compare Bash and minishell outputs
for test_name in "${test_names[@]}"; do
    echo "Comparing outputs for $test_name"
    diff $TESTDIR/${test_name}_expected_output $TESTDIR/${test_name}_minishell_output -s
done


echo "Expected output files generated and compared successfully."
