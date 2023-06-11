# so2gra                         

## Opis projektu

Projekt Cell Factory jest gr¹ sandbox, w której mo¿emy wystawiaæ i usówaæ obiekty na planszy.<br>
Program dzia³a w konsoli i u¿ywa biblioteki curses do obs³ugi interfejsu u¿ytkownika.<br>

gra:<br>
![wygl¹d gry](/gra.png)

### Instrukcje i sterowanie
Po uruchomieniu programu, gra rozpoczyna siê na planszy w konsoli.<br>
![wygl¹d menu](/menu.png)

Strza³ki: Poruszanie siê po planszy.<br>
Delete: Usuniêcie obiektu z aktualnej pozycji.<br>
C: Utworzenie obiektu na aktualnej pozycji do wypisania w konsoli .<br>
G: Utworzenie generatora kropek na aktualnej pozycji.<br>
O: Utworzenie obiektu obracaj¹cego na aktualnej pozycji.<br>
R: Obrót wskaŸnika.<br>
Tab: Zmiana wybranej zak³adki(* przy nazwie, do zmieniania czasu).<br>
Shift + Tab: Odœwierzanie kierunku poruszania siê kropki.<br>
Plus (+): Zwiêkszenie czasu dla wybranego typu obiektu.<br>
Minus (-): Zmniejszenie czasu dla wybranego typu obiektu.<br>


### Struktura projektu
Projekt sk³ada siê z nastêpuj¹cych plików Ÿród³owych:<br>
<br>
commons.h: Plik nag³ówkowy zawieraj¹cy deklaracje ogólnych funkcji i struktur danych wykorzystywanych w projekcie.<br>
Object.h: Plik nag³ówkowy zawieraj¹cy deklaracjê klasy Object, która jest podstawowym elementem gry.<br>
GeneratorObject.h: Plik nag³ówkowy zawieraj¹cy deklaracjê klasy GeneratorObject, która jest specjalizacj¹ klasy Object.<br>
MovingObject.h: Plik nag³ówkowy zawieraj¹cy deklaracjê klasy MovingObject, która jest specjalizacj¹ klasy Object.<br>
SpecializedNonMoving.h: Plik nag³ówkowy zawieraj¹cy deklaracjê klas, która jest specjalizacj¹ klasy Object.<br>
SpecializedMoving.h: Plik nag³ówkowy zawieraj¹cy deklaracjê klas, która jest specjalizacj¹ klasy MovingObject.<br>
main.cpp: G³ówny plik Ÿród³owy programu, zawieraj¹cy funkcjê main i logikê gry.<br>

### W¹tki:
W¹tek odœwierzaj¹cy ekran co 500ms<br>
W¹tek dla ka¿dego wystawionego i wygenerowanego obiektu<br>
W¹tek interakcji z u¿ytkownikiem<br>

### Sekcje krytyczne:
rysowanie na ekranie<br>
usówanie/dzia³anie obiektu<br>
zmiana miejsca na ka¿dym polu gry<br>

## Autor:
Dominik Szczypiór 259053<br>










