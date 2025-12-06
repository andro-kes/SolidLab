#!/bin/bash

# Test script for Dungeon Editor

cd "$(dirname "$0")/build"

# Create a test input file
cat > /tmp/test_input.txt << 'EOF'
1
Orc
Grom
100
100
1
Bear
Bruno
120
110
1
Squirrel
Chip
130
105
1
Orc
Gruk
200
200
2
3
dungeon_save.txt
5
2
6
EOF

echo "=== Running Dungeon Editor Test ==="
./dungeon_editor < /tmp/test_input.txt

echo ""
echo "=== Checking saved file ==="
if [ -f dungeon_save.txt ]; then
    cat dungeon_save.txt
fi

echo ""
echo "=== Checking log file ==="
if [ -f log.txt ]; then
    cat log.txt
fi
