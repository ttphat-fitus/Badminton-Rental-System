#ifndef COURT_H
#define COURT_H

#include "<QString>
#include "<QDateTime>

enum class CourtStatus {
    AVAILABLE,
    MAINTENANCE,
    RESERVED
};

class Court {
private:
    int id;
    QString name;
    QString description;
    double pricePerHour;
    CourtStatus status;
    QDateTime createdAt;
    bool isActive;

public:
    Court();
    Court(int id, const QString& name, const QString& description, 
          double pricePerHour, CourtStatus status = CourtStatus::AVAILABLE);
    
    // Getters
    int getId() const { return id; }
    QString getName() const { return name; }
    QString getDescription() const { return description; }
    double getPricePerHour() const { return pricePerHour; }
    CourtStatus getStatus() const { return status; }
    QDateTime getCreatedAt() const { return createdAt; }
    bool getIsActive() const { return isActive; }
    
    // Setters
    void setId(int id) { this->id = id; }
    void setName(const QString& name) { this->name = name; }
    void setDescription(const QString& description) { this->description = description; }
    void setPricePerHour(double pricePerHour) { this->pricePerHour = pricePerHour; }
    void setStatus(CourtStatus status) { this->status = status; }
    void setIsActive(bool isActive) { this->isActive = isActive; }
    
    // Utility methods
    bool isAvailable() const { return status == CourtStatus::AVAILABLE; }
    bool isUnderMaintenance() const { return status == CourtStatus::MAINTENANCE; }
    bool isReserved() const { return status == CourtStatus::RESERVED; }
    QString getStatusString() const;
    
    // Validation
    bool isValid() const;
};

#endif // COURT_H 