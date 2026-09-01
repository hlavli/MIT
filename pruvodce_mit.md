# Průvodce předmětem Mikroprocesorová technika: Domácí příprava a projekty

Předmět Mikroprocesorová technika (3. ročník, obor Elektrotechnika) má časovou dotaci **3 hodiny týdně** (2 hodiny teoretického výkladu v klasické třídě a 2 hodiny praktických cvičení v laboratoři jednou za 14 dní). Abychom efektivně využili omezený čas v laboratořích, zavádíme koncept **obrácené třídy (Flipped Classroom)** s využitím cenově dostupného domácího kitu.

---

## 1. Koncepce výuky: Uno (doma) ──► Mega (škola)

*   **Domácí příprava (Arduino UNO):** Doma zapojíte obvod na nepájivém poli a v prostředí **Microchip Studio** napíšete a odladíte program v **čistém jazyce C** (přímá manipulace s registry a bitové operace).
*   **Práce v laboratoři (Školní deska ATmega2560):** Předvedete funkční domácí zapojení a získáte „vstupenku“ ke školnímu přípravku. Vaším úkolem bude kód adaptovat (přemapovat piny a registry) pro mikrokontrolér ATmega2560 podle školních schémat.
*   **Proč to děláme?** Rozdílné čipy vás donutí číst elektrotechnická schémata a datasheet, namísto slepého opisování kódu.

---

## 2. Nákupní lístek: Domácí výukový kit

Povinnou pomůckou pro každého žáka (nebo střídavou dvojici) je tato startovací sada:
*   **Název:** [Malá sada s precizním klonem UNO R3](https://dratek.cz/arduino-platforma/51554-mala-sada-s-preciznim-klonem-uno-r3.html)
*   **E-shop:** [dratek.cz](https://dratek.cz/)
*   **Cena:** cca 636 Kč (při sdílení ve dvojici **318 Kč na žáka**), (při koupi 2 a více kusů doprava zdarma)

### Proč vyžadujeme právě tuto sadu?
1.  **Opravitelnost (DIP28 patice):** Procesor ATmega328P lze z desky vyjmout. Pokud neopatrností zničíte pin, čip vyměníme za nový (cca 80 Kč). U levných SMD klonů se musí vyhodit celá deska.
2.  **Spolehlivost připojení (ATmega16U2):** Levné klony používají USB převodník CH340, se kterým jsou kritické problémy pod Windows 11 (nahrávání často končí chybami). Tato sada obsahuje čip ATmega16U2, který Windows 11 detekují okamžitě a bez ovladačů.
3.  **Vazba na ŠVP:** Obsahuje posuvný registr 74HC595, multiplexované 7segmentové displeje, LED matici, teplotní čidlo LM35DZ a bzučáky – to vše jsou témata našeho ŠVP.

---

## 3. Pravidla sdílení (1 kit do dvojice ob týden)

Abychom snížili finanční zátěž, využijeme střídavou výuku skupin A a B:
*   **Utvoření dvojic:** Vytvoříte dvojici napříč skupinami (žák ze skupiny A + žák ze skupiny B). Na sadu se složíte rovným dílem (318 Kč na osobu).
*   **Pravidlo předávání:** K předání kitu parťákovi musí dojít **každý pátek během společné teoretické hodiny**.
*   **Odpovědnost:** Součástí krabičky je evidenční arch. Při předání oba podepíší, že je sada kompletní. Za neohlášené poškození odpovídá ten, kdo měl kit doma.
*   **Záloha:** V případě nemoci nebo zapomenutí zapůjčí škola na cvičení jednu ze svých 3 záložních sad.

---

## 4. Průběh cvičení: „Vstupenka na přípravek“

Laboratorní cvičení má přísný, ale efektivní průběh:
1.  **Předvedení (prvních 10 minut):** Zapojíte svůj domácí kit a ukážete funkční domácí úkol (např. blikání LED řízené časovačem Timer 1).
2.  **Ústní obhajoba (Vstupenka):** Vyučující se vás zeptá na princip fungování (např. *„Který registr nastavuje děličku časovače?“* nebo *„Jak funguje toto bitové maskování?“*). Pokud nebudete vědět, kód je považován za opsaný.
3.  **Školní přípravek:** Po obhajobě dostanete [školní desku](01_Uvod.md) a kód přemapujete na školní periferie.
4.  **Nepřipravenost:** Pokud domácí úkol neodevzdáte, nesmíte pracovat se školní deskou. Celé cvičení strávíte zapojováním základu na Unu a vaše **nepřipravenost bude penalizována**.

---

## 5. Pololetní projekt: Výběr vývojové cesty a pravidla

V průběhu pololetí zpracujete samostatný (nebo ve sdílené dvojici) praktický projekt. Hodnotí se technické řešení, čistota kódu v C, dokumentace a úroveň prezentace.
Abychom vyřešili logistiku domácí přípravy a motivovali vás k samostatné práci, platí pro projekt tato pravidla:

### A) Volba formátu práce (Jednotlivec vs. Dvojice)
Můžete pracovat samostatně, nebo ve dvojici utvořené napříč skupinami A/B (parťák, se kterým sdílíte domácí kit). Podmínky se však liší:

*   **Samostatná práce (Doporučeno):**
    *   **Jednodušší zadání:** Stačí splnit základní minimum z kombinační matice stavebních kamenů.
    *   **Snazší obhajoba:** Obhajujete pouze svůj vlastní kód, kterému plně rozumíte.
    *   **Plná kontrola:** Vaše hodnocení nezávisí na (ne)zodpovědnosti druhého spolužáka.
    *   **Hardware pro sebe:** Domácí kit máte v týdnu před svým cvičením plně k dispozici.
*   **Práce ve dvojici:**
    *   **Složitější zadání:** Projekt musí mít vyšší komplexnost (např. složitější stavový automat, souběh více časovačů či pokročilejší logiku).
    *   **Kolektivní odpovědnost při obhajobě:** U zkoušení se mohu zeptat kteréhokoliv z dvojice na jakoukoliv část společného kódu. Pokud jeden z vás kód neobhájí, hodnocení jde dolů oběma.

---

### B) Volba realizační cesty (Jak projekt postavit?)
Aby zapojení pololetního projektu doma nekolidovalo s týdenními domácími úkoly (které musíte na nepájivém poli průběžně stavět a rozebírat pro cvičení), zvolíte si jednu ze dvou vývojářských cest:

*   **Cesta „Bastlíř“ (Fyzická stavba doma):**
    *   Projekt máte fyzicky zapojený na svém nepájivém poli doma.
    *   **Podmínka:** K sadě si dobrovolně dokoupíte jedno malé nepájivé pole (cca 40–50 Kč). Na velkém poli máte trvale sestavený projekt, na malém poli stavíte průběžné domácí úkoly. Desku Arduino UNO pouze přepojujete několika vodiči.
*   **Cesta „Kodér“ (Vývoj na školním HW):**
    *   Doma nepájivé pole po každém úkolu bez problému rozeberete.
    *   **Podmínka:** Svůj pololetní projekt vyvíjete doma čistě softwarově v Microchip Studiu. Fyzicky ho zapojujete, ladíte a odevzdáváte **výhradně v laboratoři na školním integrovaném přípravku**, který má všechny periferie (LED, tlačítka, bzučák, displeje) již pevně zapájené.

---
### C) Stavební kameny projektu (Minimální požadavky konfigurace)
Své téma si sestavíte jako skládačku z těchto prvků a necháte si ho **schválit vyučujícím do konce 6. týdne**:
1.  **Software:** Minimálně **1× hardwarový časovač (Timer)** (generování tónů, odměřování času) + **1× vnější přerušení (Interrupt)**.
2.  **Hardware:** Minimálně **2 odlišné periferie** ze sady (bzučák, fotorezistor, tlačítka, displeje, otřesové čidlo).
3.  **Unikátnost:** Každý projekt (nebo dvojice) musí mít jedinečnou kombinaci zapojení a logiky.

---

### D) Umělá inteligence (AI) jako partner
V souladu s ŠVP je **povoleno využívat AI (ChatGPT atd.) jako konzultanta a generátor nápadů**.
*   **Co je povoleno:** Nechat si od AI navrhnout originální koncepty na základě vaší kombinace součástek (*„Vymysli mi zajímavou hru s tlačítkem na přerušení a pasivním bzučákem...“*).
*   **Co je zakázáno:** Slepé kopírování vygenerovaného kódu. Při obhajobě musíte do detailu vysvětlit každý řádek kódu, konfiguraci registrů i zapojení. **Pokud kód neobhájíte, projekt nebude uznán**.
