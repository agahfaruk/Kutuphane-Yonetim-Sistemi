#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <cstdlib>
#include <windows.h>
#include <ctime>
#include <algorithm>
#include "../include/agac.h"
#include "../include/ortak.h"
using namespace std;

// Personel için aðaç rapor fonksiyonlarý
void personelAgacRaporlari(kitap* /*bas*/) {
    system("cls");
    int secim;
    do {
        cout << "---KUTUPHANE YONETIM SISTEMI----\n";
        cout << "--------------------------------\n";
        cout << "Personel Menusu - Veri Analizi\n";
        cout << "1 - Odunc suresi 30 gun alti/ustu\n";
        cout << "2 - Odunc alinan kitaplardan basim yili 1950 oncesi/sonrasi\n";
        cout << "3 - Odunc alinan kitaplardan 1950 oncesi ve 30 gunu asanlar\n";
        cout << "0 - Cikis\n";
        cout << "--------------------------------\n";
        cout << "Seciminizi girin: ";
        cin >> secim;
        cin.ignore();

        switch (secim) {
        case 1: {
            // 30 gün altý ve üstü kitaplar
            vector<OduncAgacDugumu*> uzunSureli = oduncAgaci.filtreleOduncSuresi(30);
            vector<OduncAgacDugumu*> normalSureli;

            vector<OduncAgacDugumu*> tumKitaplar = oduncAgaci.tumKitaplar();
            time_t simdi = time(nullptr);

            for (auto kitap : tumKitaplar) {
                double fark = difftime(simdi, kitap->alinmaZamani) / (60 * 60 * 24);
                if (fark <= 30) {
                    normalSureli.push_back(kitap);
                }
            }

            cout << "\n30 GUNU ASAN ODUNC KITAPLAR:\n";
            cout << "------------------------------------------------\n";
            for (auto kitap : uzunSureli) {
                cout << "ID: " << kitap->kitapId << " - " << kitap->kitapAdi << endl;
                cout << "Yazar: " << kitap->yazar << endl;
                cout << "Odunc Alinma: " << ctime(&kitap->alinmaZamani);
                cout << "------------------------------------------------\n";
            }

            cout << "\n30 GUNU ASMAYAN ODUNC KITAPLAR:\n";
            cout << "------------------------------------------------\n";
            for (auto kitap : normalSureli) {
                cout << "ID: " << kitap->kitapId << " - " << kitap->kitapAdi << endl;
                cout << "Yazar: " << kitap->yazar << endl;
                cout << "Odunc Alinma: " << ctime(&kitap->alinmaZamani);
                cout << "------------------------------------------------\n";
            }
            break;
        }
        case 2: {
            // 1950 öncesi ve sonrasý kitaplar
            vector<OduncAgacDugumu*> eskiKitaplar = oduncAgaci.filtreleBasimYili(1950, true);
            vector<OduncAgacDugumu*> yeniKitaplar = oduncAgaci.filtreleBasimYili(1950, false);

            cout << "\n1950 ONCESI BASIMLI KITAPLAR:\n";
            cout << "------------------------------------------------\n";
            for (auto kitap : eskiKitaplar) {
                cout << "ID: " << kitap->kitapId << " - " << kitap->kitapAdi << endl;
                cout << "Yazar: " << kitap->yazar << " | Basim Yili: " << kitap->basimYili << endl;
                cout << "------------------------------------------------\n";
            }

            cout << "\n1950 SONRASI BASIMLI KITAPLAR:\n";
            cout << "------------------------------------------------\n";
            for (auto kitap : yeniKitaplar) {
                cout << "ID: " << kitap->kitapId << " - " << kitap->kitapAdi << endl;
                cout << "Yazar: " << kitap->yazar << " | Basim Yili: " << kitap->basimYili << endl;
                cout << "------------------------------------------------\n";
            }
            break;
        }
        case 3: {
            // 1950 öncesi ve 30 günü aþan kitaplar
            vector<OduncAgacDugumu*> eskiKitaplar = oduncAgaci.filtreleBasimYili(1950, true);
            vector<OduncAgacDugumu*> uzunSureli = oduncAgaci.filtreleOduncSuresi(30);

            // Ýki filtreyi birleþtir
            vector<OduncAgacDugumu*> sonuc;
            for (auto kitap : eskiKitaplar) {
                time_t simdi = time(nullptr);
                double fark = difftime(simdi, kitap->alinmaZamani) / (60 * 60 * 24);
                if (fark > 30) {
                    sonuc.push_back(kitap);
                }
            }

            cout << "\n1950 ONCESI BASIMLI VE 30 GUNU ASAN KITAPLAR:\n";
            cout << "------------------------------------------------\n";
            for (auto kitap : sonuc) {
                cout << "ID: " << kitap->kitapId << " - " << kitap->kitapAdi << endl;
                cout << "Yazar: " << kitap->yazar << " | Basim Yili: " << kitap->basimYili << endl;
                cout << "Odunc Alinma: " << ctime(&kitap->alinmaZamani);
                cout << "------------------------------------------------\n";
            }
            break;
        }
        case 0:
            cout << "Cikis yapiliyor...\n";
            Sleep(500);
            system("cls");
            return;
        default:
            cout << "Gecersiz secim! Tekrar deneyin.\n";
            Sleep(1000);
            system("cls");
        }

        int devam;
        do {
            cout << "\nDevam etmek icin 0'i tuslayin: ";
            cin >> devam;
            if (devam == 0) {
                break;
            }
        } while (devam != 0);
        system("cls");

    } while (secim != 0);
}

// Kullanýcý için aðaç rapor fonksiyonlarý
void kullaniciAgacRaporlari() {
    system("cls");
    int secim;
    do {
        cout << "---KUTUPHANE YONETIM SISTEMI----\n";
        cout << "--------------------------------\n";
        cout << "Kullanici Menusu - Kesfet\n";
        cout << "1 - Odunc alinan kitaplari yayinevine gore filtrele\n";
        cout << "2 - Odunc alinan kitaplari dile gore filtrele\n";
        cout << "3 - Odunc alinan kitaplari sayfa sayisina gore filtrele, 1000'den cok/az \n";
        cout << "0 - Cikis\n";
        cout << "--------------------------------\n";
        cout << "Seciminizi girin: ";
        cin >> secim;
        cin.ignore();

        switch (secim) {
        case 1: {
            // Yayýnevine göre filtrele
            string yayinEvi;
            cout << "Filtrelemek istediginiz yayin evini girin (yerli/yabanci): ";
            getline(cin, yayinEvi);

            vector<OduncAgacDugumu*> sonuc = oduncAgaci.filtreleYayinEvi(yayinEvi);

            cout << "\n" << yayinEvi << " YAYIN EVI KITAPLARI:\n";
            cout << "------------------------------------------------\n";
            for (auto kitap : sonuc) {
                cout << "ID: " << kitap->kitapId << " - " << kitap->kitapAdi << endl;
                cout << "Yazar: " << kitap->yazar << " | Sayfa: " << kitap->sayfaSayisi << endl;
                cout << "------------------------------------------------\n";
            }
            break;
        }
        case 2: {
            // Dile göre filtrele
            string dil;
            cout << "Filtrelemek istediginiz dili girin (Turkce/Ingilizce): ";
            getline(cin, dil);

            vector<OduncAgacDugumu*> sonuc = oduncAgaci.filtreleDil(dil);

            cout << "\n" << dil << " DILI KITAPLARI:\n";
            cout << "------------------------------------------------\n";
            for (auto kitap : sonuc) {
                cout << "ID: " << kitap->kitapId << " - " << kitap->kitapAdi << endl;
                cout << "Yazar: " << kitap->yazar << " | Sayfa: " << kitap->sayfaSayisi << endl;
                cout << "------------------------------------------------\n";
            }
            break;
        }
        case 3: {
            // Sayfa sayýsýna göre filtrele
            vector<OduncAgacDugumu*> azSayfali = oduncAgaci.filtreleSayfaSayisi(0, 1000);
            vector<OduncAgacDugumu*> cokSayfali = oduncAgaci.filtreleSayfaSayisi(1001, 9999);

            cout << "\n1000 SAYFADAN AZ OLAN KITAPLAR:\n";
            cout << "------------------------------------------------\n";
            for (auto kitap : azSayfali) {
                cout << "ID: " << kitap->kitapId << " - " << kitap->kitapAdi << endl;
                cout << "Yazar: " << kitap->yazar << " | Sayfa: " << kitap->sayfaSayisi << endl;
                cout << "------------------------------------------------\n";
            }

            cout << "\n1000 SAYFADAN COK OLAN KITAPLAR:\n";
            cout << "------------------------------------------------\n";
            for (auto kitap : cokSayfali) {
                cout << "ID: " << kitap->kitapId << " - " << kitap->kitapAdi << endl;
                cout << "Yazar: " << kitap->yazar << " | Sayfa: " << kitap->sayfaSayisi << endl;
                cout << "------------------------------------------------\n";
            }
            break;
        }
        case 0:
            cout << "Cikis yapiliyor...\n";
            Sleep(500);
            system("cls");
            return;
        default:
            cout << "Gecersiz secim! Tekrar deneyin.\n";
            Sleep(1000);
            system("cls");
        }

        int devam;
        do {
            cout << "\nDevam etmek icin 0'i tuslayin: ";
            cin >> devam;
            if (devam == 0) {
                break;
            }
        } while (devam != 0);
        system("cls");

    } while (secim != 0);
}

// Kitap ödünç alýndýðýnda aðaca ekleme
void kitapOduncAlAgacaEkle(kitap* bas, int kitapID) {
    kitap* temp = bas;
    while (temp != nullptr) {
        if (temp->id == kitapID) {
            time_t alinmaZamani = time(nullptr);
            oduncAgaci.ekle(temp->id, temp->isim, temp->yazar, temp->sayfaSayisi,
                temp->basimYili, temp->yayinEvi, temp->dil, alinmaZamani);
            break;
        }
        temp = temp->sonraki;
    }
}
