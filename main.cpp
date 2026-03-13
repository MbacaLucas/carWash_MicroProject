#include <iostream>
#include <algorithm> // For std::find_if
#include <numeric>   // For std::accumulate
#include <vector>
#include <string>
#include <iomanip> // For std::setw, std::fixed, and std::setprecision

// Master Catalog Entity
struct ServiceType
{
    int id;
    std::string name;
    double price;
};

// Transactional Record Entity
struct ServiceRecord
{
    int id;
    int serviceId; // Foreign Key connecting to ServiceType
    std::string customerName;
};

int main()
{
    // Predefined catalog of available services
    std::vector<ServiceType> servicesCatalog{{1, "Basic Wash", 10.0}, {2, "Premium Wash", 20.0}, {3, "VIP", 35.0}};

    // Container to store the daily sales records
    std::vector<ServiceRecord> records{};

    bool keepRunning{true};
    char answerRest{};

    // --- DATA CAPTURE LOOP ---
    while (keepRunning)
    {
        ServiceRecord newRecord{};
        bool isValid{false};
        int option{};

        // Input Validation: Ensures the user selects an existing ID from the catalog
        do
        {
            for (const auto &st : servicesCatalog)
            {
                std::cout << '[' << st.id << "]." << st.name << ": $" << st.price << '\t';
            }
            std::cout << '\n'
                      << std::string(60, '=') << "\nChoice: ";
            std::cin >> option;

            // Check if the input ID exists in the catalog
            for (const auto &st : servicesCatalog)
            {
                if (option == st.id)
                {
                    isValid = true;
                    break;
                }
            }

            if (!isValid)
            {
                std::cout << "\n(❌ERROR: Invalid ID, please try again...)\n";
            }

        } while (!isValid);

        // Building the new record
        newRecord.id = records.size() + 1; // Auto-incremental ID generation
        newRecord.serviceId = option;

        std::cout << "Enter the customer name: ";
        // std::ws clears leading whitespace to ensure getline works correctly
        std::getline(std::cin >> std::ws, newRecord.customerName);

        records.push_back(newRecord);

        std::cout << "\nDo you need to add another record? (y/n): ";
        std::cin >> answerRest;

        if (answerRest == 'n' || answerRest == 'N')
        {
            keepRunning = false;
        }
    }

    // --- REPORT SECTION (VIEW) ---
    std::cout << '\n'
              << std::left << std::setw(5) << "ID"
              << std::setw(25) << "Customer Name"
              << std::setw(15) << "Service"
              << std::setw(10) << "Price" << '\n';
    std::cout << std::string(55, '=') << '\n';

    // Iterate through records to print the tabular report
    for (const auto &sr : records)
    {
        // Relational Lookup: Find the service name using the record's serviceId
        auto it = std::find_if(servicesCatalog.begin(), servicesCatalog.end(), [sr](const ServiceType &s)
                               { return s.id == sr.serviceId; });

        if (it != servicesCatalog.end())
        {
            std::cout << std::left << std::setw(5) << sr.id
                      << std::setw(25) << sr.customerName
                      << std::setw(15) << it->name
                      << "$" << std::fixed << std::setprecision(2) << it->price << '\n';
        }
    }

    std::cout << std::string(55, '-') << '\n';

    // --- STATISTICAL CALCULATION (Advanced Relational Logic) ---
    // Use accumulate to sum prices that live in a different vector (servicesCatalog)
    double sumTotal = std::accumulate(records.begin(), records.end(), 0.0, [&servicesCatalog](double currentTotal, const ServiceRecord &sr)
                                      {
        // For each sales record, look up its price in the master catalog
        auto it = std::find_if(servicesCatalog.begin(), servicesCatalog.end(), [sr](const ServiceType &st) {
            return st.id == sr.serviceId;
        });
        
        // If found, add the price to the total; otherwise, add 0.0
        return currentTotal + (it != servicesCatalog.end() ? it->price : 0.0); });

    // Output the formatted final total
    std::cout << std::right << std::setw(45) << "TOTAL REVENUE: $"
              << std::fixed << std::setprecision(2) << sumTotal << "\n";

    return 0;
}