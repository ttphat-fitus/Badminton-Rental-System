#ifndef BOOKING_CONTROLLER_H
#define BOOKING_CONTROLLER_H

#include "<QObject>
#include "<QString>
#include "<QDateTime>
#include "<QList>
#include "<QMap>
#include <models/booking.h"
#include <models/court.h"
#include <models/user.h"
#include <utils/database_manager.h"
#include <utils/email_service.h"
#include <utils/date_utils.h"
#include <patterns/observer.h"
#include <patterns/singleton.h"

class BookingController : public QObject, public Subject, public Singleton<BookingController> {
    Q_OBJECT

private:
    DatabaseManager& dbManager;
    EmailService& emailService;
    QList<Booking> bookingCart;

public:
    explicit BookingController(QObject* parent = nullptr);
    ~BookingController();

    // Booking operations
    bool createBooking(int userId, int courtId, const QDateTime& startTime, 
                      const QDateTime& endTime, const QString& notes = QString());
    bool updateBooking(int bookingId, const QDateTime& startTime, 
                      const QDateTime& endTime, const QString& notes = QString());
    bool cancelBooking(int bookingId);
    bool confirmBooking(int bookingId);
    bool completeBooking(int bookingId);

    // Cart operations
    void addToCart(const Booking& booking);
    void removeFromCart(int index);
    void clearCart();
    bool checkoutCart();
    QList<Booking> getCart() const { return bookingCart; }
    double getCartTotal() const;

    // Query operations
    Booking getBookingById(int bookingId);
    QList<Booking> getBookingsByUserId(int userId);
    QList<Booking> getBookingsByCourtId(int courtId);
    QList<Booking> getBookingsByDate(const QDate& date);
    QList<Booking> getUpcomingBookings(int userId, int limit = 10);
    QList<Booking> getPastBookings(int userId, int limit = 10);

    // Availability checking
    bool isCourtAvailable(int courtId, const QDateTime& startTime, const QDateTime& endTime);
    QList<QTime> getAvailableTimeSlots(int courtId, const QDate& date);
    QList<Court> getAvailableCourts(const QDateTime& startTime, const QDateTime& endTime);

    // Price calculation
    double calculatePrice(int courtId, const QDateTime& startTime, const QDateTime& endTime);
    double calculatePrice(const Court& court, int durationHours);

    // Statistics
    QMap<QString, double> getRevenueByDateRange(const QDate& startDate, const QDate& endDate);
    QMap<QString, int> getBookingCountByDateRange(const QDate& startDate, const QDate& endDate);
    QMap<QString, double> getCourtUtilizationByDateRange(const QDate& startDate, const QDate& endDate);

    // Validation
    bool isValidBookingTime(const QDateTime& startTime, const QDateTime& endTime);
    bool isBookingInPast(const QDateTime& startTime);
    bool isBookingDurationValid(int durationHours);

signals:
    void bookingCreated(const Booking& booking);
    void bookingUpdated(const Booking& booking);
    void bookingCancelled(int bookingId);
    void bookingConfirmed(int bookingId);
    void bookingCompleted(int bookingId);
    void cartUpdated();
    void checkoutSuccess();
    void checkoutFailed(const QString& error);
    void availabilityChanged(int courtId, const QDate& date);

private:
    void sendBookingNotification(const Booking& booking, const QString& type);
    void updateCourtAvailability(int courtId);
    void notifyObservers(const QString& message);
};

#endif // BOOKING_CONTROLLER_H 