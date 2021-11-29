#include <iostream>
#include <string>
#include <malloc.h>
#include <iomanip>
using namespace std;

typedef struct typestack *typestck; // Linked List untuk oprasi stack
typedef struct typequeue *typeptr_que;
typedef struct typenode *typeptr;
struct typenode {
    int id_kurir;
    string nama_kurir;
    string no_kendaraan;
    typeptr next;
};
struct typestack { // deklarasi
    string nama_barang;
    typestck next;
};
struct typequeue{
    int que;
    typeptr_que next_que;
};

typeptr_que qdepan, qbelakang;
typeptr awal, akhir;
typestck awal_stack, akhir_stack;

void pop();

void sisip_data(int IB, string IB2, string IB3);

void push(string IB);

void buat_stack();

void cetak_stack();

void buat_list();

void cetak_list();

bool stack_kosong();

void hapus_data(int IH);

void buatqueue();

void cetakqueue();

void dequeue();

int queuekosong();

void enqueue(int IB);


int main() {
    int pilihan_menu,pilihan_barang,pilihan_pop, jumlah_barang, id_kurir, hapus_id;
    string pilihan_kurir,nama_kurir, no_kendaraan, nama_barang;
    char pilihan_hapus;
    char pilihan_ulang;
    buat_list();
    buat_stack();
    buatqueue();
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
            cout << "Masukan ID Kurir : ";
            cin >> id_kurir;
            cin.ignore();
            cout << "Masukan Nama Kurir : ";
            getline(cin, nama_kurir);
            cout << "Masukan No Kendaraan : ";
            getline(cin, no_kendaraan);
            enqueue(id_kurir);
            sisip_data(id_kurir, nama_kurir, no_kendaraan);
            cout << endl;
            cetak_list();
            cetakqueue();
            cout << "Apakah Anda Ingin Mengahapus Data ? (y/n) : ";
            cin >> pilihan_hapus;
            if (pilihan_hapus == 'y' || pilihan_hapus == 'Y') {
                cout << "Pilih ID Yang Ingin Dihapus : ";
                cin >> hapus_id;
                hapus_data(hapus_id);
                cetak_list();

            } else {
                cout << "apakah anda ingin mengulang ?(y/n) : ";
                cin >> pilihan_ulang;
            }


        } else if (pilihan_menu == 2) {
            cout << "--- Menu Penginputan Barang ---\n";
            cout<<"1. Input Barang\n";
            cout <<"2. Lihat Barang\n";
            if (pilihan_barang == 1)
            {
                cout << "Berapa Barang Yang Akan Di Data : ";
                cin >> jumlah_barang;
                cin.ignore();
                for (int i = 0; i < jumlah_barang; i++) {
                    cout << "Masukan Nama Barang : ";
                    getline(cin, nama_barang);
                    push(nama_barang);
                }
            }
            else if (pilihan_barang == 2){
                cout << "Data Barang\n";
                cetak_stack();
            }
            cout << "apakah anda ingin mengulang ?(y/n) : ";
            cin >> pilihan_ulang;
        } else if (pilihan_menu == 3) {
            cout << "Apakah Anda Ingin Mengambil Barang (y/n) : ";
            cin>> pilihan_kurir;
            if (pilihan_kurir == "y" || pilihan_kurir == "Y") {
                cout << "Berapa Barang Yang Ingin Diambil : ";
                cin >> pilihan_pop;
                for (int i = 0; i < pilihan_pop; i++) 
                {
                    pop();
                }
                cout<<"Sisa Barang : \n";
                cetak_stack();
            }
            else {
                cout << "apakah anda ingin mengulang ?(y/n) : ";
                cin >> pilihan_ulang;
            }

        } else if (pilihan_menu == 4) {

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
    typeptr list = nullptr;
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

void push(string IB) {
    typestck NS;
    typestck bantu;
    NS = new typestack;
    NS->nama_barang = move(IB);

    if (awal_stack == nullptr)
        awal_stack = NS;
    else {
        bantu = awal_stack;
        NS->next = bantu;
        awal_stack = NS;
    }
}

void pop() {
    typestck bantu = awal_stack;
    if (awal_stack == akhir_stack) {
        awal_stack = nullptr;
    } else {
        awal_stack = awal_stack->next;
        delete bantu;
    }
}

void cetak_stack() {
    typestck bantu = awal_stack;
    while (bantu != nullptr) {
        cout << bantu->nama_barang << " ";
        bantu = bantu->next;
    }
    cout << endl;
}

void sisip_data(int IB, string IB2, string IB3) {
    typeptr NB;
    NB = new typenode;
    NB->id_kurir = IB;
    NB->nama_kurir = move(IB2);
    NB->no_kendaraan = move(IB3);
    if (awal == nullptr) {
        awal = NB;
        akhir = NB;
        awal->next = nullptr;
    } else {
        NB->next = awal;
    }
    awal = NB;
}

void cetak_list() {
    typeptr bantu;
    bantu = awal;
    while (bantu != nullptr) {
        cout << "ID Kurir : " << bantu->id_kurir << endl;
        cout << "Nama Kurir : " << bantu->nama_kurir << endl;
        cout << "No Kendaraan : " << bantu->no_kendaraan << endl;
        bantu = bantu->next;
    }
}

void hapus_data(int IH) {
    typeptr hapus, bantu;
    if (awal == nullptr) {
        cout << "List masih Kosong" << endl;
    } else if (IH == awal->id_kurir) {
        hapus = awal;
        awal = hapus->next;
        free(hapus);
    } else if (IH == akhir->id_kurir) {
        bantu = awal;
        while (bantu->next->next != nullptr) {
            bantu = bantu->next;
        }
        hapus = bantu->next;
        bantu->next = nullptr;
        free(hapus);
    } else {
        bantu = awal;
        while (IH != bantu->next->id_kurir && bantu->next != nullptr) {
            bantu = bantu->next;
        }
        hapus = bantu->next;
        bantu->next = hapus->next;
        free(hapus);
    }
}
void buatqueue(){ 
    qdepan=(typequeue *) malloc(sizeof(typequeue));
    qdepan=NULL;
    qbelakang=qdepan;
}

int queuekosong(){ 
    if(qdepan==NULL){
        return(1);
    }
    else{
        return(0);
    }
}


void cetakqueue(){
    typeptr_que bantu_que;
    bantu_que=qdepan;
    do {
        cout << " " << bantu_que->que;
        cout << " ";
        bantu_que=bantu_que->next_que;
    } while(bantu_que!=NULL);
}

void enqueue(int IB){ 
    typeptr_que NB;
    NB=(typequeue *) malloc(sizeof(typequeue));
    NB->que=IB;
    if (qdepan==NULL)
        qdepan=NB;
    else
    qbelakang->next_que=NB;
    qbelakang=NB;
    qbelakang->next_que=NULL;
}

void dequeue()
{
    typeptr_que hapus;
    if (queuekosong()){ 
        cout << "Queue masih kosong !";
    }
    else{ 
        hapus=qdepan;
        qdepan=hapus->next_que;
        free(hapus); 
    }
}