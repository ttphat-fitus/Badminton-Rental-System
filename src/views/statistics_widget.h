#ifndef STATISTICS_WIDGET_H
#define STATISTICS_WIDGET_H

#include "<QWidget>
#include "<QVBoxLayout>
#include "<QHBoxLayout>
#include "<QGridLayout>
#include "<QLabel>
#include "<QPushButton>
#include "<QTableWidget>
#include "<QComboBox>
#include "<QDateEdit>
#include "<QGroupBox>
#include "<QHeaderView>
#include "<QChart>
#include "<QChartView>
#include "<QBarSeries>
#include "<QBarSet>
#include "<QBarCategoryAxis>
#include "<QValueAxis>
#include "<QPieSeries>
#include <controllers/booking_controller.h"

QT_CHARTS_USE_NAMESPACE

class StatisticsWidget : public QWidget {
    Q_OBJECT

private:
    // Controller
    BookingController* bookingController;
    
    // UI Components
    QTabWidget* tabWidget;
    
    // Revenue tab
    QWidget* revenueTab;
    QDateEdit* revenueStartDate;
    QDateEdit* revenueEndDate;
    QPushButton* revenueRefreshButton;
    QTableWidget* revenueTable;
    QChartView* revenueChartView;
    
    // Bookings tab
    QWidget* bookingsTab;
    QDateEdit* bookingsStartDate;
    QDateEdit* bookingsEndDate;
    QPushButton* bookingsRefreshButton;
    QTableWidget* bookingsTable;
    QChartView* bookingsChartView;
    
    // Court utilization tab
    QWidget* utilizationTab;
    QDateEdit* utilizationStartDate;
    QDateEdit* utilizationEndDate;
    QPushButton* utilizationRefreshButton;
    QTableWidget* utilizationTable;
    QChartView* utilizationChartView;
    
    // Summary tab
    QWidget* summaryTab;
    QLabel* totalRevenueLabel;
    QLabel* totalBookingsLabel;
    QLabel* averageUtilizationLabel;
    QLabel* mostPopularCourtLabel;
    QPushButton* summaryRefreshButton;
    QChartView* summaryChartView;

public:
    explicit StatisticsWidget(BookingController* controller, QWidget* parent = nullptr);
    ~StatisticsWidget();

private slots:
    void onRevenueRefreshClicked();
    void onBookingsRefreshClicked();
    void onUtilizationRefreshClicked();
    void onSummaryRefreshClicked();

private:
    void setupUI();
    void setupRevenueTab();
    void setupBookingsTab();
    void setupUtilizationTab();
    void setupSummaryTab();
    void connectSignals();
    void loadRevenueData();
    void loadBookingsData();
    void loadUtilizationData();
    void loadSummaryData();
    void updateRevenueChart(const QMap<QString, double>& data);
    void updateBookingsChart(const QMap<QString, int>& data);
    void updateUtilizationChart(const QMap<QString, double>& data);
    void updateSummaryChart();
    void showError(const QString& message);
    void showSuccess(const QString& message);
};

#endif // STATISTICS_WIDGET_H 