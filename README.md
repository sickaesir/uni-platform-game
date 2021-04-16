# uni-platform-game

##### Introduzione
Il gioco è stato scritto in `c++` (17), per la compilazione viene usato il compilatore  `g++`.
Essendo sviluppato utilizzando Linux l'unica libreria utilizzata è `ncurses` (a scopo tecnico viene però linkata la libreria `ncursesw`), viene inoltre utilizzata la libreria `stdarg.h` per la formattazione di argomenti di funzione variadici (utilizzati principalmente per la formattazione di stringhe e la console di debug).

##### Compilazione
Per compilare il progetto viene fornito lo script `build.sh`.
Il binario risultante sarà scritto nella directory del progetto con il nome `uni-platform-game-bin`
Esempio:
`~ ./build.sh` 

##### Esecuzione
L'esecuzione del progetto può avvenire in modo diretto eseguendo il binario compilato.
Esempio:
`~ ./uni-platform-game-bin`

Per compilare ed eseguire il progetto in un singolo comando viene fornito lo script `run.sh` al quale possono, inoltre, essere passati argomenti in linea di comando per la configurazione del gioco.
Esempio:

`~ ./run.sh [args]`

##### Configurazione
Il progetto utilizza una serie di variabili per la configurazione delle meccaniche del gioco.
I valori di default di tali variabili sono incluse nel file `common.hpp`.
Per consentire, inoltre, una configurazione dinamica del gioco le variabili di configurazione vengono wrappate nella classe `game_settings` la quale si occupa di interpretare gli argomenti in linea di comando ed esporre i vari getter per ogni variable.
Esiste un argomento per ogni variabile di configurazione, segue una lista:

`--game-height | intero | altezza dell'area di gioco (console di debug esclusa)`


`--game-width | intero | larghezza dell'area di gioco (menù escluso)`


`--map-wall-padding | intero | larghezza del muro iniziale (sx) di gioco, altezza del "soffitto" e "pavimento" della mappa`


`--console-mode | booleano | specifica se la console di debug del gioco viene renderizzata`


`--console-lines | intero | numero di righe della console di debug da renderizzare`


`--io-inactive-ticks | intero | numero di tick da attendere dall'ultimo input da tastiera per determinare che l'utente sia inattivo`


`--character-jump-velocity | intero | numero di tick per il quale il personaggio sale dopo aver ricevuto un comando di salto`


`--gravity-ticks | intero | numero di tick dopo il quale il personaggio "discende" di un'unità se si trova a mezz'aria`


`--map-offsetting-min | intero | posizione sull'asse X del personaggio dopo la quale la mappa slitta a sinistra di un'unità`


`--map-offsetting-max | intero | posizione sull'asse X del personaggio dopo la quale la mappa slitta a destra di un'unità`


`--map-offset-threshold | intero | valore massimo di slittamento dopo la quale la mappa viene estesa`


`--rocks-gen-count | intero | numero di rocce da generare ad ogni estensione della mappa`


`--rock-gen-collision-padding | intero | numero di unità per il cui distanziare una roccia dall'altra`


`--max-character-life | intero | valore iniziale e massimo della vita del personaggio`


`--character-reattack-ticks | intero | numero di tick da aspettare tra uno sparo e l'altro del personaggio`


`--powerup-heal-amount | intero | ammontare di vita da incrementare quando si prende un powerup vita`


`--powerup-max-gen-amount | intero | numero di powerup da generare ad ogni estensione della mappa`


`--powerup-max-total-jump | intero | valore massimo di punti salto extra dati dai powerup`


`--enemy-gen-count | intero | numero base di nemici da generare ad ogni estensione della mappa`


`--enemy-character-distance | intero | distanza in unità che i nemici devono tenere dal personaggio`


`--enemy-movement-tick-interval | intero | numero di tick da aspettare per un movimento dei nemici`


`--enemy-shoot-tick-interval | intero | numero di tick da aspettare per uno sparo dei nemici`


`--enemy-base-life | intero | valore iniziale e massimo della vita dei nemici`


`--enemy-base-laser-damage | intero | numero base di punti vita sottratti da uno sparo nemico`


`--character-base-laser-damage | intero | numero base di punti vita sottratti da uno sparo del personaggio`


`--powerup-points-increase | intero | numero di punti ricompensati quando si raccoglie un powerup`


`--enemy-kill-points-increase | intero | numero di punti ricompensati quando si uccide un nemico`


`--map-exploration-points-increase | intero | numero di punti ricompensati esplorando la mappa`


`--map-extension-points-increase | intero | numero di punti ricompensati quando la mappa si estende`

Esempio di configurazione a linea di comando:
`~ ./run.sh --game-height=60 --game-width=100 --map-wall-padding=3 --console-mode=true --console-lines=5 --io-inactive-ticks=50 --character-jump-velocity=10 --gravity-ticks=70 --map-offsetting-min=10 --map-offsetting-max=40 --map-offset-threshold=100 --rocks-gen-count=10 --rock-gen-collision-padding=3 --max-character-life=100 --character-reattack-ticks=300 --powerup-heal-amount=10 --powerup-max-gen-amount=1 --powerup-max-total-jump=5 --enemy-gen-count=3 --enemy-character-distance=30 --enemy-movement-tick-interval=150 --enemy-shoot-tick-interval=1000 --enemy-base-life=100 --enemy-base-laser-damage=5 --character-base-laser-damage=20 --powerup-points-increase=20 --map-exploration-points-increase=1 --map-extension-points-increase=5`

##### Struttura del progetto
La struttura del codice sorgente è suddivisa in categorie.
Nella directory root si trova il file comune `common.hpp` (definisce i valori standard delle variabili di configurazione, le varie sprite serializzate come laser e rocce, i colori utilizzabili dalla console etc.), il file `main.cpp` contenente l'entry point del programma e 3 directory categorizzate.
La directory `data` contiene le classi usate per immagazzinare dati generici del gioco come dizionari (non utilizzati), vettori e coordinate cartesiane a due dimensioni.
La directory `utils` contiene le implementazioni delle funzioni standard matematiche (min/max), di memoria (memcpy/memset/hash), di runtime (assert/strtok/strcmp/atoi/strlen) e di meta-programmazione (nello specifico, determinare se un argomento generico è un puntatore).
La directory `game` contiene le entità di gioco e generalmente tutte le classi relative alle meccaniche di gioco.
Tutte le classi del gioco si basano fortemente sull'uso dei namespace per mantenere il codice chiaro ed ordinato.

##### Entry point
L'entry point del programma si occupa di instanziare la classe `game`, la quale rappresenta la radice dell'albero dei componenti di gioco.
Si occupa, inoltre, di gestire un loop infinito di chiamate alle funzioni `render` e `tick` per la gestione grafica e logica dei componenti di gioco.

##### Struttura del gioco
Il gioco ha una struttura ad albero realizzata tramite la classe `game_component`, la quale può ospitare N figli di tipo `game_component`.
Chiamate grafiche, di i/o e di logica come `render`, `tick`, `check_collision` ed `on_keyboard` vengono propagate a tutti i figli, permettendo di scrivere meno codice possibile per ogni componente del gioco e personalizzare il comportamento dello stesso a livello di classe.
I componenti permettono anche di accedere al nodo padre ed ad i vari componenti chiave del gioco come `game` (radice dell'albero), `game_character` (personaggio di gioco), `game_map` (mappa di gioco), `game_settings` (configurazione del gioco).
La classe base dei componenti si occupa anche di tenere traccia della posizione e direzione di ogni componente.

##### Motore di gioco
Il progetto implementa un rudimentale motore grafico utilizzando alla base la libreria `ncurses`.
I due metodi chiave sono `render` (dove gli elementi di gioco vengono disegnati) e `tick` (dove gli elementi di gioco calcolano la propria logica).
Per il calcolo temporale viene utilizzato il numero di tick (= numero di chiamate alla funzione `tick`) in mancanza di appropriate librerie.
Il numero di tick viene inoltre utilizzato per generare numeri casuali utili alla generazione dinamica di mappa e nemici.
Per gestire l'aspetto grafico e di input da tastiera viene utilizzata la classe `game_io`.
L'input da tastiera viene propagato ad ogni componente fino a che uno di essi non segnala la "cattura" dell'input (valore di ritorno booleano), a scopo pratico, però, l'input da tastiera viene utilizzato solo dalla classe gestente il personaggio di gioco.
Per gestire le collisioni viene propagata la chiamata alla classe `check_collision` in ogni componente tramite la funzione `check_game_collision` (la quale si occupa di chiamare il metodo `check_collision` nella classe radice `game`).
La propagazione si ferma quando un componente segnala una collisione, in questo caso il componente stesso (`this`) viene ritornato, in questo modo si può determinare quale componente viene incrociato nello spazio di gioco.

##### Mappa di gioco
L'entità della mappa di gioco si limita ad essere il "pavimento" dove personaggio e mostri camminano, il "soffitto" ed il muro iniziale, viene gestita dalla classe `game_map`.
La mappa include un "offset" per creare uno scorrimento progressivo di essa, questo offset viene poi utilizzato da tutti gli altri componenti per determinare la posizione relativa sullo schermo (absolute_x - offset).
Il rendering viene inoltre saltato se la posizione relativa esce dai bordi di gioco.
Un altro aspetto gestito dalla mappa è la generazione dinamica di nemici, powerup e rocce su cui saltare e camminare.
Quando l'offset raggiunge un certo limite (configurabile) la mappa verrà "estesa", cioè verranno generate ulteriori rocce, nemici e powerup.
L'avanzamento e l'espansione della mappa comporta il ricevimento di punti di gioco.

##### Generazione dinamica
La generazione dinamica avviene in modo controllato dalla mappa di gioco e tiene conto delle collisioni tra componenti, permettendo per quanto possibile di evitare di generare componenti dentro altri componenti, creando glitch grafici.
Per quanto concerne le rocce ed i powerup, il numero di essi è fisso ed è definito nelle variabili di configurazione.
Per i nemici, invece, esiste un numero base definito nelle variabili di configurazione.
Al numero base di nemici da generare viene poi aggiunto il numero di powerup acquisiti per il laser ed il salto, in questo modo il gioco risulterà più difficile man mano che il personaggio viene migliorato.

##### Rocce
Le rocce vengono generate dinamicamente e vengono gestite dalla classe `game_rock`.
Esistono diversi tipi di rocce, definite nel file `common.hpp` (namespace `sprites`), la scelta della roccia da generare avviene in modo casuale.
L'implementazione di esse consente di aggiungerne di nuove semplicemente disegnandole nel file header comune.
La distanza minima tra una roccia e l'altra può essere configurata tramite le variabili di configurazione.

##### Personaggio
Il personaggio di gioco è l'unico componente dove le coordinate assolute coincidono con le coordinate relative su schermo, questo avviene perchè, per struttura, il personaggio è sempre visualizzato a schermo.
Viene gestito dalla classe `game_character` ed è inoltre l'unico componente a gestire l'input da tastiera.
Per muoversi, vengono utilizzati i tasti freccia destro/sinistro, per saltare il tasto freccia sù, per sparare la barra spaziatrice.
Le collisioni vengono controllate in più punti, come sul salto (se viene toccato un componente con la testa la salita si interrompe), alla base (se non c'è collisione alle gambe il personaggio inizierà la discesa) e su movimenti a destra/sinistra.
La classe si occupa anche di controllare se esiste una collisione con un powerup (per raccoglierlo) e per la determinazione del game over (se la vita del personaggio arriva a 0).

##### Powerup
I powerup sono gestiti dalla classe `game_powerup` e sono sempre generati ad un'altezza fissa.
Quando vengono generati e visualizzati dal giocatore, essi iniziano una discesa finchè una collisione non viene riscontrata sul basso, in quel caso la discesa termina.
Esistono 3 tipi di powerup e vengono riconosciuti tramite i simboli al centro di essi (`+`, `>`, `^`): 

`heal`: consente al personaggio di recuperare vita persa nello scontro con nemici

`laser`: consente al personaggio di potenziare il proprio laser e di infliggere, di conseguenza, più danno ai nemici

`jump`: consente al personaggio di saltare più in alto

L'acquisizione di un powerup `laser` o `jump` comporta l'aumentare dei nemici generati alla prossima espansione della mappa, mentre l'acquisizione di qualsiasi powerup fa guadagnare punti di gioco.

##### Nemici
I nemici, come rocce e powerup, vengono generati dinamicamente.
Ogni nemico estende la classe `game_enemy`, la quale si occupa di instanziare la classe del nemico corrispondente, calcolare la posizione del personaggio relativa al nemico (in modo che il nemico possa seguire e sparare al personaggio in modo preciso), come anche la gestione dei punti vita e la morte del nemico.
Nel gioco sono implementati due tipi di nemici:
`trooper`: nemico di terra, può saltare ed è soggetto a collisioni (gestito dalla classe `game_trooper`)
`flyier`: nemico d'aria, vola e non collide con i componenti della mappa (gestito dalla classe `game_flyier`)

##### Laser
I nemici come il personaggio di gioco utilizzano il laser gestito dalla classe `game_laser` per arrecarsi danno a vicenda.
In quanto il calcolo della collisione per tutti i laser ha un'alta complessità computazionale il componente viene cancellato se il laser raggiunge il limite della mappa.
Il danno arrecato dal laser viene determinato dalla configurazione del danno associata moltiplicata per il livello del laser.
Ad ogni livello viene associato una grafica diversa definita nel namespace `sprites` nel file header comune.
Per struttura non è possibile per un componente arrecare danno ad un componente simile (=i mostri non possono danneggiarsi a vicenda).

##### Menu
A destra della mappa di gioco (escluso dalla configurazione `--game-width`) viene renderizzato un menu che mostra la vita del personaggio, i punti di gioco accumulati e lo stato dei vari powerup.



