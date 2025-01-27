#!/usr/bin/env python3

import os
import subprocess
import sys

def run_tests():
    """Run all tests and return success status."""
    build_dir = "build"
    if not os.path.exists(build_dir):
        print("Error: Build directory not found. Run cmake first.")
        return False
        
    # Run CTest
    result = subprocess.run(["ctest", "--output-on-failure"],
                          cwd=build_dir,
                          capture_output=True,
                          text=True)
                          
    print(result.stdout)
    if result.stderr:
        print(result.stderr, file=sys.stderr)
        
    return result.returncode == 0

if __name__ == "__main__":
    success = run_tests()
    sys.exit(0 if success else 1)
