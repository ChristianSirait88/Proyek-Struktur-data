#include <iostream>
#include <iomanip>
#include <stdio.h>
#define True 1
#define False 0
using namespace std;

typedef struct typestack *typestck; // Linked List untuk oprasi stack
typedef struct typenode *typeptr;
struct typenode
{
    int id_kurir;
    string nama_kurir,no_kendaraan;
    typeptr next;
};
struct typestack{ // deklarasi
    string nama_barang;
    typestck next;
};

typeptr awal, akhir;
typestck awalstack, akhirstack;

void pop();
void sisipdata(int IB,string IB2, string IB3);
void push(string IB);
void buat_stack();
void cetak_stack();
void buatlist();
void cetak_list();
int stack_kosong();


int main()
{
    int Pilihan_menu,id_kurir;
    string nama_kurir,no_kendaraan;
    buatlist();
    do
    {
        cout << "---- Pendataan Kurir Gudang XYZ ----" << endl;
        cout << "Menu\n";
        cout << "1. Pendataan Kurir\n";             //linked List & queue
        cout << "2. Data dan Penginputan Barang\n"; // Push Stack
        cout << "3. Pengambilan Barang\n";          // pop stack
        cout << "4. Riwayat Pengambilan Barang\n";  //sampah
        cout << "5. Exit\n";                        //exit
        cout << "Masukan Pilihan Anda : ";
        cin >> Pilihan_menu;

        if (Pilihan_menu == 1)
        {
            cout << "Masukan ID Kurir";
            cin>>id_kurir;
            cout << "Masukan Nama Kurir : ";
            cin>>nama_kurir;
            cout << "Masukan No Kendaraan : ";
            cin >> no_kendaraan;
            sisipdata(id_kurir,nama_kurir,no_kendaraan);
            cout<<endl;
            cetak_list();
        }
        else if (Pilihan_menu == 2)
        {
        }
        else if (Pilihan_menu == 3)
        {
        }

    } while (Pilihan_menu <= 6);
}

void buatlist()
{
    typeptr list;
    list = (typenode *)malloc(sizeof(typenode));
    list = NULL;
    awal = list;
    akhir = list;
}

void buat_stack(){ 
    typestck NS;
    NS=NULL;
    awalstack=NS;
    akhirstack=NS; 
    }

int stack_kosong(){ 
    if(awalstack==NULL){
        return(True);
    }
    else{
        return(False); 
    }
}

void push(int IB){ 
    typestck NS;
    NS=(typestack *) malloc(sizeof(typestack));
    NS->nama_barang=IB;
    if (awalstack==NULL)
        awalstack=NS;
    else
        akhirstack->next=NS;
        akhirstack=NS;
        akhirstack->next=NULL; 
    }

void pop(){ 
    typestck hapus, bantu;
    bantu=awalstack;
    hapus=akhirstack;
    if (hapus==awalstack)
        awalstack=NULL;
    else{ 
        while(bantu->next->next!=NULL){
    bantu=bantu->next;
    }
    akhirstack=bantu;
    akhirstack->next=NULL; }
    free(hapus); 
}

void cetak_stack(){ 
    typestck depan,bantu;
    if(awalstack==akhirstack){
        cout<<awalstack->nama_barang <<endl;
    } 
    else { 
        depan=awalstack;
        awalstack=akhirstack;
        do { 
            bantu=depan;
            while (bantu->next!=akhirstack){
            bantu=bantu->next;
            }
            akhirstack->next=bantu;
            akhirstack=bantu;
        }
        while (akhirstack!=depan);
        akhirstack->next=NULL;
        bantu=awalstack;
        while(bantu!=NULL){ 
            cout << "" << bantu->nama_barang << endl;
            bantu=bantu->next; 
        }
    }
}

void sisipdata(int IB,string IB2, string IB3){
    typeptr NB;
    NB=(typenode *) malloc(sizeof(typenode));
    NB->id_kurir=IB;
    NB->nama_kurir=IB2;
    NB->no_kendaraan=IB3;
    if(awal==NULL){
        awal=NB;
        akhir=NB;
        awal->next = NULL;
    }
    else {
        NB->next=awal;
    }
    awal=NB;
}

void cetak_list() {
	typeptr bantu;
	bantu=awal;
	while(bantu!=NULL){
        cout<<"ID Kurir : "<<bantu->id_kurir<<endl;
        cout <<"Nama Kurir : "<< bantu->nama_kurir<<endl;
        cout<<"No Kendaraan : "<<bantu->no_kendaraan<<endl;
		bantu=bantu->next;
	}
}