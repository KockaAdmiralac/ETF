$(function() {
    'use strict';
    // Niz tačnih polja u trenutnoj partiji
    let correctFields = null;
    // Identifikator intervala koji u 'preview' stanju boji ćelije
    let interval = 0;
    // DOM elementi
    const $startButton = $('#start');
    const $n = $('#n');
    const $message = $('p');
    const $table = $('table');
    const $cells = $('td');
    /**
     * Generiše indekse polja na tabli sa tačnim izborima, za dat broj polja
     * koji se generiše i ukupan broj polja.
     * @param {number} n Broj polja koji se generiše
     * @param {number} max Broj za jedan većeg od najvećeg broja koji se može
     *                     generisati
     * @returns {number[]} Niz brojeva koji predstavlja indekse polja na tabli
     *                     koji su tačni izbori
     */
    function selectFields(n, max) {
        const selected = new Set();
        while (selected.size < n) {
            selected.add(Math.floor(Math.random() * max));
        }
        return [...selected];
    }
    /**
     * Dohvata indeks zadate ćelije. Ćelije su numerisane brojevima počev od 0
     * i indeks ćelije se čuva u njenom identifikatoru.
     * @param {Node} cell DOM ćelija ili jQuery objekat ćelije čiji se indeks
     *                    dohvata
     * @returns Indeks zadate ćelije
     */
    function getCellIndex(cell) {
        return Number($(cell).attr('id').substring(6));
    }
    /**
     * Vraća indekse ćelija koje nisu izabrane.
     * @returns {number[]} Niz indeksa svih ćelija koje nisu izabrane
     */
    function getUnselectedFields() {
        const selectedFields = $('.selected')
            .map((_, cell) => getCellIndex(cell))
            .toArray();
        return correctFields.filter(field => !selectedFields.includes(field));
    }
    /**
     * Označava ćeliju sa zadatim indeksom kao izabranu.
     * @param {number} number Indeks ćelije za biranje
     */
    function selectField(number) {
        $('#field-' + number).addClass('selected');
    }
    /**
     * Uklanja oznaku da su izabrane sa svih ćelija.
     */
    function deselectAll() {
        $('.selected').removeClass('selected').removeClass('previous');
    }
    /**
     * Postavlja trenutno stanje igre kao klasu table za igru.
     * 
     * Moguća stanja su:
     * - preview: Kada tačne ćelije postaju plave jedna po jedna
     * - playing: Kada korisnik može da bira ćelije i one postaju zelene
     * - error: Kada korisnik izabere pogrešnu ćeliju i ona postane crvena
     * - finished: Kada korisnik završi igru
     * @param {string} state Trenutno stanje igre
     */
    function setGameState(state) {
        $table.attr('class', state);
    }
    /**
     * Poziva se svake sekunde dok je igra u 'preview' stanju i boji jedno
     * polje u plavo ukoliko nije već obojeno, ili prelazi u 'playing' stanje
     * ako su sva već obojena.
     */
    function previewField() {
        const fieldsToPreview = getUnselectedFields();
        if (fieldsToPreview.length === 0) {
            deselectAll();
            setGameState('playing');
            clearInterval(interval);
        } else {
            $('.selected').addClass('previous');
            selectField(fieldsToPreview[0]);
        }
    }
    /**
     * Vraća igru u 'playing' stanje nakon što je korisnik pogrešio.
     */
    function restoreStart() {
        setGameState('playing');
        deselectAll();
    }
    /**
     * Rukovalac pritiska na dugme za početak.
     * @param {ClickEvent} event Podaci događaja o pritisku na dugme
     */
    $startButton.click(event => {
        event.preventDefault();
        deselectAll();
        $startButton.attr('disabled', '');
        $message.addClass('hidden');
        setGameState('preview');
        correctFields = selectFields($n.val(), $cells.length);
        interval = setInterval(previewField, 1000);
    });
    /**
     * Rukovalac pritiska na ćeliju na tabli.
     * @param {ClickEvent} event Podaci događaja o pritisku na ćeliju
     */
    $cells.click(event => {
        const $cell = $(event.currentTarget);
        $cell.addClass('selected');
        if (correctFields.includes(getCellIndex($cell))) {
            if (getUnselectedFields().length === 0) {
                $message.removeClass('hidden');
                $startButton.removeAttr('disabled');
                setGameState('finished');
            }
        } else {
            setGameState('error');
            setTimeout(restoreStart, 1000);
        }
    });
});
