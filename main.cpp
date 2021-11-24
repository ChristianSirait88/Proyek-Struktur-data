#include <iostream>
#include <string>

#define True 1
#define False 0
using namespace std;

typedef struct typestack *typestck; // Linked List untuk oprasi stack
typedef struct typenode *typeptr;
struct typenode {
    int idKurir;
    string namaKurir;
    string noKendaraan;
    typeptr next;
};
struct typestack { // deklarasi
    string namaBarang;
    typestck next;
};

typeptr awal, akhir;
typestck awalStack, akhirStack;

void pop();

void sisipData(int IB, string IB2, string IB3);

void push(string IB);

void buatStack();

void cetakStack();

void buatList();

void cetakList();

int stackKosong();

void hapusData(int IH);


int main() {
    int pilihanMenu, jumlahBarang, idKurir, hapus_id;
    string namaKurir, noKendaraan, namaBarang;
    char pilihanHapus, pilihanPop;
    char pilihanUlang;
    buatList();
    do {
        cout << "---- Pendataan Kurir Gudang XYZ ----" << endl;
        cout << "Menu\n";
        cout << "1. Pendataan Kurir\n";             // linked List & queue
        cout << "2. Data dan Penginputan Barang\n"; // Push Stack
        cout << "3. Pengambilan Barang\n";          // pop stack
        cout << "4. Riwayat Pengambilan Barang\n";  // sampah
        cout << "5. Exit\n";                        // exit
        cout << "Masukan Pilihan Anda : ";
        cin >> pilihanMenu;

        if (pilihanMenu == 1) {
            system("cls");
            cout << "Masukan ID Kurir : ";
            cin >> idKurir;
            cin.ignore();
            cout << "Masukan Nama Kurir : ";
            getline(cin, namaKurir);
            cout << "Masukan No Kendaraan : ";
            getline(cin, noKendaraan);
            sisipData(idKurir, namaKurir, noKendaraan);
            cout << endl;
            cetakList();
            cout << "Apakah Anda Ingin Mengahapus Data ? (y/n) : ";
            cin >> pilihanHapus;
            if (pilihanHapus == 'y' || pilihanHapus == 'Y') {
                cout << "Pilih ID Yang Ingin Dihapus : ";
                cin >> hapus_id;
                hapusData(hapus_id);
                cetakList();

            } else {
                cout << "apakah anda ingin mengulang ?(y/n) : ";
                cin >> pilihanUlang;
            }


        } else if (pilihanMenu == 2) {
            cout << "Berapa Barang Yang Akan Di Data : ";
            cin >> jumlahBarang;
            cin.ignore();
            for (int i = 0; i < jumlahBarang; i++) {
                cout << "Masukan Nama Barang : ";
                getline(cin, namaBarang);
                push(namaBarang);
            }
            cetakStack();
            cout << "apakah anda ingin mengulang ?(y/n) : ";
            cin >> pilihanUlang;
        } else if (pilihanMenu == 3) {
            cout << "Apakah Anda Ingin Mengambil Barang (y/n) : ";
            cin >> pilihanPop;
            if (pilihanPop == 'y' || pilihanPop == 'Y') {
                pop();
            } else {
                cout << "apakah anda ingin mengulang ?(y/n) : ";
                cin >> pilihanUlang;
            }
            cetakStack();

        } else if (pilihanMenu == 4) {

        } else if (pilihanMenu == 5) {
            cout << "Terima Kasih Telah Menggunakan Program\n";
            break;
        } else {
            cout << "Pilihan Anda Salah, Apakah Ingin Mengulang ? (y/n) : ";
            cin >> pilihanUlang;
            system("cls");

        }


    } while (pilihanUlang == 'y');
}

void buatList() {
    typeptr list;
    list = (typenode *) malloc(sizeof(typenode));
    list = nullptr;
    awal = list;
    akhir = list;
}

void buatStack() {
    typestck NS;
    NS = nullptr;
    awalStack = NS;
    akhirStack = NS;
}

int stackKosong() {
    if (awalStack == nullptr) {
        return (True);
    } else {
        return (False);
    }
}

void push(string IB) {
    typestck NS;
    NS = (typestack *) malloc(sizeof(typestack));
    NS->namaBarang = IB;

    if (awalStack == nullptr)
        awalStack = NS;
    else
        akhirStack->next = NS;
    akhirStack = NS;
    akhirStack->next = nullptr;
}

void pop() {
    typestck hapus, bantu;
    bantu = awalStack;
    hapus = akhirStack;
    if (hapus == awalStack)
        awalStack = nullptr;
    else {
        while (bantu->next->next != nullptr) {
            bantu = bantu->next;
        }
        akhirStack = bantu;
        akhirStack->next = nullptr;
    }
    free(hapus);
}

void cetakStack() {
    typestck depan, bantu;
    if (awalStack == akhirStack) {
        cout << awalStack->namaBarang << endl;
    } else {
        depan = awalStack;
        awalStack = akhirStack;
        do {
            bantu = depan;
            while (bantu->next != akhirStack) {
                bantu = bantu->next;
            }
            akhirStack->next = bantu;
            akhirStack = bantu;
        } while (akhirStack != depan);
        akhirStack->next = nullptr;
        bantu = awalStack;
        while (bantu != nullptr) {
            cout << "" << bantu->namaBarang << endl;
            bantu = bantu->next;
        }
    }
}

void sisipData(int IB, string IB2, string IB3) {
    typeptr NB;
    NB = (typenode *) malloc(sizeof(typenode));
    NB->idKurir = IB;
    NB->namaKurir = IB2;
    NB->noKendaraan = IB3;
    if (awal == nullptr) {
        awal = NB;
        akhir = NB;
        awal->next = nullptr;
    } else {
        NB->next = awal;
    }
    awal = NB;
}

void cetakList() {
    typeptr bantu;
    bantu = awal;
    while (bantu != nullptr) {
        cout << "ID Kurir : " << bantu->idKurir << endl;
        cout << "Nama Kurir : " << bantu->namaKurir << endl;
        cout << "No Kendaraan : " << bantu->noKendaraan << endl;
        bantu = bantu->next;
    }
}

void hapusData(int IH) {
    typeptr hapus, bantu;
    if (awal == nullptr) {
        cout << "List masih Kosong" << endl;
    } else if (IH == awal->idKurir) {
        hapus = awal;
        awal = hapus->next;
        free(hapus);
    } else if (IH == akhir->idKurir) {
        bantu = awal;
        while (bantu->next->next != nullptr) {
            bantu = bantu->next;
        }
        hapus = bantu->next;
        bantu->next = nullptr;
        free(hapus);
    } else {
        bantu = awal;
        while (IH != bantu->next->idKurir && bantu->next != nullptr) {
            bantu = bantu->next;
        }
        hapus = bantu->next;
        bantu->next = hapus->next;
        free(hapus);
    }
}