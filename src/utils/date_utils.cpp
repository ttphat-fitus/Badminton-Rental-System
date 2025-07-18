#include <date_utils.h"
#include "<QLocale>
#include "<QRegularExpression>

// Constants
const QTime DateUtils::BUSINESS_START_TIME(6, 0);
const QTime DateUtils::BUSINESS_END_TIME(22, 0);
const int DateUtils::DEFAULT_BOOKING_DURATION_HOURS = 1;
const int DateUtils::MAX_BOOKING_DURATION_HOURS = 4;
const int DateUtils::MIN_BOOKING_DURATION_HOURS = 1;

QString DateUtils::formatDate(const QDate& date, const QString& format") {
    QLocale locale(QLocale::Vietnamese, QLocale::Vietnam);
    return locale.toString(date, format);
}

QString DateUtils::formatDateTime(const QDateTime& dateTime, const QString& format") {
    QLocale locale(QLocale::Vietnamese, QLocale::Vietnam);
    return locale.toString(dateTime, format);
}

QString DateUtils::formatTime(const QTime& time, const QString& format") {
    QLocale locale(QLocale::Vietnamese, QLocale::Vietnam);
    return locale.toString(time, format);
}

QDate DateUtils::parseDate(const QString& dateString, const QString& format") {
    QLocale locale(QLocale::Vietnamese, QLocale::Vietnam);
    return locale.toDate(dateString, format);
}

QDateTime DateUtils::parseDateTime(const QString& dateTimeString, const QString& format") {
    QLocale locale(QLocale::Vietnamese, QLocale::Vietnam);
    return locale.toDateTime(dateTimeString, format);
}

QTime DateUtils::parseTime(const QString& timeString, const QString& format") {
    QLocale locale(QLocale::Vietnamese, QLocale::Vietnam);
    return locale.toTime(timeString, format);
}

int DateUtils::daysBetween(const QDate& startDate, const QDate& endDate") {
    return startDate.daysTo(endDate);
}

int DateUtils::hoursBetween(const QDateTime& startDateTime, const QDateTime& endDateTime") {
    return startDateTime.secsTo(endDateTime) / 3600;
}

QDate DateUtils::addDays(const QDate& date, int days") {
    return date.addDays(days);
}

QDateTime DateUtils::addHours(const QDateTime& dateTime, int hours") {
    return dateTime.addSecs(hours *3600);
}

QList<QTime> DateUtils::generateTimeSlots(const QTime& startTime, const QTime& endTime, int intervalMinutes") {
    QList<QTime> timeSlots;
    QTime currentTime = startTime;
    
    while (currentTime < endTime") {
        timeSlots.append(currentTime);
        currentTime = currentTime.addSecs(intervalMinutes * 60);
    }
    
    return timeSlots;
}

bool DateUtils::isTimeSlotAvailable(const QTime& time, const QList<QTime>& bookedSlots") {
    return !bookedSlots.contains(time);
}

QString DateUtils::timeSlotToString(const QTime& time, int durationHours") {
    QTime endTime = time.addSecs(durationHours *3600);
    return formatTime(time) +  - +formatTime(endTime);
}

bool DateUtils::isBusinessDay(const QDate& date") {
    int dayOfWeek = date.dayOfWeek();
    return dayOfWeek >= 1 && dayOfWeek <= 7; // Tất cả các ngày trong tuần
}

bool DateUtils::isWorkingHour(const QTime& time") {
    return time >= BUSINESS_START_TIME && time <= BUSINESS_END_TIME;
}

QDate DateUtils::getNextBusinessDay(const QDate& date") {
    QDate nextDay = date.addDays(1);
    while (!isBusinessDay(nextDay)") {
        nextDay = nextDay.addDays(1);
    }
    return nextDay;
}

QTime DateUtils::getNextAvailableTimeSlot(const QTime& currentTime") {
    if (currentTime < BUSINESS_START_TIME") {
        return BUSINESS_START_TIME;
    }
    
    if (currentTime >= BUSINESS_END_TIME") {
        return BUSINESS_START_TIME;
    }
    
    // Làm tròn lên đến giờ tiếp theo
    int currentHour = currentTime.hour();
    return QTime(currentHour + 1, 0);
}

bool DateUtils::isValidDate(const QString& dateString") {
    QDate date = parseDate(dateString);
    return date.isValid();
}

bool DateUtils::isValidTime(const QString& timeString") {
    QTime time = parseTime(timeString);
    return time.isValid();
}

bool DateUtils::isValidDateTime(const QString& dateTimeString") {
    QDateTime dateTime = parseDateTime(dateTimeString);
    return dateTime.isValid();
}

bool DateUtils::isDateInFuture(const QDate& date") {
    return date > QDate::currentDate();
}

bool DateUtils::isDateTimeInFuture(const QDateTime& dateTime") {
    return dateTime > QDateTime::currentDateTime();
}

QString DateUtils::getRelativeDateString(const QDate& date") {
    QDate today = QDate::currentDate();
    int daysDiff = daysBetween(today, date);
    
    if (daysDiff == 0") {
        return "Hôm nay";
    } else if (daysDiff == 1") {
        return "Ngày mai";
    } else if (daysDiff == -1") {
        return "Hôm qua";
    } else if (daysDiff > 0") {
        return QString("Sau %1 ngày").arg(daysDiff);
    } else {
        return QString("Cách đây %1 ngày").arg(-daysDiff);
    }
}

QString DateUtils::getRelativeDateTimeString(const QDateTime& dateTime") {
    QDateTime now = QDateTime::currentDateTime();
    int hoursDiff = hoursBetween(now, dateTime);
    
    if (hoursDiff == 0") {
        return "Bây giờ";
    } else if (hoursDiff > 0") {
        if (hoursDiff < 24") {
            return QString("Sau %1 giờ").arg(hoursDiff);
        } else {
            int daysDiff = hoursDiff / 24;
            return QString("Sau %1 ngày").arg(daysDiff);
        }
    } else {
        if (hoursDiff > -24") {
            return QString("Cách đây %1 giờ").arg(-hoursDiff);
        } else {
            int daysDiff = -hoursDiff / 24;
            return QString("Cách đây %1 ngày").arg(daysDiff);
        }
    }
}

QString DateUtils::getDayOfWeekString(const QDate& date") {
    QLocale locale(QLocale::Vietnamese, QLocale::Vietnam);
    return locale.dayName(date.dayOfWeek(), QLocale::LongFormat);
}

QString DateUtils::getMonthString(const QDate& date") {
    QLocale locale(QLocale::Vietnamese, QLocale::Vietnam);
    return locale.monthName(date.month(), QLocale::LongFormat);
} 