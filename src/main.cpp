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
#include "../include/tek_yonlu_bagli_liste.h"
#include "../include/cift_yonlu_dairesel_bagli_liste.h"
#include "../include/tek_yonlu_dairesel_bagli_liste.h"
#include "../include/yigin.h"
#include "../include/kuyruk.h"
#include "../include/agac.h"
#include "../include/hash.h"
using namespace std;

int main() {

    system("cls");

    kitap* tekYonluListe = nullptr;  // Kitap listesinin baþlangýcýný önce boþ belirledim
    kitapCift* ciftYonluListe = nullptr;

    //Sistemden kitap eklemekle uðraþmamak için direkt kodun içerisinde kitap ekledim, sunumda zaman kaybetmemek için
    kitapEkle(tekYonluListe, 1001, "Insan, Ekonomi ve Devlet", "Murray N. Rothbard", 1184, 1962, "yabanci", "Turkce", "Ekonomi");
    kitapEkle(tekYonluListe, 1002, "Anarko-Kapitalizm", "Murray N. Rothbard", 320, 1973, "yabanci", "Turkce", "Politika");
    kitapEkle(tekYonluListe, 1003, "Kolelik Yolu", "Friedrich A. Hayek", 256, 1944, "yabanci", "Turkce", "Ekonomi");
    kitapEkle(tekYonluListe, 1004, "Kapitalizm ve Ozgurluk", "Milton Friedman", 230, 1962, "yabanci", "Turkce", "Ekonomi");
    kitapEkle(tekYonluListe, 1005, "Hukumetin Anatomisi", "Frederic Bastiat", 180, 1848, "yabanci", "Turkce", "Politika");
    kitapEkle(tekYonluListe, 1006, "Piyasa ve Ozgurluk", "Ludwig Lachmann", 320, 1978, "yabanci", "Turkce", "Ekonomi");
    kitapEkle(tekYonluListe, 1007, "Bireycilik ve Ekonomik Duzen", "Friedrich A. Hayek", 280, 1948, "yabanci", "Turkce", "Ekonomi");
    kitapEkle(tekYonluListe, 1008, "Ekonomi Politikasi", "Ludwig von Mises", 210, 1979, "yabanci", "Turkce", "Ekonomi");
    kitapEkle(tekYonluListe, 1009, "Ozgur Toplumda Devlet", "Murray N. Rothbard", 350, 1973, "yabanci", "Turkce", "Politika");
    kitapEkle(tekYonluListe, 1010, "Para ve Devlet", "Carl Menger", 320, 1892, "yabanci", "Turkce", "Ekonomi");
    kitapEkle(tekYonluListe, 1011, "Ekonomi Biliminin Temelleri", "Carl Menger", 280, 1871, "yabanci", "Turkce", "Ekonomi");
    kitapEkle(tekYonluListe, 1012, "Faiz Teorisi", "Eugen von Bohm-Bawerk", 450, 1884, "yabanci", "Turkce", "Ekonomi");
    kitapEkle(tekYonluListe, 1013, "Kapital ve Faiz", "Eugen von Bohm-Bawerk", 500, 1889, "yabanci", "Turkce", "Ekonomi");
    kitapEkle(tekYonluListe, 1014, "Piyasa Teorisi", "Israel Kirzner", 320, 1963, "yabanci", "Turkce", "Ekonomi");
    kitapEkle(tekYonluListe, 1015, "Rekabet ve Girisimcilik", "Israel Kirzner", 280, 1973, "yabanci", "Turkce", "Ekonomi");
    kitapEkle(tekYonluListe, 1016, "Ozgurluk Yasasi", "Murray N. Rothbard", 400, 1958, "yabanci", "Turkce", "Politika");
    kitapEkle(tekYonluListe, 1017, "Hukukun Felsefesi", "Bruno Leoni", 220, 1961, "yabanci", "Turkce", "Hukuk");
    kitapEkle(tekYonluListe, 1018, "Para ve Kredi Teorisi", "Ludwig von Mises", 380, 1912, "yabanci", "Turkce", "Ekonomi");
    kitapEkle(tekYonluListe, 1019, "Iktsadi Dusunce Tarihi", "Murray N. Rothbard", 600, 1995, "yabanci", "Turkce", "Ekonomi");
    kitapEkle(tekYonluListe, 1020, "Ozel Para", "Friedrich A. Hayek", 180, 1976, "yabanci", "Turkce", "Ekonomi");
    kitapEkle(tekYonluListe, 1021, "Beyaz Gemi", "Cengiz Aytmatov", 224, 1970, "yabanci", "Turkce", "Roman");
    kitapEkle(tekYonluListe, 1022, "Korku", "Stefan Zweig", 80, 1925, "yabanci", "Turkce", "Psikolojik");
    kitapEkle(tekYonluListe, 1023, "Kirmizi Pazartesi", "Gabriel Garcia Marquez", 120, 1981, "yabanci", "Turkce", "Roman");
    kitapEkle(tekYonluListe, 1024, "Kardesimin Hikayesi", "Zulfu Livaneli", 328, 2013, "yerli", "Turkce", "Roman");
    kitapEkle(tekYonluListe, 1025, "Serenad", "Zulfu Livaneli", 408, 2011, "yerli", "Turkce", "Roman");
    kitapEkle(tekYonluListe, 1026, "Ask", "Elif Safak", 420, 2009, "yerli", "Turkce", "Roman");
    kitapEkle(tekYonluListe, 1027, "Kafamda Bir Tuhaflik", "Orhan Pamuk", 480, 2014, "yerli", "Turkce", "Roman");
    kitapEkle(tekYonluListe, 1028, "Masumiyet Muzesi", "Orhan Pamuk", 592, 2008, "yerli", "Turkce", "Roman");
    kitapEkle(tekYonluListe, 1029, "Tutunamayanlar", "Oguz Atay", 724, 1972, "yerli", "Turkce", "Roman");
    kitapEkle(tekYonluListe, 1030, "Tehlikeli Oyunlar", "Oguz Atay", 479, 1973, "yerli", "Turkce", "Roman");
    kitapEkle(tekYonluListe, 1031, "Bir Bilim Adaminin Romansi", "Oguz Atay", 288, 1975, "yerli", "Turkce", "Biyografik");
    kitapEkle(tekYonluListe, 1032, "Huzur", "Ahmet Hamdi Tanpinar", 486, 1949, "yerli", "Turkce", "Roman");
    kitapEkle(tekYonluListe, 1033, "Saatleri Ayarlama Enstitusu", "Ahmet Hamdi Tanpinar", 360, 1961, "yerli", "Turkce", "Roman");
    kitapEkle(tekYonluListe, 1034, "Anayurt Oteli", "Yusuf Atilgan", 184, 1973, "yerli", "Turkce", "Roman");
    kitapEkle(tekYonluListe, 1035, "Aylak Adam", "Yusuf Atilgan", 160, 1959, "yerli", "Turkce", "Roman");
    kitapEkle(tekYonluListe, 1036, "Parasiz Yatili", "Furuzan", 208, 1971, "yerli", "Turkce", "Oykü");
    kitapEkle(tekYonluListe, 1037, "Kirk Oda", "Murathan Mungan", 328, 1987, "yerli", "Turkce", "Oykü");
    kitapEkle(tekYonluListe, 1038, "Yuksek Gerilim", "Hakan Gunday", 248, 2010, "yerli", "Turkce", "Roman");
    kitapEkle(tekYonluListe, 1039, "Az", "Hakan Gunday", 392, 2011, "yerli", "Turkce", "Roman");
    kitapEkle(tekYonluListe, 1040, "Daha", "Hakan Gunday", 328, 2013, "yerli", "Turkce", "Roman");
    kitapEkle(tekYonluListe, 1041, "Zaman Makinesi", "H.G. Wells", 128, 1895, "yabanci", "Turkce", "Bilim Kurgu");
    kitapEkle(tekYonluListe, 1042, "Dune", "Frank Herbert", 896, 1965, "yabanci", "Turkce", "Bilim Kurgu");
    kitapEkle(tekYonluListe, 1043, "Cesur Yeni Dunya", "Aldous Huxley", 288, 1932, "yabanci", "Turkce", "Distopya");
    kitapEkle(tekYonluListe, 1044, "Otomatik Portakal", "Anthony Burgess", 192, 1962, "yabanci", "Turkce", "Distopya");
    kitapEkle(tekYonluListe, 1045, "Fahrenheit 451", "Ray Bradbury", 256, 1953, "yabanci", "Turkce", "Distopya");
    kitapEkle(tekYonluListe, 1046, "Vakif", "Isaac Asimov", 296, 1951, "yabanci", "Turkce", "Bilim Kurgu");
    kitapEkle(tekYonluListe, 1047, "Solaris", "Stanislaw Lem", 204, 1961, "yabanci", "Turkce", "Bilim Kurgu");
    kitapEkle(tekYonluListe, 1048, "Yol", "Cormac McCarthy", 256, 2006, "yabanci", "Turkce", "Post-Apokaliptik");
    kitapEkle(tekYonluListe, 1049, "Kizil Nehirler", "Jean-Christophe Grange", 480, 1998, "yabanci", "Turkce", "Polisiye");
    kitapEkle(tekYonluListe, 1050, "Kayip Sembol", "Dan Brown", 528, 2009, "yabanci", "Turkce", "Gerilim");

    int secim;
    do {
        cout << "---KUTUPHANE YONETIM SISTEMI----\n";
        cout << "--------------------------------\n";
        cout << "1 - Personel Girisi\n";
        cout << "2 - Kullanici Girisi\n";
        cout << "0 - Cikis\n";
        cout << "--------------------------------\n";
        cout << "Seciminizi girin: ";
        cin >> secim;
        cout << endl;

        switch (secim) {
        case 1:
            system("cls");
            int personelSecim1;
            do {
                cout << "---KUTUPHANE YONETIM SISTEMI----\n";
                cout << "--------------------------------\n";
                cout << "Personel Menusu\n";
                cout << "1 - Kitap Yonetimi\n";
                cout << "2 - Odunc ve Iade Islemleri\n";
                cout << "3 - Talep Yonetimi\n";
                cout << "4 - Veri Analizi\n";
                cout << "5 - Degerlendirme Sistemi\n";
                cout << "0 - Cikis\n";
                cout << "--------------------------------\n";
                cout << "Seciminizi girin: ";
                cin >> personelSecim1;
                cin.ignore();

                switch (personelSecim1) {
                case 1:
                    system("cls");
                    int personelSecim2;
                    do {
                        cout << "---KUTUPHANE YONETIM SISTEMI----\n";
                        cout << "--------------------------------\n";
                        cout << "Personel Menusu - Kitap Yonetimi\n";
                        cout << right << setw(2) << "1" << left << " - Kitap ekle\n";
                        cout << right << setw(2) << "2" << left << " - Ismine gore kitabi duzenle\n";
                        cout << right << setw(2) << "3" << left << " - Id'ye gore kitabi sil\n";
                        cout << right << setw(2) << "4" << left << " - Kitaplari listele\n";
                        cout << right << setw(2) << "5" << left << " - Id'ye gore kitap listele\n";
                        cout << right << setw(2) << "6" << left << " - Toplam kitap sayisini goster\n";
                        cout << right << setw(2) << "7" << left << " - Kitaplari sayfa sayisina gore listele\n";
                        cout << right << setw(2) << "8" << left << " - Basim yilina gore en eski 5 kitabi listele\n";
                        cout << right << setw(2) << "9" << left << " - Kitaba hasar notu ekle\n";
                        cout << right << setw(2) << "10" << left << " - Hasarli kitaplari listele\n";
                        cout << right << setw(2) << "0" << left << " - Cikis\n";
                        cout << "--------------------------------\n";
                        cout << "Seciminizi girin: ";
                        cin >> personelSecim2;
                        cin.ignore();

                        int id, sayfaSayisi, basimYili;
                        string isim, yazar, yayinEvi, dil, kategori;

                        switch (personelSecim2) {
                        case 1:
                            cout << "Kitabin ID'sini giriniz: ";
                            cin >> id;
                            cin.ignore();

                            cout << "Kitabin ismini giriniz: ";
                            getline(cin, isim);

                            cout << "Kitabin yazarini giriniz: ";
                            getline(cin, yazar);

                            cout << "Kitabin sayfa sayisini giriniz: ";
                            cin >> sayfaSayisi;

                            cout << "Kitabin basim yilini giriniz: ";
                            cin >> basimYili;
                            cin.ignore();

                            cout << "Kitabin yayin evini giriniz (yerli/yabanci): ";
                            getline(cin, yayinEvi);

                            cout << "Kitabin dilini giriniz (Turkce/Ingilizce): ";
                            getline(cin, dil);

                            cout << "Kitabin kategorisini giriniz: ";
                            getline(cin, kategori);

                            kitapEkle(tekYonluListe, id, isim, yazar, sayfaSayisi, basimYili, yayinEvi, dil, kategori);
                            cout << "\nKitap basariyla eklendi: " << isim << " - " << yazar << "\n\n";
                            Sleep(1000);
                            system("cls");
                            break;

                        case 2:
                            kitapDuzenle(tekYonluListe);
                            Sleep(1000);
                            system("cls");
                            break;

                        case 3:
                            kitapSilId(tekYonluListe, ciftYonluListe);
                            /* kullanýcý giriþi yapýp koleksiyona kitap ekleyip veya kitaplara yorum ekleyip geri
                            personel giriþinden giriþ yapýlýp ekleme yapýlan kitap silindiðinde kullanýcý kýsmýna geri dönüp ilgili kitabýn
                            yorumu veya bulunduðu koleksiyon listelendiðinde bazý sorunlar oluþtuðundan dolayý çift yönlü dairesel 
                            listeden de bazý deðiþikleri tekrar kaydetmem gerektiðinden burada çift yönlü dairesel 
                            listeye de bi kaç dokunuþum oldu (veri çekme vs. yok, sadece o listeyi de güncelliyor) 
                            ama onun dýþýnda sistemi kapatmadan personel giriþinden kullanýcý giriþine geri dönülmediði sürece 
                            buna da ihtiyaç kalmýyor, ince ayrýntýlarý düþündüðüm için buna baþvurdum.*/
                            Sleep(1000);
                            system("cls");
                            break;

                        case 4:
                            idyeGoreSirala(tekYonluListe);
                            kitapListele(tekYonluListe);

                            int cikmakIcin1;
                            do {
                                cout << "Listeden cikmak icin 0'i tuslayin ";
                                cin >> cikmakIcin1;
                                if (cikmakIcin1 == 0) {
                                    break;
                                }
                            } while (cikmakIcin1 != 0);
                            Sleep(200);
                            system("cls");
                            break;

                        case 5:
                            kitapIdListele(tekYonluListe);

                            int cikmakIcin2;
                            do {
                                cout << "Listeden cikmak icin 0'i tuslayin ";
                                cin >> cikmakIcin2;
                                if (cikmakIcin2 == 0) {
                                    break;
                                }
                            } while (cikmakIcin2 != 0);
                            Sleep(200);
                            system("cls");
                            break;

                        case 6:
                            toplamKitapSayisi(tekYonluListe);
                            Sleep(3000);
                            system("cls");
                            break;

                        case 7:
                            sayfaSayisinaGoreSirala(tekYonluListe);
                            kitapListele(tekYonluListe);

                            int cikmakIcin3;
                            do {
                                cout << "Listeden cikmak icin 0'i tuslayin ";
                                cin >> cikmakIcin3;
                                if (cikmakIcin3 == 0) {
                                    break;
                                }
                            } while (cikmakIcin3 != 0);
                            Sleep(200);
                            idyeGoreSirala(tekYonluListe); 
                            /* tekrardan id ye göre sýralatmamýn
                            sebebi ayný isimli kitaplardan birini 
                            düzenleyeceðimiz zaman id si en az olan 
                            yani ilk eklenenlerden biri düzenlensin diye, 
                            ve de bu tarz daha fazla sorunun yaþanmasýný önlemek için.*/
                            system("cls");
                            break;

                        case 8:
                            basimYilinaGoreSirala(tekYonluListe);
                            basimYilinaGoreListele(tekYonluListe);

                            int cikmakIcin4;
                            do {
                                cout << "Listeden cikmak icin 0'i tuslayin ";
                                cin >> cikmakIcin4;
                                if (cikmakIcin4 == 0) {
                                    break;
                                }
                            } while (cikmakIcin4 != 0);
                            Sleep(200);
                            system("cls");
                            break;

                        case 9:
                            kitapHasarNotuEkle(tekYonluListe);
                            Sleep(1000);
                            system("cls");
                            break;

                        case 10:
                            hasarliKitaplariListele(tekYonluListe);

                            int cikmakIcin5;
                            do {
                                cout << "Listeden cikmak icin 0'i tuslayin ";
                                cin >> cikmakIcin5;
                                if (cikmakIcin5 == 0) {
                                    break;
                                }
                            } while (cikmakIcin5 != 0);
                            Sleep(200);
                            system("cls");
                            break;

                        case 0:
                            cout << "Cikis yapiliyor...\n";
                            Sleep(500);
                            system("cls");
                            break;

                        default:
                            cout << "Gecersiz secim! Tekrar deneyin.\n";
                            Sleep(1000);
                            system("cls");
                        }
                    } while (personelSecim2 != 0);
                    break;

                case 2:
                    system("cls");
                    int personelSecim3;
                    do {
                        cout << "---KUTUPHANE YONETIM SISTEMI----\n";
                        cout << "--------------------------------\n";
                        cout << "Personel Menusu - Odunc ve Iade Islemleri\n";
                        cout << "1 - Kitap odunc raporunu goster\n";
                        cout << "2 - Kitap iade raporunu goster\n";
                        cout << "3 - Odunc alinabilir kitaplari goster\n";
                        cout << "0 - Cikis\n";
                        cout << "--------------------------------\n";
                        cout << "Seciminizi girin: ";
                        cin >> personelSecim3;

                        switch (personelSecim3) {
                        case 1:
                            oduncRaporuGoster(tekYonluListe);

                            int cikmakIcin10;
                            do {
                                cout << "Listeden cikmak icin 0'i tuslayin ";
                                cin >> cikmakIcin10;
                                if (cikmakIcin10 == 0) {
                                    break;
                                }
                            } while (cikmakIcin10 != 0);
                            Sleep(200);
                            system("cls");
                            break;

                        case 2:
                            iadeRaporuGoster(tekYonluListe);

                            int cikmakIcin11;
                            do {
                                cout << "Listeden cikmak icin 0'i tuslayin ";
                                cin >> cikmakIcin11;
                                if (cikmakIcin11 == 0) {
                                    break;
                                }
                            } while (cikmakIcin11 != 0);
                            Sleep(200);
                            system("cls");
                            break;

                        case 3:
                            erisilebilirKitaplariGoster(tekYonluListe);

                            int cikmakIcin12;
                            do {
                                cout << "Listeden cikmak icin 0'i tuslayin ";
                                cin >> cikmakIcin12;
                                if (cikmakIcin12 == 0) {
                                    break;
                                }
                            } while (cikmakIcin12 != 0);
                            Sleep(200);
                            system("cls");
                            break;

                        case 0:
                            cout << "Cikis yapiliyor...\n";
                            Sleep(500);
                            system("cls");
                            break;

                        default:
                            cout << "Gecersiz secim! Tekrar deneyin.\n";
                            Sleep(1000);
                            system("cls");
                        }
                    } while (personelSecim3 != 0);
                    break;

                case 3:
                    talepYonetimi(tekYonluListe);
                    break;

                case 4:
                    personelAgacRaporlari(tekYonluListe);
                    break;

                case 5:
                    personelHashIslemleri();
                    break;

                case 0:
                    cout << "Cikis yapiliyor...\n";
                    Sleep(500);
                    system("cls");
                    break;

                default:
                    cout << "Gecersiz secim! Tekrar deneyin.\n";
                    Sleep(1000);
                    system("cls");
                }
            } while (personelSecim1 != 0);
            break;

        case 2:
            system("cls");
            ciftYonluListe = tekYonludenCiftYonluDairesele(tekYonluListe);
            int kullaniciSecim1;
            do {
                cout << "---KUTUPHANE YONETIM SISTEMI----\n";
                cout << "--------------------------------\n";
                cout << "Kullanici Menusu\n";
                cout << "1 - Koleksiyon Yonetimi\n";
                cout << "2 - Odunc ve Iade Islemleri\n";
                cout << "3 - Talep ve Oneri\n";
                cout << "4 - Kesfet\n";
                cout << "5 - Degerlendirme\n";
                cout << "0 - Cikis\n";
                cout << "--------------------------------\n";
                cout << "Seciminizi girin: ";
                cin >> kullaniciSecim1;
                cin.ignore();

                switch (kullaniciSecim1) {
                case 1:
                    system("cls");
                    int kullaniciSecim2;
                    do {
                        cout << "---KUTUPHANE YONETIM SISTEMI----\n";
                        cout << "--------------------------------\n";
                        cout << "Kullanici Menusu - Koleksiyon Yonetimi\n";
                        cout << "1 - Kitaba yorum ekle\n";
                        cout << "2 - Kitabin yorumlarini goster\n";
                        cout << "3 - Koleksiyon olustur\n";
                        cout << "4 - Koleksiyona kitap ekle\n";
                        cout << "5 - Okuma durumunu guncelle\n";
                        cout << "6 - Koleksiyondan kitap sil\n";
                        cout << "7 - Koleksiyonu goruntule\n";
                        cout << "0 - Cikis\n";
                        cout << "--------------------------------\n";
                        cout << "Seciminizi girin: ";
                        cin >> kullaniciSecim2;
                        cin.ignore();

                        switch (kullaniciSecim2) {
                        case 1:
                            kitapYorumEkle(ciftYonluListe);
                            Sleep(1000);
                            system("cls");
                            break;

                        case 2:
                            kitapYorumlariListele(ciftYonluListe);

                            int cikmakIcin6;
                            do {
                                cout << "Listeden cikmak icin 0'i tuslayin ";
                                cin >> cikmakIcin6;
                                if (cikmakIcin6 == 0) {
                                    break;
                                }
                            } while (cikmakIcin6 != 0);
                            Sleep(200);
                            system("cls");
                            break;

                        case 3: 
                            koleksiyonOlustur();
                            Sleep(1000);
                            system("cls");
                            break;

                        case 4: 
                            koleksiyonaKitapEkle(ciftYonluListe);
                            Sleep(1000);
                            system("cls");
                            break;

                        case 5: 
                            okunmaDurumuGuncelle();
                            Sleep(1000);
                            system("cls");
                            break;

                        case 6: 
                            koleksiyondanKitapSil();
                            Sleep(1000);
                            system("cls");
                            break;

                        case 7: 
                            koleksiyonuListele();

                            int cikmakIcin7;
                            do {
                                cout << "Listeden cikmak icin 0'i tuslayin ";
                                cin >> cikmakIcin7;
                                if (cikmakIcin7 == 0) {
                                    break;
                                }
                            } while (cikmakIcin7 != 0);
                            Sleep(200);
                            system("cls");
                            break;

                        case 0:
                            cout << "Cikis yapiliyor...\n";
                            Sleep(500);
                            system("cls");
                            break;
                        default:
                            cout << "Gecersiz secim! Tekrar deneyin.\n";
                            Sleep(1000);
                            system("cls");
                        }

                    } while (kullaniciSecim2 != 0);
                    break;

                case 2:
                    system("cls");
                    int kullaniciSecim3;
                    do {
                        cout << "---KUTUPHANE YONETIM SISTEMI----\n";
                        cout << "--------------------------------\n";
                        cout << "Kullanici Menusu - Odunc ve Iade Islemleri\n";
                        cout << "1 - Kitap odunc al\n";
                        cout << "2 - Odunc alinanlari listele\n";
                        cout << "3 - Kitap iade et\n";
                        cout << "4 - Iade edilenleri goruntule\n";
                        cout << "0 - Cikis\n";
                        cout << "--------------------------------\n";
                        cout << "Seciminizi girin: ";
                        cin >> kullaniciSecim3;

                        switch (kullaniciSecim3) {
                        case 1: 
                            kitapOduncAl(tekYonluListe); 
                            Sleep(1000);
                            system("cls");
                            break;

                        case 2:
                            oduncAlinanlariListele(tekYonluListe);

                            int cikmakIcin8;
                            do {
                                cout << "Listeden cikmak icin 0'i tuslayin ";
                                cin >> cikmakIcin8;
                                if (cikmakIcin8 == 0) {
                                    break;
                                }
                            } while (cikmakIcin8 != 0);
                            Sleep(200);
                            system("cls");
                            break;

                        case 3: 
                            kitapIadeEt(tekYonluListe); 
                            Sleep(1000);
                            system("cls");
                            break;

                        case 4: 
                            iadeEdilenleriListele(tekYonluListe); 

                            int cikmakIcin9;
                            do {
                                cout << "Listeden cikmak icin 0'i tuslayin ";
                                cin >> cikmakIcin9;
                                if (cikmakIcin9 == 0) {
                                    break;
                                }
                            } while (cikmakIcin9 != 0);
                            Sleep(200);
                            system("cls");
                            break;

                        case 0:
                            cout << "Cikis yapiliyor...\n";
                            Sleep(500);
                            system("cls");
                            break;

                        default:
                            cout << "Gecersiz secim! Tekrar deneyin.\n";
                            Sleep(1000);
                            system("cls");
                        }
                    } while (kullaniciSecim3 != 0);
                    break;

                case 3:
                    system("cls");
                    int kullaniciSecim4;
                    do {
                        cout << "---KUTUPHANE YONETIM SISTEMI----\n";
                        cout << "--------------------------------\n";
                        cout << "Kullanici Menusu - Talep ve Oneri\n";
                        cout << "1 - Kitap talep et\n";
                        cout << "2 - Talepleri yazdir\n";
                        cout << "3 - Akademik talep et\n";
                        cout << "0 - Cikis\n";
                        cout << "--------------------------------\n";
                        cout << "Seciminizi girin: ";
                        cin >> kullaniciSecim4;
                        cin.ignore();

                        switch (kullaniciSecim4) {
                        case 1:
                            talepEkle();
                            Sleep(1000);
                            system("cls");
                            break;

                        case 2:
                            talepleriListele();

                            int cikmakIcin14;
                            do {
                                cout << "Listeden cikmak icin 0'i tuslayin ";
                                cin >> cikmakIcin14;
                                if (cikmakIcin14 == 0) {
                                    break;
                                }
                            } while (cikmakIcin14 != 0);
                            Sleep(200);
                            system("cls");
                            break;

                        case 3:
                            akademikTalepEkle();
                            Sleep(1000);
                            system("cls");
                            break;

                        case 0:
                            cout << "Cikis yapiliyor...\n";
                            Sleep(500);
                            system("cls");
                            break;

                        default:
                            cout << "Gecersiz secim! Tekrar deneyin.\n";
                            Sleep(1000);
                            system("cls");
                        }
                    } while (kullaniciSecim4 != 0);
                    break;
                    break;

                case 4:
                    kullaniciAgacRaporlari();
                    break;

                case 5:
                    kullaniciHashIslemleri(tekYonluListe);
                    break;

                case 0:
                    cout << "Cikis yapiliyor...\n";
                    Sleep(500);
                    system("cls");
                    break;

                default:
                    cout << "Gecersiz secim! Tekrar deneyin.\n";
                    Sleep(1000);
                    system("cls");
                }

            } while (kullaniciSecim1 != 0);
            break;

        case 0:
            cout << "Cikis yapiliyor...\n";
            Sleep(500);
            system("cls");
            break;
        default:
            cout << "Gecersiz secim! Tekrar deneyin.\n";
            Sleep(1000);
            system("cls");
        }
    } while (secim != 0);

    return 0;
}