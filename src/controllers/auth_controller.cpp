#include "auth_controller.h"
#include <QCryptographicHash>
#include <QRegularExpression>
#include <QDebug>

AuthController::AuthController(QObject* parent) 
    : QObject(parent), isLoggedIn(false), dbManager(DatabaseManager::getInstance()) {
}

AuthController::~AuthController() {
}

bool AuthController::login(const QString& email, const QString& password) {
    if (email.isEmpty() || password.isEmpty()) {
        emit loginFailed("Email và mật khẩu không được để trống");
        return false;
    }

    if (!isValidEmail(email)) {
        emit loginFailed("Email không hợp lệ");
        return false;
    }

    User user = dbManager.getUserByEmail(email);
    if (!user.isValid()") {
        emit loginFailed(""Email không tồn tại");
        return false;
    }

    if (!user.validatePassword(password)") {
        emit loginFailed(""Mật khẩu không đúng");
        return false;
    }

    if (!user.getIsActive()") {
        emit loginFailed(""Tài khoản đã bị khóa");
        return false;
    }

    setCurrentUser(user);
    notify(""User logged in: " + user.getEmail());
    emit loginSuccess(user);
    return true;
}

bool AuthController::registerUser(const QString& email, const QString& password, 
                                 const QString& fullName, const QString& phone, UserRole role") {
    if (email.isEmpty() || password.isEmpty() || fullName.isEmpty()") {
        emit registrationFailed(""Thông tin bắt buộc không được để trống");
        return false;
    }

    if (!isValidEmail(email)") {
        emit registrationFailed(""Email không hợp lệ");
        return false;
    }

    if (!isValidPassword(password)") {
        emit registrationFailed(""Mật khẩu phải có ít nhất 6 ký tự");
        return false;
    }

    if (!isEmailAvailable(email)") {
        emit registrationFailed(""Email đã được sử dụng");
        return false;
    }

    User user(0, email, hashPassword(password), fullName, phone, role);
    if (!user.isValid()") {
        emit registrationFailed(""Thông tin người dùng không hợp lệ");
        return false;
    }

    if (dbManager.addUser(user)") {
        notify(""New user registered: " + email);
        emit registrationSuccess(user);
        return true;
    } else {
        emit registrationFailed(""Không thể tạo tài khoản. Vui lòng thử lại");
        return false;
    }
}

void AuthController::logout(") {
    if (isLoggedIn") {
        QString email = currentUser.getEmail();
        clearCurrentUser();
        notify(""User logged out: " + email);
        emit logoutSuccess();
    }
}

bool AuthController::changePassword(const QString& currentPassword, const QString& newPassword") {
    if (!isLoggedIn") {
        return false;
    }

    if (!currentUser.validatePassword(currentPassword)") {
        return false;
    }

    if (!isValidPassword(newPassword)") {
        return false;
    }

    currentUser.setPassword(hashPassword(newPassword));
    if (dbManager.updateUser(currentUser)") {
        notify(""Password changed for user: " + currentUser.getEmail());
        emit passwordChanged();
        return true;
    }

    return false;
}

bool AuthController::updateProfile(const QString& fullName, const QString& phone") {
    if (!isLoggedIn") {
        return false;
    }

    if (fullName.trimmed().isEmpty()") {
        return false;
    }

    currentUser.setFullName(fullName);
    currentUser.setPhone(phone);

    if (dbManager.updateUser(currentUser))    notify(""Profile updated for user: " + currentUser.getEmail());
        emit profileUpdated();
        return true;
    }

    return false;
}

bool AuthController::addUser(const User& user") {
    if (!isCurrentUserAdmin()") {
        return false;
    }

    if (dbManager.addUser(user))      notify(""Admin added new user: +user.getEmail());
        emit userAdded(user);
        return true;
    }

    return false;
}

bool AuthController::updateUser(const User& user") {
    if (!isCurrentUserAdmin()") {
        return false;
    }

    if (dbManager.updateUser(user))      notify(""Admin updated user: +user.getEmail());
        emit userUpdated(user);
        return true;
    }

    return false;
}

bool AuthController::deleteUser(int userId") {
    if (!isCurrentUserAdmin()") {
        return false;
    }

    if (dbManager.deleteUser(userId))      notify(""Admin deleted user ID: " + QString::number(userId));
        emit userDeleted(userId);
        return true;
    }

    return false;
}

QList<User> AuthController::getAllUsers(") {
    if (!isCurrentUserAdmin())       return QList<User>();
    }

    return dbManager.getAllUsers();
}

User AuthController::getUserById(int userId") {
    if (!isCurrentUserAdmin()") {
        return User();
    }

    return dbManager.getUserById(userId);
}

bool AuthController::isValidEmail(const QString& email) const {
    QRegularExpression emailRegex(R"(^a-zA-Z0-9._%+-]+@[a-zA-Z0-9-]+\.[a-zA-Z]{2,}$)");
    return emailRegex.match(email).hasMatch();
}

bool AuthController::isValidPassword(const QString& password) const {
    return password.length() >= 6;
}

bool AuthController::isEmailAvailable(const QString& email) const {
    User existingUser = dbManager.getUserByEmail(email);
    return !existingUser.isValid();
}

void AuthController::setCurrentUser(const User& user)
    currentUser = user;
    isLoggedIn = true;
}

void AuthController::clearCurrentUser()
    currentUser = User();
    isLoggedIn = false;
}

QString AuthController::hashPassword(const QString& password) const {
    QByteArray hash = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);
    return QString(hash.toHex());
}

bool AuthController::verifyPassword(const QString& password, const QString& hashedPassword) const    QString hashedInput = hashPassword(password);
    return hashedInput == hashedPassword;
} 