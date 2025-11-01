# SmartScheduler-DAA
Trianto 01085240015

# Overview
SmartScheduler ini adalah suatu mini project scheduler yang membantu untuk mengatur eksekusi tugas berbasis deadline
Setiap job memiliki 2 parameter utama:
- processing time (p)
- deadline (d)

Tujuan utamanya adalah untuk meminimalkan total waktu penyelesaian tugas sekaligus untuk meningkatkan jumlah tugas yang selesai sebelum deadline (SLA)
Algoritma yang digunakan adalah Earliest Deadline First (EDF) dengan tie-breaker tambahan menggunakan Shortest Processing Time (SPT). Saya menggunakan EDF dikarenakan pada real cloud system atau CPU cluster deadline adalah faktor yang terpenting. EDF adalah suatu greedy strategi yang sudah sangat dikenal dalam real-time scheduling dan memiliki nilai trade-off yang terbaik untuk runtime vs near-optimal result. Sorting hanya O(n log n) sehingga scalable di konteks production.

# Menjalankan Program
1. Masuk ke folder src/
2. Compile: g++ -std=c++17 -02 main.cpp -o SmartScheduler
3. Jalankan program: ./SmartScheduler

# Analisa Kompleksitas
- Sorting: O(n log n)
- Scheduling: O(n)
- Total: T(n) = O(n log n)

