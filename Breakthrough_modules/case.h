#pragma once

#include <stdbool.h>

#define TAILLE 8

typedef struct {
    int ligne;
    int colonne;
} Case;

bool estDansPlateau(int lig, int col);
Case lireCase();
