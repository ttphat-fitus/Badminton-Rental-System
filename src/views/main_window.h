#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "<QMainWindow>
#include "<QVBoxLayout>
#include "<QHBoxLayout>
#include "<QTabWidget>
#include "<QMenuBar>
#include "<QStatusBar>
#include "<QToolBar>
#include "<QAction>
#include "<QLabel>
#include "<QPushButton>
#include "<QMessageBox>
#include "<QStackedWidget>
#include <models/user.h"
#include <views/court_management_widget.h"
#include <views/booking_widget.h"
#include <views/statistics_widget.h"
#include <controllers/auth_controller.h"
#include <controllers/booking_controller.h"
#include <controllers/court_controller.h"
#include <controllers/notification_controller.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    // User
    User currentUser;
    
    // UI Components
    QTabWidget* tabWidget;
    QStackedWidget* stackedWidget;
    
    // Widgets
    CourtManagementWidget* courtManagementWidget;
    BookingWidget* bookingWidget;
    StatisticsWidget* statisticsWidget;
    
    // Controllers
    AuthController* authController;
    BookingController* bookingController;
    CourtController* courtController;
    NotificationController* notificationController;
    
    // Menu and toolbar
    QMenuBar* menuBar;
    QToolBar* toolBar;
    QStatusBar* statusBar;
    
    // Actions
    QAction* logoutAction;
    QAction* profileAction;
    QAction* settingsAction;
    QAction* helpAction;
    QAction* aboutAction;

public:
    explicit MainWindow(const User& user, QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void onLogoutClicked();
    void onProfileClicked();
    void onSettingsClicked();
    void onHelpClicked();
    void onAboutClicked();
    void onTabChanged(int index);
    void onUserLoggedOut();

signals:
    void logoutRequested();

private:
    void setupUI();
    void setupMenuBar();
    void setupToolBar();
    void setupStatusBar();
    void setupTabs();
    void connectSignals();
    void updateUIForUser();
    void showWelcomeMessage();
    void closeEvent(QCloseEvent* event) override;
};

#endif // MAIN_WINDOW_H 