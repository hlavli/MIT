# Test na jazyk C

Teorii najdete [zde](00_Jazyk_C.md)


1. Vytvořte celočíselnou proměnnou s názvem „counter“
   - Zapište do ní číslo 152
   - Poté proměnnou zvyšte o 20. 
   - Výslednou hodnotu zapište do registru PORTF.
  
2. Napište příkaz s podmínkou:
   - Pokud je hodnota v registru PINK větší než 5, zapíše se hodnota registru PINK do registru PORTF. 
   - Pokud je hodnota menší nebo rovna 5, zapíše se do registru PORTF hodnota 0.

3. Pomocí for cyklu zapište postupně všechny hodnoty z pole “segmenty” do registru PORTB. Mezi jednotlivými zápisy udělejte pauzu 100ms pomocí funkce _delay_ms(). 

   ```int segmenty[5] = { 0x88, 0x83, 0xc6, 0xA1, 0x86};```

4. Nadefinujte funkci “druha_mocnina”. 
   - Funkce bude mít jeden vstupní argument (celé číslo)
   - Funkce bude vracet bude jeho druhou mocninu.
