#include <iostream>
#include <stack>
#include "../include/yigin.h"
#include "../include/ortak.h"
using namespace std;

// Kullanýcý için ödünç alma fonksiyonu
void kitapOduncAl(kitap* bas) {
    if (bas == nullptr) {
        cout << "Kutuphane bos!\n";
        return;
    }

    int kitapID;
    cout << "Odunc almak istediginiz kitap ID: ";
    cin >> kitapID;

    kitap* temp = bas;
    while (temp != nullptr && temp->id != kitapID) {
        temp = temp->sonraki;
    }

    if (temp != nullptr) {
        kullaniciOduncKitaplar.push(kitapID);
        time_t alinmaZamani = time(nullptr);
        oduncListesiBas = oduncListesineEkle(oduncListesiBas, kitapID, alinmaZamani);
        oduncAgaci.ekle(temp->id, temp->isim, temp->yazar, temp->sayfaSayisi,
            temp->basimYili, temp->yayinEvi, temp->dil, alinmaZamani);

        cout << "\nODUNC ALINDI: " << temp->isim << endl;
        cout << "Alinma Zamani: " << ctime(&alinmaZamani);
    }
    else {
        cout << "Kitap bulunamadi!\n";
    }
}

// Kullanýcý için iade fonksiyonu
void kitapIadeEt(kitap* bas) {
    if (kullaniciOduncKitaplar.empty()) {
        cout << "Odunc alinmis kitap yok!\n";
        return;
    }

    // Stack'i ters çevirerek en alttaki (ilk eklenen) kitabý bul
    stack<int> tempStack;
    while (kullaniciOduncKitaplar.size() > 1) {
        tempStack.push(kullaniciOduncKitaplar.top());
        kullaniciOduncKitaplar.pop();
    }

    int kitapID = kullaniciOduncKitaplar.top(); // En alttaki kitap
    kullaniciOduncKitaplar.pop();

    // Diðer kitaplarý geri yükle
    while (!tempStack.empty()) {
        kullaniciOduncKitaplar.push(tempStack.top());
        tempStack.pop();
    }

    // Ýade iþlemleri
    time_t iadeZamani = time(nullptr);

    // Kullanýcýnýn iade listesine ekle
    kullaniciIadeKitaplar.push({ kitapID, iadeZamani });

    // Personel listelerini güncelle
    if (oduncListesiBas != nullptr) {
        OduncKitap* temp = oduncListesiBas;
        bool bulundu = false;

        do {
            if (temp->kitapId == kitapID && temp->iadeZamani == 0) {
                temp->iadeZamani = iadeZamani;
                iadeListesiBas = iadeListesineEkle(iadeListesiBas, kitapID, iadeZamani);
                bulundu = true;
                break;
            }
            temp = temp->sonraki;
        } while (temp != oduncListesiBas && !bulundu);
    }

    // Kitap bilgilerini göster
    kitap* temp = bas;
    while (temp != nullptr && temp->id != kitapID) {
        temp = temp->sonraki;
    }

    if (temp != nullptr) {
        cout << "\nIADE EDILDI: " << temp->isim << endl;
        cout << "Iade Zamani: " << ctime(&iadeZamani);
    }
}

// Ödünç listeleme fonksiyonu
void oduncAlinanlariListele(kitap* bas) {
    if (kullaniciOduncKitaplar.empty()) {
        cout << "\nOdunc alinan kitap yok.\n";
        return;
    }

    cout << "\nODUNC ALINAN KITAPLAR (EN SON ALINAN EN USTTE)\n";
    cout << "---------------------------------------------\n";

    // Stack'in kopyasýný al (orijinal bozulmasýn)
    stack<int> tempStack = kullaniciOduncKitaplar;

    // Stack'ten direkt okuyarak listele (en son eklenen en üstte)
    while (!tempStack.empty()) {
        int kitapID = tempStack.top();
        kitap* temp = bas;

        // Kitap bilgilerini bul
        while (temp != nullptr && temp->id != kitapID) {
            temp = temp->sonraki;
        }

        if (temp != nullptr) {
            cout << temp->isim << " (" << temp->yazar << ")\n";
            cout << "ID: " << temp->id << "\n";
            cout << "---------------------------------------------\n";
        }
        tempStack.pop(); // Sadece geçici stack'ten pop yapýlýyor
    }
}

// Ýade listeleme fonksiyonu
void iadeEdilenleriListele(kitap* bas) {
    if (kullaniciIadeKitaplar.empty()) {
        cout << "\nHenuz iade edilen kitap yok.\n";
        return;
    }

    cout << "\nIADE EDILEN KITAPLAR (EN YENIDEN ESKIYE)\n";
    cout << "---------------------------------------------\n";

    auto tempStack = kullaniciIadeKitaplar;

    while (!tempStack.empty()) {
        auto kitapBilgisi = tempStack.top();
        kitap* temp = bas;

        while (temp != nullptr && temp->id != kitapBilgisi.first) {
            temp = temp->sonraki;
        }

        if (temp != nullptr) {
            cout << temp->isim << " (" << temp->yazar << ")\n";

            // Tarihi formatla
            char tarih[80];
            struct tm* timeinfo = localtime(&kitapBilgisi.second);
            strftime(tarih, sizeof(tarih), "%a %b %d %H:%M:%S %Y", timeinfo);
            cout << "   Zaman   " << tarih << endl;
            cout << "---------------------------------------------\n";
        }

        tempStack.pop();
    }
}
