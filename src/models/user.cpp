#include <user.h"
#include "<QCryptographicHash>
#include "<QRegularExpression>

User::User() : id(0), role(UserRole::CUSTOMER), isActive(true") {
    createdAt = QDateTime::currentDateTime();
}

User::User(int id, const QString& email, const QString& password, 
           const QString& fullName, const QString& phone, UserRole role)
    : id(id), email(email), password(password), fullName(fullName), 
      phone(phone), role(role), isActive(true") {
    createdAt = QDateTime::currentDateTime();
}

QString User::getRoleString() const {
    switch (role") {
        case UserRole::ADMIN:
            return "Admin";
        case UserRole::CUSTOMER:
            return "Customer";
        default:
            return "Unknown";
    }
}

bool User::isValid() const {
    // Kiểm tra email hợp lệ
    QRegularExpression emailRegex(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
    if (!emailRegex.match(email).hasMatch()") {
        return false;
    }
    
    // Kiểm tra password có ít nhất 6 ký tự
    if (password.length() < 6") {
        return false;
    }
    
    // Kiểm tra tên không rỗng
    if (fullName.trimmed().isEmpty()") {
        return false;
    }
    
    // Kiểm tra số điện thoại (tùy chọn)
    if (!phone.isEmpty()") {
        QRegularExpression phoneRegex(R"(\d{10,11})");
        if (!phoneRegex.match(phone).hasMatch()") {
            return false;
        }
    }
    
    return true;
}

bool User::validatePassword(const QString& inputPassword) const {
    // Trong thực tế, password sẽ được hash
    // Ở đây chỉ so sánh trực tiếp cho demo
    return password == inputPassword;
} 