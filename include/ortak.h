#ifndef ORTAK_H
#define ORTAK_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <cstdlib>
#include <windows.h>
#include <stack>
#include <queue>
#include <unordered_map>
#include <unordered_set> 
#include <ctime>
#include <algorithm>
using namespace std;

// Kitap yap�s�
struct kitap {
    int id;
    string isim;
    string yazar;
    int sayfaSayisi;
    int basimYili;
    string yayinEvi;
    string dil;
    string kategori;
    string hasarNotu;
    bool hasarli;
    kitap* sonraki;
    // Parametreli constructor
    kitap(int _id, string _isim, string _yazar, int _sayfaSayisi, int _basimYili, string _yayinEvi, string _dil, string _kategori, string _hasarNotu, bool _hasarli, kitap* _sonraki = nullptr)
        : id(_id), isim(_isim), yazar(_yazar), sayfaSayisi(_sayfaSayisi), basimYili(_basimYili), yayinEvi(_yayinEvi), dil(_dil), kategori(_kategori), hasarNotu(_hasarNotu), hasarli(_hasarli), sonraki(_sonraki) {}

    // Default constructor
    kitap() : sonraki(nullptr) {}
};

// Kullan�c� k�sm�
struct kitapCift {
    int id;
    string isim;
    string yazar;
    int sayfaSayisi;
    int basimYili;
    string yayinEvi;
    string dil;
    string kategori;
    bool okundu;
    vector<string> yorumlar;
    kitapCift* sonraki;
    kitapCift* onceki; // �ift y�nl� liste yap�s� olu�turmak i�in
};

// Kullan�c� koleksiyonu
struct KoleksiyonDugumu {
    kitapCift* kitapPtr;
    KoleksiyonDugumu* sonraki;
    KoleksiyonDugumu* onceki;
};

// Koleksiyon yap�s�
struct Koleksiyon {
    kitapCift* bas;
    bool olusturuldu;

    Koleksiyon() : bas(nullptr), olusturuldu(false) {}

    ~Koleksiyon() {
        if (!bas) return;

        kitapCift* temp = bas->sonraki;
        while (temp != bas) {
            kitapCift* silinecek = temp;
            temp = temp->sonraki;
            delete silinecek;
        }
        delete bas;
    }
};

// Talep yap�s�
struct Talep {
    int talepId;
    string kitapAdi;
    string yazar;
    bool akademik; // Akademik talep mi?
    time_t talepZamani;
};

// Kitap puan yap�s�
struct KitapPuan {
    int kitapId;
    string kitapAdi;
    string kategori;
    double ortalamaPuan;
    vector<int> puanlar;
};

// �d�n� ve iade i�lemleri i�in yeni yap�lar
struct OduncKitap {
    int kitapId;
    time_t alinmaZamani;
    time_t iadeZamani;
    OduncKitap* sonraki;
};

struct IadeKitap {
    int kitapId;
    time_t iadeZamani;
    IadeKitap* sonraki;
};

// A�a� d���m yap�s� (�d�n� al�nan kitaplar i�in)
struct OduncAgacDugumu {
    int kitapId;
    string kitapAdi;
    string yazar;
    int sayfaSayisi;
    int basimYili;
    string yayinEvi;
    string dil;
    time_t alinmaZamani;
    time_t iadeZamani;
    OduncAgacDugumu* sol;
    OduncAgacDugumu* sag;

    OduncAgacDugumu(int id, string ad, string yzr, int sayfa, int yil, string yEv, string dl, time_t alinma)
        : kitapId(id), kitapAdi(ad), yazar(yzr), sayfaSayisi(sayfa), basimYili(yil),
        yayinEvi(yEv), dil(dl), alinmaZamani(alinma), iadeZamani(0), sol(nullptr), sag(nullptr) {}
};

// A�a� s�n�f�
class OduncAgaci {
private:
    OduncAgacDugumu* kok;

    // Yard�mc� fonksiyonlar
    void temizle(OduncAgacDugumu* dugum) {
        if (dugum) {
            temizle(dugum->sol);
            temizle(dugum->sag);
            delete dugum;
        }
    }

    OduncAgacDugumu* ekle(OduncAgacDugumu* dugum, int id, string ad, string yzr, int sayfa, int yil,
        string yEv, string dl, time_t alinma) {
        if (!dugum) {
            return new OduncAgacDugumu(id, ad, yzr, sayfa, yil, yEv, dl, alinma);
        }

        if (id < dugum->kitapId) {
            dugum->sol = ekle(dugum->sol, id, ad, yzr, sayfa, yil, yEv, dl, alinma);
        }
        else if (id > dugum->kitapId) {
            dugum->sag = ekle(dugum->sag, id, ad, yzr, sayfa, yil, yEv, dl, alinma);
        }

        return dugum;
    }

    void inorder(OduncAgacDugumu* dugum, vector<OduncAgacDugumu*>& sonuc) {
        if (dugum) {
            inorder(dugum->sol, sonuc);
            sonuc.push_back(dugum);
            inorder(dugum->sag, sonuc);
        }
    }

public:
    OduncAgaci() : kok(nullptr) {}
    ~OduncAgaci() { temizle(kok); }

    void ekle(int id, string ad, string yzr, int sayfa, int yil, string yEv, string dl, time_t alinma) {
        kok = ekle(kok, id, ad, yzr, sayfa, yil, yEv, dl, alinma);
    }

    vector<OduncAgacDugumu*> tumKitaplar() {
        vector<OduncAgacDugumu*> sonuc;
        inorder(kok, sonuc);
        return sonuc;
    }

    vector<OduncAgacDugumu*> filtreleYayinEvi(string yayinEvi) {
        vector<OduncAgacDugumu*> sonuc;
        vector<OduncAgacDugumu*> kitaplar = tumKitaplar();

        for (auto kitap : kitaplar) {
            if (kitap->yayinEvi == yayinEvi) {
                sonuc.push_back(kitap);
            }
        }

        return sonuc;
    }

    vector<OduncAgacDugumu*> filtreleDil(string dil) {
        vector<OduncAgacDugumu*> sonuc;
        vector<OduncAgacDugumu*> kitaplar = tumKitaplar();

        for (auto kitap : kitaplar) {
            if (kitap->dil == dil) {
                sonuc.push_back(kitap);
            }
        }

        return sonuc;
    }

    vector<OduncAgacDugumu*> filtreleSayfaSayisi(int min, int max) {
        vector<OduncAgacDugumu*> sonuc;
        vector<OduncAgacDugumu*> kitaplar = tumKitaplar();

        for (auto kitap : kitaplar) {
            if (kitap->sayfaSayisi >= min && kitap->sayfaSayisi <= max) {
                sonuc.push_back(kitap);
            }
        }

        return sonuc;
    }

    vector<OduncAgacDugumu*> filtreleBasimYili(int yil, bool onceMi) {
        vector<OduncAgacDugumu*> sonuc;
        vector<OduncAgacDugumu*> kitaplar = tumKitaplar();

        for (auto kitap : kitaplar) {
            if ((onceMi && kitap->basimYili < yil) || (!onceMi && kitap->basimYili >= yil)) {
                sonuc.push_back(kitap);
            }
        }

        return sonuc;
    }

    vector<OduncAgacDugumu*> filtreleOduncSuresi(int gun) {
        vector<OduncAgacDugumu*> sonuc;
        vector<OduncAgacDugumu*> kitaplar = tumKitaplar();
        time_t simdi = time(nullptr);

        for (auto kitap : kitaplar) {
            double fark = difftime(simdi, kitap->alinmaZamani) / (60 * 60 * 24);
            if (fark > gun) {
                sonuc.push_back(kitap);
            }
        }

        return sonuc;
    }
};

// ortak.h
extern kitapCift* tekYonludenCiftYonluDairesele(kitap* bas);

extern unordered_map<int, KitapPuan> kitapPuanlari;
extern unordered_map<string, vector<int>> kategoriKitaplari;
extern Koleksiyon kullaniciKoleksiyonu;
extern queue<Talep> talepKuyrugu;
extern stack<int> kullaniciOduncKitaplar; // Kullan�c� taraf� i�in y���n (�d�n�)
extern OduncKitap* oduncListesiBas; // Personel taraf� i�in dairesel liste
extern IadeKitap* iadeListesiBas; // Personel taraf� i�in dairesel liste
extern stack<pair<int, time_t>> kullaniciIadeKitaplar; //Kullan�c� taraf� i�in y���n (iade)
extern OduncAgaci oduncAgaci; // a�a�

extern int talepIdSayac;

extern OduncKitap* oduncListesineEkle(OduncKitap* son, int kitapId, time_t alinmaZamani);

extern IadeKitap* iadeListesineEkle(IadeKitap* son, int kitapId, time_t iadeZamani);


#endif
