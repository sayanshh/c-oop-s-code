#include <iostream>     
#include <string>       
#include <iomanip>      
#include <cmath>
#include <vector>       

using namespace std;


class Asset {
protected:
    string name;
    int qty;
public:
    Asset(string n, int q) : name(n), qty(q) {}

    virtual void show() {
        cout << "Asset: " << name << ", Quantity: " << qty << endl;
    }

    virtual ~Asset() {}
};

class Stock : public Asset {
    double buy_price;
    double predicted_price;
public:
    Stock(string n, int q, double bp) : Asset(n, q), buy_price(bp), predicted_price(0) {}

    void setPredictedPrice(double profit_percent) {
        double raw_prediction = buy_price + (buy_price * profit_percent / 100.0);
        predicted_price = round(raw_prediction);  
    }

    void show() override {
        cout << fixed << setprecision(2);
        cout << "\nSTOCK NAME: " << name << endl;
        cout << "QUANTITY: " << qty << endl;
        cout << "BUY PRICE: ₹" << buy_price << endl;
        cout << "PREDICTED PRICE: ₹" << predicted_price << endl;

        double total_after_selling = predicted_price * qty;
        cout << "--------------------------" << endl;
        cout << "TOTAL AFTER SELLING: ₹" << total_after_selling << endl;
        cout << "--------------------------" << endl;
    }
};

int main() {
    const double PROFIT_PERCENT = 10.0;

    vector<Asset*> portfolio = {
        new Stock("Tata", 10, 1000),
        new Stock("Reliance", 5, 2000),
        new Stock("Infosys", 15, 900),
        new Stock("HDFC", 8, 1500),
        new Stock("ICICI", 12, 1400)
    };

    cout << "Portfolio" << endl;
    for (auto asset : portfolio) {
        Stock* s = dynamic_cast<Stock*>(asset);
        if (s) s->setPredictedPrice(PROFIT_PERCENT);
        asset->show();
    }

    for (auto asset : portfolio)
        delete asset;

    return 0;
}