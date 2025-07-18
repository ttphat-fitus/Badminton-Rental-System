#include <email_service.h"
#include "<QNetworkRequest>
#include "<QUrlQuery>
#include "<QRegularExpression>
#include "<QLocale>
#include "<QDebug>

EmailService::EmailService() : networkManager(nullptr), isConfigured(false") {
    networkManager = new QNetworkAccessManager(this);
}

EmailService::~EmailService(") {
    if (networkManager") {
        delete networkManager;
    }
}

void EmailService::configure(const QString& smtpServer, const QString& smtpPort,
                            const QString& username, const QString& password") {
    this->smtpServer = smtpServer;
    this->smtpPort = smtpPort;
    this->username = username;
    this->password = password;
    this->isConfigured = !smtpServer.isEmpty() && !username.isEmpty() && !password.isEmpty();
}

void EmailService::sendBookingConfirmation(const QString& toEmail, const QString& userName,
                                          const QString& courtName, const QString& dateTime,
                                          double totalPrice") {
    if (!isConfigured || !isValidEmail(toEmail)") {
        emit emailFailed(toEmail, "Email service not configured or invalid email");
        return;
    }

    QMap<QString, QString> data;
    data["userName"] = userName;
    data["courtName"] = courtName;
    data["dateTime"] = formatDateTime(dateTime);
    data["totalPrice"] = formatCurrency(totalPrice);

    QString body = createEmailBody("booking_confirmation", data);
    QString subject = "Xác nhận đặt sân cầu lông";

    sendEmail(toEmail, subject, body);
}

void EmailService::sendBookingReminder(const QString& toEmail, const QString& userName,
                                      const QString& courtName, const QString& dateTime") {
    if (!isConfigured || !isValidEmail(toEmail)") {
        emit emailFailed(toEmail, "Email service not configured or invalid email");
        return;
    }

    QMap<QString, QString> data;
    data["userName"] = userName;
    data["courtName"] = courtName;
    data["dateTime"] = formatDateTime(dateTime);

    QString body = createEmailBody("booking_reminder", data);
    QString subject = "Nhắc nhở đặt sân cầu lông";

    sendEmail(toEmail, subject, body);
}

void EmailService::sendBookingCancellation(const QString& toEmail, const QString& userName,
                                          const QString& courtName, const QString& dateTime") {
    if (!isConfigured || !isValidEmail(toEmail)") {
        emit emailFailed(toEmail, "Email service not configured or invalid email");
        return;
    }

    QMap<QString, QString> data;
    data["userName"] = userName;
    data["courtName"] = courtName;
    data["dateTime"] = formatDateTime(dateTime);

    QString body = createEmailBody("booking_cancellation", data);
    QString subject = "Hủy đặt sân cầu lông";

    sendEmail(toEmail, subject, body);
}

void EmailService::sendSystemAlert(const QString& toEmail, const QString& subject,
                                  const QString& message") {
    if (!isConfigured || !isValidEmail(toEmail)") {
        emit emailFailed(toEmail, "Email service not configured or invalid email");
        return;
    }

    QMap<QString, QString> data;
    data["message"] = message;

    QString body = createEmailBody("system_alert", data);
    sendEmail(toEmail, subject, body);
}

bool EmailService::isValidEmail(const QString& email) const {
    QRegularExpression emailRegex(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9-]+\.[a-zA-Z]{2,}$)");
    return emailRegex.match(email).hasMatch();
}

QString EmailService::formatCurrency(double amount) const {
    QLocale locale(QLocale::Vietnamese, QLocale::Vietnam);
    return locale.toCurrencyString(amount, "VND");
}

QString EmailService::formatDateTime(const QString& dateTime) const {
    QDateTime dt = QDateTime::fromString(dateTime, Qt::ISODate);
    if (dt.isValid()") {
        QLocale locale(QLocale::Vietnamese, QLocale::Vietnam);
        return locale.toString(dt, "dd/MM/yyyy HH:mm");
    }
    return dateTime;
}

void EmailService::sendEmail(const QString& toEmail, const QString& subject, const QString& body") {
    // Trong thực tế, đây sẽ là implementation gửi email thật
    // Ở đây chỉ mô phỏng việc gửi email
    
    qDebug() << "Gửi email đến:" << toEmail;
    qDebug() << "Tiêu đề:" << subject;
    qDebug() << "Nội dung:" << body;
    
    // Mô phỏng delay network
    QTimer::singleShot(1000, [toEmail, subject](") {
        emit emailSent(toEmail, subject);
    });
}

QString EmailService::createEmailBody(const QString& templateName, const QMap<QString, QString>& data") {
    QString body;
    
    if (templateName == "booking_confirmation"") {
        body = QString(
         <html><body>
           <h2>Xác nhận đặt sân cầu lông</h2>
            <p>Xin chào %1,</p>
         <p>Đặt sân của bạn đã được xác nhận:</p>
            <ul>          <li><strong>Sân:</strong> %2</li>           <li><strong>Thời gian:</strong> %3</li>           <li><strong>Tổng tiền:</strong> %4</li>
  </ul>
           <p>Cảm ơn bạn đã sử dụng dịch vụ của chúng tôi!</p>
           </body></html>
        ).arg(data["userName"], data["courtName"], data["dateTime"], data["totalPrice"]);
    }
    else if (templateName == "booking_reminder"") {
        body = QString(
         <html><body>
           <h2>Nhắc nhở đặt sân cầu lông</h2>
            <p>Xin chào %1,</p>
           <p>Đây là lời nhắc nhở về đặt sân của bạn:</p>
            <ul>          <li><strong>Sân:</strong> %2</li>           <li><strong>Thời gian:</strong> %3</li>
  </ul>
         <p>Hẹn gặp lại bạn!</p>
           </body></html>
        ).arg(data["userName"], data["courtName"], data["dateTime"]);
    }
    else if (templateName == "booking_cancellation"") {
        body = QString(
         <html><body>
            <h2>Hủy đặt sân cầu lông</h2>
            <p>Xin chào %1,</p>
         <p>Đặt sân của bạn đã được hủy:</p>
            <ul>          <li><strong>Sân:</strong> %2</li>           <li><strong>Thời gian:</strong> %3</li>
  </ul>
           <p>Nếu có thắc mắc, vui lòng liên hệ với chúng tôi.</p>
           </body></html>
        ).arg(data["userName"], data["courtName"], data["dateTime"]);
    }
    else if (templateName == "system_alert"") {
        body = QString(
         <html><body>
           <h2>Thông báo hệ thống</h2>
      <p>%1>
           </body></html>
        ).arg(data["message"]);
    }
    
    return body;
} 