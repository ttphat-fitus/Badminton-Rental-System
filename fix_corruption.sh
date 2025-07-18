#!/bin/bash

# Script to fix corrupted C++ files with [object Object] insertions

echo "Fixing corrupted C++ files..."

# Find all .cpp and .h files and fix common corruption patterns
find src/ -name "*.cpp" -o -name "*.h" | while read file; do
    echo "Fixing $file..."
    
    # Remove [object Object] corruption
    sed -i '' 's/\[object Object\]//g' "$file"
    
    # Fix missing quotes in strings
    sed -i '' 's/emit loginFailed(/emit loginFailed("/g' "$file"
    sed -i '' 's/emit registrationFailed(/emit registrationFailed("/g' "$file"
    sed -i '' 's/notify(/notify("/g' "$file"
    
    # Fix missing closing quotes and semicolons
    sed -i '' 's/);      return false;/");\'$'\n''        return false;/g' "$file"
    sed -i '' 's/);      /");\'$'\n''        /g' "$file"
    
    # Fix regex patterns
    sed -i '' 's/R(^/R"(^/g' "$file"
    sed -i '' 's/R(\[/R"([/g' "$file"
    sed -i '' 's/\$)");/\$)");/g' "$file"
    
    # Fix missing braces
    sed -i '' 's/) {$/") {/g' "$file"
    
    # Fix include statements
    sed -i '' 's/#include /#include "/g' "$file"
    sed -i '' 's/#include ""/#include </g' "$file"
    sed -i '' 's/\.h"/.h"/g' "$file"
    
done

echo "Corruption fix completed!"
