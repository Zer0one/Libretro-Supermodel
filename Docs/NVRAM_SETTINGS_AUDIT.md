# Audit di coerenza dei NVRAM Settings

Data: 2026-09-25

> Questo documento verifica l'implementazione Libretro. Il contenuto
> autorevole del Service Menu è in `GAME_SETTINGS_CATALOG.md`.

## Stato e perimetro

L'audit globale è in corso. L'inventario del core espone NVRAM Settings per 57
dei 63 set presenti in `Config/Games.xml`: 22 parent e 35 cloni. I sei set non
esposti sono `ecap`, `lostwsgp`, `mgtrkbad`, `srally2p`, `srally2pa` e
`swtrilgyp`; restano comunque nel perimetro del catalogo visuale.

| Controllo | Stato corrente |
| --- | ---: |
| Set nel catalogo Service Menu | 1 / 63 |
| Set nel perimetro NVRAM Settings | 57 / 63 |
| Set confrontati con catalogo completo | 1 / 57 |
| Parent con ricetta storica di campionamento | 22 / 22 |
| Campioni definiti dalle ricette correnti | 355 |
| Campioni definiti e presenti nell'archivio | 353 / 355 |

I due campioni nominalmente mancanti di Sega Rally 2 sono presenti con il
refuso `defautl-view` anziché `default-view`. Sei ulteriori `.srm` sono prove
manuali (`calibration`, `calibration-p1`, `calibration-p2` e `jit-test`) e non
fanno parte delle ricette correnti. Questa verifica attesta soltanto
l'inventario dei file: importazione, persistenza e integrità devono essere
rieseguite con il core di sviluppo corrente prima di considerare validi i
campioni storici.

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

La tabella `SupportedGame` usa i default nativi `japan` e `level_8`, coerenti
con gli screenshot. Le codifiche dichiarate dal core sono `0..3` per Japan,
USA, Export e Australia e `0x00..0xf0`, a passi di `0x10`, per i sedici livelli
di difficoltà. La corrispondenza binaria e l'aggiornamento dell'integrità
restano da riconfermare sui campioni correnti.

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

Per `lostwsga` il default nativo acquisito è Japan. Qualunque eventuale default
USA o Export nel frontend deve essere classificato come override di regione e
verificato separatamente. Difficulty Level 8 è un default nativo e non richiede
override. Nessuna delle tre voci mancanti è ancora candidata a un Core Option:
la campagna ne registra prima semantica, valori e codifica.

## Prossimi controlli

1. completare l'acquisizione diretta dei restanti 21 parent e 41 cloni;
2. ottenere o riclassificare `mgtrkbad`;
3. rigenerare i due campioni Sega Rally 2 con i nomi corretti;
4. validare importazione, persistenza, byte modificati e integrità dei 355
   campioni definiti, limitatamente alle opzioni già esposte;
5. produrre la matrice parent/clone solo da evidenza acquisita.
