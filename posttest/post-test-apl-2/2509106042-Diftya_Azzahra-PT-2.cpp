#include <iostream>
#include <string>
#include "tabulate/table.hpp"
using namespace std;
using namespace tabulate;

#define max_user 100
#define max_insiden 300

struct insiden {
    int id;
    int id_user;
    string kejadian;
    string tingkat;
    string status;
    string tanggal;
    string pendata;
};

struct user {
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

int main() {
    int pilihan, index;
    int pilih_menu;

    string username, password;
    string username_login = "";
    string role = "";
    string kejadian, tingkat_keparahan, status, tanggal, pendata;

    while (true) {
        if (!login) {
            cout << "\nSISTEM MANAJEMEN INSIDEN (SIEM)" << endl;
            cout << "1. Login" << endl;
            cout << "2. Register" << endl;
            cout << "3. Keluar" << endl;
            cout << "Pilih menu: ";
            cin >> pilihan;

            switch (pilihan) {
                case 1: {
                    bool ketemu = false;

                    cout << "Silakan input username Anda: ";
                    cin >> username;
                    cout << "Silakan input password Anda: ";
                    cin >> password;

                    if (username == "diftya" && password == "042") {
                        login = true;
                        username_login = username;
                        role = "admin";
                        cout << "Login Berhasil!" << endl;
                    } else {
                        for (int i = 0; i < jumlah_user; i++) {
                            if (pengguna[i].username == username && pengguna[i].password == password) {
                                login = true;
                                username_login = username;
                                role = "user";
                                ketemu = true;
                                cout << "Login Berhasil!" << endl;
                                break;
                            }
                        }

                        if (!ketemu) {
                            cout << "Username atau passwordmu salah" << endl;
                        }
                    }
                    break;
                }

                case 2: {
                    bool sudah_ada = false;

                    if (jumlah_user < max_user) {
                        cout << "Silakan input username: ";
                        cin >> username;
                        cout << "Silakan buat password Anda: ";
                        cin >> password;

                        if (username == "diftya") {
                            cout << "Username tidak boleh dipakai" << endl;
                        } else {
                            for (int i = 0; i < jumlah_user; i++) {
                                if (pengguna[i].username == username) {
                                    sudah_ada = true;
                                    break;
                                }
                            }

                            if (sudah_ada == true) {
                                cout << "Username telah terdaftar" << endl;
                            } else {
                                pengguna[jumlah_user].username = username;
                                pengguna[jumlah_user].password = password;
                                pengguna[jumlah_user].role = "user";
                                jumlah_user++;
                                cout << "Registrasi Berhasil!" << endl;
                            }
                        }
                    } else {
                        cout << "Kapasitas user penuh" << endl;
                    }
                    break;
                }

                case 3:
                    cout << "Terima kasih telah menggunakan program ini." << endl;
                    return 0;

                default:
                    cout << "Pilihan tidak valid." << endl;
            }
        }

        while (login == true) {
            if (role == "user") {
                cout << "\n=== MENU UTAMA ===" << endl;
                cout << "Login sebagai: " << username_login << " (" << role << ")" << endl;
                cout << "1. Tambah Insiden" << endl;
                cout << "2. Lihat Insiden" << endl;
                cout << "3. Ubah Status Insiden" << endl;
                cout << "4. Logout" << endl; }
            else {
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

                switch (pilih_menu) {
                    case 1: {
                        if (panjang < max_insiden) {
                            cin.ignore();

                            cout << "Tambah Insiden" << endl;

                            int id_user = 1;
                            for (int i = 0; i < panjang; i++) {
                                if (dataInsiden[i].pendata == username_login) {
                                    id_user++;
                                }
                            }

                            dataInsiden[panjang].id = id_counter;
                            dataInsiden[panjang].id_user = id_user;

                            cout << "Laporan kejadian: ";
                            getline(cin, kejadian);
                            dataInsiden[panjang].kejadian = kejadian;

                            cout << "Input tingkat keparahan (Critical / High / Medium / Low): ";
                            getline(cin, tingkat_keparahan);

                            while (tingkat_keparahan != "Critical" &&
                                tingkat_keparahan != "High" &&
                                tingkat_keparahan != "Medium" &&
                                tingkat_keparahan != "Low") {
                                cout << "Input tidak valid!" << endl;
                                cout << "Masukkan ulang tingkat keparahan (Critical / High / Medium / Low): ";
                                getline(cin, tingkat_keparahan);
                            }

                            dataInsiden[panjang].tingkat = tingkat_keparahan;

                            status = "open";
                            dataInsiden[panjang].status = status;

                            cout << "Input Tanggal (DD/MM/YYYY): ";
                            getline(cin, tanggal);
                            dataInsiden[panjang].tanggal = tanggal;

                            pendata = username_login;
                            dataInsiden[panjang].pendata = pendata;

                            panjang++;
                            id_counter++;

                            cout << "Insiden berhasil ditambahkan!" << endl;
                            cout << "Tekan Enter untuk lanjut";
                            cin.get();
                        } else {
                            cout << "Kapasitas penuh!" << endl;
                            cin.ignore();
                            cout << "Tekan Enter untuk lanjut";
                            cin.get();
                        }
                        break;
                    }
                    case 2: {
                        if (panjang == 0) {
                            cout << "Belum ada insiden yang tercatat" << endl;
                        } else {
                            cout << "Daftar Insiden" << endl;

                            Table tabel;
                            tabel.add_row({"ID", "Kejadian", "Tingkat Keparahan", "Status", "Tanggal Kejadian", "Pendata"});

                            for (int i = 0; i < panjang; i++) {
                                if (role == "admin" || dataInsiden[i].pendata == username_login) {
                                    tabel.add_row({
                                        (role == "admin" ? to_string(dataInsiden[i].id) : to_string(dataInsiden[i].id_user)),
                                        dataInsiden[i].kejadian,
                                        dataInsiden[i].tingkat,
                                        dataInsiden[i].status,
                                        dataInsiden[i].tanggal,
                                        dataInsiden[i].pendata
                                    });
                                }
                            }

                            tabel[0].format()
                                .font_style({FontStyle::bold})
                                .font_align(FontAlign::center);

                            cout << tabel << endl;
                        }
                        cin.ignore();
                        cout << "Tekan Enter untuk lanjut";
                        cin.get();
                        break;
                    }

                    case 3: {
                        if (panjang == 0) {
                            cout << "Belum ada insiden untuk diubah" << endl;
                            cin.ignore();
                            cout << "Tekan Enter untuk lanjut";
                            cin.get();
                        } else {
                            cout << "Mengubah status Insiden" << endl;

                            for (int i = 0; i < panjang; i++) {
                                if (role == "admin" || dataInsiden[i].pendata == username_login) {
                                    cout << (role == "admin" ? dataInsiden[i].id : dataInsiden[i].id_user)
                                         << ". " << dataInsiden[i].kejadian
                                         << " (" << dataInsiden[i].status << ")" << endl;
                                }
                            }

                            cout << "Silakan input nomor insiden yang ingin diubah: ";
                            cin >> index;

                            int posisi = -1;
                            for (int i = 0; i < panjang; i++) {
                                if (role == "admin") {
                                    if (dataInsiden[i].id == index) {
                                        posisi = i;
                                        break;
                                    }
                                } else {
                                    if (dataInsiden[i].id_user == index && dataInsiden[i].pendata == username_login) {
                                        posisi = i;
                                        break;
                                    }
                                }
                            }

                            if (posisi != -1) {
                                cin.ignore();
                                cout << "Masukkan status baru: ";
                                getline(cin, dataInsiden[posisi].status);
                                cout << "Status berhasil diubah!" << endl;
                            } else {
                                cout << "Id tidak valid" << endl;
                                cin.ignore();
                            }

                            cout << "Tekan Enter untuk lanjut";
                            cin.get();
                        }
                        break;
                    }

                    case 4: {
                        login = false;
                        username_login = "";
                        role = "";
                        cout << "Logout berhasil!" << endl;
                        break;
                    }

                    case 5: {
                        if (role != "admin") {
                            cout << "Input tidak valid." << endl;
                            cin.ignore();
                            cout << "Tekan Enter untuk lanjut";
                            cin.get();
                            break;
                        }

                        if (panjang == 0) {
                            cout << "Belum ada insiden untuk dihapus" << endl;
                            cin.ignore();
                            cout << "Tekan Enter untuk lanjut";
                            cin.get();
                        } else {
                            for (int i = 0; i < panjang; i++) {
                                cout << dataInsiden[i].id << ". " << dataInsiden[i].kejadian << endl;
                            }

                            cout << "Masukkan nomor insiden yang ingin dihapus: ";
                            cin >> index;

                            int posisi = -1;
                            for (int i = 0; i < panjang; i++) {
                                if (dataInsiden[i].id == index) {
                                    posisi = i;
                                    break;
                                }
                            }

                            if (posisi != -1) {
                                for (int i = posisi; i < panjang - 1; i++) {
                                    dataInsiden[i] = dataInsiden[i + 1];
                                }
                                panjang--;
                                cout << "Insiden berhasil dihapus." << endl;
                            } else {
                                cout << "Nomor tidak valid." << endl;
                            }

                            cin.ignore();
                            cout << "Tekan Enter untuk lanjut";
                            cin.get();
                        }
                        break;
                    }
                    default:
                        cout << "Pilihan tidak valid." << endl;
                        cin.ignore();
                        cout << "Tekan Enter untuk lanjut";
                        cin.get();
                }
            }
        }
        return 0;
    }

    
