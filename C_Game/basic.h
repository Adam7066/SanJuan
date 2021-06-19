#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <getopt.h>
#include "cJSON.h"
#define cOpen(pF, fileName, mode) {if((pF = fopen(fileName, #mode)) == NULL) { printf( "File could not be opened!\n" ); return 0;}}
#define cFgets(str, len, stream) {fgets(str, len, stream); if(str[strlen(str)-1]=='\n') str[strlen(str)-1]=0;}
char *tablePath = "./GameStatus/table.json";
char careerStr[5][11] = {"Adventurer", "Builder", "Councillor", "Producer", "Trader"};
char cardStr[29][20] = {
    "Tomato plant", "Pond farm", "Mill", "Zeppelin shipyard", "Shipyard",
    "Warden house", "Adventurers Guild", "Archive", "Poor House", "Black Market",
    "Trading Post", "Households", "Marketplace", "Builders Crane", "Temple",
    "Tower", "Aqueduct", "Craft House", "Prefecture", "Trade route",
    "Unite of foremans", "Library", "Statue", "Alley of Glory", "Heroes",
    "Guild Hall", "City Hall", "Triumphal Arch", "Palace"
};
int cardNum[29] = {
    6, 8, 8, 8, 8,
    3, 3, 3, 3, 3,
    3, 3, 3, 3, 3,
    3, 3, 3, 3, 3,
    3, 3, 3, 3, 3,
    2, 2, 2, 2
};
int cardCost[29] = {
    1, 2, 3, 4, 5,
    1, 1, 1, 2, 2,
    2, 2, 2, 2, 3,
    3, 3, 3, 4, 4,
    4, 5, 3, 4, 5,
    6, 6, 6, 6
};
int cardVP[29] = {
    1, 1, 2, 2, 3,
    1, 1, 1, 1, 1,
    1, 1, 1, 1, 2,
    2, 2, 2, 2, 2,
    2, 3, 3, 4, 5,
    -1, -1, -1, -1
};
int tradingCard[5][5] = {
    {1, 1, 2, 2, 3},
    {1, 1, 1, 2, 2},
    {1, 1, 2, 2, 2},
    {1, 2, 2, 2, 3},
    {1, 2, 2, 3, 3}
};
