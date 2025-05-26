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
    def wypiszelementy(tablica):
        print("wybbierz sygnał do wyświetlenia:")
        if type(tablica[0]) == example.Signal:
            for i, element in enumerate(tablica):
                print(f"sygnał[{i}]\n")
        elif type(tablica[0]) == example.Fourier:
                for i, element in enumerate(tablica):
                    print(f"Fourier[{i}]\n")
        else:
            print("Nieznany typ tablicy lub brak elementow")
        return int(input())


# Create signal object
    freaquency = float(input("podaj częstotliwość sygnału: "))
    start = float(input("podaj moment rozpoczęcia: "))
    end = float(input("podaj moment zakończenia: "))
    signal_type = input("podaj typ sygnału (sin,cos, kwadrat, pila): ")
    signallist = []
    signallist.append(example.Signal(freaquency, start, end, signal_type))
    fourierlist = []
    wybor = input("podaj wybór (g - generuj drugi sygnał, f - filtruj, p - plotuj, dft - transformata Fouriera, rdft - odwrotna transformata Fouriera): ")
    while wybor!="q":
        if wybor == "g":
            freaquency = float(input("podaj częstotliwość sygnału: "))
            start = float(input("podaj moment rozpoczęcia: "))
            end = float(input("podaj moment zakończenia: "))
            signal_type = input("podaj typ sygnału (sin,cos, kwadrat, pila): ")
            signallist.append(example.Signal(freaquency, start, end, signal_type))
        elif wybor == "f":
            filter_type = input("podaj typ filtru (lowpass, highpass): ")
            cutoff_frequency = float(input("podaj częstotliwość odcięcia: "))
            filtered_signal = example.filter_signal(wypiszelementy(signallist), filter_type, cutoff_frequency)
            plot = example.plot_signal(filtered_signal)
        elif wybor == "p":
            print("Wybierz sygnał do wyświetlenia:")
            example.plot_signal(signallist[wypiszelementy(signallist)])
        elif wybor == "pf":
            print("wybierz transformację Fouriera do wyświetlenia:")
            example.plot_fourier(fourierlist[wypiszelementy(fourierlist)])
        elif wybor == "dft":
            fourierlist.append(example.Fourier(signallist[wypiszelementy(signallist)]))
        elif wybor == "rdft":
            indekswyboru = wypiszelementy(fourierlist)
            #example.N/(fourierlist[indekswyboru].t_end-fourierlist[indekswyboru].t_start)
            signallist.append(example.Signal(3.4, fourierlist[indekswyboru].t_start, fourierlist[indekswyboru].t_end, "rdft",fourierlist[indekswyboru]))
            print("czestotliwość sygnału:", signallist[len(signallist)-1].frequency)
        else:
            print("Nieznany wybór. Spróbuj ponownie.")
        wybor = input("podaj wybór (g - generuj, f - filtruj, p - plotuj, dft - transformata Fouriera, rdft - odwrotna transformata Fouriera): ")
        # Test if import worked
        # result = example.add()
        # print(f"Success! Result of add(): {result}")
        # print(f"Running on: {system}")
        # print(f"\nModule location: {example.__file__}")

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