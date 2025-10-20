Laporan Analisis Pola Segmen Garis

1. Analisis Window Size
Setelah melakukan evaluasi, ukuran window 3x3 piksel ditetapkan sebagai ukuran yang paling ideal dan efisien.

Alasan pemilihan ukuran 3x3:
- Minimalis & Efisien
Ukuran ini adalah yang terkecil yang memungkinkan analisis kontekstual. Ia menangkap sebuah piksel pusat beserta 8 tetangga langsungnya.

- Deteksi Arah
Ukuran 3x3 sudah cukup untuk secara akurat menentukan orientasi dasar dari sebuah segmen garis, yaitu horizontal, vertikal, dan diagonal.

- Tidak Efektifnya Ukuran Lebih Kecil
Window 2x2 tidak memiliki piksel pusat yang jelas, sehingga mustahil untuk menentukan arah garis secara konsisten.

2. Pola Window yang Sesuai untuk Segmen Garis
Dalam representasi berikut, 1 menandakan piksel yang merupakan bagian dari garis (berwarna), dan 0 menandakan piksel latar belakang (putih).

Pola-pola Ideal:
- Garis Horizontal Pola ini menunjukkan tiga piksel aktif berurutan secara horizontal di baris tengah.
    0 0 0
    1 1 1
    0 0 0

- Garis Vertikal Pola ini menunjukkan tiga piksel aktif berurutan secara vertikal di kolom tengah.
    0 1 0
    0 1 0
    0 1 0

- Garis Diagonal (Menurun ke Kanan) Pola ini menunjukkan piksel aktif yang membentuk garis diagonal dari kiri atas ke kanan bawah.
    1 0 0
    0 1 0
    0 0 1

- Garis Diagonal (Naik ke Kanan) Pola ini menunjukkan piksel aktif yang membentuk garis diagonal dari kiri bawah ke kanan atas.
    0 0 1
    0 1 0
    1 0 0

Pola-pola ini adalah bentuk ideal dan akan digunakan sebagai filter atau detector dalam algoritma otomatis. Setiap area pada kanvas yang cocok dengan salah satu dari pola ini akan ditandai sebagai kandidat segmen.

AI Usage
https://gemini.google.com/share/56012d161b93