# so2gra                         

## Opis projektu

Projekt Cell Factory jest gr� sandbox, w kt�rej mo�emy wystawia� i us�wa� obiekty na planszy.<br>
Program dzia�a w konsoli i u�ywa biblioteki curses do obs�ugi interfejsu u�ytkownika.<br>

gra:<br>
![wygl�d gry](/gra.png)

### Instrukcje i sterowanie
Po uruchomieniu programu, gra rozpoczyna si� na planszy w konsoli.<br>
![wygl�d menu](/menu.png)

Strza�ki: Poruszanie si� po planszy.<br>
Delete: Usuni�cie obiektu z aktualnej pozycji.<br>
C: Utworzenie obiektu na aktualnej pozycji do wypisania w konsoli .<br>
G: Utworzenie generatora kropek na aktualnej pozycji.<br>
O: Utworzenie obiektu obracaj�cego na aktualnej pozycji.<br>
R: Obr�t wska�nika.<br>
Tab: Zmiana wybranej zak�adki(* przy nazwie, do zmieniania czasu).<br>
Shift + Tab: Od�wierzanie kierunku poruszania si� kropki.<br>
Plus (+): Zwi�kszenie czasu dla wybranego typu obiektu.<br>
Minus (-): Zmniejszenie czasu dla wybranego typu obiektu.<br>


### Struktura projektu
Projekt sk�ada si� z nast�puj�cych plik�w �r�d�owych:<br>
<br>
commons.h: Plik nag��wkowy zawieraj�cy deklaracje og�lnych funkcji i struktur danych wykorzystywanych w projekcie.<br>
Object.h: Plik nag��wkowy zawieraj�cy deklaracj� klasy Object, kt�ra jest podstawowym elementem gry.<br>
GeneratorObject.h: Plik nag��wkowy zawieraj�cy deklaracj� klasy GeneratorObject, kt�ra jest specjalizacj� klasy Object.<br>
MovingObject.h: Plik nag��wkowy zawieraj�cy deklaracj� klasy MovingObject, kt�ra jest specjalizacj� klasy Object.<br>
SpecializedNonMoving.h: Plik nag��wkowy zawieraj�cy deklaracj� klas, kt�ra jest specjalizacj� klasy Object.<br>
SpecializedMoving.h: Plik nag��wkowy zawieraj�cy deklaracj� klas, kt�ra jest specjalizacj� klasy MovingObject.<br>
main.cpp: G��wny plik �r�d�owy programu, zawieraj�cy funkcj� main i logik� gry.<br>

### W�tki:
W�tek od�wierzaj�cy ekran co 500ms<br>
W�tek dla ka�dego wystawionego i wygenerowanego obiektu<br>
W�tek interakcji z u�ytkownikiem<br>

### Sekcje krytyczne:
rysowanie na ekranie<br>
us�wanie/dzia�anie obiektu<br>
zmiana miejsca na ka�dym polu gry<br>

## Autor:
Dominik Szczypi�r 259053<br>










