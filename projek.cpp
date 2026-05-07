#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

// ================= STRUCT =================

struct Menu{
    string nama;
    int harga;
};

struct Driver{
    string nama;
    bool tersedia;
};

struct Pesanan{
    string namaMenu;
    int jumlah;
    int total;
    string driver;
};

// ================= ARRAY =================

Menu menu[100];
Driver driver[100];
Pesanan pesanan[100];

int jumlahMenu = 0;
int jumlahDriver = 0;
int jumlahPesanan = 0;

// ================= FUNCTION =================

// tampil menu
void tampilMenu(Menu *menuPointer){

    cout << "\n=== DAFTAR MENU ===\n";

    cout << left << setw(5) << "No"
         << setw(20) << "Menu"
         << setw(10) << "Harga" << endl;

    for(int i = 0; i < jumlahMenu; i++){

        cout << left << setw(5) << i+1
             << setw(20) << (menuPointer+i)->nama
             << setw(10) << (menuPointer+i)->harga
             << endl;
    }
}

// tampil driver
void tampilDriver(){

    cout << "\n=== DATA DRIVER ===\n";

    for(int i = 0; i < jumlahDriver; i++){

        cout << i+1 << ". "
             << driver[i].nama
             << " - ";

        if(driver[i].tersedia == true){
            cout << "Tersedia";
        }
        else{
            cout << "Tidak Tersedia";
        }

        cout << endl;
    }
}

// searching non sentinel
void cariMenu(string key){

    bool ketemu = false;

    for(int i = 0; i < jumlahMenu; i++){

        if(menu[i].nama == key){

            cout << "\nMenu ditemukan!\n";
            cout << "Nama  : " << menu[i].nama << endl;
            cout << "Harga : " << menu[i].harga << endl;

            ketemu = true;
        }
    }

    if(ketemu == false){
        cout << "\nMenu tidak ditemukan!\n";
    }
}

// cari driver tersedia
bool cariDriver(int &indexDriver){

    bool ketemu = false;

    for(int i = 0; i < jumlahDriver; i++){

        if(driver[i].tersedia == true){

            indexDriver = i;
            ketemu = true;
            break;
        }
    }

    return ketemu;
}

// rekursif total harga
int hitungTotal(int harga, int jumlah){

    if(jumlah == 1){
        return harga;
    }

    return harga + hitungTotal(harga, jumlah - 1);
}

// sorting bubble sort
void sortingHarga(){

    for(int i = 0; i < jumlahMenu - 1; i++){

        for(int j = 0; j < jumlahMenu - i - 1; j++){

            if(menu[j].harga > menu[j+1].harga){

                Menu temp;

                temp = menu[j];
                menu[j] = menu[j+1];
                menu[j+1] = temp;
            }
        }
    }

    cout << "\nMenu berhasil diurutkan berdasarkan harga!\n";
}

// pesan makanan
void pesanMakanan(){

    int pilih, jumlah;
    int indexDriver;
    char tambah;

    int totalSemua = 0;

    string daftarMenu = "";
    string struk = "";

    if(cariDriver(indexDriver) == true){

        do{

            system("cls");

            cout << "========== STRUK PESANAN ==========\n";
            cout << struk;

            cout << "\nTotal Sementara : " << totalSemua << endl;

            tampilMenu(menu);

            cout << "\nPilih menu : ";
            cin >> pilih;

            cout << "Jumlah beli : ";
            cin >> jumlah;

            int total = hitungTotal(menu[pilih-1].harga, jumlah);

            totalSemua = totalSemua + total;

            // simpan tampilan struk
            struk = struk +
                    menu[pilih-1].nama +
                    " x" +
                    to_string(jumlah) +
                    " = " +
                    to_string(total) +
                    "\n";

            // simpan untuk riwayat
            daftarMenu = daftarMenu +
                          menu[pilih-1].nama +
                          " x" +
                          to_string(jumlah) +
                          ", ";

            cout << "\nTambah menu lagi? (y/n) : ";
            cin >> tambah;

        }while(tambah == 'y' || tambah == 'Y');

        system("cls");

        // simpan data
        pesanan[jumlahPesanan].namaMenu = daftarMenu;
        pesanan[jumlahPesanan].jumlah = 1;
        pesanan[jumlahPesanan].total = totalSemua;
        pesanan[jumlahPesanan].driver = driver[indexDriver].nama;

        driver[indexDriver].tersedia = false;

        jumlahPesanan++;

        cout << "========== STRUK AKHIR ==========\n";

        cout << struk;

        cout << "-------------------------------\n";
        cout << "Total Harga : " << totalSemua << endl;
        cout << "Driver      : " << driver[indexDriver].nama << endl;
        cout << "-------------------------------\n";

        cout << "\nPesanan berhasil!\n";
    }
    else{
        cout << "\nDriver tidak tersedia!\n";
    }
}

// tampil riwayat
void tampilPesanan(){

    cout << "\n=== RIWAYAT PESANAN ===\n";

    for(int i = 0; i < jumlahPesanan; i++){

        cout << i+1 << ". "
             << pesanan[i].namaMenu
             << " | Jumlah : " << pesanan[i].jumlah
             << " | Total : " << pesanan[i].total
             << " | Driver : " << pesanan[i].driver
             << endl;
    }
}

// simpan file
void simpanFile(){

    ofstream file("riwayat.txt");

    for(int i = 0; i < jumlahPesanan; i++){

        file << "Pesanan : " << pesanan[i].namaMenu << endl;
		file << "Total   : " << pesanan[i].total << endl;
		file << "Driver  : " << pesanan[i].driver << endl;
		file << "----------------------" << endl;
    }

    file.close();

    cout << "\nData berhasil disimpan ke file!\n";
}

bool kembaliMenu(){

    char pilih;

    cout << "\nKembali ke menu utama? (y/n) : ";
    cin >> pilih;

    if(pilih == 'y' || pilih == 'Y'){
        return true;
    }
    else{
        cout << "\nProgram keluar...\n";
        return false;
    }
}

// ================= MAIN =================

int main(){
	bool ulang = true;

    // data menu
    menu[0] = {"Seblak", 12000};
    menu[1] = {"Dimsum Mentai", 10000};
    menu[2] = {"Kebab", 15000};
    menu[3] = {"Butterscotch", 15000};
    menu[4] = {"Americano", 15000};

    jumlahMenu = 4;

    // data driver
    driver[0] = {"Budi", true};
    driver[1] = {"Andi", true};
    driver[2] = {"Rian", true};

    jumlahDriver = 3;

    int pilih;
    string cari;

    do{

        cout << "\n========== MINI GOFOOD ==========\n";
        cout << "1. Lihat Menu\n";
        cout << "2. Pesan Makanan\n";
        cout << "3. Cari Menu\n";
        cout << "4. Sorting Harga\n";
        cout << "5. Lihat Driver\n";
        cout << "6. Riwayat Pesanan\n";
        cout << "7. Simpan File\n";
        cout << "8. Keluar\n";

        cout << "\nPilih menu : ";
        cin >> pilih;

		system("cls");

        switch(pilih){

            case 1:
                tampilMenu(menu);
                ulang = kembaliMenu();
                break;

            case 2:
                pesanMakanan();
                ulang = kembaliMenu();
                system("cls");
                break;

            case 3:

                cout << "Cari menu : ";
                cin.ignore();
                getline(cin, cari);

                cariMenu(cari);
				ulang = kembaliMenu();
				system("cls");
                break;

            case 4:
                sortingHarga();
                tampilMenu(menu);
                ulang = kembaliMenu();
                system("cls");
                break;

            case 5:
                tampilDriver();
                ulang = kembaliMenu();
                system("cls");
                break;

            case 6:
                tampilPesanan();
                ulang = kembaliMenu();
                system("cls");
                break;

            case 7:
                simpanFile();
                cout << "\n\n";
                ulang = kembaliMenu();
                break;

            case 8:
                cout << "\nProgram keluar...\n";
				ulang = false;
                break;

            default:
                cout << "\nPilihan tidak tersedia!\n";
        }

    }while(ulang == true);

    return 0;
}
