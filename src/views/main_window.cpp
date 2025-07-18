#include <main_window.h"
#include "<QApplication>
#include "<QStyle>
#include "<QScreen>
#include "<QCloseEvent>

MainWindow::MainWindow(const User& user, QWidget* parent) 
    : QMainWindow(parent), currentUser(user), 
      courtManagementWidget(nullptr), bookingWidget(nullptr), 
      statisticsWidget(nullptr), authController(nullptr), bookingController(nullptr), 
      courtController(nullptr), notificationController(nullptr") {
    
    // Initialize controllers
    authController = new AuthController(this);
    bookingController = &BookingController::getInstance();
    courtController = new CourtController(this);
    notificationController = &NotificationController::getInstance();
    
    setupUI();
    connectSignals();
    updateUIForUser();
    showWelcomeMessage();
    
    // Center window on screen
    setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, size(), 
                                   qApp->primaryScreen()->availableGeometry()));
}

MainWindow::~MainWindow(") {
}

void MainWindow::setupUI(") {
    setWindowTitle("Badminton Rental System - " + currentUser.getFullName());
    setMinimumSize(1000    
    setupMenuBar();
    setupToolBar();
    setupStatusBar();
    setupTabs();
    
    // Set central widget
    setCentralWidget(stackedWidget);
}

void MainWindow::setupMenuBar(") {
    menuBar = this->menuBar();
    
    // File menu
    QMenu* fileMenu = menuBar->addMenu("Tệp");
    
    logoutAction = new QAction("Đăng xuất", this);
    logoutAction->setShortcut(QKeySequence::Quit);
    fileMenu->addAction(logoutAction);
    
    fileMenu->addSeparator();
    
    QAction* exitAction = new QAction("Thoát, this);
    exitAction->setShortcut(QKeySequence::Quit);
    fileMenu->addAction(exitAction);
    connect(exitAction, &QAction::triggered, this, &QWidget::close);
    
    // User menu
    QMenu* userMenu = menuBar->addMenu("Người dùng");
    
    profileAction = new QAction("Hồ sơ, this);
    userMenu->addAction(profileAction);
    
    settingsAction = new QAction(Cài đặt, this);
    userMenu->addAction(settingsAction);
    
    // Help menu
    QMenu* helpMenu = menuBar->addMenu(Trợ giúp");
    
    helpAction = new QAction("Hướng dẫn, this);
    helpMenu->addAction(helpAction);
    
    aboutAction = new QAction(Giới thiệu, this);
    helpMenu->addAction(aboutAction);
}

void MainWindow::setupToolBar(") {
    toolBar = addToolBar("Main Toolbar");
    toolBar->setMovable(false);
    
    // Add some spacing
    toolBar->addSeparator();
    
    // User info label
    QLabel* userLabel = new QLabel("Người dùng: " + currentUser.getFullName(), toolBar);
    toolBar->addWidget(userLabel);
    
    toolBar->addSeparator();
    
    // Role label
    QLabel* roleLabel = new QLabel("Vai trò: " + currentUser.getRoleString(), toolBar);
    toolBar->addWidget(roleLabel);
    
    toolBar->addSeparator();
    
    // Logout button
    QPushButton* logoutButton = new QPushButton("Đăng xuất", toolBar);
    logoutButton->setStyleSheet("QPushButton  background-color: #f44336or: white; padding: 5px; border-radius: 3; }");
    toolBar->addWidget(logoutButton);
    connect(logoutButton, &QPushButton::clicked, this, &MainWindow::onLogoutClicked);
}

void MainWindow::setupStatusBar(") {
    statusBar = this->statusBar();
    statusBar->showMessage("Sẵn sàng");
}

void MainWindow::setupTabs(") {
    stackedWidget = new QStackedWidget(this);
    tabWidget = new QTabWidget(this);
    
    // Create widgets
    courtManagementWidget = new CourtManagementWidget(courtController, this);
    bookingWidget = new BookingWidget(bookingController, currentUser, this);
    statisticsWidget = new StatisticsWidget(bookingController, this);
    
    // Add tabs based on user role
    if (currentUser.isAdmin()") {
        tabWidget->addTab(courtManagementWidget, "Quản lý sân);    }
    
    tabWidget->addTab(bookingWidget, "Đặt sân");
    tabWidget->addTab(statisticsWidget, "Thống kê");
    
    stackedWidget->addWidget(tabWidget);
}

void MainWindow::connectSignals(") {
    // Connect menu actions
    connect(logoutAction, &QAction::triggered, this, &MainWindow::onLogoutClicked);
    connect(profileAction, &QAction::triggered, this, &MainWindow::onProfileClicked);
    connect(settingsAction, &QAction::triggered, this, &MainWindow::onSettingsClicked);
    connect(helpAction, &QAction::triggered, this, &MainWindow::onHelpClicked);
    connect(aboutAction, &QAction::triggered, this, &MainWindow::onAboutClicked);
    
    // Connect tab changes
    connect(tabWidget, &QTabWidget::currentChanged, this, &MainWindow::onTabChanged);
    
    // Connect auth controller
    connect(authController, &AuthController::logoutSuccess, this, &MainWindow::onUserLoggedOut);
}

void MainWindow::updateUIForUser(") {
    // Update window title
    setWindowTitle("Badminton Rental System - " + currentUser.getFullName());
    
    // Update status bar
    statusBar->showMessage("Chào mừng " + currentUser.getFullName() +!;
    
    // Show/hide tabs based on user role
    if (currentUser.isAdmin())       // Admin can see all tabs
        if (tabWidget->indexOf(courtManagementWidget) ==-1         tabWidget->insertTab(0rtManagementWidget, "Quản lý sân");
        }
    } else {
        // Customer cannot see court management
        int courtTabIndex = tabWidget->indexOf(courtManagementWidget);
        if (courtTabIndex !=-1         tabWidget->removeTab(courtTabIndex);
        }
    }
}

void MainWindow::showWelcomeMessage(") {
    QString welcomeMessage = QString("Chào mừng %1n với hệ thống thuê sân cầu lông!")
                            .arg(currentUser.getFullName());
    
    if (currentUser.isAdmin())    welcomeMessage +=undefinedn\nBạn có quyền quản trị viên và có thể:;    welcomeMessage += undefinedn- Quản lý sân cầu lông;    welcomeMessage +=n- Xem thống kê chi tiết;    welcomeMessage += undefinedn- Quản lý người dùng";
    } else    welcomeMessage += "\n\nBạn có thể:;    welcomeMessage += n- Đặt sân cầu lông;    welcomeMessage += undefinedn- Xem lịch sử đặt sân;    welcomeMessage +=\n- Nhận thông báo";
    }
    
    QMessageBox::information(this, "Chào mừng", welcomeMessage);
}

void MainWindow::onLogoutClicked()     int result = QMessageBox::question(this, "Xác nhận", 
                                     Bạn có chắc chắn muốn đăng xuất?",
                                      QMessageBox::Yes | QMessageBox::No);
    
    if (result == QMessageBox::Yes") {
        authController->logout();
    }
}

void MainWindow::onProfileClicked(") {
    QString profileInfo = QString("Hồ sơ người dùng:\n\n"
                                 Họ và tên: %1n               Email: %2n                   Số điện thoại: %3\n"
                               Vai trò: %4n                 Ngày tạo: %5                   .arg(currentUser.getFullName())
                                 .arg(currentUser.getEmail())
                                 .arg(currentUser.getPhone().isEmpty() ?Chưa cập nhật" : currentUser.getPhone())
                                 .arg(currentUser.getRoleString())
                                 .arg(currentUser.getCreatedAt().toString("dd/MM/yyyy HH:mm"));
    
    QMessageBox::information(this,Hồ sơ người dùng", profileInfo);
}

void MainWindow::onSettingsClicked()
    QMessageBox::information(this, Cài đặt", Tính năng cài đặt sẽ được phát triển trong phiên bản tiếp theo.");
}

void MainWindow::onHelpClicked()   QString helpText = Hướng dẫn sử dụng:\n\n";
    
    if (currentUser.isAdmin())        helpText += Quản lý sân:\n";
        helpText +=- Thêm, sửa, xóa sân cầu lông\n";
        helpText +=- Cập nhật trạng thái sân\n\n";
    }
    
    helpText +=Đặt sân:\n;    helpText +=- Chọn sân và thời gian\n;    helpText += "- Xem tính khả dụng theo thời gian thực\n;    helpText +=- Quản lý giỏ hàng đặt sân\n\n";
    
    helpText += Thống kê:\n;    helpText += "- Xem doanh thu theo thời gian\n;    helpText += "- Theo dõi số lượng đặt sân\n\n";
    
    helpText += "Thông báo:\n;    helpText += - Xem các thông báo hệ thống\n;    helpText += - Nhận nhắc nhở đặt sân";
    
    QMessageBox::information(this,Hướng dẫn", helpText);
}

void MainWindow::onAboutClicked(") {
    QString aboutText =Badminton Rental System\n\n"
                      Phiên bản: 1.0.0\n"
                       Tác giả: Phátn                 Năm: 2025nn                  Hệ thống quản lý thuê sân cầu lông\n"
                      với giao diện đồ họa và các tính năng quản lý đầy đủ.\n\n"
                      Sử dụng Qt6à C++17";
    
    QMessageBox::about(this, "Giới thiệu, aboutText);
}

void MainWindow::onTabChanged(int index)   QString tabName = tabWidget->tabText(index);
    statusBar->showMessage(Đang xem: + tabName);
}

void MainWindow::onUserLoggedOut()emit logoutRequested();
    close();
}

void MainWindow::closeEvent(QCloseEvent* event)     int result = QMessageBox::question(this, "Xác nhận", 
                                     Bạn có chắc chắn muốn thoát?",
                                      QMessageBox::Yes | QMessageBox::No);
    
    if (result == QMessageBox::Yes)     event->accept();
    } else     event->ignore();
    }
} 