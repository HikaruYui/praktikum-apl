// #include <iostream>
// #include <string>
// using namespace std;

// int main() {
//     string nama;
//     string password;
    
//     int salah = 0;

//     while(salah < 3) {
//         cout << "========= Kalkulator Konversi Satuan Panjang ========= " << endl;
//         cout << "Silakan masukkan nama Anda: " << endl;
//         cin >> nama;
//         cout << "Silakan masukkan Password Anda: " << endl;
//         cin >> password;

//         if (nama == "Diftya" && password == "042") {
//             cout << "Yay Login Berhasil!" << endl; 
//             break; }
//         else {
//             salah++;
//             cout << "Password Salah!" << endl;
//         }
    
//     }

//     if (salah == 3) {
//         cout << "Gagal login sebanyak 3 kali. Program akan dihentikan. " << endl;
//         return 0;
//     }

//     int pilih;
//     double nilai;

//     while (true) {
//         cout << "=== MENU KONVERSI ===\n";
//         cout << "1. Meter ke Kilometer dan Centimeter\n";
//         cout << "2. Kilometer ke Meter dan Centimeter\n";
//         cout << "3. Centimeter ke Meter dan Kilometer\n";
//         cout << "4. Keluar Program\n";
//         cout << "Pilihan Menu: "; 
//         cin >> pilih;

//         if (pilih == 1) {
//             cout << "Masukkan meter: ";
//             cin >> nilai;
//             cout << "Hasil = " << nilai / 1000 <<"Km dan " << " " 
//             << nilai * 100 << "cm " << endl;
//         }
//         else if (pilih == 2) {
//             cout << "Masukkan kilometer: " << endl;
//             cin >> nilai;
//             cout << "Hasil = " << nilai * 1000 << "Meter dan " <<
//             " " << nilai * 10000 << "cm" << endl;
//         }
//         else if (pilih == 3) {
//             cout << "Masukkan centimeter: " << endl;
//             cin >> nilai;
//             cout << "Hasil = " << nilai / 100 << "Meter dan " << " "
//             << nilai / 100000 << "Kilometer " << endl;
//         }
//         else if (pilih == 4) {
//             cout << "Terima kasih telah menggunakan program ini " << endl;
//             break;
//         }
//         else {
//             cout << "Pilihan tidak valid!\n\n";
//         }
//     }

// }

#include <iostream>
#include <string>
#include <cstdlib>
#include "tabulate.hpp"
using namespace std;
using namespace tabulate;

int main() {
    string nama;
    string password;
    
    int salah = 0;

    while(salah < 3) {
        cout << "========= Kalkulator Konversi Satuan Panjang ========= " << endl;
        cout << "Silakan masukkan nama Anda: " << endl;
        cin >> nama;
        cout << "Silakan masukkan Password Anda: " << endl;
        cin >> password;

        if (nama == "Diftya" && password == "042") {
            cout << "Yay Login Berhasil!" << endl; 
            break; }
        else {
            salah++;
            cout << "Password Salah!" << endl;
            cin.ignore();
            cin.get();
            system("clear");
        }
    
    }

    if (salah == 3) {
        cout << "Gagal login sebanyak 3 kali. Program akan dihentikan. " << endl;
        return 0;
    }

    int pilih;
    long long nilai;

    while (true) {

        system("clear");

        Table menu;
        menu.add_row({"No", "Menu"});
        menu.add_row({"1", "Meter ke Kilometer dan Centimeter"});
        menu.add_row({"2", "Kilometer ke Meter dan Centimeter"});
        menu.add_row({"3", "Centimeter ke Meter dan Kilometer"});
        menu.add_row({"4", "Keluar Program"});

        cout << menu << endl;

        cout << "Pilihan Menu: "; 
        cin >> pilih;
        system("clear");

        if (pilih == 1) {
            cout << "Masukkan meter: ";
            cin >> nilai;
            cout << "Hasil = " << nilai / 1000 <<"Km dan " << " " 
            << nilai * 100 << "cm " << endl;

            cout << "Tekan Enter untuk melanjutkan ";
            cin.ignore();
            cin.get();
        }
        else if (pilih == 2) {
            cout << "Masukkan kilometer: " << endl;
            cin >> nilai;
            cout << "Hasil = " << nilai * 1000 << "Meter dan " <<
            " " << nilai * 10000 << "cm" << endl;

            cout << "Tekan Enter untuk melanjutkan";
            cin.ignore();
            cin.get();
        }
        else if (pilih == 3) {
            cout << "Masukkan centimeter: " << endl;
            cin >> nilai;
            cout << "Hasil = " << nilai / 100 << "Meter dan " << " "
            << nilai / 100000 << "Kilometer " << endl;

            cout << "Tekan Enter untuk melanjutkan ";
            cin.ignore();
            cin.get();
        }
        else if (pilih == 4) {
            cout << "Terima kasih telah menggunakan program ini " << endl;
            break;
        }
        else {
            cout << "Pilihan tidak valid!\n\n";
        }
    }

}
