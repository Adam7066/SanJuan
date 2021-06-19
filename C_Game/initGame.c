#include "basic.h"

int main() {
    srand(time(0));
    FILE *pFile = NULL;
    cOpen(pFile, tablePath, w);

    cJSON *root, *obj;
    root = cJSON_CreateObject();

    cJSON_AddItemToObject(root, "Player State", obj = cJSON_CreateObject());
    for(int i = 0; i < 4; ++i) {
        char playerName[100] = "Player";
        char nPN[2] = {'1' + i, 0};
        strcat(playerName, nPN);
        cJSON_AddItemToObject(obj, playerName, cJSON_CreateBool(false));
    }

    cJSON_AddItemToObject(root, "CareerIsChoice", obj = cJSON_CreateObject());
    cJSON_AddBoolToObject(obj, "Adventurer", true);
    cJSON_AddBoolToObject(obj, "Builder", true);
    cJSON_AddBoolToObject(obj, "Councillor", true);
    cJSON_AddBoolToObject(obj, "Producer", true);
    cJSON_AddBoolToObject(obj, "Trader", true);

    cJSON_AddItemToObject(root, "Player Career", obj = cJSON_CreateObject());
    for(int i = 0; i < 4; ++i) {
        char playerName[100] = "Player";
        char nPN[2] = {'1' + i, 0};
        strcat(playerName, nPN);
        cJSON_AddNumberToObject(obj, playerName, 0);
    }

    cJSON_AddItemToObject(root, "Card On Table", obj = cJSON_CreateObject());
    for(int i = 0; i < 4; ++i) {
        char playerName[100] = "Player", goodsName[100] = "Goods";
        char nPN[2] = {'1' + i, 0};
        strcat(playerName, nPN);
        strcat(goodsName, nPN);

        cJSON *arr = cJSON_CreateArray();
        cJSON_AddItemToArray(arr, cJSON_CreateString("Tomato plant"));
        cJSON_AddItemToObject(obj, playerName, arr);

        cJSON *arr1 = cJSON_CreateArray();
        cJSON_AddItemToArray(arr1, cJSON_CreateBool(false));
        cJSON_AddItemToObject(obj, goodsName, arr1);
    }

    cJSON_AddItemToObject(root, "Hand Card", obj = cJSON_CreateObject());
    for(int i = 0; i < 4; ++i) {
        char playerName[100] = "Player";
        char nPN[2] = {'1' + i, 0};
        strcat(playerName, nPN);
        // cJSON_AddItemToObject(obj, playerName, subObj = cJSON_CreateObject());
        // cJSON_AddNumberToObject(subObj, "num", 0);
        cJSON *arr = cJSON_CreateArray();
        // cJSON_AddItemToObject(subObj, "Cards", arr);
        cJSON_AddItemToObject(obj, playerName, arr);
    }

    cJSON_AddItemToObject(root, "Deck", obj = cJSON_CreateObject());
    cJSON *deckArr = cJSON_CreateArray();
    while(1) {
        int n = rand() % 29;
        if(cardNum[n] > 0) {
            cJSON_AddItemToArray(deckArr, cJSON_CreateString(cardStr[n]));
            --cardNum[n];
        }
        bool flag = true;
        for(int i = 0; i < 29; ++i) {
            if(cardNum[i] > 0) {
                flag = false;
                break;
            }
        }
        if(flag) break;
    }
    cJSON_AddItemToObject(obj, "DeckArr", deckArr);
    cJSON_AddNumberToObject(obj, "posDeck", 0);
    cJSON_AddItemToObject(obj, "Deadwood", cJSON_CreateArray());

    cJSON_AddItemToObject(root, "Trading Card", obj = cJSON_CreateArray());
    bool trCaFlag[5];
    memset(trCaFlag, false, sizeof(trCaFlag));
    int cnt = 0;
    while(cnt < 5) {
        int t = rand() % 5;
        if(!trCaFlag[t]) {
            cJSON *arr = cJSON_CreateArray();
            for(int i = 0; i < 5; ++i) {
                cJSON_AddItemToArray(arr, cJSON_CreateNumber(tradingCard[t][i]));
            }
            cJSON_AddItemToArray(obj, arr);
            trCaFlag[t] = true;
            ++cnt;
        }
    }

    char *str = cJSON_Print(root);
    fwrite(str, strlen(str), 1, pFile);
    cJSON_Delete(root);
    fclose(pFile);
    return 0;
}