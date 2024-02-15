//
// Created by Jeffry - 100698915 on 2024-02-12.
//
#include <utility>

#include "CommonIncludes.h"

class Product {
    std::string delimiter;
public:
    explicit Product(std::string  del) : delimiter(std::move(del)) {}

    /// \summary Separates the product data line into parts of ID, NAME, PRICE, CATEGORY.
    /// \param data A string a data that is read directly from a file.
    /// \return An vector array of strings where each index is the product data.
    std::vector<std::string> ProductData(const std::string &data) const {
        size_t currentPos = 0;
        size_t delimiterPos = 0;

        std::vector<std::string> product;

        while ((currentPos = data.find(delimiter, delimiterPos)) != std::string::npos) {
            product.push_back(data.substr(delimiterPos, currentPos - delimiterPos));
            delimiterPos = currentPos + delimiter.length();
        }

        // Gets the last data of the line
        product.push_back(data.substr(delimiterPos));

        return product;
    }
};