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
#include "../include/hash.h"
#include "../include/ortak.h"
using namespace std;

// Personel için hash fonksiyonlarý
void personelHashIslemleri() {
    system("cls");
    int secim;
    do {
        cout << "---KUTUPHANE YONETIM SISTEMI----\n";
        cout << "--------------------------------\n";
        cout << "Personel Menusu - Degerlendirme Sistemi\n";
        cout << "1 - Yuksek puanli kitaplari listele\n";
        cout << "0 - Cikis\n";
        cout << "--------------------------------\n";
        cout << "Seciminizi girin: ";
        cin >> secim;
        cin.ignore();

        if (secim == 1) {
            cout << "\n4 VE UZERI PUAN ALAN KITAPLAR:\n";
            cout << "--------------------------------\n";

            bool bulundu = false;
            for (const auto& pair : kitapPuanlari) {
                const KitapPuan& kp = pair.second;
                if (kp.ortalamaPuan >= 4.0) {
                    cout << "ID: " << kp.kitapId << " - " << kp.kitapAdi << endl;
                    cout << "Kategori: " << kp.kategori << " | Puan: " << fixed << setprecision(1) << kp.ortalamaPuan << endl;
                    cout << "--------------------------------\n";
                    bulundu = true;
                }
            }

            if (!bulundu) {
                cout << "4 ve uzeri puan alan kitap bulunamadi.\n";
            }

            int devam;
            do {
                cout << "\nDevam etmek icin 0'i tuslayin: ";
                cin >> devam;
                if (devam == 0) break;
            } while (devam != 0);
            Sleep(200);
            system("cls");
        }
        else if (secim == 0) {
            cout << "Cikis yapiliyor...\n";
            Sleep(500);
            system("cls");
            return;
        }
        else {
            cout << "Gecersiz secim! Tekrar deneyin.\n";
            Sleep(1000);
            system("cls");
        }
    } while (secim != 0);
}

// Kitap puanlama fonksiyonu
void kitapPuanla(kitap* bas) {
    if (kullaniciOduncKitaplar.empty()) {
        cout << "Odunc alinmis kitap yok!\n";
        return;
    }

    int kitapID;
    cout << "Puanlamak istediginiz kitap ID: ";
    cin >> kitapID;

    // Kitabýn ödünç alýnýp alýnmadýðýný kontrol et
    stack<int> tempStack = kullaniciOduncKitaplar;
    bool oduncAlinmis = false;
    while (!tempStack.empty()) {
        if (tempStack.top() == kitapID) {
            oduncAlinmis = true;
            break;
        }
        tempStack.pop();
    }

    if (!oduncAlinmis) {
        cout << "Bu kitabi odunc almamissiniz!\n";
        return;
    }

    // Kitap bilgilerini bul
    kitap* k = bas;
    while (k != nullptr && k->id != kitapID) {
        k = k->sonraki;
    }

    if (k != nullptr) {
        int puan;
        do {
            cout << "Kitaba vereceginiz puan (1-5): ";
            cin >> puan;
            if (puan < 1 || puan > 5) {
                cout << "Gecersiz puan! 1-5 arasi deger girin.\n";
            }
        } while (puan < 1 || puan > 5);

        // Hash tablosuna ekle/güncelle
        if (kitapPuanlari.find(kitapID) == kitapPuanlari.end()) {
            KitapPuan kp;
            kp.kitapId = kitapID;
            kp.kitapAdi = k->isim;
            kp.kategori = k->kategori;
            kp.puanlar.push_back(puan);
            kp.ortalamaPuan = puan;
            kitapPuanlari[kitapID] = kp;

            // Kategori hash'ine ekle
            kategoriKitaplari[k->kategori].push_back(kitapID);
        }
        else {
            kitapPuanlari[kitapID].puanlar.push_back(puan);
            // Ortalamayý yeniden hesapla
            double toplam = 0;
            for (int p : kitapPuanlari[kitapID].puanlar) {
                toplam += p;
            }
            kitapPuanlari[kitapID].ortalamaPuan = toplam / kitapPuanlari[kitapID].puanlar.size();
        }

        cout << "Puanlama basariyla kaydedildi!\n";
    }
    else {
        cout << "Kitap bulunamadi!\n";
    }
}

// Kitap önerme fonksiyonu
void kitapOner(kitap* bas) {
    if (kullaniciOduncKitaplar.empty()) {
        cout << "Odunc alinmis kitap yok! Once kitap odunc almalisiniz.\n";
        return;
    }

    // Kullanýcýnýn ödünç aldýðý tüm kategorileri topla
    unordered_set<string> kategoriler;
    stack<int> tempStack = kullaniciOduncKitaplar;

    while (!tempStack.empty()) {
        int kitapID = tempStack.top();
        tempStack.pop();

        kitap* k = bas;
        while (k != nullptr && k->id != kitapID) {
            k = k->sonraki;
        }

        if (k != nullptr) {
            kategoriler.insert(k->kategori);
        }
    }

    cout << "\nODUNC ALDIGINIZ KITAPLARIN KATEGORILERINDEN ONERILER:\n";
    cout << "------------------------------------------------\n";

    // Tüm kategorilerdeki kitaplarý listele (ödünç alýnanlar hariç)
    bool oneriBulundu = false;

    // unordered_set üzerinde döngü için iterator kullanýmý
    for (unordered_set<string>::iterator it = kategoriler.begin(); it != kategoriler.end(); ++it) {
        string kategori = *it;
        cout << "\n" << kategori << " KATEGORISI:\n";
        cout << "------------------------------------------------\n";

        kitap* temp = bas;
        while (temp != nullptr) {
            // Ayný kategoride ve ödünç alýnmamýþ kitaplarý listele
            if (temp->kategori == kategori) {
                bool oduncAlinmis = false;

                // Kitabýn ödünç alýnýp alýnmadýðýný kontrol et
                if (oduncListesiBas != nullptr) {
                    OduncKitap* kontrol = oduncListesiBas;
                    do {
                        if (kontrol->kitapId == temp->id && kontrol->iadeZamani == 0) {
                            oduncAlinmis = true;
                            break;
                        }
                        kontrol = kontrol->sonraki;
                    } while (kontrol != oduncListesiBas);
                }

                // Kullanýcýnýn zaten ödünç aldýðý kitaplarý önerme
                stack<int> kullaniciKitaplar = kullaniciOduncKitaplar;
                while (!kullaniciKitaplar.empty()) {
                    if (kullaniciKitaplar.top() == temp->id) {
                        oduncAlinmis = true;
                        break;
                    }
                    kullaniciKitaplar.pop();
                }

                if (!oduncAlinmis) {
                    cout << "ID: " << temp->id << " - " << temp->isim << " (" << temp->yazar << ")\n";
                    cout << "Sayfa: " << temp->sayfaSayisi << " | Basim Yili: " << temp->basimYili << endl;
                    cout << "Durum: " << (temp->hasarli ? "Hasarli - Odunc Alinamaz" : "Uygun - Odunc Alinabilir") << endl;

                    // Kitap puaný varsa göster
                    if (kitapPuanlari.find(temp->id) != kitapPuanlari.end()) {
                        cout << "Puan: " << fixed << setprecision(1) << kitapPuanlari[temp->id].ortalamaPuan << "/5.0" << endl;
                    }
                    cout << "------------------------------------------------\n";
                    oneriBulundu = true;
                }
            }
            temp = temp->sonraki;
        }
    }

    if (!oneriBulundu) {
        cout << "Bu kategorilerde onerilebilecek yeni kitap bulunamadi.\n";
    }

    int devam;
    do {
        cout << "\nDevam etmek icin 0'i tuslayin: ";
        cin >> devam;
        if (devam == 0) break;
    } while (devam != 0);
}

// Kullanýcý için hash fonksiyonlarý
void kullaniciHashIslemleri(kitap* bas) {
    system("cls");
    int secim;
    do {
        cout << "---KUTUPHANE YONETIM SISTEMI----\n";
        cout << "--------------------------------\n";
        cout << "Kullanici Menusu - Degerlendirme\n";
        cout << "1 - Kitap onerilerini listele\n";
        cout << "2 - Kitap puanla\n";
        cout << "0 - Cikis\n";
        cout << "--------------------------------\n";
        cout << "Seciminizi girin: ";
        cin >> secim;
        cin.ignore();

        if (secim == 1) {
            kitapOner(bas);
            Sleep(1000);
            system("cls");
        }
        else if (secim == 2) {
            kitapPuanla(bas);
            Sleep(1000);
            system("cls");
        }
        else if (secim == 0) {
            cout << "Cikis yapiliyor...\n";
            Sleep(500);
            system("cls");
            return;
        }
        else {
            cout << "Gecersiz secim! Tekrar deneyin.\n";
            Sleep(1000);
            system("cls");
        }
    } while (secim != 0);
}
