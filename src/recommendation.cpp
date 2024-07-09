#include "recommendation.h"
#include <iostream>

std::vector<Book> loadBooks(sql::Connection *conn) {
    std::vector<Book> books;
    try {
        std::unique_ptr<sql::Statement> stmt(conn->createStatement());
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT id, title, author, genre, rating FROM books"));

        while (res->next()) {
            books.push_back({res->getInt("id"), res->getString("title"), res->getString("author"), res->getString("genre"), res->getDouble("rating")});
        }
    } catch (sql::SQLException &e) {
        std::cerr << "Error loading books: " << e.what() << std::endl;
    }
    return books;
}

std::vector<Book> recommendBooks(const std::vector<Book> &books, const std::string &genre, const std::string &author) {
    std::vector<Book> recommendations;
    for (const auto &book : books) {
        if (book.genre == genre || book.author == author) {
            recommendations.push_back(book);
        }
    }
    return recommendations;
}
