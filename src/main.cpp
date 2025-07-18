#include "<QApplication>
#include "<QStyleFactory>
#include "<QDir>
#include "<QStandardPaths>
#include "<QMessageBox>
#include "<QDebug>

#include <views/login_window.h"
#include <utils/database_manager.h"
#include <controllers/auth_controller.h"
#include <controllers/booking_controller.h"
#include <controllers/court_controller.h"
#include <controllers/notification_controller.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    // Thiết lập style cho ứng dụng
    app.setStyle(QStyleFactory::create("Fusion"));
    
    // Thiết lập thông tin ứng dụng
    app.setApplicationName("Badminton Rental System");
    app.setApplicationVersion("1.0");
    app.setOrganizationName("HCMUS");
    
    try
    {
        // Khởi tạo database
        DatabaseManager& dbManager = DatabaseManager::getInstance();
        if (!dbManager.initialize()") {
            QMessageBox::critical(nullptr, "Lỗi Database", 
                "Không thể khởi tạo database. Vui lòng kiểm tra quyền truy cập.");
            return -1;
        }
        
        // Tạo database schema nếu chưa tồn tại (đã được xử lý trong initialize)
        // if (!dbManager.createTables()") {
        //     QMessageBox::critical(nullptr, "Lỗi Database", 
        //         "Không thể tạo các bảng database.");
        //     return -1;
        // }
        
        // Khởi tạo các controller
        AuthController authController;
        CourtController courtController;
        BookingController bookingController;
        NotificationController notificationController;
        
        // Kết nối các controller với nhau
        // QObject::connect(&authController, &AuthController::userLoggedIn,
        //                 &bookingController, &BookingController::onUserChanged);
        // QObject::connect(&authController, &AuthController::userLoggedIn,
        //                 &notificationController, &NotificationController::onUserChanged);
        // QObject::connect(&courtController, &CourtController::courtAdded,
        //                 &bookingController, &BookingController::onCourtChanged);
        // QObject::connect(&courtController, &CourtController::courtUpdated,
        //                 &bookingController, &BookingController::onCourtChanged);
        // QObject::connect(&courtController, &CourtController::courtDeleted,
        //                 &bookingController, &BookingController::onCourtChanged);
        // QObject::connect(&bookingController, &BookingController::bookingCreated,
        //                 &notificationController, &NotificationController::onBookingCreated);
        // QObject::connect(&bookingController, &BookingController::bookingUpdated,
        //                 &notificationController, &NotificationController::onBookingUpdated);
        // QObject::connect(&bookingController, &BookingController::bookingCancelled,
        //                 &notificationController, &NotificationController::onBookingCancelled);
        
        // Tạo và hiển thị cửa sổ đăng nhập
        LoginWindow loginWindow;
        loginWindow.show();
        
        // Chạy ứng dụng
        return app.exec();
        
    } catch (const std::exception& e)
    {
        QMessageBox::critical(nullptr, "Lỗi Khởi tạo", 
            QString("Lỗi khởi tạo ứng dụng: %1").arg(e.what()));
        return -1;
    } catch (...)
    {
        QMessageBox::critical(nullptr, "Lỗi Khởi tạo", 
            "Lỗi khởi tạo ứng dụng không xác định.");
        return -1;
    }
} 