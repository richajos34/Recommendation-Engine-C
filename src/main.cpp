#include <iostream>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include "recommendation.h"

void getUserPreferences(std::string &genre, std::string &author) {
    std::cout << "Enter your favorite genre: ";
    std::getline(std::cin, genre);
    std::cout << "Enter your favorite author: ";
    std::getline(std::cin, author);
}

int main() {
    try {
        sql::mysql::MySQL_Driver *driver = sql::mysql::get_mysql_driver_instance();
        std::unique_ptr<sql::Connection> conn(driver->connect("tcp://127.0.0.1:3306", "root", "hotdog"));
        conn->setSchema("book_recommendation");

        std::vector<Book> books = loadBooks(conn.get());

        std::string favoriteGenre, favoriteAuthor;
        getUserPreferences(favoriteGenre, favoriteAuthor);

        std::vector<Book> recommendations = recommendBooks(books, favoriteGenre, favoriteAuthor);

        std::cout << "Recommended books:\n";
        for (const auto &book : recommendations) {
            std::cout << "Title: " << book.title << ", Author: " << book.author << ", Genre: " << book.genre << ", Rating: " << book.rating << "\n";
        }
    } catch (sql::SQLException &e) {
        std::cerr << "SQL error: " << e.what() << std::endl;
    }

    return 0;
}
