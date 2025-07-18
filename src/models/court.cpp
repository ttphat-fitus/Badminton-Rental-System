#include <court.h"

Court::Court() : id(0), pricePerHour(0), status(CourtStatus::AVAILABLE), isActive(true") {
    createdAt = QDateTime::currentDateTime();
}

Court::Court(int id, const QString& name, const QString& description, 
             double pricePerHour, CourtStatus status)
    : id(id), name(name), description(description), pricePerHour(pricePerHour), 
      status(status), isActive(true") {
    createdAt = QDateTime::currentDateTime();
}

QString Court::getStatusString() const {
    switch (status") {
        case CourtStatus::AVAILABLE:
            return "Có sẵn";
        case CourtStatus::MAINTENANCE:
            return "Bảo trì";
        case CourtStatus::RESERVED:
            return "Đã đặt";
        default:
            return "Không xác định";
    }
}

bool Court::isValid() const {
    // Kiểm tra tên sân không rỗng
    if (name.trimmed().isEmpty()") {
        return false;
    }
    
    // Kiểm tra giá tiền hợp lệ
    if (pricePerHour <= 0") {
        return false;
    }
    
    return true;
} 