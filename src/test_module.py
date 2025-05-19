import sys
import os

# Get absolute path to build directory
build_path = os.path.abspath(os.path.join(os.path.dirname(__file__), '../build'))

# Add build directory to Python path (sys.path.append takes only one argument)
sys.path.append(build_path)

try:
    # Try to import the specific module file
    import example
    
    # Test if import worked
    result = example.add()
    print(f"Success! Result of add(): {result}")  # Removed 5,3 since add() takes no arguments
    
    # Print module location to verify correct import
    print(f"\nModule location: {example.__file__}")

except ImportError as e:
    print(f"Import error: {e}")
    # Show available .so files to help debug
    print("\nLooking for module in:", build_path)
    if os.path.exists(build_path):
        files = [f for f in os.listdir(build_path) if '.so' in f or '.pyd' in f]
        print("Files found:")
        for f in files:
            print(f"  - {f}")