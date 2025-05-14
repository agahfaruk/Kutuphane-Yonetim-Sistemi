#ifndef CIFT_YONLU_DAIRESEL_BAGLI_LISTE_H
#define CIFT_YONLU_DAIRESEL_BAGLI_LISTE_H

#include <string>
#include "ortak.h"
using namespace std;

void kitapYorumEkle(kitapCift* bas);
void kitapYorumlariListele(kitapCift* bas);
void koleksiyonOlustur();
void koleksiyonaKitapEkle(kitapCift* bas);
void okunmaDurumuGuncelle();
void koleksiyondanKitapSil();
void koleksiyonuListele();

#endif
