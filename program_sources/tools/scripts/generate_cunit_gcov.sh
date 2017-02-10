#!/bin/sh

# Check if the needed files exist
if [ ! -f `find test/cunit -name *.gcno` ]; then
    echo "ERROR: No gcno files found. Execute the test binary file before running this script."
    echo "This script should be launched from the build directory"
    exit 0
fi

# Print statistics on the screen
gcov `find test/cunit -name *.gcno`

## Delete all gcda files
#lcov --directory test/cunit -zerocounters

# Generate the html files and the reports
lcov --directory test/cunit --capture --output-file app.info
genhtml app.info
