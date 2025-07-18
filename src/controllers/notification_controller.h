#ifndef NOTIFICATION_CONTROLLER_H
#define NOTIFICATION_CONTROLLER_H

#include "<QObject>
#include "<QString>
#include "<QList>
#include "<QTimer>
#include <models/notification.h"
#include <models/booking.h"
#include <utils/database_manager.h"
#include <utils/email_service.h"
#include <patterns/observer.h"
#include <patterns/singleton.h"

class NotificationController : public QObject, public Subject, public Singleton<NotificationController> {
    Q_OBJECT

private:
    DatabaseManager& dbManager;
    EmailService& emailService;
    QTimer* reminderTimer;
    QTimer* cleanupTimer;

public:
    explicit NotificationController(QObject* parent = nullptr);
    ~NotificationController();

    // Notification creation
    bool createBookingConfirmation(int userId, int bookingId);
    bool createBookingReminder(int userId, int bookingId, const QDateTime& scheduledTime);
    bool createBookingCancellation(int userId, int bookingId);
    bool createSystemAlert(int userId, const QString& title, const QString& message);

    // Notification management
    bool sendNotification(int notificationId);
    bool markAsSent(int notificationId);
    bool markAsFailed(int notificationId);
    bool deleteNotification(int notificationId);

    // Query operations
    Notification getNotificationById(int notificationId);
    QList<Notification> getNotificationsByUserId(int userId);
    QList<Notification> getPendingNotifications();
    QList<Notification> getOverdueNotifications();

    // Automated operations
    void startAutomatedServices();
    void stopAutomatedServices();
    void processPendingNotifications();
    void sendBookingReminders();
    void cleanupOldNotifications();

    // Statistics
    int getTotalNotifications() const;
    int getPendingNotificationsCount() const;
    int getSentNotificationsCount() const;
    int getFailedNotificationsCount() const;

signals:
    void notificationCreated(const Notification& notification);
    void notificationSent(const Notification& notification);
    void notificationFailed(const Notification& notification);
    void reminderSent(const Notification& notification);
    void automatedServicesStarted();
    void automatedServicesStopped();

private slots:
    void onReminderTimerTimeout();
    void onCleanupTimerTimeout();
    void onEmailSent(const QString& toEmail, const QString& subject);
    void onEmailFailed(const QString& toEmail, const QString& error);

private:
    void setupTimers();
    void sendEmailNotification(const Notification& notification);
    void scheduleReminder(const Booking& booking);
    void notifyObservers(const QString& message);
};

#endif // NOTIFICATION_CONTROLLER_H 