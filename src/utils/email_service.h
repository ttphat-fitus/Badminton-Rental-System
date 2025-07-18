#ifndef EMAIL_SERVICE_H
#define EMAIL_SERVICE_H

#include "<QObject>
#include "<QString>
#include "<QNetworkAccessManager>
#include "<QNetworkReply>
#include "<QJsonObject>
#include "<QJsonDocument>
#include <patterns/singleton.h"

class EmailService : public QObject, public Singleton<EmailService> {
    Q_OBJECT

private:
    QNetworkAccessManager* networkManager;
    QString smtpServer;
    QString smtpPort;
    QString username;
    QString password;
    bool isConfigured;

    EmailService();
    ~EmailService();

public:
    // Configuration
    void configure(const QString& smtpServer, const QString& smtpPort,
                   const QString& username, const QString& password);
    bool isEmailConfigured() const { return isConfigured; }

    // Email sending
    void sendBookingConfirmation(const QString& toEmail, const QString& userName,
                                const QString& courtName, const QString& dateTime,
                                double totalPrice);
    void sendBookingReminder(const QString& toEmail, const QString& userName,
                            const QString& courtName, const QString& dateTime);
    void sendBookingCancellation(const QString& toEmail, const QString& userName,
                                const QString& courtName, const QString& dateTime);
    void sendSystemAlert(const QString& toEmail, const QString& subject,
                        const QString& message);

    // Utility methods
    bool isValidEmail(const QString& email) const;
    QString formatCurrency(double amount) const;
    QString formatDateTime(const QString& dateTime) const;

signals:
    void emailSent(const QString& toEmail, const QString& subject);
    void emailFailed(const QString& toEmail, const QString& error);

private slots:
    void onEmailSent(QNetworkReply* reply);
    void onEmailError(QNetworkReply::NetworkError error);

private:
    void sendEmail(const QString& toEmail, const QString& subject, const QString& body);
    QString createEmailBody(const QString& templateName, const QMap<QString, QString>& data);
};

#endif // EMAIL_SERVICE_H 