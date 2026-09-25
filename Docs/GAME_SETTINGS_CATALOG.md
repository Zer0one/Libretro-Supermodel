# Catalogo autorevole dei Game Settings SEGA Model 3

Stato: campagna in corso.

Questo documento trascrive i Service Menu acquisiti direttamente con il core
Libretro. Gli screenshot sono la fonte autorevole per presenza, ordine, default
visibile e valori selezionabili. `Config/Games.xml` viene usato soltanto per
identità del set, titolo e relazione parent/clone. Le tabelle di implementazione
e le precedenti ricette NVRAM non vengono usate per dedurre dati mancanti. Le
ricette vengono però riutilizzate come percorso di navigazione già validato,
in particolare per le schermate nascoste e le combinazioni di tasti Country.
Per i cloni, presenza, ordine e default entrano nel catalogo solo dopo la
verifica dello screenshot; i cicli del parent possono essere attribuiti alle
righe corrispondenti soltanto indicandone esplicitamente la provenienza.

## Revisione e copertura

- sorgente core: `c4684561f4911842b478a84e4262a1f15d2922ab`;
- SHA-256 del core acquisito: `a347ed61a53475bbfc721f864dd5d8570330b1e8c6b8d994fa905ca886f7585d`;
- SHA-256 di `Config/Games.xml`:
  `275832cdb077c22883192f5aaeb8f76547f4dce786370f10b2d54c46a8ed3c5e`;
- inventario sorgente: 63 set;
- perimetro della campagna: 62 set, composto da 22 parent e 40 cloni;
- esclusione: `mgtrkbad`, bad dump non acquisibile;
- parent acquisiti: 22 / 22;
- cloni acquisiti o classificati direttamente: 38 / 40;
- screenshot primari indicizzati: 510, di cui 419 parent e 91 cloni.

Le catture dedicate al valore iniziale di `dirtdvls`, `fvipers2`, `magtruck` e
`spikeout` sono state ripetute e ora raggiungono la riga attesa. `dirtdvls` e
`spikeout` richiedono 12 secondi di attesa iniziale; `fvipers2` ne richiede 25
per superare la schermata di avvertenza regionale. Anche `bassdx` richiede 12
secondi prima di accettare Test/Service. Le sequenze di navigazione delle
ricette restano invariate.

Il conteggio comprende i PNG collocati direttamente nelle cartelle
`screenshots`. Diciassette catture esplorative di `lostwsga` e venticinque
catture secondarie dei cloni, risultate copie o ripetizioni logiche di pagine
già documentate, sono conservate in `screenshots/redundant`. Quattro schermate
diagnostiche che non rappresentano settings sono conservate in
`screenshots/non-settings`. Nessuna di queste viene conteggiata come evidenza
primaria.

I file PNG, i log e i profili temporanei restano fuori dal repository in
`~/Documents/RetroArch/model3-game-settings-catalog`. Ogni ciclo parte dalla
baseline immutabile del set, con `Automatic Initial NVRAM Setup` e `NVRAM
Settings` disabilitati. La SRAM prodotta incidentalmente da RetroArch viene
scartata nelle acquisizioni destinate al solo catalogo.

## Regole di lettura

- **Valori osservati** contiene solo valori fotografati durante il ciclo.
- Una riga visibile ma non modificabile è indicata esplicitamente.
- Un clone non eredita struttura o default dal parent: la sua acquisizione
  diretta deve dimostrare righe, ordine e default. I valori del parent possono
  essere derivati in seguito per una riga corrispondente, mantenendo distinta
  la loro provenienza dai valori ciclati direttamente sul clone.
- I default riportati nel catalogo sono quelli nativi fotografati. Il frontend
  applica separatamente l'override Country concordato: Export se disponibile,
  altrimenti USA.
- Le etichette descrittive del core non sostituiscono la rappresentazione del
  Service Menu. Per esempio, The Lost World mostra la difficoltà come barra a
  sedici posizioni, senza la dicitura `Level N`.

## Parent

### The Lost World (`lostwsga`)

- **Versione:** Japan, Revision A
- **Menu:** Game Assignments; Country Select Mode
- **Schermata base:** [apri screenshot](</Users/andrea/Documents/RetroArch/model3-game-settings-catalog/lostwsga/screenshots/lostwsga-difficulty-00.png>)
- **Country Select Mode:** [apri screenshot](</Users/andrea/Documents/RetroArch/model3-game-settings-catalog/lostwsga/screenshots/lostwsga-country-assignments-00.png>)
- **Screenshot primari:** 36

| # | Game Setting | Default visibile | Valori osservati negli screenshot | Evidenza |
| ---: | --- | --- | --- | --- |
| 1 | GAME DIFFICULTY | barra 8 / 16 | barre da 1 / 16 a 16 / 16 | base + ciclo completo |
| 2 | ADVERTISE SOUND | ON | ON, OFF | base + ciclo completo |
| 3 | LIFE | 3 | 1, 2, 3, 4, 5, 6, 7, 8, 9 | base + ciclo completo |
| 4 | COUNTRY | JAPAN | JAPAN, USA, EXPORT, AUSTRALIA | riga non modificabile in Game Assignments; ciclo completo in Country Select Mode |
| 5 | BOSS ACTION | NORMAL | NORMAL, MILD | base + ciclo completo |

La difficoltà parte dalla posizione 8 / 16, sale fino a 16 / 16 e prosegue da
1 / 16 a 7 / 16 prima di tornare al default. `COUNTRY` non cambia premendo Test
nella schermata Game Assignments: la selezione avviene nella schermata separata
Country Select Mode. La sequenza primaria conserva una sola fotografia della
riga non modificabile, due valori di ADVERTISE SOUND, nove di LIFE, due di BOSS
ACTION e quattro di COUNTRY. I diciassette fotogrammi ripetuti prodotti dalle
prime prove sono separati in `screenshots/redundant`.

### Daytona USA 2 - Battle on the Edge (`daytona2`)

- **Versione:** Japan, Revision A
- **Menu:** Game Assignments; Country Assignments nascosto
- **Schermata base:** [apri screenshot](</Users/andrea/Documents/RetroArch/model3-game-settings-catalog/daytona2/screenshots/daytona2-game-assignments-base.png>)
- **Country Assignments:** [apri screenshot](</Users/andrea/Documents/RetroArch/model3-game-settings-catalog/daytona2/screenshots/daytona2-country-assignments-base.png>)
- **Screenshot primari:** 35

| # | Game Setting | Default visibile | Valori osservati negli screenshot | Evidenza |
| ---: | --- | --- | --- | --- |
| 1 | COUNTRY | JAPAN | JAPAN, USA, EXPORT, AUSTRALIA, KOREA | base + ciclo completo nella schermata nascosta Country Assignments |
| 2 | LINK ID | MASTER | MASTER, SLAVE, LIVE, SINGLE | base + ciclo completo |
| 3 | CAR NUMBER | 1 | da 1 a 16 | base + ciclo completo; disponibile con LINK ID MASTER |
| 4 | CABINET TYPE | TWIN | TWIN, DELUXE | base + ciclo completo |
| 5 | DIFFICULTY | NORMAL | NORMAL, HARD, HARDER, EASY | base + ciclo completo |
| 6 | ADVERTISE SOUND | ON | ON | sola schermata base; ciclo da acquisire |
| 7 | VOCAL | DENNIS | DENNIS, MITSUYOSHI | base + ciclo completo |
| 8 | GAME MODE | NORMAL(SPRINT) | NORMAL(SPRINT) | sola schermata base; ciclo da acquisire |
| 9 | MOTOR POWER | 80% | 80% | sola schermata base; ciclo da acquisire |
| 10 | RANKING MODE | NORMAL | NORMAL | sola schermata base; ciclo da acquisire |

I 33 campioni già presenti nella ricetta storica sono stati riutilizzati senza
alterarne le combinazioni. La schermata Country nascosta ha confermato cinque
valori; le altre quattro impostazioni visibili saranno percorse con campioni
supplementari perché non fanno parte della ricetta NVRAM corrente.

### Emergency Call Ambulance (`eca`)

- **Versione:** Export
- **Menu:** Game Assignments
- **Schermata base:** [apri screenshot](</Users/andrea/Documents/RetroArch/model3-game-settings-catalog/eca/screenshots/eca-game-assignments-base.png>)
- **Screenshot primari:** 6

| # | Game Setting | Default visibile | Valori osservati negli screenshot | Evidenza |
| ---: | --- | --- | --- | --- |
| 1 | DIFFICULTY | NORMAL | NORMAL, HARD, VERY HARD, VERY EASY, EASY | base + ciclo completo |
| 2 | ADVERTISE SOUND | ON | ON | sola schermata base; ciclo da acquisire |
| 3 | MILE/METER | METER | METER | sola schermata base; ciclo da acquisire |
| 4 | GAME OVER COLOR | RED | RED | sola schermata base; ciclo da acquisire |
| 5 | GAME OVER LINE | ON | ON | sola schermata base; ciclo da acquisire |
| 6 | GAME OVER SOUND | ON | ON | sola schermata base; ciclo da acquisire |
| 7 | SIREN VOLUME | 7 | 7 | sola schermata base; ciclo da acquisire |
| 8 | STEERING REACTION | 4 | 4 | sola schermata base; ciclo da acquisire |
| 9 | GEAR LEVER | UP/DOWN | UP/DOWN | sola schermata base; ciclo da acquisire |
| 10 | TOURNAMENT MODE | OFF | OFF | sola schermata base; ciclo da acquisire |

I cinque campioni della ricetta storica hanno confermato l'intero ciclo della
difficoltà. Le altre nove impostazioni, pur essendo già censite dalla schermata
base, richiedono campioni supplementari.

### Virtua Fighter 3 (`vf3`)

- **Versione:** Japan, Revision D
- **Menu:** Game Assignments
- **Schermata base:** [apri screenshot](</Users/andrea/Documents/RetroArch/model3-game-settings-catalog/vf3/screenshots/vf3-game-assignments-base.png>)
- **Screenshot primari:** 10

| # | Game Setting | Default visibile | Valori osservati negli screenshot | Evidenza |
| ---: | --- | --- | --- | --- |
| 1 | MATCH COUNT(1P) | 2 | 2 | sola schermata base; ciclo da acquisire |
| 2 | MATCH COUNT(VS) | 3 | 3 | sola schermata base; ciclo da acquisire |
| 3 | DIFFICULTY | NORMAL | NORMAL, HARD, HARDEST, EASY | base + ciclo completo |
| 4 | ENERGY MAX(1P) | 180 | 180 | sola schermata base; ciclo da acquisire |
| 5 | ENERGY MAX(VS) | 200 | 200 | sola schermata base; ciclo da acquisire |
| 6 | ADVERTISE SOUND | ON | ON | sola schermata base; ciclo da acquisire |
| 7 | RANKING MODE | ON | ON | sola schermata base; ciclo da acquisire |
| 8 | REPLAY CANCEL | ON | ON | sola schermata base; ciclo da acquisire |
| 9 | COMMAND DISP | OFF | OFF | sola schermata base; ciclo da acquisire |
| 10 | STAGE SELECT | OFF | OFF | sola schermata base; ciclo da acquisire |
| 11 | DRINK | OK | OK | sola schermata base; ciclo da acquisire |
| 12 | NAKED | OK | OK | sola schermata base; ciclo da acquisire |
| 13 | COUNTRY | JAPAN | JAPAN, USA, EXPORT, ASIA | base + ciclo completo |
| 14 | VS FINISH | 0 | 0 | sola schermata base; ciclo da acquisire |

Gli otto campioni della ricetta storica hanno confermato integralmente i cicli
DIFFICULTY e COUNTRY. `INITIALIZE` è un comando del menu e non viene catalogato
come impostazione.

### Virtua Striker 2 (`vs2`)

- **Versione:** Step 2.0, Export, USA
- **Menu:** Game Assignments
- **Schermata base:** [apri screenshot](</Users/andrea/Documents/RetroArch/model3-game-settings-catalog/vs2/screenshots/vs2-game-assignments-base.png>)
- **Screenshot primari:** 8

| # | Game Setting | Default visibile | Valori osservati negli screenshot | Evidenza |
| ---: | --- | --- | --- | --- |
| 1 | ADVERTISE SOUND | ON | ON | sola schermata base; ciclo da acquisire |
| 2 | COUNTRY | EXPORT | EXPORT, U.S.A | base + ciclo completo |
| 3 | DIFFICULTY | NORMAL | NORMAL, HARD, HARDEST, EASY | base + ciclo completo |
| 4 | VIRTUAL TIME | REAL | REAL | sola schermata base; ciclo da acquisire |
| 5 | BILLBOARD | ON | ON | sola schermata base; ciclo da acquisire |
| 6 | ONE MATCH MODE | OFF | OFF | sola schermata base; ciclo da acquisire |
| 7 | 1P TIME SET | 2'00\" | 2'00\" | sola schermata base; ciclo da acquisire |
| 8 | 1P V GOAL SYSTEM | OFF | OFF | sola schermata base; ciclo da acquisire |
| 9 | 1P PK SYSTEM | OFF | OFF | sola schermata base; ciclo da acquisire |
| 10 | VS TIME SET | 2'00\" | 2'00\" | sola schermata base; ciclo da acquisire |
| 11 | VS G GOAL SYSTEM | OFF | OFF | sola schermata base; ciclo da acquisire |
| 12 | VS PK SYSTEM | OFF | OFF | sola schermata base; ciclo da acquisire |

I sei campioni della ricetta storica hanno confermato integralmente i cicli
DIFFICULTY e COUNTRY.

### Fighting Vipers 2 (`fvipers2`)

- **Versione:** Japan, Revision A
- **Menu:** Game Assignments
- **Schermata base:** [apri screenshot](</Users/andrea/Documents/RetroArch/model3-game-settings-catalog/fvipers2/screenshots/fvipers2-game-assignments-base.png>)
- **Screenshot primari:** 11

| # | Game Setting | Default visibile | Valori osservati negli screenshot | Evidenza |
| ---: | --- | --- | --- | --- |
| 1 | MATCH COUNT(1P) | 2 | 2 | sola schermata base; ciclo da acquisire |
| 2 | MATCH COUNT(VS) | 3 | 3 | sola schermata base; ciclo da acquisire |
| 3 | ROUND TIME(1P) | 30 | 30 | sola schermata base; ciclo da acquisire |
| 4 | ROUND TIME(VS) | 45 | 45 | sola schermata base; ciclo da acquisire |
| 5 | DIFFICULTY | NORMAL | NORMAL, HARD, VERY HARD, VERY EASY, EASY | base + ciclo completo |
| 6 | ENERGY MAX(1P) | 210 | 210 | sola schermata base; ciclo da acquisire |
| 7 | ENERGY MAX(VS) | 210 | 210 | sola schermata base; ciclo da acquisire |
| 8 | ADVERTISE SOUND | ON | ON | sola schermata base; ciclo da acquisire |
| 9 | SURVIVAL MODE | OFF | OFF | sola schermata base; ciclo da acquisire |
| 10 | COUNTRY | JAPAN | JAPAN, USA, EXPORT, ASIA | base + ciclo completo |
| 11 | VS FINISH | OFF | OFF | sola schermata base; ciclo da acquisire |
| 12 | SUPER K.O. | ON | ON | sola schermata base; ciclo da acquisire |
| 13 | BIKE LOGO | ON | ON, `--` | base; `--` osservato con COUNTRY ASIA; ciclo proprio da acquisire |

I nove campioni della ricetta storica hanno confermato integralmente i cicli
DIFFICULTY e COUNTRY. Il ciclo Country mostra inoltre che `BIKE LOGO` non è
disponibile nella configurazione ASIA. La fotografia dedicata a NORMAL è stata
ripetuta dopo il completamento della schermata di avvertenza ed è inclusa tra
le evidenze primarie.

### Virtua Striker 2 '98 (`vs298`)

- **Versione:** Step 2.0, Japan
- **Menu:** Game Assignments; Change Country nascosto
- **Schermata base:** [apri screenshot](</Users/andrea/Documents/RetroArch/model3-game-settings-catalog/vs298/screenshots/vs298-game-assignments-base.png>)
- **Change Country:** [apri screenshot](</Users/andrea/Documents/RetroArch/model3-game-settings-catalog/vs298/screenshots/vs298-country-02-australia-selected.png>)
- **Screenshot primari:** 10

| # | Game Setting | Default visibile | Valori osservati negli screenshot | Evidenza |
| ---: | --- | --- | --- | --- |
| 1 | COUNTRY | JAPAN | JAPAN, USA, AUSTRALIA, EXPORT | base + ciclo completo nella schermata nascosta Change Country |
| 2 | ADVERTISE SOUND | ON | ON | sola schermata base; ciclo da acquisire |
| 3 | DIFFICULTY | NORMAL | NORMAL, HARD, HARDEST, EASY | base + ciclo completo |
| 4 | VIRTUAL TIME | REAL | REAL | sola schermata base; ciclo da acquisire |
| 5 | BILLBOARD | ON | ON | sola schermata base; ciclo da acquisire |
| 6 | ONE MATCH MODE | OFF | OFF | sola schermata base; ciclo da acquisire |
| 7 | 1P TIME SET | 2'00\" | 2'00\" | sola schermata base; ciclo da acquisire |
| 8 | 1P V GOAL SYSTEM | OFF | OFF | sola schermata base; ciclo da acquisire |
| 9 | 1P PK SYSTEM | OFF | OFF | sola schermata base; ciclo da acquisire |
| 10 | VS TIME SET | 2'00\" | 2'00\" | sola schermata base; ciclo da acquisire |
| 11 | VS V GOAL SYSTEM | OFF | OFF | sola schermata base; ciclo da acquisire |
| 12 | VS PK SYSTEM | OFF | OFF | sola schermata base; ciclo da acquisire |

Gli otto campioni della ricetta storica hanno confermato integralmente i cicli
DIFFICULTY e COUNTRY, compresa la combinazione che apre la schermata nascosta
Change Country.

### The Ocean Hunter (`oceanhun`)

- **Versione:** Japan, Revision A
- **Menu:** Game Assignments
- **Schermata base:** [apri screenshot](</Users/andrea/Documents/RetroArch/model3-game-settings-catalog/oceanhun/screenshots/oceanhun-game-assignments-base.png>)
- **Screenshot primari:** 13

| # | Game Setting | Default visibile | Valori osservati negli screenshot | Evidenza |
| ---: | --- | --- | --- | --- |
| 1 | COUNTRY | JAPAN | JAPAN, USA, EXPORT, AUSTRALIA, KOREA | base + ciclo completo |
| 2 | DIFFICULTY | NORMAL | NORMAL, HARD, HARDEST, EASY | base + ciclo completo |
| 3 | ADVERTISE SOUND | ON | ON | sola schermata base; ciclo da acquisire |
| 4 | CABINET TYPE | DELUXE | DELUXE, STANDARD | base + ciclo completo |
| 5 | CONTROLLER REACTION | ON | ON | sola schermata base; ciclo da acquisire |

Gli undici campioni della ricetta storica hanno confermato integralmente i
cicli COUNTRY, DIFFICULTY e CABINET TYPE.

### Ski Champ (`skichamp`)

- **Versione:** Japan
- **Menu:** Game Assignments; Country Select Mode; Network Assignments
- **Schermata base:** [apri screenshot](</Users/andrea/Documents/RetroArch/model3-game-settings-catalog/skichamp/screenshots/skichamp-game-assignments-base.png>)
- **Country Select Mode:** [apri screenshot](</Users/andrea/Documents/RetroArch/model3-game-settings-catalog/skichamp/screenshots/skichamp-country-04-australia-selected.png>)
- **Network Assignments:** [apri screenshot](</Users/andrea/Documents/RetroArch/model3-game-settings-catalog/skichamp/screenshots/skichamp-network-assignments-base.png>)
- **Screenshot primari:** 15

| # | Game Setting | Default visibile | Valori osservati negli screenshot | Evidenza |
| ---: | --- | --- | --- | --- |
| 1 | ADVERTISE SOUND | ON | ON | sola schermata base; ciclo da acquisire |
| 2 | DRIVE BOARD POWER | 2 | 2 | sola schermata base; ciclo da acquisire |
| 3 | INITIAL TIME | 30[SEC] | 30[SEC] | sola schermata base; ciclo da acquisire |
| 4 | EXTEND TIME | 20[SEC] | 20[SEC] | sola schermata base; ciclo da acquisire |
| 5 | AREA1 (MOUNTAINTOP) | 25[SEC] | 25[SEC] | sola schermata base; ciclo da acquisire |
| 6 | AREA2 (LARGE FOREST / SNOWY WASTELAND) | 25[SEC] | 25[SEC] | sola schermata base; ciclo da acquisire |
| 7 | AREA3 (GIGANTIC GLACIER / SNOWY CANYON) | 30[SEC] | 30[SEC] | sola schermata base; ciclo da acquisire |
| 8 | COUNTRY | JAPAN | JAPAN, USA, EXPORT, KOREA, AUSTRALIA | base + ciclo completo in Country Select Mode |
| 9 | COMMUNICATION | STAND-ALONE | STAND-ALONE, NETWORK | base + ciclo completo |
| 10 | PRIVILEGE MODE | non visibile con STAND-ALONE | MASTER, SLAVE | compare con COMMUNICATION NETWORK; ciclo completo |
| 11 | CABINET ID NUMBER | non visibile con STAND-ALONE | 1, 2, 3, 4 | compare con COMMUNICATION NETWORK; ciclo completo |

I dodici campioni della ricetta storica hanno confermato COUNTRY e l'intera
configurazione di rete. Le etichette storiche `link-00-stand-alone`,
`link-01-master` e `link-02-slave` corrispondono nel Service Menu a due righe:
`COMMUNICATION` seleziona STAND-ALONE o NETWORK, mentre `PRIVILEGE MODE`
distingue MASTER e SLAVE quando la rete è attiva.

### L.A. Machineguns: Rage of the Machines (`lamachin`)

- **Versione:** Japan
- **Menu:** Game Assignments; Country Select Mode
- **Schermata base:** [apri screenshot](</Users/andrea/Documents/RetroArch/model3-game-settings-catalog/lamachin/screenshots/lamachin-game-assignments-base.png>)
- **Country Select Mode:** [apri screenshot](</Users/andrea/Documents/RetroArch/model3-game-settings-catalog/lamachin/screenshots/lamachin-country-03-australia-selected.png>)
- **Screenshot primari:** 16

| # | Game Setting | Default visibile | Valori osservati negli screenshot | Evidenza |
| ---: | --- | --- | --- | --- |
| 1 | GAME DIFFICULTY | barra 5 / 8 | barre da 1 / 8 a 8 / 8 | base + ciclo completo |
| 2 | PLAYER LIFE | 3 | 3 | sola schermata base; ciclo da acquisire |
| 3 | GUN ACTION | ON | ON | sola schermata base; ciclo da acquisire |
| 4 | ADVERTISE SOUND | ON | ON | sola schermata base; ciclo da acquisire |
| 5 | CABINET TYPE | STANDERD | STANDERD, DELUXE | base + ciclo completo; grafia del Service Menu conservata |
| 6 | BASS SHAKER | non visibile con STANDERD | OFF | compare con CABINET TYPE DELUXE; ciclo da acquisire |
| 7 | COUNTRY CODE | JAPAN | JAPAN, USA, EXPORT, AUSTRALIA | ciclo completo in Country Select Mode |

I quattordici valori della ricetta storica corrispondono alle fotografie di
GAME DIFFICULTY, COUNTRY CODE e CABINET TYPE. Il passaggio a DELUXE rende
visibile anche `BASS SHAKER`, voce non coperta dalla ricetta corrente.

### Star Wars Trilogy Arcade (`swtrilgy`)

- **Versione:** Export, Revision A
- **Menu:** Game Assignments; Country Select
- **Schermata base:** [apri screenshot](</Users/andrea/Documents/RetroArch/model3-game-settings-catalog/swtrilgy/screenshots/swtrilgy-game-assignments-base.png>)
- **Country Select:** [apri screenshot](</Users/andrea/Documents/RetroArch/model3-game-settings-catalog/swtrilgy/screenshots/swtrilgy-country-04-korea-selected.png>)
- **Screenshot primari:** 16

| # | Game Setting | Default visibile | Valori osservati negli screenshot | Evidenza |
| ---: | --- | --- | --- | --- |
| 1 | COUNTRY | EXPORT | EXPORT, JAPAN, USA, AUSTRALIA, KOREA | base + ciclo completo nella schermata Country Select |
| 2 | ADVERTISE SOUND | ON | ON | sola schermata base; ciclo da acquisire |
| 3 | DIFFICULTY | NORMAL | NORMAL, HARD, VERY HARD, VERY EASY, EASY | base + ciclo completo |
| 4 | CABINET TYPE | DX | DX, U/R | base + ciclo completo |
| 5 | FEEDBACK LEVER | ENABLE | ENABLE, DISABLE | visibile con CABINET TYPE DX; ciclo completo |

I quattordici valori della ricetta storica corrispondono alle fotografie di
COUNTRY, DIFFICULTY, CABINET TYPE e FEEDBACK LEVER. Con CABINET TYPE U/R la
riga FEEDBACK LEVER non viene mostrata.

### Spikeout Final Edition (`spikeofe`)

- **Versione:** Export
- **Menu:** Game Assignments; Country Setting
- **Schermata base:** [apri screenshot](</Users/andrea/Documents/RetroArch/model3-game-settings-catalog/spikeofe/screenshots/spikeofe-game-assignments-base.png>)
- **Country Setting:** [apri screenshot](</Users/andrea/Documents/RetroArch/model3-game-settings-catalog/spikeofe/screenshots/spikeofe-country-01-australia-selected.png>)
- **Screenshot primari:** 15

| # | Game Setting | Default visibile | Valori osservati negli screenshot | Evidenza |
| ---: | --- | --- | --- | --- |
| 1 | COUNTRY | EXPORT | EXPORT, AUSTRALIA, JAPAN, USA | base + ciclo completo nella schermata Country Setting |
| 2 | GAME DIFFICULTY | NORMAL | NORMAL, HARD, HARDEST, EASIEST, EASY | base + ciclo completo |
| 3 | ADVERTISE SOUND | ON | ON | sola schermata base; ciclo da acquisire |
| 4 | COMM ID | SINGLE | SINGLE, MASTER, SLAVE | base + ciclo completo |

I dodici valori della ricetta storica corrispondono alle fotografie di COUNTRY,
GAME DIFFICULTY e COMM ID. `INITIALIZE` è un comando del menu e non viene
catalogato come impostazione.

### Dirt Devils (`dirtdvls`)

- **Versione:** Export, Revision A
- **Menu:** Game Assignments; Country Select Mode
- **Schermata base:** [apri screenshot](</Users/andrea/Documents/RetroArch/model3-game-settings-catalog/dirtdvls/screenshots/dirtdvls-game-assignments-base.png>)
- **Country Select Mode:** [apri screenshot](</Users/andrea/Documents/RetroArch/model3-game-settings-catalog/dirtdvls/screenshots/dirtdvls-country-assignments-base.png>)
- **Screenshot primari:** 30

| # | Game Setting | Default visibile | Valori osservati negli screenshot | Evidenza |
| ---: | --- | --- | --- | --- |
| 1 | COUNTRY / COUNTRY CODE | EXPORT | EXPORT, AUSTRALIA, JAPAN, USA | base + ciclo completo in Country Select Mode |
| 2 | GAME DIFFICULTY | barra 9 / 16 | barre da 1 / 16 a 16 / 16 | base + ciclo completo |
| 3 | TIME (CANYON) | NORMAL | NORMAL | sola schermata base; ciclo da acquisire |
| 4 | TIME (STADIUM) | NORMAL | NORMAL | sola schermata base; ciclo da acquisire |
| 5 | TIME (DESERT) | NORMAL | NORMAL | sola schermata base; ciclo da acquisire |
| 6 | STEERING FORCE | 80% | 80% | sola schermata base; ciclo da acquisire |
| 7 | ADVERTISE SOUND | ON | ON | sola schermata base; ciclo da acquisire |
| 8 | COMMUNICATION MODE | SLAVE | SLAVE, SATELLITE, NOLINK, MASTER | base + ciclo completo |
| 9 | MACHINE ID | 1 | 1, 2, 3, 4 | base + ciclo completo |
| 10 | SPEED METER | KM/H | KM/H | sola schermata base; ciclo da acquisire |

I ventotto valori della ricetta storica corrispondono alle fotografie di GAME
DIFFICULTY, COUNTRY CODE, COMMUNICATION MODE e MACHINE ID. La fotografia
dedicata alla barra 9 / 16 è stata ripetuta con l'attesa iniziale corretta ed è
inclusa tra le evidenze primarie.

### Harley-Davidson and L.A. Riders (`harley`)

- **Versione:** Export, Revision B
- **Menu:** Game Assignments; Country nascosto; Network Assignments
- **Schermata base:** [apri screenshot](</Users/andrea/Documents/RetroArch/model3-game-settings-catalog/harley/screenshots/harley-game-assignments-base.png>)
- **Country nascosto:** [apri screenshot](</Users/andrea/Documents/RetroArch/model3-game-settings-catalog/harley/screenshots/harley-country-04-usa-selected.png>)
- **Network Assignments:** [apri screenshot](</Users/andrea/Documents/RetroArch/model3-game-settings-catalog/harley/screenshots/harley-network-assignments-base.png>)
- **Screenshot primari:** 24

| # | Game Setting | Default visibile | Valori osservati negli screenshot | Evidenza |
| ---: | --- | --- | --- | --- |
| 1 | DIFFICULTY | NORMAL | NORMAL, +05SEC, +10SEC, +15SEC, +20SEC, -10SEC, -05SEC | base + ciclo completo |
| 2 | ADVERTISE SOUND | ON | ON | sola schermata base; ciclo da acquisire |
| 3 | CABINET TYPE | DELUXE | DELUXE, STANDARD | base + ciclo completo |
| 4 | BGM VOLUME | 4 | 4 | sola schermata base; ciclo da acquisire |
| 5 | ENGINE VOLUME | 8 | 8 | sola schermata base; ciclo da acquisire |
| 6 | NUMBER OF STAGES | 4 | 4 | sola schermata base; ciclo da acquisire |
| 7 | TOURNAMENT MODE | OFF | OFF | sola schermata base; ciclo da acquisire |
| 8 | COUNTRY | EXPORT | EXPORT, KOREA, AUSTRALIA, JAPAN, U.S.A. | ciclo completo nella schermata nascosta |
| 9 | COMMUNICATION | STAND-ALONE | STAND-ALONE, NETWORK | base + ciclo completo |
| 10 | PRIVILEGE MODE | non visibile con STAND-ALONE | MASTER, SLAVE | compare con COMMUNICATION NETWORK; ciclo completo |
| 11 | CABINET ID NUMBER | non visibile con STAND-ALONE | 1, 2, 3, 4 | compare con COMMUNICATION NETWORK; ciclo completo |

I ventuno valori della ricetta storica corrispondono alle fotografie di
DIFFICULTY, COUNTRY, CABINET TYPE e configurazione di rete.

### Magical Truck Adventure (`magtruck`)

- **Versione:** Japan
- **Menu:** Game Assignments; Country Select Mode
- **Schermata base:** [apri screenshot](</Users/andrea/Documents/RetroArch/model3-game-settings-catalog/magtruck/screenshots/magtruck-game-assignments-base.png>)
- **Country Select Mode:** [apri screenshot](</Users/andrea/Documents/RetroArch/model3-game-settings-catalog/magtruck/screenshots/magtruck-country-assignments-base.png>)
- **Screenshot primari:** 23

| # | Game Setting | Default visibile | Valori osservati negli screenshot | Evidenza |
| ---: | --- | --- | --- | --- |
| 1 | GAME DIFFICULTY | barra 8 / 16 | barre da 1 / 16 a 16 / 16 | base + ciclo completo |
| 2 | DAMAGE RECOVERY | barra | barra al default | sola schermata base; ciclo da acquisire |
| 3 | BOSS DIFFICULTY | NORMAL | NORMAL | sola schermata base; ciclo da acquisire |
| 4 | ADVERTISE SOUND | ON | ON | sola schermata base; ciclo da acquisire |
| 5 | CHRISTMAS MODE | OFF | OFF, ON | base + ciclo completo |
| 6 | COUNTRY / COUNTRY CODE | EXPORT | EXPORT, AUSTRALIA, USA | base + ciclo completo in Country Select Mode |

I ventuno valori della ricetta storica corrispondono alle fotografie di GAME
DIFFICULTY, COUNTRY CODE e CHRISTMAS MODE. La fotografia dedicata alla barra 8
/ 16 è stata ripetuta ed è inclusa tra le evidenze primarie.

### Scud Race (`scud`)

- **Versione:** Export, Twin/DX
- **Menu:** Game Assignments
- **Schermata base:** [apri screenshot](</Users/andrea/Documents/RetroArch/model3-game-settings-catalog/scud/screenshots/scud-game-assignments-base.png>)
- **Screenshot primari:** 23

| # | Game Setting | Default visibile | Valori osservati negli screenshot | Evidenza |
| ---: | --- | --- | --- | --- |
| 1 | LINK ID | MASTER | MASTER, SLAVE, SINGLE | base + ciclo completo |
| 2 | CAR NUMBER | 1 | da 1 a 8 | base + ciclo completo |
| 3 | CABINET TYPE | TWIN | TWIN, DELUXE | base + ciclo completo |
| 4 | COUNTRY | JAPAN | JAPAN, USA, EXPORT | base + ciclo completo |
| 5 | DIFFICULTY | NORMAL | NORMAL, HARD, HARDEST, EASY | base + ciclo completo |
| 6 | ADVERTISE SOUND | ON | ON | sola schermata base; ciclo da acquisire |
| 7 | GAME MODE | NORMAL(SPRINT) | NORMAL(SPRINT) | sola schermata base; ciclo da acquisire |
| 8 | MOTOR POWER | 80% | 80% | sola schermata base; ciclo da acquisire |
| 9 | MULTI DISPLAY | OFF | OFF | sola schermata base; ciclo da acquisire |

I venti valori della ricetta storica corrispondono alle fotografie di LINK ID,
CAR NUMBER, CABINET TYPE, COUNTRY e DIFFICULTY.

### Le Mans 24 (`lemans24`)

- **Versione:** Japan, Revision B
- **Menu:** Game Assignments; Country Select Mode
- **Schermata base:** [apri screenshot](</Users/andrea/Documents/RetroArch/model3-game-settings-catalog/lemans24/screenshots/lemans24-game-assignments-base.png>)
- **Screenshot primari:** 40

| # | Game Setting | Default visibile | Valori osservati negli screenshot | Evidenza |
| ---: | --- | --- | --- | --- |
| 1 | GAME DIFFICULTY | barra 8 / 16 | barre da 1 / 16 a 16 / 16 | base + ciclo completo |
| 2 | ADVERTISE SOUND | ON | ON | sola schermata base; ciclo da acquisire |
| 3 | CABINET TYPE | TWIN-LEMANS | TWIN-LEMANS, TWIN-NORMAL | base + ciclo completo |
| 4 | COMMUNICATION MODE | NO LINK | NO LINK, MASTER, SLAVE | base + ciclo completo |
| 5 | MOTOR DRIVE | 80% | 80% | sola schermata base; ciclo da acquisire |
| 6 | SPECIAL CAR | NONE | NONE, MCLAREN, SKYLINE, FERRARI, PORSCHE, MAZDA, ZAUBER | base + ciclo completo |
| 7 | DEFAULT TIME | NORMAL | NORMAL | sola schermata base; ciclo da acquisire |
| 8 | CONTINUE TIME | NORMAL | NORMAL | sola schermata base; ciclo da acquisire |
| 9 | GOAL TIME | NORMAL | NORMAL | sola schermata base; ciclo da acquisire |
| 10 | CABINET NUMBER | 1 | 1, 2, 3, 4, SATELLITE | base + ciclo completo |
| 11 | COUNTRY | JAPAN | JAPAN, USA, EXPORT, AUSTRALIA | base + ciclo completo in Country Select Mode |

I trentasette valori della ricetta storica corrispondono alle fotografie di
GAME DIFFICULTY, COUNTRY, CABINET TYPE, COMMUNICATION MODE, CABINET NUMBER e
SPECIAL CAR.

### Sega Rally 2 (`srally2`)

- **Versione:** Export
- **Menu:** Game Assignments; Country Select
- **Schermata base:** [apri screenshot](</Users/andrea/Documents/RetroArch/model3-game-settings-catalog/srally2/screenshots/srally2-game-assignments-base.png>)
- **Country Select:** [apri screenshot](</Users/andrea/Documents/RetroArch/model3-game-settings-catalog/srally2/screenshots/srally2-country-03-australia-selected.png>)
- **Screenshot primari:** 21

| # | Game Setting | Default visibile | Valori osservati negli screenshot | Evidenza |
| ---: | --- | --- | --- | --- |
| 1 | ADVERTISE SOUND | ON | ON | sola schermata base; ciclo da acquisire |
| 2 | DIFFICULTY | NORMAL | NORMAL, HARD, VERY HARD, VERY EASY, EASY | base + ciclo completo |
| 3 | GAME MODE | NORMAL | NORMAL | sola schermata base; ciclo da acquisire |
| 4 | DEFAULT VIEW | DRIVER | DRIVER, BEHIND | base + ciclo completo |
| 5 | SPEED | KM/H | KM/H | sola schermata base; ciclo da acquisire |
| 6 | COCKPIT REACTION | ENABLE | ENABLE | sola schermata base; ciclo da acquisire |
| 7 | DISPLAY URL | OFF | OFF | sola schermata base; ciclo da acquisire |
| 8 | CABINET TYPE | DELUXE | DELUXE, TWIN | base + ciclo completo |
| 9 | LINK TYPE | STAND ALONE | STAND ALONE, MASTER (CAR 1), SLAVE (CAR 2), SLAVE (CAR 3), SLAVE (CAR 4), RELAY | base + ciclo completo |
| 10 | COUNTRY | EXPORT | EXPORT, JAPAN, USA, AUSTRALIA | ciclo completo in Country Select |

I diciannove valori della ricetta storica corrispondono alle fotografie di
DIFFICULTY, COUNTRY, CABINET TYPE, LINK TYPE e DEFAULT VIEW. I due campioni
DRIVER e BEHIND sono stati rinominati da `defautl-view` a `default-view` senza
alterarne il contenuto.

### Cyber Troopers Virtual-On Oratorio Tangram (`von2`)

- **Versione:** Japan, Revision B
- **Menu:** Game Assignments; Country Select Mode
- **Schermata base:** [apri screenshot](</Users/andrea/Documents/RetroArch/model3-game-settings-catalog/von2/screenshots/von2-game-assignments-base.png>)
- **Country Select Mode:** [apri screenshot](</Users/andrea/Documents/RetroArch/model3-game-settings-catalog/von2/screenshots/von2-country-03-australia-selected.png>)
- **Screenshot primari:** 33

| # | Game Setting | Default visibile | Valori osservati negli screenshot | Evidenza |
| ---: | --- | --- | --- | --- |
| 1 | GAME DIFFICULTY | barra 10 / 16 | barre da 1 / 16 a 16 / 16 | base + ciclo completo |
| 2 | ADVERTISE SOUND | LOUD | LOUD | sola schermata base; ciclo da acquisire |
| 3 | COMMUNICATION MODE | NO LINK | NO LINK, MASTER, SLAVE, SATELLITE | base + ciclo completo |
| 4 | SEAT LETTER & ATTRIB. | SEAT A : GOOD | SEAT A : GOOD, SEAT B : EVIL, SEAT C : GOOD, SEAT D : EVIL | base + ciclo completo |
| 5 | BILLBOARD CONFIG | NO CONNECTION | NO CONNECTION | sola schermata base; ciclo da acquisire |
| 6 | PLAY TIME (1P:GROUND) | 80 SECS | 80 SECS | sola schermata base; ciclo da acquisire |
| 7 | PLAY TIME (1P:SPACE) | 80 SECS | 80 SECS | sola schermata base; ciclo da acquisire |
| 8 | PLAY TIME (VERSUS) | 80 SECS | 80 SECS | sola schermata base; ciclo da acquisire |
| 9 | MATCH COUNT (1P:GROUND) | 1 | 1 | sola schermata base; ciclo da acquisire |
| 10 | MATCH COUNT (1P:SPACE) | 1 | 1 | sola schermata base; ciclo da acquisire |
| 11 | MATCH COUNT (VERSUS) | 2 | 2 | sola schermata base; ciclo da acquisire |
| 12 | INSTANT REPLAY | ON | ON | sola schermata base; ciclo da acquisire |
| 13 | RANKING MODE | ON | ON | sola schermata base; ciclo da acquisire |
| 14 | CONTINUE | ON | ON | sola schermata base; ciclo da acquisire |
| 15 | VERSUS FINISH | OFF | OFF | sola schermata base; ciclo da acquisire |
| 16 | CHAIN VERSUS | OFF | OFF | sola schermata base; ciclo da acquisire |
| 17 | DISPLAY TYPE | C.R.T | C.R.T, PROJECTOR | base + ciclo completo |
| 18 | FORCEDLY GO VERSUS | OFF | OFF | sola schermata base; ciclo da acquisire |
| 19 | SURVIVAL MODE | OFF | OFF | sola schermata base; ciclo da acquisire |
| 20 | COUNTRY | JAPAN | JAPAN, USA, EXPORT, AUSTRALIA | ciclo completo in Country Select Mode |

I trenta valori della ricetta storica corrispondono alle fotografie di GAME
DIFFICULTY, COUNTRY, COMMUNICATION MODE, SEAT LETTER & ATTRIB. e DISPLAY TYPE.
Country Select Mode mostra inoltre `CLOCK (YEAR)`, `CLOCK (MONTH)`, `CLOCK
(DAY)` e `CLOCK (AM/PM)`: sono controlli dell'orologio corrente, non default di
gioco, e restano separati dall'audit NVRAM Settings.

### Spikeout (`spikeout`)

- **Versione:** Export, Revision C
- **Menu:** Game Assignments; Country Setting
- **Schermata completa:** [apri screenshot](</Users/andrea/Documents/RetroArch/model3-game-settings-catalog/spikeout/screenshots/spikeout-link-00-single-selected.png>)
- **Country Setting:** [apri screenshot](</Users/andrea/Documents/RetroArch/model3-game-settings-catalog/spikeout/screenshots/spikeout-country-03-usa-selected.png>)
- **Screenshot primari:** 15

| # | Game Setting | Default visibile | Valori osservati negli screenshot | Evidenza |
| ---: | --- | --- | --- | --- |
| 1 | COUNTRY | EXPORT | EXPORT, AUSTRALIA, JAPAN, U.S.A. | ciclo completo nella schermata Country Setting |
| 2 | GAME DIFFICULTY | NORMAL | NORMAL, HARD, HARDEST, EASIEST, EASY | ciclo completo; NORMAL visibile nella fotografia COMM ID = SINGLE |
| 3 | ADVERTISE SOUND | ON | ON | visibile nelle fotografie Game Assignments; ciclo da acquisire |
| 4 | COMM ID | SINGLE | SINGLE, MASTER, SLAVE | ciclo completo |

I dodici valori della ricetta storica trovano corrispondenza nelle fotografie;
il totale di quindici comprende anche le tre schermate base Game, Country e
Network Assignments. La cattura dedicata `difficulty-00-normal` è stata
ripetuta con l'attesa iniziale corretta ed è inclusa tra le evidenze primarie.
`INITIALIZE` è un comando del menu e non viene catalogato come impostazione.

### Sega Bass Fishing (`bassdx`)

- **Versione:** USA, Deluxe
- **Menu:** Game Assignments; Country Select Mode nascosto
- **Schermata base:** [apri screenshot](</Users/andrea/Documents/RetroArch/model3-game-settings-catalog/bassdx/screenshots/bassdx-game-assignments-base.png>)
- **Country Select Mode:** [apri screenshot](</Users/andrea/Documents/RetroArch/model3-game-settings-catalog/bassdx/screenshots/bassdx-country-assignments-base.png>)
- **Screenshot primari:** 11

| # | Game Setting | Default visibile | Valori osservati negli screenshot | Evidenza |
| ---: | --- | --- | --- | --- |
| 1 | GAME DIFFICULTY | NORMAL | NORMAL, MEDIUM HARD, VERY HARD, VERY EASY, MEDIUM EASY | base + ciclo completo |
| 2 | GAME MODE | NORMAL | NORMAL | sola schermata base; ciclo da acquisire |
| 3 | GAME TIME | 1M 30S | 1M 30S | sola schermata base; ciclo da acquisire |
| 4 | CONTINUE TIME | 1M 20S | 1M 20S | sola schermata base; ciclo da acquisire |
| 5 | ADVERTISE SOUND | ON | ON | sola schermata base; ciclo da acquisire |
| 6 | TOURNAMENT MODE | OFF | OFF | sola schermata base; ciclo da acquisire |
| 7 | COUNTRY | USA | USA, EXPORT, AUSTRALIA, JAPAN | base + ciclo completo nella schermata nascosta Country Select Mode |

I nove valori della ricetta storica trovano corrispondenza nelle fotografie e i
campioni `.srm` esistenti non sono stati rigenerati. La ricetta richiede
un'attesa iniziale di 12 secondi perché `bassdx` accetta gli input Test/Service
più tardi degli altri parent; combinazioni, conteggi e polarità L3 = Test / R3 =
Service restano invariati. `EXIT` è un comando del menu e non viene catalogato
come impostazione.

### Virtua Striker 2 '99.1 (`vs2v991`)

- **Versione:** Export, USA, Revision B
- **Menu:** Game Assignments
- **Schermata base:** [apri screenshot](</Users/andrea/Documents/RetroArch/model3-game-settings-catalog/vs2v991/screenshots/vs2v991-game-assignments-base.png>)
- **Screenshot primari:** 8

| # | Game Setting | Default visibile | Valori osservati negli screenshot | Evidenza |
| ---: | --- | --- | --- | --- |
| 1 | COUNTRY | EXPORT | EXPORT, U.S.A | base + ciclo completo |
| 2 | ADVERTISE SOUND | ON | ON | sola schermata base; ciclo da acquisire |
| 3 | DIFFICULTY | NORMAL | NORMAL, HARD, HARDEST, EASY | base + ciclo completo |
| 4 | VIRTUAL TIME | REAL | REAL | sola schermata base; ciclo da acquisire |
| 5 | BILLBOARD | ON | ON | sola schermata base; ciclo da acquisire |
| 6 | ONE MATCH MODE | OFF | OFF | sola schermata base; ciclo da acquisire |
| 7 | 1P TIME SET | 2'00\" | 2'00\" | sola schermata base; ciclo da acquisire |
| 8 | 1P G GOAL SYSTEM | OFF | OFF | sola schermata base; ciclo da acquisire |
| 9 | 1P PK SYSTEM | OFF | OFF | sola schermata base; ciclo da acquisire |
| 10 | VS TIME SET | 2'00\" | 2'00\" | sola schermata base; ciclo da acquisire |
| 11 | VS G GOAL SYSTEM | OFF | OFF | sola schermata base; ciclo da acquisire |
| 12 | VS PK SYSTEM | OFF | OFF | sola schermata base; ciclo da acquisire |

I sei campioni della ricetta storica hanno confermato integralmente i cicli
DIFFICULTY e COUNTRY.

## Cloni

Le acquisizioni strutturali partono da una Save RAM vuota con le modifiche
NVRAM del core disattivate. La ricetta del parent viene usata soltanto per
raggiungere il Test Menu e la pagina Game Assignments. La matrice seguente è la
trascrizione delle schermate dei cloni; `stesse righe` significa che la pagina
completa è stata acquisita direttamente e confrontata, non che sia stata
dedotta dal parent.

Una seconda passata ha riutilizzato le sole macro Country e Network già
validate nei parent. Sedici catture documentano pagine distinte e valide;
venticinque ripetevano Game Assignments e sono state riclassificate come
ridondanti, mentre tre schermate non pertinenti sono state separate in
`non-settings`. Questo controllo ha confermato, fra gli altri casi, il Country
nascosto di `srally2dx` e l'assenza delle righe di rete in `scuddx` e
`scuddxo`.

| Clone | Parent | Differenze nelle righe visibili | Differenze nei default visibili | Stato |
| --- | --- | --- | --- | --- |
| `getbassdx` | `bassdx` | stesse righe | GAME TIME 2M 00S; COUNTRY JAPAN | acquisito |
| `getbassur` | `bassdx` | stesse righe | COUNTRY JAPAN | acquisito |
| `getbass` | `bassdx` | assenti GAME TIME, CONTINUE TIME, TOURNAMENT MODE | GAME DIFFICULTY MEDIUM HARD; COUNTRY JAPAN | acquisito |
| `dayto2pe` | `daytona2` | stesse righe; CABINET TYPE espone TWIN/SPECIAL (parent TWIN/DELUXE) | VOCAL MITSUYOSHI | acquisito |
| `dirtdvlsu` | `dirtdvls` | stesse righe | COUNTRY USA; SPEED METER MPH | acquisito |
| `dirtdvlsau` | `dirtdvls` | stesse righe | COUNTRY AUSTRALIA | acquisito |
| `dirtdvlsj` | `dirtdvls` | stesse righe | COUNTRY JAPAN | acquisito |
| `dirtdvlsg` | `dirtdvls` | stesse righe | nessuna | acquisito |
| `ecap` | `eca` | assenti DIFFICULTY e STEERING REACTION; aggiunte 1ST/2ND/3RD/4TH STAGE TIME RATE | MILE/METER MILE; SIREN VOLUME 8 | acquisito |
| `ecau` | `eca` | stesse righe | MILE/METER MILE | acquisito |
| `ecaj` | `eca` | stesse righe | nessuna | acquisito |
| `fvipers2o` | `fvipers2` | stesse righe | nessuna | acquisito |
| `harleya` | `harley` | stesse righe | nessuna | acquisito |
| `lostwsgp` | `lostwsga` | assente BOSS ACTION | GAME DIFFICULTY barra 4 / 16; ADVERTISE SOUND OFF | acquisito |
| `oceanhuna` | `oceanhun` | stesse righe | nessuna | acquisito |
| `scudau` | `scud` | Game Assignments assente dal Test Menu | non applicabile | acquisito; nessun Game Setting |
| `scuddx` | `scud` | assenti LINK ID, CAR NUMBER, CABINET TYPE e MULTI DISPLAY | nessuna sulle righe comuni | acquisito |
| `scuddxo` | `scud` | assenti LINK ID, CAR NUMBER, CABINET TYPE e MULTI DISPLAY | nessuna sulle righe comuni | acquisito |
| `scudplus` | `scud` | stesse righe | nessuna | acquisito |
| `scudplusa` | `scud` | stesse righe | nessuna | acquisito |
| `srally2p` | `srally2` | non determinabile | non determinabile | bloccato: loop illegale prima del Test Menu |
| `srally2pa` | `srally2` | non determinabile | non determinabile | bloccato: uscita video nera prima del Test Menu |
| `srally2dx` | `srally2` | assenti DISPLAY URL, CABINET TYPE e LINK TYPE | nessuna sulle righe comuni | acquisito |
| `swtrilgya` | `swtrilgy` | stesse righe | nessuna | acquisito |
| `swtrilgyp` | `swtrilgy` | assente FEEDBACK LEVER | COUNTRY JAPAN | acquisito |
| `vf3a` | `vf3` | stesse righe; COUNTRY espone JAPAN/USA/EXPORT (ASIA assente) | nessuna | acquisito |
| `vf3c` | `vf3` | stesse righe | nessuna | acquisito |
| `vf3tb` | `vf3` | assenti REPLAY CANCEL e COMMAND DISP; aggiunti SOUND BALANCE, DEFAULT MODE ed ENERGY RECOVERY | STAGE SELECT CHALLENGER | acquisito |
| `von254g` | `von2` | stesse righe | nessuna | acquisito |
| `von2a` | `von2` | stesse righe | nessuna | acquisito |
| `von2o` | `von2` | stesse righe | nessuna | acquisito |
| `vs215` | `vs2` | stesse righe | nessuna | acquisito |
| `vs215o` | `vs2` | stesse righe | COUNTRY JAPAN; overlay diagnostico presente | acquisito |
| `vs29815` | `vs298` | stesse righe | nessuna | acquisito |
| `vs299a` | `vs2v991` | stesse righe | nessuna | acquisito |
| `vs299` | `vs2v991` | stesse righe | nessuna | acquisito |
| `vs299j` | `vs2v991` | stesse righe | COUNTRY JAPAN | acquisito |
| `vs29915` | `vs2v991` | stesse righe | nessuna | acquisito |
| `vs29915a` | `vs2v991` | stesse righe | nessuna | acquisito |
| `vs29915j` | `vs2v991` | stesse righe | COUNTRY JAPAN | acquisito |

Le prove non valide di `srally2p` e `srally2pa` sono conservate separatamente
in `~/Documents/RetroArch/model3-clone-service-menu-failures` e non sono contate
come evidenza primaria. Per `scudau` è primaria la schermata del Test Menu, che
non contiene Game Assignments; la schermata raggiunta applicando la navigazione
del parent è archiviata come test diagnostico non pertinente.

### Get Bass: Sega Bass Fishing (`getbassdx`)

- **Parent:** `bassdx`
- **Versione:** Japan, Deluxe
- **Menu:** Game Assignments; Country Select Mode
- **Test Menu:** [apri screenshot](</Users/andrea/Documents/RetroArch/model3-game-settings-catalog/getbassdx/screenshots/getbassdx-menu-structure-test-menu.png>)
- **Game Assignments:** [apri screenshot](</Users/andrea/Documents/RetroArch/model3-game-settings-catalog/getbassdx/screenshots/getbassdx-menu-structure-game-assignments.png>)
- **Country Select Mode:** [apri screenshot](</Users/andrea/Documents/RetroArch/model3-game-settings-catalog/getbassdx/screenshots/getbassdx-country-assignments-base.png>)
- **Screenshot primari:** 3

| # | Game Setting | Default visibile nel clone | Confronto col parent | Evidenza |
| ---: | --- | --- | --- | --- |
| 1 | GAME DIFFICULTY | NORMAL | uguale | schermata base clone |
| 2 | GAME MODE | NORMAL | uguale | schermata base clone |
| 3 | GAME TIME | 2M 00S | parent: 1M 30S | schermata base clone |
| 4 | CONTINUE TIME | 1M 20S | uguale | schermata base clone |
| 5 | ADVERTISE SOUND | ON | uguale | schermata base clone |
| 6 | TOURNAMENT MODE | OFF | uguale | schermata base clone |
| 7 | COUNTRY | JAPAN | parent: USA | schermata base clone |

La struttura e i default sono una trascrizione diretta del clone. Nel workbook
i valori selezionabili sono derivati dalla ricetta fotografica di `bassdx` e
marcati come tali; non vengono presentati come cicli acquisiti direttamente sul
clone. I default divergenti restano invece quelli osservati in `getbassdx`.

Il workbook `revisione_core_options_model3.xlsx` applica lo stesso criterio a
tutti i cloni nella scheda `Cloni` e registra stato ed evidenze nella scheda
`Copertura cloni`, mantenendo separati i valori direttamente osservati da
quelli attribuiti al parent.

## Esclusioni

`mgtrkbad` (Magical Truck Adventure) è un bad dump e resta fuori dalla campagna.
Non viene contato come set mancante e non richiede acquisizione sostitutiva.
