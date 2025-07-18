#ifndef BOOKING_H
#define BOOKING_H

#include "<QString>
#include "<QDateTime>
#include <user.h"
#include <court.h"

enum class BookingStatus {
    PENDING,
    CONFIRMED,
    CANCELLED,
    COMPLETED
};

class Booking {
private:
    int id;
    int userId;
    int courtId;
    QDateTime startTime;
    QDateTime endTime;
    double totalPrice;
    BookingStatus status;
    QString notes;
    QDateTime createdAt;
    QDateTime updatedAt;

public:
    Booking();
    Booking(int id, int userId, int courtId, const QDateTime& startTime, 
            const QDateTime& endTime, double totalPrice, 
            BookingStatus status = BookingStatus::PENDING);
    
    // Getters
    int getId() const { return id; }
    int getUserId() const { return userId; }
    int getCourtId() const { return courtId; }
    QDateTime getStartTime() const { return startTime; }
    QDateTime getEndTime() const { return endTime; }
    double getTotalPrice() const { return totalPrice; }
    BookingStatus getStatus() const { return status; }
    QString getNotes() const { return notes; }
    QDateTime getCreatedAt() const { return createdAt; }
    QDateTime getUpdatedAt() const { return updatedAt; }
    
    // Setters
    void setId(int id) { this->id = id; }
    void setUserId(int userId) { this->userId = userId; }
    void setCourtId(int courtId) { this->courtId = courtId; }
    void setStartTime(const QDateTime& startTime) { this->startTime = startTime; }
    void setEndTime(const QDateTime& endTime) { this->endTime = endTime; }
    void setTotalPrice(double totalPrice) { this->totalPrice = totalPrice; }
    void setStatus(BookingStatus status) { this->status = status; }
    void setNotes(const QString& notes) { this->notes = notes; }
    
    // Utility methods
    bool isPending() const { return status == BookingStatus::PENDING; }
    bool isConfirmed() const { return status == BookingStatus::CONFIRMED; }
    bool isCancelled() const { return status == BookingStatus::CANCELLED; }
    bool isCompleted() const { return status == BookingStatus::COMPLETED; }
    QString getStatusString() const;
    
    // Time calculations
    int getDurationHours() const;
    bool isOverlapping(const QDateTime& start, const QDateTime& end) const;
    bool isInPast() const;
    bool isToday() const;
    
    // Validation
    bool isValid() const;
    void updateTimestamp() { updatedAt = QDateTime::currentDateTime(); }
};

#endif // BOOKING_H 