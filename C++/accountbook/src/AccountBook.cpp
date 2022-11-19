#include "../include/AccountBook.h"
#include "../include/DataAnalysis.h"
#include <iostream>
#include <string>

using namespace std;

AccountBook::AccountBook() {
    isTerminate = false;
}
void AccountBook::initialize() {
    dataManager.load();
}
MENU AccountBook::printAndGetMenu() {
    
    MENU menu;
    int input;

    while(true) {
        cout << endl;
        cout << "----------- Please Select Menu -----------" << endl;
        cout << "1. Input" << endl;
        cout << "2. Spend Pattern Analysis" << endl;
        cout << "3. Terminate" << endl;

        cin >> input;
        if(input > (int)MENU::NONE && input < (int)MENU::LAST) {
            menu = (MENU)input;
            break;
        } else {
            cout << "You entered wrong menu" << endl;
            cout << "Please select menu again" << endl;
        }
    }

    return menu;
}
bool AccountBook::isProgramTerminate() {
    if(isTerminate) {
        dataManager.save();
    }
    return isTerminate;
}
INPUT_MENU AccountBook::printAndGetInputMenu() {

    INPUT_MENU menu;
    int input;

    while(true) {
        cout << endl;
        cout << "----------- Please Select Input Menu -----------" << endl;
        cout << "1. Incom" << endl;
        cout << "2. Outcome" << endl;
        cout << "3. Terminate" << endl;

        cin >> input;
        if(input > (int)INPUT_MENU::NONE && input < (int)INPUT_MENU::LAST) {
            menu = (INPUT_MENU)input;
            break;
        } else {
            cout << "You entered wrong input menu" << endl;
            cout << "Please select input menu again" << endl;
        }
    }

    return menu;
}
void AccountBook::runInput(INPUT_MENU inputMenu) {
    switch(inputMenu){
        case INPUT_MENU::INCOME:
            string date;
            int amount;

            cout << "Date(YYMMDD) : ";
            cin >> date;
            cout << "Income Amount : ";
            cin >> amount;

            AccountData data(
                date,
                DATA_TYPE::INCOME,
                amount);
            dataManager.appendData(data);
            break;

        case INPUT_MENU::OUTCOME:
            string date, name, category;
            int amount;

            cout << "Date(YYMMDD) : ";
            cin >> date;
            cout << "Item Name : ";
            cin >> name;
            cout << "Item Category : ";
            cin >> category;
            cout << "Income Amount : ";
            cin >> amount;

            AccountData data(
                date,
                DATA_TYPE::OUTCOME,
                amount,
                name,
                category);
            dataManager.appendData(data);
            break;

        default:
            break;    
    }
}
void AccountBook::runSPA() {
    cout << "1. Period Analysis" << endl;
    cout << "2. Yearly Analysis" << endl;
    cout << "3. Monthly Analysis" << endl;
    cout << "4. Daily Analysis" << endl;
    cin >> type;
    
    string date, date_end = "";
    switch((ANALYSIS_TYPE)type) {
        case ANALYSIS_TYPE::PERIOD:
            cout << "Type start date(YYYYMMDD) : ";
            cin >> date;
            cout << "Type end date(YYYYMMDD) : ";
            cin >> date_end;
            break;
        case ANALYSIS_TYPE::YEARLY:
            cout << "Type year(YYYY) : ";
            cin >> date;
            break;
        case ANALYSIS_TYPE::MONTHLY:
            cout << "Type month with year(YYYYMM) : ";
            cin >> date;
            break;
        case ANALYSIS_TYPE::DAILY:
            cout << "Type date(YYYYMMDD) : ";
            cin >> date;
            break;
        default:
            break;
    }
    dataAnalysis.selectTarget(date, date_end);

    int mode;
    cout << "Select analysis mode" << endl;
    cout << "1. Total income/outcome" << endl;
    cout << "2. Outcome by category" << endl;
    cin >> mode;

    dataAnalysis.makeAnalysisData(
        (ANALYSIS_TYPE)type, 
        (ANALYSIS_MODE)mode,
        dataManager.get());

    dataAnalysis.analyze((ANALYSIS_TYPE)type, (ANALYSIS_MODE)mode);
}
void AccountBook::setProgramTerminate() {
    isTerminate = true;
}