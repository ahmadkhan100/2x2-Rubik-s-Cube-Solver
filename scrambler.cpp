#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <ctime>
#include <algorithm>
#include "cube.h"

using namespace std;

/**
 * Cube Scrambler Utility
 * Generates random scrambles for testing the 2x2 Rubik's Cube Solver
 */

class CubeScrambler {
private:
    vector<string> moves = {"U", "U'", "U2", "R", "R'", "R2", "L", "L'", "L2", 
                           "F", "F'", "F2", "B", "B'", "B2", "D", "D'", "D2"};
    mt19937 rng;
    
public:
    CubeScrambler() : rng(time(nullptr)) {}
    
    /**
     * Generate a random scramble sequence
     * @param length Number of moves in the scramble
     * @param avoid_redundant Avoid consecutive moves on the same face
     * @return Vector of move strings
     */
    vector<string> generateScramble(int length, bool avoid_redundant = true) {
        vector<string> scramble;
        string last_face = "";
        
        uniform_int_distribution<int> dist(0, moves.size() - 1);
        
        for (int i = 0; i < length; i++) {
            string move;
            string current_face;
            
            do {
                move = moves[dist(rng)];
                current_face = move.substr(0, 1);
            } while (avoid_redundant && current_face == last_face && i > 0);
            
            scramble.push_back(move);
            last_face = current_face;
        }
        
        return scramble;
    }
    
    /**
     * Apply a scramble to a cube
     * @param cube Reference to the cube to scramble
     * @param scramble Vector of moves to apply
     */
    void applyScramble(Cube& cube, const vector<string>& scramble) {
        for (const string& move : scramble) {
            applyMove(cube, move);
        }
    }
    
    /**
     * Apply a single move to the cube
     * @param cube Reference to the cube
     * @param move Move string (e.g., "R", "U'", "F2")
     */
    void applyMove(Cube& cube, const string& move) {
        if (move == "U") cube.U();
        else if (move == "U'") cube.Up();
        else if (move == "U2") cube.U2();
        else if (move == "R") cube.R();
        else if (move == "R'") cube.Rp();
        else if (move == "R2") cube.R2();
        else if (move == "L") cube.L();
        else if (move == "L'") cube.Lp();
        else if (move == "L2") cube.L2();
        else if (move == "F") cube.F();
        else if (move == "F'") cube.Fp();
        else if (move == "F2") cube.F2();
        else if (move == "B") cube.B();
        else if (move == "B'") cube.Bp();
        else if (move == "B2") cube.B2();
        else if (move == "D") cube.D();
        else if (move == "D'") cube.Dp();
        else if (move == "D2") cube.D2();
        else {
            cerr << "Unknown move: " << move << endl;
        }
    }
    
    /**
     * Generate a scrambled cube state
     * @param scramble_length Number of moves to apply
     * @return Scrambled cube
     */
    Cube generateScrambledCube(int scramble_length = 20) {
        Cube cube;
        // Initialize solved cube (you may need to modify this based on your Cube constructor)
        cube.set(0, 0, 0, 0, 0); // up - white
        cube.set(1, 1, 1, 1, 1); // right - red  
        cube.set(2, 3, 3, 3, 3); // left - orange
        cube.set(3, 4, 4, 4, 4); // front - green
        cube.set(4, 2, 2, 2, 2); // back - blue
        cube.set(5, 5, 5, 5, 5); // down - yellow
        
        vector<string> scramble = generateScramble(scramble_length);
        applyScramble(cube, scramble);
        
        cout << "Scramble applied: ";
        for (const string& move : scramble) {
            cout << move << " ";
        }
        cout << endl;
        
        return cube;
    }
    
    /**
     * Print scramble in standard notation
     * @param scramble Vector of moves
     */
    void printScramble(const vector<string>& scramble) {
        cout << "Scramble: ";
        for (size_t i = 0; i < scramble.size(); i++) {
            cout << scramble[i];
            if (i < scramble.size() - 1) cout << " ";
        }
        cout << endl;
    }
    
    /**
     * Generate multiple scrambles for testing
     * @param count Number of scrambles to generate
     * @param length Length of each scramble
     */
    void generateMultipleScrambles(int count, int length = 20) {
        cout << "Generating " << count << " scrambles of length " << length << ":" << endl;
        cout << "================================================" << endl;
        
        for (int i = 1; i <= count; i++) {
            vector<string> scramble = generateScramble(length);
            cout << "Scramble " << i << ": ";
            for (const string& move : scramble) {
                cout << move << " ";
            }
            cout << endl;
        }
    }
};

/**
 * Performance testing function
 */
void performanceTest(int num_tests = 100) {
    CubeScrambler scrambler;
    cout << "Running performance test with " << num_tests << " scrambled cubes..." << endl;
    
    clock_t start_time = clock();
    int successful_solves = 0;
    
    for (int i = 0; i < num_tests; i++) {
        try {
            Cube scrambled_cube = scrambler.generateScrambledCube(25);
            // Here you would call your solver function
            // For now, we'll just assume it works
            successful_solves++;
            
            if ((i + 1) % 10 == 0) {
                cout << "Completed " << (i + 1) << " tests..." << endl;
            }
        } catch (const exception& e) {
            cerr << "Error in test " << (i + 1) << ": " << e.what() << endl;
        }
    }
    
    clock_t end_time = clock();
    double elapsed_time = double(end_time - start_time) / CLOCKS_PER_SEC;
    
    cout << "Performance Test Results:" << endl;
    cout << "========================" << endl;
    cout << "Tests completed: " << successful_solves << "/" << num_tests << endl;
    cout << "Total time: " << elapsed_time << " seconds" << endl;
    cout << "Average time per test: " << (elapsed_time / num_tests) << " seconds" << endl;
}

int main(int argc, char* argv[]) {
    CubeScrambler scrambler;
    
    if (argc == 1) {
        // Interactive mode
        cout << "2x2 Rubik's Cube Scrambler" << endl;
        cout << "==========================" << endl;
        cout << "1. Generate single scramble" << endl;
        cout << "2. Generate multiple scrambles" << endl;
        cout << "3. Generate scrambled cube state" << endl;
        cout << "4. Run performance test" << endl;
        cout << "Enter choice (1-4): ";
        
        int choice;
        cin >> choice;
        
        switch (choice) {
            case 1: {
                cout << "Enter scramble length (default 20): ";
                int length;
                cin >> length;
                if (length <= 0) length = 20;
                
                vector<string> scramble = scrambler.generateScramble(length);
                scrambler.printScramble(scramble);
                break;
            }
            case 2: {
                cout << "Enter number of scrambles: ";
                int count;
                cin >> count;
                cout << "Enter scramble length (default 20): ";
                int length;
                cin >> length;
                if (length <= 0) length = 20;
                
                scrambler.generateMultipleScrambles(count, length);
                break;
            }
            case 3: {
                cout << "Enter scramble length (default 20): ";
                int length;
                cin >> length;
                if (length <= 0) length = 20;
                
                Cube scrambled = scrambler.generateScrambledCube(length);
                cout << "Scrambled cube generated. Current state:" << endl;
                scrambled.displayCube();
                break;
            }
            case 4: {
                cout << "Enter number of tests (default 100): ";
                int tests;
                cin >> tests;
                if (tests <= 0) tests = 100;
                
                performanceTest(tests);
                break;
            }
            default:
                cout << "Invalid choice." << endl;
        }
    } else if (argc == 2) {
        // Command line mode
        string command = argv[1];
        
        if (command == "scramble") {
            vector<string> scramble = scrambler.generateScramble(20);
            scrambler.printScramble(scramble);
        } else if (command == "test") {
            performanceTest(50);
        } else {
            cout << "Usage: " << argv[0] << " [scramble|test]" << endl;
        }
    } else if (argc == 3) {
        string command = argv[1];
        int param = atoi(argv[2]);
        
        if (command == "scramble") {
            vector<string> scramble = scrambler.generateScramble(param);
            scrambler.printScramble(scramble);
        } else if (command == "multiple") {
            scrambler.generateMultipleScrambles(param);
        } else if (command == "test") {
            performanceTest(param);
        }
    }
    
    return 0;
}

