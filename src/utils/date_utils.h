#ifndef DATE_UTILS_H
#define DATE_UTILS_H

#include "<QString>
#include "<QDateTime>
#include "<QDate>
#include "<QTime>
#include "<QList>

class DateUtils {
public:
    // Date formatting
    static QString formatDate(const QDate& date, const QString& format = "dd/MM/yyyy");
    static QString formatDateTime(const QDateTime& dateTime, const QString& format = "dd/MM/yyyy HH:mm");
    static QString formatTime(const QTime& time, const QString& format = "HH:mm");
    
    // Date parsing
    static QDate parseDate(const QString& dateString, const QString& format = "dd/MM/yyyy");
    static QDateTime parseDateTime(const QString& dateTimeString, const QString& format = "dd/MM/yyyy HH:mm");
    static QTime parseTime(const QString& timeString, const QString& format = "HH:mm");
    
    // Date calculations
    static int daysBetween(const QDate& startDate, const QDate& endDate);
    static int hoursBetween(const QDateTime& startDateTime, const QDateTime& endDateTime);
    static QDate addDays(const QDate& date, int days);
    static QDateTime addHours(const QDateTime& dateTime, int hours);
    
    // Time slot utilities
    static QList<QTime> generateTimeSlots(const QTime& startTime = QTime(6, 0), 
                                         const QTime& endTime = QTime(22, 0), 
                                         int intervalMinutes = 60);
    static bool isTimeSlotAvailable(const QTime& time, const QList<QTime>& bookedSlots);
    static QString timeSlotToString(const QTime& time, int durationHours = 1);
    
    // Business logic
    static bool isBusinessDay(const QDate& date);
    static bool isWorkingHour(const QTime& time);
    static QDate getNextBusinessDay(const QDate& date);
    static QTime getNextAvailableTimeSlot(const QTime& currentTime);
    
    // Validation
    static bool isValidDate(const QString& dateString);
    static bool isValidTime(const QString& timeString);
    static bool isValidDateTime(const QString& dateTimeString);
    static bool isDateInFuture(const QDate& date);
    static bool isDateTimeInFuture(const QDateTime& dateTime);
    
    // Display helpers
    static QString getRelativeDateString(const QDate& date);
    static QString getRelativeDateTimeString(const QDateTime& dateTime);
    static QString getDayOfWeekString(const QDate& date);
    static QString getMonthString(const QDate& date);
    
    // Constants
    static const QTime BUSINESS_START_TIME;
    static const QTime BUSINESS_END_TIME;
    static const int DEFAULT_BOOKING_DURATION_HOURS;
    static const int MAX_BOOKING_DURATION_HOURS;
    static const int MIN_BOOKING_DURATION_HOURS;
};

#endif // DATE_UTILS_H 