#include "basic.h"

struct option long_options[] = {
    {"distribute", 1, NULL, 'd'},
    {"discard", 1, NULL, 'r'},
    {"start", 0, NULL, 's'},
    {"builder", 1, NULL, 'b'},
    {"end", 0, NULL, 'e'},
    {0, 0, 0, 0},
};

int cmpfunc (const void * a, const void * b) {
    return ( *(int*)a - * (int*)b );
}

cJSON *dofile(char *filename) {
    FILE *f;
    long len;
    char *data;
    cJSON *json, *ret;
    f = fopen(filename, "rb");
    fseek(f, 0, SEEK_END);
    len = ftell(f);
    fseek(f, 0, SEEK_SET);
    data = (char*)malloc(len + 1);
    int cnt = fread(data, 1, len, f);
    data[cnt] = '\0';
    json = cJSON_Parse(data);
    if (!json) {
        printf("Error before: [%s]\n", cJSON_GetErrorPtr());
        ret = NULL;
        goto EXIT;
    }
    else {
        //printf("%s\n",data);
        ret = json;
    }
EXIT:
    free(data);
    fclose(f);
    return ret;
}

void write_file(char *filename, char *out) {
    FILE *fp = NULL;
    fp = fopen(filename, "w");
    if(fp == NULL) {
        fprintf(stderr, "open file failed\n");
        exit(-1);
    }
    fprintf(fp, "%s", out);
    if(fp != NULL) fclose(fp);
}

void distribute(int player, int num) {
    cJSON *root, *handCard, *deck;
    char *out;
    root = dofile(tablePath);
    handCard = cJSON_GetObjectItem(root, "Hand Card");
    deck = cJSON_GetObjectItem(root, "Deck");
    char temp[8] = "Player";
    char cc[2] = {'0' + player, 0};
    strcat(temp, cc);
    cJSON *handCardArr = cJSON_GetObjectItem(handCard, temp);
    cJSON *deckArr = cJSON_GetObjectItem(deck, "DeckArr");
    cJSON *deadwood = cJSON_GetObjectItem(deck, "Deadwood");
    int deckArrLen = cJSON_GetArraySize(deckArr);
    int pos = cJSON_GetObjectItem(deck, "posDeck")->valueint;
    if(pos + num >= deckArrLen) {
        for(int i = 0; i < deckArrLen - pos; ++i)
            cJSON_AddItemToArray(deadwood, cJSON_CreateString(cJSON_GetArrayItem(deckArr, pos + i)->valuestring));
        deckArrLen = cJSON_GetArraySize(deckArr);
        for(int i = 0; i < deckArrLen; ++i) {
            cJSON_DeleteItemFromArray(deckArr, 0);
        }
        cJSON_GetObjectItem(deck, "posDeck")->valueint = 0;
        cJSON_GetObjectItem(deck, "posDeck")->valuedouble = 0;
        pos = 0;
        int deadwoodLen = cJSON_GetArraySize(deadwood);
        for(int i = 0; i < deadwoodLen; ++i) {
            cJSON_AddItemToArray(deckArr, cJSON_CreateString(cJSON_GetArrayItem(deadwood, 0)->valuestring));
            cJSON_DeleteItemFromArray(deadwood, 0);
        }
    }
    deckArrLen = cJSON_GetArraySize(deckArr);

    for(int i = 0; i < num; ++i) {
        char *item = cJSON_GetArrayItem(deckArr, pos + i)->valuestring;
        cJSON_AddItemToArray(handCardArr, cJSON_CreateString(item));
    }
    cJSON_GetObjectItem(deck, "posDeck")->valueint += num;
    cJSON_GetObjectItem(deck, "posDeck")->valuedouble += num;
    out = cJSON_Print(root);
    write_file(tablePath, out);
    cJSON_Delete(root);
}

void discard(int player, int pos) {
    cJSON *root, *handCard, *deck, *deadwood;
    char *out;
    root = dofile(tablePath);
    handCard = cJSON_GetObjectItem(root, "Hand Card");
    deck = cJSON_GetObjectItem(root, "Deck");
    deadwood = cJSON_GetObjectItem(deck, "Deadwood");
    char temp[8] = "Player";
    char cc[2] = {'0' + player, 0};
    strcat(temp, cc);
    cJSON *handCardArr = cJSON_GetObjectItem(handCard, temp);
    if(pos <= cJSON_GetArraySize(handCardArr)) {
        cJSON_AddItemToArray(deadwood, cJSON_CreateString(cJSON_GetArrayItem(handCardArr, pos - 1)->valuestring));
        cJSON_DeleteItemFromArray(handCardArr, pos - 1);
    }
    out = cJSON_Print(root);
    write_file(tablePath, out);
    cJSON_Delete(root);
}

void chooseFromDeck(int player, int t, int n, int m) { // 發 t 張從最後 n 張選 m 張
    distribute(player, t);
    if(player == 1) printf("ChooseFromDeck:%d/%d", n, m);
    else {
        cJSON *root, *handCard, *plArrHand;
        root = dofile(tablePath);
        handCard = cJSON_GetObjectItem(root, "Hand Card");
        char temp[8] = "Player";
        char cc[2] = {'0' + player, 0};
        strcat(temp, cc);
        plArrHand = cJSON_GetObjectItem(handCard, temp);
        int plArrHandLen = cJSON_GetArraySize(plArrHand);
        for(int i = 0; i < n - m; ++i) {
            discard(player, (plArrHandLen - n + m + 1 + i));
        }
        cJSON_Delete(root);
    }
}

void adventurer(int player, bool privilege) {
    distribute(player, 1);
    cJSON *root, *cardOnTable, *plArr, *deck, *deckArr;
    root = dofile(tablePath);
    cardOnTable = cJSON_GetObjectItem(root, "Card On Table");
    char temp[8] = "Player";
    char cc[2] = {'0' + player, 0};
    strcat(temp, cc);
    plArr = cJSON_GetObjectItem(cardOnTable, temp);
    int plArrLen = cJSON_GetArraySize(plArr);
    bool adGuFlag = false, librFlag = false;
    for(int i = 0; i < plArrLen; ++i) {
        char *cardName = cJSON_GetArrayItem(plArr, i)->valuestring;
        if(strcmp(cardName, "Adventurers Guild") == 0) adGuFlag = true;
        else if(strcmp(cardName, "Library") == 0) librFlag = true;
    }
    deck = cJSON_GetObjectItem(root, "Deck");
    deckArr = cJSON_GetObjectItem(deck, "DeckArr");
    int posDeck = cJSON_GetObjectItem(deck, "posDeck")->valueint;
    char nextCardStr[4][20] = {0};
    int cntNextCard = 0;
    for(int i = 0; i < 4; ++i) {
        if(posDeck + i <= 105) {
            strcpy(nextCardStr[i], cJSON_GetArrayItem(deckArr, posDeck + i)->valuestring);
            ++cntNextCard;
        }
    }
    if(adGuFlag) {
        int cost[4];
        for(int i = 0; i < cntNextCard; ++i) {
            cost[i] = -1;
            for(int j = 0; j < 29; ++j) {
                if(strcmp(nextCardStr[i], cardStr[j]) == 0) {
                    cost[i] = cardCost[j];
                    break;
                }
            }
        }
        qsort(cost, cntNextCard, sizeof(int), cmpfunc);
        bool flagCostDiff = true;
        for(int i = 0; i < cntNextCard - 1; ++i) {
            if(cost[i] == cost[i + 1]) {
                flagCostDiff = false;
                break;
            }
        }
        if(flagCostDiff) chooseFromDeck(player, 4, 4, 1);
        else {
            cJSON_GetObjectItem(deck, "posDeck")->valueint += cntNextCard;
            cJSON_GetObjectItem(deck, "posDeck")->valuedouble += cntNextCard;
            char *out = cJSON_Print(root);
            write_file(tablePath, out);
        }
    }
    cJSON_Delete(root);
    if(librFlag && privilege) distribute(player, 2);
}

int checkCanBuild(int player, int whichCard, int discount, bool privilege) {
    cJSON *root, *cardOnTable, *plArrTable, *handCard, *plArrHand, *gdsArr;
    root = dofile(tablePath);
    cardOnTable = cJSON_GetObjectItem(root, "Card On Table");
    handCard = cJSON_GetObjectItem(root, "Hand Card");
    char temp[8] = "Player", temp2[7] = "Goods";
    char cc[2] = {'0' + player, 0};
    strcat(temp, cc);
    strcat(temp2, cc);
    plArrTable = cJSON_GetObjectItem(cardOnTable, temp);
    gdsArr = cJSON_GetObjectItem(cardOnTable, temp2);
    plArrHand = cJSON_GetObjectItem(handCard, temp);
    int plArrTableLen = cJSON_GetArraySize(plArrTable);
    int plArrHandLen = cJSON_GetArraySize(plArrHand);
    if(plArrHandLen <= whichCard) {
        if(player == 1) printf("Can't Build.");
        return -1;
    }
    char *wantBuCaName = cJSON_GetArrayItem(plArrHand, whichCard)->valuestring;
    int cost = 0;
    bool productionFlag = false;
    for(int i = 0; i < 29; ++i) {
        if(strcmp(wantBuCaName, cardStr[i]) == 0) {
            if(i < 5) productionFlag = true;
            cost = cardCost[i];
            break;
        }
    }
    cost -= discount;

    if(!productionFlag) {
        for(int i = 0; i < plArrTableLen; ++i) {
            char *cardName = cJSON_GetArrayItem(plArrTable, i)->valuestring;
            if(strcmp(wantBuCaName, cardName) == 0) {
                if(player == 1) printf("Can't Build.");
                return -1;
            }
        }
    }
    bool waHoFlag = false, poHoFlag = false, crHoFlag = false, unOfFoFlag = false, librFlag = false;
    for(int i = 0; i < plArrTableLen; ++i) {
        char *cardName = cJSON_GetArrayItem(plArrTable, i)->valuestring;
        if(strcmp(cardName, "Warden house") == 0) waHoFlag = true;
        if(strcmp(cardName, "Poor House") == 0) poHoFlag = true;
        // Black Market, Builders Crane
        if(strcmp(cardName, "Craft House") == 0) crHoFlag = true;
        if(strcmp(cardName, "Unite of foremans") == 0) unOfFoFlag = true;
        else if(strcmp(cardName, "Library") == 0) librFlag = true;
    }
    if(waHoFlag && productionFlag) --cost;
    if(unOfFoFlag && !productionFlag) --cost;
    if(librFlag && privilege) cost -= 2;
    if(cost < 0) cost = 0;
    if(cost < plArrHandLen) {
        // 結束手牌<=1時抽一張, 抽一張
        if(player == 1) printf("Can Build. Cost:%d. %d, %d", cost, poHoFlag, (crHoFlag && !productionFlag));
        cJSON_AddItemToArray(plArrTable, cJSON_CreateString(wantBuCaName));
        cJSON_AddItemToArray(gdsArr, cJSON_CreateBool(false));
        char *out = cJSON_Print(root);
        write_file(tablePath, out);
        discard(player, whichCard + 1);
        if(player != 1) {
            if(poHoFlag) distribute(player, 1);
            if(crHoFlag && !productionFlag) distribute(player, 1);
        }
        return cost;
    }
    else {
        if(player == 1) printf("Can't Build.");
        return -1;
    }
    cJSON_Delete(root);
}

void robotBuild(int player, int discount, bool privilege) {
    for(int i = 0; i < 24; ++i) {
        int cost = checkCanBuild(player, i, discount, privilege);
        if(cost != -1) {
            for(int j = 0; j < cost; ++j) discard(player, 1);
            break;
        }
    }
}

void councillor(int player, int n, int m, bool privilege) { // 發 n 選 m
    cJSON *root, *cardOnTable, *plArrTable, *handCard, *plArrHand;
    root = dofile(tablePath);
    cardOnTable = cJSON_GetObjectItem(root, "Card On Table");
    handCard = cJSON_GetObjectItem(root, "Hand Card");
    char temp[8] = "Player";
    char cc[2] = {'0' + player, 0};
    strcat(temp, cc);
    plArrTable = cJSON_GetObjectItem(cardOnTable, temp);
    plArrHand = cJSON_GetObjectItem(handCard, temp);
    int plArrTableLen = cJSON_GetArraySize(plArrTable);
    int plArrHandLen = cJSON_GetArraySize(plArrHand);
    bool archFlag = false, prefFlag = false, librFlag = false;
    for(int i = 0; i < plArrTableLen; ++i) {
        char *cardName = cJSON_GetArrayItem(plArrTable, i)->valuestring;
        if(strcmp(cardName, "Archive") == 0) archFlag = true;
        else if(strcmp(cardName, "Prefecture") == 0) prefFlag = true;
        else if(strcmp(cardName, "Library") == 0) librFlag = true;
    }
    cJSON_Delete(root);
    if(prefFlag) m = 2;
    if(librFlag && privilege) n = 8;
    int q = n;
    if(archFlag) q += plArrHandLen;
    chooseFromDeck(player, n, q, m);
}

int checkNumCanProduce(int player, bool privilege) {
    cJSON *root, *cardOnTable, *plArrTable, *goodsArr;
    root = dofile(tablePath);
    cardOnTable = cJSON_GetObjectItem(root, "Card On Table");
    char temp[8] = "Player", temp2[7] = "Goods";
    char cc[2] = {'0' + player, 0};
    strcat(temp, cc);
    strcat(temp2, cc);
    plArrTable = cJSON_GetObjectItem(cardOnTable, temp);
    goodsArr = cJSON_GetObjectItem(cardOnTable, temp2);
    int plArrTableLen = cJSON_GetArraySize(plArrTable);
    int cnt = 0;
    bool aqFlag = false, librFlag = false;
    for(int i = 0; i < plArrTableLen; ++i) {
        char *cardName = cJSON_GetArrayItem(plArrTable, i)->valuestring;
        for(int j = 0; j < 5; ++j) {
            if(cJSON_GetArrayItem(goodsArr, i)->type == cJSON_False) {
                if(strcmp(cardName, cardStr[j]) == 0) {
                    ++cnt;
                    break;
                }
            }
        }
        // Households in Qt,
        if(strcmp(cardName, "Aqueduct") == 0) aqFlag = true;
        else if(strcmp(cardName, "Library") == 0) librFlag = true;
    }
    cJSON_Delete(root);
    int res = (privilege) ? 2 : 1;
    if(librFlag && privilege) res = 3;
    if(aqFlag) ++res;
    return (res < cnt) ? res : cnt;
}

void robotProduce(int player, bool privilege) {
    int cnt = checkNumCanProduce(player, privilege);
    int tcnt = cnt;
    cJSON *root, *cardOnTable, *plArrTable, *goodsArr, *deck, *deckArr, *deadwood;
    root = dofile(tablePath);
    cardOnTable = cJSON_GetObjectItem(root, "Card On Table");
    deck = cJSON_GetObjectItem(root, "Deck");
    char temp[8] = "Player", temp2[7] = "Goods";
    char cc[2] = {'0' + player, 0};
    strcat(temp, cc);
    strcat(temp2, cc);
    plArrTable = cJSON_GetObjectItem(cardOnTable, temp);
    goodsArr = cJSON_GetObjectItem(cardOnTable, temp2);
    deckArr = cJSON_GetObjectItem(deck, "DeckArr");
    deadwood = cJSON_GetObjectItem(deck, "Deadwood");
    int plArrTableLen = cJSON_GetArraySize(plArrTable);
    int pos = cJSON_GetObjectItem(deck, "posDeck")->valueint;
    for(int i = 0; i < cnt; ++i)
        cJSON_AddItemToArray(deadwood, cJSON_CreateString(cJSON_GetArrayItem(deckArr, pos + i)->valuestring));
    cJSON_GetObjectItem(deck, "posDeck")->valueint += cnt;
    cJSON_GetObjectItem(deck, "posDeck")->valuedouble += cnt;
    bool hoFlag = false;
    for(int i = 0; i < plArrTableLen; ++i) {
        char *cardName = cJSON_GetArrayItem(plArrTable, i)->valuestring;
        for(int j = 0; j < 5; ++j) {
            if(cJSON_GetArrayItem(goodsArr, i)->type == cJSON_False) {
                if(strcmp(cardName, cardStr[j]) == 0) {
                    if(cnt > 0) {
                        cJSON_ReplaceItemInArray(goodsArr, i, cJSON_CreateBool(true));
                        --cnt;
                    }
                    break;
                }
            }
        }
        if(strcmp(cardName, "Households") == 0) hoFlag = true;
    }
    char *out = cJSON_Print(root);
    write_file(tablePath, out);
    cJSON_Delete(root);
    if(hoFlag && tcnt >= 2) distribute(player, 1);
}

int checkNumCanTrade(int player, bool privilege) {
    cJSON *root, *cardOnTable, *plArrTable, *goodsArr;
    root = dofile(tablePath);
    cardOnTable = cJSON_GetObjectItem(root, "Card On Table");
    char temp[8] = "Player", temp2[7] = "Goods";
    char cc[2] = {'0' + player, 0};
    strcat(temp, cc);
    strcat(temp2, cc);
    plArrTable = cJSON_GetObjectItem(cardOnTable, temp);
    goodsArr = cJSON_GetObjectItem(cardOnTable, temp2);
    int plArrTableLen = cJSON_GetArraySize(plArrTable);
    int cnt = 0;
    bool trPoFlag = false, librFlag = false;
    for(int i = 0; i < plArrTableLen; ++i) {
        char *cardName = cJSON_GetArrayItem(plArrTable, i)->valuestring;
        if(cJSON_GetArrayItem(goodsArr, i)->type == cJSON_True) ++cnt;
        // Marketplace, Trade route in Qt
        if(strcmp(cardName, "Trading Post") == 0) trPoFlag = true;
        else if(strcmp(cardName, "Library") == 0) librFlag = true;
    }
    cJSON_Delete(root);
    int res = (privilege) ? 2 : 1;
    if(librFlag && privilege) res = 3;
    if(trPoFlag) ++res;
    return (res < cnt) ? res : cnt;
}

void robotTrade(int player, bool privilege) {
    int cnt = checkNumCanTrade(player, privilege);
    int tcnt = cnt;
    cJSON *root, *cardOnTable, *plArrTable, *goodsArr, *trCaArr;
    root = dofile(tablePath);
    cardOnTable = cJSON_GetObjectItem(root, "Card On Table");
    trCaArr = cJSON_GetArrayItem(cJSON_GetObjectItem(root, "Trading Card"), 0);
    char temp[8] = "Player", temp2[7] = "Goods";
    char cc[2] = {'0' + player, 0};
    strcat(temp, cc);
    strcat(temp2, cc);
    plArrTable = cJSON_GetObjectItem(cardOnTable, temp);
    goodsArr = cJSON_GetObjectItem(cardOnTable, temp2);
    int plArrTableLen = cJSON_GetArraySize(plArrTable);

    int prices = 0;
    bool maPlFlag = false, trRoFlag = false;
    for(int i = 0; i < plArrTableLen; ++i) {
        char *cardName = cJSON_GetArrayItem(plArrTable, i)->valuestring;
        for(int j = 0; j < 5; ++j) {
            if(cJSON_GetArrayItem(goodsArr, i)->type == cJSON_True) {
                if(strcmp(cardName, cardStr[j]) == 0) {
                    if(cnt > 0) {
                        cJSON_ReplaceItemInArray(goodsArr, i, cJSON_CreateBool(false));
                        prices += cJSON_GetArrayItem(trCaArr, j)->valueint;
                        --cnt;
                    }
                    break;
                }
            }
        }
        if(strcmp(cardName, "Marketplace") == 0) maPlFlag = true;
        if(strcmp(cardName, "Trade route") == 0) trRoFlag = true;
    }
    char *out = cJSON_Print(root);
    write_file(tablePath, out);
    cJSON_Delete(root);
    distribute(player, prices);
    if(maPlFlag && tcnt >= 2) distribute(player, 1);
    if(trRoFlag) distribute(player, 1);
}

void moveTradingCard() {
    cJSON *root, *trCaArr, *tempArr, *tt;
    root = dofile(tablePath);
    trCaArr = cJSON_GetObjectItem(root, "Trading Card");
    tt = cJSON_GetArrayItem(trCaArr, 0);
    tempArr = cJSON_CreateArray();
    for(int i = 0; i < 5; ++i)
        cJSON_AddItemToArray(tempArr, cJSON_CreateNumber(cJSON_GetArrayItem(tt, i)->valueint));
    cJSON_DeleteItemFromArray(trCaArr, 0);
    cJSON_AddItemToArray(trCaArr, tempArr);
    char *out = cJSON_Print(root);
    write_file(tablePath, out);
    cJSON_Delete(root);
}

void robotRound(int player, int career) {
    if(career == 1) adventurer(player, true);
    else if(career == 2) {
        for(int i = 1; i <= 4; ++i) {
            if(i == 1) printf("P1 Build");
            else if(i == player) robotBuild(i, 1, true);
            else robotBuild(i, 0, false);
        }
    }
    else if(career == 3) {
        for(int i = 1; i <= 4; ++i) {
            if(i == player) councillor(i, 5, 1, true);
            else councillor(i, 2, 1, false);
        }
    }
    else if(career == 4) {
        for(int i = 1; i <= 4; ++i) {
            if(i == 1) printf("Can Produce %d items", checkNumCanProduce(1, false));
            else if(i == player) robotProduce(i, true);
            else robotProduce(i, false);
        }
    }
    else if(career == 5) {
        for(int i = 1; i <= 4; ++i) {
            if(i == 1) printf("Can Trade %d items", checkNumCanTrade(1, false));
            else if(i == player) robotTrade(i, true);
            else robotTrade(i, false);
        }
        moveTradingCard();
    }
}

void check() {
    cJSON *root, *handCard;
    root = dofile(tablePath);
    handCard = cJSON_GetObjectItem(root, "Hand Card");
    for(int i = 1; i <= 1; ++i) {
        char temp[8] = "Player";
        char cc[2] = {'0' + i, 0};
        strcat(temp, cc);
        cJSON *handArr = cJSON_GetObjectItem(handCard, temp);
        int handArrLen = cJSON_GetArraySize(handArr);
        bool towerFlag = false;
        for(int j = 0; j < handArrLen; ++j) {
            char *cardName = cJSON_GetArrayItem(handArr, j)->valuestring;
            if(strcmp(cardName, "Tower") == 0) towerFlag = true;
        }
        int maxCardNum = (towerFlag) ? 12 : 7;
        if(handArrLen > maxCardNum)
            chooseFromDeck(i, 0, handArrLen, maxCardNum);
    }
    cJSON *playerState, *caIsCh, *playerCareer;
    playerState = cJSON_GetObjectItem(root, "Player State");
    caIsCh = cJSON_GetObjectItem(root, "CareerIsChoice");
    playerCareer = cJSON_GetObjectItem(root, "Player Career");
    for(int i = 0; i < 5; ++i)
        cJSON_GetObjectItem(caIsCh, careerStr[i])->type = cJSON_True;
    for(int i = 1; i <= 4; ++i) {
        char temp[8] = "Player";
        char cc[2] = {'0' + i, 0};
        strcat(temp, cc);
        cJSON_GetObjectItem(playerState, temp)->type = cJSON_False;
        cJSON_GetObjectItem(playerCareer, temp)->valueint = 0;
        cJSON_GetObjectItem(playerCareer, temp)->valuedouble = 0;
    }
    char *out = cJSON_Print(root);
    write_file(tablePath, out);
    cJSON_Delete(root);
}

void gameEnd() {
    int sum[4] = {0}, prodCardNum[4] = {0}, specCardNum[4] = {0}, monumentNum[4] = {0};
    cJSON *root, *cardOnTable, *plArrTable, *handCard;
    root = dofile(tablePath);
    cardOnTable = cJSON_GetObjectItem(root, "Card On Table");
    handCard = cJSON_GetObjectItem(root, "Hand Card");
    for(int i = 1; i <= 4; ++i) {
        char temp[8] = "Player";
        char cc[2] = {'0' + i, 0};
        strcat(temp, cc);
        plArrTable = cJSON_GetObjectItem(cardOnTable, temp);
        int plArrTableLen = cJSON_GetArraySize(plArrTable);
        bool guHaFlag = false, ciHaFlag = false, trArFlag = false, palaFlag = false;
        for(int j = 0; j < plArrTableLen; ++j) {
            char *cardName = cJSON_GetArrayItem(plArrTable, j)->valuestring;
            if(strcmp(cardName, "Statue") == 0 || strcmp(cardName, "Alley of Glory") == 0 || strcmp(cardName, "Heroes") == 0)
                ++monumentNum[i - 1];
            else if(strcmp(cardName, "Guild Hall") == 0) guHaFlag = true;
            else if(strcmp(cardName, "City Hall") == 0) ciHaFlag = true;
            else if(strcmp(cardName, "Triumphal Arch") == 0) trArFlag = true;
            else if(strcmp(cardName, "Palace") == 0) palaFlag = true;
            for(int k = 0; k < 29; ++k) {
                if(strcmp(cardName, cardStr[k]) == 0) {
                    if(k < 5) ++prodCardNum[i - 1];
                    else ++specCardNum[i - 1];
                    if(cardVP[k] > 0) sum[i - 1] += cardVP[k];
                    break;
                }
            }
        }
        if(guHaFlag) sum[i - 1] += prodCardNum[i - 1] * 2;
        if(ciHaFlag) sum[i - 1] += specCardNum[i - 1];
        if(trArFlag) sum[i - 1] += monumentNum[i - 1] * 2 + 2;
        if(palaFlag) sum[i - 1] += (int)(sum[i - 1] / 4);
    }
    int temp[4], maxVP = 0;
    for(int i = 0 ; i < 4; ++i) {
        printf("%d ", sum[i]);
        if(sum[i] > maxVP) maxVP = sum[i];
        temp[i] = sum[i];
    }
    qsort(temp, 4, sizeof(int), cmpfunc);
    bool tieFlag = false;
    for(int i = 0; i < 3; ++i) {
        if(temp[i] == temp[i + 1]) {
            tieFlag = true;
            break;
        }
    }
    int winner = 1;
    if(tieFlag) {
        int tieCardNum = 0;
        for(int i = 0; i < 4; ++i) {
            if(sum[i] == maxVP) {
                cJSON *plArrHand, *goodArr;
                char temp[8] = "Player", temp2[7] = "Goods";
                char cc[2] = {'1' + i, 0};
                strcat(temp, cc);
                strcat(temp2, cc);
                plArrHand = cJSON_GetObjectItem(handCard, temp);
                int plArrHandLen = cJSON_GetArraySize(plArrHand);
                goodArr = cJSON_GetObjectItem(cardOnTable, temp2);
                int goodArrLen = cJSON_GetArraySize(goodArr);
                int goods  = 0;
                for(int j = 0; j < goodArrLen; ++j) {
                    if(cJSON_IsTrue(cJSON_GetArrayItem(goodArr, j))) ++goods;
                }
                if(plArrHandLen + goods > tieCardNum) {
                    tieCardNum = plArrHandLen + goods;
                    winner = i + 1;
                }
                break;
            }
        }
    }
    printf("%d", winner);
    cJSON_Delete(root);
}

int main(int argc, char *argv[]) {
    srand(time(0));
    int c = 0, index = 0, bMode = -1;
    bool sMode = false;
    while ((c = getopt_long(argc, argv, "d:r:sb:e", long_options, &index)) != -1) {
        if(c == 'd') {
            char str[1000] = {0};
            strcpy(str, optarg);
            int player, num;
            char *find = strchr(str, '/'), **endptr = NULL;
            char temp[1000] = {0};
            strncpy(temp, str, find - str);
            player = strtol(temp, endptr, 10);
            strcpy(temp, find + 1);
            num = strtol(temp, endptr, 10);
            distribute(player, num);
        }
        else if(c == 'r') {
            char str[1000] = {0};
            strcpy(str, optarg);
            int player, pos;
            char *find = strchr(str, '/'), **endptr = NULL;
            char temp[1000] = {0};
            strncpy(temp, str, find - str);
            player = strtol(temp, endptr, 10);
            strcpy(temp, find + 1);
            pos = strtol(temp, endptr, 10);
            discard(player, pos);
        }
        else if(c == 's') sMode = true;
        else if(c == 'b') {
            char **endptr = NULL;
            bMode = strtol(optarg, endptr, 10);
        }
        else if(c == 'e') gameEnd();
        else {
            puts("Error Option!");
            return 0;
        }
    }
    cJSON *root, *playerCareer, *playerState;
    root = dofile(tablePath);
    playerCareer = cJSON_GetObjectItem(root, "Player Career");
    playerState = cJSON_GetObjectItem(root, "Player State");
    int plCa[4] = {0};
    bool plSt[4] = {false};
    for(int i = 0; i < 4; ++i) {
        char temp[8] = "Player";
        char cc[2] = {'1' + i, 0};
        strcat(temp, cc);
        plCa[i] = cJSON_GetObjectItem(playerCareer, temp)->valueint;
        if(cJSON_IsTrue(cJSON_GetObjectItem(playerState, temp))) plSt[i] = true;
        else plSt[i] = false;
    }
    if(sMode) {
        if(plCa[0] == 0) {
            printf("P1 select career");
            return 0;
        }
        else {
            if(!plSt[0]) {
                plSt[0] = true;
                cJSON_GetObjectItem(playerState, "Player1")->type = cJSON_True;
                cJSON *caIsCh = cJSON_GetObjectItem(root, "CareerIsChoice");
                for(int i = 0; i < 5; ++i) {
                    if(plCa[0] == i + 1) {
                        cJSON_GetObjectItem(caIsCh, careerStr[i])->type = cJSON_False;
                        break;
                    }
                }
                char *out = cJSON_Print(root);
                write_file(tablePath, out);
                if(plCa[0] == 1) adventurer(1, true);
                else if(plCa[0] == 2) {
                    printf("P1 Build");
                    for(int i = 2; i <= 4; ++i)
                        robotBuild(i, 0, false);
                }
                else if(plCa[0] == 3) {
                    for(int i = 1; i <= 4; ++i)
                        councillor(i, ((i == 1) ? 5 : 2), 1, ((i == 1) ? true : false));
                }
                else if(plCa[0] == 4) {
                    int cnt = checkNumCanProduce(1, true);
                    printf("Can Produce %d items", cnt);
                    for(int i = 2; i <= 4; ++i)
                        robotProduce(i, false);
                }
                else if(plCa[0] == 5) {
                    int cnt = checkNumCanTrade(1, true);
                    printf("Can Trade %d items", cnt);
                    for(int i = 2; i <= 4; ++i)
                        robotTrade(i, false);
                    moveTradingCard();
                }
            }
            else {
                for(int i = 2; i <= 4; ++i) {
                    if(!plSt[i - 1]) {
                        cJSON *caIsCh = cJSON_GetObjectItem(root, "CareerIsChoice");
                        bool caIsChFlag[5] = {false};
                        for(int i = 0; i < 5; ++i) {
                            if(cJSON_IsTrue(cJSON_GetObjectItem(caIsCh, careerStr[i]))) caIsChFlag[i] = true;
                            else caIsChFlag[i] = false;
                        }
                        char temp[8] = "Player";
                        char cc[2] = {'0' + i, 0};
                        strcat(temp, cc);
                        int t = rand() % 5;
                        while(!caIsChFlag[t]) t = rand() % 5;
                        plCa[i - 1] = t + 1;
                        cJSON_GetObjectItem(caIsCh, careerStr[t])->type = cJSON_False;
                        cJSON_GetObjectItem(playerCareer, temp)->valueint = t + 1;
                        cJSON_GetObjectItem(playerCareer, temp)->valuedouble = t + 1;
                        plSt[i - 1] = true;
                        cJSON_GetObjectItem(playerState, temp)->type = cJSON_True;
                        char *out = cJSON_Print(root);
                        write_file(tablePath, out);
                        robotRound(i, plCa[i - 1]);
                        break;
                    }
                }
            }
            bool flagNeedCheck = true;
            for(int i = 0; i < 4; ++i) {
                if(!plSt[i]) {
                    flagNeedCheck = false;
                    break;
                }
            }
            if(flagNeedCheck) check();
        }
        cJSON_Delete(root);
    }
    if(bMode != -1) {
        int cnt = 0;
        for(int i = 0; i < 4; ++i) if(plSt[i]) ++cnt;
        if(cnt == 1) checkCanBuild(1, bMode, 1, true);
        else checkCanBuild(1, bMode, 0, false);
    }
    return 0;
}