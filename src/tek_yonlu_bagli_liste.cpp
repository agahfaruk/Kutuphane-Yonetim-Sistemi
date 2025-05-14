#include <iostream>
#include <iomanip>
#include "../include/tek_yonlu_bagli_liste.h"
#include "../include/ortak.h"
using namespace std;

// Kitap ekleme fonksiyonu - Hasar bilgileri eklendi
void kitapEkle(kitap*& bas, int id, string isim, string yazar, int sayfaSayisi,
    int basimYili, string yayinEvi, string dil, string kategori,
    bool hasarli, string hasarNotu) {
    kitap* yeniKitap = new kitap{ id, isim, yazar, sayfaSayisi, basimYili, yayinEvi,
                                 dil, kategori, hasarNotu, hasarli };

    if (bas == nullptr) {
        bas = yeniKitap;
    }
    else {
        kitap* temp = bas;
        while (temp->sonraki != nullptr) {
            temp = temp->sonraki;
        }
        temp->sonraki = yeniKitap;
    }
}

// Kitaba hasar notu ekleme fonksiyonu 
void kitapHasarNotuEkle(kitap* bas) {
    if (bas == nullptr) {
        cout << "\nKutuphane bos!\n\n";
        return;
    }

    int kitapId;
    cout << "Hasar notu eklemek istediginiz kitabin ID'sini giriniz: ";
    cin >> kitapId;
    cin.ignore();

    kitap* temp = bas;
    while (temp != nullptr) {
        if (temp->id == kitapId) {
            cout << "Hasar notunu giriniz: ";
            getline(cin, temp->hasarNotu);
            temp->hasarli = true;
            cout << "Hasar notu eklendi.\n\n";
            return;
        }
        temp = temp->sonraki;
    }
    cout << "\nKitap bulunamadi!\n\n";
}

// Hasarlý kitaplarý listeleme fonksiyonu
void hasarliKitaplariListele(kitap* bas) {
    if (bas == nullptr) {
        cout << "\nKutuphane bos!\n\n";
        return;
    }

    bool hasarliKitapVar = false;
    kitap* temp = bas;

    cout << "\n---------------------------------------------------------------------------------------------------------\n";
    cout << left << setw(8) << "ID" << setw(30) << "Isim" << setw(25) << "Yazar" << setw(15) << "Durum" << setw(40) << "Hasar Notu" << endl;
    cout << "---------------------------------------------------------------------------------------------------------\n";

    while (temp != nullptr) {
        if (temp->hasarli) {
            cout << left << setw(8) << temp->id
                << setw(30) << temp->isim.substr(0, 28)
                << setw(25) << temp->yazar.substr(0, 23)
                << setw(15) << "Hasarli"
                << setw(40) << temp->hasarNotu.substr(0, 38) << endl;
            hasarliKitapVar = true;
        }
        temp = temp->sonraki;
    }

    if (!hasarliKitapVar) {
        cout << "Hasarli kitap bulunamadi.\n";
    }
    cout << "---------------------------------------------------------------------------------------------------------\n\n";
}

// Kitap düzenleme fonksiyonu
void kitapDuzenle(kitap* bas) {
    if (bas == nullptr) {
        cout << "Kutuphane bos!\n\n";
        return;
    }

    string girilenIsim;
    cout << "Duzenlemek istediginiz kitabin ismini giriniz: ";
    getline(cin, girilenIsim);

    kitap* temp = bas;
    while (temp != nullptr) {
        if (temp->isim == girilenIsim) {
            cout << "\nKitap bulundu.\n\n";

            cout << "Yeni id giriniz: ";
            cin >> temp->id;
            cin.ignore();

            cout << "Yeni yazar giriniz: ";
            getline(cin, temp->yazar);

            cout << "Yeni sayfa sayisi giriniz: ";
            cin >> temp->sayfaSayisi;

            cout << "Yeni basim yilini giriniz: ";
            cin >> temp->basimYili;
            cin.ignore();

            cout << "Yeni yayin evi giriniz (yerli/yabanci): ";
            getline(cin, temp->yayinEvi);

            cout << "Yeni dil giriniz (Turkce/Ingilizce): ";
            getline(cin, temp->dil);

            cout << "Yeni kategori giriniz: ";
            getline(cin, temp->kategori);

            cout << "\nKitap duzenlendi.\n\n";
            return;
        }
        temp = temp->sonraki;
    }
    cout << "\nKitap bulunamadi!\n\n";
}

// Id'ye göre kitap silme fonksiyonu 
void kitapSilId(kitap*& bas, kitapCift*& bas2) {
    if (bas == nullptr) {
        cout << "Kutuphane bos!\n\n";
        return;
    }

    int girilenId;
    cout << "Silmek istediginiz kitabin id'sini giriniz: ";
    cin >> girilenId;
    cin.ignore();

    kitap* temp = bas;
    kitap* onceki = nullptr;

    while (temp != nullptr) {
        if (temp->id == girilenId) {
            // Çift yönlü dairesel listeden de silelim ki koleksiyon gösterme veya yorum gösterme kýsmýnda sorun yaþamayalým
            if (bas2 != nullptr) {
                kitapCift* ciftTemp = bas2;
                bool silindi = false;

                do {
                    if (ciftTemp->id == girilenId) {
                        if (ciftTemp->sonraki == ciftTemp) { // Tek eleman
                            delete ciftTemp;
                            bas2 = nullptr;
                        }
                        else {
                            ciftTemp->onceki->sonraki = ciftTemp->sonraki;
                            ciftTemp->sonraki->onceki = ciftTemp->onceki;
                            if (ciftTemp == bas2) {
                                bas2 = ciftTemp->sonraki;
                            }
                            delete ciftTemp;
                        }
                        silindi = true;
                        break;
                    }
                    ciftTemp = ciftTemp->sonraki;
                } while (ciftTemp != bas2 && !silindi);
            }

            // Ana listeden sil
            if (onceki == nullptr) {
                bas = temp->sonraki;
            }
            else {
                onceki->sonraki = temp->sonraki;
            }

            delete temp;
            cout << "\n" << girilenId << " id'li kitap silindi.\n\n";
            return;
        }
        onceki = temp;
        temp = temp->sonraki;
    }
    cout << "\nKitap bulunamadi!\n\n";
}

// Id'ye göre kitap listeleme fonksiyonu
void kitapIdListele(kitap* bas) {
    if (bas == nullptr) {
        cout << "Kutuphane bos!\n\n";
        return;
    }

    int girilenId;
    cout << "Sorgulanacak kitabin id'sini giriniz: ";
    cin >> girilenId;
    cin.ignore();

    kitap* temp = bas;
    while (temp != nullptr) {
        if (temp->id == girilenId) {
            cout << "\n-------------------------------------------------------------------------------------------------------------------------------------------------------\n";
            cout << left << setw(8) << "ID" << setw(30) << "Isim" << setw(25) << "Yazar" << setw(15) << "Sayfa" << setw(12) << "Basim Yili"
                << setw(15) << "Yayin Evi" << setw(15) << "Dil" << setw(25) << "Kategori" << setw(10) << "Durum" << endl;
            cout << "-------------------------------------------------------------------------------------------------------------------------------------------------------\n";
            cout << left << setw(8) << temp->id << setw(30) << temp->isim.substr(0, 28)
                << setw(25) << temp->yazar.substr(0, 23) << setw(15) << temp->sayfaSayisi
                << setw(12) << temp->basimYili << setw(15) << temp->yayinEvi
                << setw(15) << temp->dil << setw(25) << temp->kategori
                << setw(10) << (temp->hasarli ? "Hasarli" : "Saglam") << endl;
            cout << "-------------------------------------------------------------------------------------------------------------------------------------------------------\n\n";
            return;
        }
        temp = temp->sonraki;
    }
    cout << "\nKitap bulunamadi!\n\n";
}

// Kütüphanedeki toplam kitap sayýsýný getiren fonksiyon
void toplamKitapSayisi(kitap* bas) {
    kitap* temp = bas;
    int kitapSayisi = 0;
    if (bas == nullptr) {
        cout << "Kutuphane bos!\n\n";
        return;
    }
    else {
        do {
            kitapSayisi += 1;
            temp = temp->sonraki;
        } while (temp != nullptr);
        cout << "Kutuphanede " << kitapSayisi << " kitap var.\n\n";
    }
}

// Kitaplarý id bilgisine göre sýralayan fonksiyon
void idyeGoreSirala(kitap*& bas) {
    if (bas == nullptr || bas->sonraki == nullptr) return; // Liste boþ veya tek elemanlýysa sýralamaya gerek yok

    bool degisim;
    do {
        degisim = false;
        kitap* temp = bas;
        kitap* onceki = nullptr;

        while (temp->sonraki != nullptr) {
            kitap* sonraki = temp->sonraki;

            if (temp->id > sonraki->id) {
                // Düðümleri deðiþtir
                temp->sonraki = sonraki->sonraki;
                sonraki->sonraki = temp;

                if (onceki == nullptr) {
                    bas = sonraki;  // Baþ düðüm deðiþti
                }
                else {
                    onceki->sonraki = sonraki;
                }

                degisim = true;
                onceki = sonraki; // Önceki düðümü güncelle
            }
            else {
                onceki = temp;
                temp = temp->sonraki;
            }
        }
    } while (degisim);
}

// Kitaplarý sayfa sayýsýna göre sýralayan fonksiyon
void sayfaSayisinaGoreSirala(kitap*& bas) {
    if (bas == nullptr || bas->sonraki == nullptr) return; // Liste boþ veya tek elemanlýysa sýralamaya gerek yok

    bool degisim;
    do {
        degisim = false;
        kitap* temp = bas;
        kitap* onceki = nullptr;

        while (temp->sonraki != nullptr) {
            kitap* sonraki = temp->sonraki;

            if (temp->sayfaSayisi > sonraki->sayfaSayisi) {
                // Düðümleri deðiþtir
                temp->sonraki = sonraki->sonraki;
                sonraki->sonraki = temp;

                if (onceki == nullptr) {
                    bas = sonraki;  // Baþ düðüm deðiþti
                }
                else {
                    onceki->sonraki = sonraki;
                }

                degisim = true;
                onceki = sonraki; // Önceki düðümü güncelle
            }
            else {
                onceki = temp;
                temp = temp->sonraki;
            }
        }
    } while (degisim);
}

// Kitaplarý basým yýlýna göre sýralayan fonksiyon
void basimYilinaGoreSirala(kitap*& bas) {
    if (bas == nullptr || bas->sonraki == nullptr) return; // Liste boþ veya tek elemanlýysa sýralamaya gerek yok

    bool degisim;
    do {
        degisim = false;
        kitap* temp = bas;
        kitap* onceki = nullptr;

        while (temp->sonraki != nullptr) {
            kitap* sonraki = temp->sonraki;

            if (temp->basimYili > sonraki->basimYili) {
                // Düðümleri deðiþtir
                temp->sonraki = sonraki->sonraki;
                sonraki->sonraki = temp;

                if (onceki == nullptr) {
                    bas = sonraki;  // Baþ düðüm deðiþti
                }
                else {
                    onceki->sonraki = sonraki;
                }

                degisim = true;
                onceki = sonraki; // Önceki düðümü güncelle
            }
            else {
                onceki = temp;
                temp = temp->sonraki;
            }
        }
    } while (degisim);
}

// Kitaplarý basým yýlýna göre listeleme fonksiyonu
void basimYilinaGoreListele(kitap* bas) {
    if (bas == nullptr) {
        cout << "Kutuphane bos!\n\n";
        return;
    }

    kitap* temp = bas;
    cout << "\n-------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    cout << left << setw(8) << "ID" << setw(30) << "Isim" << setw(25) << "Yazar" << setw(15) << "Sayfa" << setw(12) << "Basim Yili"
        << setw(15) << "Yayin Evi" << setw(15) << "Dil" << setw(25) << "Kategori" << setw(10) << "Durum" << endl;
    cout << "-------------------------------------------------------------------------------------------------------------------------------------------------------\n";

    for (int i = 0; i < 5 && temp != nullptr; i++) {
        cout << left << setw(8) << temp->id << setw(30) << temp->isim.substr(0, 28)
            << setw(25) << temp->yazar.substr(0, 23) << setw(15) << temp->sayfaSayisi
            << setw(12) << temp->basimYili << setw(15) << temp->yayinEvi
            << setw(15) << temp->dil << setw(25) << temp->kategori
            << setw(10) << (temp->hasarli ? "Hasarli" : "Saglam") << endl;
        temp = temp->sonraki;
    }

    cout << "-------------------------------------------------------------------------------------------------------------------------------------------------------\n\n";
}

// Kitap listeleme fonksiyonu
void kitapListele(kitap* bas) {
    if (bas == nullptr) {
        cout << "\nKutuphane bos!\n\n";
        return;
    }

    kitap* temp = bas;
    cout << "\n-------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    cout << left << setw(8) << "ID" << setw(30) << "Isim" << setw(25) << "Yazar" << setw(15) << "Sayfa" << setw(12) << "Basim Yili"
        << setw(15) << "Yayin Evi" << setw(15) << "Dil" << setw(25) << "Kategori" << setw(10) << "Durum" << endl;
    cout << "-------------------------------------------------------------------------------------------------------------------------------------------------------\n";

    while (temp != nullptr) {
        cout << left << setw(8) << temp->id << setw(30) << temp->isim.substr(0, 28)
            << setw(25) << temp->yazar.substr(0, 23) << setw(15) << temp->sayfaSayisi
            << setw(12) << temp->basimYili << setw(15) << temp->yayinEvi
            << setw(15) << temp->dil << setw(25) << temp->kategori
            << setw(10) << (temp->hasarli ? "Hasarli" : "Saglam") << endl;
        temp = temp->sonraki;
    }
    cout << "-------------------------------------------------------------------------------------------------------------------------------------------------------\n\n";
}

