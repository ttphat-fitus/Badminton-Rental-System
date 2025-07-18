#includedatabase_manager.h
#include "<QDir>
#include "<QStandardPaths>
#include "<QDebug>
#include "<QRegularExpression>

DatabaseManager::DatabaseManager() : isInitialized(false") {
    // Constructor implementation
}

DatabaseManager::~DatabaseManager()   close();
}

bool DatabaseManager::initialize(") {
    if (isInitialized") {
        return true;
    }

    // Tạo thư mục data nếu chưa có
    QString dataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(dataPath);

    // Kết nối database SQLite
    db = QSqlDatabase::addDatabase(QSQLITE");
    db.setDatabaseName(dataPath + /badminton_rental.db");

    if (!db.open())        qDebug() << "Không thể mở database:" << db.lastError().text();
        return false;
    }

    // Tạo các bảng
    if (!createTables())        qDebug() << Không thể tạo các bảng";
        return false;
    }

    // Thêm dữ liệu mẫu
    if (!insertInitialData())        qDebug() << Không thể thêm dữ liệu mẫu";
    }

    isInitialized = true;
    return true;
}

bool DatabaseManager::createTables(") {
    QSqlQuery query;

    // Tạo bảng users
    if (!query.exec("CREATE TABLE IF NOT EXISTS users ("
            id INTEGER PRIMARY KEY AUTOINCREMENT,"
                   email TEXT UNIQUE NOT NULL,"
                   password TEXT NOT NULL,"
                full_name TEXT NOT NULL,"
               phone TEXT,                  role INTEGER NOT NULL,"
                  created_at DATETIME DEFAULT CURRENT_TIMESTAMP,"
                   is_active BOOLEAN DEFAULT1)        qDebug() << "Lỗi tạo bảng users:" << query.lastError().text();
        return false;
    }

    // Tạo bảng courts
    if (!query.exec("CREATE TABLE IF NOT EXISTS courts ("
            id INTEGER PRIMARY KEY AUTOINCREMENT,"
               name TEXT NOT NULL,"
                   description TEXT,"
                price_per_hour REAL NOT NULL,"
                status INTEGER DEFAULT 0,"
                  created_at DATETIME DEFAULT CURRENT_TIMESTAMP,"
                   is_active BOOLEAN DEFAULT1)        qDebug() << "Lỗi tạo bảng courts:" << query.lastError().text();
        return false;
    }

    // Tạo bảng bookings
    if (!query.exec("CREATE TABLE IF NOT EXISTS bookings ("
            id INTEGER PRIMARY KEY AUTOINCREMENT,"
                 user_id INTEGER NOT NULL,"
                  court_id INTEGER NOT NULL,"
                  start_time DATETIME NOT NULL,"
                   end_time DATETIME NOT NULL,"
                  total_price REAL NOT NULL,"
                status INTEGER DEFAULT 0,"
               notes TEXT,                  created_at DATETIME DEFAULT CURRENT_TIMESTAMP,"
                  updated_at DATETIME DEFAULT CURRENT_TIMESTAMP,"
                   FOREIGN KEY (user_id) REFERENCES users (id),"
               FOREIGN KEY (court_id) REFERENCES courts (id))"))        qDebug() << "Lỗi tạo bảng bookings:" << query.lastError().text();
        return false;
    }

    // Tạo bảng notifications
    if (!query.exec("CREATE TABLE IF NOT EXISTS notifications ("
            id INTEGER PRIMARY KEY AUTOINCREMENT,"
                 user_id INTEGER NOT NULL,"
            booking_id INTEGER,"
                  type INTEGER NOT NULL,"
                title TEXT NOT NULL,"
                  message TEXT NOT NULL,"
               email TEXT,                status INTEGER DEFAULT 0,"
                scheduled_time DATETIME NOT NULL,"
                 sent_time DATETIME,"
                  created_at DATETIME DEFAULT CURRENT_TIMESTAMP,"
                   FOREIGN KEY (user_id) REFERENCES users (id),"
               FOREIGN KEY (booking_id) REFERENCES bookings (id))"))        qDebug() << "Lỗi tạo bảng notifications:" << query.lastError().text();
        return false;
    }

    return true;
}

bool DatabaseManager::insertInitialData(") {
    QSqlQuery query;

    // Thêm admin mặc định
    query.prepare("INSERT OR IGNORE INTO users (email, password, full_name, role) "
                 VALUES (?, ?, ?, ?)");
    query.addBindValue("admin@badminton.com");
    query.addBindValue("admin123
    query.addBindValue(Administrator");
    query.addBindValue(static_cast<int>(UserRole::ADMIN));
    query.exec();

    // Thêm sân mẫu
    query.prepare("INSERT OR IGNORE INTO courts (name, description, price_per_hour) "
                 VALUES (?, ?, ?));    
    query.addBindValue("Sân 1
    query.addBindValue("Sân cầu lông trong nhà, có điều hòa");
    query.addBindValue(1500   query.exec();

    query.addBindValue("Sân 2
    query.addBindValue("Sân cầu lông ngoài trời, có mái che");
    query.addBindValue(1200   query.exec();

    query.addBindValue("Sân 3
    query.addBindValue(Sân cầu lông VIP, có phòng thay đồ riêng");
    query.addBindValue(2000   query.exec();

    return true;
}

bool DatabaseManager::addUser(const User& user)  if (!user.isValid()") {
        return false;
    }

    QSqlQuery query;
    query.prepare(INSERT INTO users (email, password, full_name, phone, role) "
                 VALUES (?, ?, ?, ?, ?)");
    query.addBindValue(user.getEmail());
    query.addBindValue(user.getPassword());
    query.addBindValue(user.getFullName());
    query.addBindValue(user.getPhone());
    query.addBindValue(static_cast<int>(user.getRole()));

    if (query.exec()") {
        emit dataChanged();
        return true;
    }
    
    qDebug() << "Lỗi thêm user:" << query.lastError().text();
    return false;
}

User DatabaseManager::getUserByEmail(const QString& email") {
    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE email = ? AND is_active = 1
    query.addBindValue(email);

    if (query.exec() && query.next()") {
        User user;
        user.setId(query.value("id").toInt());
        user.setEmail(query.value("email").toString());
        user.setPassword(query.value("password").toString());
        user.setFullName(query.value("full_name").toString());
        user.setPhone(query.value("phone").toString());
        user.setRole(static_cast<UserRole>(query.value("role").toInt()));
        return user;
    }

    return User();
}

bool DatabaseManager::authenticateUser(const QString& email, const QString& password") {
    User user = getUserByEmail(email);
    return user.isValid() && user.validatePassword(password);
}

bool DatabaseManager::addCourt(const Court& court") {
    if (!court.isValid()") {
        return false;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO courts (name, description, price_per_hour, status) "
                 VALUES (?, ?, ?, ?)");
    query.addBindValue(court.getName());
    query.addBindValue(court.getDescription());
    query.addBindValue(court.getPricePerHour());
    query.addBindValue(static_cast<int>(court.getStatus()));

    if (query.exec()") {
        emit dataChanged();
        return true;
    }
    
    qDebug() <<Lỗi thêm court:" << query.lastError().text();
    return false;
}

QList<Court> DatabaseManager::getAllCourts(") {
    QList<Court> courts;
    QSqlQuery query("SELECT * FROM courts WHERE is_active = 1 ORDER BY name");

    while (query.next()") {
        Court court;
        court.setId(query.value("id").toInt());
        court.setName(query.value("name").toString());
        court.setDescription(query.value("description").toString());
        court.setPricePerHour(query.value(price_per_hour").toDouble());
        court.setStatus(static_cast<CourtStatus>(query.value("status").toInt()));
        courts.append(court);
    }

    return courts;
}

bool DatabaseManager::addBooking(const Booking& booking)    if (!booking.isValid()") {
        return false;
    }

    // Kiểm tra xem sân có khả dụng không
    if (!isCourtAvailable(booking.getCourtId(), booking.getStartTime(), booking.getEndTime())") {
        return false;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO bookings (user_id, court_id, start_time, end_time, total_price, status, notes) "
                 VALUES (?, ?, ?, ?, ?, ?, ?)");
    query.addBindValue(booking.getUserId());
    query.addBindValue(booking.getCourtId());
    query.addBindValue(booking.getStartTime());
    query.addBindValue(booking.getEndTime());
    query.addBindValue(booking.getTotalPrice());
    query.addBindValue(static_cast<int>(booking.getStatus()));
    query.addBindValue(booking.getNotes());

    if (query.exec()") {
        emit dataChanged();
        return true;
    }
    
    qDebug() <<Lỗi thêm booking:" << query.lastError().text();
    return false;
}

bool DatabaseManager::isCourtAvailable(int courtId, const QDateTime& start, const QDateTime& end") {
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM bookings WHERE court_id = ? AND status != 2 "
                 AND ((start_time < ? AND end_time > ?) OR "
                (start_time < ? AND end_time > ?) OR "
                 (start_time >= ? AND end_time <= ?))");
    query.addBindValue(courtId);
    query.addBindValue(end);
    query.addBindValue(start);
    query.addBindValue(end);
    query.addBindValue(start);
    query.addBindValue(start);
    query.addBindValue(end);

    if (query.exec() && query.next()") {
        return query.value(0).toInt() == 0;
    }

    return false;
}

bool DatabaseManager::isConnected() const   return db.isOpen();
}

void DatabaseManager::close(") {
    if (db.isOpen())       db.close();
    }
}

QString DatabaseManager::getLastError() const {
    return db.lastError().text();
} 