#ifndef COURT_CONTROLLER_H
#define COURT_CONTROLLER_H

#include "<QObject>
#include "<QString>
#include "<QList>
#include <models/court.h"
#include <utils/database_manager.h"
#include <patterns/observer.h"

class CourtController : public QObject, public Subject {
    Q_OBJECT

private:
    DatabaseManager& dbManager;

public:
    explicit CourtController(QObject* parent = nullptr);
    ~CourtController();

    // Court management operations
    bool addCourt(const QString& name, const QString& description, 
                  double pricePerHour, CourtStatus status = CourtStatus::AVAILABLE);
    bool updateCourt(int courtId, const QString& name, const QString& description, 
                     double pricePerHour, CourtStatus status);
    bool deleteCourt(int courtId);
    bool setCourtStatus(int courtId, CourtStatus status);

    // Query operations
    Court getCourtById(int courtId);
    QList<Court> getAllCourts();
    QList<Court> getAvailableCourts();
    QList<Court> getCourtsByStatus(CourtStatus status);

    // Validation
    bool isValidCourtName(const QString& name) const;
    bool isValidPrice(double price) const;
    bool isCourtNameUnique(const QString& name, int excludeId = 0);

    // Statistics
    int getTotalCourts() const;
    int getAvailableCourtsCount() const;
    int getMaintenanceCourtsCount() const;
    double getAveragePrice() const;

signals:
    void courtAdded(const Court& court);
    void courtUpdated(const Court& court);
    void courtDeleted(int courtId);
    void courtStatusChanged(int courtId, CourtStatus status);
    void courtListUpdated();

private:
    void notifyObservers(const QString& message);
};

#endif // COURT_CONTROLLER_H 