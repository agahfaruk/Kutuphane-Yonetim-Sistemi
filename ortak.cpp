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
#include "../include/ortak.h"
using namespace std;

// Tek y�nl� listedekileri �ift y�nl� listeye �ekme fonksiyonu
kitapCift* tekYonludenCiftYonluDairesele(kitap* bas) {
    if (bas == nullptr) {
        return nullptr;
    }

    kitapCift* yeniBaslangic = nullptr;
    kitapCift* son = nullptr;
    kitap* gecici = bas;

    while (gecici != nullptr) {
        // Koleksiyonda bu kitap var m� kontrol et
        bool koleksiyondaVar = false;
        kitapCift* koleksiyonKitap = nullptr;

        if (kullaniciKoleksiyonu.bas != nullptr) {
            koleksiyonKitap = kullaniciKoleksiyonu.bas;
            do {
                if (koleksiyonKitap->id == gecici->id) {
                    koleksiyondaVar = true;
                    break;
                }
                koleksiyonKitap = koleksiyonKitap->sonraki;
            } while (koleksiyonKitap != kullaniciKoleksiyonu.bas);
        }

        kitapCift* yeniDugum;
        if (koleksiyondaVar) {
            // Koleksiyondaki kopyay� kullan
            yeniDugum = new kitapCift(*koleksiyonKitap);
        }
        else {
            // Yeni bir kitap olu�tur
            yeniDugum = new kitapCift;
            yeniDugum->id = gecici->id;
            yeniDugum->isim = gecici->isim;
            yeniDugum->yazar = gecici->yazar;
            yeniDugum->sayfaSayisi = gecici->sayfaSayisi;
            yeniDugum->basimYili = gecici->basimYili;
            yeniDugum->yayinEvi = gecici->yayinEvi;
            yeniDugum->dil = gecici->dil;
            yeniDugum->kategori = gecici->kategori;
            yeniDugum->okundu = false;
            yeniDugum->yorumlar = {};
        }

        // Liste ba�lant�lar�
        if (yeniBaslangic == nullptr) {
            yeniBaslangic = yeniDugum;
            son = yeniDugum;
            yeniDugum->sonraki = yeniDugum;
            yeniDugum->onceki = yeniDugum;
        }
        else {
            yeniDugum->onceki = son;
            yeniDugum->sonraki = yeniBaslangic;
            son->sonraki = yeniDugum;
            yeniBaslangic->onceki = yeniDugum;
            son = yeniDugum;
        }

        gecici = gecici->sonraki;
    }

    return yeniBaslangic;
}

unordered_map<int, KitapPuan> kitapPuanlari;
unordered_map<string, vector<int>> kategoriKitaplari;
Koleksiyon kullaniciKoleksiyonu;
queue<Talep> talepKuyrugu;
stack<int> kullaniciOduncKitaplar; // Kullan�c� taraf� i�in y���n (�d�n�)
OduncKitap* oduncListesiBas = nullptr; // Personel taraf� i�in dairesel liste
IadeKitap* iadeListesiBas = nullptr; // Personel taraf� i�in dairesel liste
stack<pair<int, time_t>> kullaniciIadeKitaplar; //Kullan�c� taraf� i�in y���n (iade)
OduncAgaci oduncAgaci; // a�a�

int talepIdSayac = 1;

// Dairesel listeye ekleme fonksiyonlar�
OduncKitap* oduncListesineEkle(OduncKitap* son, int kitapId, time_t alinmaZamani) {
    OduncKitap* yeni = new OduncKitap{ kitapId, alinmaZamani, 0, nullptr };

    if (son == nullptr) {
        yeni->sonraki = yeni;
        return yeni;
    }
    else {
        yeni->sonraki = son->sonraki;
        son->sonraki = yeni;
        return yeni;
    }
}

IadeKitap* iadeListesineEkle(IadeKitap* son, int kitapId, time_t iadeZamani) {
    IadeKitap* yeni = new IadeKitap{ kitapId, iadeZamani, nullptr };

    if (son == nullptr) {
        yeni->sonraki = yeni;
        return yeni;
    }
    else {
        yeni->sonraki = son->sonraki;
        son->sonraki = yeni;
        return yeni;
    }
}