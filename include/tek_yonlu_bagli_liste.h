#ifndef TEK_YONLU_BAGLI_LISTE_H
#define TEK_YONLU_BAGLI_LISTE_H

#include <string>
#include "ortak.h"
using namespace std;

void kitapEkle(kitap*& bas, int id, string isim, string yazar, int sayfaSayisi,
    int basimYili, string yayinEvi, string dil, string kategori,
    bool hasarli = false, string hasarNotu = "");
void kitapHasarNotuEkle(kitap* bas);
void hasarliKitaplariListele(kitap* bas);
void kitapDuzenle(kitap* bas);
void kitapSilId(kitap*& bas, kitapCift*& bas2);
void kitapIdListele(kitap* bas);
void toplamKitapSayisi(kitap* bas);
void idyeGoreSirala(kitap*& bas);
void sayfaSayisinaGoreSirala(kitap*& bas);
void basimYilinaGoreSirala(kitap*& bas);
void basimYilinaGoreListele(kitap* bas);
void kitapListele(kitap* bas);

#endif
