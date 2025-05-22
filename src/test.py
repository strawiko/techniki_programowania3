import sys
import os
import platform

# Get absolute path to build directory
build_path = os.path.abspath(os.path.join(os.path.dirname(__file__), '../build'))

# Check operating system
system = platform.system()
if system == 'Windows':
    # Add Debug directory for Windows builds
    build_path = os.path.join(build_path, 'Debug')
    module_extension = '.pyd'
else:
    # For Linux/Mac
    module_extension = '.so'

# Add build directory to Python path
sys.path.append(build_path)

try:
    # Try to import the specific module
    import example

# Create signal object
    signal1 = example.Signal(3.0, 0.0, 1.0, "sin")
    plot = example.plot_signal(signal1)
    # Test if import worked
    result = example.add()
    print(f"Success! Result of add(): {result}")
    print(f"Running on: {system}")
    print(f"\nModule location: {example.__file__}")

except ImportError as e:
    print(f"Import error: {e}")
    print(f"Running on: {system}")
    print("\nLooking for module in:", build_path)
    if os.path.exists(build_path):
        files = [f for f in os.listdir(build_path) if module_extension in f]
        print("Files found:")
        for f in files:
            print(f"  - {f}")
    else:
        print(f"Build directory not found: {build_path}")