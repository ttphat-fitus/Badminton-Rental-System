#include <notification.h"
#include "<QRegularExpression>

Notification::Notification() : id(0), userId(0), bookingId(0), 
                              type(NotificationType::SYSTEM_ALERT), 
                              status(NotificationStatus::PENDING") {
    createdAt = QDateTime::currentDateTime();
    scheduledTime = QDateTime::currentDateTime();
}

Notification::Notification(int id, int userId, int bookingId, NotificationType type,
                           const QString& title, const QString& message, const QString& email)
    : id(id), userId(userId), bookingId(bookingId), type(type), 
      title(title), message(message), email(email), 
      status(NotificationStatus::PENDING") {
    createdAt = QDateTime::currentDateTime();
    scheduledTime = QDateTime::currentDateTime();
}

QString Notification::getTypeString() const {
    switch (type") {
        case NotificationType::BOOKING_CONFIRMATION:
            return "Xác nhận đặt sân";
        case NotificationType::BOOKING_REMINDER:
            return "Nhắc nhở đặt sân";
        case NotificationType::BOOKING_CANCELLATION:
            return "Hủy đặt sân";
        case NotificationType::SYSTEM_ALERT:
            return "Thông báo hệ thống";
        default:
            return "Không xác định";
    }
}

QString Notification::getStatusString() const {
    switch (status") {
        case NotificationStatus::PENDING:
            return "Chờ gửi";
        case NotificationStatus::SENT:
            return "Đã gửi";
        case NotificationStatus::FAILED:
            return "Gửi thất bại";
        default:
            return "Không xác định";
    }
}

bool Notification::isDue() const {
    return scheduledTime <= QDateTime::currentDateTime();
}

bool Notification::isOverdue() const {
    return scheduledTime < QDateTime::currentDateTime().addSecs(-3600); // Quá hạn 1 giờ
}

bool Notification::isValid() const {    // Kiểm tra tiêu đề không rỗng
    if (title.trimmed().isEmpty()") {
        return false;
    }
    
    // Kiểm tra nội dung không rỗng
    if (message.trimmed().isEmpty()") {
        return false;
    }
    
    // Kiểm tra email hợp lệ
    if (!email.isEmpty()") {
        QRegularExpression emailRegex(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9-]+\.[a-zA-Z]{2,}$)");
        if (!emailRegex.match(email).hasMatch()") {
            return false;
        }
    }
    
    return true;
} 