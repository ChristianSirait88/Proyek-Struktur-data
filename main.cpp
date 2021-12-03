#include <iostream>
#include <iomanip>
#include <malloc.h>
#include <string>
#include <cstring>
#include <fstream>
#include <vector>

using namespace std;

typedef struct typestack_sampah *typeptr_sampah; // linked list untuk oprasi stack sampah
typedef struct typequeue *typeptr_que; // Linked List untuk oprasi queue
typedef struct typestack *typestck; // Linked List untuk oprasi stack
typedef struct typenode *typeptr; // Linked List
fstream file;
//deklarasi struck linked list
struct typenode {
    int id_kurir;
    char nama_kurir[100]; //penggunaan array untuk char
    char no_kendaraan[8]; //penggunaan array untuk char
    typeptr next;
};
struct typestack { // deklarasi linked list untuk oprasi stack
    char nama_barang[100]; //penggunaan array untuk char
    typestck next_stck;
};
struct typequeue { // deklarasi linked list untuk oprasi queue
    int que;
    typeptr_que next_que;
};
struct typestack_sampah { //deklarasi linked list untuk oprasi stack sampah
    char sampah[100];
    typeptr_sampah next_sampah;
};

int batas(string nama_file, int jumlah_atribut) { // fungsi untuk menghitung jumlah data dalam suatu file
    int jumlah = 0;
    string baris;
    file.open(nama_file, ios::in);
    while (getline(file, baris)) {
        jumlah++;
    }
    file.close();
    return jumlah / jumlah_atribut;
}
// deklarasi pointer dan vektor 
typeptr awal, akhir;
typestck awal_stack, akhir_stack;
typeptr_que qdepan, qbelakang;
typeptr_sampah awalsampah, akhirsampah;
vector<typenode> v_kurir;
vector<typestack> v_barang;
vector<typequeue> v_antrian;
vector<typestack_sampah> v_sampah;

//fungsi-fungsi
void pop();

void sisip_data(int IB, char IB2[100], char IB3[8]); // fungsi sisip data ke linked list

void push(char IB[100]);//fungsi push stack

void buat_stack(); //fungsi untuk membuat stack kosong

void cetak_stack(); // fungsi untuk mencetak stack

void buat_list(); //fungsi untuk membuat list

void cetak_list(); // fungsi untuk mencetak list

bool stack_kosong(); // fungsi untuk mengetahui apakah stack kosong atau tidak

void hapus_data(int IH); // fungsi untuk menghapus data pada linked list dan queue

void buatqueue(); //fungsi untuk membuat queue

void cetakqueue(); // fungsi untuk mencetak queue

void dequeue(); // fungsi untuk menghapus queue

int queuekosong(); // fungsi untuk mengecek apakah queue kosong atau tidak

void enqueue(int IB); // fungsi untuk memasukan data pada queue

void sampah(); // fungsi untuk memasukan data pada stack sampah

void cetak_sampah(); // fungsi untuk mencetak stack sampah

void buat_stack_sampah(); // fungsi untuk membuat stack sampah

bool listkosong(); // fungsi untuk mengetahui apakah list kosong atau tidak

bool carikurir(int id); // fungsi untuk mencari kurir pada linked list

bool cariqueue(int id); // fungsi untuk mencari antrian pada queue

void read(); // fungsi untuk membaca file

void trunc_kurir() {
    // oprasi file untuk pendataan kurir
    typeptr bantu = awal;
    file.open("kurir.txt", ios::out | ios::trunc);
    while (bantu != nullptr) {
        file << bantu->id_kurir << endl;
        file << bantu->nama_kurir << endl;
        file << bantu->no_kendaraan << endl;
        bantu = bantu->next;
    }
    file.close();
}

void trunc_antrian() {
    // oprasi file untuk antrian
    typeptr_que qbantu = qdepan;
    file.open("antrian.txt", ios::out | ios::trunc);
    while (qbantu != nullptr) {
        file << qbantu->que << endl; // error
        qbantu = qbantu->next_que;
    }
    file.close();
}

void trunc_barang() {
    // oprasi file untuk pendataan barang
    typestck bantu = awal_stack;
    file.open("barang.txt", ios::out | ios::trunc);
    while (bantu != nullptr) {
        file << bantu->nama_barang << endl;
        bantu = bantu->next_stck;
    }
    file.close();
}

void trunc_sampah() {
    // oprasi file untuk pendataan barang yang sudah diambil
    typeptr_sampah bantu = awalsampah;
    file.open("sampah.txt", ios::out | ios::trunc);
    while (bantu != nullptr) {
        file << bantu->sampah << endl;
        bantu = bantu->next_sampah;
    }
    file.close();
}

void tambah_sampah(char sampah[100]) {
    // operasi untuk menambah isi pada stack sampah
    typeptr_sampah sampah_baru;
    typeptr_sampah bantu;
    sampah_baru = new typestack_sampah;
    strcpy(sampah_baru->sampah, sampah);
    if (awalsampah == nullptr) {
        awalsampah = sampah_baru;
        akhirsampah = awalsampah;
    } else {

        bantu = awalsampah;
        sampah_baru->next_sampah = bantu;
        awalsampah = sampah_baru;
    }
}

void tambah_ke_program() {
    // oprasi untuk memasukan data dari file ke list/ queue/ stack yanga ada
    for (auto &i: v_kurir) {
        sisip_data(i.id_kurir, i.nama_kurir, i.no_kendaraan);
    }

    for (int i = v_barang.size() - 1; i >= 0; --i) {
        push(v_barang.at(i).nama_barang);
    }

    for (auto &i: v_antrian) {
        enqueue(i.que);
    }

    for (int i = v_sampah.size() - 1; i >= 0; --i) {
        tambah_sampah(v_sampah.at(i).sampah);
    }
}

int main() {
    //deklarasi Variabel
    int pilihan_barang, pilihan_menu, jumlah_barang, id_kurir, hapus_id;
    char nama_kurir[100], no_kendaraan[8], nama_barang[100];
    char pilihan_hapus, pilihan_pop;
    char pilihan_ulang;
    //pemangilan Fungsi
    buat_list();
    buat_stack();
    buat_stack_sampah();
    buatqueue();
    read();
    tambah_ke_program();
    do {
        cout << "---- Pendataan Kurir Gudang XYZ ----" << endl;
        cout << "Menu\n";
        cout << "1. Pendataan Kurir\n";             // linked List & queue
        cout << "2. Data dan Penginputan Barang\n"; // Push Stack
        cout << "3. Pengambilan Barang\n";          // pop stack
        cout << "4. Riwayat Pengambilan Barang\n";  // sampah
        cout << "5. Exit\n";                        // exit
        cout << "Masukan Pilihan Anda : ";
        cin >> pilihan_menu;
        if (pilihan_menu == 1) {
            system("cls");
            cout << "---- Menu Pendataan Kurir ----\n";
            cout << "1. Penambahan Kurir\n";
            cout << "2. Daftar Kurir\n";
            cout << "3. Hapus Kurir\n";
            cout << "4. Antrian Kurir\n";
            cout << "Masukkan Pilihan Anda : ";
            cin >> pilihan_menu;
            if (pilihan_menu == 1) {
                // menu untuk menambahkan kurir dengan linked list
                system("cls");
                cout << "------ Penambahan Kurir ------\n";
                int jumlah_kurir;
                cout << "Jumlah Kurir yang Ditambahkan: ";
                cin >> jumlah_kurir;
                // looping untuk menentukan jumlah kurir yang akan dilakukan
                for (int i = 0; i < jumlah_kurir; ++i) { // memulai looping
                    cout << "- Penambahan ke-" << i + 1 << endl;  
                    cout << "  Masukan ID Kurir: ";
                    cin >> id_kurir;
                    cin.ignore();
                    cout << "  Masukan Nama Kurir: ";
                    cin.getline(nama_kurir, 100);
                    cout << "  Masukan No Kendaraan: ";
                    cin.getline(no_kendaraan, 8);
                    sisip_data(id_kurir, nama_kurir, no_kendaraan); // memasukan data ke linked list
                    enqueue(id_kurir); // memasukan data ke queue
                }
                cout << "Penambahan Kurir Berhasil\n";
            } else if (pilihan_menu == 2) {
                system("cls");
                cout << "---- Daftar Kurir ----\n";
                //percabangan menngunakan IF
                if (listkosong()) {
                    cout << "- Kurir Kosong\n";
                } else {
                    cetak_list();
                }
            } else if (pilihan_menu == 3) {
                // menu menghapus kurir dengan menggunakan linked list dan seaching
                system("cls");
                cout << "------------ Hapus Kurir ------------\n";
                cout << "Masukkan ID Kurir yang Ingin Dihapus: ";
                cin >> hapus_id;
                cout << "Yakin Untuk Menghapus Data? (Y/n): ";
                cin >> pilihan_hapus;
                if ((pilihan_hapus == 'y' || pilihan_hapus == 'Y') && carikurir(hapus_id)) {
                    hapus_data(hapus_id);
                    cout << "Penghapusan Kurir Berhasil\n";
                } else {
                    cout << "Penghapusan Kurir Gagal\n";
                }
            } else if (pilihan_menu == 4) {
                system("cls");
                cout << "---- Antrian Kurir ----\n";
                if (queuekosong()) { // penggunaan percabangan (jika queue dalam keadaan kosong)
                    cout << "- Antrian Kosong\n";
                } else {
                    cetakqueue();
                }
            }
            cout << "Ulangi Menu? (y/n): ";
            cin >> pilihan_ulang;
        } else if (pilihan_menu == 2) {
            //menu penginputan barang dengan stack
            system("cls");
            cout << "--- Menu Penginputan Barang ---\n";
            cout << "1. Input Barang\n";
            cout << "2. Lihat Barang\n";
            cout << "Pilihan Menu : ";
            cin >> pilihan_barang;;
            if (pilihan_barang == 1) {
                system("cls");
                cout << "--------- Input Barang ---------\n";
                cout << "Berapa Barang Yang Akan Di Data: ";
                cin >> jumlah_barang;
                cin.ignore();
                for (int i = 1; i <= jumlah_barang; i++) { // looping dengan for (looping akan berjalan selama jumlah barang lebih kecil atau sama dengan i)
                    cout << "[" << i << "]  Masukan Nama Barang: ";
                    cin.getline(nama_barang, 100);
                    push(nama_barang); // proses push ke stack
                }
                cout << "Penambahan Barang Berhasil\n";
            } else if (pilihan_barang == 2) {
                system("cls");
                cout << "----- Data Barang -----\n";
                if (stack_kosong()) { // percabangan untuk mengecek apakah stack kosong atau tidak
                    cout << "- Barang Kosong\n";
                } else {
                    // fungsi menampilkan stack
                    cetak_stack();
                }
            }
            cout << "Ulangi Menu? (y/n): ";
            cin >> pilihan_ulang;
        } else if (pilihan_menu == 3) {
            //menu 3 pengambilan barang dengan fungsi pop pada stack dan dequeue pada queue
            system("cls");
            cout << "----------- Pengambilan Barang -----------\n";
            cout << "Apakah Anda Ingin Mengambil Barang? (y/n): ";
            cin >> pilihan_pop;
            if ((pilihan_pop == 'y' || pilihan_pop == 'Y') && !queuekosong() && !stack_kosong() && !listkosong()) {
                sampah(); // stack sampah, digunakan untuk merekam barang apa saja yang telah diambil
                pop(); // pop pada stack untuk menghapus barang
                dequeue(); // dequeue untuk menghilangkan elemen pada queue
                cout << "Pengambilan Barang Berhasil\n";
            } else {
                cout << "Pengambilan Barang Gagal\n";
            }
            cout << "Ulangi Menu? (y/n): ";
            cin >> pilihan_ulang;
        } else if (pilihan_menu == 4) {
            //menu 4 untuk melihat barang yang telah diambil
            system("cls");
            cout << "----- Riwayat Pengambilan Barang -----\n";
            if (awalsampah == nullptr) {
                cout << "- Pengambilan Barang Belum Dilakukan\n";
            } else {
                cetak_sampah();
            }
            cout << "Ulangi Menu? (y/n): ";
            cin >> pilihan_ulang;
        } else if (pilihan_menu == 5) {
            cout << "Terima Kasih Telah Menggunakan Program\n";
            break;
        } else {
            cout << "Pilihan Anda Salah, Ulangi Menu? (y/n): ";
            cin >> pilihan_ulang;
            system("cls");
        }
        system("cls");
    } while (pilihan_ulang == 'y');
}

void buat_list() { // fungsi untuk pembuatan linked list dengan node kosong
    typeptr list;
    list = nullptr;
    awal = list;
    akhir = list;
}

void buat_stack() { // fungsi untuk pembuatan stack kosong
    typestck NS;
    NS = nullptr;
    awal_stack = NS;
    akhir_stack = NS;
}

bool stack_kosong() { // fungsi untuk mengecek stack kosong
    if (awal_stack == nullptr) {
        return true;
    } else {
        return false;
    }
}


void push(char IB[100]) { // fungsi untuk melakukan push / penginputan ke dalam stack
    typestck NS;
    typestck bantu;
    NS = new typestack;
    strcpy(NS->nama_barang, IB);

    if (awal_stack == nullptr) {
        awal_stack = NS;
    } else { // stack akan dimasukan dari depan 
        bantu = awal_stack;
        NS->next_stck = bantu;
        awal_stack = NS;
    }
    // oprasi file pada queue
    trunc_barang();
}

void pop() { // fungsi pop untuk mengeluarkan isi dari stack
    typestck bantu = awal_stack;
    if (awal_stack == akhir_stack) {
        awal_stack = nullptr;
    } else {
        awal_stack = awal_stack->next_stck;
        delete bantu;
    }
    // opreasi file pada pop
    trunc_barang();
}

void cetak_stack() {
    // fungsi untuk mencetak stack
    typestck bantu = awal_stack;
    int i = 1;
    while (bantu != NULL) {
        cout << "[" << i << "] " << bantu->nama_barang << endl;
        bantu = bantu->next_stck;
        i++;
    }
}

void sisip_data(int IB, char IB2[100], char IB3[8]) { // fungsi untuk memasukan data pada linked list
    typeptr NB;
    NB = new typenode;
    NB->id_kurir = IB;
    strcpy(NB->nama_kurir, IB2);
    strcpy(NB->no_kendaraan, IB3);
    if (awal == nullptr) {
        awal = NB;
        akhir = NB;
        awal->next = NULL;
    } else {
        akhir->next = NB;

    }
    akhir = NB;
    akhir->next = NULL;

    trunc_kurir();
}

void cetak_list() { // fungsi untuk mencetak linked list
    typeptr bantu;
    bantu = awal;
    while (bantu != NULL) {
        cout << "- ID Kurir: " << bantu->id_kurir << endl;
        cout << "  Nama Kurir: " << bantu->nama_kurir << endl;
        cout << "  No Kendaraan: " << bantu->no_kendaraan << endl;
        bantu = bantu->next;
    }
}

void hapus_data(int IH) { // fungsi untuk menghapus data pada linked list dan queue
    bool sukses = false;
    typeptr hapus, bantu;
    // list
    if (awal == nullptr) {
        sukses = false;
        cout << "List masih Kosong" << endl;
    } else if (IH == awal->id_kurir) {
        sukses = true;
        hapus = awal;
        awal = hapus->next;
        free(hapus);
    } else if (IH == akhir->id_kurir) {
        sukses = true;
        bantu = awal;
        while (bantu->next->next != nullptr) {
            bantu = bantu->next;
        }
        hapus = bantu->next;
        bantu->next = nullptr;
        free(hapus);
    } else {
        sukses = true;
        bantu = awal;
        while (IH != bantu->next->id_kurir && bantu->next->next != nullptr) {
            bantu = bantu->next;

        }
        if (IH != bantu->next->id_kurir) {
            cout << "Data Tidak Ditemukan\n";
        } else {
            hapus = bantu->next;
            bantu->next = hapus->next;
            free(hapus);
        }
    }

    // queue
    typeptr_que qbantu = qdepan, hapusqueue = nullptr;
    if (qdepan == nullptr) {
        sukses = false;
        cout << "Antrian kosong\n";
    } else if (qdepan->que == IH) {
        sukses = true;
        hapusqueue = qdepan;
        qdepan = qdepan->next_que;
        free(hapusqueue);
    } else if (qbelakang->que == IH) {
        sukses = true;
        qbantu = qdepan;
        while (qbantu->next_que != qbelakang) {
            qbantu = qbantu->next_que;
        }
        hapusqueue = qbantu->next_que;
        qbelakang = qbantu;
        free(hapusqueue);
    } else {
        sukses = true;
        qbantu = qdepan;
        while (IH != qbantu->next_que->que && qbantu->next_que->next_que != nullptr) {
            qbantu = qbantu->next_que;
        }
        hapusqueue = qbantu->next_que;
        qbantu->next_que = hapusqueue->next_que;
        free(hapusqueue);
    }
    // sampe sini
    if (sukses) {
        //opreasi file pada linked list dan queue
        trunc_kurir();
        trunc_antrian();
    }
}

void buatqueue() { // fungsi untuk membuat queue kosong
    qdepan = nullptr;
    qbelakang = qdepan;
}

int queuekosong() { // fungsi untuk mengecek apakah queue kosong atau tidak
    if (qdepan == NULL) {
        return (1);
    } else {
        return (0);
    }
}


void cetakqueue() { // fungsi untuk mencetak queue
    typeptr_que bantu_que;
    bantu_que = qdepan;
    int i = 1;
    do {
        cout << "[" << i << "] ID Kurir: " << bantu_que->que << endl;
        bantu_que = bantu_que->next_que;
        i++;
    } while (bantu_que != NULL);
}

void enqueue(int IB) { // fungsi untuk menginput data pada queue
    file.close();
    typeptr_que NB;
    NB = new typequeue;
    NB->que = IB;
    if (qdepan == NULL) {
        qdepan = NB;
        qbelakang = qdepan;
    } else {
        qbelakang->next_que = NB;
    }
    qbelakang = NB;
    qbelakang->next_que = NULL;
    //opreasi file pada enqueue
    trunc_antrian();
}

void dequeue() { // fungsi untuk mengeluarkan data pada queue
    typeptr_que hapus;
    if (queuekosong()) {
        cout << "Antrian masih kosong !";
    } else {
        hapus = qdepan;
        qdepan = hapus->next_que;
        free(hapus);
    }
    //opreasi file pada dequeue
    trunc_antrian();
}

void buat_stack_sampah() { // fungsi untuk membuat stack kedua stack sampah
    typeptr_sampah NS;
    NS = nullptr;
    awalsampah = NS;
    akhirsampah = NS;;
}

void cetak_sampah() { // fungsi untuk mencetak stack sampah
    int i = 1;
    typeptr_sampah depan = nullptr, bantu = nullptr;
    if (awalsampah == akhirsampah) {
        cout << "[" << i << "] " << awalsampah->sampah << endl;
    } else {
        depan = awalsampah;
        awalsampah = akhirsampah;
        do {
            bantu = depan;
            while (bantu->next_sampah != akhirsampah) {
                bantu = bantu->next_sampah;
            }
            akhirsampah->next_sampah = bantu;
            akhirsampah = bantu;
        } while (akhirsampah != depan);
        akhirsampah->next_sampah = NULL;
        bantu = awalsampah;
        while (bantu != NULL) {
            cout << "[" << i << "] " << bantu->sampah << endl;
            bantu = bantu->next_sampah;
            i++;
        }
    }
}

void sampah() { // fungsi untuk memasukan nilai pada stack sampah
    typeptr_sampah NS, bantu = nullptr;
    NS = new typestack_sampah;
    strcpy(NS->sampah, awal_stack->nama_barang); // nilai NS akan sama dengan Nilai akhirstack
    if (awalsampah == nullptr) {
        awalsampah = NS;
        akhirsampah = awalsampah;
    } else {
        bantu = awalsampah;
    }
    NS->next_sampah = bantu;
    awalsampah = NS;

    trunc_sampah();
}

bool listkosong() {
    return awal == nullptr;
}

bool carikurir(int id) { // fungsi seaching pada kurir menggunakan sequential seaching
    typeptr bantu = awal;
    while (bantu != nullptr) {
        if (bantu->id_kurir == id) {
            return true;
        }
        bantu = bantu->next;
    }
    return false;
}

bool cariqueue(int id) { // fungsi seaching pada queue menggunakan sequential seaching
    typeptr_que bantu = qdepan;
    while (bantu != nullptr) {
        if (bantu->next_que->que == id) {
            return true;
        }
        bantu = bantu->next_que;
    }
    return false;
}

void read() { // fungsi untuk membaca file dan menginputkannya ke dalam list/queue/ stack
    int temp;
    string escape, nama_kurir, no_kendaraan, nama_barang;
    int nilai;

    // baca file kurir.txt
    nilai = batas("kurir.txt", 3);
    typenode node_kurir{};
    file.open("kurir.txt", ios::in); //membuka file kurir.txt
    if (nilai != 0) {
        for (int i = 0; i < nilai; i++) { //pengulangan untuk me load data dilakukan sampai end of file (datanya habis)
            file >> node_kurir.id_kurir; //masukkan data yang sudah di load ke variabel temporary
            getline(file, escape);
            getline(file, nama_kurir);
            getline(file, no_kendaraan);
            strcpy(node_kurir.nama_kurir, nama_kurir.c_str());
            strcpy(node_kurir.no_kendaraan, no_kendaraan.c_str());
            v_kurir.push_back(node_kurir);
        }
    }
    file.close(); //menutup file txt

    // baca file barang.txt
    typestack node_barang{};
    nilai = batas("barang.txt", 1);
    file.open("barang.txt", ios::in);
    if (nilai != 0) {
        for (int i = 0; i < nilai; ++i) {
            getline(file, nama_barang);
            strcpy(node_barang.nama_barang, nama_barang.c_str());
            v_barang.push_back(node_barang);
        }
    }
    file.close();

    typequeue node_antrian{};
    // baca file antrian.txt
    nilai = batas("antrian.txt", 1);

    file.open("antrian.txt", ios::in);
    if (nilai != 0) {
        for (int i = 0; i < nilai; ++i) {
            file >> node_antrian.que;
            v_antrian.push_back(node_antrian);
        }
    }
    file.close();

    typestack_sampah node_sampah{};
    // baca file sampah.txt
    nilai = batas("sampah.txt", 1);
    file.open("sampah.txt");
    if (nilai != 0) {
        for (int i = 0; i < nilai; ++i) {
            getline(file, nama_barang);
            strcpy(node_sampah.sampah, nama_barang.c_str());
            v_sampah.push_back(node_sampah);
        }
    }
    file.close();
}