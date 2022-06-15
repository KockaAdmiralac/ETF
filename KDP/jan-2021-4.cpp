#include "common.h"

const int N = 10;
const int M = 100;

void setCurrentFromSidetrack() {
    int sidetrackTicket;
    int sidetrackHead;
    in("sidetrackHead", &sidetrackHead);
    in("sidetrack", sidetrackHead, &sidetrackTicket);
    out("sidetrackHead", sidetrackHead + 1);
    out("current", sidetrackTicket);
}

void train(bool isInternational) {
    int ticket;
    in("ticket", &ticket);
    out("ticket", ticket + 1);
    in("current", ticket);
    bool arrivedLater = ticket >= M;
    bool isSidetrack = !isInternational && !arrivedLater;
    if (isSidetrack) {
        // Прво идемо у слепи колосек
        int sidetrackTail;
        in("sidetrackTail", &sidetrackTail);
        out("sidetrack", sidetrackTail, ticket);
        out("sidetrackTail", sidetrackTail + 1);
        if (ticket == M - 1) {
            // Ми смо последњи воз који је стигао током квара,
            // треба да предамо првом из слепог колосека
            setCurrentFromSidetrack();
            in("current", ticket);
        } else {
            // Предајемо следећем возу који је стигао током квара
            out("current", ticket + 1);
            in("current", ticket);
        }
    }
    int station;
    in("station", &station);
    // Идемо на станицу, па чим ослободимо улаз пуштамо следећег
    if (isSidetrack) {
        if (rdp("sidetrack")) {
            // Пуштамо следећег из слепог колосека
            setCurrentFromSidetrack();
        } else {
            // Нема више никог из слепог колосека, пуштамо обичну колону
            out("current", M);
        }
    } else {
        if (ticket == M - 1) {
            // Ми смо последњи воз који је стигао током квара,
            // треба да предамо возовима из слепог колосека, уколико постоје
            if (rdp("sidetrack")) {
                setCurrentFromSidetrack();
            } else {
                // Нико није ушао у слепи колосек
                out("current", ticket + 1);
            }
        } else {
            // Пуштамо следећи воз, пошто још увек колона која је стигла
            // током квара није изашла из улаза
            out("current", ticket + 1);
        }
    }
    // Одлазимо са станице
    out("station", station);
}

void initialize() {
    out("ticket", 0);
    for (int i = 0; i < M; ++i) {
        eval(train, rand() % 2 == 1);
        // Чекамо да воз покупи свој ticket
        rd("ticket", i + 1);
    }
    for (int i = 0; i < N; ++i) {
        out("station", i);
    }
    out("current", 0);
    out("sidetrackHead", 0);
    out("sidetrackTail", 0);
}
