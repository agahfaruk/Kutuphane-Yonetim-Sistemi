#include <iostream>
#include "../include/cift_yonlu_dairesel_bagli_liste.h"
#include "../include/ortak.h"
using namespace std;

// Yorum ekleme fonksiyonu
void kitapYorumEkle(kitapCift* bas) {
    if (bas == nullptr) {
        cout << "Kutuphane bos!\n";
        return;
    }

    int arananId;
    cout << "Yorum yapmak istediginiz kitabin id'sini girin: ";
    cin >> arananId;
    cin.ignore();

    kitapCift* temp = bas;
    bool bulundu = false;

    do {
        if (temp->id == arananId) {
            string yorum;
            cout << "Yorumunuzu yazin: ";
            getline(cin, yorum);

            temp->yorumlar.push_back(yorum);
            cout << "Yorum basariyla eklendi!\n";
            bulundu = true;
            break;
        }
        temp = temp->sonraki;
    } while (temp != bas && !bulundu); // Bulunca çýk

    if (!bulundu) {
        cout << "Bu id'ye sahip kitap bulunamadi!\n";
    }
}

// Yorumlarý listeleme fonksiyonu
void kitapYorumlariListele(kitapCift* bas) {
    if (bas == nullptr) {
        cout << "Kutuphane bos!\n";
        return;
    }

    int arananId;
    cout << "Yorumlarini gormek istediginiz kitabin id'sini girin: ";
    cin >> arananId;

    kitapCift* temp = bas;
    bool bulundu = false;

    // Dairesel liste olduðu için do-while kullanmak gerekiyor
    do {
        if (temp->id == arananId) {
            cout << "\n----- " << temp->isim << " (" << temp->yazar << ") Yorumlari -----\n";
            if (temp->yorumlar.empty()) {
                cout << "Henuz yorum yok.\n";
            }
            else {
                for (size_t i = 0; i < temp->yorumlar.size(); i++) {
                    cout << i + 1 << ". " << temp->yorumlar[i] << "\n";
                }
            }
            cout << "----------------------------------------\n";
            bulundu = true;
            break;
        }
        temp = temp->sonraki;
    } while (temp != bas && !bulundu);

    if (!bulundu) {
        cout << "Bu id'ye sahip kitap bulunamadi!\n";
    }
}

// Koleksiyon oluþturma
void koleksiyonOlustur() {
    if (kullaniciKoleksiyonu.olusturuldu) {
        cout << "Zaten bir koleksiyonunuz var!\n";
        return;
    }
    kullaniciKoleksiyonu.olusturuldu = true;
    cout << "Koleksiyonunuz basariyla olusturuldu!\n";
}

// Koleksiyona kitap ekleme
void koleksiyonaKitapEkle(kitapCift* bas) {
    if (!kullaniciKoleksiyonu.olusturuldu) {
        cout << "Once koleksiyon olusturmalisiniz!\n";
        return;
    }

    if (bas == nullptr) {
        cout << "Kutuphane bos!\n";
        return;
    }

    int girilenId;
    cout << "Koleksiyonunuza ekleyeceginiz kitabin id'sini giriniz: ";
    cin >> girilenId;

    kitapCift* temp = bas;
    bool bulundu = false;
    bool kitapVar = false;

    // Önce koleksiyonda bu kitabýn olup olmadýðýný kontrol et
    if (kullaniciKoleksiyonu.bas != nullptr) {
        kitapCift* koleksiyonTemp = kullaniciKoleksiyonu.bas;
        do {
            if (koleksiyonTemp->id == girilenId) {
                cout << "Bu kitap zaten koleksiyonunuzda var!\n";
                kitapVar = true;
                break;
            }
            koleksiyonTemp = koleksiyonTemp->sonraki;
        } while (koleksiyonTemp != kullaniciKoleksiyonu.bas);
    }

    if (kitapVar) return;

    // Ana listede kitabý ara
    do {
        if (temp->id == girilenId) {
            // Yeni bir kitap oluþtur (pointer deðil, kopya)
            kitapCift* yeni = new kitapCift;
            *yeni = *temp; // Tüm verileri kopyala
            yeni->yorumlar.clear(); // Yorumlarý temizle (isteðe baðlý)

            if (kullaniciKoleksiyonu.bas == nullptr) {
                yeni->sonraki = yeni;
                yeni->onceki = yeni;
                kullaniciKoleksiyonu.bas = yeni;
            }
            else {
                kitapCift* son = kullaniciKoleksiyonu.bas->onceki;
                son->sonraki = yeni;
                yeni->onceki = son;
                yeni->sonraki = kullaniciKoleksiyonu.bas;
                kullaniciKoleksiyonu.bas->onceki = yeni;
            }

            cout << yeni->isim << " koleksiyona eklendi!\n";
            bulundu = true;
            break;
        }
        temp = temp->sonraki;
    } while (temp != bas);

    if (!bulundu) {
        cout << "Kitap bulunamadi!\n";
    }
}

// Okunma durumu güncelleme
void okunmaDurumuGuncelle() {
    if (!kullaniciKoleksiyonu.bas) {
        cout << "Koleksiyonunuz bos!\n";
        return;
    }

    int id;
    cout << "Durumunu guncellemek istediginiz kitabin ID'si: ";
    cin >> id;

    kitapCift* temp = kullaniciKoleksiyonu.bas;
    do {
        if (temp->id == id) {
            temp->okundu = !temp->okundu;
            cout << temp->isim << " - "
                << (temp->okundu ? "OKUNDU" : "OKUNMADI") << endl;
            return;
        }
        temp = temp->sonraki;
    } while (temp != kullaniciKoleksiyonu.bas);

    cout << "Kitap bulunamadi!\n";
}

// Koleksiyondan kitap silme
void koleksiyondanKitapSil() {
    if (!kullaniciKoleksiyonu.bas) {
        cout << "Koleksiyonunuz bos!\n";
        return;
    }

    int id;
    cout << "Silmek istediginiz kitabin ID'si: ";
    cin >> id;

    kitapCift* temp = kullaniciKoleksiyonu.bas;
    do {
        if (temp->id == id) {
            if (temp->sonraki == temp) { // Tek eleman varsa
                kullaniciKoleksiyonu.bas = nullptr;
            }
            else {
                temp->onceki->sonraki = temp->sonraki;
                temp->sonraki->onceki = temp->onceki;
                if (temp == kullaniciKoleksiyonu.bas) {
                    kullaniciKoleksiyonu.bas = temp->sonraki;
                }
            }
            cout << temp->isim << " silindi!\n";
            delete temp;
            return;
        }
        temp = temp->sonraki;
    } while (temp != kullaniciKoleksiyonu.bas);

    cout << "Kitap bulunamadi!\n";
}

// Koleksiyonu listeleme
void koleksiyonuListele() {
    if (!kullaniciKoleksiyonu.bas) {
        cout << "\nKoleksiyonunuz bos!\n\n";
        return;
    }

    cout << "\n----- KITAP KOLEKSIYONUNUZ -----\n";
    cout << left << setw(5) << "ID" << setw(30) << "KITAP ADI"
        << setw(20) << "YAZAR" << setw(10) << "DURUM" << endl;
    cout << "---------------------------------------------------------------\n";

    kitapCift* temp = kullaniciKoleksiyonu.bas;
    do {
        cout << left << setw(5) << temp->id
            << setw(30) << (temp->isim.size() > 28 ? temp->isim.substr(0, 28) + ".." : temp->isim)
            << setw(20) << (temp->yazar.size() > 18 ? temp->yazar.substr(0, 18) + ".." : temp->yazar)
            << setw(10) << (temp->okundu ? "OKUNDU" : "OKUNMADI") << endl;
        temp = temp->sonraki;
    } while (temp != kullaniciKoleksiyonu.bas);
    cout << "---------------------------------------------------------------\n\n";
}