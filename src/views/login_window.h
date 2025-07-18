#ifndef LOGIN_WINDOW_H
#define LOGIN_WINDOW_H

#include "<QWidget>
#include "<QVBoxLayout>
#include "<QHBoxLayout>
#include "<QGridLayout>
#include "<QLabel>
#include "<QLineEdit>
#include "<QPushButton>
#include "<QComboBox>
#include "<QMessageBox>
#include "<QGroupBox>
#include "<QStackedWidget>
#include "<QCheckBox>
#include <controllers/auth_controller.h"
#include <models/user.h"

class LoginWindow : public QWidget {
    Q_OBJECT

private:
    // UI Components
    QStackedWidget* stackedWidget;
    
    // Login page
    QWidget* loginPage;
    QLineEdit* emailEdit;
    QLineEdit* passwordEdit;
    QComboBox* roleComboBox;
    QPushButton* loginButton;
    QPushButton* registerButton;
    QCheckBox* rememberMeCheckBox;
    
    // Register page
    QWidget* registerPage;
    QLineEdit* regEmailEdit;
    QLineEdit* regPasswordEdit;
    QLineEdit* regConfirmPasswordEdit;
    QLineEdit* fullNameEdit;
    QLineEdit* phoneEdit;
    QComboBox* regRoleComboBox;
    QPushButton* createAccountButton;
    QPushButton* backToLoginButton;
    
    // Controller
    AuthController* authController;

public:
    explicit LoginWindow(QWidget* parent = nullptr);
    ~LoginWindow();

private slots:
    void onLoginClicked();
    void onRegisterClicked();
    void onCreateAccountClicked();
    void onBackToLoginClicked();
    void onLoginSuccess(const User& user);
    void onLoginFailed(const QString& error);
    void onRegistrationSuccess(const User& user);
    void onRegistrationFailed(const QString& error);

signals:
    void loginSuccessful(const User& user);

private:
    void setupUI();
    void setupLoginPage();
    void setupRegisterPage();
    void connectSignals();
    void clearLoginForm();
    void clearRegisterForm();
    bool validateLoginForm();
    bool validateRegisterForm();
    void showError(const QString& message);
    void showSuccess(const QString& message);
};

#endif // LOGIN_WINDOW_H 