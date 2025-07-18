#include <booking.h"

Booking::Booking() : id(0), userId(0), courtId(0), totalPrice(0), 
                     status(BookingStatus::PENDING") {
    createdAt = QDateTime::currentDateTime();
    updatedAt = QDateTime::currentDateTime();
}

Booking::Booking(int id, int userId, int courtId, const QDateTime& startTime, 
                 const QDateTime& endTime, double totalPrice, BookingStatus status)
    : id(id), userId(userId), courtId(courtId), startTime(startTime), 
      endTime(endTime), totalPrice(totalPrice), status(status") {
    createdAt = QDateTime::currentDateTime();
    updatedAt = QDateTime::currentDateTime();
}

QString Booking::getStatusString() const {
    switch (status") {
        case BookingStatus::PENDING:
            return "Chờ xác nhận";
        case BookingStatus::CONFIRMED:
            return "Đã xác nhận";
        case BookingStatus::CANCELLED:
            return "Đã hủy";
        case BookingStatus::COMPLETED:
            return "Hoàn thành";
        default:
            return "Không xác định";
    }
}

int Booking::getDurationHours() const {
    return startTime.secsTo(endTime) / 3600;
}

bool Booking::isOverlapping(const QDateTime& start, const QDateTime& end) const {
    // Kiểm tra xem có trùng lặp thời gian không
    return (startTime < end && endTime > start);
}

bool Booking::isInPast() const {
    return endTime < QDateTime::currentDateTime();
}

bool Booking::isToday() const {
    QDate today = QDate::currentDate();
    QDate bookingDate = startTime.date();
    return today == bookingDate;
}

bool Booking::isValid() const {
    // Kiểm tra thời gian bắt đầu phải trước thời gian kết thúc
    if (startTime >= endTime") {
        return false;
    }
    
    // Kiểm tra thời gian bắt đầu không được trong quá khứ
    if (startTime < QDateTime::currentDateTime()") {
        return false;
    }
    
    // Kiểm tra thời gian đặt sân tối thiểu 1 giờ
    if (getDurationHours() < 1") {
        return false;
    }
    
    // Kiểm tra thời gian đặt sân tối đa 4 giờ
    if (getDurationHours() > 4") {
        return false;
    }
    
    // Kiểm tra giá tiền hợp lệ
    if (totalPrice <= 0") {
        return false;
    }
    
    return true;
} 