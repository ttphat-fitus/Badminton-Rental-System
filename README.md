# Badminton Rental System

Hệ thống quản lý thuê sân cầu lông với giao diện đồ họa và các tính năng quản lý đầy đủ.

## Tính năng chính

### Quản lý người dùng
- Đăng ký và đăng nhập cho admin và khách hàng
- Phân quyền dựa trên vai trò

### Quản lý sân (Chỉ Admin)
- Thêm, sửa, xóa thông tin sân
- Hiển thị danh sách sân

### Đặt sân (Khách hàng)
- Chọn sân, ngày và khung giờ
- Kiểm tra tính khả dụng theo thời gian thực
- Giỏ hàng đặt sân

### Chỉnh sửa đặt sân
- Hủy hoặc cập nhật đặt sân hiện có

### Thông báo
- Email nhắc nhở cho các đặt sân sắp tới

### Thống kê & Báo cáo
- Theo dõi đặt sân, lịch sử và doanh thu theo ngày, tuần, tháng

## Design Patterns được sử dụng

1. **Singleton Pattern**: Kiểm soát tập trung cho các thao tác đặt sân
2. **Observer Pattern**: Tự động thông báo khi trạng thái đặt sân thay đổi
3. **MVC Pattern**: Tách biệt Model, View và Controller

## Cấu trúc dự án

```
Badminton-Rental-System/
├── src/                    # Mã nguồn chính
│   ├── main.cpp           # Entry point
│   ├── models/            # Các model dữ liệu
│   ├── views/             # Giao diện người dùng
│   ├── controllers/       # Logic điều khiển
│   ├── utils/             # Tiện ích
│   └── patterns/          # Design patterns
├── data/                  # Dữ liệu
├── docs/                  # Tài liệu
├── test/                  # Unit tests
└── build/                 # Build files
```

## Yêu cầu hệ thống

- Qt60trở lên
- C++17 trở lên
- CMake 3.16lên

## Cách build và chạy

```bash
mkdir build
cd build
cmake ..
make
./badminton_rental_system
```

## Tác giả

Phát - 2025
## Giấy phép

MIT License
