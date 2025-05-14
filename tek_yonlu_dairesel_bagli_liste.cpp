#include <iostream>
#include "../include/tek_yonlu_dairesel_bagli_liste.h"
#include "../include/ortak.h"
using namespace std;

// Personel için rapor fonksiyonlarý
void oduncRaporuGoster(kitap* bas) {
    if (oduncListesiBas == nullptr) {
        cout << "Odunc alinmis kitap yok!\n";
        return;
    }

    cout << "\nODUNC ALINAN KITAPLAR RAPORU (EN SON ALINAN EN USTTE)\n";
    cout << "-----------------------------------------\n";

    // Önce tüm ödünç kayýtlarýný bir vektöre alalým
    vector<OduncKitap*> kayitlar;
    OduncKitap* temp = oduncListesiBas;
    do {
        kayitlar.push_back(temp);
        temp = temp->sonraki;
    } while (temp != oduncListesiBas);

    // Kayýtlarý alýnma zamanýna göre ters sýrala (en yeni en üstte)
    sort(kayitlar.begin(), kayitlar.end(), [](OduncKitap* a, OduncKitap* b) {
        return a->alinmaZamani > b->alinmaZamani;
        });

    // Sýralanmýþ kayýtlarý listele
    for (auto kayit : kayitlar) {
        kitap* ktp = bas;
        while (ktp != nullptr && ktp->id != kayit->kitapId) {
            ktp = ktp->sonraki;
        }

        if (ktp != nullptr) {
            cout << "ID: " << kayit->kitapId << " - " << ktp->isim << endl;
            cout << "Alinma Zamani: " << ctime(&kayit->alinmaZamani);
            if (kayit->iadeZamani != 0) {
                cout << "Iade Zamani: " << ctime(&kayit->iadeZamani);
            }
            else {
                cout << "Durum: Odunc Alinmis\n";
            }
            cout << "-----------------------------------------\n";
        }
    }
}

void iadeRaporuGoster(kitap* bas) {
    if (iadeListesiBas == nullptr) {
        cout << "Iade edilmis kitap yok!\n";
        return;
    }

    cout << "\nIADE EDILEN KITAPLAR RAPORU\n";
    cout << "-----------------------------------------\n";

    IadeKitap* temp = iadeListesiBas;
    do {
        kitap* ktp = bas;
        while (ktp != nullptr && ktp->id != temp->kitapId) {
            ktp = ktp->sonraki;
        }

        if (ktp != nullptr) {
            cout << "ID: " << temp->kitapId << " - " << ktp->isim << endl;
            cout << "Iade Zamani: " << ctime(&temp->iadeZamani);
            cout << "-----------------------------------------\n";
        }

        temp = temp->sonraki;
    } while (temp != iadeListesiBas);
}

void erisilebilirKitaplariGoster(kitap* bas) {
    if (bas == nullptr) {
        cout << "Kutuphane bos!\n";
        return;
    }

    cout << "\nERISILEBILIR KITAPLAR\n";
    cout << "-----------------------------------------\n";

    kitap* temp = bas;
    while (temp != nullptr) {
        // Kitabýn ödünç alýnýp alýnmadýðýný kontrol et
        bool oduncAlinmis = false;
        if (oduncListesiBas != nullptr) {
            OduncKitap* oTemp = oduncListesiBas;
            do {
                if (oTemp->kitapId == temp->id && oTemp->iadeZamani == 0) {
                    oduncAlinmis = true;
                    break;
                }
                oTemp = oTemp->sonraki;
            } while (oTemp != oduncListesiBas);
        }

        if (!oduncAlinmis) {
            cout << "ID: " << temp->id << " - " << temp->isim << " (" << temp->yazar << ")\n";
        }

        temp = temp->sonraki;
    }
    cout << "-----------------------------------------\n";
}
