// main.cpp
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
//#include "StateClimate.h"

class StateClimate {
    private:
    int fips;
    int year;
    double temp;
    double tempc;
    public:
    // Constructor
    StateClimate(int f, int y, double t, double tc);
    // Getters
    int getFips() const;
    int getYear() const;
    double getTemp() const;
    double getTempC() const;
    // Setters
    void setFips(int f);
    void setYear(int y);
    void setTemp(double t);
    void setTempC(double tc);
    // Display function
    void display() const;
    };
    StateClimate::StateClimate(int f, int y, double t, double tc) : fips(f), year(y),
    temp(t), tempc(tc) {}
    // Getters
    int StateClimate::getFips() const { return fips; }
    int StateClimate::getYear() const { return year; }
    double StateClimate::getTemp() const { return temp; }
    double StateClimate::getTempC() const { return tempc; }
    // Setters
    void StateClimate::setFips(int f) { fips = f; }
    void StateClimate::setYear(int y) { year = y; }
    void StateClimate::setTemp(double t) { temp = t; }
    void StateClimate::setTempC(double tc) { tempc = tc; }
    // Display function
    void StateClimate::display() const {
    std::cout << "FIPS: " << fips << ", Year: " << year
    << ", Temp (F): " << temp << ", Temp (C): " << tempc << std::endl;
    }

// Binary Search
int binarySearch(const std::vector<StateClimate>& data, int fips){
    int left = 0;
    int right = data.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (data[mid].getFips() == fips) {
            return mid;
        }
        if (data[mid].getFips() < fips) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

int main() {
    std::vector<StateClimate> climateData;
    std::ifstream file("climdiv_state_year.csv");
    
    if (!file) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    std::string line;
    std::getline(file, line); // Skip header line
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        int fips, year;
        double temp, tempc;
        char comma;

        ss >> fips >> comma >> year >> comma >> temp >> comma >> tempc;
        climateData.emplace_back(fips, year, temp, tempc);
    }

    file.close();

    // Display data
    for (const auto &entry : climateData) {
        entry.display();
    }
    
    // Search for FIPS code
    int fipsToSearch;
    std::cout << "Enter FIPS code to search:";
    std::cin >> fipsToSearch;

    // Search for FIPS code
    int index = binarySearch(climateData, fipsToSearch);
    if(index != -1){
        climateData[index].display();
    }else{
        std::cout << "FIPS code not found!" << std::endl;
    }

    return 0;
}
