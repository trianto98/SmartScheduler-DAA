#include <bits/stdc++.h>
using namespace std;

struct Job {
    int id;
    long long p; // processing time
    long long d; // deadline
    long long completion; // computed later
    bool onTime;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const string path = "../data/sample.txt";
    ifstream fin(path);
    if (!fin.is_open()) {
        cerr << "Gagal membuka file: " << path << "\n";
        return 1;
    }

    int n;
    if (!(fin >> n)) {
        cerr << "Format file salah atau file kosong. Baris pertama harus berisi jumlah job (n).\n";
        return 1;
    }
    if (n < 0) {
        cerr << "Jumlah job negatif tidak valid.\n";
        return 1;
    }

    vector<Job> tugas;
    tugas.reserve(n);

    for (int i = 1; i <= n; ++i) {
        long long p, d;
        if (!(fin >> p >> d)) {
            cerr << "Input kurang. Pastikan ada " << n << " baris job setelah baris pertama.\n";
            return 1;
        }
        if (p < 0) {
            cerr << "Processing time (p) harus non-negatif. Job " << i << " bermasalah.\n";
            return 1;
        }
        Job job;
        job.id = i;
        job.p = p;
        job.d = d;
        job.completion = 0;
        job.onTime = false;
        tugas.push_back(job);
    }
    fin.close();

    // EDF sort: pertama mencari berdasarkan deadline, jika deadline sama diurut dengan waktu pengerjaan
    sort(tugas.begin(), tugas.end(), [](const Job &a, const Job &b) {
        if (a.d != b.d) return a.d < b.d;
        return a.p < b.p;
    });

    // Menghitung waktu
    long long currentTime = 0;
    long long totalWaktu = 0; // Total waktu yang dibutuhkan
    int onTimeCount = 0;

    cout << "Urutan dan Jadwal (EDF):\n";
    cout << "---------------------------------\n";

    for (size_t i = 0; i < tugas.size(); ++i) {
        currentTime += tugas[i].p;
        tugas[i].completion = currentTime;
        tugas[i].onTime = (tugas[i].completion <= tugas[i].d);
        totalWaktu += tugas[i].completion;
        if (tugas[i].onTime) ++onTimeCount;

        cout << "Tugas " << tugas[i].id
             << " (p=" << tugas[i].p << ", d=" << tugas[i].d << ") "
             << "Waktu=" << tugas[i].completion
             << " -> " << (tugas[i].onTime ? "On time" : "Telat")
             << "\n";
    }

    cout << "---------------------------------\n";
    cout << "Total waktu penyelesaian = " << totalWaktu << "\n";
    cout << "Total tugas = " << n << "\n";
    cout << "Total tugas selesai tepat waktu = " << onTimeCount << "/" << n << "\n";

    double successRate = (n == 0) ? 0.0 : (100.0 * onTimeCount / n);
    cout.setf(ios::fixed);
    cout << "Success rate = " << setprecision(2) << successRate << "%\n";

    // Untuk step-step penyelesaian
    cout << "\nStep by step pengerjaan: ";
    for (size_t i = 0; i < tugas.size(); ++i) {
        if (i) cout << " ";
        cout << tugas[i].id;
    }
    cout << "\n";

    return 0;
}
