//
// Created by Jeffry - 100698915 on 2024-02-08.
//

#include "CommonIncludes.h"
#include "QuickSort.cpp"

#include <fstream>
#include <filesystem>
#include <algorithm>
#include <sstream>
#include <iomanip>

class DataManager {
    std::vector<std::string> dataArray;
    std::string delimiter = ", ";
    Product productData;
    QuickSorter sorter;

    std::string GetID(const std::string& data) const;
public:
    DataManager();
    Product Product() const {return  productData; }
    void Display() const;
    std::string Search(const std::string& ID, bool sendMessage = true) const;
    std::string Search(const int& ID, bool sendMessage = true) const;
    int SearchI(const std::string& ID, bool sendMessage = true) const;
    int SearchI(const int& ID, bool sendMessage = true) const;
    void Insert(const std::string& newProduct);
    void Insert(const int& ID, const std::string& name, const float& price, const std::string& category);
    void Delete(const std::string& ID);
    void Update(const std::string& ID, const std::string& newData);
    void Update(const int& ID, const std::string& newName = "", const float& newPrice = -1.0, const std::string& newCategory = "");
    void Sort(int section, bool ascending = true);
};

    DataManager::DataManager() : productData(delimiter) {
        std::filesystem::path filePath = std::filesystem::current_path().parent_path() / "product_data.txt";

        std::ifstream file;
        file.open(filePath);

        if (!file.is_open()) {
            std::cerr << "Unable to open the file" << std::endl;
            return;
        }

        std::string line;
        while (!file.eof()) {
            std::getline(file, line);
            dataArray.push_back(line);
        }

        file.close();
    }

    /// \summary Displays the product.
    void DataManager::Display() const
    {
        int i = 1;
        for(const std::string& data : dataArray) {
            std::cout << i << ". " << data << std::endl;
            i++;
        }
    }

    /// \summary Gets the ID of the product.
    /// \param data A string of the entire product data.
    /// \return The product ID as a string.
    std::string DataManager::GetID(const std::string& data) const {
    return productData.ProductData(data).at(0);
    }

    /// \summary Finds a product by ID.
    /// \param ID A string representing the ID of the product you want to find.
    /// \param sendMessage (Optional; Default is True) A boolean for whether or not to output any message for not finding the product.
    /// \return A string for the product info.
    std::string DataManager::Search(const std::string &ID, bool sendMessage) const {
        for (std::string product : dataArray) {
            if (GetID(product) == ID) {
                return product;
            }
        }

        if (sendMessage) {
            std::cout << "Product with ID: " << ID << " could not be found." << std::endl;
        }
        return "";
    }

    /// Finds a product by ID.
    /// \param ID A number representing the ID of the product you want to find
    /// \param sendMessage (Optional; Default is True) A boolean for whether or not to output any message for not finding the product.
    /// \return A string for the product info.
    std::string DataManager::Search(const int &ID, bool sendMessage) const {
        /*for (std::string product : dataArray) {
            if (GetID(product) == std::to_string(ID)) {
                return product;
            }
        }

        if (sendMessage == true) {
            std::cout << "Product with ID: " << ID << " could not be found." << std::endl;
        }
        return "";*/

        return Search(std::to_string(ID), sendMessage); // Yea, I'm lazy.
    }

    ///
    /// \param ID
    /// \param sendMessage
    /// \return
    int DataManager::SearchI(const std::string &ID, bool sendMessage) const {
        auto it = std::find(dataArray.begin(), dataArray.end(), Search(ID));

        if (it != dataArray.end()) {
            int index = std::distance(dataArray.begin(), it);
            return index;
        }

        if (sendMessage) {
            std::cout << "Product with ID: " << ID << " could not be found." << std::endl;
        }
        return -1;
    }

    ///
    /// \param ID
    /// \param sendMessage
    /// \return
    int DataManager::SearchI(const int &ID, bool sendMessage) const {
        /*auto it = std::find(dataArray.begin(), dataArray.end(), Search(ID));

        if (it != dataArray.end()) {
            int index = std::distance(dataArray.begin(), it);
            return index;
        }

        if (sendMessage) {
            std::cout << "Product with ID: " << ID << " could not be found." << std::endl;
        }
        return -1;*/

        return SearchI(std::to_string(ID));
    }

    /// \summary Adds new products into the vector array.
    /// \param newData A string that holds all the product info.
    void DataManager::Insert(const std::string& newProduct) {
        std::string id = GetID(newProduct);
        std::string product = Search(id, false);

        if (!product.empty()) {
            std::cout << "Product with ID: " << id << " is already in the array." << std::endl;
            return; // DO NOT REPEAT DATA (IDs are unique)
        }

        dataArray.push_back(newProduct);
        std::cout << "Product ID: " << GetID(dataArray.back()) << " has been successfully added." << std::endl;
    }

    /// \summary Adds new products into the vector array (Overloaded).
    /// \param ID A string of the product ID.
    /// \param name A string of the product name.
    /// \param price A string of the product price.
    /// \param category A string of the product category.
    void DataManager::Insert(const int &ID, const std::string &name, const float &price, const std::string &category) {
        std::string product = Search(std::to_string(ID), false);

        if (!product.empty()) {
            std::cout << "Product with ID: " << ID << " is already in the array." << std::endl;
            return; // DO NOT REPEAT DATA (IDs are unique)
        }

        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2) << price;

        // Combine the data into a single line like each line in the product_data.txt file
        dataArray.push_back(std::to_string(ID) + delimiter + name + delimiter + oss.str() + delimiter + category);
        std::cout << "Product with ID: " << ID << " has been successfully added." << std::endl;
    }

    /// \summary Deletes the product by ID.
    /// \param ID ID of the product to be deleted.
    void DataManager::Delete(const std::string& ID) {
        std::string product = Search(ID);

        if (product.empty()) {
            return;
        }

        auto index = std::find(dataArray.begin(), dataArray.end(),product);

        dataArray.erase(index);
        std::cout << "Product with ID: " << ID << " has been successfully deleted." << std::endl;

    }

    /// Changes the product info without changing the ID.
    /// \param ID A string representing the ID of the product to change.
    /// \param newData The new data of the product.
    void DataManager::Update(const std::string& ID, const std::string& newData) {
        if (ID != GetID(newData)) {
            std::cerr << std::endl << "The product ID of the new data does not match the ID you want to find." << std::endl;
            exit(-1);
        }

        std::string product = Search(ID);
        if (product.empty()) {
            return;
        }

        auto index = std::find(dataArray.begin(), dataArray.end(), product);
        std::replace(dataArray.begin(), dataArray.end(), product, newData);
    }

    /// \summary Changes the product info without changing the ID.
    /// \param ID A number representing the ID of the product to change.
    /// \param newName The new name of the product.
    /// \param newPrice The new price of the product as a float.
    /// \param newCategory The new category of the product.
    void DataManager::Update(const int& ID, const std::string& newName, const float& newPrice, const std::string& newCategory) {
        std::string product = Search(std::to_string(ID));
        if (product.empty() && newName.empty() && newPrice <= 0.0 && newCategory.empty()) {
            return;
        }

        vector<string> productInfo = productData.ProductData(product);

        if (!newName.empty()) {
            productInfo.at(1) = newName;
        }

        if (newPrice >= 0.0) {
            productInfo.at(2) = to_string(newPrice);
        }

        if (!newCategory.empty()) {
            productInfo.at(3) = newCategory;
        }

        string newData = productInfo.at(0) + delimiter
                       + productInfo.at(1) + delimiter
                       + productInfo.at(2) + delimiter
                       + productInfo.at(3);


        auto index = std::find(dataArray.begin(), dataArray.end(), product);
        std::replace(dataArray.begin(), dataArray.end(), product, newData);
    }

    /// \summary Sorts the array using quick sort
    /// \param section The data section you want to sort by. 0 = ID, 1 = NAME, 2 = PRICE, 3 = CATEGORY.
    /// \param ascending Determines whether to sort ascending or descending. Default mode is Ascending.
    void DataManager::Sort(int section, bool ascending)
    {
        if (ascending) {
            sorter.SortAscending(dataArray, section);
        }
        else {
            sorter.SortDescending(dataArray, section);
        }

        //Display();
    }

#include "Timer.cpp"

using namespace std;
int main() {
    DataManager dataManager;

    cout << "Product data Loaded. Displaying product data:" << endl;
    cout << "--------------------------------------------------------" << endl;
    dataManager.Display();

    string dupProduct = "22806, Smartwatch VVFNT, 203.55, Electronics"; // #16
    cout << endl << "Inserting duplicated product: " << dupProduct<< "." << endl;
    cout << "--------------------------------------------------------" << endl;
    dataManager.Insert(dupProduct);
    //dataManager.Display();

    string newProduct = "42069, Sir Poops-A-Lot SHTFX, 69.69, Electronics";
    cout << endl << "Inserting new product: " << newProduct << "." << endl;
    cout << "--------------------------------------------------------" << endl;
    dataManager.Insert(newProduct);
    dataManager.Display();

    int newProdID = 91101;
    string newProdName = "RC Plane WTCUSA";
    float newProdPrice = 175.93;
    string newProdCategory = "Electronics";
    cout << endl << "Inserting new product: " << newProdID << ", " + newProdName + ", " << newProdPrice << ", " + newProdCategory << "." << endl;
    cout << "--------------------------------------------------------" << endl;
    dataManager.Insert(newProdID, newProdName, newProdPrice,newProdCategory);
    dataManager.Display();

    string poopAlotChanges = "42069, Sir Poops-A-Lot SHTFX, 69.69, Toys";
    cout << endl << "Updating " << dataManager.Product().ProductData(newProduct).at(1) << "." << endl;
    cout << "--------------------------------------------------------" << endl;
    dataManager.Update(dataManager.Product().ProductData(newProduct).at(0), poopAlotChanges);
    dataManager.Display();

    string rcPlaneCategory = "Toys";
    cout << endl << "Updating " << newProdName << "." << endl;
    cout << "--------------------------------------------------------" << endl;
    dataManager.Update(newProdID, "", -1.0, rcPlaneCategory);
    dataManager.Display();

    cout << endl << "Deleting " << dataManager.Product().ProductData(newProduct).at(1) << "." << endl;
    cout << "--------------------------------------------------------" << endl;
    dataManager.Delete(dataManager.Product().ProductData(newProduct).front());
    dataManager.Display();

    cout << endl << "Searching deleted product: " << dataManager.Product().ProductData(newProduct).at(1) << "." << endl;
    cout << "--------------------------------------------------------" << endl;
    dataManager.Search(dataManager.Product().ProductData(newProduct).front());

    cout << endl << "Searching for product ID: 96314." << endl;
    cout << "--------------------------------------------------------" << endl;
    cout << "Product #" << dataManager.SearchI(96314) << ": " << dataManager.Search(96314) << endl;

    Timer timer;

    cout << endl << "Sorting Ascending Prices." << endl;
    cout << "--------------------------------------------------------" << endl;
    auto start = chrono::high_resolution_clock::now();
    dataManager.Sort(2);
    auto end = chrono::high_resolution_clock::now();

    auto unsortedTime = chrono::duration_cast<chrono::microseconds>(end-start);
    cout << "The quick sort when sorting an UNSORTED array took [";
    timer.DisplayTime(unsortedTime);
    cout << "] microseconds. " << endl;

    cout << endl << "Sorting Ascending Prices Again." << endl;
    cout << "--------------------------------------------------------" << endl;
    start = chrono::high_resolution_clock::now();
    dataManager.Sort(2);
    end = chrono::high_resolution_clock::now();

    auto sortedTime = chrono::duration_cast<chrono::microseconds>(end-start);
    auto sortedVsUnsorted = sortedTime.count() - unsortedTime.count();
    cout << "The quick sort when sorting a SORTED array took [";
    timer.DisplayTime(sortedTime);
    cout << "] microseconds. Which is [" << sortedVsUnsorted << "] microseconds longer than unsorted." << endl;

    cout << endl << "Sorting Descending Prices." << endl;
    cout << "--------------------------------------------------------" << endl;
    start = chrono::high_resolution_clock::now();
    dataManager.Sort(2, false);
    end = chrono::high_resolution_clock::now();

    auto reverseTime = chrono::duration_cast<chrono::microseconds>(end-start);
    auto reverseVsUnsorted = sortedTime.count() - unsortedTime.count();
    cout << "The quick sort when sorting in REVERSE order took [";
    timer.DisplayTime(reverseTime);
    cout << "] microseconds. Which is [" << reverseVsUnsorted << "] microseconds longer than unsorted." << endl;

    return 0;
}