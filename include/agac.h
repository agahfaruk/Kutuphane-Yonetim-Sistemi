#ifndef AGAC_H
#define AGAC_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <cstdlib>
#include <windows.h>
#include <ctime>
#include <algorithm>
#include <string>
#include "ortak.h"
using namespace std;

void personelAgacRaporlari(kitap* bas);
void kullaniciAgacRaporlari();
void kitapOduncAlAgacaEkle(kitap* bas, int kitapID);

#endif
