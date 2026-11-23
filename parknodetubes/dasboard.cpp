void dashboard() {
    int choice;

    do {
        cout << "\n";
        cout << "====================================================\n";
        cout << "                    P A R K N O D E                 \n";
        cout << "              SMART PARKING MANAGEMENT             \n";
        cout << "====================================================\n";
        cout << " Kapasitas: 30 Slot | Motor: 20 | Mobil: 10\n";
        cout << "----------------------------------------------------\n";
        cout << " [1] Check-In Kendaraan\n";
        cout << " [2] Check-Out Kendaraan & Pembayaran\n";
        cout << " [3] Data Kendaraan Parkir\n";
        cout << " [4] Antrean Kendaraan\n";
        cout << " [5] Pencarian Kendaraan\n";
        cout << " [6] Batalkan Antrean\n";
        cout << " [7] Riwayat Kendaraan Keluar\n";
        cout << " [8] Informasi Slot Parkir\n";
        cout << " [9] Laporan Parkir\n";
        cout << " [10] Simpan Data\n";
        cout << " [0] Simpan & Keluar\n";
        cout << "====================================================\n";

        choice = readInt("Pilih menu: ", 0, 10);

        switch (choice) {
            case 1: checkIn(); break;
            case 2: checkOut(); break;
            case 3: showActiveVehicles(); break;
            case 4: showQueues(); break;
            case 5: searchVehicle(); break;
            case 6: cancelQueue(); break;
            case 7: showHistory(); break;
            case 8: showSlots(); break;
            case 9: showReport(); break;
            case 10: saveData(); break;

            case 0:
                saveData();
                cout << "Terima kasih telah menggunakan ParkNode.\n";
                break;
        }

        if (choice != 0) pauseScreen();

    } while (choice != 0);
}