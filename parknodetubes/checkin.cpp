void checkIn() {
    cout << "\n========== CHECK-IN KENDARAAN ==========\n";

    Kendaraan vehicle;

    cout << "Nomor Plat       : ";
    getline(cin, vehicle.platNomor);
    vehicle.platNomor = normalizePlate(vehicle.platNomor);

    if (vehicle.platNomor.empty()) {
        cout << "Nomor plat tidak boleh kosong.\n";
        return;
    }

    if (plateExists(vehicle.platNomor)) {
        cout << "Kendaraan dengan plat tersebut sudah terdaftar.\n";
        return;
    }

    cout << "Nama Pemilik     : ";
    getline(cin, vehicle.namaPemilik);

    if (vehicle.namaPemilik.empty()) {
        cout << "Nama pemilik tidak boleh kosong.\n";
        return;
    }

    cout << "Jenis Kendaraan\n";
    cout << "1. Motor\n";
    cout << "2. Mobil\n";

    int choice = readInt("Pilih jenis: ", 1, 2);
    vehicle.jenis = (choice == 1) ? "Motor" : "Mobil";

    vehicle.nomorSlot = "";
    vehicle.waktuMasuk = 0;

    if (slots.isAvailable(vehicle.jenis)) {
        vehicle.nomorSlot = slots.allocate(vehicle.jenis);
        vehicle.waktuMasuk = time(nullptr);

        if (activeVehicles.insert(vehicle)) {
            vehicleIndex.insert(vehicle);

            cout << "\nCHECK-IN BERHASIL!\n";
            cout << "Plat       : " << vehicle.platNomor << "\n";
            cout << "Pemilik    : " << vehicle.namaPemilik << "\n";
            cout << "Jenis      : " << vehicle.jenis << "\n";
            cout << "Nomor Slot : " << vehicle.nomorSlot << "\n";
            cout << "Waktu Masuk: "
                 << timeToString(vehicle.waktuMasuk) << "\n";
        } else {
            slots.release(vehicle.nomorSlot);
            cout << "Gagal menambahkan kendaraan.\n";
        }
    } else {
        if (vehicle.jenis == "Motor")
            motorQueue.enqueue(vehicle);
        else
            carQueue.enqueue(vehicle);

        cout << "\nSLOT " << vehicle.jenis << " PENUH.\n";
        cout << "Kendaraan dimasukkan ke antrean "
             << (vehicle.jenis == "Motor" ? "motor" : "mobil")
             << ".\n";

        cout << "Posisi antrean: "
             << (vehicle.jenis == "Motor"
                 ? motorQueue.getSize()
                 : carQueue.getSize())
             << "\n";
    }
}