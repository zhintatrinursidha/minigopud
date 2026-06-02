#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

struct Menu{
    string nama;
    int harga;
};
Menu menu[100];
int jumlahMenu = 0;

struct Driver{
    string nama;
    bool tersedia;
};
Driver driver[100];
int jumlahDriver = 0;

struct Pesanan{
    string namaMenu;
    int total;
    string driver;
};
Pesanan pesanan[100];
int jumlahPesanan = 0;

void tampilMenu(){
	
	if(jumlahMenu == 0){
        cout << "\nBelum ada menu tersedia!\n";
        return;
    } else {
		cout << "\n======== DAFTAR MENU ========\n";
		cout << left << setw(5) << "No"
			 << setw(20) << "Menu"
			 << setw(10) << "Harga" << endl;
		for(int i = 0; i < jumlahMenu; i++){
			cout << left << setw(5) << i+1
				 << setw(20) << menu[i].nama
				 << setw(10) << menu[i].harga
				 << endl;
		}
	}
    cout << "\n=============================\n";
}

void tampilDriver(){
	
	if(jumlahDriver == 0){
		cout << "\nBelum ada driver tersedia!\n";
		return;
	} else {	
		cout << "\n======== DATA DRIVER ========\n";
		for(int i = 0; i < jumlahDriver; i++){
			cout << i+1 << ". "
				 << driver[i].nama
				 << " - ";
			if(driver[i].tersedia){
				cout << "Tersedia";
			} else {
				cout << "Tidak Tersedia";
			}
			cout << endl;
		}
		cout << "\n=============================\n";
	}
}

void tampilPesanan(){
	
	if(jumlahPesanan == 0){
		cout << "\nBelum ada pesanan!\n";
		return;
	} else {
		cout << "\n======== RIWAYAT PESANAN ========\n";
		for(int i = 0; i < jumlahPesanan; i++){
			cout << i+1 << ". "
				 << pesanan[i].namaMenu
				 << " | Total : " << pesanan[i].total
				 << " | Driver : " << pesanan[i].driver << endl;
		}
	}
	cout << "\n=============================\n";
}

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
    cout << "\n=============================\n";
    if(ketemu == false){
        cout << "\nMenu tidak ditemukan!\n";
    }
    cout << "\n=============================\n";
}

bool cariDriver(int &indexDriver){

    bool ketemu = false;
    for(int i = 0; i < jumlahDriver; i++){

        if(driver[i].tersedia){
            indexDriver = i;
            ketemu = true;
            break;
        }
    }
    return ketemu;
}

int hitungTotal(int harga, int jumlah){

    if(jumlah == 1){
        return harga;
    }
    return harga + hitungTotal(harga, jumlah - 1);
}

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

void bacaMenu(int &total) {
    total = 0;
    ifstream file("menu.txt");
    while(getline(file, menu[total].nama, '|')){
        file >> menu[total].harga;
        file.ignore();
        total++;
    }
    file.close();
    jumlahMenu = total;
}

void bacaDriver(int &total) {
    total = 0;
    ifstream file("driver.txt");
    while(getline(file, driver[total].nama, '|')){
        file >> driver[total].tersedia;
        file.ignore();
        total++;
    }
    file.close();
    jumlahDriver = total;
}

void tambahMenu() {
	char lagi;
		
	do{	
		cin.ignore();
		Menu menuBaru;
		
		system("cls");
		cout << "\nMasukkan menu yang ingin ditambahkan!" << endl;
		cout << "Nama menu : "; 
			getline(cin, menuBaru.nama);
		cout << "Harga     : "; 
			cin >> menuBaru.harga;

		ofstream file("menu.txt", ios::app);
		if(file.is_open()){
			file << menuBaru.nama << "|" 
				 << menuBaru.harga << endl;
			file.close();
		} 
		cout << "\n=============================\n";
		cout << "\nTambah menu lagi? (y/n) : ";
		cout << "\n=============================\n";
			cin >> lagi;
	} while(lagi == 'y' || lagi == 'Y');
	system("cls");
	cout << "\nMenu berhasil ditambahkan!\n";
	cout << "\n=============================\n";
	bacaMenu(jumlahMenu);
}


void hapusMenu() {
    int totalMenu = 0;
    bacaMenu(totalMenu);

    if(totalMenu == 0){
        cout << "Menu kosong, tidak ada yang bisa dihapus." << endl;
        return;
    }

    tampilMenu();
    int nomor;
    cout << "Pilih nomor menu yang ingin dihapus: "; cin >> nomor;

    if(nomor < 1 || nomor > totalMenu){
        cout << "Nomor tidak valid!" << endl;
        return;
    }

    ofstream file("menu.txt", ios::trunc);
    for(int i = 0; i < totalMenu; i++){
        if(i != (nomor - 1)){
            file << menu[i].nama << "|" 
				 << menu[i].harga << endl;
        }
    }
    file.close();
	system("cls");
    cout << "Menu berhasil dihapus!\n";
    cout << "\n=============================\n";
}

void tambahDriver() {
	char lagi;
	
	do{
		cin.ignore();
		Driver driverBaru;

		cout << "Masukkan driver yang ingin ditambahkan!" << endl;
		cout << "Nama driver : "; 
			getline(cin, driverBaru.nama);
		driverBaru.tersedia = true;

		ofstream file("driver.txt", ios::app);
		if(file.is_open()){
			file << driverBaru.nama << "|"
				 << driverBaru.tersedia << endl;
			file.close();
		}
		cout << "\n=============================\n";
		cout << "\nTambah driver lagi? (y/n) : ";
		cout << "\n=============================\n";
			cin >> lagi;
	}while (lagi == 'y' || lagi == 'Y');
	system("cls");
	cout << "\nDriver berhasil ditambahkan!" << endl;
	cout << "\n=============================\n";
	bacaDriver(jumlahDriver);
}

void hapusDriver() {
    int totalDriver = 0;
    bacaDriver(totalDriver);

    if(totalDriver == 0){
        cout << "Driver kosong, tidak ada yang bisa dihapus." << endl;
        return;
    }

    tampilDriver();
    int nomor;
    cout << "\n=============================\n";
    cout << "\nPilih nomor driver yang ingin dihapus: "; cin >> nomor;

    if(nomor < 1 || nomor > totalDriver){
        cout << "Nomor tidak valid!" << endl;
        return;
    }

    ofstream file("driver.txt", ios::trunc);
    for(int i = 0; i < totalDriver; i++){
        if(i != (nomor - 1)){
            file << driver[i].nama << "|"
				 << driver[i].tersedia << endl;
        }
    }
    file.close();
	system("cls");
    cout << "Driver berhasil dihapus!\n";
    cout << "\n=============================\n";
    bacaDriver(jumlahDriver);
}



void ubah_status_driver(){

    int nomor;
    tampilDriver();
    cout << "\nPilih driver : ";
    cin >> nomor;
    driver[nomor-1].tersedia = !driver[nomor-1].tersedia;
    
    ofstream file("driver.txt");
	for(int i = 0; i < jumlahDriver; i++){
		file << driver[i].nama << "|"
			 << driver[i].tersedia << endl;
	}
	file.close();
	system("cls");
    cout << "\nStatus driver berhasil diubah!\n";
    cout << "\n=============================\n";
}

void simpanRiwayat(){

    ofstream file("riwayat.txt", ios::app);

    file << "Pesanan : " << pesanan[jumlahPesanan-1].namaMenu << endl;
    file << "Total   : " << pesanan[jumlahPesanan-1].total << endl;
    file << "Driver  : " << pesanan[jumlahPesanan-1].driver << endl;
    file << "----------------------" << endl;

    file.close();
}

void pesanMakanan(){

    int pilih, jumlah;
    int indexDriver;
    char tambah;
    int totalSemua = 0;
    string daftarMenu = "";
    string struk = "";
    
    if(jumlahMenu == 0){
		cout << "\nBelum ada menu tersedia!\n";
		return;
	}
    
    if(cariDriver(indexDriver)){
       do{
			system("cls");
			tampilMenu();

			cout << "\nPilih menu : ";
			cin >> pilih;

			if(pilih < 1 || pilih > jumlahMenu){
				cout << "Pilihan tidak valid!\n";
			} else {
				cout << "Jumlah beli : ";
				cin >> jumlah;

				if(jumlah < 1){
					cout << "Jumlah tidak valid!\n";
				} else {
					int total = hitungTotal(menu[pilih-1].harga, jumlah);
					totalSemua += total;

					struk += menu[pilih-1].nama + " x" + to_string(jumlah) + " = " + to_string(total) + "\n";
					daftarMenu += menu[pilih-1].nama + " x" + to_string(jumlah) + ", ";
				}
			}

			cout << "\nTambah menu lagi? (y/n) : ";
			cin >> tambah;

		}while(tambah == 'y' || tambah == 'Y');

        system("cls");

        pesanan[jumlahPesanan].namaMenu = daftarMenu;
        pesanan[jumlahPesanan].total = totalSemua;
        pesanan[jumlahPesanan].driver = driver[indexDriver].nama;

        driver[indexDriver].tersedia = false;
		ofstream file("driver.txt");
		for(int i = 0; i < jumlahDriver; i++){
			file << driver[i].nama << "|"
				 << driver[i].tersedia << endl;
		}

		file.close();
		
        jumlahPesanan++;
        simpanRiwayat();
        
        cout << "========== STRUK AKHIR ==========\n";
        cout << struk;
        cout << "-------------------------------\n";
        cout << "Total Harga : " << totalSemua << endl;
        cout << "Driver      : " << driver[indexDriver].nama << endl;
        cout << "-------------------------------\n";
        cout << "\nPesanan berhasil!\n";
    } else {
        cout << "\nDriver tidak tersedia!\n";
        cout << "\n=============================\n";
    }
}

bool kembaliMenu(){

    char pilih;
    cout << "\nKembali ke menu utama? (y/n) : ";
    cin >> pilih;
    if(pilih == 'y' || pilih == 'Y'){
        return true;
    } else {
        cout << "\nProgram keluar...\n";
        return false;
    }
}

int main(){
    system("cls");
    
    bacaMenu(jumlahMenu);
    bacaDriver(jumlahDriver);

    int masuk, m_admin, m_pelanggan;
    string cari, password;
    bool diAdmin, diPelanggan;

    do{
        system("cls");
        cout << "\n========== MINI GO FOOD ==========\n";
        cout << "1. Admin\n";
        cout << "2. Pelanggan\n";
        cout << "3. Keluar\n";
        cout << "Masuk sebagai: ";
        cin >> masuk;

        switch(masuk){
            case 1:
                system("cls");
                cout << "Password Admin : ";
                cin >> password;
                system("cls");

                if(password != "admin123"){
                    cout << "\nPassword Salah!\n";
                    break;
                }
                diAdmin = true;
                while(diAdmin){
                    system("cls");
                    cout << "\n======== MENU ADMIN ========\n";
                    cout << "1. Lihat Menu\n";
                    cout << "2. Tambah Menu\n";
                    cout << "3. Hapus Menu\n";
                    cout << "4. Lihat Driver\n";
                    cout << "5. Tambah Driver\n";
                    cout << "6. Hapus Driver\n";
                    cout << "7. Ubah Status Driver\n";
                    cout << "8. Kembali\n";
                    cout << "Pilih Menu: ";
                    cin >> m_admin;
                    system("cls");

                    switch(m_admin){
                        case 1:
							tampilMenu(); 
                        break;
                        case 2:
							tambahMenu();
							 bacaMenu(jumlahMenu);   
                        break;
                        case 3:
							hapusMenu();  
							 bacaMenu(jumlahMenu);  
                        break;
                        case 4: 
							tampilDriver(); 
							 bacaDriver(jumlahDriver);
                        break;
                        case 5: 
							tambahDriver();
							 bacaDriver(jumlahDriver);
                        break;
                        case 6: 
							hapusDriver();  
                        break;
                        case 7: 
							ubah_status_driver(); 
                        break;
                        case 8: 
							diAdmin = false; 
                        break;
                        default: cout << "Pilihan tidak tersedia!\n";
                        break;
                    }

                    if(diAdmin){ 
                        char balik;
                        cout << "\nKembali ke menu admin? (y/n): ";
                        cin >> balik;
                        if(balik != 'y' && balik != 'Y') 
							diAdmin = false;
                    }
                }
            break;
            case 2:
                system("cls");
                cout << "SELAMAT DATANG!\n";

                diPelanggan = true;
                while(diPelanggan){
					system("cls");
                    cout << "\n======== MENU PELANGGAN ========\n";
                    cout << "1. Lihat Menu\n";
                    cout << "2. Pesan Makanan\n";
                    cout << "3. Cari Menu\n";
                    cout << "4. Sorting Harga\n";
                    cout << "5. Lihat Driver\n";
                    cout << "6. Riwayat Pesanan\n";
                    cout << "7. Kembali\n";
                    cout << "Pilih Menu: ";
                    cin >> m_pelanggan;
                    system("cls");

                    switch(m_pelanggan){
                        case 1:
							tampilMenu();
                        break;
                        case 2:
							pesanMakanan();
						break;
                        case 3:
                            cout << "Cari menu : ";
                            cin.ignore();
                            getline(cin, cari);
                            cariMenu(cari);
                        break;
                        case 4:
                            sortingHarga();
                            tampilMenu();
                        break;
                        case 5:
							tampilDriver();
                        break;
                        case 6: 
							tampilPesanan();
						break;
                        case 7:
							diPelanggan = false; 
						break; 
                        default: 
							cout << "Pilihan tidak tersedia!\n";
                        break;
                    }

                    if(diPelanggan){
                        char balik;
                        cout << "\nKembali ke menu pelanggan? (y/n): ";
                        cin >> balik;
                        if(balik != 'y' && balik != 'Y') 
							diPelanggan = false;
                    }
                }
            break;
            case 3:
				system("cls");
                cout << "==========================================================\n";
                cout << "\nTerima Kasih sudah menggunakan Layanan Mini Go Food Kami!";
                cout << "\nBy : Anis and Zhinta cihuyyyyy\n";
                cout << "==========================================================\n";
                return 0;

            default:
                cout << "Pilihan tidak tersedia!\n";
                break;
        }
    }while(true);
    return 0;
}


