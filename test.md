### Test - jazyk C, časovač

1. Vytvořte proměnnou typu int, zapište do ní číslo 152. Poté proměnnou zvyšte o 20. Výslednou hodnotu zapiště do registru PORTF.
	
2. Napište příkaz s podmínkou. Pokud je hodnota v registru PINK větší než 5, zapíše se hodnota registru PINK do registru PORTF. Pokud je hodnota menší nebo rovna 5, zapíše se do registru PORTF hodnota 0.

3. Pomocí cyklu zapište postupně všechny hodnoty z pole "segmenty" do registru PORTB. Mezi jednotlivými zápisy udělejte pauzu 100ms pomocí funkce _delay_ms(). int segmenty[5] = { 0x88, 0x83, 0xc6, 0xA1, 0x86};

4. Nadefinujte funkci "druha_mocnina". Funkce bude mít jeden vstupní argument (celé číslo), vracet bude jeho druhou mocninu.

5. Nastavte registr TCCR1B tak, abyste použili předděličku 256 a CTC režim. Můžete použít [stránku o časovači na githubu](https://tomaschovanec.github.io/MIT/08_Timer.html)

6. Nastavte časovač Timer1 tak, aby k přetečení došlo jednou za 150ms. Použijte CTC režim. Jako řešení uveďte dva příkazy, jeden nastavení registru TCCR1B (mode, prescaler) a druhý nastavení komparačního registru OCR1A.
