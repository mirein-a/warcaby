_Obcowska Weronika, Dominika Zając, Stanisław Stankiewicz_
Grupa 101 (wtorek godzina 14)
## WARCABY

Gra zrealizowana jest według zasad warcabów klasycznych(określane też warcabami brazylijskimi). Odbywa się na jednym komputerze, na planszy o wymiarach 8x8, wyświetlanej graficznie, za pomocą biblioteki graficznej SFML.

### Wersje gry

Istnieją dwie wersje gry, mają bardzo zbliżoną funkcjonalność, różnią się tylko interfacem graficznym.

1. Symboliczna plansza w konsoli

W projekcie pod nazwą 'warcaby' znajdują się pliki potrzebne do uruchomienia tej wersji.
Żeby rozpocząć grę należy je uruchomić i postępować zgodnie z wyświetlanymi instrukcjami.

2. Plansza GUI

W projekcie pod nazwą 'checkers' znajdują się pliki potrzebne do uruchomienia wersji z planszą graficzną.

Plansza została zrealizowana przy pomocy SFML: https://youtu.be/YfMQyOw1zik

### Tryby gry

1. użytkownik vs użytkownik –gra dla dwóch osób, rozgrywana na jednym komputerze tak, jak na papierowej planszy.
2. użytkownik vs gracz komputerowy–gra dla jednej osoby, drugim graczem jest gracz komputerowy, który dobiera ruchy na zasadzie losowania.

### Klasy:

1. Klasa `Player` (gracz) i dziedziczące z niej klasy `ComputerPlayer` (gracz komputerowy) i `UserPlayer`(gracz użytkownik komputera). Klasy te zawierałyby metody odpowiedzialne za odbieranie informacji od gracza i przekazywaniu ich do metod innych klas w celu przesuwania pionków. – Stanisław Stankiewicz
2. Klasa `Men`(pion), obiekt tej klasy odpowiada jednemu zwykłemu pionkowi. Atrybuty tej klasy określają kolor i współrzędne pionka na planszy. Metody zawarte w tej klasie określają jak pion porusza się po planszy oraz kiedy jest usuwany lub zamieniany na damkę (obiekt klasy `King`).– Stanisław Stankiewicz
3. Klasa `Kings`(damka)dziedziczy z klasy `Men`,obiekt tej klasy odpowiada jednemu pionkowi z rangą dama.Atrybuty pozostają takie same jak w klasie Men, ale zmienione zostają metody odpowiadające poruszaniu się po planszy.– Stanisław Stankiewicz
4. Klasa `Rules` (zasady)przechowująca zasady gry i założenia jej prowadzenia. Metody tej klasy określają jaki ruch możliwy jest dla danego pionka, a także kryteria wygrania gry.– Weronika Obcowska
5. Klasa `PlayGameNew` (rozgrywka), w której będą wywoływane obiekty pozostałych klas na czas prowadzenia gry. W tej klasie powinny się też znaleźć metody sprawdzające czy rozgrywka ma być prowadzona dalej, czy któryś z graczy już wygrał. – Weronika Obcowska
6. Klasa `Moves` (ruchy), a w niej metody przyjmujące współrzędne pionków i sprawdzające na jakie pole dany pionek można przesunąć oraz generująca listę możliwych ruchów, z której gracz może wybierać. –Weronika Obcowska
7. Klasa `Board` (plansza) przechowująca tekstury, obrazy rastrowe i inne elementy niezbędne dla interfejsu graficznego, jak i informacje o ułożeniu pionków na planszy w odniesieniu do okna aplikacji (w pikselach). – Dominika Zając
8. Klasa `Game` (gra) analizująca dane wejściowe gracza, takie jak kliknięcia myszy czy przycisków klawiatury. Przechowuje informacje o stanach gry, tymczasowe współrzędne wybranych w danej kolejce pionków i pól, na które mają się ruszyć, jak i parametry okna aplikacji  – Dominika Zając
9. Klasa `GUI_Piece` przechowująca informacje o położeniu danego pionka w odniesieniu do okna aplikacji (w pikselach), jak i teksturze reprezentującego go obrazka rastrowego. - Dominika Zając
10. Klasa `ProtoBoard` przechowująca układ pionków na planszy - Stanisław Stankiewicz, Weronika Obcowska
11. Klasa `SaveGame` odpowiadająca za zapisywanie stanu gry - Weronika Obcowska
12. Klasa `ResumeGame` odpowiadająca za odczytywanie stanu gry - Weronika Obcowska


## ZADANIE 4 (Weronika Obcowska)

### AKTUALIZACJA KLASY MOVES
1. Wprowadzenie szablonu metody `template<typename Col, int size> bool surroundings(Col color_checking, Col board[size][size], int r, int c, int type)`
oraz atrybutu `options`

Założeniem szablonu tej metody jest, że można wykorzystać ją do planszy o dowolnym rozmiarze (parametr `int size`) oraz sprawdzić pionki o dowolnym symbolu (parametr `typename Col`).
Dokładne działanie metody jest określane poprzez argument `int type`. Metoda rozpoznaje trzy typy: bicie (`type = 1`), zwykły ruch pionka "w dół planszy" (`type = 2`), zwykły ruch pionka "w górę planszy" (`type = 3`).
Ogólne działanie metody polega na sprawdzaniu otoczenia pionka, umożliwia sprawdzenie najbliższego pola po skosie i pola o 1 dalej, w tym samym kierunku.
Po sprawdzeniu tych współrzędnych - jeśli spełniają określone warunki - pola dodawane są do atrybutu `options`.
To, że `bool` jest typem watości zwracanej umożliwia sprawdzenie czy którekolwiek z warunków zostały spełnione.
Metoda jest wykorzystywana w innych metodach klasy `Moves`, które ustawiają parametry szablonu i argumenty.

2. Modyfikacja metody `check_move`

Metoda została zmodyfikowana w taki sposób, że przyłuje wyżej wymieniony szablon i ustawia argument `type` na 1 lub 2 w zależności od tego,
jaki kolor pionka jest sprawdzany. Jeśli rozmiar vectora `options` jest różny od 0 - metoda `check_move` doda współrzędne sprawdzanego pionka do atrybutu `possible_pieces`.

2. Dodanie atrybutu `beats` oraz metody `check_beat` - służących do sprawdzania bić.

Metoda `check_beat` wykorzystuje wyżej wymieniony szablon. Ustawia argument `type` na 1. 
Zgodnie z regułami gry, bicia są obowiązkowe i mogą odbywać się w dowolnych kierunkach po skosie. 
Metoda `check_beat` przyjmuje jako argumenty współrzędne danego pionka (`int coefficient_r`, `int coefficient_c`), jego kolor (`char color`)
oraz dwuwymiarową tablicę z aktualnym ułożeniem pionków na planszy (`board[8][8]`). 
W wyniku działania tej metody, współrzędne pionka są dodane do vectora `possible_pieces`, jeśli spełniają warunki umożliwiające przeprowadzenie bicia. 
Atrybut `beats` zostaje ustawiony na taką wartość, jaką zwróci `template<typename Col, int size> bool surroundings` zwróci `false` - ma to zastosowanie w metodzie `create_possibilities`.

3. Wprowadzone zostały zmian do metod `get_possible_pieces()` oraz `create_possibilities()` - służące do generowania gotowego zestawu pinków, z których gracz może wybierać.

Ponieważ bicia są obowiązkowe, sprawdzenie czy można je w danym ruchu wykonać ma większy priorytet niż sprawdzenie czy możliwe jest wykonanie zwykłego ruchu. 
Modyfikacja metody `get_possible_pieces()` polega zatem na sprawdzenie czy dla któregokolwiek pionka można wykonać bicie, a jeśli nie – sprawdzane jest czy dla któregokolwiek pionka można wykonać zwykłe ruchy. 
Pionki, które można przesunąć (albo z biciem albo bez bić) są dodawane do atrybutu `possible_pieces`. 

Analogicznie, metoda `create_possibilities()` doda do vectora przede wszystkim te pionki, dla których można przeprowadzić bicia.
Możliwe są bicia podwójne - jeśli metoda wykryje takie bicie, do atrybutu `possible_moves` zostanie dodana cała "trasa" dla danego pionka.
Jeśli nie ma możliwości wykonania bicia – metoda doda do atrybutu `possible_moves` te pionki, dla których można przeprowadzić zwykły ruch.
W celu sprawdzenia czy danym pionkiem można się ruszyć, metoda przywołuje `template<typename Col, int size> bool surroundings`.


### WPROWADZENIE KLASY PLAYGAMENEW
Jest to główna klasa służąca do prowadzenia rozgrywki. Została zrealizowana jako szablon: `template<class PlayerOfChoice> class PlayGameNew`
Wykorzystuje wszystkie pozostałe klasy, przywołuje ich metody i zmienia ich atrybuty w odpowiednich momentach. 
1. W Konstruktorze przygotowywane są wszystkie potrzebne elementy: tworzone są obiekty graczy, obiekt planszy, obiekt klasy `Moves` (klasa kontrolująca możliwe ruchy). 
2. W metodzie `one_full_turn` znajduje się schemat procedury jednego pełnego ruchu, z uwzględnieniem zmiany kolejki (metoda `switch_turn`). 
3. Metoda `lets_play` odpowiada za uruchomienie gry – tworzy obiekt klasy `Rules` (klasy odpowiadającej za warunki kontynuowania rozgrywki) 
i wywołuje metodę `one_full_turn` dopóki `game_over` nie przyjmie wartości true. 

### WPROWADZENIE KLASY RULES
Ta klasa działa jako pomocniczy element prowadzenia rozgrywki. 
Zawiera atrybuty określające koniec gry (`bool game_over`) oraz wygraną któregoś z graczy (`bool player1_won`, `bool player2_won`). 
1. W metodzie `check_if_game_over` sprawdzane są: liczby pionków graczy i możliwości dalszego wykonania ruchu. 
Metoda ta wywoływana jest co kolejkę (w metodzie `lets_play()` klasy `PlayGame`). 
2. Jeśli atrybut `game_over` został zmieniony na true, wywoływana jest metoda `evaluate_results()`, która sprawdza który gracz zwyciężył.

### WPROWADZENIE KLASY PROTOBOARD
Celem wprowadzenia tej klasy było stworzenie prototypu planszy (stąd jej nazwa: `ProtoBoard`), która symbolicznie obrazuje przebieg rozgrywki na planszy. 
Ta klasa została napisana przez *Stanisława Stankiewicza* i przeze mnie (*Weronika Obcowska*), tak jak wyobrażamy sobie docelowe schematy działania klasy Board i GUI. 
Zrobiliśmy ją w taki sposób żeby była jak najbardziej dopasowana do klas pisanych przez nas samodzielnie. 
Korzysta bezpośrednio z atrybutów i metod klas: `Moves`, `Player`, `Piece` i `PlayGame`.
Metody zrobione przeze mnie:
1. `the_display` - wyświetlenie planszy.
2. `choose_piece` - wczytanie z klawiatury numeru pionka i odnalezienie go w atrybucie `possible_pieces` klasy `Moves`.
3. `choose_the_field` - wczytanie z klawiatury numery pola, na który ma być przesunięty wcześniej wybrany pionek i odnalezienie go w atrybucie `possible_moves` klasy `Moves`.
4. `check_input` - sprawdzenie, czy Użytkownik wpisał cyfrę przy wyborze pionka lub pola.



### MILESTONES
1. Wprowadzenie pojedynczych i wielokrotnych bić do gry.

2. Wprowadzenie szablonów klas i funkcji:

Zrealizowanie metody klasy `Moves`: `template<typename Col, int size> bool surroundings` jako szablon
umożliwia teoretyczne sprawdzenie położenia pionków o dowolnym symbolu (`typename Col`) na planszy o dowolnym rozmiarze (`int size`).
Zrealizowanie klasy `PlayGameNew`: `template<class PlayerOfChoice> class PlayGameNew` jako szablon
umożlwia wykorzystanie tych samych procedur znajdujących się w tej klasie dla obiektów klas `UserPlayer` i `ComputerPlayer` (parametr `PlayerOfChoice`).

3. Zredukowanie powtarzalności procedur w metodach `check_move`, `check_beat` i `create_possibilities` klasy `Moves`.

Wcześniejsza wersja zakładała sprawdzanie współrzędnych pionka w wielokrotnych pętlach `for` i `if` w każdej z metod.
Obecnie metody korzystają z szablonu, w którym znajdują się te procedury.
To redukuje rozmiar kodu klasy `Moves` i pozwala uniknąć wielokrotnej powtarzalności procedur o zbliżonych zasadach działania.

### ISSUES
1. W kolejnej wersji gry: pojawienie się możliwość zmiany pionków na damy. Pojawi się też interface graficzny.
2. Wprowadzenie możliwości zapisu gry

## Zadanie 4 Stanisław Stankiewicz; (wersja finalna)

### Zmiany w Player:

1. Zostały dodane dziedziczące klasy `UserPlayer` i `ComputerPlayer` (`Player` pozostała jako bazowa klasa). 
2. Został dodany atrybut `actual_piece` (i dodatkowo metoda `pick_up_piece` ustalająca ten atrybut ) będący wskaźnikiem na objekt typu `Piece`. Na objekcie wskazywanym przez ten pointer wywoływana jest metoda ruchu `Piece.move()`.
3. Zdefiniowane zostały metody wyboru pionka i ruchu poprzez gracza-komputera `pick_up_piece` i `move_piece` . Wykorzystują one metody nowej klasy `Estimation`.

Wszystkie metody `UserPlayer` i `ComputerPlayer` są te same i zadeklarowane są w klasie bazowej `Piece`, natomiast mają różne definicje. Na przykład metoda `set_name` w przypadku `UserPlayer` zapisuje dane wpisane przez użytkownika w konsoli jako atrybut `Name`, natomiast w przypadku `ComputerPlayer` losuje jedno imię z `vector<string>` możliwych imoin.


### Zmiany w Piece:

1. Zosatała stworzona klasa bazowa `Piece` (klasy `Man` i `King` teraz dziedziczą z niej). 
2. Metoda `move` teraz przejmuje `vector<int>` przekazywany z klasy `Moves` zamiast dwóch elemntów typu `int`. Zrobione to jest po to żeby można było wywoływać metodę `beat()`. Funckja zawiera rekurencję (w przypadku kiedy jest bicie wielokrotne, funkcja `move` na końcu wywołuje samą siebie ponownie).
3. Została opisana metoda `beat()` usuwająca objekt klasy `Piece` z pamięci i pozostawiająca na miejscu pointera na ten objekt w wektorze `vector<vector<Piece*>>` - `nullptr`.

(Dodanie klas dziedziczących pociągnęło za sobą dodanie funkcji wirtualnych (na razie prostych) i konstruktorów dziedziczących).


Wszystkie metody `Man` nie różnią się od metod `King` i są zdefiniowane w bazowej klasie `Piece`. Za rozróżnienia ruchów zwykłych pionków i damek odpowiada `Moves`.
Wszystkie metody są dobrze skomentowane w kodzie.

### Wprowadzenie klasy Estimation:

Ta klasa odpowiada za wybór pionków i ruchów poprzez gracza-komputera `ComputerPlayer`. Działanie polega na tworzeniu nowej symulacji (tzn planszy `ProtoBoard` wraz ze wszystkimi pionkami `Man/King`) która mam stan identyczny ze stanem aktualnej symulacji w której się odbywa gra i robieniu wszystkich możliwych ruchów ewaluując skutki tych ruchów i nadając pionkom/ruchom ocenę `rating`.
Metody klasy operują na dwóch typach: `Piece*` i `vector<int>`, pierwszy to wskaźnik na pionek na planszy, drugi to ruch w formie ciągu liczb-współrzędnych `int`, w takiej formie w której ruchy są przedstawione w klasie `Moves`.


Atrybuty:

1. `double acceptable_rating` - atrybut potrzebny do sortowania pionków i ruchów (na razie tylko pionków). Pionki/ruchy z rating niższym niż ten `acceptable_rating` są skreślane z listy preferowanych pionków/ruchów.
2. `map< Piece*, vector<vector<int>> > pieces_with_moves;` - `map` w którym key to `Piece *` tzn pionek, value to `vectot<vector<int>>` tzn wektor możliwych ruchów dla danego pionka.
3. `map< Piece*, double > pieces_with_rating;` - map w którym key to `Piece *` tzn pionek, value to `double` tzn rating danego pionka.

Metody:

1. `template<typename T> void sort(map< T, double>& options);` - funkcja usuwająca z podanej `map`y elementy (pionki lub ruchy) które mają rating niższy niż `acceptable_rating`. 
2. `template<typename T> void set_acceptable_rating(map< T, double>& options);` - funckja która patrząc na podaną mapę `options` typu options[ruch/pionek] = rating, ustala atrybut `acceptable_rating` (największy w mapie).
3. `void get_pieces(Moves& m, ProtoBoard* pb);` - funkcja, która na podstawie atrybuta `Moves` `possible_moves`, ustala atrybut `pieces_with_rating` w którym key to wskaźnik na możliwy pionek na planszy `ProtoBoard`, value to 0 (początkowy rating).
4. `template<typename T> map< T, double> prerate(vector<T> options);` - funckja przejmuje wektor pionków/ruchów i zwraca `map`ę typu map[ruch/pionek] = 0 (początkowy rating), wykorzystywana jest w powyższej funkcji. 
5. `void rate_endangered_pieces(map< Piece*, double>& pieces, ProtoBoard& pb);` - funckja która za pomocą funckji `check_danger` klasy `Moves` znachodzi pionki którym grozi bicie i podwyża im rating, żeby takie pionki z większym prawdopodobieństem zostały przesunięte.
6. 	`void test_piece(Piece* piece, Moves& m, ProtoBoard& pb);` - funkcja testuje możliwe ruchy każdego pionka, i w zależności od efektów tych ruchów zmienia rating pionka i zapisuje (lub nie) ruch jako preferowany.
7. 	`vector<Piece*> best_pieces(Moves& m, ProtoBoard* pb);` - głowna funkcja która korzystając z informacja zawartej w `Moves` i `ProtoBoard` zwróci graczowi-komputerowi `vector<Piece*>` najlepszych w danej sytuacji pionków.
8. 	`vector<vector<int>> best_moves(Moves& m, ProtoBoard* pb);` - na razie nie zdefiniowana
9. 	`bool good_move(Piece* piece, vector<int>& move, ProtoBoard& pb);` - funckja zwraca `true` w przypadku gdy po wykonaniu danego ruchu danemu pionkowi żaden pionek nie będzie grozić.

Reasumując, klasa stworzona jest po to żeby pomagać `ComputerPlayer` wybierać pionki/ruchy poprzez wywoałanie odpowiednio `best_pieces`/`good_moves`. Na razie cały proces jest zdefiniowany tylko dla wyboru pionków. Ale wybierając ruch `ComputerPlayer` najpierw sprawdzi `map` `pieces_with_moves` w którym znajdują się preferowane ruchy. Na razie analiza jest nie bardzo głęboka. 
Szablony są używane po to żeby metody działały również dla pionków `Piece*` jak i dla ruchów `vector<int>`, tzn na przyszłość.

### ProtoBoard:

To jest tymczasowa klasa która pomaga przetestować działanie innych klas i stanowi tymczasowy prosty "interfejs graficzny" w konsoli. Autory klasy : Weronika Obcowska i Stanisław Stankiewicz (ja).
Metody stworzone przeze mnie:

1. `create_men_vector()` 
2. `get_board`
3. `show_possible_pieces`
4. `show_possibilities` (stworzona przez Weronikę Obcoswską - zmodyfikowana przeze mnie)
5. `operator=` - przeciążenie operatora `=` potrzebne do głębokiego kopiowania zawartości objekta klasy `ProtoBoard` 
6. `~ProtoBoard` - destruktor klasy `ProtoBoard` powodujący destrunkcję wsztstkich objektów na które są wskaźniki w zniszczonym objekcie `ProtoBoard`.

Wszystkie metody są dobrze skomentowane w kodzie.

### URUCHOMIENIE GRY
Żeby sprawdzić działanie klas wystarcz uruchomić plik `main.cpp`. 
Żeby program zadziałał konieczne są pliki z klasami `ProtoBoard`, `PlayGameNew`, `Player`, `Piece`, `Moves` i `Rules`



## ZADANIE 4 Dominika Zając


### DYNAMICZNA ALOKACJA PAMIĘCI
W klasie Board utworzona została metoda CreateGuiPieceVector(), w której następuje tworzenie nowych obiektów GUI_Piece za pomocą operatora new. 

### SZABLON KLASY
W klasie Board (plik Board.hpp) utworzony został szablon metody `template <typename T>
    void GetOffBoard(pair<int, int> coords, vector<vector<T*>> TVector)`, który pozwolił na zmniejszenie objętości kodu poprzez umożliwienie zmieniania współrzędnych pionka, nie zależnie czy jest to pionek logiczny (Piece), czy pionek interfejsu graficznego (GUI_Piece).

### DZIEDZICZENIE
W klasie GUI_Piece stworzone zostały klasy pochodne - GUI_Man i GUI_King, które zostaną wykorzystane przy wprowadzeniu do projektu zamiany zwykłych pionów na damki.

### PRZECIĄŻANIE OPERATORÓW
W klasie Score (przechowującej liczbę punktów danego gracza) obciążony został operator ++, który pozwala na łatwiejszy i bardziej intuicyjny zapis zwiększenia liczby punktów danego gracza.  Znalazło to zastosowanie w pliku Game.cpp



## Jak grać?
W pliku `main.cpp` znajduje się wywołanie obiektu klasy `PlayGameNew` i metody `lets_play` tej klasy - z kontrolą wejścia i możliwością wyboru trybu rozgrywki.
To wystarczy żeby rozpocząć grę.
Po uruchomieniu pliku `main.cpp`, w konsoli wyświetli się pytanie o tryb gry. Po wpisaniu 0 lub 1, Użytkownik zostaje poproszony o wpisanie imienia/pseudonimu. 
Po wpisaniu imion (pseudonimów) rozpocznie się pierwsza kolejka, zawsze zaczyna gracz który gra pionkami białymi ('b'). 
Pionki, którymi można wykonać ruch zostaną wyświetlone jako cyfry.
Żeby wybrać pionek należy wpisać cyfrę symbolizującą pion, który chcemy przesunąć i kliknąć enter. 
Wówczas pojawi się plansza, na której zaznaczone będą pola, na które można przesunąć dany pionek. 
Podobnie jak przy wyborze pionka, będą one zaznczone cyframi, a wcześniej wybrany przez użytkownika pionek będzie wyśweitlony jako litera 'A'(actual). 
Aby wybrać pole należy wpisać cyfrę, która symbolizuje to pole. W przypadku wybrania niedozwolonego pionu lub pola (wpisanie cyfry, której nie ma na planszy lub wpisanie znaku, który nie jest liczbą całkowitą),
Gracz Użytkownik zostanie poproszony o wpisanie cyfry ponownie. 
Po wybraniu dozwolonego pola, następuje zmiana kolejki, schemat powtarza się.



## Weronika Obcowska, AKTUALIZACJA GRY (01.06.20)

### Aktualizacja klasy `Moves`

1. Wprowadzenie metody `check_king_beat` i modyfikacje metody `get_possible_pieces`:

We wcześniejszych wersjach metoda `get_possibile_pieces` rozpoznawała wyłącznie zwykłe pionki, obecnie metoda rozpoznaje również damki
i w zależności od tego jaki jest status pionka, sprawdza czy możliwe są dla niego ruchy do wykonania.
Sposoby bić pionków dla zwykłych pionków i damek znacznie się różnią, więc potrzebna była metoda `check_beat`, która korzystając z szablonu `template<typename Col, int size> bool Moves::king_surroundings`
sprawdza czy możliwe są ruchy dla pionu, który jest damką.

2. Wprowadzenie metod `create_king_possibilities` i `create_man_possibilities`; modyfikacja metody `create_possibilities`

Dawna zawartość metody `create_possibilities` została przeniesiona do metody `get_man_possibilities`,
a nowa metoda `create_possibilities` sprawdza czy pion jest damką czy zwykłym pionkiem - w zależności od tego przywołuje odpowiednią metodę tworzącą wektor możliwych pól.

3. Szablon `template<typename Col, int size> bool Moves::king_surroundings`

Ta metoda działa analogicznie do `template<typename Col, int size> bool Moves::surroundings`, z tymże pionek, dla którego sprawdza ruchy, w założeniu jest damką.
To oznacza, że badając otoczenie uwzględnia wszystkie wolne pola po przekątnych, a sprawdzając potencjalne bicia - wszystkie pionki przeciwnika po przekątnych.

4. Metody `get_dangerous_pieces` i `template<typename Col, int size> check_danger`

Te metody pojawiły się już w poprzedniej wersji. W obecnej zostały zrealizowane analogicznie do pozostałych metod tej klasy. 
Metoda `get_dangerous_pieces` nastawia parametry i wywołuje odpowiednią wersję szablonu. 
Szablon sprawdza najbliższe otoczenie danego pionka i na podstawie tych informacji dodaje do vectora `dangerous_pieces` współrzędne pionków, 
które w następnym ruchu mogą zbić pionek, dla którego badane jest jego otoczenie.

### Wprowadzenie klasy `SaveGame`

Obiekt tej klasy wywoływany jest bezpośrednio w metodzie `prepare_and_save` klasy `template<class PlayerOfChoice> PlayGameNew`. 
Tam przygotowywany jest zestaw danych potrzebnych do odtworzenia zapisanego stanu gry. Klasa posiada atrybuty, które są nastawiane w momencie,
gdy gracz decyduje się przerwać i zapisać grę.

1. Metoda `save_game`

W tej metodzie tworzona jest zmienna `fstream saved_game`, a potem plik `*.txt`, w kótrym zapisywane są dane gry przechowywane tymczasowo w atrybutach.

### Wprowadzenie klasy `ResumeGame`

Obiekt tej klasy wywoływany jest wywoływany, jeśli użytkownik wybierze w Menu startowym opcję wczytania poprzedniej gry.
Wejście jest zabezpieczone - jeśli żadna gra nie była poprzednio zapisana to program poinformuje o tym użytkownika i zakończy pracę.
W przeciwnym przypadku, wczyta dane z pliku tesktowego linia po linii i utworzy tymczasowe atrybuty potrzebne do przestawienia domyślnych atrybutów obiektu klasy `PlayGameNew`.

1. Metoda `resmue_game`

Wejście jest zabezpieczone - jeśli żadna gra nie była poprzednio zapisana to program poinformuje o tym użytkownika i zakończy pracę.
W przeciwnym przypadku, wczyta dane z pliku tesktowego linia po linii i utworzy tymczasowe atrybuty potrzebne do ustawienia argumentów (w tym domyślnych) konstruktora obiektu klasy `PlayGameNew`.

2. Metody pomocnicze `get_coords`, `get_color`

Te metody służą do wczytania danych i zapisania ich w tymczasowych zmiennych, z których potem utworzony zostanie vector reprezentujący planszę.

### Aktualizacja klasy `Rules`

Dodane zostało sprawdzanie kryterium zmiany zwykłego pionka na damkę oraz kryterium zakończenia gry po 30 ruchach damkami bez bić wykonanych przez graczy.

1. Metoda `check_status`

W tej metodzie w pierwszej kolejności sprawdzane jest, czy współrzędna pionka przypisana do rzędu jest równy 7 lub 0 (w zależności od koloru pionka).
Jeśli ten warunek jest spełniony, dotychczasowy obiekt klasy Piece odpowiadający tym współrzędnym zostaje usunięty, a na jego miejsca tworzony jest nowy obiekt - klasy King.

### Aktualizacja klasy `PlayGameNew`

Klasa została dostosowana do możliwości zapisu gry oraz możliwości cofania ruchu pionków w trakcie gry.

1. Modyfikacja konstruktora

W konstruktorze pojawiły się argumenty domyślne, których nie trzeba nastawiać wywołując grę po raz pierwszy.
Jeśli użytkownik odczyta grę z wcześniejszego zapisu, atrybuty obiektu tej klasy są ustawiane zgodnie z tym, co pojawiło się w zapisie.
Atrybut, który determinuje jaki tryb gry będzie rozegrany to `bool from_saved`. Jeśli zostanie ustawiony na true, potrzebne jest ustawienie pozostałych argumentów,
ponieważ oznacza to, że gra ma być reazlizowana z wcześniejszego zapisu.

2. Metoda `prepare_and_save`

Po wywołaniu tej metody tworzony jest obiekt klasy `SaveGame` oraz ustawiane są jego atrybuty.
Potem wywoływana jest metoda `save_game` klasy SaveGame, co bezpośrednio prowadzi do zapisania gry i jej przerwania.

### Aktualizacja klasy `ProtoBoard`

Klasa została dostosowana do możliwości zapisu gry

1. Metoda `create_man_vector_from_save`

Argumentami tej metody są dwa vectory, które odpowiadają ułożeniu pionków na planszy w poprzedniej grze.
Ta metoda jest wywoływana w konstruktorze klasy `PlayGameNew` zamiast `create_man_vector`, jeśli użytkownik wybrał opcję odczytu poprzednio zapisanej gry.

### Milestones:
1. Wprowadzenie klas SaveGame i ResumeGame umożliwiających zapis stanu gry i odczyt poprzednio zapisanej gry.
2. Wprowadzenie metod odpowiadających za pionki-damki do klasy Moves i Rules.



## Dominika Zając, AKTUALIZACJA GRY (01.06.20)

W tej aktualizacji połączyłam wszystkie istniejące klasy w spójną całość, zastępując w klasach PlayGameNew i Player dane wejściowe w postaci `cin >>` danymi pobieranymi za pomocą metody `processEvents(char what_do, Moves& mo, char current_color)`.

### Aktualizacja klasy Game

1. Metoda `processEvents`

Metoda wywoływana jest za pomocą trzech argumentów- znaku what_do, obiektu Moves i znaku bieżącego koloru (koloru pionków gracza, który wykonuje ruch). W zależności od znaku what_do, metoda analizuje jedną z kilku sytuacji, w których użytkownik musi wprowadzić dane:

- what_do == `p` - użytkownik wybiera jeden z pionków, którymi może się ruszyć (znajdujących się na podświetlonym na czerwono polu)
- what_do == `f` - użytkownik wybiera jedno z pól, na które może ruszyć się wybranym przez siebie pionkiem (pola te podświetlone są na czerwono)
- what_do == `c` - użytkownik ma do wyboru kliknięcie na klawiaturze klawisza „C” lub klawisza „S”, oznaczających odpowiednio anulowanie ruchu (c- cancel), bądź jego zaakceptowanie i zmianę kolejki (s - switch)
- what_do == `a` - użytkownik ma do wyboru kliknięcie na klawiaturze klawisza „P” lub klawisza „S”, oznaczających odpowiednio zatrzymanie gry (p- pause), lub zmianę kolejki (s- switch)

W oknie aplikacji znajduje się również przycisk `Instructions`, który służy do wyłączania/ włączania komunikatów (instrukcji) wyświetlających się na ekranie. Są one pomocne przy nauce korzystania z programu, lecz po dłuższym czasie mogą stawać się uciążliwe, więc guzik ten powoduje, że instrukcje nie będą już wyświetlane na ekranie. W każdym momencie można również z powrotem włączyć instrukcje. Wyłączenie instrukcji symbolizowane jest zaciemnieniem guzika, a włączenie, jego powrotem do pierwotnego, jaśniejszego koloru.

Metoda ta zastąpiła wcześniejszy sposób pobierania danych wejściowych od użytkownika metodą `cin >>` .

2. Metoda `render`

Służy do wyświetlenia w oknie aplikacji wszystkich elementów, które powinny się w nim znaleźć. W zależności od tego, czy gra zakończyła się czy nie, wyświetlana jest albo plansza z pionkami, albo menu końcowe informujące o zwycięstwie któregoś z graczy, bądź remisie.

3. Metoda `WindowSetUp’

Metoda ta ustawia wszelkie parametry konieczne do właściwego wyświetlenia planszy w zależności od rozdzielczości monitora urządzenia, na którym uruchamiana jest gra. Pobiera ona wysokość monitora metodą `sf::VideoMode::getDesktopMode().height` i wykorzystuje ją do właściwego dobrania wymiarów okna aplikacji, tak, by cala zmieściła się na ekranie bez powodowania zniekształceń planszy i utrudnień w prowadzeniu rozgrywki.

4. Metoda `SetUp`

Wywołuje metody potrzebne do prawidłowego przebiegu gry na poziomie interfejsu. Wywoływana jest jednokrotnie, na samym początku gry w metodzie lets_play() klasy PlayGameNew. Korzystając z metod klasy Board, tworzy ona wektor możliwych pozycji  metodą CreateXYPositions, ładuje tekstury metodą LoadTextures, tworzy wektor pionków interfejsowych GUI_Pieces metodą CreateGuiVector jak i ładuje tekstury obrazów rastrowych pionków. Po zatrzymaniu gry i ponownym jej uruchomieniu, sprawdza ona również, czy na planszy obecne były damki i jeśli tak, przypisuje im odpowiednie tekstury. Przyjmuje za argument wektor pionków logicznych, by na jego podstawie stworzyć wektor pionków interfejsowych.

5. Metoda `HighlightPieces`

Służy do podświetlenia pionków, którymi gracz może się ruszyć w danej kolejce. Podświetlenie polega na narysowaniu pod pionkiem czerwonego kwadratu. 
Metoda przyjmuje za argument adres obiektu Moves, co pozwoli na szybkie skorzystanie z zawartego w tym obiekcie wektora possible_pieces, zawierającego współrzędne pionków, którymi gracz może się ruszyć w danej kolejce.

6. Metoda `HighlightFields`

Służy do podświetlenia pól, na które może się ruszyć wybrany przez gracza w danej kolejce pionek. Podświetlenie polega na narysowaniu nad polem czerwonego kwadratu. Metoda przyjmuje za argument adres obiektu Moves, co pozwoli na szybkie skorzystanie z zawartego w tym obiekcie wektora possible_moves, zawierającego współrzędne pól, na które może się ruszyć pionek.

7. Metoda `BringThePastBack`

Przywraca informacje o wybranym pionku i ewentualnych pionkach przez niego zbitych, po anulowaniu ruchu. Zamienia ona miejscami GUI_Piece/ nullptr znajdujące się na polach o współrzędnych selected_piece_coords i chosen_square_coords, czyli odpowiednio współrzędnych wybranego w danej rundzie pionka i wybranego dla niego pola. Poprzez zamienienie ich miejscami funkcją swap, pionek wraca na swoje poprzednie miejsce, a na pole z którego użytkownik zrezygnował umieszczony zostaje nullptr. Korzysta z zapisanych wcześniej informacji w wektorach beat_coords, by odczytać współrzędne zbitych przed anulowaniem pionów interfejsowych GUI_Piece i przywrócić przypisaną im pozycję, kolor i współrzędne.

8. Metoda `ResetThePast`

Resetuje pod koniec każdej kolejki informacje o pionkach po anulacji, by w następnej rundzie anulacja mogła zostać przeprowadzona bez przeszkód.

9. Metoda `RemovePiece`

Metoda zapisuje informacje o zbitym pionie, w razie ewentualnej przyszłej anulacji bieżącego bicia, po czym usuwa pion z planszy. Jego pozycja ustawiona zostaje na (3000, 3000), tj. poza granice okna, kolor ustawiony zostaje na `n`, a koordynaty zmienione na (30, 30);

10. Metoda `Shout`

Przyjmuje string jako argument i ustawia go jako treść wiadomości, która wyświetli się na środku ekranu. Informacje te są instrukcjami dla gracza, które można wyłączyć i ponownie włączyć w każdym momencie rozgrywki, za pomocą guzika `Instructions`


### Aktualizacja klasy Board


1. Metoda `loadTextures`

Odpowiedzialna za załadowanie wszystkich tekstur potrzebnych do wyświetlenia elementów planszy w oknie aplikacji. Jeśli plik o danej nazwie nie zostanie znaleziony w folderze, element nie będzie miał tekstury, a więc nie zostanie wyświetlony w oknie aplikacji, a na konsoli pokaże się informacja o błędzie załadowania pliku. Metoda ustawia również pozycje obrazów rastrowych oraz czcionki, wielkości i kolory tekstów.

2. Metoda `CreateGuiPieceVector`

Tworzy wektor pionków interfejsowych GUI_Pieces  o nazwie GuiPiece na podstawie wektora pionków logicznych Pieces, który jest argumentem tej metody. Następuje dynamiczna alokacja pamięci- nowe elementy dodawane są do wektora operatorem new.

3. Metoda `SetPieceTextures`

Iteruje przez wektor pionków interfejsowych GUI_Pieces o nazwie GuiPiece i na jego podstawie przypisuje obrazkom rastrowym reprezentującym pionki odpowiednie tekstury i pozycje.

4. Metoda `CreateXYPositions`

Uzupełnia tablicę XYPositions, której elementami są dane typu sf::Vector2f, czyli dwie dane typu float złączone razem w dwuelementowy wektor. Do każdego z tych dwóch elementów odwołać się można poprzez operator .x lub .y . Jako że sf::Vector2f przechowuje dwie dane float, to metoda CreateXYPositions przypisuje każdemu z elementowi tablicy XYPositions jeden z ośmiu możliwych położeń pól na planszy wszerz i jeden z ośmiu możliwych wzdłuż.

5. Metoda `ChangeToKing`

 Sprawdza, czy na planszy przy załadowaniu gry obecne były damki i jeśli tak, przypisuje im odpowiednie tekstury.

### Aktualizacja klasy GUI_Piece

1. Poprawa błędu w konstruktorze obiektu

W poprzednich wersjach konstruktor był postaci:
GUI_Piece( char color, int x_coord, int y_coord).

Zmieniony został do poprawnej i zgodnej z wersją w pliku nagłówkowym wersji postaci: 
GUI_Piece(int x_coord, int y_coord, char color);

2. Metoda UpdateGuiPiece

Zmienia pozycję pionka w GUI, kiedy wybierane jest dla niego nowe pole. Użyta zostaje funkcja swap, by zamienić miejscami dwie zawartości wektora GuiPiece o podanych współrzędnych. Nowe współrzędne pionka zapisywane są w jego atrybucie coordinates, który jest typu sf::Vector2f, więc podobnie jak wyżej, przypisane one zostają operatorami .x i .y .


### Aktualizacje w innych klasach

Z uwagi na to, że w ramach finalizacji projektu miałam za zadanie połączyć wszystkie klasy w spójną całość, musiałam częściowo ingerować w klasy kolegów z projektu. Dokonałam zmian w klasach PlayGameNew, Player oraz Rules. Zmiany te polegały głównie na dodaniu jednego bądź kilku argumentów wchodzących do danej funkcji oraz użycia w niej metod klasy Game, Board, bądź GUI_Piece. 

Oto spis metod, w których dokonałam zmian:

	PlayGameNew :
		- konstruktor klasy 
		- lets_play
		- one_full_turn
	
	Player:
		- pick_up_piece (dla UserPlayer jak i dla ComputerPlayer)
		- move_piece (dla UserPlayer jak i dla ComputerPlayer)

	Rules:
		- evaluate_results
		- check_status

### Overall Challenges

Na samym początku zdecydowanym wyzwaniem było zapoznanie się z nową mi biblioteką graficzną SFML jak i przestawienie się na programowanie zorientowane obiektowo, z którym nie miałam dużego doświadczenia, przez co pierwsze wersje moich klas znajdowały się w całości w jednej funkcji main. W późniejszych fazach projektu trudności sprawiało mi stopniowe rozdzielanie funkcji main na klasy i łączenie ich z klasami logicznymi kolegów, gdyż początkowe zmagania z biblioteką graficzną opóźniły moją pracę. Moje klasy przechodziły więc wiele modyfikacji i przybierały różne kształty, jednak finalnie udało mi się połączyć logikę gry z graficznym interfejsem interaktywnym.
