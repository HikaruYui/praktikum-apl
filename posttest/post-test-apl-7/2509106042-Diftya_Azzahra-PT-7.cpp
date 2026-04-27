#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <stdexcept>
#include <cctype>
#include "tabulate/table.hpp"

using namespace std;
using namespace tabulate;

#define max_user 100
#define max_insiden 3005

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
        if(dataInsiden[i].id == id && dataInsiden[i].pendata == user)
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

void updateStatusInsiden(insiden *data, string statusBaru){
    data->status = statusBaru;
}

int prioritasTingkat(string tingkat){
    if(tingkat == "Low") return 1;
    if(tingkat == "Medium") return 2;
    if(tingkat == "High") return 3;
    if(tingkat == "Critical") return 4;
    return 0;
}

bool lebihKecilPendata(insiden a, insiden b){
    return a.pendata < b.pendata;
}

bool lebihBesarPendata(insiden a, insiden b){
    return a.pendata > b.pendata;
}

void quickSortPendata(int low, int high){
    if(low >= high)
        return;

    int mid = low + (high - low) / 2;
    insiden pivot = dataInsiden[mid];

    int i = low;
    int j = high;

    while(i <= j){
        while(i <= high && lebihKecilPendata(dataInsiden[i], pivot)){
            i++;
        }

        while(j >= low && lebihBesarPendata(dataInsiden[j], pivot)){
            j--;
        }

        if(i <= j){
            swap(dataInsiden[i], dataInsiden[j]);
            i++;
            j--;
        }
    }

    if(low < j)
        quickSortPendata(low, j);

    if(i < high)
        quickSortPendata(i, high);
}

void selectionSortId(){
    for(int i = 0; i < panjang - 1; i++){
        int indeksMin = i;

        for(int j = i + 1; j < panjang; j++){
            if(dataInsiden[j].id < dataInsiden[indeksMin].id){
                indeksMin = j;
            }
        }

        if(indeksMin != i){
            swap(dataInsiden[i], dataInsiden[indeksMin]);
        }
    }
}

void insertionSortTingkat(){
    for(int i = 1; i < panjang; i++){
        insiden key = dataInsiden[i];
        int j = i - 1;

        while(j >= 0 &&
              prioritasTingkat(dataInsiden[j].tingkat) > prioritasTingkat(key.tingkat)){
            dataInsiden[j + 1] = dataInsiden[j];
            j--;
        }

        dataInsiden[j + 1] = key;
    }
}

int binarySearchID(insiden *arr, int n, int targetID) {
    int low = 0;
    int high = n - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid].id == targetID) {
            return mid;
        }
        else if (arr[mid].id < targetID) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }
    return -1;
}

int jumpSearchPendata(insiden *arr, int n, string targetPendata) {
    if (n <= 0) {
        return -1;
    }

    int step = sqrt(n);
    int prev = 0;

    while(arr[min(step, n) - 1].pendata < targetPendata) {
        prev = step;
        step += sqrt(n);

        if(prev >= n) {
            return -1;
        }
    }
    while (prev < min(step, n) && arr[prev].pendata < targetPendata) {
        prev++;
    }
    if (prev < n && arr[prev].pendata == targetPendata) {
        return prev;
    }
    return -1;
}

int inputAngka(string pesan) {
    string input;
    int nilai;

    while(true) {
        try {
            cout << pesan;
            getline(cin, input);

            if(input == "") {
                throw invalid_argument("Input tidak boleh kosong!");
            }

            for(int i = 0; i < input.length(); i++) {
                if(!isdigit(input[i])) {
                    throw invalid_argument("Input harus berupa angka!");
                }
            }

            nilai = stoi(input);
            return nilai;
        }
        catch(const exception& e) {
            cout << "Error: " << e.what() << endl;
        }
    }
}

string input(string pesan) {
    string nilai;

    while(true) {
        try {
            cout << pesan;
            getline(cin, nilai);

            if(nilai == "") {
                throw invalid_argument("Input tidak boleh kosong!");
            }

            return nilai;
        }
        catch (const exception &e) {
            cout << "Error: " << e.what() << endl;
        }
    }
}

void tambahInsiden(string username_login){
    try{
        if(panjang >= max_insiden){
            throw overflow_error("Kapasitas insiden penuh!");
        }

        cout << "Tambah Insiden" << endl;

        string kejadian = input("Laporan Kejadian: ");
        string tingkat_keparahan;

        while (true) {
            try {
                tingkat_keparahan = input("Tingkat Keparahan (Critical/High/Medium/Low): ");

                if (tingkat_keparahan != "Critical" &&
                    tingkat_keparahan != "High" &&
                    tingkat_keparahan != "Medium" &&
                    tingkat_keparahan != "Low") {
                    throw invalid_argument("Input tidak valid!");
                }

                break;
            }
            catch (const exception& e) {
                cout << "Error: " << e.what() << endl;
            }
        }

        string tanggal = input("Tanggal: ");

        int id_user = hitungid(username_login, 0) + 1;

        dataInsiden[panjang].id = id_counter;
        dataInsiden[panjang].id_user = id_user;
        dataInsiden[panjang].kejadian = kejadian;
        dataInsiden[panjang].tingkat = tingkat_keparahan;
        dataInsiden[panjang].status = "open";
        dataInsiden[panjang].tanggal = tanggal;
        dataInsiden[panjang].pendata = username_login;

        panjang++;
        id_counter++;

        cout << "Insiden berhasil ditambahkan!" << endl;
    }
    catch (const exception& e){
        cout << "Error: " << e.what() << endl;
    }
}

void lihatInsiden(string username_login, string role){
    try {
        if(panjang == 0){
            throw runtime_error("Belum ada insiden!");
        }

        cout << "\n=== Pilih Metode Sorting ===" << endl;
        cout << "1. Pendata (Quick Sort)" << endl;
        cout << "2. ID (Selection Sort)" << endl;
        cout << "3. Tingkat Keparahan (Insertion Sort)" << endl;

        int pilihan_sort;

        while (true) {
            try {
                pilihan_sort = inputAngka("Pilih sorting: ");

                if (pilihan_sort < 1 || pilihan_sort > 3) {
                    throw out_of_range("Pilihan Sorting harus di antara 1 - 3!");
                }

                break;
            }
            catch (const exception& e) {
                cout << "Error: " << e.what() << endl;
            }
        }

        switch(pilihan_sort){
            case 1:
                quickSortPendata(0, panjang - 1);
                break;
            case 2:
                selectionSortId();
                break;
            case 3:
                insertionSortTingkat();
                break;
        }

        bool adaData = false;
        for(int i = 0; i < panjang; i++){
            if(role == "admin" || dataInsiden[i].pendata == username_login){
                adaData = true;
                break;
            }
        }

        if(!adaData){
            throw runtime_error("Belum ada insiden untuk ditampilkan!");
        }

        Table tabel;
        tabel.add_row({"ID","Kejadian","Tingkat","Status","Tanggal","Pendata"});

        for(int i = 0; i < panjang; i++){
            if(role == "admin" || dataInsiden[i].pendata == username_login){
                tabel.add_row({
                    to_string(dataInsiden[i].id),
                    dataInsiden[i].kejadian,
                    dataInsiden[i].tingkat,
                    dataInsiden[i].status,
                    dataInsiden[i].tanggal,
                    dataInsiden[i].pendata
                });
            }
        }

        cout << tabel << endl;
    }
    catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
}

void ubahStatus(string username_login, string role){
    try {
        if(panjang <= 0){
            throw runtime_error("Belum ada Insiden untuk diubah");
        }

        int posisi;
        int id = inputAngka("Silakan Masukkan ID Insiden: ");

        if(role == "admin")
            posisi = cariInsiden(id);
        else
            posisi = cariInsiden(id, username_login);

        if(posisi == -1) {
            throw runtime_error("ID tidak valid!");
        }

        string statusBaru;

        cout << "Status baru (In Progress/Escalated/Resolved/Closed): ";
        getline(cin, statusBaru);

        if(statusBaru != "In Progress" &&
           statusBaru != "Escalated" &&
           statusBaru != "Resolved" &&
           statusBaru != "Closed"){
            throw invalid_argument("Input tidak valid!");
        }

        updateStatusInsiden(&dataInsiden[posisi], statusBaru);

        cout << "Status berhasil diubah" << endl;
    }
    catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
}

void cariInsiden(string username_login, string role) {
    try {
        if (panjang == 0) {
            throw runtime_error("Belum ada insiden");
        }

        cout << "\n=== MENU SEARCHING ===" << endl;
        cout << "1. Cari berdasarkan ID" << endl;
        if (role == "admin") {
            cout << "2. Cari berdasarkan Pendata" << endl;
        }

        int pilihan_search = inputAngka("Pilih menu: ");

        if (role == "admin") {
            if (pilihan_search < 1 || pilihan_search > 2) {
                throw out_of_range("Input tidak valid!");
            }
        }
        else {
            if (pilihan_search != 1) {
                throw out_of_range("Input tidak valid!");
            }
        }

        if (pilihan_search == 1) {
            int targetID = inputAngka("Masukkan ID Insiden: ");

            if (targetID <= 0) {
                throw invalid_argument("ID harus lebih dari 0!");
            }

            selectionSortId();
            int posisi = binarySearchID(dataInsiden, panjang, targetID);

            if (posisi == -1) {
                throw runtime_error("Insiden tidak ditemukan!");
            }

            if (role != "admin" && dataInsiden[posisi].pendata != username_login) {
                throw runtime_error("Anda tidak memiliki akses ke insiden tersebut!");
            }

            Table tabel;
            tabel.add_row({"ID", "Kejadian", "Tingkat", "Status", "Tanggal", "Pendata"});
            tabel.add_row({
                to_string(dataInsiden[posisi].id),
                dataInsiden[posisi].kejadian,
                dataInsiden[posisi].tingkat,
                dataInsiden[posisi].status,
                dataInsiden[posisi].tanggal,
                dataInsiden[posisi].pendata
            });

            cout << "Insiden Ditemukan!" << endl;
            cout << tabel << endl;
        }
        else if (pilihan_search == 2 && role == "admin") {
            string targetPendata = input("Silakan Masukkan nama Pendata: ");

            quickSortPendata(0, panjang - 1);
            int posisi = jumpSearchPendata(dataInsiden, panjang, targetPendata);

            if (posisi == -1) {
                throw runtime_error("Pendata tidak ditemukan");
            }

            int i = posisi;

            while (i > 0 && dataInsiden[i - 1].pendata == targetPendata) {
                i--;
            }

            Table tabel;
            tabel.add_row({"ID", "Kejadian", "Tingkat", "Status", "Tanggal", "Pendata"});

            while (i < panjang && dataInsiden[i].pendata == targetPendata) {
                tabel.add_row({
                    to_string(dataInsiden[i].id),
                    dataInsiden[i].kejadian,
                    dataInsiden[i].tingkat,
                    dataInsiden[i].status,
                    dataInsiden[i].tanggal,
                    dataInsiden[i].pendata
                });
                i++;
            }

            cout << "Daftar Insiden " << targetPendata << ":" << endl;
            cout << tabel << endl;
        }
    }
    catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
}

void hapusInsiden(){
    try {
        if(panjang == 0) {
            throw runtime_error("Belum ada insiden untuk dihapus!");
        }

        int index = inputAngka("Masukkan ID insiden: ");

        if (index <= 0) {
            throw invalid_argument("ID harus lebih dari 0!");
        }

        int posisi = cariInsiden(index);

        if(posisi == -1){
            throw runtime_error("ID insiden tidak valid atau tidak ditemukan!");
        }

        for(int i = posisi; i < panjang - 1; i++)
            dataInsiden[i] = dataInsiden[i + 1];

        panjang--;

        cout << "Insiden berhasil dihapus" << endl;
    }
    catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
}

void menuUtama(string &username_login, string &role){
    int pilih_menu;

    while(login){
        try {
            cout << "\n=== MENU UTAMA ===" << endl;
            cout << "Login sebagai: " << username_login << " (" << role << ")" << endl;
            cout << "1. Tambah Insiden" << endl;
            cout << "2. Lihat Insiden" << endl;
            cout << "3. Ubah Status Insiden" << endl;
            cout << "4. Cari Insiden" << endl;
            cout << "5. Logout" << endl;
            if(role == "admin")
                cout << "6. Hapus Insiden" << endl;

            pilih_menu = inputAngka("Pilih menu: ");

            if(role == "admin"){
                if(pilih_menu < 1 || pilih_menu > 6){
                    throw invalid_argument("Pilih angka di antara 1 - 6!");
                }
            }
            else{
                if(pilih_menu < 1 || pilih_menu > 5){
                    throw invalid_argument("Pilih angka di antara 1 - 5!");
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
                    cariInsiden(username_login, role);
                    break;

                case 5:
                    login = false;
                    username_login = "";
                    role = "";
                    cout << "Logout berhasil!" << endl;
                    break;

                case 6:
                    if (role == "admin") {
                        hapusInsiden();
                    }
                    else {
                        throw runtime_error("Akses ditolak! Fitur ini hanya untuk admin.");
                    }
                    break;
            }
        }
        catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
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
        try {
            if(!login){
                cout << "\nSISTEM MANAJEMEN INSIDEN (SIEM)" << endl;
                cout << "1. Login" << endl;
                cout << "2. Register" << endl;
                cout << "3. Keluar" << endl;

                pilihan = inputAngka("Pilih menu: ");

                if (pilihan < 1 || pilihan > 3) {
                    throw out_of_range("Silakan pilih menu 1 - 3");
                }
            }

            switch(pilihan){
                case 1:
                    while(percobaan_login < 3 && !login){
                        username = input("Silakan Input Username Anda: ");
                        password = input("Silakan input password Anda: ");

                        if(username == "") {
                            throw invalid_argument("Username tidak boleh kosong!");
                        }

                        if (password == "") {
                            throw invalid_argument("Password tidak boleh kosong!");
                        }

                        if(loginUser(username, password, role)){
                            login = true;
                            username_login = username;
                            percobaan_login = 0;

                            cout << "Login Berhasil!" << endl;
                            menuUtama(username_login, role);
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
                    if(jumlah_user >= max_user){
                        throw out_of_range("overflow error!");
                    }

                    username = input("Input username anda: ");
                    password = input("Input password anda: ");

                    if(registerUser(username, password))
                        cout << "Registrasi Berhasil!" << endl;
                    else
                        cout << "Username sudah terdaftar" << endl;
                    break;

                case 3:
                    cout << "Terima kasih telah menggunakan program ini" << endl;
                    return 0;
            }
        }
        catch (const exception &e) {
            cout << "Error: " << e.what() << endl;

            if (percobaan_login >= 3) {
                return 0;
            }
        }
    }

    return 0;
}
