#include "booking_widget.h"
#include "<QHeaderView>

BookingWidget::BookingWidget(BookingController* controller, const User& user, QWidget* parent) 
    : QWidget(parent), currentUser(user), bookingController(controller)    setupUI();
    connectSignals();
    loadAvailableCourts();
    loadUserBookings();
}

BookingWidget::~BookingWidget()void BookingWidget::setupUI()  QVBoxLayout* mainLayout = new QVBoxLayout(this);
    
    tabWidget = new QTabWidget(this);
    
    setupBookingTab();
    setupCartTab();
    setupMyBookingsTab();
    
    mainLayout->addWidget(tabWidget);
    setLayout(mainLayout);
}

void BookingWidget::setupBookingTab()   bookingTab = new QWidget();
    
    QVBoxLayout* layout = new QVBoxLayout(bookingTab);
    
    // Title
    QLabel* titleLabel = new QLabel("Đặt sân cầu lông", bookingTab);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 18 font-weight: bold; margin: 10x;");
    layout->addWidget(titleLabel);
    
    // Booking form
    QGroupBox* formGroup = new QGroupBox(Thông tin đặt sân", bookingTab);
    QGridLayout* formLayout = new QGridLayout(formGroup);
    
    // Court selection
    formLayout->addWidget(new QLabel(Chọn sân:"), 0, 0);
    courtComboBox = new QComboBox(bookingTab);
    courtComboBox->addItem("Chọn sân...", -1;
    formLayout->addWidget(courtComboBox, 0;
    
    // Date selection
    formLayout->addWidget(new QLabel("Ngày:"), 1, 0    dateEdit = new QDateEdit(bookingTab);
    dateEdit->setDate(QDate::currentDate());
    dateEdit->setMinimumDate(QDate::currentDate());
    dateEdit->setCalendarPopup(true);
    formLayout->addWidget(dateEdit, 1;
    
    // Time selection
    formLayout->addWidget(new QLabel(Giờ bắt đầu:"), 2,0
    startTimeEdit = new QTimeEdit(bookingTab);
    startTimeEdit->setTime(QTime(8, 0
    startTimeEdit->setDisplayFormat(HH:mm);
    formLayout->addWidget(startTimeEdit, 2  
    // Duration
    formLayout->addWidget(new QLabel("Thời gian (giờ):"), 3, 0);
    durationSpinBox = new QSpinBox(bookingTab);
    durationSpinBox->setRange(1, 4);
    durationSpinBox->setValue(1;
    formLayout->addWidget(durationSpinBox, 3
    
    // Notes
    formLayout->addWidget(new QLabel("Ghi chú:"), 4,0);
    notesEdit = new QTextEdit(bookingTab);
    notesEdit->setMaximumHeight(80);
    notesEdit->setPlaceholderText(Nhập ghi chú (tùy chọn));
    formLayout->addWidget(notesEdit, 4
    
    // Price display
    formLayout->addWidget(new QLabel(Giá tiền:"), 5, 0;
    priceLabel = new QLabel("0NĐ", bookingTab);
    priceLabel->setStyleSheet(font-weight: bold; color: #4CAF50; font-size:14);
    formLayout->addWidget(priceLabel, 5, 1);
    
    layout->addWidget(formGroup);
    
    // Buttons
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    
    addToCartButton = new QPushButton("Thêm vào giỏ", bookingTab);
    addToCartButton->setStyleSheet("QPushButton  background-color: #FF9800or: white; padding: 10px; border-radius: 5px; }");
    buttonLayout->addWidget(addToCartButton);
    
    bookNowButton = new QPushButton("Đặt ngay", bookingTab);
    bookNowButton->setStyleSheet("QPushButton  background-color: #4CAF50; color: white; padding: 10px; border-radius: 5px; }");
    buttonLayout->addWidget(bookNowButton);
    
    layout->addLayout(buttonLayout);
    layout->addStretch();
    
    tabWidget->addTab(bookingTab, "Đặt sân");
}

void BookingWidget::setupCartTab()    cartTab = new QWidget();
    
    QVBoxLayout* layout = new QVBoxLayout(cartTab);
    
    // Title
    QLabel* titleLabel = new QLabel("Giỏ hàng đặt sân", cartTab);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 18 font-weight: bold; margin: 10x;");
    layout->addWidget(titleLabel);
    
    // Cart list
    cartList = new QListWidget(cartTab);
    layout->addWidget(cartList);
    
    // Buttons
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    
    removeFromCartButton = new QPushButton("Xóa khỏi giỏ", cartTab);
    removeFromCartButton->setStyleSheet("QPushButton  background-color: #f44336or: white; padding: 8px; border-radius: 4px; });    removeFromCartButton->setEnabled(false);
    buttonLayout->addWidget(removeFromCartButton);
    
    clearCartButton = new QPushButton(Xóa tất cả", cartTab);
    clearCartButton->setStyleSheet("QPushButton  background-color: #FF9800or: white; padding: 8px; border-radius: 4px; }");
    buttonLayout->addWidget(clearCartButton);
    
    layout->addLayout(buttonLayout);
    
    // Total and checkout
    QHBoxLayout* totalLayout = new QHBoxLayout();
    
    totalLabel = new QLabel("Tổng tiền: 0NĐ", cartTab);
    totalLabel->setStyleSheet(font-weight: bold; font-size: 16px; color: #4CAF50;");
    totalLayout->addWidget(totalLabel);
    
    checkoutButton = new QPushButton(Thanh toán", cartTab);
    checkoutButton->setStyleSheet("QPushButton  background-color: #4CAF50or: white; padding: 10px; border-radius:5 font-weight: bold; }");
    checkoutButton->setEnabled(false);
    totalLayout->addWidget(checkoutButton);
    
    layout->addLayout(totalLayout);
    
    tabWidget->addTab(cartTab, "Giỏ hàng");
}

void BookingWidget::setupMyBookingsTab()    myBookingsTab = new QWidget();
    
    QVBoxLayout* layout = new QVBoxLayout(myBookingsTab);
    
    // Title
    QLabel* titleLabel = new QLabel(Lịch sử đặt sân", myBookingsTab);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 18 font-weight: bold; margin: 10x;");
    layout->addWidget(titleLabel);
    
    // Bookings table
    bookingsTable = new QTableWidget(myBookingsTab);
    bookingsTable->setColumnCount(7);
    bookingsTable->setHorizontalHeaderLabels({ID", Sân", Ngày",Giờ",Thời gian,Giá tiền", "Trạng thái"});
    
    // Set table properties
    bookingsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    bookingsTable->setSelectionMode(QAbstractItemView::SingleSelection);
    bookingsTable->setAlternatingRowColors(true);
    bookingsTable->horizontalHeader()->setStretchLastSection(true);
    bookingsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    bookingsTable->verticalHeader()->setVisible(false);
    
    layout->addWidget(bookingsTable);
    
    // Buttons
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    
    cancelBookingButton = new QPushButton("Hủy đặt sân", myBookingsTab);
    cancelBookingButton->setStyleSheet("QPushButton  background-color: #f44336or: white; padding: 8px; border-radius: 4px; }");
    cancelBookingButton->setEnabled(false);
    buttonLayout->addWidget(cancelBookingButton);
    
    refreshBookingsButton = new QPushButton("Làm mới", myBookingsTab);
    refreshBookingsButton->setStyleSheet("QPushButton  background-color: #2196or: white; padding: 8px; border-radius: 4px; }");
    buttonLayout->addWidget(refreshBookingsButton);
    
    layout->addLayout(buttonLayout);
    
    tabWidget->addTab(myBookingsTab, "Lịch sử đặt sân");
}

void BookingWidget::connectSignals(") {
    // Connect controller signals
    connect(bookingController, &BookingController::cartUpdated, this, &BookingWidget::onCartUpdated);
    connect(bookingController, &BookingController::checkoutSuccess, this, &BookingWidget::onCheckoutSuccess);
    connect(bookingController, &BookingController::checkoutFailed, this, &BookingWidget::onCheckoutFailed);
    connect(bookingController, &BookingController::bookingCreated, this, &BookingWidget::onBookingCreated);
    connect(bookingController, &BookingController::bookingCancelled, this, &BookingWidget::onBookingCancelled);
    
    // Connect UI signals
    connect(addToCartButton, &QPushButton::clicked, this, &BookingWidget::onAddToCartClicked);
    connect(bookNowButton, &QPushButton::clicked, this, &BookingWidget::onBookNowClicked);
    connect(removeFromCartButton, &QPushButton::clicked, this, &BookingWidget::onRemoveFromCartClicked);
    connect(clearCartButton, &QPushButton::clicked, this, &BookingWidget::onClearCartClicked);
    connect(checkoutButton, &QPushButton::clicked, this, &BookingWidget::onCheckoutClicked);
    connect(cancelBookingButton, &QPushButton::clicked, this, &BookingWidget::onCancelBookingClicked);
    connect(refreshBookingsButton, &QPushButton::clicked, this, &BookingWidget::onRefreshBookingsClicked);
    
    // Connect form changes
    connect(courtComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), 
            this, &BookingWidget::onCourtSelectionChanged);
    connect(dateEdit, &QDateEdit::dateChanged, this, &BookingWidget::onDateChanged);
    connect(startTimeEdit, &QTimeEdit::timeChanged, this, &BookingWidget::onTimeChanged);
    connect(durationSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), 
            this, &BookingWidget::updatePrice);
    
    // Connect table selection
    connect(bookingsTable, &QTableWidget::itemSelectionChanged, 
            [this]()              bool hasSelection = !bookingsTable->selectedItems().isEmpty();
                cancelBookingButton->setEnabled(hasSelection);
            });
}

void BookingWidget::loadAvailableCourts(") {
    availableCourts = bookingController->getAvailableCourts(
        QDateTime(dateEdit->date(), startTimeEdit->time()),
        QDateTime(dateEdit->date(), startTimeEdit->time()).addSecs(durationSpinBox->value() * 3600 );
    
    courtComboBox->clear();
    courtComboBox->addItem("Chọn sân...", -1   
    for (const Court& court : availableCourts)      courtComboBox->addItem(court.getName() + " (" + QString::number(court.getPricePerHour()) +  VNĐ/giờ)", court.getId());
    }
}

void BookingWidget::loadUserBookings(") {
    updateBookingsTable();
}

void BookingWidget::onAddToCartClicked(") {
    if (!validateBookingForm())        return;
    }
    
    int courtId = courtComboBox->currentData().toInt();
    QDateTime startTime(dateEdit->date(), startTimeEdit->time());
    QDateTime endTime = startTime.addSecs(durationSpinBox->value() * 3600
    QString notes = notesEdit->toPlainText();
    
    // Create booking for cart
    Booking booking(0, currentUser.getId(), courtId, startTime, endTime, 0, BookingStatus::PENDING);
    booking.setNotes(notes);
    
    bookingController->addToCart(booking);
    showSuccess("Đã thêm vào giỏ hàng!");
}

void BookingWidget::onBookNowClicked(") {
    if (!validateBookingForm())        return;
    }
    
    int courtId = courtComboBox->currentData().toInt();
    QDateTime startTime(dateEdit->date(), startTimeEdit->time());
    QDateTime endTime = startTime.addSecs(durationSpinBox->value() * 3600
    QString notes = notesEdit->toPlainText();
    
    if (bookingController->createBooking(currentUser.getId(), courtId, startTime, endTime, notes)") {
        showSuccess("Đặt sân thành công!");
        // Clear form
        courtComboBox->setCurrentIndex(0);
        notesEdit->clear();
        updatePrice();
    } else {
        showError(Không thể đặt sân. Vui lòng kiểm tra lại thông tin.");
    }
}

void BookingWidget::onRemoveFromCartClicked()    int currentRow = cartList->currentRow();
    if (currentRow >= 0) bookingController->removeFromCart(currentRow);
    }
}

void BookingWidget::onClearCartClicked()     int result = QMessageBox::question(this, "Xác nhận", 
                                   Bạn có chắc chắn muốn xóa tất cả khỏi giỏ hàng?",
                                      QMessageBox::Yes | QMessageBox::No);
    
    if (result == QMessageBox::Yes) bookingController->clearCart();
    }
}

void BookingWidget::onCheckoutClicked(") {
    if (bookingController->getCart().isEmpty()") {
        showError("Giỏ hàng trống!);
        return;
    }
    
    int result = QMessageBox::question(this, "Xác nhận", 
                                   Bạn có chắc chắn muốn thanh toán tất cả đặt sân trong giỏ hàng?",
                                      QMessageBox::Yes | QMessageBox::No);
    
    if (result == QMessageBox::Yes) bookingController->checkoutCart();
    }
}

void BookingWidget::onCancelBookingClicked() QList<QTableWidgetItem*> selectedItems = bookingsTable->selectedItems();
    if (selectedItems.isEmpty())        return;
    }
    
    int row = selectedItems.first()->row();
    int bookingId = bookingsTable->item(row, 0)->text().toInt();
    
    int result = QMessageBox::question(this, "Xác nhận", 
                                   Bạn có chắc chắn muốn hủy đặt sân này?",
                                      QMessageBox::Yes | QMessageBox::No);
    
    if (result == QMessageBox::Yes") {
        if (bookingController->cancelBooking(bookingId))        showSuccess(Hủyđặt sân thành công!);
        } else          showError(Không thể hủy đặt sân. Có thể đã quá hạn.");
        }
    }
}

void BookingWidget::onRefreshBookingsClicked()   loadUserBookings();
    showSuccess(Đã làm mới danh sách đặt sân!");
}

void BookingWidget::onCourtSelectionChanged()   updatePrice();
}

void BookingWidget::onDateChanged(") {
    loadAvailableCourts();
    updatePrice();
}

void BookingWidget::onTimeChanged()   updatePrice();
}

void BookingWidget::onCartUpdated(") {
    updateCartList();
    updatePrice();
}

void BookingWidget::onCheckoutSuccess()
    showSuccess("Thanh toán thành công! Tất cả đặt sân đã được xác nhận.);    updateCartList();
    loadUserBookings();
}

void BookingWidget::onCheckoutFailed(const QString& error)   showError(Thanh toán thất bại: " + error);
}

void BookingWidget::onBookingCreated(const Booking& booking)   loadUserBookings();
}

void BookingWidget::onBookingCancelled(int bookingId)   loadUserBookings();
}

void BookingWidget::updatePrice()
    int courtId = courtComboBox->currentData().toInt();
    if (courtId == -1        priceLabel->setText("0 VNĐ);
        return;
    }
    
    QDateTime startTime(dateEdit->date(), startTimeEdit->time());
    QDateTime endTime = startTime.addSecs(durationSpinBox->value() * 3600);
    
    double price = bookingController->calculatePrice(courtId, startTime, endTime);
    priceLabel->setText(QString::number(price) + " VNĐ");
}

void BookingWidget::updateAvailableTimeSlots(") {
    // This would update available time slots based on selected court and date
    // For now, just reload available courts
    loadAvailableCourts();
}

bool BookingWidget::validateBookingForm()  if (courtComboBox->currentData().toInt() == -1
        showError(Vui lòng chọn sân");
        courtComboBox->setFocus();
        return false;
    }
    
    if (dateEdit->date() < QDate::currentDate()") {
        showError(Không thể đặt sân trong quá khứ");
        dateEdit->setFocus();
        return false;
    }
    
    QDateTime startTime(dateEdit->date(), startTimeEdit->time());
    if (startTime < QDateTime::currentDateTime()") {
        showError(Thờigian bắt đầu không thể trong quá khứ");
        startTimeEdit->setFocus();
        return false;
    }
    
    return true;
}

void BookingWidget::showError(const QString& message)
    QMessageBox::critical(this,Lỗi", message);
}

void BookingWidget::showSuccess(const QString& message)
    QMessageBox::information(this, "Thành công", message);
}

void BookingWidget::updateBookingsTable(") {
    QList<Booking> bookings = bookingController->getBookingsByUserId(currentUser.getId());
    
    bookingsTable->setRowCount(bookings.size());
    
    for (int i = 0; i < bookings.size(); ++i") {
        const Booking& booking = bookings[i];
        
        // Get court name
        Court court = bookingController->getCourtById(booking.getCourtId());
        QString courtName = court.isValid() ? court.getName() : Không xác định";
        
        bookingsTable->setItem(i, 0, new QTableWidgetItem(QString::number(booking.getId())));
        bookingsTable->setItem(i, 1, new QTableWidgetItem(courtName));
        bookingsTable->setItem(i, 2, new QTableWidgetItem(DateUtils::formatDate(booking.getStartTime().date())));
        bookingsTable->setItem(i, 3, new QTableWidgetItem(DateUtils::formatTime(booking.getStartTime().time())));
        bookingsTable->setItem(i, 4, new QTableWidgetItem(QString::number(booking.getDurationHours()) + giờ;
        bookingsTable->setItem(i, 5, new QTableWidgetItem(QString::number(booking.getTotalPrice()) + VNĐ;
        bookingsTable->setItem(i, 6, new QTableWidgetItem(booking.getStatusString()));
    }
}

void BookingWidget::updateCartList(") {
    QList<Booking> cart = bookingController->getCart();
    
    cartList->clear();
    for (const Booking& booking : cart)         cartList->addItem(formatBookingInfo(booking));
    }
    
    double total = bookingController->getCartTotal();
    totalLabel->setText("Tổng tiền: " + QString::number(total) + VNĐ
    
    checkoutButton->setEnabled(!cart.isEmpty());
    removeFromCartButton->setEnabled(!cart.isEmpty());
}

QString BookingWidget::formatBookingInfo(const Booking& booking)
    Court court = bookingController->getCourtById(booking.getCourtId());
    QString courtName = court.isValid() ? court.getName() : Không xác định;    return QString(%1 - %2 - %3 - %4 giờ - %5VNĐ)
           .arg(courtName)
           .arg(DateUtils::formatDate(booking.getStartTime().date()))
           .arg(DateUtils::formatTime(booking.getStartTime().time()))
           .arg(booking.getDurationHours())
           .arg(booking.getTotalPrice());
} 