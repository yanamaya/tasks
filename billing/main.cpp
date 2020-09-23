#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <ctime>

struct CallInfo {
    std::string number;
    uint durationSeconds;
    time_t date; // month number
};
struct MonthCosts{
    int month; // month's number
    double constFee; //payment for each connection
    int SecondsLimit; //30 seconds limit for Subscriber per month
    double payment;
    //TODO
    int minsOverLimit (int callDuration);//TODO
    void calculateCall(const CallInfo&call);//TODO
    void report();//TODO
};
using CallData = std::vector<CallInfo>;
using SubscriberCallList = std::map <std::string, CallData>;

void fillmap(SubscriberCallList&maptofill);
void showmapinfo (const SubscriberCallList & mpinfo);
time_t setTime (int year, int mon, int day, int hour, int min, int sec);
//TODO:
int checkmonth(const CallInfo & call);



int main() { //main с аргументами, чтобы получить номер: надо посмотреть как, не помню
    SubscriberCallList mp;
    fillmap(mp);
    std::string number="0669876543"; // не знаю как его считать при запуске из командной строки (вводится номер телефона и файл.exe)

    //check if number found
    CallData & callslist = mp.find(number)->second;

    //IF FOUND:
    int size = callslist.size();
    std::vector <MonthCosts> bills;//bills for each month
    //process each call
    int month=0;
    int n=0; // number of bills - months with payments
    for (int i=0; i<size; ++i)
    {
     //if month is not defined yet: create new bill for respective month number
     if (month==0)
       {
        month = checkmonth(callslist[i]);
        bills.push_back(MonthCosts{month, 0.00, 30, 0.00});

        bills[n].calculateCall(callslist[i]);
       }
      //if month the same as previous: the same bill processed
      else if (month==checkmonth(callslist[i]))
      {
        //calculation started for current month
        bills[n].calculateCall(callslist[i]);
        }
      //if month is already defined but differ from previous: new bill for new month created
      else
      {
        //new month calculation started here
        month = checkmonth(callslist[i]);
        bills[n].calculateCall(callslist[i]);
        bills.push_back(MonthCosts{month, 0.00, 30, 0.00});
        ++n; //new month appeared
        bills[n].calculateCall(callslist[i]);
       }
    }
    //Bills info for each month is shown:
    for (auto it=bills.begin(); it<bills.end(); ++it)
    {
        it->report();
    }
    //showmapinfo(mp);
    return 0;
}
time_t setTime (int year, int mon, int day, int hour, int min, int sec){
    time_t date;
    time(&date);
    struct tm* enteredTime = localtime(&date);
    enteredTime->tm_year = year-1900;
    enteredTime->tm_mon = mon-1;
    enteredTime->tm_mday = day;
    enteredTime->tm_hour = hour;
    enteredTime->tm_min = min;
    enteredTime->tm_sec = sec;
    return mktime(enteredTime);
}

void fillmap(SubscriberCallList&maptofill){
    maptofill["0509876543"]=CallData {{"0980123456", 1400, setTime(2020, 8, 28, 10, 22, 33)},
                                      {"0500123456",  712, setTime(2020, 8, 30, 15,  2,  3)},
                                      {"0660123456",  105, setTime(2020, 8, 30, 11, 10, 57)},
                                      {"0970123456",   37, setTime(2020, 8, 31, 20, 17, 41)},
                                      {"0480123456",  534, setTime(2020, 8, 31, 12, 20, 32)},
                                      {"0660123456",  125, setTime(2020, 9,  2,  1, 30, 57)},
                                      {"0970123456",   37, setTime(2020, 9,  3, 20, 17, 41)},
                                      {"0480123456",  534, setTime(2020, 9,  3, 19, 20, 12)}

    };
    maptofill["0669876543"]=CallData {{"0980123456",  140, setTime(2020, 8, 23, 20, 11, 33)},
                                      {"0500123456",   72, setTime(2020, 8, 23, 12, 32, 13)},
                                      {"0660123456", 1005, setTime(2020, 8, 23, 21, 18, 53)},
                                      {"0970123456",  307, setTime(2020, 8, 31, 23, 59,  1)},
                                      {"0480123456", 2534, setTime(2020, 9,  1, 22, 20, 32)},
                                      {"0660123456",   25, setTime(2020, 9,  2,  7, 29, 17)},
                                      {"0970123456",  750, setTime(2020, 9,  2, 14, 25, 32)},
                                      {"0480123456", 1534, setTime(2020, 9,  3, 17, 20, 42)}

    };
    maptofill["0999876543"]=CallData {{"0980123456",  207, setTime(2020, 8, 29, 20, 11, 33)},
                                      {"0500123456",  539, setTime(2020, 8, 29, 12, 32, 13)},
                                      {"0660123456", 1305, setTime(2020, 8, 30, 21, 18, 53)},
                                      {"0970123456",    7, setTime(2020, 8, 31, 23, 59,  1)},
                                      {"0480123456",   39, setTime(2020, 9,  1, 22, 20, 32)},
                                      {"0660123456",  199, setTime(2020, 9,  1,  7, 29, 17)},
                                      {"0970123456",  896, setTime(2020, 9,  1, 14, 25, 32)},
                                      {"0480123456",  134, setTime(2020, 9,  4, 17, 20, 42)}

    };
}

void showmapinfo(const SubscriberCallList & mpinfo){
    for (auto & it : mpinfo) {
        std::cout << it.first << std::endl;
        for (auto & itv: it.second){
            std::cout << "\t\t\t" << itv.number << "\t"
                                  << itv.durationSeconds << " seconds" << "\t"
                                  << ctime(&itv.date) << std::endl;
        }
    }
}

int checkmonth(const CallInfo & call){
    //get from vector element month number and return it as int
    return 8;
}
int MonthCosts::minsOverLimit (int callDuration){
    //check the value monthLimit if it is no more than 30 minutes return 0 to pay
    // if more than 30 -> add the limit to 30 and return the rest for payment
    return true;
}
void MonthCosts::calculateCall(const CallInfo&call){
    this->constFee +=0.33;
    //check the net
    this->payment +=minsOverLimit(call.durationSeconds)*0.51; // or 0.95
}
void MonthCosts::report(){
std::cout << " per month: " << this->payment << "UAH" << std::endl;
}
