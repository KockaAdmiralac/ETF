CREATE TABLE `korisnik` (
    `id` INT PRIMARY KEY AUTO_INCREMENT,
    `korisnicko_ime` VARCHAR(45),
    `sifra` VARCHAR(45)
);
CREATE TABLE `admin` (
    `korisnik_id` INT PRIMARY KEY,
    FOREIGN KEY (`korisnik_id`) REFERENCES `korisnik` (`id`)
        ON DELETE CASCADE
        ON UPDATE NO ACTION
);
CREATE TABLE `student` (
    `korisnik_id` INT PRIMARY KEY,
    `indeks` VARCHAR(45),
    `ime_prezime` VARCHAR(45) NOT NULL,
    `godina` INT,
    FOREIGN KEY (`korisnik_id`) REFERENCES `korisnik` (`id`)
        ON DELETE CASCADE
        ON UPDATE NO ACTION
);
CREATE TABLE `nastavnik` (
    `korisnik_id` INT PRIMARY KEY,
    `ime_prezime` VARCHAR(45),
    FOREIGN KEY (`korisnik_id`) REFERENCES `korisnik` (`id`)
        ON DELETE CASCADE
        ON UPDATE NO ACTION
);
CREATE TABLE `semestar` (
    `id` INT PRIMARY KEY AUTO_INCREMENT,
    `naziv` VARCHAR(45) NOT NULL,
    `status` VARCHAR(1)
);
CREATE TABLE `predmet` (
    `id` INT PRIMARY KEY AUTO_INCREMENT,
    `sifra` VARCHAR(45) NOT NULL,
    `naziv` VARCHAR(45) NOT NULL,
    `semestar_id` INT NOT NULL,
    `godina` INT,
    FOREIGN KEY (`semestar_id`) REFERENCES `semestar` (`id`)
        ON DELETE CASCADE
        ON UPDATE NO ACTION
);
CREATE TABLE `predaje` (
    `nastavnik_korisnik_id` INT,
    `predmet_id` INT,
    PRIMARY KEY (`nastavnik_korisnik_id`, `predmet_id`),
    FOREIGN KEY (`nastavnik_korisnik_id`) REFERENCES `nastavnik` (`korisnik_id`)
        ON DELETE CASCADE
        ON UPDATE NO ACTION,
    FOREIGN KEY (`predmet_id`) REFERENCES `predmet` (`id`)
        ON DELETE CASCADE
        ON UPDATE NO ACTION
);
CREATE TABLE `prati` (
    `id` INT PRIMARY KEY AUTO_INCREMENT,
    `predmet_id` INT NOT NULL,
    `student_korisnik_id` INT NOT NULL,
    FOREIGN KEY (`predmet_id`) REFERENCES `predmet` (`id`)
        ON DELETE CASCADE
        ON UPDATE NO ACTION,
    FOREIGN KEY (`student_korisnik_id`) REFERENCES `student` (`korisnik_id`)
        ON DELETE CASCADE
        ON UPDATE NO ACTION
);
CREATE TABLE `rok` (
    `id` INT PRIMARY KEY AUTO_INCREMENT,
    `naziv` VARCHAR(45) NOT NULL,
    `semestar_id` INT NOT NULL,
    `status` VARCHAR(1),
    FOREIGN KEY (`semestar_id`) REFERENCES `semestar` (`id`)
        ON DELETE CASCADE
        ON UPDATE NO ACTION
);
CREATE TABLE `prijava` (
    `id` INT PRIMARY KEY AUTO_INCREMENT,
    `prati_id` INT NOT NULL,
    `rok_id` INT NOT NULL,
    FOREIGN KEY (`prati_id`) REFERENCES `prati` (`id`)
        ON DELETE CASCADE
        ON UPDATE NO ACTION,
    FOREIGN KEY (`rok_id`) REFERENCES `rok` (`id`)
        ON DELETE CASCADE
        ON UPDATE NO ACTION
);
CREATE TABLE `ocena` (
    `id` INT PRIMARY KEY AUTO_INCREMENT,
    `ocena` INT,
    `prijava_id` INT NOT NULL,
    FOREIGN KEY (`prijava_id`) REFERENCES `prijava` (`id`)
        ON DELETE CASCADE
        ON UPDATE NO ACTION
);

INSERT INTO `korisnik` (`korisnicko_ime`, `sifra`) VALUES
('admin', 'admin'),         -- 1
('pera', 'peric'),          -- 2
('mika', 'mikic'),          -- 3
('zika', 'zikic'),          -- 4
('cmilos', 'cmilos'),       -- 5
('tasha', 'tasha'),         -- 6
('stubic', 'stubic'),       -- 7
('tartalja', 'tartalja');   -- 8

INSERT INTO `admin` (`korisnik_id`) VALUES (1);

INSERT INTO `student` (`korisnik_id`, `indeks`, `ime_prezime`, `godina`) VALUES
(2, '0001', 'Pera Perić', 2019),
(3, '0002', 'Mika Mikić', 2020),
(4, '0010', 'Žika Žikić', 2018);

INSERT INTO `nastavnik` (`korisnik_id`, `ime_prezime`) VALUES
(1, 'Admin Adminić'),
(5, 'Miloš Cvetanović'),
(6, 'Tamara Šekularac'),
(7, 'Stefan Tubić'),
(8, 'Igor Tartalja');

INSERT INTO `semestar` (`naziv`, `status`) VALUES
('Peti semestar 2019', 'N'),    -- 1
('Peti semestar 2021', 'T'),    -- 2
('Treći semestar 2021', 'T'),   -- 3
('Drugi semestar 2022', 'P'),   -- 4
('Četvrti semestar 2022', 'P'); -- 5

INSERT INTO `predmet` (`sifra`, `naziv`, `semestar_id`, `godina`) VALUES
('13S113IS1', 'Informacioni sistemi 1', 2, 2021),                   -- 1
('13E114IS1', 'Informacioni sistemi 1', 2, 2021),                   -- 2
('13S112OO1', 'Objektno orijentisano programiranje 1', 3, 2021),    -- 3
('13E112OO1', 'Objektno orijentisano programiranje 1', 3, 2021),    -- 4
('13S112OO2', 'Objektno orijentisano programiranje 2', 5, 2022),    -- 5
('13E112OO2', 'Objektno orijentisano programiranje 2', 5, 2022);    -- 6

INSERT INTO `predaje` (`nastavnik_korisnik_id`, `predmet_id`) VALUES
(8, 3),
(8, 4),
(8, 5),
(8, 6),
(5, 1),
(5, 2),
(6, 1),
(6, 2),
(7, 1),
(7, 2);

INSERT INTO `prati` (`predmet_id`, `student_korisnik_id`) VALUES
(1, 2), -- 1: Pera prati IS1
(2, 3), -- 2: Mika prati IS1
(3, 3), -- 3: Mika prati OO1
(3, 4); -- 4: Žika prati OO1

INSERT INTO `rok` (`naziv`, `semestar_id`, `status`) VALUES
('Januar', 1, 'N'),     -- 1
('Januar', 2, 'T'),     -- 2
('Januar', 3, 'T'),     -- 3
('Februar', 2, 'P'),    -- 4
('Februar', 3, 'P');    -- 5

INSERT INTO `prijava` (`prati_id`, `rok_id`) VALUES
(1, 2), -- 1: Pera prijavio IS1 za januar
(1, 4), -- 2: Pera prijavio IS1 za februar
(2, 2), -- 3: Mika prijavio IS1 za februar
(3, 5), -- 4: Mika prijavio OO1 za februar
(4, 3); -- 5: Žika prijavio OO1 za januar

INSERT INTO `ocena` (`ocena`, `prijava_id`) VALUES
(5, 1),
(10, 5);
