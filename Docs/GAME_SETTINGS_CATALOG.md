# Catalogo autorevole dei Game Settings SEGA Model 3

Stato: campagna in corso.

Questo documento trascrive i Service Menu acquisiti direttamente con il core
Libretro. Gli screenshot sono la fonte autorevole per presenza, ordine, default
visibile e valori selezionabili. `Config/Games.xml` viene usato soltanto per
identità del set, titolo e relazione parent/clone. Le tabelle di implementazione
e le precedenti ricette NVRAM non vengono usate per dedurre dati mancanti.

## Revisione e copertura

- sorgente core: `c4684561f4911842b478a84e4262a1f15d2922ab`;
- SHA-256 del core acquisito: `a347ed61a53475bbfc721f864dd5d8570330b1e8c6b8d994fa905ca886f7585d`;
- SHA-256 di `Config/Games.xml`:
  `275832cdb077c22883192f5aaeb8f76547f4dce786370f10b2d54c46a8ed3c5e`;
- inventario: 63 set, composto da 22 parent e 41 cloni;
- ROM disponibili: 62 / 63; manca `mgtrkbad`;
- parent acquisiti: 1 / 22;
- cloni acquisiti: 0 / 41;
- screenshot primari indicizzati: 34.

Una prima scansione ha inoltre prodotto 48 screenshot base preliminari per gli
altri 21 parent. La cattura tecnica è riuscita in 48 sessioni su 48, ma la
validazione visuale ha già rilevato due navigazioni Game Assignments da
correggere (`bassdx` e `spikeout`) e alcune sequenze Country/Network che si sono
fermate nella pagina precedente. Queste immagini non vengono conteggiate come
evidenza primaria finché menu e contenuto non sono stati confermati.

I file PNG, i log e i profili temporanei restano fuori dal repository in
`~/Documents/RetroArch/model3-game-settings-catalog`. Ogni ciclo parte dalla
baseline immutabile del set, con `Automatic Initial NVRAM Setup` e `NVRAM
Settings` disabilitati. La SRAM prodotta incidentalmente da RetroArch viene
scartata nelle acquisizioni destinate al solo catalogo.

## Regole di lettura

- **Valori osservati** contiene solo valori fotografati durante il ciclo.
- Una riga visibile ma non modificabile è indicata esplicitamente.
- Un clone non eredita dati dal parent finché la sua acquisizione diretta non
  dimostra menu, default e valori equivalenti.
- Le etichette descrittive del core non sostituiscono la rappresentazione del
  Service Menu. Per esempio, The Lost World mostra la difficoltà come barra a
  sedici posizioni, senza la dicitura `Level N`.

## Parent

### The Lost World (`lostwsga`)

- **Versione:** Japan, Revision A
- **Menu:** Game Assignments; Country Select Mode
- **Schermata base:** [apri screenshot](</Users/andrea/Documents/RetroArch/model3-game-settings-catalog/lostwsga/screenshots/lostwsga-difficulty-00.png>)
- **Country Select Mode:** [apri screenshot](</Users/andrea/Documents/RetroArch/model3-game-settings-catalog/lostwsga/screenshots/lostwsga-country-assignments-00.png>)
- **Screenshot primari:** 34

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
Country Select Mode.

## Cloni

Nessun clone è ancora catalogato. `lostwsgp` deve essere acquisito direttamente
prima di poter confrontare il location test con `lostwsga`.

## Blocchi correnti

La sola ROM assente dall'inventario locale è `mgtrkbad` (Magical Truck
Adventure, bad dump). La copertura 63 / 63 non può essere dichiarata finché non
è disponibile una sorgente eseguibile per quel set oppure il set non viene
formalmente riclassificato fuori dal catalogo richiesto.
