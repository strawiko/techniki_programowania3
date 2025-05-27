import sys
import os
import platform
#prawie pseudokod a działa
# szuka ścieżki do katalogu build
build_path = os.path.abspath(os.path.join(os.path.dirname(__file__), '../build'))

# chyba jasne
system = platform.system()
if system == 'Windows':
    # folder na debug
    build_path = os.path.join(build_path, 'Debug')
    module_extension = '.pyd'
else:
    #wersja linuxowa
    module_extension = '.so'

# kolejne dir
sys.path.append(build_path)

try:
    # pobiera z c++
    import example
    def wypiszelementy(tablica):
        print("wybierz sygnał: ")
        if type(tablica[0]) == example.Signal:
            for i, element in enumerate(tablica):
                print(f"sygnał[{i}]\n")
        elif type(tablica[0]) == example.Fourier:
                for i, element in enumerate(tablica):
                    print(f"Fourier[{i}]\n")
        else:
            print("Nieznany typ tablicy lub brak elementow")
        return int(input())


# obiekt sygnał
    freaquency = float(input("podaj częstotliwość sygnału: "))
    start = float(input("podaj moment rozpoczęcia: "))
    end = float(input("podaj moment zakończenia: "))
    signal_type = input("podaj typ sygnału (sin,cos, kwadrat, pila): ")
    signallist = []
    signallist.append(example.Signal(freaquency, start, end, signal_type))
    fourierlist = []
    wybor = input("podaj wybór (g - generuj drugi sygnał, f - filtruj, p - plotuj, pf- plotuj transformaty, dft - transformata Fouriera, rdft - odwrotna transformata Fouriera): ")
    while wybor!="q": #wielkie menu tylko że to pyton
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
            signallist.append(example.Signal(fourierlist[indekswyboru].t_start, fourierlist[indekswyboru].t_end, "rdft",fourierlist[indekswyboru]))
            print("Odwrotna transformata Fouriera została dodana do listy sygnałów.")
        else:
            print("Nieznany wybór. Spróbuj ponownie.")
        wybor = input("podaj wybór (g - generuj, f - filtruj, p - plotuj, dft - transformata Fouriera, rdft - odwrotna transformata Fouriera): ")
        # sprawdź czy działa

except ImportError as e:#debug
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