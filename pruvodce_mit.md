# Průvodce předmětem Mikroprocesorová technika: Domácí příprava a projekty

Předmět Mikroprocesorová technika (3. ročník, obor Elektrotechnika) má časovou dotaci **3 hodiny týdně** (2 hodiny teoretického výkladu v klasické třídě a 2 hodiny praktických cvičení v laboratoři jednou za 14 dní) [4, 5]. Abychom efektivně využili omezený čas v laboratořích, zavádíme koncept **obrácené třídy (Flipped Classroom)** s využitím cenově dostupného domácího kitu.

---

## 1. Koncepce výuky: Uno (doma) ──► Mega (škola)

*   **Domácí příprava (Arduino UNO):** Doma zapojíte obvod na nepájivém poli a v prostředí **Microchip Studio** napíšete a odladíte program v **čistém jazyce C** (přímá manipulace s registry a bitové operace) [4].
*   **Práce v laboratoři (Školní deska ATmega2560):** Předvedete funkční domácí zapojení a získáte „vstupenku“ ke školnímu přípravku. Vaším úkolem bude kód adaptovat (přemapovat piny a registry) pro mikrokontrolér ATmega2560 podle školních schémat.
*   **Proč to děláme?** Rozdílné čipy vás donutí číst elektrotechnická schémata a datasheet, namísto slepého opisování kódu.

---

## 2. Nákupní lístek: Domácí výukový kit

Povinnou pomůckou pro každého žáka (nebo střídavou dvojici) je tato startovací sada:
*   **Název:** Malá sada s precizním klonem UNO R3
*   **E-shop:** dratek.cz
*   **Cena:** cca 636 Kč (při sdílení ve dvojici **318 Kč na žáka**)

### Proč vyžadujeme právě tuto sadu?
1.  **Opravitelnost (DIP28 patice):** Procesor ATmega328P lze z desky vyjmout. Pokud neopatrností zničíte pin, čip vyměníme za nový (cca 80 Kč). U levných SMD klonů se musí vyhodit celá deska.
2.  **Spolehlivost připojení (ATmega16U2):** Levné klony používají USB převodník CH340, se kterým jsou kritické problémy pod Windows 11 (nahrávání často končí chybami). Tato sada obsahuje čip ATmega16U2, který Windows 11 detekují okamžitě a bez ovladačů.
3.  **Vazba na ŠVP:** Obsahuje posuvný registr 74HC595, multiplexované 7segmentové displeje, LED matici, teplotní čidlo LM35DZ a bzučáky – to vše jsou témata našeho ŠVP [2, 24].

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
1.  **Předvedení (prvních 10 minut):** Zapojíte svůj domácí kit a ukážete funkční domácí úkol (např. blikání LED řízené časovačem Timer 1) [22].
2.  **Ústní obhajoba (Vstupenka):** Vyučující se vás zeptá na princip fungování (např. *„Který registr nastavuje děličku časovače?“* nebo *„Jak funguje toto bitové maskování?“*) [1, 22]. Pokud nebudete vědět, kód je považován za opsaný.
3.  **Školní přípravek:** Po obhajobě dostanete školní desku a kód přemapujete na školní periferie.
4.  **Nepřipravenost:** Pokud domácí úkol neodevzdáte, nesmíte pracovat se školní deskou. Celé cvičení strávíte zapojováním základu na Unu v rohu laboratoře, což znamená nedostatečnou známku z cvičení za nepřipravenost.

---

## 5. Pololetní projekt: Kombinační matice

V průběhu pololetí zpracujete samostatný (nebo ve sdílené dvojici) praktický projekt [18]. Hodnotí se technické řešení, čistota kódu v C, dokumentace a úroveň prezentace [18].

Nechceme omezovat vaši kreativitu zadáváním konkrétních témat, proto si svůj projekt sestavíte sami jako skládačku z těchto **stavebních kamenů**:

### Povinné stavební kameny projektu:
Pro úspěšné schválení musí váš projekt v čistém C využívat:
1.  **Software:** Minimálně **1× hardwarový časovač (Timer)** (např. CTC režim, generování tónu či časování) [22] + **1× vnější přerušení (Interrupt)** [23].
2.  **Hardware:** Minimálně **2 odlišné periferie** ze sady (např. bzučák + fotorezistor, nebo tlačítka + multiplexovaný displej).
3.  **Unikátnost:** Projekt každého studenta/dvojice musí mít jedinečnou kombinaci zapojení a logiky. Kombinaci si necháte schválit vyučujícím do konce 6. týdne.

### Umělá inteligence (AI) jako partner:
V souladu s rozvojem digitálních kompetencí ŠVP je **povoleno využívat AI (ChatGPT atd.) jako konzultanta a generátor nápadů** [15].
*   *Co je povoleno:* Nechat si od AI vygenerovat tipy na zajímavé projekty pro danou kombinaci součástek (např. *„Navrhni nápad na projekt s tlačítkem na přerušení, bzučákem a fotorezistorem“*).
*   *Co je zakázáno:* Slepě zkopírovat kód. Při ústní obhajobě projektu musíte do detailu vysvětlit každý řádek kódu, konfiguraci registrů i fyzické zapojení. Pokud kód neobhájíte, projekt nebude uznán.
