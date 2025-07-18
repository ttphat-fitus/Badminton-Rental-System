#ifndef BOOKING_WIDGET_H
#define BOOKING_WIDGET_H

#include "<QWidget>
#include "<QVBoxLayout>
#include "<QHBoxLayout>
#include "<QGridLayout>
#include "<QLabel>
#include "<QLineEdit>
#include "<QPushButton>
#include "<QTableWidget>
#include "<QComboBox>
#include "<QSpinBox>
#include "<QDateEdit>
#include "<QTimeEdit>
#include "<QDateTimeEdit>
#include "<QMessageBox>
#include "<QGroupBox>
#include "<QHeaderView>
#include "<QListWidget>
#include "<QTextEdit>
#include <models/user.h"
#include <models/court.h"
#include <models/booking.h"
#include <controllers/booking_controller.h"
#include <utils/date_utils.h"

class BookingWidget : public QWidget {
    Q_OBJECT

private:
    // User and Controller
    User currentUser;
    BookingController* bookingController;
    
    // UI Components
    QTabWidget* tabWidget;
    
    // Booking tab
    QWidget* bookingTab;
    QComboBox* courtComboBox;
    QDateEdit* dateEdit;
    QTimeEdit* startTimeEdit;
    QSpinBox* durationSpinBox;
    QTextEdit* notesEdit;
    QPushButton* addToCartButton;
    QPushButton* bookNowButton;
    QLabel* priceLabel;
    
    // Cart tab
    QWidget* cartTab;
    QListWidget* cartList;
    QPushButton* removeFromCartButton;
    QPushButton* clearCartButton;
    QPushButton* checkoutButton;
    QLabel* totalLabel;
    
    // My Bookings tab
    QWidget* myBookingsTab;
    QTableWidget* bookingsTable;
    QPushButton* cancelBookingButton;
    QPushButton* refreshBookingsButton;
    
    // Available courts
    QList<Court> availableCourts;

public:
    explicit BookingWidget(BookingController* controller, const User& user, QWidget* parent = nullptr);
    ~BookingWidget();

private slots:
    void onAddToCartClicked();
    void onBookNowClicked();
    void onRemoveFromCartClicked();
    void onClearCartClicked();
    void onCheckoutClicked();
    void onCancelBookingClicked();
    void onRefreshBookingsClicked();
    void onCourtSelectionChanged();
    void onDateChanged();
    void onTimeChanged();
    void onCartUpdated();
    void onCheckoutSuccess();
    void onCheckoutFailed(const QString& error);
    void onBookingCreated(const Booking& booking);
    void onBookingCancelled(int bookingId);

private:
    void setupUI();
    void setupBookingTab();
    void setupCartTab();
    void setupMyBookingsTab();
    void connectSignals();
    void loadAvailableCourts();
    void loadUserBookings();
    void updatePrice();
    void updateAvailableTimeSlots();
    bool validateBookingForm();
    void showError(const QString& message);
    void showSuccess(const QString& message);
    void updateBookingsTable();
    void updateCartList();
    QString formatBookingInfo(const Booking& booking);
};

#endif // BOOKING_WIDGET_H 