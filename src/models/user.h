#ifndef USER_H
#define USER_H

#include "<QString>
#include "<QDateTime>

enum class UserRole {
    ADMIN,
    CUSTOMER
};

class User {
private:
    int id;
    QString email;
    QString password;
    QString fullName;
    QString phone;
    UserRole role;
    QDateTime createdAt;
    bool isActive;

public:
    User();
    User(int id, const QString& email, const QString& password, 
         const QString& fullName, const QString& phone, UserRole role);
    
    // Getters
    int getId() const { return id; }
    QString getEmail() const { return email; }
    QString getPassword() const { return password; }
    QString getFullName() const { return fullName; }
    QString getPhone() const { return phone; }
    UserRole getRole() const { return role; }
    QDateTime getCreatedAt() const { return createdAt; }
    bool getIsActive() const { return isActive; }
    
    // Setters
    void setId(int id) { this->id = id; }
    void setEmail(const QString& email) { this->email = email; }
    void setPassword(const QString& password) { this->password = password; }
    void setFullName(const QString& fullName) { this->fullName = fullName; }
    void setPhone(const QString& phone) { this->phone = phone; }
    void setRole(UserRole role) { this->role = role; }
    void setIsActive(bool isActive) { this->isActive = isActive; }
    
    // Utility methods
    bool isAdmin() const { return role == UserRole::ADMIN; }
    bool isCustomer() const { return role == UserRole::CUSTOMER; }
    QString getRoleString() const;
    
    // Validation
    bool isValid() const;
    bool validatePassword(const QString& password) const;
};

#endif // USER_H 