# 🐔 KerebanAyam

<div align="center">
  
  ![KerebanAyam Logo](https://img.shields.io/badge/🐔-KerebanAyam-orange?style=for-the-badge)
  
  **Sistem Manajemen Peternakan Ayam Digital**
  
  [![GitHub license](https://img.shields.io/github/license/BagusA23/KerebanAyam?style=flat-square)](https://github.com/BagusA23/KerebanAyam/blob/main/LICENSE)
  [![GitHub stars](https://img.shields.io/github/stars/BagusA23/KerebanAyam?style=flat-square)](https://github.com/BagusA23/KerebanAyam/stargazers)
  [![GitHub forks](https://img.shields.io/github/forks/BagusA23/KerebanAyam?style=flat-square)](https://github.com/BagusA23/KerebanAyam/network)
  [![GitHub issues](https://img.shields.io/github/issues/BagusA23/KerebanAyam?style=flat-square)](https://github.com/BagusA23/KerebanAyam/issues)

  <p align="center">
    <a href="#-tentang-project">Tentang</a> •
    <a href="#-fitur">Fitur</a> •
    <a href="#-teknologi">Teknologi</a> •
    <a href="#-instalasi">Instalasi</a> •
    <a href="#-penggunaan">Penggunaan</a> •
    <a href="#-kontribusi">Kontribusi</a> •
    <a href="#-lisensi">Lisensi</a>
  </p>
  
</div>

---

## 📋 Tentang Project

**KerebanAyam** adalah sistem manajemen peternakan ayam digital yang dirancang untuk membantu peternak dalam mengelola kandang, monitoring kesehatan ayam, pencatatan produksi telur, dan manajemen keuangan peternakan. Aplikasi ini dibuat dengan tujuan untuk memodernisasi industri peternakan ayam di Indonesia.

### 🎯 Tujuan

- Memudahkan peternak dalam mengelola data peternakan
- Meningkatkan efisiensi produksi dan monitoring
- Menyediakan analisis data untuk pengambilan keputusan
- Digitalisasi proses tradisional peternakan ayam

## ✨ Fitur

### 🏠 Manajemen Kandang
- ✅ Pendaftaran dan pengelolaan kandang
- ✅ Monitoring kondisi lingkungan kandang
- ✅ Pencatatan kapasitas dan status kandang
- ✅ Penjadwalan pembersihan kandang

### 🐔 Manajemen Ayam
- ✅ Database ayam dengan informasi lengkap
- ✅ Tracking kesehatan dan status ayam
- ✅ Pencatatan vaksinasi dan pengobatan
- ✅ Monitoring pertumbuhan dan perkembangan

### 🥚 Produksi Telur
- ✅ Pencatatan produksi telur harian
- ✅ Analisis tren produksi
- ✅ Kualitas kontrol telur
- ✅ Laporan produktivitas

### 💰 Manajemen Keuangan
- ✅ Pencatatan pengeluaran pakan dan obat
- ✅ Tracking pendapatan dari penjualan
- ✅ Analisis profit dan loss
- ✅ Laporan keuangan bulanan

### 📊 Dashboard & Analitik
- ✅ Dashboard real-time
- ✅ Grafik produksi dan keuangan
- ✅ Prediksi tren produksi
- ✅ Export data ke Excel/PDF

## 🛠 Teknologi

### Frontend
- ![HTML5](https://img.shields.io/badge/HTML5-E34F26?style=flat-square&logo=html5&logoColor=white)
- ![CSS3](https://img.shields.io/badge/CSS3-1572B6?style=flat-square&logo=css3&logoColor=white)
- ![JavaScript](https://img.shields.io/badge/JavaScript-F7DF1E?style=flat-square&logo=javascript&logoColor=black)
- ![Bootstrap](https://img.shields.io/badge/Bootstrap-7952B3?style=flat-square&logo=bootstrap&logoColor=white)

### Backend
- ![PHP](https://img.shields.io/badge/PHP-777BB4?style=flat-square&logo=php&logoColor=white)
- ![MySQL](https://img.shields.io/badge/MySQL-4479A1?style=flat-square&logo=mysql&logoColor=white)

### Tools
- ![Git](https://img.shields.io/badge/Git-F05032?style=flat-square&logo=git&logoColor=white)
- ![VS Code](https://img.shields.io/badge/VS%20Code-007ACC?style=flat-square&logo=visual-studio-code&logoColor=white)

## 🚀 Instalasi

### Prasyarat
- PHP >= 7.4
- MySQL >= 5.7
- Web Server (Apache/Nginx)
- Composer (opsional)

### Langkah Instalasi

1. **Clone Repository**
   ```bash
   git clone https://github.com/BagusA23/KerebanAyam.git
   cd KerebanAyam
   ```

2. **Setup Database**
   ```bash
   # Buat database baru
   mysql -u root -p
   CREATE DATABASE kereban_ayam;
   
   # Import database
   mysql -u root -p kereban_ayam < database/kereban_ayam.sql
   ```

3. **Konfigurasi Database**
   ```php
   // config/database.php
   <?php
   $host = 'localhost';
   $username = 'root';
   $password = 'your_password';
   $database = 'kereban_ayam';
   ```

4. **Jalankan Aplikasi**
   ```bash
   # Untuk development
   php -S localhost:8000
   
   # Atau copy ke folder web server
   cp -r . /var/www/html/kereban-ayam
   ```

5. **Akses Aplikasi**
   - Buka browser dan akses: `http://localhost:8000`
   - Login default: `admin` / `admin123`

## 📖 Penggunaan

### Login & Dashboard
1. Login menggunakan akun admin default
2. Dashboard menampilkan ringkasan data peternakan
3. Navigasi menu untuk mengakses fitur-fitur

### Mengelola Kandang
```php
// Tambah kandang baru
$kandang = new Kandang();
$kandang->nama = "Kandang A1";
$kandang->kapasitas = 100;
$kandang->save();
```

### Pencatatan Produksi
```php
// Catat produksi telur harian
$produksi = new Produksi();
$produksi->kandang_id = 1;
$produksi->tanggal = date('Y-m-d');
$produksi->jumlah_telur = 85;
$produksi->save();
```

## 📸 Screenshot

<div align="center">
  
  ### Dashboard Utama
  ![Dashboard](https://via.placeholder.com/800x400/4CAF50/FFFFFF?text=Dashboard+KerebanAyam)
  
  ### Manajemen Kandang
  ![Kandang](https://via.placeholder.com/800x400/2196F3/FFFFFF?text=Manajemen+Kandang)
  
  ### Laporan Produksi
  ![Produksi](https://via.placeholder.com/800x400/FF9800/FFFFFF?text=Laporan+Produksi)
  
</div>

## 🤝 Kontribusi

Kontribusi sangat diapresiasi! Silakan ikuti langkah berikut:

1. **Fork** repository ini
2. **Buat branch** untuk fitur baru (`git checkout -b feature/AmazingFeature`)
3. **Commit** perubahan Anda (`git commit -m 'Add some AmazingFeature'`)
4. **Push** ke branch (`git push origin feature/AmazingFeature`)
5. **Buat Pull Request**

### 📝 Contribution Guidelines

- Pastikan code mengikuti PSR-4 standards
- Tambahkan tests untuk fitur baru
- Update dokumentasi jika diperlukan
- Gunakan commit message yang deskriptif

## 🐛 Bug Reports & Feature Requests

Jika Anda menemukan bug atau memiliki ide untuk fitur baru, silakan:

1. Cek [existing issues](https://github.com/BagusA23/KerebanAyam/issues)
2. Buat [new issue](https://github.com/BagusA23/KerebanAyam/issues/new) dengan template yang sesuai
3. Berikan detail yang lengkap dan langkah untuk reproduksi

## 📄 Lisensi

Project ini dilisensikan under [MIT License](LICENSE) - lihat file LICENSE untuk detail lengkap.

## 👥 Tim Pengembang

<table>
  <tr>
    <td align="center">
      <a href="https://github.com/BagusA23">
        <img src="https://github.com/BagusA23.png" width="100px;" alt="Bagus A23"/>
        <br />
        <sub><b>Bagus Ardiansyah</b></sub>
      </a>
      <br />
      <a href="https://github.com/BagusA23/KerebanAyam/commits?author=BagusA23" title="Code">💻</a>
    </td>
    <td align="center">
      <a href="https://github.com/Adttt-dev">
        <img src="https://github.com/Adttt-dev.png" width="100px;" alt="Bagus A23"/>
        <br />
        <sub><b>Aditya yudha</b></sub>
      </a>
      <br />
      <a href="https://github.com/BagusA23/KerebanAyam/commits?author=BagusA23" title="Code">💻</a>
    </td>
</table>

## 🙏 Acknowledgments

- Terima kasih kepada komunitas open source Indonesia
- Inspirasi dari para peternak ayam lokal
- Special thanks to contributors dan beta testers

---

<div align="center">
  
  **⭐ Jangan lupa untuk memberikan star jika project ini bermanfaat! ⭐**
  
  ![Made with Love](https://img.shields.io/badge/Made%20with-❤️-red?style=for-the-badge)
  ![Indonesia](https://img.shields.io/badge/Made%20in-🇮🇩%20Indonesia-red?style=for-the-badge)
  
</div>
