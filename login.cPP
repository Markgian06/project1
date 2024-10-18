#include <iostream>
#include <mysql/mysql.h>
#include <string>                                                                                                                                                                                                 

using namespace std;

// Database connection 
const char* host = "localhost";   
const char* user = "root";    
const char* password = "IamMarkGianAbejero06Y";  
const char* db = "my_database";   

MYSQL* connectDB() {
    MYSQL* conn;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, host, user, password, db, 3306, NULL, 0);

    if (conn) {
        cout << "Connected to MySQL database!" << endl;
    } else {
        cerr << "Failed to connect: " << mysql_error(conn) << endl;
    }
    return conn;
}

bool loginUser() {
    MYSQL* conn = connectDB();
    MYSQL_ROW row;
    MYSQL_RES* res;

    if (!conn) {
        return false;
    }

    string email, userPassword;  
    cout << "Enter Email: ";
    cin >> email;
    cout << "Enter Password: ";
    cin >> userPassword;

    string query = "SELECT * FROM users WHERE email='" + email + "'";
    const char* q = query.c_str();

    if (mysql_query(conn, q)) {
        cerr << "Query execution failed: " << mysql_error(conn) << endl;
        return false;
    }
    res = mysql_store_result(conn);
    int numRows = mysql_num_rows(res);

    if (numRows == 0) {
        cout << "No user found with that email!" << endl;
        mysql_free_result(res);
        return false;
    } else {
        row = mysql_fetch_row(res);
        string storedPassword = row[4];  
        
        if (storedPassword == userPassword) {
            cout << "Login successful!" << endl;
            mysql_free_result(res); 
            return true;
        } else {
            cout << "Incorrect password!" << endl;
            mysql_free_result(res); 
            return false;
        }
    }

    mysql_close(conn);  
}

int main() {
    if (loginUser()) {
        // Additional 
    }
    return 0;
}
