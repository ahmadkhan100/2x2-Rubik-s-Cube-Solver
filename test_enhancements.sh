#!/bin/bash

# Test script for 2x2 Rubik's Cube Solver enhancements
# This script tests the new features added to the project

echo "🧩 Testing 2x2 Rubik's Cube Solver Enhancements"
echo "================================================"

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Function to print colored output
print_status() {
    if [ $1 -eq 0 ]; then
        echo -e "${GREEN}✅ $2${NC}"
    else
        echo -e "${RED}❌ $2${NC}"
    fi
}

print_info() {
    echo -e "${BLUE}ℹ️  $1${NC}"
}

print_warning() {
    echo -e "${YELLOW}⚠️  $1${NC}"
}

# Test 1: Check if makefile builds correctly
echo
print_info "Test 1: Building project with enhanced makefile"
make clean > /dev/null 2>&1
if make all > /dev/null 2>&1; then
    print_status 0 "Makefile builds both solver and scrambler successfully"
else
    print_status 1 "Makefile build failed"
    exit 1
fi

# Test 2: Check if executables exist
echo
print_info "Test 2: Checking executable files"
if [ -f "./solver" ]; then
    print_status 0 "Solver executable exists"
else
    print_status 1 "Solver executable not found"
fi

if [ -f "./scrambler" ]; then
    print_status 0 "Scrambler executable exists"
else
    print_status 1 "Scrambler executable not found"
fi

# Test 3: Test scrambler functionality
echo
print_info "Test 3: Testing scrambler functionality"
if ./scrambler scramble 10 > /dev/null 2>&1; then
    print_status 0 "Scrambler generates scrambles successfully"
else
    print_status 1 "Scrambler failed to generate scrambles"
fi

# Test 4: Check Python wrapper
echo
print_info "Test 4: Testing Python wrapper"
if python3 --version > /dev/null 2>&1; then
    if python3 -c "import cube_solver_wrapper; print('Python wrapper imports successfully')" 2>/dev/null; then
        print_status 0 "Python wrapper imports without errors"
    else
        print_status 1 "Python wrapper has import errors"
    fi
else
    print_warning "Python3 not available, skipping Python wrapper test"
fi

# Test 5: Check web interface file
echo
print_info "Test 5: Checking web interface"
if [ -f "web_interface.html" ]; then
    # Basic HTML validation
    if grep -q "<!DOCTYPE html>" web_interface.html && grep -q "</html>" web_interface.html; then
        print_status 0 "Web interface HTML file is properly formatted"
    else
        print_status 1 "Web interface HTML file has formatting issues"
    fi
else
    print_status 1 "Web interface file not found"
fi

# Test 6: Check documentation
echo
print_info "Test 6: Checking documentation files"
if [ -f "ENHANCEMENTS.md" ]; then
    print_status 0 "Enhancement documentation exists"
else
    print_status 1 "Enhancement documentation not found"
fi

# Test 7: Test scrambler with different parameters
echo
print_info "Test 7: Testing scrambler with various parameters"
test_count=0
success_count=0

# Test different scramble lengths
for length in 5 10 15 20 25; do
    test_count=$((test_count + 1))
    if timeout 5s ./scrambler scramble $length > /dev/null 2>&1; then
        success_count=$((success_count + 1))
    fi
done

if [ $success_count -eq $test_count ]; then
    print_status 0 "Scrambler works with different scramble lengths"
else
    print_status 1 "Scrambler failed with some scramble lengths ($success_count/$test_count)"
fi

# Test 8: File permissions and executability
echo
print_info "Test 8: Checking file permissions"
if [ -x "./solver" ] && [ -x "./scrambler" ]; then
    print_status 0 "Executables have correct permissions"
else
    print_status 1 "Executables don't have execute permissions"
fi

# Test 9: Memory leak check (if valgrind is available)
echo
print_info "Test 9: Memory leak check (optional)"
if command -v valgrind > /dev/null 2>&1; then
    if timeout 10s valgrind --leak-check=summary --error-exitcode=1 ./scrambler scramble 5 > /dev/null 2>&1; then
        print_status 0 "No memory leaks detected in scrambler"
    else
        print_status 1 "Potential memory leaks detected"
    fi
else
    print_warning "Valgrind not available, skipping memory leak check"
fi

# Test 10: Code compilation with different flags
echo
print_info "Test 10: Testing compilation with different flags"
make clean > /dev/null 2>&1
if g++ -Wall -Wextra -std=c++11 -o test_solver solver.cpp row.cpp side.cpp cube.cpp > /dev/null 2>&1; then
    print_status 0 "Code compiles with strict warnings enabled"
    rm -f test_solver
else
    print_status 1 "Code has compilation warnings or errors"
fi

# Summary
echo
echo "🏁 Test Summary"
echo "==============="
print_info "All enhancement tests completed!"
print_info "Check the results above for any issues that need attention."

# Cleanup
echo
print_info "Cleaning up test files..."
make clean > /dev/null 2>&1

echo
print_info "To manually test the enhancements:"
echo "  1. Run 'make all' to build everything"
echo "  2. Try './scrambler' for interactive scramble generation"
echo "  3. Run 'python3 cube_solver_wrapper.py' for Python interface"
echo "  4. Open 'web_interface.html' in a web browser"
echo "  5. Read 'ENHANCEMENTS.md' for detailed documentation"

echo
echo "🎉 Enhancement testing complete!"

