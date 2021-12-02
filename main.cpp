#include <iostream>
#include <malloc.h>
#include <string>
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
int batas() { 
	int awal = 0;
    string baris;
    file.open("kurir.txt",  ios::in);
    while (getline(file, baris)) {
        awal++;
    }
    file.close();
    return awal/3;
}

typeptr awal, akhir;
typestck awal_stack, akhir_stack;
typeptr_que qdepan, qbelakang;
typeptr_sampah awalsampah, akhirsampah;

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

void buatqueue();

void cetakqueue();

void dequeue();

int queuekosong();

void enqueue(int IB);

void sampah();

void cetak_sampah();

void buat_stack_sampah();

bool listkosong(); // fungsi untuk mengetahui apakah list kosong atau tidak

bool carikurir(int id);

bool cariqueue(int id);

void read();

int batas();



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
    cout<<batas();
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
            cout << "---- Pendataan Kurir ----\n";
            cout << "1. Penambahan Kurir\n";
            cout << "2. Daftar Kurir\n";
            cout << "3. Hapus Kurir\n";
            cout<<"Antrian Saat ini : ";
            if (queuekosong()) { // penggunaan percabangan (jika queue dalam keadaan kosong)
                cout << "Antrian masih kosong";
            } else {
                cetakqueue();
            }
            cout<<endl;
            cout << "Masukkan Pilihan Anda : ";
            cin >> pilihan_menu;
            if (pilihan_menu == 1) {
                // menu untuk menambahkan kurir dengan linked list
                system("cls");
                cout << "---- Penambahan Kurir ----\n";
                int jumlah_kurir;
                cout << "Masukkan jumlah kurir yang ingin ditambahkan: ";
                cin >> jumlah_kurir;
                // looping untuk menentukan jumlah kurir yang akan dilakukan
                for (int i = 0; i < jumlah_kurir; ++i) { // memulai looping
                    cout << "Masukan ID Kurir : ";
                    cin >> id_kurir;
                    cin.ignore();
                    cout << "Masukan Nama Kurir : ";
                    cin.getline (nama_kurir,100);
                    cout << "Masukan No Kendaraan : ";
                    cin.getline (no_kendaraan,8);
                    sisip_data(id_kurir, nama_kurir, no_kendaraan); // memasukan data ke linked list
                    enqueue(id_kurir); // memasukan data ke queue
                }
                cout << "Penambahan Kurir Berhasil\n";
            } else if (pilihan_menu == 2) {
                system("cls");
                cout << "---- Daftar Kurir ----\n";
                //percabangan menngunakan IF
                if (listkosong()) {
                    cout << "Kurir masih kosong\n";
                } else {
                    cetak_list();
                }
            } else if (pilihan_menu == 3) {
                // menu menghapus kurir dengan menggunakan linked list dan seaching
                system("cls");
                cout << "---- Hapus Kurir ----\n";
                cout << "Masukkan ID Kurir yang ingin dihapus: ";
                cin >> hapus_id;
                cout << "Apakah Anda Yakin Untuk Mengahapus Data ? (Y/n) : ";
                cin >> pilihan_hapus;
                if ((pilihan_hapus == 'y' || pilihan_hapus == 'Y') && carikurir(id_kurir)) {
                    hapus_data(hapus_id);
                    cout << "Penghapusan kurir berhasil\n";
                    cetakqueue();
                } else {
                    cout << "Penghapusan kurir gagal\n";
                }
            }
            cout << "Apakah Ingin Mengulangi Menu ? (y/n) : ";
            cin >> pilihan_ulang;
        } else if (pilihan_menu == 2) {
            cout << "--- Menu Penginputan Barang ---\n";
            cout << "1. Input Barang\n";
            cout << "2. Lihat Barang\n";
            cout << "Pilihan Menu : ";
            cin >> pilihan_barang;;
            if (pilihan_barang == 1) {
                cout << "Berapa Barang Yang Akan Di Data : ";
                cin >> jumlah_barang;
                cin.ignore();
                for (int i = 1; i <= jumlah_barang; i++) {
                    cout << "Masukan Nama Barang : ";
                    cin.getline(nama_barang,100);
                    push(nama_barang);
                }
            } else if (pilihan_barang == 2) {
                cout << "Data Barang\n";
                cetak_stack();
            }
            cout << "apakah anda ingin mengulang ?(y/n) : ";
            cin >> pilihan_ulang;
        } else if (pilihan_menu == 3) {
            cout << "Apakah Anda Ingin Mengambil Barang (y/n) : ";
            cin >> pilihan_pop;
            if (pilihan_pop == 'y' || pilihan_pop == 'Y') {
                sampah();
                pop();
                dequeue();
            } else {
                cout << "apakah anda ingin mengulang ?(y/n) : ";
                cin >> pilihan_ulang;
            }
            cout << "Apakah Ingin Mengulangi Menu ? (y/n) : ";
            cin >> pilihan_ulang;
        } else if (pilihan_menu == 4) {
            cout << "Barang Yang Sudah Diambil\n";
            cetak_sampah();
            cout << "Apakah Ingin Mengulangi Menu ? (y/n) : ";
            cin >> pilihan_ulang;
        } else if (pilihan_menu == 5) {
            cout << "Terima Kasih Telah Menggunakan Program\n";
            break;
        } else {
            cout << "Pilihan Anda Salah, Apakah Ingin Mengulang ? (y/n) : ";
            cin >> pilihan_ulang;
            system("cls");
        }
    } while (pilihan_ulang == 'y');
}

void buat_list() {
    typeptr list;
    list = nullptr;
    awal = list;
    akhir = list;
}

void buat_stack() {
    typestck NS;
    NS = nullptr;
    awal_stack = NS;
    akhir_stack = NS;
}

bool stack_kosong() {
    if (awal_stack == nullptr) {
        return true;
    } else {
        return false;
    }
}



void push(char IB[100]) {
    file.open("barang.txt", ios::in | ios::app);
    typestck NS;
    typestck bantu;
    NS = new typestack;
    strcpy(NS->nama_barang,IB);

    if (awal_stack == nullptr)
        awal_stack = NS;
    else {
        bantu = awal_stack;
        NS->next_stck = bantu;
        awal_stack = NS;
    }

    file << IB << endl;
    file.close();
}

void pop() {
    file.open("barang.txt", ios::out | ios::trunc);
    typestck bantu = awal_stack;
    if (awal_stack == akhir_stack) {
        awal_stack = nullptr;
    } else {
        awal_stack = awal_stack->next_stck;
        delete bantu;
    }

    bantu = awal_stack;
    
    while (bantu != nullptr) {
        file << bantu->nama_barang << endl;
        bantu = bantu->next_stck;
    }
    file.close();

}

void cetak_stack() {
    file.open("barang.txt",ios::out);
    typestck bantu = awal_stack;
    while (bantu != NULL) {
        cout << bantu->nama_barang << "\n";
        bantu = bantu->next_stck;
    }
    file.close();
}

void sisip_data(int IB, char IB2[100], char IB3[8]) {
    file.open("kurir.txt", ios::in | ios::app);
    typeptr NB;
    NB = new typenode;
    NB->id_kurir = IB;
    strcpy(NB->nama_kurir,IB2);
    strcpy(NB->no_kendaraan,IB3);
    if (awal == nullptr) {
        awal = NB;
        akhir = NB;
        awal->next = NULL;
    } else {
		akhir->next = NB;
		
	}
	akhir=NB;
	akhir->next=NULL;
    
    file << IB << endl;
    file << IB2 << endl;
    file << IB3 << endl;
    file.close();
}

void cetak_list() {
    file.open("kurir.txt",ios::out);
    typeptr bantu;
    bantu = awal;
    cout<<bantu;
    while (bantu != NULL) {
        cout << "ID Kurir : " << bantu->id_kurir << endl;
        cout << "Nama Kurir : " << bantu->nama_kurir << endl;
        cout << "No Kendaraan : " << bantu->no_kendaraan << endl;
        bantu = bantu->next;
    }
    file.close();
}

void hapus_data(int IH) {
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
        if (IH != bantu->next->id_kurir){
            cout<<"Data Tidak Ditemukan\n";
        }
        else{
            hapus = bantu->next;
            bantu->next = hapus->next;
            free(hapus);
        }
    }

    // kemungkinan eror dari sini
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
        while (IH != qbantu->next_que->que  && qbantu->next_que->next_que != nullptr) {
            qbantu = qbantu->next_que;
        }
        hapusqueue = qbantu->next_que;
        qbantu->next_que = hapusqueue->next_que;
        free(hapusqueue);
    }
    // sampe sini
    if (sukses) {
        bantu = awal;
        file.open("kurir.txt", ios::in | ios::out | ios::trunc);
        while (bantu != nullptr) {
            file << bantu->id_kurir << endl;
            file << bantu->nama_kurir << endl;
            file << bantu->no_kendaraan << endl;
            bantu = bantu->next;
        }
        file.close();
        qbantu = qdepan;
        file.open("antrian.txt",ios::in| ios::out | ios::trunc);
        while (qbantu != nullptr) {
            file << qbantu->que << endl; // error
            qbantu = qbantu->next_que;
        }
        file.close();
    }
}

void buatqueue() {
    typeptr_que qdepan;
    qdepan = nullptr;
    qbelakang = qdepan;
}

int queuekosong() {
    if (qdepan == NULL) {
        return (1);
    } else {
        return (0);
    }
}


void cetakqueue() {
    // file.open("antrian.txt",ios::out);
    typeptr_que bantu_que;
    bantu_que = qdepan;
    do {
        cout << " " << bantu_que->que;
        cout << " ";
        bantu_que = bantu_que->next_que;
    } while (bantu_que != NULL);
}

void enqueue(int IB) {
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
    file.open("antrian.txt",  ios::in | ios::app );
    file << IB << endl;
    file.close();
}

void dequeue() {
    typeptr_que hapus;
    file.open("antrian.txt", ios::in|ios::out | ios::trunc);
    if (queuekosong()) {
        cout << "Antrian masih kosong !";
    } else {
        hapus = qdepan;
        qdepan = hapus->next_que;
        free(hapus);
    }

    typeptr_que bantu = qdepan;
    
    while (bantu != nullptr) {
        file << bantu->que << endl;
        bantu = bantu->next_que;
    }
    file.close();
}

void buat_stack_sampah() {
    typeptr_sampah NS;
    NS = nullptr;
    awalsampah = NS;
    akhirsampah = NS;;
}

void cetak_sampah() {
    typeptr_sampah depan = nullptr, bantu = nullptr;
    if (awalsampah == akhirsampah) {
        cout << awalsampah->sampah << endl;
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
            cout << "" << bantu->sampah << endl;
            bantu = bantu->next_sampah;
        }
    }
}

void sampah() {
    file.open("sampah.txt", ios::out | ios::trunc);
    typeptr_sampah NS, bantu = nullptr;
    NS = new typestack_sampah;
    strcpy(NS->sampah,awal_stack->nama_barang); // nilai NS akan sama dengan Nilai akhirstack
    if (awalsampah == nullptr) {
        awalsampah = NS;
        akhirsampah = awalsampah;
    } else {
        bantu = awalsampah;
    }
    NS->next_sampah = bantu;
    awalsampah = NS;

    bantu = awalsampah;
    
    while (bantu != nullptr) {
        file << bantu->sampah << endl;
        bantu = bantu->next_sampah;
    }
    file.close();
}

bool listkosong() {
    return awal == nullptr;
}

bool carikurir(int id) {
    typeptr bantu = awal;
    while (bantu != nullptr) {
        if (bantu->id_kurir == id) {
            return true;
        }
        bantu = bantu->next;
    }
    return false;
}

bool cariqueue(int id) {
    typeptr_que bantu = qdepan;
    while (bantu != nullptr) {
        if (bantu->next_que->que == id) {
            return true;
        }
        bantu = bantu->next_que;
    }
    return false;
}

void read(){
    int temp;
    char temp2[100],temp3[8];
    int nilai=batas();
    file.open("kurir.txt"); //membuka file buku.txt
    if (nilai !=0){
       for(int i = 0; i <nilai ; i++) { //pengulangan untuk me load data dilakukan sampai end of file (datanya habis)
            file >> temp; //masukkan data yang sudah di load ke variabel temporary
            file.getline(temp2,100); //
            file.getline(temp3,8);
            // cout<<temp<<endl;
            // cout<<temp2<<endl;
            // cout<<temp3<<endl;
            sisip_data(temp,temp2,temp3);
            // enqueue(temp); //memanggil void push dengan argumen temp dan di masukkan ke stack
        }
    }
    file.close(); //menutup file txt
}