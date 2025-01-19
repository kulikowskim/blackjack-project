#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "karty.h"

void tura_gracza(int *suma_gracza, int *blackjack, int *saldo, int stawka);
void tura_bota(int *suma_bota);
void sprawdz_wynik(int suma_gracza, int suma_bota, int blackjack, int *saldo, int stawka);
int zapytaj_split(int *pierwsza_karta, int *druga_karta);
void double_down(int *suma_gracza);

int main() {
    srand(time(NULL));

    int saldo;
    printf("Witaj w blackjacku! Ile pieniędzy chcesz wpłacić? ($): ");
    scanf("%d", &saldo);

    int gra_trwa = 1;
    while (gra_trwa) {
        int suma_gracza = 0, suma_bota = 0;
        int blackjack = 0;

        if (saldo <= 0) {
            printf("Nie masz wystarczająco pieniędzy, aby kontynuować grę. Gra zakończona.\n");
            break;
        }

        printf("Masz aktualnie $%d. Ile chcesz postawić? ($): ", saldo);
        int stawka;
        scanf("%d", &stawka);

        while (stawka > saldo || stawka <= 0) {
            printf("Nieprawidłowa stawka. Podaj kwotę mniejszą lub równą Twojemu saldu i większą od 0: ");
            scanf("%d", &stawka);
        }

        printf("Twoje karty:\n");
        tura_gracza(&suma_gracza, &blackjack, &saldo, stawka);

        if (!blackjack && suma_gracza <= 21) {
            printf("Tura bota:\n");
            tura_bota(&suma_bota);
        }

        sprawdz_wynik(suma_gracza, suma_bota, blackjack, &saldo, stawka);

        printf("Twoje aktualne saldo: $%d\n", saldo);
        printf("Czy chcesz zagrać jeszcze raz? (1 - tak, 0 - nie): ");
        scanf("%d", &gra_trwa);
    }

    printf("Dziękujemy za grę! Twoje końcowe saldo: $%d\n", saldo);
    return 0;
}

void tura_gracza(int *suma_gracza, int *blackjack, int *saldo, int stawka) {
    int dobiera = 1;

    int pierwsza_karta = karta();
    int druga_karta = karta();
    *suma_gracza = pierwsza_karta + druga_karta;
    printf("Suma: %d\n", *suma_gracza);

    if (pierwsza_karta == druga_karta) {
        if (zapytaj_split(&pierwsza_karta, &druga_karta)) {
            printf("Rozdzielono karty!\n");
            *suma_gracza = pierwsza_karta; // Pierwsza karta staje się jedyną kartą w pierwszej ręce
            tura_gracza(suma_gracza, blackjack, saldo, stawka); // Rekurencyjne wywołanie dla drugiej ręki
            return;
        }
    }

    if (*suma_gracza == 21) {
        printf("Blackjack! Wygrywasz automatycznie!\n");
        *blackjack = 1;
        *saldo += stawka * 1.5;
        return;
    }

    printf("Czy chcesz skorzystać z opcji Double Down? (1 - tak, 0 - nie): ");
    int chce_double_down;
    scanf("%d", &chce_double_down);

    if (chce_double_down) {
        if (stawka * 2 > *saldo) {
            printf("Nie masz wystarczająco pieniędzy na Double Down.\n");
        } else {
            stawka *= 2;
            double_down(suma_gracza);
            if (*suma_gracza <= 21) {
                *saldo -= stawka;
            }
            return;
        }
    }

    while (dobiera && *suma_gracza < 21) {
        printf("Czy chcesz dobrać kartę? (1 - tak, 0 - nie): ");
        scanf("%d", &dobiera);

        if (dobiera) {
            *suma_gracza += karta();
            printf("Suma: %d\n", *suma_gracza);
        }

        if (*suma_gracza > 21) {
            printf("Bust! Przegrywasz!\n");
            *saldo -= stawka;
            return;
        }
    }
}

void tura_bota(int *suma_bota) {
    *suma_bota += karta();
    *suma_bota += karta();
    printf("Suma bota: %d\n", *suma_bota);

    while (*suma_bota < 17) {
        printf("Bot dobiera kartę...\n");
        Sleep(2000); // Opóźnienie dla lepszego efektu
        *suma_bota += karta();
        printf("Suma bota: %d\n", *suma_bota);

        if (*suma_bota > 21) {
            printf("Bot bust! Wygrywasz!\n");
            return;
        }
    }
}

int zapytaj_split(int *pierwsza_karta, int *druga_karta) {
    printf("Masz dwie takie same karty (%d, %d). Czy chcesz je rozdzielić (split)? (1 - tak, 0 - nie): ", *pierwsza_karta, *druga_karta);
    int chce_split;
    scanf("%d", &chce_split);
    if (chce_split) {
        *druga_karta = karta(); // Nowa karta dla drugiej ręki
    }
    return chce_split;
}

void double_down(int *suma_gracza) {
    printf("Double Down! Podwajanie stawki i dobieranie jednej karty...\n");
    *suma_gracza += karta();
    printf("Ostateczna suma: %d\n", *suma_gracza);

    if (*suma_gracza > 21) {
        printf("Bust! Przegrywasz!\n");
    }
}

void sprawdz_wynik(int suma_gracza, int suma_bota, int blackjack, int *saldo, int stawka) {
    if (blackjack) {
        return;
    }

    if (suma_gracza > 21) {
        printf("Przegrana. Twoja suma przekroczyła 21.\n");
    } else if (suma_bota > 21) {
        printf("Wygrana! Bot przekroczył 21.\n");
        *saldo += stawka * 2;
    } else if (suma_gracza > suma_bota) {
        printf("Wygrana! Twoja suma jest wyższa.\n");
        *saldo += stawka * 2;
    } else if (suma_gracza < suma_bota) {
        printf("Przegrana. Suma bota jest wyższa.\n");
        *saldo -= stawka;
    } else {
        printf("Remis. Stawka zostaje zwrócona.\n");
    }
}
