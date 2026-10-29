#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
using namespace std;

struct Ngay {
    int ngay, thang, nam;
};

struct HangHoa {
    string maHH;
    string tenHH;
    Ngay   ngayXuat;
    double giaXuat;
};

bool laNamNhuan(int nam) {
    return (nam % 400 == 0) || (nam % 4 == 0 && nam % 100 != 0);
}

bool ngayHopLe(Ngay d) {
    if (d.nam < 1 || d.thang < 1 || d.thang > 12 || d.ngay < 1) return false;
    int soNgay[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (laNamNhuan(d.nam)) soNgay[1] = 29;
    return d.ngay <= soNgay[d.thang - 1];
}

void nhapHangHoa(HangHoa &h) {
    cout << "  Ma hang hoa  : ";
    getline(cin, h.maHH);
    cout << "  Ten hang hoa : ";
    getline(cin, h.tenHH);

    char c1, c2;
    do {
        cout << "  Ngay xuat (dd/mm/yyyy): ";
        cin >> h.ngayXuat.ngay >> c1 >> h.ngayXuat.thang >> c2 >> h.ngayXuat.nam;
        if (cin.fail() || c1 != '/' || c2 != '/' || !ngayHopLe(h.ngayXuat)) {
            cout << "  -> Ngay khong hop le, vui long nhap lai!\n";
            cin.clear();
            cin.ignore(1000, '\n');
            h.ngayXuat.ngay = 0;
            h.ngayXuat.thang = 0;
            h.ngayXuat.nam = 0;
        }
    } while (!ngayHopLe(h.ngayXuat));

    cout << "  Gia xuat (trieu dong): ";
    cin >> h.giaXuat;
    cin.ignore(1000, '\n');
}

void nhapMang(HangHoa a[], int n) {
    for (int i = 0; i < n; i++) {
        cout << "Nhap hang hoa thu " << i + 1 << ":\n";
        nhapHangHoa(a[i]);
    }
}

void xuatTieuDe() {
    cout << left << setw(5)  << "STT"
         << setw(12) << "Ma HH"
         << setw(25) << "Ten HH"
         << setw(14) << "Ngay xuat"
         << setw(12) << "Gia (trieu)" << "\n";
    cout << string(68, '-') << "\n";
}

void xuatHangHoa(const HangHoa &h, int stt) {
    cout << left << setw(5)  << stt
         << setw(12) << h.maHH
         << setw(25) << h.tenHH;

    ostringstream oss;
    oss << setfill('0') << setw(2) << h.ngayXuat.ngay << "/"
        << setw(2) << h.ngayXuat.thang << "/"
        << setw(4) << h.ngayXuat.nam;
    string ngayStr = oss.str();
    cout << setw(14) << ngayStr
         << setw(12) << h.giaXuat << "\n";
}

void xuatMang(const HangHoa a[], int n) {
    xuatTieuDe();
    for (int i = 0; i < n; i++)
        xuatHangHoa(a[i], i + 1);
}

void quickSort(HangHoa a[], int left, int right) {
    if (left >= right) return;

    double pivot = a[(left + right) / 2].giaXuat;
    int i = left, j = right;

    while (i <= j) {
        while (a[i].giaXuat < pivot) i++;
        while (a[j].giaXuat > pivot) j--;
        if (i <= j) {
            swap(a[i], a[j]);
            i++;
            j--;
        }
    }

    quickSort(a, left, j);
    quickSort(a, i, right);
}

void sapXepTheoGia(HangHoa a[], int n) {
    quickSort(a, 0, n - 1);
}

int timViTriDau(const HangHoa a[], int left, int right, double x) {
    if (left > right) return -1;

    int mid = (left + right) / 2;
    if (a[mid].giaXuat == x) {

        int r = timViTriDau(a, left, mid - 1, x);
        return (r != -1) ? r : mid;
    }
    if (a[mid].giaXuat > x)
        return timViTriDau(a, left, mid - 1, x);
    return timViTriDau(a, mid + 1, right, x);
}

void timKiemTheoGia(const HangHoa a[], int n, double x) {
    int vt = timViTriDau(a, 0, n - 1, x);
    if (vt == -1) {
        cout << "Khong tim thay hang hoa nao co gia xuat = " << x << " trieu dong.\n";
        return;
    }
    cout << "Cac hang hoa co gia xuat = " << x << " trieu dong:\n";
    xuatTieuDe();
    int stt = 1;

    for (int i = vt; i < n && a[i].giaXuat == x; i++)
        xuatHangHoa(a[i], stt++);
}

int main() {
    int n;
    do {
        cout << "Nhap so luong hang hoa n: ";
        cin >> n;
        if (cin.fail() || n <= 0) {
            cout << "n phai la so nguyen duong!\n";
            cin.clear();
            cin.ignore(1000, '\n');
            n = 0;
        }
    } while (n <= 0);
    cin.ignore(1000, '\n');

    HangHoa *ds = new HangHoa[n];

    cout << "\n===== NHAP DANH SACH HANG HOA =====\n";
    nhapMang(ds, n);
    cout << "\n===== DANH SACH HANG HOA VUA NHAP =====\n";
    xuatMang(ds, n);

    sapXepTheoGia(ds, n);
    cout << "\n===== DANH SACH SAU KHI SAP XEP TANG DAN THEO GIA =====\n";
    xuatMang(ds, n);

    double X;
    cout << "\nNhap gia xuat X can tim (trieu dong): ";
    cin >> X;
    cout << "\n===== KET QUA TIM KIEM =====\n";
    timKiemTheoGia(ds, n, X);

    delete[] ds;
    return 0;
}
