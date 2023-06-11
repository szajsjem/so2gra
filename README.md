# so2gra                         

## Opis projektu

Projekt Cell Factory jest gr� sandbox, w kt�rej mo�emy wystawia� i us�wa� obiekty na planszy.
Program dzia�a w konsoli i u�ywa biblioteki curses do obs�ugi interfejsu u�ytkownika.

gra:
![wygl�d gry](/gra.png)

### Instrukcje i sterowanie
Po uruchomieniu programu, gra rozpoczyna si� na planszy w konsoli.
![wygl�d menu](/menu.png)

Strza�ki: Poruszanie si� po planszy.
Delete: Usuni�cie obiektu z aktualnej pozycji.
C: Utworzenie obiektu na aktualnej pozycji do wypisania w konsoli .
G: Utworzenie generatora kropek na aktualnej pozycji.
O: Utworzenie obiektu obracaj�cego na aktualnej pozycji.
R: Obr�t wska�nika.
Tab: Zmiana wybranej zak�adki(* przy nazwie, do zmieniania czasu).
Shift + Tab: Od�wierzanie kierunku poruszania si� kropki.
Plus (+): Zwi�kszenie czasu dla wybranego typu obiektu.
Minus (-): Zmniejszenie czasu dla wybranego typu obiektu.


### Struktura projektu
Projekt sk�ada si� z nast�puj�cych plik�w �r�d�owych:

commons.h: Plik nag��wkowy zawieraj�cy deklaracje og�lnych funkcji i struktur danych wykorzystywanych w projekcie.
Object.h: Plik nag��wkowy zawieraj�cy deklaracj� klasy Object, kt�ra jest podstawowym elementem gry.
GeneratorObject.h: Plik nag��wkowy zawieraj�cy deklaracj� klasy GeneratorObject, kt�ra jest specjalizacj� klasy Object.
MovingObject.h: Plik nag��wkowy zawieraj�cy deklaracj� klasy MovingObject, kt�ra jest specjalizacj� klasy Object.
SpecializedNonMoving.h: Plik nag��wkowy zawieraj�cy deklaracj� klas, kt�ra jest specjalizacj� klasy Object.
SpecializedMoving.h: Plik nag��wkowy zawieraj�cy deklaracj� klas, kt�ra jest specjalizacj� klasy MovingObject.
main.cpp: G��wny plik �r�d�owy programu, zawieraj�cy funkcj� main i logik� gry.

### W�tki:
W�tek od�wierzaj�cy ekran co 500ms
W�tek dla ka�dego wystawionego i wygenerowanego obiektu
W�tek interakcji z u�ytkownikiem

### Sekcje krytyczne:
rysowanie na ekranie
us�wanie/dzia�anie obiektu
zmiana miejsca na ka�dym polu gry

## Autor:
Dominik Szczypi�r 259053










