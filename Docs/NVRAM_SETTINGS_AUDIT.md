# Audit di coerenza dei NVRAM Settings

Data: 2026-09-25

> Questo documento verifica l'implementazione Libretro. Il contenuto
> autorevole del Service Menu è in `GAME_SETTINGS_CATALOG.md`.

## Stato e perimetro

L'audit fotografico globale è ancora in corso, mentre la campagna binaria dei
cloni release è completa. Dopo la correzione del routing clone, l'inventario
del core espone NVRAM Settings per 56 dei 62 set acquisibili presenti in
`Config/Games.xml`: 22 parent e 34 cloni. I sei set acquisibili non esposti sono
`ecap`, `lostwsgp`, `scudau`, `srally2p`, `srally2pa` e `swtrilgyp`.
`mgtrkbad` è escluso come bad dump sia dal catalogo visuale sia dall'audit.
I prototipi e i location test non sono esclusi in quanto tali: `ecap`,
`lostwsgp` e `swtrilgyp`, già acquisiti, restano nel catalogo, mentre
`srally2p` e `srally2pa` sono fallimenti di acquisizione ancora aperti.
Questa regola riguarda esclusivamente il catalogo visuale. Prototipi, location
test e altre versioni pre-release sono esclusi per policy da `NVRAM Settings`,
da `Automatic Initial NVRAM Setup` e dalla campagna binaria supplementare.

| Controllo | Stato corrente |
| --- | ---: |
| Parent con inventario fotografico trascritto | 22 / 22 |
| Fotografie primarie parent indicizzate | 419 |
| Cloni acquisiti o classificati direttamente | 38 / 40 |
| Fotografie primarie clone indicizzate | 91 |
| Set nel perimetro NVRAM Settings | 56 / 62 |
| Parent con ricetta confrontata con i valori fotografati | 22 / 22 |
| Parent con ricetta storica di campionamento | 22 / 22 |
| Campioni definiti dalle ricette correnti | 355 |
| Campioni definiti e presenti nell'archivio | 355 / 355 |
| Cloni release con campagna binaria completa | 34 / 34 |
| Valori clone acquisiti e validati | 461 / 461 |

I due campioni Sega Rally 2 con il refuso `defautl-view` sono stati rinominati
in `default-view` senza modificarne il contenuto. Sei ulteriori `.srm` sono
prove manuali (`calibration`, `calibration-p1`, `calibration-p2` e `jit-test`)
e non fanno parte delle ricette correnti. Tutti i 355 valori delle ricette
corrispondono alle fotografie; le quattro correzioni apportate alle ricette
modificano soltanto l'attesa iniziale e non la sequenza o il significato del
campione. Gli `.srm` esistenti sono quindi considerati validi e non vengono
rigenerati.

Gli EEPROM degli SRM usati per i template storici sono inoltre identici byte
per byte alle baseline correnti in 33 confronti con l'archivio NVRAM e in 38
confronti con i `menu-structure.srm` delle nuove acquisizioni clone. Questi
ultimi restano baseline strutturali distinte. La campagna supplementare ha poi
generato da ciascuna baseline clone i campioni separati per ogni valore esposto.
Gli stessi dati alimentano `NVRAM Settings` e `Automatic Initial NVRAM Setup`.

Il confronto clone/parent delle baseline native produce invece differenze per
tutti i 38 cloni acquisiti, sia considerando la sola EEPROM sia, dove
applicabile, la Backup RAM. Ogni clone deve quindi conservare il proprio
campione iniziale: l'identità con una precedente acquisizione dello stesso set
dimostra la riproducibilità della baseline, non la compatibilità binaria con il
parent.

La campagna supplementare è completa per 461 valori e 34 cloni release. Il
conteggio iniziale di 462 è sceso di uno perché l'acquisizione diretta di
`vf3a` ha dimostrato che Country espone Japan, USA ed Export ma non Asia. Tutti
i 461 campioni sono stati associati univocamente al valore atteso, hanno
struttura e integrità valide e superano la simulazione di persistenza. Sono
esclusi dal conteggio i controlli operativi di calibrazione, `scudau`, che non
contiene Game Assignments, e tutte le versioni prototype/location-test/
pre-release per la policy concordata.

La campagna ha inoltre corretto `dayto2pe`: le sottovoci di Game Mode richiedono
percorsi Service Menu più lunghi rispetto al parent; Cabinet Type espone
`Twin` e `Special`, non `Twin` e `Deluxe`, e viene memorizzato in due copie in
Backup RAM. L'override clone-specifico è condiviso dai due percorsi applicativi,
quindi la correzione vale sia per i NVRAM Settings sia per l'inizializzazione
automatica delle nuove Save RAM.

## Metodo di confronto

Le ricette parent esistenti e i 355 campioni presenti sono il riferimento di
partenza già collaudato. Per ogni parent si confrontano i valori dichiarati nei
suffissi della ricetta con le etichette acquisite nelle fotografie del Service
Menu, mantenendo le combinazioni già codificate per raggiungere Country e le
altre schermate nascoste. La modalità fotografica riproduce soltanto i primi
passaggi della sequenza, cattura il valore selezionato e scarta la Save RAM;
non rigenera i campioni `.srm`. La campagna non rigenera sistematicamente i
campioni.

Il controllo visivo complessivo ha individuato quattro catture dedicate rimaste
nel Test Menu o nella sequenza di avvio. Sono state ripetute singolarmente e
ora mostrano la riga attesa: barra 9 / 16 per `dirtdvls`, NORMAL per `fvipers2`,
barra 8 / 16 per `magtruck` e NORMAL per `spikeout`. Tutte e quattro sono
incluse nelle fotografie primarie.

Un nuovo campione è ammesso soltanto quando una voce già esposta dal core non ha
una corrispondenza nella ricetta o nell'archivio, quando il file esistente non è
verificabile, oppure quando foto, ricetta e campione non concordano. Le voci
fotografate ma non esposte restano nel catalogo e non ampliano il campionamento
iniziale.

### Corrispondenza ricette / fotografie verificata

| Parent | Gruppi coperti dalla ricetta | Valori ricetta confrontati | Esito fotografico |
| --- | --- | ---: | --- |
| `lostwsga` | Difficulty, Country | 20 / 20 | corrispondenti |
| `daytona2` | Difficulty, Country, Cabinet Type, Link ID, Car Number, Vocal | 33 / 33 | corrispondenti |
| `eca` | Difficulty | 5 / 5 | corrispondenti |
| `vf3` | Difficulty, Country | 8 / 8 | corrispondenti |
| `vs2` | Difficulty, Country | 6 / 6 | corrispondenti |
| `vs2v991` | Difficulty, Country | 6 / 6 | corrispondenti |
| `fvipers2` | Difficulty, Country | 9 / 9 | corrispondenti |
| `vs298` | Difficulty, Country | 8 / 8 | corrispondenti; confermata la schermata nascosta Change Country |
| `oceanhun` | Difficulty, Country, Cabinet Type | 11 / 11 | corrispondenti |
| `skichamp` | Country, Communication, Privilege Mode, Cabinet ID Number | 12 / 12 | corrispondenti; le tre etichette `link-*` descrivono la configurazione combinata |
| `lamachin` | Difficulty, Country, Cabinet Type | 14 / 14 | corrispondenti; DELUXE rende visibile il gap BASS SHAKER |
| `swtrilgy` | Difficulty, Country, Cabinet Type, Feedback Lever | 14 / 14 | corrispondenti; Feedback Lever è disponibile soltanto per il cabinet DX |
| `spikeofe` | Difficulty, Country, Comm ID | 12 / 12 | corrispondenti; confermata la schermata nascosta Country Setting |
| `dirtdvls` | Difficulty, Country, Communication Mode, Machine ID | 28 / 28 | corrispondenti |
| `harley` | Difficulty, Country, Cabinet Type, Communication, Privilege Mode, Cabinet ID Number | 21 / 21 | corrispondenti; confermate le righe di rete condizionali |
| `magtruck` | Difficulty, Country, Christmas Mode | 21 / 21 | corrispondenti |
| `scud` | Difficulty, Country, Cabinet Type, Link ID, Car Number | 20 / 20 | corrispondenti |
| `lemans24` | Difficulty, Country, Cabinet Type, Communication Mode, Cabinet Number, Special Car | 37 / 37 | corrispondenti; SATELLITE è un valore di Cabinet Number |
| `srally2` | Difficulty, Country, Cabinet Type, Link Type, Default View | 19 / 19 | corrispondenti; confermati DRIVER e BEHIND |
| `von2` | Difficulty, Country, Communication Mode, Seat Letter & Attribute, Display Type | 30 / 30 | corrispondenti; i campi CLOCK restano fuori dall'audit NVRAM Settings |
| `spikeout` | Difficulty, Country, Comm ID | 12 / 12 | corrispondenti |
| `bassdx` | Difficulty, Country | 9 / 9 | corrispondenti; acquisizione resa stabile portando l'attesa iniziale a 12 secondi |

Il confronto copre 355 valori su 355 definiti dalle ventidue ricette esaminate.
Questo risultato conferma etichette e cardinalità rispetto al Service Menu e,
secondo il criterio concordato per campioni generati da ricette già validate,
conferma la correttezza semantica dei 355 `.srm` esistenti. Nessuna ricetta ha
richiesto una correzione capace di invalidarne il contenuto.

## Esito strutturale dei cloni

L'acquisizione diretta ha classificato 38 cloni su 40. Trentasette condividono
integralmente o parzialmente la struttura del parent; `scudau` non espone Game
Assignments. `srally2p` e `srally2pa` non raggiungono il Test Menu con il core
corrente e restano senza dati attribuiti.

La verifica secondaria delle macro Country e Network ha prodotto sedici pagine
distinte valide. Venticinque catture che ripetevano Game Assignments sono state
riclassificate come ridondanti e tre schermate non pertinenti sono state
separate dalle evidenze primarie. Il catalogo contiene ora 510 screenshot
primari: 419 parent e 91 cloni.

Il confronto fra le pagine fotografate e `LibretroNvramSettings.h` ha rilevato
quattro errori di esposizione:

| Set | Opzioni erroneamente esposte | Correzione |
| --- | --- | --- |
| `scudau` | tutte le opzioni della famiglia Scud | nessun NVRAM Setting, coerentemente con l'assenza di Game Assignments |
| `scuddx` | Linked Cabinets, Link ID, Car Number, Cabinet Type | conservati soltanto Country e Difficulty |
| `scuddxo` | Linked Cabinets, Link ID, Car Number, Cabinet Type | conservati soltanto Country e Difficulty |
| `srally2dx` | Linked Cabinets, Cabinet Type | conservati Country, Difficulty e Default View |

I default relativi alle righe assenti sono stati rimossi anche dalle tabelle per
set, impedendo che vengano applicati indirettamente. Gli altri default esposti
rimangono invariati in attesa della verifica ciclica e binaria.

### Correzione dell'acquisizione `bassdx`

La prima esecuzione iniziava a inviare Test/Service dopo 5 secondi, mentre
`bassdx` era ancora nella sequenza di avvio. Le catture progressive hanno
mostrato lo schermo bianco e la schermata FBI durante gli impulsi che avrebbero
dovuto navigare il Test Menu. Portando a 12 secondi la sola attesa iniziale, la
ricetta invariata raggiunge Game Assignments e Country Select Mode e fotografa
tutti i nove valori attesi. La polarità resta L3 = Test e R3 = Service; i nove
`.srm` esistenti non sono stati rigenerati.

## The Lost World (`lostwsga`)

Il Service Menu contiene cinque Game Settings. Il core ne espone due come
selezioni ordinarie e aggiunge un controllo operativo per applicare dati di
calibrazione convalidati.

| Ordine Service Menu | Game Setting | Copertura del core | Esito iniziale |
| ---: | --- | --- | --- |
| 1 | GAME DIFFICULTY | `Difficulty`, 16 valori | valori e default coerenti; etichetta descrittiva del core |
| 2 | ADVERTISE SOUND | assente | gap di implementazione |
| 3 | LIFE | assente | gap di implementazione |
| 4 | COUNTRY | `Country`, 4 valori | valori, ordine ciclico e default coerenti |
| 5 | BOSS ACTION | assente | gap di implementazione |

Il default nativo fotografato è Japan per Country e Level 8 per Difficulty. La
tabella `SupportedGame` conserva Level 8 e applica il Country Export come
override di frontend. Le codifiche dichiarate dal core sono `0..3` per Japan,
USA, Export e Australia e `0x00..0xf0`, a passi di `0x10`, per i sedici livelli
di difficoltà.

L'ordine relativo delle due opzioni implementate non segue il menu: il core
registra `Country` prima di `Difficulty`, mentre il Service Menu mostra
`GAME DIFFICULTY` prima di `COUNTRY`. La correzione verrà applicata solo dopo
aver completato il confronto con gli altri titoli, così da evitare una modifica
locale che renda incoerente la regola generale.

`Provide Calibration Data` non corrisponde a una riga Game Setting: è un
controllo operativo che applica dati di calibrazione già convalidati. Viene
quindi auditato nella parte di persistenza NVRAM, senza presentarlo come voce
del catalogo del gioco.

## Default e override

Per `lostwsga` il default nativo acquisito è Japan, mentre il frontend usa
Export come override regionale concordato. La regola generale è Export quando
disponibile e USA come fallback. Lo stesso valore alimenta sia il default dei
`NVRAM Settings` sia `Automatic Initial NVRAM Setup`; quest'ultimo opera solo
su una nuova Save RAM e non modifica salvataggi esistenti. Difficulty Level 8
resta il default nativo. Nessuna delle tre voci mancanti è ancora candidata a
un Core Option: la campagna ne registra prima semantica, valori e codifica.

## Prossimi controlli

1. documentare nel catalogo visuale il blocco pre-Service Menu di `srally2p` e
   `srally2pa`, mantenendoli fuori dalla gestione NVRAM come tutti i prototipi;
2. generare nuovi campioni parent soltanto per futuri gap o discrepanze
   dimostrate;
3. completare i cicli fotografici delle impostazioni catalogate ma non coperte
   dalle ricette correnti.
