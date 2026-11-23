# PARKNODE - Smart Parking System

## Persyaratan
- Compiler C++ yang mendukung C++17 (G++ / MinGW / Code::Blocks / VS Code).
- Folder `data` harus berada satu tingkat dengan file `main.cpp`.

## Struktur folder
```text
ParkNode/
├── main.cpp
├── README.txt
└── data/
```

## Cara compile dengan G++
Buka terminal pada folder ParkNode, lalu jalankan:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o ParkNode
```

## Cara menjalankan
Windows:
```bash
ParkNode.exe
```

Linux/macOS:
```bash
./ParkNode
```

## Modul utama dalam main.cpp
1. Dashboard: `ParkingSystem::dashboard()`
2. Check-In: `ParkingSystem::checkIn()`
3. Check-Out dan pembayaran: `ParkingSystem::checkOut()`
4. Linked List: class `ParkingList`
5. Queue: class `ParkingQueue`
6. Stack: class `HistoryStack`
7. BST: class `VehicleTree`
8. Slot: class `ParkingSlots`
9. File I/O: `saveData()` dan `loadData()`

## Aturan simulasi
- 20 slot motor (M01-M20).
- 10 slot mobil (C01-C10).
- Antrean motor dan mobil terpisah.
- FIFO untuk antrean.
- LIFO untuk riwayat.
- Tarif motor: Rp2.000 jam pertama, Rp1.000 per jam berikutnya.
- Tarif mobil: Rp5.000 jam pertama, Rp2.000 per jam berikutnya.
- Durasi dibulatkan ke atas per jam.
- Waktu parkir dimulai saat kendaraan mendapatkan slot, bukan saat masuk antrean.

## Catatan
Ini adalah prototype akademik untuk simulasi. Belum mencakup integrasi pembayaran elektronik, database server, keamanan akun, atau sinkronisasi multi-terminal.
