#include "dict.hpp"

// Data

Data::Data(unsigned long id, int score): id{id}, score{score}
    {}

void Data::operator=(int val) {
    score = val;
}

bool Data::operator==(unsigned long other) {
    return (id == other);
}

bool Data::operator!=(unsigned long other) {
    return (id != other);
}

string Data::repr() {
    return "(" + to_string(id) + "->" + to_string(score) + ")";
}

int Data::value() {
    return score;
}

// Dict

Dict::Dict(int size): size{size}, arr{new Data*[size]}, nb{0}
    {}

Dict::~Dict() {
    for (int i = 0; i < size; i ++) {
        delete arr[i];
    }
    delete[] arr;
}

Data& Dict::operator[](unsigned long id) {
    int i;
    bool found;
    i = search(id, &found);
    if (found) return *arr[i];
    if (size == nb)
        throw length_error("Dict too short");
    arr[i] = new Data{id};
    nb ++;
    return *arr[i];
}

string Dict::repr() {
    if (nb == 0)
        return (string)"Dict()";
    string str = "Dict(";
    for (int i = 0; i < size; i ++) {
        if (!arr[i]) continue;
        str += arr[i]->repr() + ", ";
    }
    str.resize(str.length()-2);
    return str + ")";
}

int Dict::length() {
    return nb;
}

int Dict::search(unsigned long id, bool *found) {
    int i = id % size, cmp = 0;
    *found = false;
    while (arr[i] && *arr[i] != id) {
        i = (i + 1) % size;
        if (++ cmp >= size) break;
    }
    if (arr[i] && *arr[i] == id) {
        *found = true;
    }
    return i;
}

unsigned long hashf(Game *game) {
    unsigned long hash = 14695981039346656037UL;
    for (int i = 0; i < game->height(); i ++) {
        for (int j = 0; j < game->width(); j ++) {
            hash += (hash << 5);
            hash ^= (unsigned long)game->select(i, j);
        }
    }
    return hash;
}

void dictTest() {
    Dict dict{10};

    cout << dict.repr() << endl;
    dict[4] = 5;
    dict[14] = 10;
    cout << dict.repr() << endl;
    dict[14] = 7;
    cout << dict.repr() << endl;
    dict[43] = 5;
    dict[454] = 5;
    dict[41] = 5;
    dict[423423] = 5;
    dict[123] = 5;
    dict[456] = 5;
    dict[1] = 5;
    dict[2] = 5;
    dict[4] = 1;
    // dict[5] = 1; // uncomment will throw an error
    cout << dict.repr() << endl;
    cout << dict.length() << endl;
}