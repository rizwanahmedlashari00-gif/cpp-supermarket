#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;


const string RESET = "\033[0m";
const string BOLD = "\033[1m";
const string GREEN = "\033[1;32m";
const string RED = "\033[1;31m";
const string CYAN = "\033[1;36m";
const string YELLOW = "\033[1;33m";
const string CLEAR_SCREEN = "\033[2J\033[1;1H"; 


struct Product {
    string name;
    float costPrice;     
    float sellingPrice;  
    int stock;           
};


unordered_map<int, Product> inventory; 
float dailyRevenue = 0.0;
float dailyCost = 0.0;


void ensureDatabaseExists() {
    ifstream file("supermarket.csv");
    if (!file.is_open()) {
        ofstream newFile("supermarket.csv");
        newFile << "Code,Name,CostPrice,SellingPrice,Stock\n";
        
        // --- Dairy & Bakery ---
        newFile << "101,Milk 1L,220.0,250.0,50\n";
        newFile << "102,White Bread,100.0,120.0,30\n";
        newFile << "103,Eggs (1 Dozen),260.0,300.0,100\n";
        newFile << "104,Butter 200g,300.0,350.0,40\n";
        newFile << "105,Yogurt 500g,120.0,150.0,45\n";
        newFile << "106,Cheese Slices,400.0,450.0,20\n";
        newFile << "107,Cake Rusk,150.0,200.0,35\n";
        newFile << "108,Chocolate Pastry,80.0,120.0,25\n";
        newFile << "109,Brown Bread,120.0,140.0,20\n";
        newFile << "110,Burger Buns (4pc),60.0,80.0,30\n";

        // --- Pantry Staples ---
        newFile << "111,Wheat Flour 10kg,1200.0,1400.0,50\n";
        newFile << "112,Basmati Rice 1kg,300.0,350.0,80\n";
        newFile << "113,Premium Cooking Oil 1L,450.0,500.0,60\n";
        newFile << "114,Ghee 1kg,480.0,550.0,40\n";
        newFile << "115,Sugar 1kg,130.0,150.0,100\n";
        newFile << "116,Salt 800g,40.0,60.0,90\n";
        newFile << "117,Daal Chana 1kg,240.0,280.0,50\n";
        newFile << "118,Daal Mash 1kg,300.0,350.0,45\n";
        newFile << "119,Daal Moong 1kg,260.0,300.0,50\n";
        newFile << "120,Daal Masoor 1kg,280.0,320.0,55\n";
        newFile << "121,White Chickpeas 1kg,320.0,380.0,40\n";
        newFile << "122,Black Chickpeas 1kg,250.0,290.0,40\n";
        newFile << "123,Tea 200g,480.0,550.0,60\n";
        newFile << "124,Coffee 50g,350.0,400.0,30\n";
        newFile << "125,Green Tea Box,150.0,180.0,40\n";

        // --- Spices & Condiments ---
        newFile << "126,Red Chili Powder 100g,120.0,150.0,50\n";
        newFile << "127,Turmeric Powder 100g,100.0,130.0,50\n";
        newFile << "128,Coriander Powder 100g,90.0,120.0,50\n";
        newFile << "129,Garam Masala 50g,80.0,110.0,40\n";
        newFile << "130,Black Pepper 50g,90.0,120.0,45\n";
        newFile << "131,Cumin Seeds 50g,70.0,100.0,40\n";
        newFile << "132,Tomato Ketchup 500g,200.0,250.0,60\n";
        newFile << "133,Garlic Paste 250g,120.0,150.0,35\n";
        newFile << "134,Ginger Paste 250g,120.0,150.0,35\n";
        newFile << "135,Mayonnaise 500ml,300.0,350.0,40\n";
        newFile << "136,Soy Sauce 250ml,140.0,180.0,30\n";
        newFile << "137,Chili Sauce 250ml,140.0,180.0,30\n";
        newFile << "138,Vinegar 250ml,90.0,120.0,40\n";
        newFile << "139,Mixed Pickle 330g,180.0,220.0,25\n";
        newFile << "140,Honey 250g,500.0,600.0,20\n";

        // --- Beverages ---
        newFile << "141,Mineral Water 1.5L,60.0,80.0,100\n";
        newFile << "142,Cola 1.5L,120.0,150.0,80\n";
        newFile << "143,Lemon Lime Soda 1.5L,120.0,150.0,80\n";
        newFile << "144,Orange Soda 1.5L,120.0,150.0,70\n";
        newFile << "145,Mango Juice 1L,180.0,220.0,50\n";
        newFile << "146,Apple Juice 1L,180.0,220.0,50\n";
        newFile << "147,Energy Drink 250ml,200.0,250.0,60\n";
        newFile << "148,Peach Malt 330ml,80.0,120.0,45\n";
        newFile << "149,Cold Coffee Can,150.0,200.0,30\n";
        newFile << "150,Soda Water 1L,70.0,100.0,40\n";

        // --- Snacks & Chocolates ---
        newFile << "151,Potato Chips (Salted),80.0,100.0,90\n";
        newFile << "152,Potato Chips (Spicy),80.0,100.0,90\n";
        newFile << "153,Corn Puffs,40.0,60.0,60\n";
        newFile << "154,Chocolate Bar 50g,60.0,80.0,100\n";
        newFile << "155,Wafers Box,120.0,150.0,40\n";
        newFile << "156,Instant Noodles (Chicken),50.0,70.0,120\n";
        newFile << "157,Instant Noodles (Spicy),50.0,70.0,120\n";
        newFile << "158,Biscuits (Zeera),40.0,60.0,80\n";
        newFile << "159,Biscuits (Chocolate),50.0,70.0,80\n";
        newFile << "160,Cookies Box,150.0,200.0,30\n";
        newFile << "161,Popcorn Microwave,100.0,150.0,25\n";
        newFile << "162,Mixed Nuts 100g,250.0,300.0,20\n";
        newFile << "163,Peanuts 100g,100.0,150.0,40\n";
        newFile << "164,Candies Pack,80.0,120.0,50\n";
        newFile << "165,Bubble Gum Pack,40.0,60.0,70\n";

        // --- Fresh Produce ---
        newFile << "166,Apples 1kg,200.0,250.0,30\n";
        newFile << "167,Bananas 1 Dozen,120.0,150.0,40\n";
        newFile << "168,Oranges 1 Dozen,150.0,200.0,35\n";
        newFile << "169,Onions 1kg,80.0,120.0,60\n";
        newFile << "170,Potatoes 1kg,70.0,100.0,70\n";
        newFile << "171,Tomatoes 1kg,100.0,150.0,45\n";
        newFile << "172,Garlic 250g,140.0,180.0,25\n";
        newFile << "173,Ginger 250g,160.0,200.0,25\n";
        newFile << "174,Lemons 250g,80.0,120.0,30\n";
        newFile << "175,Green Chilies 100g,40.0,60.0,40\n";

        // --- Personal Care ---
        newFile << "176,Bath Soap 100g,70.0,90.0,80\n";
        newFile << "177,Shampoo 200ml,280.0,350.0,40\n";
        newFile << "178,Hair Conditioner 200ml,280.0,350.0,35\n";
        newFile << "179,Toothpaste 100g,140.0,180.0,60\n";
        newFile << "180,Toothbrush,80.0,120.0,70\n";
        newFile << "181,Face Wash 100ml,240.0,300.0,30\n";
        newFile << "182,Body Lotion 200ml,320.0,400.0,25\n";
        newFile << "183,Hand Wash Liquid 250ml,180.0,220.0,45\n";
        newFile << "184,Deodorant Body Spray,400.0,500.0,30\n";
        newFile << "185,Shaving Cream,120.0,160.0,25\n";

        // --- Cleaning & Household ---
        newFile << "186,Laundry Detergent 1kg,320.0,400.0,50\n";
        newFile << "187,Dishwash Liquid 500ml,200.0,250.0,40\n";
        newFile << "188,Dishwash Bar,50.0,70.0,80\n";
        newFile << "189,Floor Cleaner 1L,240.0,300.0,35\n";
        newFile << "190,Toilet Cleaner 500ml,160.0,200.0,40\n";
        newFile << "191,Glass Cleaner 500ml,180.0,220.0,30\n";
        newFile << "192,Tissue Box (150s),120.0,160.0,60\n";
        newFile << "193,Toilet Paper (4 Rolls),280.0,350.0,40\n";
        newFile << "194,Trash Bags (Medium),120.0,150.0,50\n";
        newFile << "195,Matchbox Pack,40.0,60.0,100\n";

        // --- Stationary & Misc ---
        newFile << "196,Ballpoint Pens (5pc),80.0,100.0,50\n";
        newFile << "197,A4 Paper Rim,800.0,1000.0,15\n";
        newFile << "198,AA Batteries (2pc),120.0,160.0,40\n";
        newFile << "199,AAA Batteries (2pc),120.0,160.0,40\n";
        newFile << "200,Super Glue,40.0,50.0,100\n";

        newFile.close();
    } else {
        file.close();
    }
}


void loadCSV() {
    ensureDatabaseExists();
    ifstream file("supermarket.csv");
    string line, word;
    
    getline(file, line); 

    while (getline(file, line)) {
        stringstream ss(line);
        int code, stock;
        string name;
        float cp, sp;

        getline(ss, word, ','); code = stoi(word);
        getline(ss, word, ','); name = word;
        getline(ss, word, ','); cp = stof(word);
        getline(ss, word, ','); sp = stof(word);
        getline(ss, word, ','); stock = stoi(word);

        inventory[code] = {name, cp, sp, stock};
    }
    file.close();
}


void saveCSV() {
    ofstream file("supermarket.csv");
    file << "Code,Name,CostPrice,SellingPrice,Stock\n";
    for (auto const& pair : inventory) {
        file << pair.first << "," 
             << pair.second.name << "," 
             << pair.second.costPrice << "," 
             << pair.second.sellingPrice << "," 
             << pair.second.stock << "\n";
    }
    file.close();
}


int main() {
    loadCSV(); 
    int choice;

    while (true) {
        cout << CLEAR_SCREEN; 
        cout << CYAN << BOLD << "=================================================\n";
        cout << "            SUPER-MART SOFTWARE              \n";
        cout << "=================================================\n" << RESET;
        cout << "1. Cashier: Start Checkout\n";
        cout << "2. Admin: Add New Product\n";
        cout << "3. Admin: View Live Inventory\n";
        cout << "4. Admin: Manager Dashboard (Analytics)\n";
        cout << "5. Exit System\n";
        cout << "Enter Choice: ";
        cin >> choice;

        if (choice == 1) {
            
            if (inventory.empty()) {
                cout << RED << "Database is empty.\n" << RESET;
                system("pause"); 
                continue;
            }

            cout << CLEAR_SCREEN;
            cout << GREEN << BOLD << "--- CASHIER TERMINAL RUNNING ---\n\n" << RESET;
            
            float billSubTotal = 0.0;
            float billCost = 0.0; 
            char addMore = 'y';

            
            int cartCodes[50];
            int cartQtys[50];
            int cartSize = 0;

            while ((addMore == 'y' || addMore == 'Y') && cartSize < 50) {
                int searchCode;
                cout << "Scan Item Code: ";
                cin >> searchCode;
                if (inventory.find(searchCode) != inventory.end()) {
                    cout << "Found: " << inventory[searchCode].name << " | Stock: " << inventory[searchCode].stock << "\n";
                    
                    int qty;
                    cout << "Enter Quantity: ";
                    cin >> qty;

                    if (qty > inventory[searchCode].stock) {
                        cout << RED << "Error: Not enough stock available!\n" << RESET;
                    } else {
                        cartCodes[cartSize] = searchCode;
                        cartQtys[cartSize] = qty;
                        cartSize++;
                        inventory[searchCode].stock -= qty; 
                        
                        cout << GREEN << "Added to cart.\n" << RESET;
                    }
                } else {
                    cout << RED << "Error: Unrecognized Barcode/Code.\n" << RESET;
                }

                cout << "Scan another item? (y/n): ";
                cin >> addMore;
            }
            if (cartSize > 0) {
                cout << CLEAR_SCREEN;
                cout << CYAN << "=================================================\n";
                cout << "                 FINAL RECEIPT                   \n";
                cout << "=================================================\n" << RESET;
                cout << left << setw(10) << "Code" << setw(20) << "Item" << setw(5) << "Qty" << "Total\n";
                cout << "-------------------------------------------------\n";

                for (int i = 0; i < cartSize; i++) {
                    int id = cartCodes[i];
                    float itemTotal = inventory[id].sellingPrice * cartQtys[i];
                    
                    billSubTotal += itemTotal;
                    billCost += (inventory[id].costPrice * cartQtys[i]); // Calculate cost silently

                    cout << left << setw(10) << id << setw(20) << inventory[id].name 
                         << setw(5) << cartQtys[i] << itemTotal << " PKR\n";
                }
                
                cout << "-------------------------------------------------\n";
                float tax = billSubTotal * 0.15;
                float finalPayable = billSubTotal + tax;
                
                cout << "SUBTOTAL: " << billSubTotal << " PKR\n";
                cout << YELLOW << "GST (15%): +" << tax << " PKR\n" << RESET;
                cout << GREEN << BOLD << "FINAL PAYABLE: " << finalPayable << " PKR\n" << RESET;
                cout << CYAN << "=================================================\n" << RESET;

                float cash;
                cout << "\nEnter Cash Received: ";
                cin >> cash;
                while (cash < finalPayable) {
                    cout << RED << "Insufficient. Enter at least " << finalPayable << ": " << RESET;
                    cin >> cash;
                }

                cout << BOLD << "CHANGE RETURNED: " << (cash - finalPayable) << " PKR\n" << RESET;
                dailyRevenue += billSubTotal;
                dailyCost += billCost;
                saveCSV(); 
            }
            system("pause");
        }
        else if (choice == 2) {
            
            string pass;
            cout << "Admin Password: "; cin >> pass;
            if (pass == "01100011") {
                int code;
                cout << "Enter New Product Code: "; cin >> code;
                
                if (inventory.find(code) != inventory.end()) {
                    cout << RED << "Error: Code already exists!\n" << RESET;
                } else {
                    Product p;
                    cout << "Name: "; cin >> ws; getline(cin, p.name);
                    cout << "Cost Price (What you paid): "; cin >> p.costPrice;
                    cout << "Selling Price: "; cin >> p.sellingPrice;
                    cout << "Initial Stock: "; cin >> p.stock;
                    
                    inventory[code] = p;
                    saveCSV();           
                    cout << GREEN << "Product Added & Database Updated!\n" << RESET;
                }
            } else { cout << RED << "Access Denied.\n" << RESET; }
            system("pause");
        }
       else if (choice == 3) {
            string pass;
            cout << "Admin Password: "; 
            cin >> pass;

            if (pass == "01100011") {
                cout << CLEAR_SCREEN;
                cout << YELLOW << BOLD << "--- LIVE INVENTORY DATABASE ---\n" << RESET;
                cout << left << setw(10) << "Code" << setw(20) << "Name" << setw(10) << "Stock" << "Price\n";
                cout << "--------------------------------------------------------\n";
                
                for (auto const& pair : inventory) {
                    cout << left << setw(10) << pair.first 
                         << setw(20) << pair.second.name 
                         << setw(10) << pair.second.stock 
                         << pair.second.sellingPrice << " PKR\n";
                }
            } else {
                cout << RED << "Access Denied! Incorrect password.\n" << RESET;
            }
            
            cout << "\n";
            system("pause");
        }
        else if (choice == 4) {
            string pass;
            cout << "Manager Password: "; cin >> pass;
            if (pass == "01100011") {
                cout << CLEAR_SCREEN;
                float grossProfit = dailyRevenue - dailyCost;
                float margin = (dailyRevenue > 0) ? (grossProfit / dailyRevenue) * 100 : 0.0;

                cout << CYAN << BOLD << "=================================================\n";
                cout << "              END OF DAY ANALYTICS               \n";
                cout << "=================================================\n" << RESET;
                cout << "Total Revenue (Excl Tax): " << GREEN << dailyRevenue << " PKR\n" << RESET;
                cout << "Total Cost of Goods:      " << RED << dailyCost << " PKR\n" << RESET;
                cout << "Gross Profit:             " << GREEN << BOLD << grossProfit << " PKR\n" << RESET;
                cout << "Profit Margin:            " << margin << " %\n";
                cout << "-------------------------------------------------\n";
                cout << YELLOW << "?? LOW STOCK ALERTS (< 10 units): \n" << RESET;
                
                bool alerts = false;
                for (auto const& pair : inventory) {
                    if (pair.second.stock < 10) {
                        cout << RED << " -> " << pair.second.name << " (Only " << pair.second.stock << " left!)\n" << RESET;
                        alerts = true;
                    }
                }
                if (!alerts) cout << GREEN << "All items are well stocked.\n" << RESET;
                cout << "=================================================\n";
            } else { cout << RED << "Access Denied.\n" << RESET; }
            system("pause");
        }
        else if (choice == 5) {
            cout << GREEN << "Saving database and exiting... Goodbye!\n" << RESET;
            saveCSV();
            break;
        }
    }
    return 0;
}
