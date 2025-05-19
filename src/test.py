import sys
import os


print(os.listdir('../build/Debug'))
sys.path.append('../build/Debug')  # lub 'build/Debug' jeśli tam jest plik
import example

print(example.add())