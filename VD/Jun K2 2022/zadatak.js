$(function() {
    'use strict';
    // Matrica polja
    const cells = Array(4)
        // Napunimo niz dužine 4
        .fill()
        // i za svako polje tog niza 
        .map(
            (_, i) => $('tr')
                .eq(i)
                // dovučemo <td>ove u tom redu
                .children()
                // pretvorimo ih u niz
                .toArray()
                // a zatim članove tog niza pretvorimo u objekte
                .map(el => ({
                    // koji sadrže jQuery element,
                    $element: $(el),
                    // podatak da li je polje bomba
                    isBomb: false,
                    // kao i podatak da li je polje otkriveno
                    uncovered: false
                }))
        );
    // Broj polja ostao za otkrivanje
    let fieldsLeft = 0;
    // DOM elementi
    const $startButton = $('#start');
    const $n = $('#n');
    const $message = $('p');
    const $table = $('table');
    /**
     * Generiše indekse polja na tabli sa bombama, za dat broj polja
     * koji se generiše i ukupan broj polja.
     *
     * Generisani indeks se posle koristi kako bi se podelio na red i kolonu
     * polja sa bombom.
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
     * Za svaku ćeliju poziva funkciju kojoj prosleđuje red, kolonu i podatke
     * iz te ćelije.
     * @param {(cell, row, col) => void} callback Funkcija koja se poziva za
     *                                            svaku ćeliju
     */
    function forEachCell(callback) {
        cells.forEach(
            (row, rowIndex) => row.forEach((cell, colIndex) =>
                callback(cell, rowIndex, colIndex)
        ));
    }
    /**
     * Nalazi broj bombi oko ćelije na zadatoj poziciji.
     * @param {number} row Red ćelije
     * @param {number} col Kolona ćelije
     * @returns {number} Broj bombi oko ćelije
     */
    function countBombs(row, col) {
        let count = 0;
        if (row > 0) {
            count += cells[row-1][col].isBomb;
        }
        if (row < 3) {
            count += cells[row+1][col].isBomb;
        }
        if (col > 0) {
            count += cells[row][col-1].isBomb;
        }
        if (col < 3) {
            count += cells[row][col+1].isBomb;
        }
        if (row > 0 && col > 0) {
            count += cells[row-1][col-1].isBomb;
        }
        if (row > 0 && col < 3) {
            count += cells[row-1][col+1].isBomb;
        }
        if (row < 3 && col > 0) {
            count += cells[row+1][col-1].isBomb;
        }
        if (row < 3 && col < 3) {
            count += cells[row+1][col+1].isBomb;
        }
        return count;
    }
    /**
     * Dovodi igru u završno stanje.
     */
    function endGame() {
        $message.removeClass('hidden');
        $table.removeClass('playing');
        $startButton.removeAttr('disabled');
    }
    /**
     * Rukovalac pritiska na dugme za početak.
     * @param {ClickEvent} event Podaci događaja o pritisku na dugme
     */
    $startButton.click(event => {
        event.preventDefault();
        $startButton.attr('disabled', '');
        $table.addClass('playing');
        $message.addClass('hidden');
        forEachCell(cell => {
            cell.isBomb = false;
            cell.uncovered = false;
            cell.$element.text('').removeClass('bomb');
        });
        const n = Number($n.val());
        fieldsLeft = 16 - n;
        const selectedFields = selectFields(n, $('td').length);
        selectedFields.forEach(index => {
            cells[index % 4][Math.floor(index / 4)].isBomb = true;
        });
        console.info(cells.map(row => row
            .map(cell => cell.isBomb ? 'X' : '-')
            .join(' ')
        ).join('\n'));
    });
    /**
     * Rukovođenje klikom na ćeliju.
     */
    forEachCell((cell, row, col) => {
        cell.$element.click(() => {
            if (cell.uncovered) {
                return;
            }
            cell.uncovered = true;
            const {$element, isBomb} = cell;
            if (isBomb) {
                // Polje je bomba, otkrivamo sve bombe
                forEachCell(({$element, isBomb}) => {
                    if (isBomb) {
                        $element.text('💣💣').addClass('bomb');
                    }
                });
                endGame();
            } else {
                $element.text(countBombs(row, col));
                if (--fieldsLeft === 0) {
                    endGame();
                }
            }
        });
    });
});
