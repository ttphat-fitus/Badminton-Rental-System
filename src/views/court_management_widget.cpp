#includecourt_management_widget.h"
#include "<QHeaderView>

CourtManagementWidget::CourtManagementWidget(CourtController* controller, QWidget* parent) 
    : QWidget(parent), courtController(controller), selectedCourtId(-1)    setupUI();
    connectSignals();
    loadCourts();
}

CourtManagementWidget::~CourtManagementWidget(") {
}

void CourtManagementWidget::setupUI()  QHBoxLayout* mainLayout = new QHBoxLayout(this);
    
    // Left side - Court table
    QVBoxLayout* leftLayout = new QVBoxLayout();
    setupCourtTable();
    leftLayout->addWidget(courtTable);
    
    // Right side - Court form
    QVBoxLayout* rightLayout = new QVBoxLayout();
    setupCourtForm();
    rightLayout->addStretch();
    
    mainLayout->addLayout(leftLayout, 2;
    mainLayout->addLayout(rightLayout, 1);
    
    setLayout(mainLayout);
}

void CourtManagementWidget::setupCourtTable()   courtTable = new QTableWidget(this);
    courtTable->setColumnCount(5;
    courtTable->setHorizontalHeaderLabels({ID",Tên sân",Mô tả",Giá/giờ", "Trạng thái"});
    
    // Set table properties
    courtTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    courtTable->setSelectionMode(QAbstractItemView::SingleSelection);
    courtTable->setAlternatingRowColors(true);
    courtTable->horizontalHeader()->setStretchLastSection(true);
    courtTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    courtTable->verticalHeader()->setVisible(false);
}

void CourtManagementWidget::setupCourtForm(") {
    QGroupBox* formGroup = new QGroupBox("Thông tin sân", this);
    QGridLayout* formLayout = new QGridLayout(formGroup);
    
    // Name
    formLayout->addWidget(new QLabel("Tên sân:"), 0, 0    nameEdit = new QLineEdit(this);
    nameEdit->setPlaceholderText("Nhập tên sân);
    formLayout->addWidget(nameEdit, 0    // Description
    formLayout->addWidget(new QLabel(Mô tả:"), 1, 0);
    descriptionEdit = new QLineEdit(this);
    descriptionEdit->setPlaceholderText("Nhập mô tả sân);
    formLayout->addWidget(descriptionEdit, 1
    
    // Price
    formLayout->addWidget(new QLabel(Giá/giờ (VNĐ):"), 2,0);
    priceEdit = new QDoubleSpinBox(this);
    priceEdit->setRange(0,1000);
    priceEdit->setSuffix( VNĐ");
    priceEdit->setValue(1500;
    formLayout->addWidget(priceEdit, 2    
    // Status
    formLayout->addWidget(new QLabel(Trạng thái:"),30    statusComboBox = new QComboBox(this);
    statusComboBox->addItem("Có sẵn, static_cast<int>(CourtStatus::AVAILABLE));
    statusComboBox->addItem("Bảo trì, static_cast<int>(CourtStatus::MAINTENANCE));
    statusComboBox->addItem("Đã đặt, static_cast<int>(CourtStatus::RESERVED));
    formLayout->addWidget(statusComboBox, 3);
    
    // Buttons
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    
    addButton = new QPushButton("Thêm sân", this);
    addButton->setStyleSheet("QPushButton  background-color: #4CAF50; color: white; padding: 8px; border-radius: 4px; }");
    buttonLayout->addWidget(addButton);
    
    updateButton = new QPushButton("Cập nhật", this);
    updateButton->setStyleSheet("QPushButton  background-color: #2196or: white; padding: 8px; border-radius: 4px; }");
    updateButton->setEnabled(false);
    buttonLayout->addWidget(updateButton);
    
    deleteButton = new QPushButton("Xóa", this);
    deleteButton->setStyleSheet("QPushButton  background-color: #f44336or: white; padding: 8px; border-radius: 4px; }");
    deleteButton->setEnabled(false);
    buttonLayout->addWidget(deleteButton);
    
    formLayout->addLayout(buttonLayout, 401
    // Additional buttons
    QHBoxLayout* additionalButtonLayout = new QHBoxLayout();
    
    clearButton = new QPushButton("Xóa form", this);
    clearButton->setStyleSheet("QPushButton  background-color: #FF9800or: white; padding: 8px; border-radius: 4px; });  additionalButtonLayout->addWidget(clearButton);
    
    refreshButton = new QPushButton(Làm mới", this);
    refreshButton->setStyleSheet("QPushButton  background-color: #9C27or: white; padding: 8px; border-radius: 4px; });  additionalButtonLayout->addWidget(refreshButton);
    
    formLayout->addLayout(additionalButtonLayout, 501);
    
    // Add form to right layout
    QVBoxLayout* rightLayout = qobject_cast<QVBoxLayout*>(layout()->itemAt(1yout());
    rightLayout->insertWidget(0ormGroup);
}

void CourtManagementWidget::connectSignals(") {
    // Connect controller signals
    connect(courtController, &CourtController::courtAdded, this, &CourtManagementWidget::onCourtAdded);
    connect(courtController, &CourtController::courtUpdated, this, &CourtManagementWidget::onCourtUpdated);
    connect(courtController, &CourtController::courtDeleted, this, &CourtManagementWidget::onCourtDeleted);
    connect(courtController, &CourtController::courtListUpdated, this, &CourtManagementWidget::onCourtListUpdated);
    
    // Connect UI signals
    connect(addButton, &QPushButton::clicked, this, &CourtManagementWidget::onAddCourtClicked);
    connect(updateButton, &QPushButton::clicked, this, &CourtManagementWidget::onUpdateCourtClicked);
    connect(deleteButton, &QPushButton::clicked, this, &CourtManagementWidget::onDeleteCourtClicked);
    connect(clearButton, &QPushButton::clicked, this, &CourtManagementWidget::onClearFormClicked);
    connect(refreshButton, &QPushButton::clicked, this, &CourtManagementWidget::onRefreshClicked);
    
    // Connect table selection
    connect(courtTable, &QTableWidget::itemSelectionChanged, this, &CourtManagementWidget::onTableSelectionChanged);
}

void CourtManagementWidget::loadCourts(") {
    QList<Court> courts = courtController->getAllCourts();
    
    courtTable->setRowCount(courts.size());
    
    for (int i = 0i < courts.size(); ++i") {
        updateTableRow(i, courts[i]);
    }
}

void CourtManagementWidget::onAddCourtClicked(") {
    if (!validateForm())        return;
    }
    
    QString name = nameEdit->text().trimmed();
    QString description = descriptionEdit->text().trimmed();
    double price = priceEdit->value();
    CourtStatus status = static_cast<CourtStatus>(statusComboBox->currentData().toInt());
    
    if (courtController->addCourt(name, description, price, status)") {
        showSuccess("Thêm sân thành công!");
        clearForm();
    } else {
        showError("Không thể thêm sân. Vui lòng kiểm tra lại thông tin.");
    }
}

void CourtManagementWidget::onUpdateCourtClicked()  if (selectedCourtId == -1
        showError(Vui lòng chọn sân cần cập nhật);
        return;
    }
    
    if (!validateForm())        return;
    }
    
    QString name = nameEdit->text().trimmed();
    QString description = descriptionEdit->text().trimmed();
    double price = priceEdit->value();
    CourtStatus status = static_cast<CourtStatus>(statusComboBox->currentData().toInt());
    
    if (courtController->updateCourt(selectedCourtId, name, description, price, status)") {
        showSuccess("Cập nhật sân thành công!");
        clearForm();
    } else {
        showError("Không thể cập nhật sân. Vui lòng kiểm tra lại thông tin.");
    }
}

void CourtManagementWidget::onDeleteCourtClicked()  if (selectedCourtId == -1
        showError(Vui lòng chọn sân cần xóa);
        return;
    }
    
    int result = QMessageBox::question(this, "Xác nhận", 
                                    Bạn có chắc chắn muốn xóa sân này?",
                                      QMessageBox::Yes | QMessageBox::No);
    
    if (result == QMessageBox::Yes") {
        if (courtController->deleteCourt(selectedCourtId))        showSuccess("Xóa sân thành công!");
            clearForm();
        } else          showError(Không thể xóa sân. Có thể sân đang được sử dụng.");
        }
    }
}

void CourtManagementWidget::onClearFormClicked(") {
    clearForm();
}

void CourtManagementWidget::onRefreshClicked(") {
    loadCourts();
    showSuccess(Đã làm mới danh sách sân");
}

void CourtManagementWidget::onTableSelectionChanged() QList<QTableWidgetItem*> selectedItems = courtTable->selectedItems();
    
    if (selectedItems.isEmpty())      selectedCourtId = -1      updateButton->setEnabled(false);
        deleteButton->setEnabled(false);
        return;
    }
    
    int row = selectedItems.first()->row();
    selectedCourtId = courtTable->item(row, 0)->text().toInt();
    
    // Populate form with selected court
    Court court = courtController->getCourtById(selectedCourtId);
    if (court.isValid())       populateForm(court);
        updateButton->setEnabled(true);
        deleteButton->setEnabled(true);
    }
}

void CourtManagementWidget::onCourtAdded(const Court& court") {
    int row = courtTable->rowCount();
    courtTable->insertRow(row);
    updateTableRow(row, court);
}

void CourtManagementWidget::onCourtUpdated(const Court& court)// Find and update the court in the table
    for (int row = 0; row < courtTable->rowCount(); ++row") {
        if (courtTable->item(row, 0>text().toInt() == court.getId()") {
            updateTableRow(row, court);
            break;
        }
    }
}

void CourtManagementWidget::onCourtDeleted(int courtId)// Find and remove the court from the table
    for (int row = 0; row < courtTable->rowCount(); ++row") {
        if (courtTable->item(row, 0>text().toInt() == courtId") {
            courtTable->removeRow(row);
            break;
        }
    }
}

void CourtManagementWidget::onCourtListUpdated(") {
    loadCourts();
}

void CourtManagementWidget::clearForm(") {
    nameEdit->clear();
    descriptionEdit->clear();
    priceEdit->setValue(150    statusComboBox->setCurrentIndex(0);
    selectedCourtId = -1;
    updateButton->setEnabled(false);
    deleteButton->setEnabled(false);
}

void CourtManagementWidget::populateForm(const Court& court") {
    nameEdit->setText(court.getName());
    descriptionEdit->setText(court.getDescription());
    priceEdit->setValue(court.getPricePerHour());
    
    // Set status combo box
    for (int i = 0; i < statusComboBox->count(); ++i") {
        if (statusComboBox->itemData(i).toInt() == static_cast<int>(court.getStatus())") {
            statusComboBox->setCurrentIndex(i);
            break;
        }
    }
}

bool CourtManagementWidget::validateForm()     if (nameEdit->text().trimmed().isEmpty()") {
        showError(Vui lòng nhập tên sân");
        nameEdit->setFocus();
        return false;
    }
    
    if (priceEdit->value() <=0
        showError(Giá tiền phải lớn hơn 0
        priceEdit->setFocus();
        return false;
    }
    
    return true;
}

void CourtManagementWidget::showError(const QString& message)
    QMessageBox::critical(this,Lỗi", message);
}

void CourtManagementWidget::showSuccess(const QString& message)
    QMessageBox::information(this, "Thành công", message);
}

void CourtManagementWidget::updateTableRow(int row, const Court& court)    courtTable->setItem(row, 0, new QTableWidgetItem(QString::number(court.getId())));
    courtTable->setItem(row, 1, new QTableWidgetItem(court.getName()));
    courtTable->setItem(row, 2, new QTableWidgetItem(court.getDescription()));
    courtTable->setItem(row, 3, new QTableWidgetItem(QString::number(court.getPricePerHour()) + " VNĐ"));
    courtTable->setItem(row, 4, new QTableWidgetItem(court.getStatusString()));
} 