#include "dict.h"

Dict makeDict() {
    Dict dict;
    dict = (Dict)calloc(SIZE, sizeof(Data*));
    if (dict == NULL) {
        fprintf(stderr, "Erreur calloc dans 'makeDict'\n");
        exit(2);
    }
    return dict;
}

// unsigned long hashf(Player *board) {
//     unsigned long hash = 14695981039346656037UL;
//     for (Player *p = board; *p; p++) {
//         hash ^= (unsigned long)(unsigned char)((*p)->pion);
//         hash *= 1099511628211UL;
//     }
//     //printf("%lu\n", hash);
//     return hash;
// }

unsigned long hashf(Game game) {
    unsigned long hash = 14695981039346656037UL;
    for (int i = 0; i < game->height; i ++) {
        for (int j = 0; j < game->width; j ++) {
            hash ^= (unsigned long)(unsigned char)game->board[i][j];
            hash *= 1099511628211UL;
        }
    }
    return hash;
}

int search(Dict dict, unsigned long id, bool *found) {
    int i = id % SIZE;
    *found = false;
    while (dict[i] && dict[i]->id != id) {
        i = (i + 1) % SIZE;
    }
    if (dict[i] && dict[i]->id == id)
        *found = true;
    return i;
}

void insert(Dict dict, unsigned long id, int score) {
    Data *d;
    bool found;
    int i = search(dict, id, &found);
    if (found) {
        dict[i]->score = score;
        return;
    }
    d = (Data*)malloc(sizeof(Data));
    if (!d) {
        fprintf(stderr, "Erreur malloc dans 'insert'\n");
        exit(2);
    }
    d->id = id;
    d->score = score;
    dict[i] = d;
}

void freeDict(Dict dict) {
    for (int i = 0; i < SIZE; i ++) {
        free(dict[i]);
    }
    free(dict);
}

void printDict(Dict dict) {
    printf("Dict(\n\t");
    for (int i = 0; i < SIZE; i ++) {
        if (dict[i])
            printf("(%lu, %d) ", dict[i]->id, dict[i]->score);
    }
    printf("\n)\n");
}
