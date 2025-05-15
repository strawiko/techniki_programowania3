import sys
import os

# Get absolute path to build directory
build_path = os.path.abspath(os.path.join(os.path.dirname(__file__), "build"))
lib_path = os.path.join(build_path, "lib")  # some builds put .so files in lib/

# Add both possible locations to Python path
sys.path.extend([build_path, lib_path])

try:
    # Try to import the specific module file
    
    import example
    
    # Test if import worked
    result = example.add()
    print(f"Success! Result of add(5,3): {result}")

except ImportError as e:
    print(f"Import error: {e}")
    # Show available .so files to help debug
    print("\nAvailable .so files in build directories:")
    for path in [build_path, lib_path]:
        if os.path.exists(path):
            files = [f for f in os.listdir(path) if f.endswith('.so')]
            print(f"\nIn {path}:")
            for f in files:
                print(f"  - {f}")