#include <iostream>
#include <queue>
#include <cstdlib>
#include <windows.h>
#include <ctime>
#include <algorithm>
#include <map>
#include <string>
#include "../include/tek_yonlu_bagli_liste.h"
#include "../include/kuyruk.h"
#include "../include/ortak.h"
using namespace std;

// Personel için talep yönetimi fonksiyonu
void talepYonetimi(kitap*& bas) {
    system("cls");
    int personelSecim;
    do {
        cout << "---KUTUPHANE YONETIM SISTEMI----\n";
        cout << "--------------------------------\n";
        cout << "Personel Menusu - Talep Yonetimi\n";
        cout << "1 - Talep Listesini Goster ve Kitap Ekle\n";
        cout << "0 - Cikis\n";
        cout << "--------------------------------\n";
        cout << "Seciminizi girin: ";
        cin >> personelSecim;
        cin.ignore();

        if (personelSecim == 1) {

            // Talep listesini göster
            if (talepKuyrugu.empty()) {
                cout << "Talep bulunmamaktadir.\n";
                Sleep(1000);
                system("cls");
                continue;
            }

            cout << "\nTALEP LISTESI:\n";
            cout << "------------------------------------------------\n";

            queue<Talep> tempKuyruk = talepKuyrugu;
            while (!tempKuyruk.empty()) {
                Talep t = tempKuyruk.front();
                tempKuyruk.pop();
                cout << "Talep ID: " << t.talepId << " | ";
                cout << "Kitap: " << t.kitapAdi << " - " << t.yazar << " | ";
                cout << "Tur: " << (t.akademik ? "AKADEMIK" : "Normal") << endl;
                cout << "------------------------------------------------\n";
            }

            // Talep ID'si girilmesini iste
            int girilenTalepId;
            cout << "\nEklemek istediginiz kitabin Talep ID'sini girin (0 - Iptal): ";
            cin >> girilenTalepId;
            cin.ignore();

            if (girilenTalepId == 0) {
                system("cls");
                continue;
            }

            // Kuyrukta arama yap
            bool talepBulundu = false;
            Talep bulunanTalep;
            queue<Talep> guncelKuyruk;

            while (!talepKuyrugu.empty()) {
                Talep mevcut = talepKuyrugu.front();
                talepKuyrugu.pop();

                if (mevcut.talepId == girilenTalepId) {
                    talepBulundu = true;
                    bulunanTalep = mevcut;
                    while (!talepKuyrugu.empty()) {
                        guncelKuyruk.push(talepKuyrugu.front());
                        talepKuyrugu.pop();
                    }
                    break;
                }
                else {
                    guncelKuyruk.push(mevcut);
                }
            }

            talepKuyrugu = guncelKuyruk;

            if (talepBulundu) {
                // Yeni bilgileri al
                int sayfaSayisi, basimYili;
                string yayinEvi, dil, kategori;

                cout << "\nKitap bilgilerini giriniz:\n";
                cout << "Sayfa Sayisi: ";
                cin >> sayfaSayisi;
                cin.ignore();

                cout << "Basim Yili: ";
                cin >> basimYili;
                cin.ignore();

                cout << "Yayin Evi (yerli/yabanci): ";
                getline(cin, yayinEvi);

                cout << "Dil (Turkce/Ingilizce): ";
                getline(cin, dil);

                cout << "Kategori: ";
                getline(cin, kategori);

                // Kitabý kütüphaneye ekle
                int yeniKitapId = 2000 + talepIdSayac++;
                kitapEkle(bas, yeniKitapId, bulunanTalep.kitapAdi, bulunanTalep.yazar,
                    sayfaSayisi, basimYili, yayinEvi, dil, kategori);

                cout << "\nKitap basariyla eklendi:\n";
                cout << "Yeni Kitap ID: " << yeniKitapId << endl;
                cout << "Kitap Adi: " << bulunanTalep.kitapAdi << endl;
                cout << "Yazar: " << bulunanTalep.yazar << endl;
                cout << "Sayfa Sayisi: " << sayfaSayisi << endl;
                cout << "Basim Yili: " << basimYili << endl;
                cout << "Yayin Evi: " << yayinEvi << endl;
                cout << "Dil: " << dil << endl;
                cout << "Kategori: " << kategori << endl;
                cout << "Tur: " << (bulunanTalep.akademik ? "AKADEMIK" : "Normal") << endl;
            }
            else {
                cout << "Hata: Belirtilen Talep ID bulunamadi!\n";
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

        }
        else if (personelSecim == 0) {
            cout << "Cikis yapiliyor...\n";
            Sleep(500);
            system("cls");
        }
        else {
            cout << "Gecersiz secim! Tekrar deneyin.\n";
            Sleep(1000);
            system("cls");
        }

    } while (personelSecim != 0);
}

//Kullanýcý için
// Talep ekleme fonksiyonu
void talepEkle() {
    Talep yeniTalep;
    yeniTalep.talepId = talepIdSayac++;

    cout << "Talep edilen kitabin adini girin: ";
    getline(cin, yeniTalep.kitapAdi);

    cout << "Kitabin yazarini girin: ";
    getline(cin, yeniTalep.yazar);

    yeniTalep.akademik = false;
    yeniTalep.talepZamani = time(nullptr);

    talepKuyrugu.push(yeniTalep);
    cout << "\nTalep basariyla eklendi. Talep ID: " << yeniTalep.talepId << endl;
}

// Akademik talep ekleme fonksiyonu
void akademikTalepEkle() {
    Talep yeniTalep;
    yeniTalep.talepId = talepIdSayac++;

    cout << "Talep edilen kitabin adini girin: ";
    getline(cin, yeniTalep.kitapAdi);

    cout << "Kitabin yazarini girin: ";
    getline(cin, yeniTalep.yazar);

    yeniTalep.akademik = true;
    yeniTalep.talepZamani = time(nullptr);

    // Akademik talepleri öncelikli olarak kuyruðun baþýna eklemek için
    // Önce tüm akademik talepleri bir geçici kuyruða al
    queue<Talep> akademikTalepler;
    queue<Talep> normalTalepler;

    // Mevcut kuyruðu ayýr
    while (!talepKuyrugu.empty()) {
        Talep mevcut = talepKuyrugu.front();
        talepKuyrugu.pop();
        if (mevcut.akademik) {
            akademikTalepler.push(mevcut);
        }
        else {
            normalTalepler.push(mevcut);
        }
    }

    // Önce yeni akademik talebi ekle
    akademikTalepler.push(yeniTalep);
    cout << "\nAKADEMIK TALEP basariyla eklendi. Talep ID: " << yeniTalep.talepId << endl;

    // Sonra diðer akademik talepleri ekle
    while (!akademikTalepler.empty()) {
        talepKuyrugu.push(akademikTalepler.front());
        akademikTalepler.pop();
    }

    // En son normal talepleri ekle
    while (!normalTalepler.empty()) {
        talepKuyrugu.push(normalTalepler.front());
        normalTalepler.pop();
    }

    // Kuyruðu göster
    cout << "\nGuncel Talep Kuyrugu:\n";
    queue<Talep> gosterKuyruk = talepKuyrugu;
    while (!gosterKuyruk.empty()) {
        Talep t = gosterKuyruk.front();
        gosterKuyruk.pop();
        cout << "ID: " << t.talepId << " - " << t.kitapAdi << " (" << t.yazar << ") - "
            << (t.akademik ? "AKADEMIK" : "Normal") << endl;
    }
}

// Talepleri listeleme fonksiyonu
void talepleriListele() {
    if (talepKuyrugu.empty()) {
        cout << "Talep bulunmamaktadir.\n";
        return;
    }

    cout << "\nTALEP LISTESI (Ilk talep edilen ilk tedarik edilecek)\n";
    cout << "------------------------------------------------\n";

    queue<Talep> tempKuyruk = talepKuyrugu;
    while (!tempKuyruk.empty()) {
        Talep t = tempKuyruk.front();
        tempKuyruk.pop();

        cout << "Talep ID: " << t.talepId << endl;
        cout << "Kitap: " << t.kitapAdi << " - " << t.yazar << endl;
        cout << "Tur: " << (t.akademik ? "AKADEMIK" : "Normal") << endl;

        char tarih[80];
        struct tm* timeinfo = localtime(&t.talepZamani);
        strftime(tarih, sizeof(tarih), "%d.%m.%Y %H:%M:%S", timeinfo);
        cout << "Talep Zamani: " << tarih << endl;
        cout << "------------------------------------------------\n";
    }
}
