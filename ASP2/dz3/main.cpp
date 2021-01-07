#include <algorithm>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include "dictionary.hpp"
// #define DEBUG
// #define REPORT_REJECTED

void clear() {
    #ifndef DEBUG
    std::cout << "\033[2J\033[f";
    #endif
}

char lowercase(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c - ('Z' - 'z');
    }
    return c;
}

// https://stackoverflow.com/a/313990
void toLowercase(std::string &str) {
    std::transform(str.begin(), str.end(), str.begin(), lowercase);
}

void createDictionaryFromFiles(Dictionary &dict) {
    std::string directory;
    std::cout << "Unesite putanju do direktorijuma sa datotekama za čitanje: ";
    std::cin.ignore();
    std::getline(std::cin, directory);
    #ifdef REPORT_REJECTED
    std::map<std::string, int> rejected;
    int sumRejected = 0;
    #endif
    std::clock_t clk = clock();
    for (auto &entry : std::filesystem::directory_iterator(directory)) {
        std::string word;
        std::ifstream file(entry.path());
        while (!file.eof()) {
            file >> word;
            bool valid = true;
            for (std::size_t i = 0; i < word.length(); ++i) {
                char c = word[i];
                if (c >= 'A' && c <= 'Z') {
                    word[i] = c - 'A' + 'a';
                } else if (c == '.' && i == word.length() - 1) {
                    word = word.substr(0, word.length() - 1);
                    break;
                } else if (!(c >= 'a' && c <= 'z')) {
                    valid = false;
                    break;
                }
            }
            if (valid) {
                dict.insert(word);
            } else {
                #ifdef REPORT_REJECTED
                ++sumRejected;
                if (rejected.find(word) == rejected.end()) {
                    rejected.insert({word, 1});
                } else {
                    ++rejected[word];
                }
                #endif
            }
        }
    }
    clk = clock() - clk;
    #ifdef REPORT_REJECTED
    std::ofstream rejectedFile("rejected.txt");
    for (const auto &pair : rejected) {
        rejectedFile << pair.first << ": " << pair.second << "\n";
    }
    rejectedFile.close();
    #endif
    std::cout
    #ifdef REPORT_REJECTED
              << "Broj odbačenih reči: " << sumRejected << std::endl
              << "Broj jedinstvenih odbačenih reči: " << rejected.size() << std::endl
    #else
              << "Za izveštaj odbačenih reči kompajlirati "
              << "sa REPORT_REJECTED zastavicom." << std::endl
    #endif
              << "Vreme izvršavanja: " << ((float)clk)/CLOCKS_PER_SEC << "s" << std::endl
              << "Broj reči: " << dict.countKeys() << std::endl;
}

void searchForWord(Dictionary &dict) {
    std::string word;
    std::cout << "Reč za pretragu: ";
    std::cin >> word;
    toLowercase(word);
    int frequency = dict.find(word);
    if (frequency == 0) {
        std::cout << "Reč se ne pojavljuje u rečniku." << std::endl;
    } else {
        std::cout << "Reč se pojavljuje " << frequency
                  << " puta." << std::endl;
    }
}

void insertWord(Dictionary &dict) {
    std::string word;
    std::cout << "Reč za umetanje: ";
    std::cin >> word;
    toLowercase(word);
    dict.insert(word);
}

void predictWord(Dictionary &dict) {
    std::string word;
    std::cout << "Reč za predviđanje: ";
    std::cin >> word;
    toLowercase(word);
    auto predicted = dict.predict(word);
    if (predicted.size() == 0) {
        std::cout << "Nije pronađena nijedna reč za predviđanje." << std::endl;
    } else {
        for (std::size_t i = 0; i < predicted.size(); ++i) {
            std::cout << "  " << i + 1 << ". " << predicted[i].first << ": "
                      << predicted[i].second << std::endl;
        }
    }
}

int main(void) {
    Dictionary dict;
    int option = 1;
    void (*options[])(Dictionary &) = {
        createDictionaryFromFiles,
        searchForWord,
        insertWord,
        predictWord
    };
    clear();
    while (option) {
        std::cout
        <<  "╔══════════════════════════════════════════════════════════╗\n"
        <<  "║ Treći domaći iz Algoritama i struktura podataka 2        ║\n"
        <<  "║ Student Luka Simić, broj indeksa 368, godina upisa 2019. ║\n"
        <<  "╟──────────────────────────────────────────────────────────╢\n"
        <<  "║ Izaberite opciju za svoju narednu operaciju.             ║\n"
        <<  "║ 1. Stvaranje rečnika na osnovu datoteka.                 ║\n"
        <<  "║ 2. Pretraživanje reči.                                   ║\n"
        <<  "║ 3. Umetanje reči.                                        ║\n"
        <<  "║ 4. Predviđanje reči.                                     ║\n"
        <<  "║ 0. Izlaz iz programa.                                    ║\n"
        <<  "╚══════════════════════════════════════════════════════════╝"
        << std::endl;
        std::cin >> option;
        clear();
        if (option > 0 && option < 5) {
            try {
                options[option-1](dict);
            } catch (std::exception &exc) {
                std::cout << "Desila se greška: " << exc.what() << std::endl;
            }
        } else if (option != 0) {
            std::cout << "Nije izabrana validna opcija." << std::endl;
        }
    }
    return EXIT_SUCCESS;
}
