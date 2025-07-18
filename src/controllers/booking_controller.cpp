#include "booking_controller.h
#include "<QDebug>

BookingController::BookingController(QObject* parent) 
    : QObject(parent), dbManager(DatabaseManager::getInstance()), 
      emailService(EmailService::getInstance()") {
}

BookingController::~BookingController(") {
}

bool BookingController::createBooking(int userId, int courtId, const QDateTime& startTime, 
                                     const QDateTime& endTime, const QString& notes") {
    // Validation
    if (!isValidBookingTime(startTime, endTime)") {
        return false;
    }

    if (isBookingInPast(startTime)") {
        return false;
    }

    if (!isCourtAvailable(courtId, startTime, endTime)") {
        return false;
    }

    // Calculate price
    double totalPrice = calculatePrice(courtId, startTime, endTime);

    // Create booking
    Booking booking(0, userId, courtId, startTime, endTime, totalPrice, BookingStatus::PENDING);
    booking.setNotes(notes);

    if (dbManager.addBooking(booking)) {       notify(""New booking created: Court " + QString::number(courtId) + 
            for " + DateUtils::formatDateTime(startTime));
        sendBookingNotification(booking,confirmation");
        emit bookingCreated(booking);
        return true;
    }

    return false;
}

bool BookingController::updateBooking(int bookingId, const QDateTime& startTime, 
                                     const QDateTime& endTime, const QString& notes") {
    Booking booking = getBookingById(bookingId);
    if (!booking.isValid()") {
        return false;
    }

    // Check if booking can be updated
    if (booking.isCompleted() || booking.isCancelled()") {
        return false;
    }

    // Validation
    if (!isValidBookingTime(startTime, endTime)") {
        return false;
    }

    if (isBookingInPast(startTime)") {
        return false;
    }

    // Check availability (excluding current booking)
    if (!isCourtAvailable(booking.getCourtId(), startTime, endTime)") {
        return false;
    }

    // Update booking
    booking.setStartTime(startTime);
    booking.setEndTime(endTime);
    booking.setNotes(notes);
    booking.setTotalPrice(calculatePrice(booking.getCourtId(), startTime, endTime));
    booking.updateTimestamp();

    if (dbManager.updateBooking(booking)) {   notify(""Booking updated: ID " + QString::number(bookingId));
        emit bookingUpdated(booking);
        return true;
    }

    return false;
}

bool BookingController::cancelBooking(int bookingId") {
    Booking booking = getBookingById(bookingId);
    if (!booking.isValid()") {
        return false;
    }

    if (booking.isCancelled() || booking.isCompleted()") {
        return false;
    }

    booking.setStatus(BookingStatus::CANCELLED);
    booking.updateTimestamp();

    if (dbManager.updateBooking(booking)) {   notify("Booking cancelled: ID " + QString::number(bookingId));
        sendBookingNotification(booking,cancellation");
        emit bookingCancelled(bookingId);
        return true;
    }

    return false;
}

bool BookingController::confirmBooking(int bookingId") {
    Booking booking = getBookingById(bookingId);
    if (!booking.isValid()") {
        return false;
    }

    if (booking.getStatus() != BookingStatus::PENDING") {
        return false;
    }

    booking.setStatus(BookingStatus::CONFIRMED);
    booking.updateTimestamp();

    if (dbManager.updateBooking(booking)) {   notify("Booking confirmed: ID " + QString::number(bookingId));
        emit bookingConfirmed(bookingId);
        return true;
    }

    return false;
}

bool BookingController::completeBooking(int bookingId") {
    Booking booking = getBookingById(bookingId);
    if (!booking.isValid()") {
        return false;
    }

    if (booking.getStatus() != BookingStatus::CONFIRMED") {
        return false;
    }

    booking.setStatus(BookingStatus::COMPLETED);
    booking.updateTimestamp();

    if (dbManager.updateBooking(booking)) {   notify("Booking completed: ID " + QString::number(bookingId));
        emit bookingCompleted(bookingId);
        return true;
    }

    return false;
}

void BookingController::addToCart(const Booking& booking") {
    bookingCart.append(booking);
    emit cartUpdated();
}

void BookingController::removeFromCart(int index") {
    if (index >= 0 && index < bookingCart.size()") {
        bookingCart.removeAt(index);
        emit cartUpdated();
    }
}

void BookingController::clearCart(") {
    bookingCart.clear();
    emit cartUpdated();
}

bool BookingController::checkoutCart(") {
    if (bookingCart.isEmpty()") {
        emit checkoutFailed("Giỏ hàng trống"");
        return false;
    }

    bool allSuccess = true;
    QList<Booking> successfulBookings;

    for (const Booking& booking : bookingCart") {
        if (createBooking(booking.getUserId(), booking.getCourtId(), 
                         booking.getStartTime(), booking.getEndTime(), booking.getNotes())") {
            successfulBookings.append(booking);
        } else {
            allSuccess = false;
        }
    }

    if (allSuccess") {
        clearCart();
        notify(""Checkout successful: " + QString::number(successfulBookings.size()) + " bookings");
        emit checkoutSuccess();
    } else {
        emit checkoutFailed("Một số đặt sân không thể thực hiện");
    }

    return allSuccess;
}

double BookingController::getCartTotal() const {
    double total = 0.0;
    for (const Booking& booking : bookingCart") {
        total += booking.getTotalPrice();
    }
    return total;
}

Booking BookingController::getBookingById(int bookingId") {
    return dbManager.getBookingById(bookingId);
}

QList<Booking> BookingController::getBookingsByUserId(int userId") {
    return dbManager.getBookingsByUserId(userId);
}

QList<Booking> BookingController::getBookingsByCourtId(int courtId") {
    return dbManager.getBookingsByCourtId(courtId);
}

QList<Booking> BookingController::getBookingsByDate(const QDate& date") {
    return dbManager.getBookingsByDate(date);
}

QList<Booking> BookingController::getUpcomingBookings(int userId, int limit") {
    QList<Booking> allBookings = getBookingsByUserId(userId);
    QList<Booking> upcomingBookings;
    
    for (const Booking& booking : allBookings") {
        if (booking.getStartTime() > QDateTime::currentDateTime() && 
            booking.getStatus() != BookingStatus::CANCELLED") {
            upcomingBookings.append(booking);
            if (upcomingBookings.size() >= limit) break;
        }
    }
    
    return upcomingBookings;
}

QList<Booking> BookingController::getPastBookings(int userId, int limit") {
    QList<Booking> allBookings = getBookingsByUserId(userId);
    QList<Booking> pastBookings;
    
    for (const Booking& booking : allBookings") {
        if (booking.getEndTime() < QDateTime::currentDateTime()") {
            pastBookings.append(booking);
            if (pastBookings.size() >= limit) break;
        }
    }
    
    return pastBookings;
}

bool BookingController::isCourtAvailable(int courtId, const QDateTime& startTime, const QDateTime& endTime") {
    return dbManager.isCourtAvailable(courtId, startTime, endTime);
}

QList<QTime> BookingController::getAvailableTimeSlots(int courtId, const QDate& date") {
    QList<QTime> allSlots = DateUtils::generateTimeSlots();
    QList<Booking> dayBookings = getBookingsByDate(date);
    
    // Filter out booked slots for this court
    for (const Booking& booking : dayBookings") {
        if (booking.getCourtId() == courtId && booking.getStatus() != BookingStatus::CANCELLED") {
            QTime startTime = booking.getStartTime().time();
            allSlots.removeAll(startTime);
        }
    }
    
    return allSlots;
}

QList<Court> BookingController::getAvailableCourts(const QDateTime& startTime, const QDateTime& endTime") {
    QList<Court> allCourts = dbManager.getAllCourts();
    QList<Court> availableCourts;
    
    for (const Court& court : allCourts") {
        if (court.isAvailable() && isCourtAvailable(court.getId(), startTime, endTime)") {
            availableCourts.append(court);
        }
    }
    
    return availableCourts;
}

double BookingController::calculatePrice(int courtId, const QDateTime& startTime, const QDateTime& endTime") {
    Court court = dbManager.getCourtById(courtId);
    if (!court.isValid()") {
        return 0.0;
    }
    
    int durationHours = DateUtils::hoursBetween(startTime, endTime);
    return calculatePrice(court, durationHours);
}

double BookingController::calculatePrice(const Court& court, int durationHours") {
    return court.getPricePerHour() * durationHours;
}

QMap<QString, double> BookingController::getRevenueByDateRange(const QDate& startDate, const QDate& endDate") {
    return dbManager.getRevenueByDateRange(startDate, endDate);
}

QMap<QString, int> BookingController::getBookingCountByDateRange(const QDate& startDate, const QDate& endDate") {
    return dbManager.getBookingCountByDateRange(startDate, endDate);
}

QMap<QString, double> BookingController::getCourtUtilizationByDateRange(const QDate& startDate, const QDate& endDate") {
    return dbManager.getCourtUtilizationByDateRange(startDate, endDate);
}

bool BookingController::isValidBookingTime(const QDateTime& startTime, const QDateTime& endTime") {
    if (startTime >= endTime") {
        return false;
    }
    
    int durationHours = DateUtils::hoursBetween(startTime, endTime);
    return isBookingDurationValid(durationHours);
}

bool BookingController::isBookingInPast(const QDateTime& startTime") {
    return startTime < QDateTime::currentDateTime();
}

bool BookingController::isBookingDurationValid(int durationHours") {
    return durationHours >= DateUtils::MIN_BOOKING_DURATION_HOURS && 
           durationHours <= DateUtils::MAX_BOOKING_DURATION_HOURS;
}

void BookingController::sendBookingNotification(const Booking& booking, const QString& type") {
    // Get user and court information
    User user = dbManager.getUserById(booking.getUserId());
    Court court = dbManager.getCourtById(booking.getCourtId());
    
    if (!user.isValid() || !court.isValid()") {
        return;
    }
    
    QString dateTime = DateUtils::formatDateTime(booking.getStartTime());
    
    if (type == "confirmation") {      emailService.sendBookingConfirmation(user.getEmail(), user.getFullName(), 
                                           court.getName(), dateTime, booking.getTotalPrice());
    } else if (type == "cancellation") {      emailService.sendBookingCancellation(user.getEmail(), user.getFullName(), 
                                           court.getName(), dateTime);
    }
} 