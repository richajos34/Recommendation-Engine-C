#ifndef RECOMMENDATION_H
#define RECOMMENDATION_H

#include <vector>
#include <string>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

struct Book {
    int id;
    std::string title;
    std::string author;
    std::string genre;
    double rating;
};

std::vector<Book> loadBooks(sql::Connection *conn);
std::vector<Book> recommendBooks(const std::vector<Book> &books, const std::string &genre, const std::string &author);

#endif // RECOMMENDATION_H
