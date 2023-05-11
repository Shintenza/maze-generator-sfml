## Kilka słów o projekcie
Poniższy projekt skupia się na implementacji algorytmu do generowania labiryntu. Generator jest oparty o bibliotekę SFML, którą wykorzystałem do graficznego zaprezentowania działania 
algorytmu. Program pozwala również dopasować rozmiar generowanego labiryntu z poziomu menu (do menu można wrócić po naciśnięciu przycisku "Q"). Działanie programu oparte jest koncepcyjnie
o działanie algorytmu DFS. Btw. testy były przeprowadzane tylko na Linuxie.

## Zależności
Do poprawnego działania projektu, wymagane są poniższe zależności:
- [SFML](https://www.sfml-dev.org/)
- [make](https://www.gnu.org/software/make/)

## Kompilacja i użytkowanie
Przed rozpoczęciem procesu kompilacji programu upewnij się, że masz zainstalowane wszystkie, wymagane zależności:

ArchLinux:
> sudo pacman -S sfml make g++

Fedora:
> sudo dnf install SFML SFML-devel make g++

Debian:
> sudo apt install libsfml-dev make g++

### Uruchamianie/kompilowanie
Będąc w katalogu projektu, uruchom polecenie `make run`
