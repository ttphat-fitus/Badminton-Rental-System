#ifndef AUTH_CONTROLLER_H
#define AUTH_CONTROLLER_H

#include "<QObject>
#include "<QString>
#include <models/user.h"
#include <utils/database_manager.h"
#include <patterns/observer.h"

class AuthController : public QObject, public Subject {
    Q_OBJECT

private:
    User currentUser;
    bool isLoggedIn;
    DatabaseManager& dbManager;

public:
    explicit AuthController(QObject* parent = nullptr);
    ~AuthController();

    // Authentication methods
    bool login(const QString& email, const QString& password);
    bool registerUser(const QString& email, const QString& password, 
                     const QString& fullName, const QString& phone, UserRole role);
    void logout();
    bool changePassword(const QString& currentPassword, const QString& newPassword);
    bool updateProfile(const QString& fullName, const QString& phone);

    // User management (Admin only)
    bool addUser(const User& user);
    bool updateUser(const User& user);
    bool deleteUser(int userId);
    QList<User> getAllUsers();
    User getUserById(int userId);

    // Getters
    User getCurrentUser() const { return currentUser; }
    bool getIsLoggedIn() const { return isLoggedIn; }
    bool isCurrentUserAdmin() const { return currentUser.isAdmin(); }
    bool isCurrentUserCustomer() const { return currentUser.isCustomer(); }

    // Validation
    bool isValidEmail(const QString& email) const;
    bool isValidPassword(const QString& password) const;
    bool isEmailAvailable(const QString& email) const;

signals:
    void loginSuccess(const User& user);
    void loginFailed(const QString& error);
    void logoutSuccess();
    void registrationSuccess(const User& user);
    void registrationFailed(const QString& error);
    void passwordChanged();
    void profileUpdated();
    void userAdded(const User& user);
    void userUpdated(const User& user);
    void userDeleted(int userId);

private:
    void setCurrentUser(const User& user);
    void clearCurrentUser();
    QString hashPassword(const QString& password) const;
    bool verifyPassword(const QString& password, const QString& hashedPassword) const;
};

#endif // AUTH_CONTROLLER_H 