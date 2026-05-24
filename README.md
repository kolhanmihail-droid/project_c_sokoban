# 📦 Sokoban - Projekt w C (Wersja z GUI)

Projekt semestralny z przedmiotu Programowanie Niskopoziomowe w C. Jest to w pełni funkcjonalny klon klasycznej gry logicznej Sokoban, wykorzystujący bibliotekę SDL2 do obsługi interfejsu graficznego. 

Gra spełnia wszystkie wymagania techniczne dla projektu na ocenę 5.0.

## 🌟 Główne funkcjonalności (Zrealizowane Wymagania)
- **Modularna Architektura:** Kod podzielony na moduły logiki, operacji plikowych i GUI.
- **Dynamiczne Zarządzanie Pamięcią:** Dynamiczna alokacja mapy (podwójne wskaźniki `**`) oraz obsługa cofania ruchów (Undo) zrealizowana w oparciu o jednokierunkową listę wiązaną.
- **Operacje na Plikach:** Wczytywanie poziomów z plików tekstowych, zapisywanie stanu gry (Save) oraz automatyczne logowanie zdarzeń (logi z rozgrywki).
- **Interfejs Graficzny (GUI):** Zaimplementowany za pomocą zewnętrznej biblioteki SDL2, zastępujący standardową konsolę.

## 🛠️ Instrukcja kompilacji i uruchomienia
Projekt wykorzystuje plik `Makefile` do automatyzacji budowania. Wymagane jest środowisko z kompilatorem `gcc` oraz zainstalowaną biblioteką `SDL2` (np. przez MSYS2 na systemie Windows).

1. Otwórz terminal w głównym katalogu projektu.
2. Wpisz komendę `mingw32-make` (lub `make`), aby skompilować kod.
3. Uruchom wygenerowany plik `sokoban.exe`.

## 🎮 Sterowanie w grze
* **W / S / A / D** - Poruszanie się postacią
* **Z** - Cofnięcie ostatniego ruchu (Nielimitowane Undo!)
* **F5** - Zapisanie aktualnego stanu planszy (Zapis znajduje się w folderze `saves/`)
* **Q / ESC** - Bezpieczne wyjście z gry
* **N** - Nowy Poziom
* **R** - Reset Poziomu 

## 📁 Struktura Projektu
- `src/` - Kod źródłowy (`.c`)
- `include/` - Pliki nagłówkowe (`.h`)
- `assets/` - Pliki poziomów wczytywane do gry
- `saves/` i `logs/` - Katalogi operacji plikowych