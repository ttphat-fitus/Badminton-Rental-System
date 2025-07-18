#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include "<QString>
#include "<QDateTime>

enum class NotificationType {
    BOOKING_CONFIRMATION,
    BOOKING_REMINDER,
    BOOKING_CANCELLATION,
    SYSTEM_ALERT
};

enum class NotificationStatus {
    PENDING,
    SENT,
    FAILED
};

class Notification {
private:
    int id;
    int userId;
    int bookingId;
    NotificationType type;
    QString title;
    QString message;
    QString email;
    NotificationStatus status;
    QDateTime scheduledTime;
    QDateTime sentTime;
    QDateTime createdAt;

public:
    Notification();
    Notification(int id, int userId, int bookingId, NotificationType type,
                 const QString& title, const QString& message, const QString& email);
    
    // Getters
    int getId() const { return id; }
    int getUserId() const { return userId; }
    int getBookingId() const { return bookingId; }
    NotificationType getType() const { return type; }
    QString getTitle() const { return title; }
    QString getMessage() const { return message; }
    QString getEmail() const { return email; }
    NotificationStatus getStatus() const { return status; }
    QDateTime getScheduledTime() const { return scheduledTime; }
    QDateTime getSentTime() const { return sentTime; }
    QDateTime getCreatedAt() const { return createdAt; }
    
    // Setters
    void setId(int id) { this->id = id; }
    void setUserId(int userId) { this->userId = userId; }
    void setBookingId(int bookingId) { this->bookingId = bookingId; }
    void setType(NotificationType type) { this->type = type; }
    void setTitle(const QString& title) { this->title = title; }
    void setMessage(const QString& message) { this->message = message; }
    void setEmail(const QString& email) { this->email = email; }
    void setStatus(NotificationStatus status) { this->status = status; }
    void setScheduledTime(const QDateTime& scheduledTime) { this->scheduledTime = scheduledTime; }
    void setSentTime(const QDateTime& sentTime) { this->sentTime = sentTime; }
    
    // Utility methods
    bool isPending() const { return status == NotificationStatus::PENDING; }
    bool isSent() const { return status == NotificationStatus::SENT; }
    bool isFailed() const { return status == NotificationStatus::FAILED; }
    QString getTypeString() const;
    QString getStatusString() const;
    
    // Time methods
    bool isDue() const;
    bool isOverdue() const;
    
    // Validation
    bool isValid() const;
};

#endif // NOTIFICATION_H 