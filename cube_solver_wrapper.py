#!/usr/bin/env python3
"""
Python wrapper for the 2x2 Rubik's Cube Solver
Provides a more user-friendly interface to the C++ solver
"""

import subprocess
import sys
import os
import random
from typing import List, Dict, Tuple
import json

class CubeSolverWrapper:
    """Python wrapper for the C++ 2x2 Rubik's Cube Solver"""
    
    # Color mappings
    COLORS = {
        'w': 0, 'white': 0,
        'r': 1, 'red': 1,
        'b': 2, 'blue': 2,
        'o': 3, 'orange': 3,
        'g': 4, 'green': 4,
        'y': 5, 'yellow': 5
    }
    
    COLOR_NAMES = ['white', 'red', 'blue', 'orange', 'green', 'yellow']
    COLOR_CHARS = ['w', 'r', 'b', 'o', 'g', 'y']
    
    def __init__(self, solver_path: str = "./solver"):
        """Initialize the wrapper with path to the compiled solver"""
        self.solver_path = solver_path
        self._check_solver_exists()
    
    def _check_solver_exists(self):
        """Check if the solver executable exists"""
        if not os.path.exists(self.solver_path):
            raise FileNotFoundError(f"Solver executable not found at {self.solver_path}. Please compile first with 'make'")
    
    def generate_scrambled_cube(self, num_moves: int = 20) -> Dict[str, List[List[str]]]:
        """
        Generate a scrambled cube state
        
        Args:
            num_moves: Number of random moves to apply
            
        Returns:
            Dictionary representing the cube state
        """
        # Start with solved cube
        cube_state = {
            'up': [['w', 'w'], ['w', 'w']],
            'right': [['r', 'r'], ['r', 'r']],
            'left': [['o', 'o'], ['o', 'o']],
            'front': [['g', 'g'], ['g', 'g']],
            'back': [['b', 'b'], ['b', 'b']],
            'down': [['y', 'y'], ['y', 'y']]
        }
        
        # Apply random moves
        moves = ['U', "U'", 'U2', 'R', "R'", 'R2', 'L', "L'", 'L2', 
                'F', "F'", 'F2', 'B', "B'", 'B2', 'D', "D'", 'D2']
        
        scramble = []
        for _ in range(num_moves):
            move = random.choice(moves)
            scramble.append(move)
            # Note: For a complete implementation, we'd need to simulate the moves
            # For now, this returns a template that can be manually set
        
        return {
            'cube_state': cube_state,
            'scramble_sequence': scramble
        }
    
    def validate_cube_input(self, cube_input: str) -> bool:
        """
        Validate that cube input contains valid colors
        
        Args:
            cube_input: String of 24 characters representing cube state
            
        Returns:
            True if valid, False otherwise
        """
        if len(cube_input) != 24:
            return False
        
        color_count = {color: 0 for color in self.COLOR_CHARS}
        
        for char in cube_input.lower():
            if char not in self.COLOR_CHARS:
                return False
            color_count[char] += 1
        
        # Each color should appear exactly 4 times on a 2x2 cube
        return all(count == 4 for count in color_count.values())
    
    def format_cube_display(self, cube_state: Dict) -> str:
        """
        Format cube state for display
        
        Args:
            cube_state: Dictionary representing cube state
            
        Returns:
            Formatted string representation
        """
        display = []
        display.append("    " + " ".join(cube_state['up'][0]))
        display.append("    " + " ".join(cube_state['up'][1]))
        display.append("")
        
        # Middle row with left, front, right, back
        display.append(" ".join(cube_state['left'][0]) + " " + 
                      " ".join(cube_state['front'][0]) + " " +
                      " ".join(cube_state['right'][0]) + " " +
                      " ".join(cube_state['back'][0]))
        display.append(" ".join(cube_state['left'][1]) + " " + 
                      " ".join(cube_state['front'][1]) + " " +
                      " ".join(cube_state['right'][1]) + " " +
                      " ".join(cube_state['back'][1]))
        display.append("")
        display.append("    " + " ".join(cube_state['down'][0]))
        display.append("    " + " ".join(cube_state['down'][1]))
        
        return "\n".join(display)
    
    def solve_interactive(self):
        """Run the solver in interactive mode"""
        try:
            subprocess.run([self.solver_path], check=True)
        except subprocess.CalledProcessError as e:
            print(f"Error running solver: {e}")
        except KeyboardInterrupt:
            print("\nSolver interrupted by user")
    
    def get_solution_steps(self, cube_input: str) -> List[str]:
        """
        Get solution steps for a given cube state
        Note: This would require modifying the C++ code to output machine-readable format
        
        Args:
            cube_input: String representation of cube state
            
        Returns:
            List of solution steps
        """
        # This is a placeholder - would need C++ modifications for full implementation
        print("Note: This feature requires modifications to the C++ solver")
        print("to output machine-readable solution steps")
        return []

def main():
    """Main function for command-line usage"""
    wrapper = CubeSolverWrapper()
    
    if len(sys.argv) > 1:
        if sys.argv[1] == "scramble":
            num_moves = int(sys.argv[2]) if len(sys.argv) > 2 else 20
            scrambled = wrapper.generate_scrambled_cube(num_moves)
            print("Scramble sequence:", " ".join(scrambled['scramble_sequence']))
            print("\nCube state:")
            print(wrapper.format_cube_display(scrambled['cube_state']))
        
        elif sys.argv[1] == "validate":
            if len(sys.argv) > 2:
                is_valid = wrapper.validate_cube_input(sys.argv[2])
                print(f"Cube input is {'valid' if is_valid else 'invalid'}")
            else:
                print("Please provide cube input to validate")
        
        elif sys.argv[1] == "solve":
            wrapper.solve_interactive()
        
        else:
            print("Usage: python cube_solver_wrapper.py [scramble|validate|solve]")
    else:
        # Interactive mode
        print("2x2 Rubik's Cube Solver - Python Wrapper")
        print("1. Generate scrambled cube")
        print("2. Solve cube (interactive)")
        print("3. Validate cube input")
        
        choice = input("Enter choice (1-3): ")
        
        if choice == "1":
            num_moves = input("Number of scramble moves (default 20): ")
            num_moves = int(num_moves) if num_moves.isdigit() else 20
            scrambled = wrapper.generate_scrambled_cube(num_moves)
            print("Scramble sequence:", " ".join(scrambled['scramble_sequence']))
            print("\nCube state:")
            print(wrapper.format_cube_display(scrambled['cube_state']))
        
        elif choice == "2":
            wrapper.solve_interactive()
        
        elif choice == "3":
            cube_input = input("Enter 24-character cube state: ")
            is_valid = wrapper.validate_cube_input(cube_input)
            print(f"Cube input is {'valid' if is_valid else 'invalid'}")

if __name__ == "__main__":
    main()

