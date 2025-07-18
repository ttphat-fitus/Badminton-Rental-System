#include <QApplication>
#include <QMainWindow>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    // Create a simple main window
    QMainWindow window;
    window.setWindowTitle("Badminton Rental System");
    window.resize(800, 600);
    
    // Create central widget
    QWidget *centralWidget = new QWidget(&window);
    window.setCentralWidget(centralWidget);
    
    // Create layout
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    
    // Add welcome message
    QLabel *welcomeLabel = new QLabel("Welcome to Badminton Rental System", centralWidget);
    welcomeLabel->setStyleSheet("font-size: 24px; font-weight: bold; margin: 20px;");
    welcomeLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(welcomeLabel);
    
    // Add status message
    QLabel *statusLabel = new QLabel("System is running successfully!", centralWidget);
    statusLabel->setStyleSheet("font-size: 16px; color: green; margin: 10px;");
    statusLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(statusLabel);
    
    // Add features list
    QLabel *featuresLabel = new QLabel(
        "Features:\n"
        "• User Management (Admin/Customer)\n"
        "• Court Management\n"
        "• Booking System\n"
        "• Email Notifications\n"
        "• Statistics & Reports\n"
        "• Real-time Availability",
        centralWidget
    );
    featuresLabel->setStyleSheet("font-size: 14px; margin: 20px; padding: 20px; border: 1px solid #ccc; border-radius: 5px;");
    layout->addWidget(featuresLabel);
    
    // Show window
    window.show();
    
    // Show information dialog
    QMessageBox::information(&window, "Project Info", 
        "Badminton Rental System\n\n"
        "This is a Qt6-based desktop application for managing badminton court rentals.\n"
        "Built with C++17, Qt6, and SQLite database.\n\n"
        "Architecture: MVC Pattern with Singleton and Observer patterns\n"
        "Author: Phát - 2025");
    
    return app.exec();
}
