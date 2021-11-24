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
    char nama_kurir[100],no_kendaraan[8];
    typeptr next;
};
struct typestack{ // deklarasi
    char nama_barang[100];
    typestck next;
};

typeptr awal, akhir;
typestck awalstack, akhirstack;

void pop();
void sisipdata(int IB,char IB2[100], char IB3[8]);
void push(char IB[100]);
void buat_stack();
void cetak_stack();
void buatlist();
void cetak_list();
int stack_kosong();
void hapusdata(int IH);


int main()
{
    int Pilihan_menu,jumlah_barang,id_kurir,hapus_id;
    char nama_kurir[100],no_kendaraan[8],nama_barang[100];
    string pilihan_hapus,pilihan_pop;
    char pilihan_ulang;
    buatlist();
    do
    {
        cout << "---- Pendataan Kurir Gudang XYZ ----" << endl;
        cout << "Menu\n";
        cout << "1. Pendataan Kurir\n";             // linked List & queue
        cout << "2. Data dan Penginputan Barang\n"; // Push Stack
        cout << "3. Pengambilan Barang\n";          // pop stack
        cout << "4. Riwayat Pengambilan Barang\n";  // sampah
        cout << "5. Exit\n";                        // exit
        cout << "Masukan Pilihan Anda : ";
        cin >> Pilihan_menu;

        if (Pilihan_menu == 1)
        {
            system("cls");
            cout << "Masukan ID Kurir : ";
            cin>>id_kurir;
            cin.ignore();
            cout << "Masukan Nama Kurir : ";
            cin.getline(nama_kurir,100);
            cout << "Masukan No Kendaraan : ";
            cin >> no_kendaraan;
            sisipdata(id_kurir,nama_kurir,no_kendaraan);
            cout<<endl;
            cetak_list();
            cout<<"Apakah Anda Ingin Mengahapus Data ? (y/n) : ";
            cin>>pilihan_hapus;
            if (pilihan_hapus == "y" || pilihan_hapus == "Y")
            {
                cout << "Pilih ID Yang Ingin Dihapus : ";
                cin>>hapus_id;
                hapusdata(hapus_id);
                cetak_list();

            }
            else
            {
            cout<<"apakah anda ingin mengulang ?(y/n) : ";
            cin>>pilihan_ulang;
            }
            
            
        }
        else if (Pilihan_menu == 2)
        {
            cout<<"Berapa Barang Yang Akan Di Data : ";
            cin>>jumlah_barang;
            cin.ignore();
            for (int i=0;i<jumlah_barang;i++){
                cout<<"Masukan Nama Barang : ";
                cin.getline(nama_barang,100);
                push(nama_barang);
            }
            cetak_stack();
             cout<<"apakah anda ingin mengulang ?(y/n) : ";
            cin>>pilihan_ulang;
        }
        else if (Pilihan_menu == 3)
        {
            cout<<"Apakah Anda Ingin Mengambil Barang (y/n) : ";
            cin>>pilihan_pop;
            if (pilihan_pop == "y" || pilihan_pop=="Y")
            {
                pop();
            }
            else{
                cout<<"apakah anda ingin mengulang ?(y/n) : ";
                cin>>pilihan_ulang;
            }
            cetak_stack();
            
        }
        else if (Pilihan_menu == 4) {
            
        } else if (Pilihan_menu == 5) {
            cout<<"Terima Kasih Telah Menggunakan Program\n";
            break;
        } else {
            cout << "Pilihan Anda Salah, Apakah Ingin Mengulang ? (y/n) : ";
            cin>>pilihan_ulang;
            system("cls");

        }
        

    } while (pilihan_ulang == 'y');
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

void push(char IB[100]){ 
    typestck NS;
    NS=(typestack *) malloc(sizeof(typestack));
    strcpy(NS->nama_barang,IB);
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

void sisipdata(int IB,char IB2[100], char IB3[8]){
    typeptr NB;
    NB=(typenode *) malloc(sizeof(typenode));
    NB->id_kurir=IB;
    strcpy(NB->nama_kurir,IB2);
	strcpy(NB->no_kendaraan,IB3);
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

void hapusdata(int IH){
	typeptr hapus,bantu;
	if (awal==NULL){
		cout<<"List masih Kosong"<<endl;
	}
    else if (IH == awal->id_kurir) {
			hapus=awal;
			awal=hapus->next;
			free(hapus);
		}
        else if (IH == akhir->id_kurir){
            bantu=awal;
			while (bantu->next->next!=NULL){
					bantu=bantu->next;
				}
					hapus=bantu->next;
					bantu->next=NULL;
					free(hapus);
        }
	else {
		bantu=awal;
			while (IH!=bantu->next->id_kurir && bantu->next != NULL){
					bantu=bantu->next;
				}
					hapus=bantu->next;
					bantu->next=hapus->next;
					free(hapus);
		}
}