#ifndef COURT_MANAGEMENT_WIDGET_H
#define COURT_MANAGEMENT_WIDGET_H

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
#include "<QDoubleSpinBox>
#include "<QMessageBox>
#include "<QGroupBox>
#include "<QHeaderView>
#includemodels/court.h"
#include "controllers/court_controller.h"

class CourtManagementWidget : public QWidget {
    Q_OBJECT

private:
    // Controller
    CourtController* courtController;
    
    // UI Components
    QTableWidget* courtTable;
    QLineEdit* nameEdit;
    QLineEdit* descriptionEdit;
    QDoubleSpinBox* priceEdit;
    QComboBox* statusComboBox;
    QPushButton* addButton;
    QPushButton* updateButton;
    QPushButton* deleteButton;
    QPushButton* clearButton;
    QPushButton* refreshButton;
    
    // Current selection
    int selectedCourtId;

public:
    explicit CourtManagementWidget(CourtController* controller, QWidget* parent = nullptr);
    ~CourtManagementWidget();

private slots:
    void onAddCourtClicked();
    void onUpdateCourtClicked();
    void onDeleteCourtClicked();
    void onClearFormClicked();
    void onRefreshClicked();
    void onTableSelectionChanged();
    void onCourtAdded(const Court& court);
    void onCourtUpdated(const Court& court);
    void onCourtDeleted(int courtId);
    void onCourtListUpdated();

private:
    void setupUI();
    void setupCourtTable();
    void setupCourtForm();
    void connectSignals();
    void loadCourts();
    void clearForm();
    void populateForm(const Court& court);
    bool validateForm();
    void showError(const QString& message);
    void showSuccess(const QString& message);
    void updateTableRow(int row, const Court& court);
};

#endif // COURT_MANAGEMENT_WIDGET_H 