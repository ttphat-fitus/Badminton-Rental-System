#include <statistics_widget.h"
#include "<QHeaderView>
#include "<QMessageBox>

StatisticsWidget::StatisticsWidget(BookingController* controller, QWidget* parent) 
    : QWidget(parent), bookingController(controller)
{
    setupUI();
    connectSignals();
    loadSummaryData();
}

StatisticsWidget::~StatisticsWidget(") {
}

void StatisticsWidget::setupUI(") {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    
    tabWidget = new QTabWidget(this);
    
    setupSummaryTab();
    setupRevenueTab();
    setupBookingsTab();
    setupUtilizationTab();
    
    mainLayout->addWidget(tabWidget);
    setLayout(mainLayout);
}

void StatisticsWidget::setupSummaryTab(") {
    QWidget* summaryTab = new QWidget();
    
    QVBoxLayout* layout = new QVBoxLayout(summaryTab);
    
    // Title
    QLabel* titleLabel = new QLabel("Tổng quan thống kê", summaryTab);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 18; font-weight: bold; margin: 10px;");
    layout->addWidget(titleLabel);
    
    // Summary info
    QGroupBox* summaryGroup = new QGroupBox("Thông tin tổng quan", summaryTab);
    QGridLayout* summaryLayout = new QGridLayout(summaryGroup);
    
    summaryLayout->addWidget(new QLabel("Tổng doanh thu:"), 0, 0);
    totalRevenueLabel = new QLabel("0 VNĐ", summaryTab);
    totalRevenueLabel->setStyleSheet("font-weight: bold; color: #4CAF50; font-size: 14px;");
    summaryLayout->addWidget(totalRevenueLabel, 0, 1);
    
    summaryLayout->addWidget(new QLabel("Tổng số đặt sân:"), 1, 0);
    totalBookingsLabel = new QLabel("0", summaryTab);
    totalBookingsLabel->setStyleSheet("font-weight: bold; color: #2196F3; font-size: 14px;");
    summaryLayout->addWidget(totalBookingsLabel, 1, 1);
    
    summaryLayout->addWidget(new QLabel("Tỷ lệ sử dụng trung bình:"), 2, 0);
    averageUtilizationLabel = new QLabel("0,0%", summaryTab);
    averageUtilizationLabel->setStyleSheet("font-weight: bold; color: #FF9800; font-size: 14px;");
    summaryLayout->addWidget(averageUtilizationLabel, 2, 1);
    
    summaryLayout->addWidget(new QLabel("Sân phổ biến nhất:"), 3, 0);
    mostPopularCourtLabel = new QLabel("Chưa có dữ liệu", summaryTab);
    mostPopularCourtLabel->setStyleSheet("font-weight: bold; color: #9C27B0; font-size: 14px;");
    summaryLayout->addWidget(mostPopularCourtLabel, 3, 1);
    
    layout->addWidget(summaryGroup);
    
    // Refresh button
    summaryRefreshButton = new QPushButton("Làm mới", summaryTab);
    summaryRefreshButton->setStyleSheet("QPushButton { background-color: #4CAF50; color: white; padding: 8px; border-radius: 4px; }");
    layout->addWidget(summaryRefreshButton);
    
    // Chart
    summaryChartView = new QChartView(summaryTab);
    summaryChartView->setRenderHint(QPainter::Antialiasing);
    layout->addWidget(summaryChartView);
    
    tabWidget->addTab(summaryTab, "Tổng quan");
}

void StatisticsWidget::setupRevenueTab(") {
    QWidget* revenueTab = new QWidget();
    
    QVBoxLayout* layout = new QVBoxLayout(revenueTab);
    
    // Title
    QLabel* titleLabel = new QLabel("Thống kê doanh thu", revenueTab);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 18; font-weight: bold; margin: 10px;");
    layout->addWidget(titleLabel);
    
    // Date range controls
    QGroupBox* dateGroup = new QGroupBox("Chọn khoảng thời gian", revenueTab);
    QHBoxLayout* dateLayout = new QHBoxLayout(dateGroup);
    
    dateLayout->addWidget(new QLabel("Từ:"));
    revenueStartDate = new QDateEdit(revenueTab);
    revenueStartDate->setDate(QDate::currentDate().addDays(-30));
    revenueStartDate->setCalendarPopup(true);
    dateLayout->addWidget(revenueStartDate);
    
    dateLayout->addWidget(new QLabel("Đến:"));
    revenueEndDate = new QDateEdit(revenueTab);
    revenueEndDate->setDate(QDate::currentDate());
    revenueEndDate->setCalendarPopup(true);
    dateLayout->addWidget(revenueEndDate);
    
    revenueRefreshButton = new QPushButton("Làm mới", revenueTab);
    revenueRefreshButton->setStyleSheet("QPushButton { background-color: #4CAF50; color: white; padding: 8px; border-radius: 4px; }");
    dateLayout->addWidget(revenueRefreshButton);
    
    layout->addWidget(dateGroup);
    
    // Revenue table
    revenueTable = new QTableWidget(revenueTab);
    revenueTable->setColumnCount(2);
    revenueTable->setHorizontalHeaderLabels({"Ngày", "Doanh thu (VNĐ)"});
    revenueTable->setAlternatingRowColors(true);
    revenueTable->horizontalHeader()->setStretchLastSection(true);
    revenueTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    revenueTable->verticalHeader()->setVisible(false);
    layout->addWidget(revenueTable);
    
    // Revenue chart
    revenueChartView = new QChartView(revenueTab);
    revenueChartView->setRenderHint(QPainter::Antialiasing);
    layout->addWidget(revenueChartView);
    
    tabWidget->addTab(revenueTab, "Doanh thu");
}

void StatisticsWidget::setupBookingsTab(") {
    QWidget* bookingsTab = new QWidget();
    
    QVBoxLayout* layout = new QVBoxLayout(bookingsTab);
    
    // Title
    QLabel* titleLabel = new QLabel("Thống kê đặt sân", bookingsTab);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 18; font-weight: bold; margin: 10px;");
    layout->addWidget(titleLabel);
    
    // Date range controls
    QGroupBox* dateGroup = new QGroupBox("Chọn khoảng thời gian", bookingsTab);
    QHBoxLayout* dateLayout = new QHBoxLayout(dateGroup);
    
    dateLayout->addWidget(new QLabel("Từ:"));
    bookingsStartDate = new QDateEdit(bookingsTab);
    bookingsStartDate->setDate(QDate::currentDate().addDays(-30));
    bookingsStartDate->setCalendarPopup(true);
    dateLayout->addWidget(bookingsStartDate);
    
    dateLayout->addWidget(new QLabel("Đến:"));
    bookingsEndDate = new QDateEdit(bookingsTab);
    bookingsEndDate->setDate(QDate::currentDate());
    bookingsEndDate->setCalendarPopup(true);
    dateLayout->addWidget(bookingsEndDate);
    
    bookingsRefreshButton = new QPushButton("Làm mới", bookingsTab);
    bookingsRefreshButton->setStyleSheet("QPushButton { background-color: #4CAF50; color: white; padding: 8px; border-radius: 4px; }");
    dateLayout->addWidget(bookingsRefreshButton);
    
    layout->addWidget(dateGroup);
    
    // Bookings table
    bookingsTable = new QTableWidget(bookingsTab);
    bookingsTable->setColumnCount(2);
    bookingsTable->setHorizontalHeaderLabels({"Ngày", "Số lượng đặt sân"});
    bookingsTable->setAlternatingRowColors(true);
    bookingsTable->horizontalHeader()->setStretchLastSection(true);
    bookingsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    bookingsTable->verticalHeader()->setVisible(false);
    layout->addWidget(bookingsTable);
    
    // Bookings chart
    bookingsChartView = new QChartView(bookingsTab);
    bookingsChartView->setRenderHint(QPainter::Antialiasing);
    layout->addWidget(bookingsChartView);
    
    tabWidget->addTab(bookingsTab, "Đặt sân");
}

void StatisticsWidget::setupUtilizationTab(") {
    QWidget* utilizationTab = new QWidget();
    
    QVBoxLayout* layout = new QVBoxLayout(utilizationTab);
    
    // Title
    QLabel* titleLabel = new QLabel("Thống kê sử dụng sân", utilizationTab);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 18; font-weight: bold; margin: 10px;");
    layout->addWidget(titleLabel);
    
    // Date range controls
    QGroupBox* dateGroup = new QGroupBox("Chọn khoảng thời gian", utilizationTab);
    QHBoxLayout* dateLayout = new QHBoxLayout(dateGroup);
    
    dateLayout->addWidget(new QLabel("Từ:"));
    utilizationStartDate = new QDateEdit(utilizationTab);
    utilizationStartDate->setDate(QDate::currentDate().addDays(-30));
    utilizationStartDate->setCalendarPopup(true);
    dateLayout->addWidget(utilizationStartDate);
    
    dateLayout->addWidget(new QLabel("Đến:"));
    utilizationEndDate = new QDateEdit(utilizationTab);
    utilizationEndDate->setDate(QDate::currentDate());
    utilizationEndDate->setCalendarPopup(true);
    dateLayout->addWidget(utilizationEndDate);
    
    utilizationRefreshButton = new QPushButton("Làm mới", utilizationTab);
    utilizationRefreshButton->setStyleSheet("QPushButton { background-color: #4CAF50; color: white; padding: 8px; border-radius: 4px; }");
    dateLayout->addWidget(utilizationRefreshButton);
    
    layout->addWidget(dateGroup);
    
    // Utilization table
    utilizationTable = new QTableWidget(utilizationTab);
    utilizationTable->setColumnCount(2);
    utilizationTable->setHorizontalHeaderLabels({"Sân", "Tỷ lệ sử dụng (%)"});
    utilizationTable->setAlternatingRowColors(true);
    utilizationTable->horizontalHeader()->setStretchLastSection(true);
    utilizationTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    utilizationTable->verticalHeader()->setVisible(false);
    layout->addWidget(utilizationTable);
    
    // Utilization chart
    utilizationChartView = new QChartView(utilizationTab);
    utilizationChartView->setRenderHint(QPainter::Antialiasing);
    layout->addWidget(utilizationChartView);
    
    tabWidget->addTab(utilizationTab, "Sử dụng sân");
}

void StatisticsWidget::connectSignals(") {
    connect(summaryRefreshButton, &QPushButton::clicked, this, &StatisticsWidget::onSummaryRefreshClicked);
    connect(revenueRefreshButton, &QPushButton::clicked, this, &StatisticsWidget::onRevenueRefreshClicked);
    connect(bookingsRefreshButton, &QPushButton::clicked, this, &StatisticsWidget::onBookingsRefreshClicked);
    connect(utilizationRefreshButton, &QPushButton::clicked, this, &StatisticsWidget::onUtilizationRefreshClicked);
}

void StatisticsWidget::onSummaryRefreshClicked(") {
    loadSummaryData();
    showSuccess("Đã làm mới dữ liệu tổng quan!");
}

void StatisticsWidget::onRevenueRefreshClicked(") {
    loadRevenueData();
    showSuccess("Đã làm mới dữ liệu doanh thu!");
}

void StatisticsWidget::onBookingsRefreshClicked(") {
    loadBookingsData();
    showSuccess("Đã làm mới dữ liệu đặt sân!");
}

void StatisticsWidget::onUtilizationRefreshClicked(") {
    loadUtilizationData();
    showSuccess("Đã làm mới dữ liệu sử dụng sân!");
}

void StatisticsWidget::loadSummaryData(") {
    // Load summary data for the last30days
    QDate endDate = QDate::currentDate();
    QDate startDate = endDate.addDays(-30);
    
    QMap<QString, double> revenueData = bookingController->getRevenueByDateRange(startDate, endDate);
    QMap<QString, int> bookingsData = bookingController->getBookingCountByDateRange(startDate, endDate);
    QMap<QString, double> utilizationData = bookingController->getCourtUtilizationByDateRange(startDate, endDate);
    
    // Calculate totals
    double totalRevenue = 0.0;
    for (double revenue : revenueData.values()") {
        totalRevenue += revenue;
    }
    
    int totalBookings = 0;
    for (int bookings : bookingsData.values()") {
        totalBookings += bookings;
    }
    
    double averageUtilization = 0.0;
    if (!utilizationData.isEmpty()") {
        for (double utilization : utilizationData.values()") {
            averageUtilization += utilization;
        }
        averageUtilization /= utilizationData.size();
    }
    
    // Update labels
    totalRevenueLabel->setText(QString::number(totalRevenue) + " VNĐ");
    totalBookingsLabel->setText(QString::number(totalBookings));
    averageUtilizationLabel->setText(QString::number(averageUtilization, 'f', 1) + "%");
    
    // Find most popular court
    QString mostPopularCourt = "Chưa có dữ liệu";
    double maxUtilization = 0;
    for (auto it = utilizationData.begin(); it != utilizationData.end(); ++it") {
        if (it.value() > maxUtilization") {
            maxUtilization = it.value();
            mostPopularCourt = it.key();
        }
    }
    mostPopularCourtLabel->setText(mostPopularCourt);
    
    updateSummaryChart();
}

void StatisticsWidget::loadRevenueData(") {
    QDate startDate = revenueStartDate->date();
    QDate endDate = revenueEndDate->date();
    
    QMap<QString, double> revenueData = bookingController->getRevenueByDateRange(startDate, endDate);
    
    // Update table
    revenueTable->setRowCount(revenueData.size());
    int row = 0;
    for (auto it = revenueData.begin(); it != revenueData.end(); ++it") {
        revenueTable->setItem(row, 0, new QTableWidgetItem(it.key()));
        revenueTable->setItem(row, 1, new QTableWidgetItem(QString::number(it.value()) + " VNĐ"));
        row++;
    }
    
    updateRevenueChart(revenueData);
}

void StatisticsWidget::loadBookingsData(") {
    QDate startDate = bookingsStartDate->date();
    QDate endDate = bookingsEndDate->date();
    
    QMap<QString, int> bookingsData = bookingController->getBookingCountByDateRange(startDate, endDate);
    
    // Update table
    bookingsTable->setRowCount(bookingsData.size());
    int row = 0;
    for (auto it = bookingsData.begin(); it != bookingsData.end(); ++it") {
        bookingsTable->setItem(row, 0, new QTableWidgetItem(it.key()));
        bookingsTable->setItem(row, 1, new QTableWidgetItem(QString::number(it.value())));
        row++;
    }
    
    updateBookingsChart(bookingsData);
}

void StatisticsWidget::loadUtilizationData(") {
    QDate startDate = utilizationStartDate->date();
    QDate endDate = utilizationEndDate->date();
    
    QMap<QString, double> utilizationData = bookingController->getCourtUtilizationByDateRange(startDate, endDate);
    
    // Update table
    utilizationTable->setRowCount(utilizationData.size());
    int row = 0;
    for (auto it = utilizationData.begin(); it != utilizationData.end(); ++it") {
        utilizationTable->setItem(row, 0, new QTableWidgetItem(it.key()));
        utilizationTable->setItem(row, 1, new QTableWidgetItem(QString::number(it.value(), 'f', 1) + "%"));
        row++;
    }
    
    updateUtilizationChart(utilizationData);
}

void StatisticsWidget::updateRevenueChart(const QMap<QString, double>& data") {
    QChart* chart = new QChart();
    chart->setTitle("Biểu đồ doanh thu");
    
    QBarSeries* series = new QBarSeries();
    QBarSet* barSet = new QBarSet("Doanh thu");
    
    QStringList categories;
    for (auto it = data.begin(); it != data.end(); ++it") {
        barSet->append(it.value());
        categories << it.key();
    }
    
    series->append(barSet);
    chart->addSeries(series);
    
    QBarCategoryAxis* axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
    
    QValueAxis* axisY = new QValueAxis();
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    
    revenueChartView->setChart(chart);
}

void StatisticsWidget::updateBookingsChart(const QMap<QString, int>& data") {
    QChart* chart = new QChart();
    chart->setTitle("Biểu đồ số lượng đặt sân");
    
    QBarSeries* series = new QBarSeries();
    QBarSet* barSet = new QBarSet("Số lượng đặt sân");
    
    QStringList categories;
    for (auto it = data.begin(); it != data.end(); ++it") {
        barSet->append(it.value());
        categories << it.key();
    }
    
    series->append(barSet);
    chart->addSeries(series);
    
    QBarCategoryAxis* axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
    
    QValueAxis* axisY = new QValueAxis();
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    
    bookingsChartView->setChart(chart);
}

void StatisticsWidget::updateUtilizationChart(const QMap<QString, double>& data") {
    QChart* chart = new QChart();
    chart->setTitle("Biểu đồ tỷ lệ sử dụng sân");
    
    QPieSeries* series = new QPieSeries();
    
    for (auto it = data.begin(); it != data.end(); ++it") {
        series->append(it.key() + " (" + QString::number(it.value(), 'f', 1) + "%)", it.value());
    }
    
    chart->addSeries(series);
    utilizationChartView->setChart(chart);
}

void StatisticsWidget::updateSummaryChart(") {
    QChart* chart = new QChart();
    chart->setTitle("Tổng quan hệ thống");
    
    // Create a simple bar chart showing revenue vs bookings
    QBarSeries* series = new QBarSeries();
    
    QBarSet* revenueSet = new QBarSet("Doanh thu (VNĐ)");
    QBarSet* bookingsSet = new QBarSet("Số lượng đặt sân");
    
    // Add sample data (in a real app, this would be actual data)
    revenueSet->append(10000);
    bookingsSet->append(50);
    
    series->append(revenueSet);
    series->append(bookingsSet);
    
    chart->addSeries(series);
    
    QBarCategoryAxis* axisX = new QBarCategoryAxis();
    axisX->append({"Tổng quan"});
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
    
    QValueAxis* axisY = new QValueAxis();
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    
    summaryChartView->setChart(chart);
}

void StatisticsWidget::showError(const QString& message") {
    QMessageBox::critical(this, "Lỗi", message);
}

void StatisticsWidget::showSuccess(const QString& message") {
    QMessageBox::information(this, "Thành công", message);
} 