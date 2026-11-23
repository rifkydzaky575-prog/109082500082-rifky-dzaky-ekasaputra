#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>
#include <fstream>
#include <sstream>
#include <limits>
#include <cctype>

using namespace std;

// ============================================================
// PARKNODE - SMART PARKING SYSTEM
// C++17 | Console Application
// ============================================================

const int MOTOR_CAPACITY = 20;
const int CAR_CAPACITY = 10;
const int TOTAL_CAPACITY = MOTOR_CAPACITY + CAR_CAPACITY;

const long long MOTOR_FIRST_HOUR = 2000;
const long long MOTOR_NEXT_HOUR  = 1000;
const long long CAR_FIRST_HOUR   = 5000;
const long long CAR_NEXT_HOUR    = 2000;

string normalizePlate(string plate) {
    string result;
    for (char c : plate) {
        if (!isspace(static_cast<unsigned char>(c))) {
            result += static_cast<char>(toupper(static_cast<unsigned char>(c)));
        }
    }
    return result;
}

string currentDateTime() {
    time_t now = time(nullptr);
    tm* local = localtime(&now);
    if (!local) return "Unknown";
    stringstream ss;
    ss << put_time(local, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

string timeToString(time_t value) {
    tm* local = localtime(&value);
    if (!local) return "Unknown";
    stringstream ss;
    ss << put_time(local, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

string cleanField(string value) {
    for (char& c : value) {
        if (c == '|') c = '/';
        if (c == '\n' || c == '\r') c = ' ';
    }
    return value;
}

void pauseScreen() {
    cout << "\nTekan ENTER untuk melanjutkan...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int readInt(const string& prompt, int minValue, int maxValue) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value && value >= minValue && value <= maxValue) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        cout << "Input tidak valid. Masukkan angka " << minValue
             << " sampai " << maxValue << ".\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

struct Kendaraan {
    string platNomor;
    string namaPemilik;
    string jenis;       // Motor / Mobil
    string nomorSlot;   // M01-M20 / C01-C10
    time_t waktuMasuk = 0;
    time_t waktuKeluar = 0;
    int durasiMenit = 0;
    long long biaya = 0;
};

struct Node {
    Kendaraan data;
    Node* next;
    explicit Node(const Kendaraan& value) : data(value), next(nullptr) {}
};

struct QueueNode {
    Kendaraan data;
    QueueNode* next;
    explicit QueueNode(const Kendaraan& value) : data(value), next(nullptr) {}
};

struct StackNode {
    Kendaraan data;
    StackNode* next;
    explicit StackNode(const Kendaraan& value) : data(value), next(nullptr) {}
};

struct TreeNode {
    Kendaraan data;
    TreeNode* left;
    TreeNode* right;
    explicit TreeNode(const Kendaraan& value)
        : data(value), left(nullptr), right(nullptr) {}
};

// ============================================================
// ADT LINKED LIST: KENDARAAN YANG SEDANG PARKIR
// ============================================================

class ParkingList {
private:
    Node* head;

public:
    ParkingList() : head(nullptr) {}
    ~ParkingList() { clear(); }

    bool isEmpty() const { return head == nullptr; }

    bool contains(const string& plate) const {
        Node* current = head;
        while (current) {
            if (current->data.platNomor == plate) return true;
            current = current->next;
        }
        return false;
    }

    bool insert(const Kendaraan& vehicle) {
        if (contains(vehicle.platNomor)) return false;
        Node* freshNode = new Node(vehicle);
        freshNode->next = head;
        head = freshNode;
        return true;
    }

    bool remove(const string& plate, Kendaraan& removed) {
        Node* current = head;
        Node* previous = nullptr;

        while (current) {
            if (current->data.platNomor == plate) {
                if (previous == nullptr) head = current->next;
                else previous->next = current->next;

                removed = current->data;
                delete current;
                return true;
            }
            previous = current;
            current = current->next;
        }
        return false;
    }

    Kendaraan* search(const string& plate) {
        Node* current = head;
        while (current) {
            if (current->data.platNomor == plate) return &current->data;
            current = current->next;
        }
        return nullptr;
    }

    int countType(const string& type) const {
        int count = 0;
        Node* current = head;
        while (current) {
            if (current->data.jenis == type) count++;
            current = current->next;
        }
        return count;
    }

    int countAll() const {
        int count = 0;
        Node* current = head;
        while (current) {
            count++;
            current = current->next;
        }
        return count;
    }

    void display() const {
        if (!head) {
            cout << "Belum ada kendaraan yang sedang parkir.\n";
            return;
        }

        cout << left << setw(16) << "Plat"
             << setw(20) << "Pemilik"
             << setw(10) << "Jenis"
             << setw(10) << "Slot"
             << "Waktu Masuk\n";
        cout << string(78, '-') << "\n";

        Node* current = head;
        while (current) {
            cout << left << setw(16) << current->data.platNomor
                 << setw(20) << current->data.namaPemilik.substr(0, 18)
                 << setw(10) << current->data.jenis
                 << setw(10) << current->data.nomorSlot
                 << timeToString(current->data.waktuMasuk) << "\n";
            current = current->next;
        }
    }

    void save(ofstream& out) const {
        Node* current = head;
        while (current) {
            const Kendaraan& v = current->data;
            out << "P|" << cleanField(v.platNomor) << "|"
                << cleanField(v.namaPemilik) << "|" << v.jenis << "|"
                << v.nomorSlot << "|" << static_cast<long long>(v.waktuMasuk)
                << "\n";
            current = current->next;
        }
    }

    void clear() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// ============================================================
// ADT QUEUE: ANTREAN MOTOR DAN MOBIL (FIFO)
// ============================================================

class ParkingQueue {
private:
    QueueNode* frontNode;
    QueueNode* rearNode;
    int size;

public:
    ParkingQueue() : frontNode(nullptr), rearNode(nullptr), size(0) {}
    ~ParkingQueue() { clear(); }

    bool isEmpty() const { return frontNode == nullptr; }
    int getSize() const { return size; }

    bool contains(const string& plate) const {
        QueueNode* current = frontNode;
        while (current) {
            if (current->data.platNomor == plate) return true;
            current = current->next;
        }
        return false;
    }

    void enqueue(const Kendaraan& vehicle) {
        QueueNode* freshNode = new QueueNode(vehicle);
        if (isEmpty()) frontNode = rearNode = freshNode;
        else {
            rearNode->next = freshNode;
            rearNode = freshNode;
        }
        size++;
    }

    bool dequeue(Kendaraan& result) {
        if (isEmpty()) return false;
        QueueNode* temp = frontNode;
        result = temp->data;
        frontNode = frontNode->next;
        if (!frontNode) rearNode = nullptr;
        delete temp;
        size--;
        return true;
    }

    bool removeByPlate(const string& plate) {
        QueueNode* current = frontNode;
        QueueNode* previous = nullptr;

        while (current) {
            if (current->data.platNomor == plate) {
                if (!previous) frontNode = current->next;
                else previous->next = current->next;

                if (current == rearNode) rearNode = previous;
                delete current;
                size--;
                if (!frontNode) rearNode = nullptr;
                return true;
            }
            previous = current;
            current = current->next;
        }
        return false;
    }

    void display() const {
        if (isEmpty()) {
            cout << "Antrean kosong.\n";
            return;
        }

        int number = 1;
        QueueNode* current = frontNode;
        cout << left << setw(6) << "No."
             << setw(16) << "Plat"
             << setw(20) << "Pemilik"
             << "Jenis\n";
        cout << string(52, '-') << "\n";

        while (current) {
            cout << left << setw(6) << number++
                 << setw(16) << current->data.platNomor
                 << setw(20) << current->data.namaPemilik.substr(0, 18)
                 << current->data.jenis << "\n";
            current = current->next;
        }
    }

    void save(ofstream& out) const {
        QueueNode* current = frontNode;
        while (current) {
            const Kendaraan& v = current->data;
            out << "Q|" << cleanField(v.platNomor) << "|"
                << cleanField(v.namaPemilik) << "|" << v.jenis << "\n";
            current = current->next;
        }
    }

    void clear() {
        Kendaraan temp;
        while (dequeue(temp)) {}
    }
};

// ============================================================
// ADT STACK: RIWAYAT KENDARAAN KELUAR (LIFO)
// ============================================================

class HistoryStack {
private:
    StackNode* topNode;
    int size;

public:
    HistoryStack() : topNode(nullptr), size(0) {}
    ~HistoryStack() { clear(); }

    bool isEmpty() const { return topNode == nullptr; }
    int getSize() const { return size; }

    void push(const Kendaraan& vehicle) {
        StackNode* freshNode = new StackNode(vehicle);
        freshNode->next = topNode;
        topNode = freshNode;
        size++;
    }

    bool pop(Kendaraan& result) {
        if (isEmpty()) return false;
        StackNode* temp = topNode;
        result = temp->data;
        topNode = topNode->next;
        delete temp;
        size--;
        return true;
    }

    void display() const {
        if (isEmpty()) {
            cout << "Belum ada riwayat kendaraan keluar.\n";
            return;
        }

        cout << left << setw(16) << "Plat"
             << setw(10) << "Jenis"
             << setw(10) << "Slot"
             << setw(14) << "Biaya"
             << "Waktu Keluar\n";
        cout << string(75, '-') << "\n";

        StackNode* current = topNode;
        while (current) {
            cout << left << setw(16) << current->data.platNomor
                 << setw(10) << current->data.jenis
                 << setw(10) << current->data.nomorSlot
                 << "Rp" << setw(12) << current->data.biaya
                 << timeToString(current->data.waktuKeluar) << "\n";
            current = current->next;
        }
    }

    void save(ofstream& out) const {
        // Simpan dari top ke bawah. Saat load, dibangun ulang dari bawah ke atas.
        StackNode* current = topNode;
        while (current) {
            const Kendaraan& v = current->data;
            out << "H|" << cleanField(v.platNomor) << "|"
                << cleanField(v.namaPemilik) << "|" << v.jenis << "|"
                << v.nomorSlot << "|" << static_cast<long long>(v.waktuMasuk)
                << "|" << static_cast<long long>(v.waktuKeluar)
                << "|" << v.durasiMenit << "|" << v.biaya << "\n";
            current = current->next;
        }
    }

    void clear() {
        Kendaraan temp;
        while (pop(temp)) {}
    }
};

// ============================================================
// ADT BINARY SEARCH TREE: INDEKS KENDARAAN AKTIF
// ============================================================

class VehicleTree {
private:
    TreeNode* root;

    TreeNode* insertNode(TreeNode* node, const Kendaraan& vehicle) {
        if (!node) return new TreeNode(vehicle);

        if (vehicle.platNomor < node->data.platNomor)
            node->left = insertNode(node->left, vehicle);
        else if (vehicle.platNomor > node->data.platNomor)
            node->right = insertNode(node->right, vehicle);

        return node;
    }

    TreeNode* searchNode(TreeNode* node, const string& plate) const {
        if (!node || node->data.platNomor == plate) return node;
        if (plate < node->data.platNomor)
            return searchNode(node->left, plate);
        return searchNode(node->right, plate);
    }

    TreeNode* minimumNode(TreeNode* node) {
        while (node && node->left) node = node->left;
        return node;
    }

    TreeNode* deleteNode(TreeNode* node, const string& plate) {
        if (!node) return nullptr;

        if (plate < node->data.platNomor)
            node->left = deleteNode(node->left, plate);
        else if (plate > node->data.platNomor)
            node->right = deleteNode(node->right, plate);
        else {
            if (!node->left) {
                TreeNode* rightChild = node->right;
                delete node;
                return rightChild;
            }
            if (!node->right) {
                TreeNode* leftChild = node->left;
                delete node;
                return leftChild;
            }

            TreeNode* successor = minimumNode(node->right);
            node->data = successor->data;
            node->right = deleteNode(node->right, successor->data.platNomor);
        }
        return node;
    }

    void clearNode(TreeNode* node) {
        if (!node) return;
        clearNode(node->left);
        clearNode(node->right);
        delete node;
    }

    void inorder(TreeNode* node) const {
        if (!node) return;
        inorder(node->left);
        cout << node->data.platNomor << " (" << node->data.jenis << ")  ";
        inorder(node->right);
    }

public:
    VehicleTree() : root(nullptr) {}
    ~VehicleTree() { clear(); }

    void insert(const Kendaraan& vehicle) {
        root = insertNode(root, vehicle);
    }

    bool search(const string& plate, Kendaraan& result) const {
        TreeNode* found = searchNode(root, plate);
        if (!found) return false;
        result = found->data;
        return true;
    }

    void remove(const string& plate) {
        root = deleteNode(root, plate);
    }

    void displayInorder() const {
        if (!root) cout << "BST kosong.\n";
        else {
            inorder(root);
            cout << "\n";
        }
    }

    void clear() {
        clearNode(root);
        root = nullptr;
    }
};

// ============================================================
// ADT PARKING SLOT: ARRAY 30 SLOT
// ============================================================

class ParkingSlots {
private:
    bool motorSlots[MOTOR_CAPACITY];
    bool carSlots[CAR_CAPACITY];

public:
    ParkingSlots() {
        for (int i = 0; i < MOTOR_CAPACITY; i++) motorSlots[i] = false;
        for (int i = 0; i < CAR_CAPACITY; i++) carSlots[i] = false;
    }

    string allocate(const string& type) {
        if (type == "Motor") {
            for (int i = 0; i < MOTOR_CAPACITY; i++) {
                if (!motorSlots[i]) {
                    motorSlots[i] = true;
                    return "M" + (i + 1 < 10 ? string("0") : string("")) + to_string(i + 1);
                }
            }
        } else if (type == "Mobil") {
            for (int i = 0; i < CAR_CAPACITY; i++) {
                if (!carSlots[i]) {
                    carSlots[i] = true;
                    return "C" + (i + 1 < 10 ? string("0") : string("")) + to_string(i + 1);
                }
            }
        }
        return "";
    }

    void release(const string& slot) {
        if (slot.size() < 2) return;
        try {
            int number = stoi(slot.substr(1));
            if (slot[0] == 'M' && number >= 1 && number <= MOTOR_CAPACITY)
                motorSlots[number - 1] = false;
            else if (slot[0] == 'C' && number >= 1 && number <= CAR_CAPACITY)
                carSlots[number - 1] = false;
        } catch (...) {}
    }

    bool isAvailable(const string& type) const {
        if (type == "Motor") {
            for (bool occupied : motorSlots) if (!occupied) return true;
        } else if (type == "Mobil") {
            for (bool occupied : carSlots) if (!occupied) return true;
        }
        return false;
    }

    void display() const {
        cout << "\n========== STATUS SLOT PARKNODE ==========\n";
        cout << "MOTOR (M01-M20)\n";
        for (int i = 0; i < MOTOR_CAPACITY; i++) {
            string slot = "M" + (i + 1 < 10 ? string("0") : string("")) + to_string(i + 1);
            cout << setw(5) << slot << "[" << (motorSlots[i] ? "ISI" : "KOSONG") << "] ";
            if ((i + 1) % 4 == 0) cout << "\n";
        }
        cout << "\nMOBIL (C01-C10)\n";
        for (int i = 0; i < CAR_CAPACITY; i++) {
            string slot = "C" + (i + 1 < 10 ? string("0") : string("")) + to_string(i + 1);
            cout << setw(5) << slot << "[" << (carSlots[i] ? "ISI" : "KOSONG") << "] ";
            if ((i + 1) % 2 == 0) cout << "\n";
        }
        cout << "==========================================\n";
    }

    int occupied(const string& type) const {
        int count = 0;
        if (type == "Motor") {
            for (bool value : motorSlots) if (value) count++;
        } else if (type == "Mobil") {
            for (bool value : carSlots) if (value) count++;
        }
        return count;
    }

    void reset() {
        for (int i = 0; i < MOTOR_CAPACITY; i++) motorSlots[i] = false;
        for (int i = 0; i < CAR_CAPACITY; i++) carSlots[i] = false;
    }

    void setOccupied(const string& slot) {
        if (slot.size() < 2) return;
        try {
            int number = stoi(slot.substr(1));
            if (slot[0] == 'M' && number >= 1 && number <= MOTOR_CAPACITY)
                motorSlots[number - 1] = true;
            else if (slot[0] == 'C' && number >= 1 && number <= CAR_CAPACITY)
                carSlots[number - 1] = true;
        } catch (...) {}
    }
};

// ============================================================
// PARKING SYSTEM: MENGHUBUNGKAN SEMUA ADT
// ============================================================

class ParkingSystem {
private:
    ParkingList activeVehicles;
    ParkingQueue motorQueue;
    ParkingQueue carQueue;
    HistoryStack history;
    VehicleTree vehicleIndex;
    ParkingSlots slots;
    long long totalRevenue;
    int totalCompleted;

    bool plateExists(const string& plate) const {
        return activeVehicles.contains(plate) ||
               motorQueue.contains(plate) ||
               carQueue.contains(plate);
    }

    long long calculateFee(int durationMinutes, const string& type) const {
        int billedHours = (durationMinutes + 59) / 60;
        if (billedHours < 1) billedHours = 1;

        if (type == "Motor") {
            return MOTOR_FIRST_HOUR +
                   static_cast<long long>(billedHours - 1) * MOTOR_NEXT_HOUR;
        }
        return CAR_FIRST_HOUR +
               static_cast<long long>(billedHours - 1) * CAR_NEXT_HOUR;
    }

    void admitFromQueue(const string& type) {
        ParkingQueue& queue = (type == "Motor") ? motorQueue : carQueue;

        if (queue.isEmpty() || !slots.isAvailable(type)) return;

        Kendaraan waiting;
        if (!queue.dequeue(waiting)) return;

        string slot = slots.allocate(type);
        if (slot.empty()) {
            queue.enqueue(waiting);
            return;
        }

        waiting.nomorSlot = slot;
        waiting.waktuMasuk = time(nullptr); // Waktu parkir dimulai saat slot diperoleh.
        activeVehicles.insert(waiting);
        vehicleIndex.insert(waiting);

        cout << "\nAntrean berikutnya berhasil masuk parkir.\n";
        cout << "Plat: " << waiting.platNomor
             << " | Slot: " << waiting.nomorSlot << "\n";
    }

public:
    ParkingSystem() : totalRevenue(0), totalCompleted(0) {}

    // --------------------------------------------------------
    // CHECK-IN KENDARAAN
    // --------------------------------------------------------
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
                cout << "Waktu Masuk: " << timeToString(vehicle.waktuMasuk) << "\n";
            } else {
                slots.release(vehicle.nomorSlot);
                cout << "Gagal menambahkan kendaraan.\n";
            }
        } else {
            if (vehicle.jenis == "Motor") motorQueue.enqueue(vehicle);
            else carQueue.enqueue(vehicle);

            cout << "\nSLOT " << vehicle.jenis << " PENUH.\n";
            cout << "Kendaraan dimasukkan ke antrean "
                 << (vehicle.jenis == "Motor" ? "motor" : "mobil") << ".\n";
            cout << "Posisi antrean: "
                 << (vehicle.jenis == "Motor" ? motorQueue.getSize() : carQueue.getSize())
                 << "\n";
        }
    }

    // --------------------------------------------------------
    // CHECK-OUT DAN PEMBAYARAN
    // --------------------------------------------------------
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
        int durationMinutes = static_cast<int>((seconds + 59.0) / 60.0);
        int billedHours = (durationMinutes + 59) / 60;
        if (billedHours < 1) billedHours = 1;

        long long fee = calculateFee(durationMinutes, vehicle.jenis);

        cout << "\n------------- DETAIL PARKIR -------------\n";
        cout << "Plat Nomor    : " << vehicle.platNomor << "\n";
        cout << "Nama Pemilik  : " << vehicle.namaPemilik << "\n";
        cout << "Jenis         : " << vehicle.jenis << "\n";
        cout << "Nomor Slot    : " << vehicle.nomorSlot << "\n";
        cout << "Waktu Masuk   : " << timeToString(vehicle.waktuMasuk) << "\n";
        cout << "Waktu Keluar  : " << timeToString(exitTime) << "\n";
        cout << "Durasi        : " << durationMinutes << " menit ("
             << billedHours << " jam tagihan)\n";
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

        // Jika ada antrean, kendaraan paling depan langsung mendapatkan slot.
        admitFromQueue(removed.jenis);
    }

    // --------------------------------------------------------
    // FITUR DASHBOARD PENDUKUNG
    // --------------------------------------------------------
    void showActiveVehicles() const {
        cout << "\n========== DATA KENDARAAN PARKIR ==========\n";
        activeVehicles.display();
    }

    void showQueues() const {
        cout << "\n========== ANTREAN MOTOR ==========\n";
        motorQueue.display();
        cout << "\n========== ANTREAN MOBIL ==========\n";
        carQueue.display();
    }

    void searchVehicle() const {
        cout << "\n========== PENCARIAN KENDARAAN ==========\n";
        string plate;
        cout << "Masukkan nomor plat: ";
        getline(cin, plate);
        plate = normalizePlate(plate);

        Kendaraan vehicle;
        if (vehicleIndex.search(plate, vehicle)) {
            cout << "\nKENDARAAN DITEMUKAN\n";
            cout << "Plat       : " << vehicle.platNomor << "\n";
            cout << "Pemilik    : " << vehicle.namaPemilik << "\n";
            cout << "Jenis      : " << vehicle.jenis << "\n";
            cout << "Slot       : " << vehicle.nomorSlot << "\n";
            cout << "Waktu Masuk: " << timeToString(vehicle.waktuMasuk) << "\n";
        } else if (motorQueue.contains(plate) || carQueue.contains(plate)) {
            cout << "Kendaraan ditemukan, tetapi masih dalam antrean.\n";
        } else {
            cout << "Data kendaraan tidak ditemukan.\n";
        }
    }

    void cancelQueue() {
        cout << "\n========== BATALKAN ANTREAN ==========\n";
        string plate;
        cout << "Masukkan nomor plat: ";
        getline(cin, plate);
        plate = normalizePlate(plate);

        if (motorQueue.removeByPlate(plate) || carQueue.removeByPlate(plate))
            cout << "Antrean berhasil dibatalkan.\n";
        else
            cout << "Nomor plat tidak ditemukan dalam antrean.\n";
    }

    void showHistory() const {
        cout << "\n========== RIWAYAT KENDARAAN KELUAR ==========\n";
        history.display();
    }

    void showSlots() const {
        slots.display();
        cout << "Motor terisi : " << slots.occupied("Motor")
             << "/" << MOTOR_CAPACITY << "\n";
        cout << "Mobil terisi : " << slots.occupied("Mobil")
             << "/" << CAR_CAPACITY << "\n";
        cout << "Total terisi : " << activeVehicles.countAll()
             << "/" << TOTAL_CAPACITY << "\n";
    }

    void showReport() const {
        cout << "\n========== LAPORAN PARKNODE ==========\n";
        cout << "Kendaraan sedang parkir : " << activeVehicles.countAll() << "\n";
        cout << "Motor sedang parkir     : " << activeVehicles.countType("Motor") << "\n";
        cout << "Mobil sedang parkir     : " << activeVehicles.countType("Mobil") << "\n";
        cout << "Antrean motor           : " << motorQueue.getSize() << "\n";
        cout << "Antrean mobil           : " << carQueue.getSize() << "\n";
        cout << "Kendaraan selesai       : " << totalCompleted << "\n";
        cout << "Total pendapatan        : Rp" << totalRevenue << "\n";
        cout << "Slot motor kosong       : " << MOTOR_CAPACITY - slots.occupied("Motor") << "\n";
        cout << "Slot mobil kosong       : " << CAR_CAPACITY - slots.occupied("Mobil") << "\n";
    }

    // --------------------------------------------------------
    // FILE I/O
    // --------------------------------------------------------
    void saveData() const {
        ofstream out("data/parkNode_data.txt");
        if (!out) {
            cout << "Gagal membuka file penyimpanan. Pastikan folder data tersedia.\n";
            return;
        }

        out << "R|" << totalRevenue << "|" << totalCompleted << "\n";
        activeVehicles.save(out);
        motorQueue.save(out);
        carQueue.save(out);
        history.save(out);

        cout << "Data berhasil disimpan ke data/parkNode_data.txt\n";
    }

    void loadData() {
        ifstream in("data/parkNode_data.txt");
        if (!in) {
            cout << "File data belum tersedia. ParkNode dimulai dengan data kosong.\n";
            return;
        }

        string line;
        // Simpan sementara agar urutan TOP Stack tetap sama setelah proses load.
        HistoryStack loadedHistory;

        while (getline(in, line)) {
            if (line.empty()) continue;

            stringstream ss(line);
            string tag;
            getline(ss, tag, '|');

            if (tag == "R") {
                string revenue, completed;
                getline(ss, revenue, '|');
                getline(ss, completed, '|');
                try {
                    totalRevenue = stoll(revenue);
                    totalCompleted = stoi(completed);
                } catch (...) {}
            } else if (tag == "P") {
                Kendaraan v;
                string timestamp;
                getline(ss, v.platNomor, '|');
                getline(ss, v.namaPemilik, '|');
                getline(ss, v.jenis, '|');
                getline(ss, v.nomorSlot, '|');
                getline(ss, timestamp, '|');
                try { v.waktuMasuk = static_cast<time_t>(stoll(timestamp)); }
                catch (...) { continue; }

                if (!activeVehicles.contains(v.platNomor)) {
                    activeVehicles.insert(v);
                    vehicleIndex.insert(v);
                    slots.setOccupied(v.nomorSlot);
                }
            } else if (tag == "Q") {
                Kendaraan v;
                getline(ss, v.platNomor, '|');
                getline(ss, v.namaPemilik, '|');
                getline(ss, v.jenis, '|');
                if (!plateExists(v.platNomor)) {
                    if (v.jenis == "Motor") motorQueue.enqueue(v);
                    else if (v.jenis == "Mobil") carQueue.enqueue(v);
                }
            } else if (tag == "H") {
                Kendaraan v;
                string masuk, keluar, duration, fee;
                getline(ss, v.platNomor, '|');
                getline(ss, v.namaPemilik, '|');
                getline(ss, v.jenis, '|');
                getline(ss, v.nomorSlot, '|');
                getline(ss, masuk, '|');
                getline(ss, keluar, '|');
                getline(ss, duration, '|');
                getline(ss, fee, '|');
                try {
                    v.waktuMasuk = static_cast<time_t>(stoll(masuk));
                    v.waktuKeluar = static_cast<time_t>(stoll(keluar));
                    v.durasiMenit = stoi(duration);
                    v.biaya = stoll(fee);
                    loadedHistory.push(v);
                } catch (...) {}
            }
        }

        // File disimpan dari TOP ke bawah. Satu kali pemindahan membangun
        // kembali Stack dengan TOP yang sama seperti sebelum program ditutup.
        Kendaraan temp;
        while (loadedHistory.pop(temp)) history.push(temp);

        cout << "Data ParkNode berhasil dimuat.\n";
    }

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
};

// ============================================================
// MAIN PROGRAM
// ============================================================

int main() {
    ParkingSystem parkNode;

    cout << "Memuat data ParkNode...\n";
    parkNode.loadData();

    parkNode.dashboard();

    return 0;
}
