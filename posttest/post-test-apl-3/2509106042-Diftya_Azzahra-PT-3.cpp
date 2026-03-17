#include <iostream>
#include <string>
#include "tabulate/table.hpp"

using namespace std;
using namespace tabulate;

#define max_user 100
#define max_insiden 300

struct insiden{
    int id;
    int id_user;
    string kejadian;
    string tingkat;
    string status;
    string tanggal;
    string pendata;
};

struct user{
    string username;
    string password;
    string role;
};

int panjang = 0;
bool login = false;
int id_counter = 1;
int jumlah_user = 0;

user pengguna[max_user];
insiden dataInsiden[max_insiden];


int hitungid(string user, int index){
    if(index == panjang)
        return 0;

    if(dataInsiden[index].pendata == user)
        return 1 + hitungid(user, index + 1);

    return hitungid(user, index + 1);
}

int cariInsiden(int id){
    for(int i = 0; i < panjang; i++)
        if(dataInsiden[i].id == id)
            return i;
    return -1;
}

int cariInsiden(int id, string user){
    for(int i = 0; i < panjang; i++)
        if(dataInsiden[i].id_user == id && dataInsiden[i].pendata == user)
            return i;
    return -1;
}

bool loginUser(string username, string password, string &role){
    if(username == "diftya" && password == "042"){
        role = "admin";
        return true;
    }

    for(int i = 0; i < jumlah_user; i++)
        if(pengguna[i].username == username && pengguna[i].password == password){
            role = "user";
            return true;
        }

    return false;
}

bool registerUser(string username, string password){
    if(username == "diftya")
        return false;

    for(int i = 0; i < jumlah_user; i++)
        if(pengguna[i].username == username)
            return false;

    pengguna[jumlah_user].username = username;
    pengguna[jumlah_user].password = password;
    pengguna[jumlah_user].role = "user";

    jumlah_user++;
    return true;
}



void tambahInsiden(string username_login){

    string kejadian, tingkat_keparahan, status, tanggal;

    if(panjang < max_insiden){

        cout << "Tambah Insiden" << endl;

        int id_user = hitungid(username_login,0) + 1;

        do{
            cout << "Laporan kejadian: ";
            getline(cin, kejadian);

            if(kejadian == "")
                cout << "Laporan kejadian tidak boleh kosong!" << endl;

        }while(kejadian == "");


        do{
            cout << "Input tingkat keparahan (Critical/High/Medium/Low): ";
            getline(cin, tingkat_keparahan);

            if(tingkat_keparahan == "")
                cout << "Tingkat keparahan tidak boleh kosong!" << endl;

        }while(tingkat_keparahan == "");


        while(tingkat_keparahan != "Critical" &&
            tingkat_keparahan != "High" &&
            tingkat_keparahan != "Medium" &&
            tingkat_keparahan != "Low"){

            cout << "Input tidak valid!" << endl;
            cout << "Masukkan ulang tingkat keparahan: ";
            getline(cin, tingkat_keparahan);
        }

        do{
            cout << "Tanggal: ";
            getline(cin, tanggal);

            if(tanggal == "")
                cout << "Tanggal tidak boleh kosong!" << endl;

        }while(tanggal == "");


        dataInsiden[panjang].id = id_counter;
        dataInsiden[panjang].id_user = id_user;
        dataInsiden[panjang].kejadian = kejadian;
        dataInsiden[panjang].tingkat = tingkat_keparahan;

        status = "open";
        dataInsiden[panjang].status = status;

        dataInsiden[panjang].tanggal = tanggal;
        dataInsiden[panjang].pendata = username_login;

        panjang++;
        id_counter++;

        cout << "Insiden berhasil ditambahkan!" << endl;
    }
    else
        cout << "Kapasitas penuh!" << endl;
}

void lihatInsiden(string username_login, string role){

    if(panjang == 0)
        cout << "Belum ada insiden" << endl;

    else{

        Table tabel;

        tabel.add_row({"ID","Kejadian","Tingkat","Status","Tanggal","Pendata"});

        for(int i = 0; i < panjang; i++)
            if(role == "admin" || dataInsiden[i].pendata == username_login)
                tabel.add_row({
                to_string(dataInsiden[i].id),
                dataInsiden[i].kejadian,
                dataInsiden[i].tingkat,
                dataInsiden[i].status,
                dataInsiden[i].tanggal,
                dataInsiden[i].pendata
                });

        cout << tabel << endl;
    }
}

void ubahStatus(string username_login, string role){

    if (panjang == 0) {
        cout << "Belum ada Insiden untuk diubah" << endl;
        return;
    }

    int index, posisi;

    do {
    cout << "Masukkan ID insiden: ";
    cin >> index;
    cin.clear();
    cin.ignore(1000,'\n');

    if(role == "admin")
        posisi = cariInsiden(index);
    else
        posisi = cariInsiden(index, username_login);

    if(posisi == -1) 
        cout << "ID tidak valid!" << endl;
    } while (posisi == -1);

    string statusBaru;

    cout << "Status baru (In Progress/Escalated/Resolved/Closed): ";
    getline(cin, statusBaru);

    while(statusBaru != "In Progress" &&
        statusBaru != "Escalated" &&
        statusBaru != "Resolved" &&
        statusBaru != "Closed"){

        cout << "Input tidak valid!" << endl;
        cout << "Masukkan ulang status baru: ";
        getline(cin, statusBaru);
    }

    dataInsiden[posisi].status = statusBaru;

    cout << "Status berhasil diubah" << endl;
}

void hapusInsiden(){

    int index;

    cout << "Masukkan ID insiden: ";
    cin >> index;
    cin.clear();
    cin.ignore(1000,'\n');

    int posisi = cariInsiden(index);

    if(posisi != -1){

        for(int i = posisi; i < panjang-1; i++)
            dataInsiden[i] = dataInsiden[i+1];

        panjang--;

        cout << "Insiden berhasil dihapus" << endl;
    }
    else
        cout << "ID tidak valid" << endl;
}

void menuUtama(string &username_login, string &role){

    int pilih_menu;

    while(login){

        if(role == "user"){
            cout << "\n=== MENU UTAMA ===" << endl;
            cout << "Login sebagai: " << username_login << " (" << role << ")" << endl;
            cout << "1. Tambah Insiden" << endl;
            cout << "2. Lihat Insiden" << endl;
            cout << "3. Ubah Status Insiden" << endl;
            cout << "4. Logout" << endl;
        }
        else{
            cout << "\n=== MENU UTAMA ===" << endl;
            cout << "Login sebagai: " << username_login << " (" << role << ")" << endl;
            cout << "1. Tambah Insiden" << endl;
            cout << "2. Lihat Insiden" << endl;
            cout << "3. Ubah Status Insiden" << endl;
            cout << "4. Logout" << endl;    
            cout << "5. Hapus Insiden" << endl;
        }

        cout << "Pilih menu: ";
        cin >> pilih_menu;
        cin.ignore();

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000,'\n');
            cout << "Input tidak valid" << endl;
            continue;
        }

        if (role == "admin") {
            if (pilih_menu < 1 || pilih_menu > 5) {
                cout << "Input tidak valid" << endl;
                continue;
            }
        }
        else {
            if (pilih_menu < 1 || pilih_menu > 4) {
                cout << "Input tidak valid" << endl;
                continue;
            }
        }

        switch(pilih_menu){

        case 1:
            tambahInsiden(username_login);
        break;

        case 2:
            lihatInsiden(username_login, role);
        break;

        case 3:
            ubahStatus(username_login, role);
        break;

        case 4:
            login = false;
            username_login = "";
            role = "";
            cout << "Logout berhasil!" << endl;
        break;

        case 5: {
            if(role != "admin"){
                cout << "Input tidak valid" << endl;
                break;
            }
            hapusInsiden();
        break;
        }

        default:
            cout << "Pilihan tidak valid" << endl;
        }
    }
}


int main(){

    int pilihan;
    string username, password;
    string username_login = "";
    string role = "";

    int percobaan_login = 0;

    while(true){

        if(!login){

            cout << "\nSISTEM MANAJEMEN INSIDEN (SIEM)" << endl;
            cout << "1. Login" << endl;
            cout << "2. Register" << endl;
            cout << "3. Keluar" << endl;

            cout << "Pilih menu: ";
            cin >> pilihan;

            if(cin.fail()){
                cin.clear();
                cin.ignore(1000,'\n');
                cout << "Input tidak valid" << endl;
                continue;
            }

            if(pilihan < 1 || pilihan > 3){
                cout << "Input tidak valid" << endl;
                continue;
            }

            switch(pilihan){

            case 1:

                while(percobaan_login < 3 && !login){
                    cin.ignore(1000, '\n');

                    do {
                        cout << "Input Username Anda: ";
                        getline(cin, username);

                        if (username == "") {
                            cout << "Username tidak boleh kosong!" << endl;
                        }
                    }while(username == "");

                    do {
                        cout << "Input Password Anda: ";
                        getline(cin, password);

                        if (password == "")
                        cout << "Password tidak boleh kosong!" << endl;
                    }while (password == "");

                    if(cin.fail()){
                        cin.clear();
                        cin.ignore(1000,'\n');
                        cout << "Input tidak valid" << endl;
                        continue;
                    }

                    if(loginUser(username,password,role)){

                        login = true;
                        username_login = username;
                        percobaan_login = 0;

                        cout << "Login Berhasil!" << endl;

                        menuUtama(username_login,role);
                        break;
                    }
                    else{

                        percobaan_login++;

                        cout << "Username atau password salah" << endl;

                        if(percobaan_login >= 3){
                            cout << "Gagal login 3 kali, Program berhenti." << endl;
                            return 0;
                        }
                    }
                }

            break;

            case 2:

                if(jumlah_user < max_user){

                    cin.ignore(1000, '\n'); // buang newline sisa sebelumnya

                    cout << "input username anda: ";
                    getline(cin, username);

                    cout << "input password anda : ";
                    getline(cin, password);

                    if(registerUser(username,password))
                        cout << "Registrasi Berhasil!" << endl;
                    else
                        cout << "Username sudah terdaftar" << endl;
                }
                else
                    cout << "Kapasitas user penuh" << endl;

            break;

            case 3:
                cout << "Terima kasih telah menggunakan program ini" << endl;
                return 0;

            default:
                cout << "Pilihan tidak valid" << endl;
            }
        }
    }
}