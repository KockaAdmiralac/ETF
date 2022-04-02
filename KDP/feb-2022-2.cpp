#include "common.h"

const int NumOfAccounts = 100;
const int NumOfUsers = 100;

struct Account {
    int balance;
    int maxTicket = 0;
    int waitUntilAbove = 0;
    sem mutex = 1;
    sem balanceSem = 0;
    sem users[NumOfUsers] = {1, 0, 0, ...};
};

Account accounts[NumOfAccounts];

void deposit(int amount, int accountId) {
    Account& account = accounts[accountId];
    account.mutex.wait();
    // Уплаћујемо паре на рачун.
    account.balance += amount;
    // Уколико је неки други корисник захтевао исплату, проверавамо да ли може бити задовољена.
    if (account.waitUntilAbove != 0 && account.balance >= account.waitUntilAbove) {
        // Уколико јесте, на нама је да ажурирамо стање.
        account.balance -= account.waitUntilAbove;
        account.waitUntilAbove = 0;
        account.balanceSem.signal();
    }
    account.mutex.signal();
}

void withdraw(int amount, int accountId) {
    Account& account = accounts[accountId];
    // Дохватамо наше место у реду чекања за исплату.
    account.mutex.wait();
    // Рачуна се на то да неће један корисник истовремено радити две исплате са истог налога.
    int ticket = (account.maxTicket++) % NumOfUsers;
    account.mutex.signal();

    // Чекамо да нас претходни корисник у реду чекања прозове.
    account.users[ticket].wait();

    // Чекамо да се ослободи довољно средстава пре исплате.
    account.mutex.wait();
    if (account.balance >= amount) {
        // Уколико већ има довољно средстава, ажурирамо стање.
        account.balance -= amount;
        account.mutex.signal();
    } else {
        // Уколико нема, остављамо следећем кориснику који уплаћује да ажурира стање и обавести нас.
        account.waitUntilAbove = amount;
        account.mutex.signal();
        account.balanceSem.wait();
    }

    // Јави следећем кориснику да може да изврши исплату.
    account.users[(ticket + 1) % NumOfUsers].signal();
}
