# Kontrola kontrolního hlášení

**Hodnocení:** 5.0 bodů (žádný možný bonus)  
**Termín odevzdání:** 24.04.2023 11:59:59

## Zadání

Úkolem je realizovat třídy, které implementují správu daně z přidané hodnoty (DPH).

Předpokládáme, že firmy si předávají faktury. Firma, která vydá fakturu, musí z fakturované částky odvést státu DPH. Firma, která fakturu přijme (a zaplatí), může nárokovat vratku DPH. Systém musí tento proces usnadnit a omezit daňové podvody.

Vydané a přijaté faktury eviduje třída `CVATRegister`. Firmy musí registrovat vydávané i přijímané faktury. Registr páruje faktury a umožňuje najít nespárované faktury. Registr faktur umožňuje:

- **Přidání** a **odstranění** faktur
- **Vyhledávání nespárovaných faktur** podle určitých kritérií.

Rozhraní třídy je následující:

### Metody třídy `CVATRegister`

- **`CVATRegister()`**: Implicitní konstruktor, inicializuje prázdnou instanci registru.
- **`registerCompany(name)`**: Zaregistruje firmu v registru. Název firmy nerozlišuje malá/velká písmena a ignoruje nadbytečné mezery.
  - Návratová hodnota: `true`/`false` pro úspěch/neúspěch.
- **`addIssued(invoice)`**: Přidá fakturu vydanou firmou. Návratová hodnota: `true`/`false` pro úspěch/neúspěch.
- **`addAccepted(invoice)`**: Přidá přijatou fakturu firmou. Návratová hodnota: `true`/`false` pro úspěch/neúspěch.
- **`delIssued(invoice)`**: Odebere dříve zaregistrovanou vydanou fakturu.
- **`delAccepted(invoice)`**: Odebere dříve zaregistrovanou přijatou fakturu.
- **`unmatched(company, sortOpt)`**: Vrací seznam nespárovaných faktur pro zadanou firmu, seřazený podle kritérií v `sortOpt`.

### Třída `CInvoice`

- **Konstruktor**:  
  `CInvoice(date, seller, buyer, amount, vat)`  
  Inicializuje fakturu datem, prodávajícím, kupujícím, částkou a DPH.

- **Metody**:  
  `date`, `seller`, `buyer`, `amount`, `vat` - Přístupové metody ke čtení hodnot faktury.

### Třída `CSortOpt`

- **Konstruktor**:  
  Implicitní konstruktor inicializuje prázdnou instanci třídy.

- **`addKey(sortBy, ascending)`**: Přidá řadicí kritérium `sortBy`. Pokud `ascending` je `true`, řadí se vzestupně, pokud `false`, tak sestupně.

  - Možnosti řazení:
    - `BY_DATE` - podle data faktury
    - `BY_SELLER` - podle prodávající firmy
    - `BY_BUYER` - podle kupující firmy
    - `BY_AMOUNT` - podle částky
    - `BY_VAT` - podle DPH

### Třída `CDate`

- Implementuje jednoduché datum. Její implementace je dostupná v testovacím prostředí.

### Odevzdání

Odevzdávejte zdrojový kód s implementací tříd `CVATRegister`, `CInvoice` a `CSortOpt`. Důležité je použít efektivní datové struktury pro správu firem a faktur. Očekává se, že operace jako přidávání a mazání budou rychlejší než lineární, a řazení bude `n log n`.

- Je povoleno používat kontejnery z STL, včetně `unordered_set` a `unordered_map`.
- Hashovací funkce/funktor deklarujte explicitně při vytváření instancí `unordered_set`/`unordered_map`.

Správné řešení této úlohy, které splní závazné testy na 100%, může být odevzdáno k code review. (Pro code review není nutné zvládnout bonusové testy.)

---

*(Poznámka: Doporučujeme také exportovat tento projekt jako PDF, pokud byste se nudili.)*
