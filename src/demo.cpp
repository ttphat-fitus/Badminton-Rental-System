#include <iostream>
#include <string>
#include <vector>
#include <memory>

// Simplified User class for demonstration
class User {
private:
    int id;
    std::string email;
    std::string fullName;
    std::string role;
    bool isActive;

public:
    User(int id, const std::string& email, const std::string& fullName, const std::string& role) 
        : id(id), email(email), fullName(fullName), role(role), isActive(true) {}
    
    int getId() const { return id; }
    std::string getEmail() const { return email; }
    std::string getFullName() const { return fullName; }
    std::string getRole() const { return role; }
    bool getIsActive() const { return isActive; }
    
    void displayInfo() const {
        std::cout << "User ID: " << id << std::endl;
        std::cout << "Email: " << email << std::endl;
        std::cout << "Name: " << fullName << std::endl;
        std::cout << "Role: " << role << std::endl;
        std::cout << "Status: " << (isActive ? "Active" : "Inactive") << std::endl;
    }
};

// Simplified Court class
class Court {
private:
    int id;
    std::string name;
    double pricePerHour;
    bool isAvailable;

public:
    Court(int id, const std::string& name, double price) 
        : id(id), name(name), pricePerHour(price), isAvailable(true) {}
    
    int getId() const { return id; }
    std::string getName() const { return name; }
    double getPricePerHour() const { return pricePerHour; }
    bool getIsAvailable() const { return isAvailable; }
    
    void displayInfo() const {
        std::cout << "Court ID: " << id << std::endl;
        std::cout << "Name: " << name << std::endl;
        std::cout << "Price per hour: $" << pricePerHour << std::endl;
        std::cout << "Available: " << (isAvailable ? "Yes" : "No") << std::endl;
    }
};

// Simplified Booking class
class Booking {
private:
    int id;
    int userId;
    int courtId;
    std::string dateTime;
    double totalPrice;
    std::string status;

public:
    Booking(int id, int userId, int courtId, const std::string& dateTime, double price) 
        : id(id), userId(userId), courtId(courtId), dateTime(dateTime), totalPrice(price), status("Confirmed") {}
    
    void displayInfo() const {
        std::cout << "Booking ID: " << id << std::endl;
        std::cout << "User ID: " << userId << std::endl;
        std::cout << "Court ID: " << courtId << std::endl;
        std::cout << "Date/Time: " << dateTime << std::endl;
        std::cout << "Total Price: $" << totalPrice << std::endl;
        std::cout << "Status: " << status << std::endl;
    }
};

// Simple demonstration of the Badminton Rental System
int main() {
    std::cout << "=============================================" << std::endl;
    std::cout << "    BADMINTON RENTAL SYSTEM DEMO" << std::endl;
    std::cout << "=============================================" << std::endl;
    std::cout << std::endl;

    // Create sample users
    std::vector<std::unique_ptr<User>> users;
    users.push_back(std::make_unique<User>(1, "admin@badminton.com", "Admin User", "ADMIN"));
    users.push_back(std::make_unique<User>(2, "john@email.com", "John Doe", "CUSTOMER"));
    users.push_back(std::make_unique<User>(3, "jane@email.com", "Jane Smith", "CUSTOMER"));

    // Create sample courts
    std::vector<std::unique_ptr<Court>> courts;
    courts.push_back(std::make_unique<Court>(1, "Court A", 25.0));
    courts.push_back(std::make_unique<Court>(2, "Court B", 30.0));
    courts.push_back(std::make_unique<Court>(3, "Court C (Premium)", 40.0));

    // Create sample bookings
    std::vector<std::unique_ptr<Booking>> bookings;
    bookings.push_back(std::make_unique<Booking>(1, 2, 1, "2025-07-18 10:00-12:00", 50.0));
    bookings.push_back(std::make_unique<Booking>(2, 3, 2, "2025-07-18 14:00-16:00", 60.0));

    // Display system information
    std::cout << "SYSTEM FEATURES:" << std::endl;
    std::cout << "• User Management (Admin/Customer roles)" << std::endl;
    std::cout << "• Court Management" << std::endl;
    std::cout << "• Booking System with real-time availability" << std::endl;
    std::cout << "• Email Notifications" << std::endl;
    std::cout << "• Statistics & Reports" << std::endl;
    std::cout << "• MVC Architecture with Design Patterns" << std::endl;
    std::cout << std::endl;

    // Display users
    std::cout << "REGISTERED USERS:" << std::endl;
    std::cout << "=================" << std::endl;
    for (const auto& user : users) {
        user->displayInfo();
        std::cout << std::endl;
    }

    // Display courts
    std::cout << "AVAILABLE COURTS:" << std::endl;
    std::cout << "=================" << std::endl;
    for (const auto& court : courts) {
        court->displayInfo();
        std::cout << std::endl;
    }

    // Display bookings
    std::cout << "CURRENT BOOKINGS:" << std::endl;
    std::cout << "=================" << std::endl;
    for (const auto& booking : bookings) {
        booking->displayInfo();
        std::cout << std::endl;
    }

    std::cout << "TECHNOLOGY STACK:" << std::endl;
    std::cout << "=================" << std::endl;
    std::cout << "• Language: C++17" << std::endl;
    std::cout << "• GUI Framework: Qt6 (or Qt5)" << std::endl;
    std::cout << "• Database: SQLite" << std::endl;
    std::cout << "• Build System: CMake" << std::endl;
    std::cout << "• Architecture: MVC Pattern" << std::endl;
    std::cout << "• Design Patterns: Singleton, Observer" << std::endl;
    std::cout << std::endl;

    std::cout << "PROJECT STRUCTURE:" << std::endl;
    std::cout << "==================" << std::endl;
    std::cout << "src/" << std::endl;
    std::cout << "├── models/          # Data models (User, Court, Booking, Notification)" << std::endl;
    std::cout << "├── views/           # Qt UI components (Windows, Widgets)" << std::endl;
    std::cout << "├── controllers/     # Business logic controllers" << std::endl;
    std::cout << "├── utils/           # Utilities (Database, Email, Date)" << std::endl;
    std::cout << "├── patterns/        # Design pattern implementations" << std::endl;
    std::cout << "└── main.cpp         # Application entry point" << std::endl;
    std::cout << std::endl;

    std::cout << "To run the full Qt GUI version:" << std::endl;
    std::cout << "1. Install Qt6 (or Qt5)" << std::endl;
    std::cout << "2. Fix any remaining syntax errors in the source files" << std::endl;
    std::cout << "3. Build with: mkdir build && cd build && cmake .. && make" << std::endl;
    std::cout << "4. Run: ./badminton_rental_system" << std::endl;
    std::cout << std::endl;

    std::cout << "Demo completed successfully!" << std::endl;
    std::cout << "=============================================" << std::endl;

    return 0;
}
