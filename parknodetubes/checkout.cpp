void checkOut() {
    cout << "\n========== CHECK-OUT & PEMBAYARAN ==========\n";

    string plate;

    cout << "Masukkan Nomor Plat: ";
    getline(cin, plate);
    plate = normalizePlate(plate);

    Kendaraan vehicle;

    if (!vehicleIndex.search(plate, vehicle)) {
        cout << "Kendaraan tidak ditemukan di area parkir.\n";
        return;
    }

    time_t exitTime = time(nullptr);

    if (exitTime < vehicle.waktuMasuk) {
        cout << "Waktu sistem tidak valid. Check-out dibatalkan.\n";
        return;
    }

    double seconds = difftime(exitTime, vehicle.waktuMasuk);

    int durationMinutes =
        static_cast<int>((seconds + 59.0) / 60.0);

    int billedHours = (durationMinutes + 59) / 60;

    if (billedHours < 1)
        billedHours = 1;

    long long fee = calculateFee(durationMinutes, vehicle.jenis);

    cout << "\n------------- DETAIL PARKIR -------------\n";
    cout << "Plat Nomor    : " << vehicle.platNomor << "\n";
    cout << "Nama Pemilik  : " << vehicle.namaPemilik << "\n";
    cout << "Jenis         : " << vehicle.jenis << "\n";
    cout << "Nomor Slot    : " << vehicle.nomorSlot << "\n";
    cout << "Waktu Masuk   : "
         << timeToString(vehicle.waktuMasuk) << "\n";
    cout << "Waktu Keluar  : "
         << timeToString(exitTime) << "\n";
    cout << "Durasi        : " << durationMinutes
         << " menit (" << billedHours << " jam tagihan)\n";
    cout << "Total Bayar   : Rp" << fee << "\n";
    cout << "-----------------------------------------\n";

    cout << "Konfirmasi pembayaran? (Y/N): ";

    string confirmation;
    getline(cin, confirmation);

    if (confirmation.empty() ||
        (toupper(static_cast<unsigned char>(confirmation[0])) != 'Y')) {
        cout << "Pembayaran dibatalkan. Data parkir tetap aktif.\n";
        return;
    }

    Kendaraan removed;

    if (!activeVehicles.remove(plate, removed)) {
        cout << "Gagal menghapus data parkir. Silakan periksa kembali.\n";
        return;
    }

    vehicleIndex.remove(plate);
    slots.release(removed.nomorSlot);

    removed.waktuKeluar = exitTime;
    removed.durasiMenit = durationMinutes;
    removed.biaya = fee;

    history.push(removed);

    totalRevenue += fee;
    totalCompleted++;

    cout << "\nPEMBAYARAN BERHASIL. TERIMA KASIH!\n";
    cout << "Slot " << removed.nomorSlot << " sekarang kosong.\n";

    admitFromQueue(removed.jenis);
}