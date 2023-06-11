# so2gra                         

Opis projektu

Projekt Cell Factory jest gr¹ sandbox, w której mo¿emy wystawiaæ i usówaæ obiekty na planszy.
Program dzia³a w konsoli i u¿ywa biblioteki curses do obs³ugi interfejsu u¿ytkownika.

gra:
![wygl¹d gry](/gra.png)

Instrukcje i sterowanie
Po uruchomieniu programu, gra rozpoczyna siê na planszy w konsoli. Poni¿ej znajduje siê krótki opis sterowania i funkcji programu:
![wygl¹d menu](/menu.png)

Strza³ki: Poruszanie siê po planszy.
Delete: Usuniêcie obiektu z aktualnej pozycji.
C: Utworzenie podstawowego obiektu na aktualnej pozycji do wypisania w konsoli.
G: Utworzenie generatora obiektów na aktualnej pozycji.
O: Utworzenie obiektu obracaj¹cego na aktualnej pozycji.
R: Obrót wskaŸnika.
Tab: Zmiana typu obiektu do tworzenia.
Shift + Tab: Zmiana kierunku obiektu do tworzenia.
Plus (+): Zwiêkszenie czasu dla wybranego typu obiektu.
Minus (-): Zmniejszenie czasu dla wybranego typu obiektu.


Struktura projektu
Projekt sk³ada siê z nastêpuj¹cych plików Ÿród³owych:

commons.h: Plik nag³ówkowy zawieraj¹cy deklaracje ogólnych funkcji i struktur danych wykorzystywanych w projekcie.
Object.h: Plik nag³ówkowy zawieraj¹cy deklaracjê klasy Object, która jest podstawowym elementem gry.
GeneratorObject.h: Plik nag³ówkowy zawieraj¹cy deklaracjê klasy GeneratorObject, która jest specjalizacj¹ klasy Object.
MovingObject.h: Plik nag³ówkowy zawieraj¹cy deklaracjê klasy MovingObject, która jest specjalizacj¹ klasy Object.
SpecializedNonMoving.h: Plik nag³ówkowy zawieraj¹cy deklaracjê klas, która jest specjalizacj¹ klasy Object.
SpecializedMoving.h: Plik nag³ówkowy zawieraj¹cy deklaracjê klas, która jest specjalizacj¹ klasy MovingObject.
main.cpp: G³ówny plik Ÿród³owy programu, zawieraj¹cy funkcjê main i logikê gry.

W¹tki:
W¹tek odœwierzaj¹cy ekran co 500ms
W¹tek dla ka¿dego wystawionego i wygenerowanego obiektu
W¹tek interakcji z u¿ytkownikiem

Sekcje krytyczne:
rysowanie na ekranie
usówanie/dzia³anie obiektu
zmiana miejsca na ka¿dym polu gry

Autor:
Dominik Szczypiór










