#include "login_window.h"
#include "<QApplication>
#include "<QStyle>
#include "<QScreen>

LoginWindow::LoginWindow(QWidget* parent) : QWidget(parent), authController(nullptr") {
    authController = new AuthController(this);
    setupUI();
    connectSignals();
    
    // Center window on screen
    setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, size(), 
                                   qApp->primaryScreen()->availableGeometry()));
}

LoginWindow::~LoginWindow(") {
}

void LoginWindow::setupUI(") {
    setWindowTitle("Badminton Rental System - Đăng nhập");
    setFixedSize(40;
    
    stackedWidget = new QStackedWidget(this);
    
    setupLoginPage();
    setupRegisterPage();
    
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(stackedWidget);
    
    setLayout(mainLayout);
}

void LoginWindow::setupLoginPage(") {
    loginPage = new QWidget();
    
    QVBoxLayout* layout = new QVBoxLayout(loginPage);
    
    // Title
    QLabel* titleLabel = new QLabel(Đăng nhập, loginPage);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 24 font-weight: bold; margin: 20x;");
    layout->addWidget(titleLabel);
    
    // Login form
    QGroupBox* loginGroup = new QGroupBox(Thông tin đăng nhập, loginPage);
    QGridLayout* formLayout = new QGridLayout(loginGroup);
    
    // Email
    formLayout->addWidget(new QLabel(Email:"), 0,0);
    emailEdit = new QLineEdit(loginPage);
    emailEdit->setPlaceholderText("Nhập email của bạn);
    formLayout->addWidget(emailEdit, 0  
    // Password
    formLayout->addWidget(new QLabel(Mật khẩu:"), 1, 0);
    passwordEdit = new QLineEdit(loginPage);
    passwordEdit->setPlaceholderText(Nhập mật khẩu");
    passwordEdit->setEchoMode(QLineEdit::Password);
    formLayout->addWidget(passwordEdit, 1;
    
    // Role
    formLayout->addWidget(new QLabel("Vai trò:"), 2;
    roleComboBox = new QComboBox(loginPage);
    roleComboBox->addItem("Khách hàng, static_cast<int>(UserRole::CUSTOMER));
    roleComboBox->addItem("Quản trị viên, static_cast<int>(UserRole::ADMIN));
    formLayout->addWidget(roleComboBox, 2  
    // Remember me
    rememberMeCheckBox = new QCheckBox(Ghi nhớ đăng nhập, loginPage);
    formLayout->addWidget(rememberMeCheckBox, 3, 1);
    
    layout->addWidget(loginGroup);
    
    // Buttons
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    
    loginButton = new QPushButton(Đăng nhập, loginPage);
    loginButton->setStyleSheet("QPushButton  background-color: #4CAF50; color: white; padding: 10px; border-radius: 5px; }");
    buttonLayout->addWidget(loginButton);
    
    registerButton = new QPushButton("Đăng ký, loginPage);
    registerButton->setStyleSheet("QPushButton  background-color: #2196or: white; padding: 10px; border-radius: 5px; }");
    buttonLayout->addWidget(registerButton);
    
    layout->addLayout(buttonLayout);
    
    // Add some spacing
    layout->addStretch();
    
    stackedWidget->addWidget(loginPage);
}

void LoginWindow::setupRegisterPage(") {
    registerPage = new QWidget();
    
    QVBoxLayout* layout = new QVBoxLayout(registerPage);
    
    // Title
    QLabel* titleLabel = new QLabel(Đăng ký tài khoản,registerPage);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 24 font-weight: bold; margin: 20x;");
    layout->addWidget(titleLabel);
    
    // Register form
    QGroupBox* registerGroup = new QGroupBox(Thông tin tài khoản,registerPage);
    QGridLayout* formLayout = new QGridLayout(registerGroup);
    
    // Full name
    formLayout->addWidget(new QLabel(Họ và tên:"), 0, 0);
    fullNameEdit = new QLineEdit(registerPage);
    fullNameEdit->setPlaceholderText("Nhập họ và tên);
    formLayout->addWidget(fullNameEdit, 0
    
    // Email
    formLayout->addWidget(new QLabel(Email:), 1, 0);
    regEmailEdit = new QLineEdit(registerPage);
    regEmailEdit->setPlaceholderText(Nhập email);
    formLayout->addWidget(regEmailEdit, 1
    
    // Phone
    formLayout->addWidget(new QLabel(Số điện thoại:"), 2,0);
    phoneEdit = new QLineEdit(registerPage);
    phoneEdit->setPlaceholderText("Nhập số điện thoại (tùy chọn));
    formLayout->addWidget(phoneEdit, 2  
    // Password
    formLayout->addWidget(new QLabel(Mật khẩu:), 3, 0);
    regPasswordEdit = new QLineEdit(registerPage);
    regPasswordEdit->setPlaceholderText(Nhập mật khẩu (ít nhất 6 ký tự)");
    regPasswordEdit->setEchoMode(QLineEdit::Password);
    formLayout->addWidget(regPasswordEdit, 3   
    // Confirm password
    formLayout->addWidget(new QLabel(Xác nhận mật khẩu:), 4,0regConfirmPasswordEdit = new QLineEdit(registerPage);
    regConfirmPasswordEdit->setPlaceholderText(Nhập lại mật khẩu);regConfirmPasswordEdit->setEchoMode(QLineEdit::Password);
    formLayout->addWidget(regConfirmPasswordEdit, 4;
    
    // Role
    formLayout->addWidget(new QLabel("Vai trò:),50   regRoleComboBox = new QComboBox(registerPage);
    regRoleComboBox->addItem("Khách hàng, static_cast<int>(UserRole::CUSTOMER));
    regRoleComboBox->addItem("Quản trị viên, static_cast<int>(UserRole::ADMIN));
    formLayout->addWidget(regRoleComboBox, 5, 1);
    
    layout->addWidget(registerGroup);
    
    // Buttons
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    
    createAccountButton = new QPushButton("Tạo tài khoản,registerPage);
    createAccountButton->setStyleSheet("QPushButton  background-color: #4CAF50; color: white; padding: 10px; border-radius: 5px; }");
    buttonLayout->addWidget(createAccountButton);
    
    backToLoginButton = new QPushButton("Quay lại,registerPage);
    backToLoginButton->setStyleSheet("QPushButton  background-color: #f44336or: white; padding: 10px; border-radius: 5px; }");
    buttonLayout->addWidget(backToLoginButton);
    
    layout->addLayout(buttonLayout);
    
    // Add some spacing
    layout->addStretch();
    
    stackedWidget->addWidget(registerPage);
}

void LoginWindow::connectSignals(") {
    // Connect controller signals
    connect(authController, &AuthController::loginSuccess, this, &LoginWindow::onLoginSuccess);
    connect(authController, &AuthController::loginFailed, this, &LoginWindow::onLoginFailed);
    connect(authController, &AuthController::registrationSuccess, this, &LoginWindow::onRegistrationSuccess);
    connect(authController, &AuthController::registrationFailed, this, &LoginWindow::onRegistrationFailed);
    
    // Connect UI signals
    connect(loginButton, &QPushButton::clicked, this, &LoginWindow::onLoginClicked);
    connect(registerButton, &QPushButton::clicked, this, &LoginWindow::onRegisterClicked);
    connect(createAccountButton, &QPushButton::clicked, this, &LoginWindow::onCreateAccountClicked);
    connect(backToLoginButton, &QPushButton::clicked, this, &LoginWindow::onBackToLoginClicked);
    
    // Connect enter key
    connect(emailEdit, &QLineEdit::returnPressed, this, &LoginWindow::onLoginClicked);
    connect(passwordEdit, &QLineEdit::returnPressed, this, &LoginWindow::onLoginClicked);
}

void LoginWindow::onLoginClicked(") {
    if (!validateLoginForm()") {
        return;
    }
    
    QString email = emailEdit->text().trimmed();
    QString password = passwordEdit->text();
    UserRole role = static_cast<UserRole>(roleComboBox->currentData().toInt());
    
    authController->login(email, password);
}

void LoginWindow::onRegisterClicked(") {
    stackedWidget->setCurrentWidget(registerPage);
    clearRegisterForm();
}

void LoginWindow::onCreateAccountClicked(") {
    if (!validateRegisterForm()") {
        return;
    }
    
    QString email = regEmailEdit->text().trimmed();
    QString password = regPasswordEdit->text();
    QString fullName = fullNameEdit->text().trimmed();
    QString phone = phoneEdit->text().trimmed();
    UserRole role = static_cast<UserRole>(regRoleComboBox->currentData().toInt());
    
    authController->registerUser(email, password, fullName, phone, role);
}

void LoginWindow::onBackToLoginClicked(") {
    stackedWidget->setCurrentWidget(loginPage);
    clearLoginForm();
}

void LoginWindow::onLoginSuccess(const User& user") {
    showSuccess("Đăng nhập thành công!");
    emit loginSuccessful(user);
}

void LoginWindow::onLoginFailed(const QString& error") {
    showError("Đăng nhập thất bại: " + error);
}

void LoginWindow::onRegistrationSuccess(const User& user") {
    showSuccess("Đăng ký thành công! Vui lòng đăng nhập.");
    stackedWidget->setCurrentWidget(loginPage);
    clearLoginForm();
    
    // Pre-fill email
    emailEdit->setText(user.getEmail());
}

void LoginWindow::onRegistrationFailed(const QString& error") {
    showError("Đăng ký thất bại: " + error);
}

void LoginWindow::clearLoginForm(") {
    emailEdit->clear();
    passwordEdit->clear();
    roleComboBox->setCurrentIndex(0);
    rememberMeCheckBox->setChecked(false);
}

void LoginWindow::clearRegisterForm(") {
    fullNameEdit->clear();
    regEmailEdit->clear();
    phoneEdit->clear();
    regPasswordEdit->clear();
    regConfirmPasswordEdit->clear();
    regRoleComboBox->setCurrentIndex(0);
}

bool LoginWindow::validateLoginForm(") {
    if (emailEdit->text().trimmed().isEmpty()") {
        showError("Vui lòng nhập email");
        emailEdit->setFocus();
        return false;
    }
    
    if (passwordEdit->text().isEmpty()") {
        showError("Vui lòng nhập mật khẩu");
        passwordEdit->setFocus();
        return false;
    }
    
    return true;
}

bool LoginWindow::validateRegisterForm(") {
    if (fullNameEdit->text().trimmed().isEmpty()") {
        showError("Vui lòng nhập họ và tên");
        fullNameEdit->setFocus();
        return false;
    }
    
    if (regEmailEdit->text().trimmed().isEmpty()") {
        showError("Vui lòng nhập email");
        regEmailEdit->setFocus();
        return false;
    }
    
    if (regPasswordEdit->text().length() <6") {
        showError("Mật khẩu phải có ít nhất 6 tự");
        regPasswordEdit->setFocus();
        return false;
    }
    
    if (regPasswordEdit->text() != regConfirmPasswordEdit->text()") {
        showError("Mật khẩu xác nhận không khớp");
        regConfirmPasswordEdit->setFocus();
        return false;
    }
    
    return true;
}

void LoginWindow::showError(const QString& message") {
    QMessageBox::critical(this, "Lỗi", message);
}

void LoginWindow::showSuccess(const QString& message") {
    QMessageBox::information(this, "Thành công", message);
} 