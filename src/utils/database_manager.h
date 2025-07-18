#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include "<QObject>
#include "<QSqlDatabase>
#include "<QSqlQuery>
#include "<QSqlError>
#include "<QString>
#include "<QVariant>
#include "<QList>
#include "<QMap>
#include <patterns/singleton.h"
#include <models/user.h"
#include <models/court.h"
#include <models/booking.h"
#include <models/notification.h"

class DatabaseManager : public QObject, public Singleton<DatabaseManager> {
    Q_OBJECT

private:
    QSqlDatabase db;
    bool isInitialized;

protected:
    bool createTables();
    bool insertInitialData();

public:
    DatabaseManager();
    ~DatabaseManager();
    // User operations
    bool addUser(const User& user);
    bool updateUser(const User& user);
    bool deleteUser(int userId);
    User getUserById(int userId);
    User getUserByEmail(const QString& email);
    QList<User> getAllUsers();
    bool authenticateUser(const QString& email, const QString& password);

    // Court operations
    bool addCourt(const Court& court);
    bool updateCourt(const Court& court);
    bool deleteCourt(int courtId);
    Court getCourtById(int courtId);
    QList<Court> getAllCourts();
    QList<Court> getAvailableCourts();

    // Booking operations
    bool addBooking(const Booking& booking);
    bool updateBooking(const Booking& booking);
    bool deleteBooking(int bookingId);
    Booking getBookingById(int bookingId);
    QList<Booking> getBookingsByUserId(int userId);
    QList<Booking> getBookingsByCourtId(int courtId);
    QList<Booking> getBookingsByDate(const QDate& date);
    QList<Booking> getOverlappingBookings(int courtId, const QDateTime& start, const QDateTime& end);
    bool isCourtAvailable(int courtId, const QDateTime& start, const QDateTime& end);

    // Notification operations
    bool addNotification(const Notification& notification);
    bool updateNotification(const Notification& notification);
    bool deleteNotification(int notificationId);
    Notification getNotificationById(int notificationId);
    QList<Notification> getNotificationsByUserId(int userId);
    QList<Notification> getPendingNotifications();

    // Statistics operations
    QMap<QString, double> getRevenueByDateRange(const QDate& startDate, const QDate& endDate);
    QMap<QString, int> getBookingCountByDateRange(const QDate& startDate, const QDate& endDate);
    QMap<QString, double> getCourtUtilizationByDateRange(const QDate& startDate, const QDate& endDate);

    // Database management
    bool initialize();
    bool isConnected() const;
    void close();
    QString getLastError() const;

signals:
    void databaseError(const QString& error);
    void dataChanged();
};

#endif // DATABASE_MANAGER_H 