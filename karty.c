#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#endif

int karta() {
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8); // Ustawienie UTF-8 dla konsoli Windows
    #endif

    // Tablica figur i ich wartości
    int wartosci[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10};
    char *figury[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    int liczbaFigur = sizeof(figury) / sizeof(figury[0]);

    // Tablica kolorów
    char *kolory[] = {"♠", "♥", "♦", "♣"};
    int liczbaKolorow = sizeof(kolory) / sizeof(kolory[0]);

    // Losowanie figury i koloru
    int indexFigury = rand() % liczbaFigur;
    int indexKoloru = rand() % liczbaKolorow;

    char *wylosowanaFigura = figury[indexFigury];
    char *wylosowanyKolor = kolory[indexKoloru];
    int wartoscKarty = wartosci[indexFigury];

    // Wyświetlenie karty
    printf("┌─────────┐\n");
    printf("│ %-2s      │\n", wylosowanaFigura);
    printf("│    %s    │\n", wylosowanyKolor);
    printf("│  %s   %s  │\n", wylosowanyKolor, wylosowanyKolor);
    printf("│    %s    │\n", wylosowanyKolor);
    printf("│  %s   %s  │\n", wylosowanyKolor, wylosowanyKolor);
    printf("│       %-2s│\n", wylosowanaFigura);
    printf("└─────────┘\n");

    return wartoscKarty;
}
