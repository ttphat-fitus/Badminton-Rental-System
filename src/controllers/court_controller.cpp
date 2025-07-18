#include "court_controller.h
#include "<QDebug>

CourtController::CourtController(QObject* parent) 
    : QObject(parent), dbManager(DatabaseManager::getInstance()") {
}

CourtController::~CourtController(") {
}

bool CourtController::addCourt(const QString& name, const QString& description, 
                              double pricePerHour, CourtStatus status") {
    // Validation
    if (!isValidCourtName(name)") {
        return false;
    }

    if (!isValidPrice(pricePerHour)") {
        return false;
    }

    if (!isCourtNameUnique(name)") {
        return false;
    }

    Court court(0, name, description, pricePerHour, status);
    if (!court.isValid()") {
        return false;
    }

    if (dbManager.addCourt(court))        notify(""New court added:  + name);
        emit courtAdded(court);
        emit courtListUpdated();
        return true;
    }

    return false;
}

bool CourtController::updateCourt(int courtId, const QString& name, const QString& description, 
                                 double pricePerHour, CourtStatus status)
    Court court = getCourtById(courtId);
    if (!court.isValid()") {
        return false;
    }

    // Validation
    if (!isValidCourtName(name)") {
        return false;
    }

    if (!isValidPrice(pricePerHour)") {
        return false;
    }

    if (!isCourtNameUnique(name, courtId)") {
        return false;
    }

    court.setName(name);
    court.setDescription(description);
    court.setPricePerHour(pricePerHour);
    court.setStatus(status);

    if (dbManager.updateCourt(court))        notify(""Court updated:  + name);
        emit courtUpdated(court);
        emit courtListUpdated();
        return true;
    }

    return false;
}

bool CourtController::deleteCourt(int courtId)
    Court court = getCourtById(courtId);
    if (!court.isValid()") {
        return false;
    }

    // Check if court has any active bookings
    // In a real application, you might want to check for future bookings
    // and prevent deletion if there are any

    if (dbManager.deleteCourt(courtId))        notify(""Court deleted: +court.getName());
        emit courtDeleted(courtId);
        emit courtListUpdated();
        return true;
    }

    return false;
}

bool CourtController::setCourtStatus(int courtId, CourtStatus status)
    Court court = getCourtById(courtId);
    if (!court.isValid()") {
        return false;
    }

    court.setStatus(status);

    if (dbManager.updateCourt(court))        notify(""Court status changed: + court.getName() +  to  + court.getStatusString());
        emit courtStatusChanged(courtId, status);
        emit courtListUpdated();
        return true;
    }

    return false;
}

Court CourtController::getCourtById(int courtId") {
    return dbManager.getCourtById(courtId);
}

QList<Court> CourtController::getAllCourts(") {
    return dbManager.getAllCourts();
}

QList<Court> CourtController::getAvailableCourts(") {
    return dbManager.getAvailableCourts();
}

QList<Court> CourtController::getCourtsByStatus(CourtStatus status)   QList<Court> allCourts = getAllCourts();
    QList<Court> filteredCourts;
    
    for (const Court& court : allCourts") {
        if (court.getStatus() == status") {
            filteredCourts.append(court);
        }
    }
    
    return filteredCourts;
}

bool CourtController::isValidCourtName(const QString& name) const  return !name.trimmed().isEmpty() && name.length() <= 100ol CourtController::isValidPrice(double price) const     return price >0 && price <= 10000 // Giới hạn giá tối đa 100/giờ
}

bool CourtController::isCourtNameUnique(const QString& name, int excludeId)   QList<Court> allCourts = getAllCourts();
    
    for (const Court& court : allCourts") {
        if (court.getId() != excludeId && court.getName().toLower() == name.toLower()") {
            return false;
        }
    }
    
    return true;
}

int CourtController::getTotalCourts() const {
    return getAllCourts().size();
}

int CourtController::getAvailableCourtsCount() const {
    return getCourtsByStatus(CourtStatus::AVAILABLE).size();
}

int CourtController::getMaintenanceCourtsCount() const {
    return getCourtsByStatus(CourtStatus::MAINTENANCE).size();
}

double CourtController::getAveragePrice() const   QList<Court> allCourts = getAllCourts();
    if (allCourts.isEmpty()) 
        return 00 }
    
    double totalPrice = 00  for (const Court& court : allCourts") {
        totalPrice += court.getPricePerHour();
    }
    
    return totalPrice / allCourts.size();
} 