#include<bits/stdc++.h>
#define Shelter main
using namespace std;

#define endFunc cout << "\n\n"

class Wage {
    private:
        float wageBase;
        double wage;
    public:
        Wage() { wageBase = 0; wage = 0; }
        float getWageBase() { return wageBase; }
        double getWage() { return wage; }
        void setWageBase(string onPos) {
            if (onPos == "Chef") wageBase = 24000;
            if (onPos == "Served") wageBase = 12000;
            if (onPos == "Receptionist") wageBase = 18000;
            if (onPos == "Bartender") wageBase = 18000;
            if (onPos == "#") wageBase = 0;
        }
        void setWage(double inpWage) { wage = inpWage; }
        void calWage(float workingTime) { wage = workingTime*wageBase; }
        void expData() { cout << setw(15) << wageBase << " | " << setw(20) << wage << " |"; }
};

class Staff {
    private:
        string id;
        string name;
        int age;
        string gender;
        string flAddress;
        string onPos;
        Wage wage;
    public:
        Staff() { 
            id = "#"; 
            name = "#"; 
            age = -1; 
            gender = "#";
            flAddress = "#"; 
            onPos = "#";
        }
        string getId() { return id; }
        string getName() { return name; }
        int getAge() { return age; }
        string getGender() { return gender; }
        string getFlAddress() { return flAddress; }
        string getOnPos() { return onPos; }
        Wage &getWageAtr() { return wage; }  

        void setId(string inpId) { id = inpId; }
        void setName(string inpName) { name = inpName; }
        void setAge(int inpAge) { name = inpAge; }
        void setGender(string inpGender) { gender = inpGender; }
        void setFlAddress(string inpFlAddress) { flAddress = inpFlAddress; }
        void setOnPos(string inpOnPos) { 
            onPos = inpOnPos;
            wage.setWageBase(inpOnPos);
        }
        
        Staff &operator = (Staff stf) {
            id = stf.getId();
            name = stf.getName();
            age = stf.getAge();
            gender = stf.getGender();
            flAddress = stf.getFlAddress();
            onPos = stf.getOnPos();
            wage = stf.getWageAtr();

            return *this;
        }
        bool operator < (Staff stf) {
            return wage.getWage() < stf.getWageAtr().getWage();
        }

        friend istream &operator >> (istream &is, Staff &stf);
        friend ostream &operator << (ostream &os, Staff &stf);
};

istream &operator >> (istream &is, Staff &stf) {
    cout << "ID: ";
    getline(is, stf.id);
    if (stf.id.length() > 9) stf.id = "#";
    cout << "Name: ";
    getline(is, stf.name); 
    cout << "Age: ";
    is >> stf.age;
    is.ignore();
    cout << "Gender: ";
    getline(is, stf.gender);
    cout << "Address: ";
    getline(is, stf.flAddress);
    cout << "On Position: ";
    getline(is, stf.onPos);
    stf.wage.setWageBase(stf.onPos);

    return is;
}

ostream &operator << (ostream &os, Staff &stf) {
    os << "| " << setw(10) << stf.getId() << " | " << setw(20) << stf.getName() << " | " << setw(5) << stf.getAge() << " | " << setw(10) << stf.getGender() << " | " << setw(15) << stf.getFlAddress() << " | " << setw(15) << stf.getOnPos() << " | ";
    stf.getWageAtr().expData();
    
    return os;
}

class StaffManage {
    private:
        vector<Staff> sVect;
        string mode;
    public:
        StaffManage() { mode = "ID"; }
        int getQty() { return sVect.size(); }
        vector<Staff> &getData() { return sVect; }
        string getMode() { return mode; }
        string getNextMode() {
            if (mode == "ID") return "Wage";
            else return "ID";
        }

        void insert(Staff stf) {
            int currPos = 0;
            if (mode == "ID") {
                while (currPos < sVect.size() && stf.getId() > sVect[currPos].getId()) currPos++;
            } else if (mode == "Wage") {
                while (currPos < sVect.size() && stf.getWageAtr().getWage() > sVect[currPos].getWageAtr().getWage()) currPos++;
            }

            sVect.insert(sVect.begin() + currPos, stf);
        }
        
        void getInp(Staff newStaff) {
            insert(newStaff);
            cout << "[Alert] Da them nhan vien co ID: " << newStaff.getId() << "\n";
        }
        void del(string inpId) {
            for (int i = 0; i < sVect.size(); i++) {
                if (sVect[i].getId() == inpId) {
                    sVect.erase(sVect.begin() + i);
                    cout << "[Alert] Da xoa 1 nhan vien: " << sVect[i].getId() << "\n";
                    return;
                }
            }
            cout << "[Error] Khong tim thay nhan vien " << inpId << " trong du lieu!\n";
        }
        void changeInfor(string fixType, string needFixId, string inpId, string inpName, int inpAge, string inpGender, string inpAddress, string inpOnPos, double inpWage) {
            int staffPos = getStaff(needFixId);
            if (staffPos != -1) {
                if (inpId != "#") sVect[staffPos].setId(inpId);
                if (inpName != "#") sVect[staffPos].setName(inpName);
                if (inpAge != -1) sVect[staffPos].setAge(inpAge);
                if (inpGender != "#") sVect[staffPos].setGender(inpGender);
                if (inpAddress != "#") sVect[staffPos].setFlAddress(inpAddress);
                if (inpOnPos != "#") sVect[staffPos].setOnPos(inpOnPos);
                if (inpWage != -1) sVect[staffPos].getWageAtr().setWage(inpWage);
                cout << "[Alert] Da sua thong tin: " << fixType << " cho nhan vien co ID: " << needFixId << "\n";
            } else {
                cout << "[Error] Khong tim thay nhan vien " << needFixId << " trong du lieu!\n";
            }
        }
        friend bool wageCmp(Staff a, Staff b);
        friend void staffSort(vector<Staff> &v, string mode);
        void findById(string inpId) {
            int posRes = -1;
            if (mode == "ID") {
                int l = 0, r = sVect.size()-1;
                while (l <= r) {
                    int m = l + (r-l)/2;
                    if (sVect[m].getId() == inpId) {
                        posRes = m;
                        break;
                    }
                    if (sVect[m].getId() < inpId) l = m + 1;
                    if (sVect[m].getId() > inpId) r = m - 1;
                }
            } else {
                for (int i = 0; i < sVect.size(); i++) {
                    if (sVect[i].getId() == inpId) {
                        posRes = i;
                        break;
                    }
                }
            }
            if (posRes != -1) {
                cout << "[Infor] Thong tin nhan vien can tim:\n";
                cout << "---------------------------------------------------------------------------------------------------------------------------------------\n";
                cout << "| " << setw(10) << "ID" << " | " << setw(20) << "Ho Ten" << " | " << setw(5) << "Age" << " | " << setw(10) << "Gender" << " | " << setw(15) << "Address" << " | " << setw(15) << "On-Position" << " | " << setw(15) << setw(15) << "Base Wage" << " | " << setw(20) << "Wage" << " |" << "\n";
                cout << "---------------------------------------------------------------------------------------------------------------------------------------\n";
                cout << sVect[posRes] << "\n";
                cout << "---------------------------------------------------------------------------------------------------------------------------------------\n";
            } else {
                cout << "[Error] Khong tim thay nhan vien can tim\n";
            }
        }
        void findByName(string name) {
            vector<Staff> res;
            for (int i = 0; i < sVect.size(); i++) {
                if (sVect[i].getName() == name) {
                    res.push_back(sVect[i]);
                }
            }
            if (res.size() != 0) {
                cout << "[Infor] Thong tin nhan vien can tim:\n";
                cout << "---------------------------------------------------------------------------------------------------------------------------------------\n";
                cout << "| " << setw(10) << "ID" << " | " << setw(20) << "Ho Ten" << " | " << setw(5) << "Age" << " | " << setw(10) << "Gender" << " | " << setw(15) << "Address" << " | " << setw(15) << "On-Position" << " | " << setw(15) << setw(15) << "Base Wage" << " | " << setw(20) << "Wage" << " |" << "\n";
                cout << "---------------------------------------------------------------------------------------------------------------------------------------\n";
                for (int i = 0; i < res.size(); i++) {
                    cout << res[i] << "\n";
                }   
                cout << "---------------------------------------------------------------------------------------------------------------------------------------\n";
            } else {
                cout << "[Error] Khong tim thay nhan vien can tim\n";
            }
        }
        void switchMode() {
            if (mode == "ID") mode = "Wage";
            else mode = "ID";
            cout << "[Alert] Mode had been changed to " << mode << " mode!\n";
        }
        void calWage(string type, string inpId, vector<float> wTime) {
            if (type == "One") {
                if (mode == "ID") {
                    int l = 0, r = sVect.size()-1;
                    while (l <= r) {
                        int m = l + (r-l)/2;
                        if (sVect[m].getId() == inpId) {
                            sVect[m].getWageAtr().calWage(wTime[0]);
                            break;
                        }
                        if (sVect[m].getId() < inpId) l = m + 1;
                        if (sVect[m].getId() > inpId) r = m - 1;
                    }
                } else {
                    for (int i = 0; i < sVect.size(); i++) {
                        if (sVect[i].getId() == inpId) {
                            sVect[i].getWageAtr().calWage(wTime[i]);
                            break;
                        }
                    }
                }
            } else {
                for (int i = 0; i < sVect.size(); i++) {
                    sVect[i].getWageAtr().calWage(wTime[i]);
                }
            }
            cout << "[Alert] Da tinh luong!\n";
        }
        void expData() {
            cout << "[Alert] Thong tin cac nhan vien:\n";
            cout << "---------------------------------------------------------------------------------------------------------------------------------------\n";
            cout << "| " << setw(10) << "ID" << " | " << setw(20) << "Ho Ten" << " | " << setw(5) << "Age" << " | " << setw(10) << "Gender" << " | " << setw(15) << "Address" << " | " << setw(15) << "On-Position" << " | " << setw(15) << "Base Wage" << " | " << setw(20) << "Wage" << " |" << "\n";
            cout << "---------------------------------------------------------------------------------------------------------------------------------------\n";
            for (int i = 0; i < sVect.size(); i++) {
                cout << sVect[i];
                cout << "\n";
            }
            cout << "---------------------------------------------------------------------------------------------------------------------------------------\n";
        }
        //Addition Function: 
        int getStaff(string inpId) {
            if (mode == "ID") {
                int l = 0, r = sVect.size()-1;
                while (l <= r) {
                    int m = l + (r-l)/2;
                    if (sVect[m].getId() == inpId) {
                        return m;
                    }
                    if (sVect[m].getId() < inpId) l = m + 1;
                    if (sVect[m].getId() > inpId) r = m - 1;
                }
            } else {
                for (int i = 0; i < sVect.size(); i++) {
                    if (sVect[i].getId() == inpId) {
                        return i;
                    }
                }
            }
            return -1;
        }
};

bool idCmp(Staff a, Staff b) { 
    return a.getId() < b.getId();
}
bool wageCmp(Staff a, Staff b) {
    return a < b;
}
void staffSort(vector<Staff> &v, string mode) {
    if (mode == "ID") {
        sort(v.begin(), v.end(), idCmp);
        cout << "[Alert] Data da duoc sap xep theo ID!\n";
    } else {
        sort(v.begin(), v.end(), wageCmp);
        cout << "[Alert] Data da duoc sap xep theo luong!\n";
    }
}

class App {
    private:
        StaffManage stfm;
    public:
        App() { 
            cout << "[Infor] App started!\n";
            endFunc;
        }

        void run() {
            bool check = true;
            while (check) {
                cout << "Functions:\n";
                cout << "1. Them nhan vien\n";
                cout << "2. Xoa nhan vien\n";
                cout << "3. Sua thong tin nhan vien\n";
                cout << "4. Sap xep nhan vien\n";
                cout << "5. Tim nhan vien\n";
                cout << "6. Switch mode " << "[CURR: " << stfm.getMode() << "] [NEXT: " << stfm.getNextMode() << "]\n";
                cout << "7. Tinh luong\n";
                cout << "8. Hien thi bang thong tin\n";
                cout << "9. Exit\n";
                cout << "[Request] Chon chuc nang: ";
                int btn; cin >> btn;

                if (btn == 1) {
                    cout << "[Request] Nhap so luong nhan vien: ";
                    int n; cin >> n;
                    cin.ignore();
                    for (int i = 0; i < n; i++) {
                        Staff inpStaff;
                        cin >> inpStaff;
                        stfm.getInp(inpStaff);
                    }
                    endFunc;
                }

                if (btn == 2) {
                    cin.ignore();
                    cout << "[Request] Nhap ID nhan vien can xoa: ";
                    string inpId; getline(cin, inpId);
                    stfm.del(inpId);
                    endFunc;
                }

                if (btn == 3) {
                    cin.ignore();
                    cout << "[Request] Nhap ID cua nhan vien can sua: ";
                    string inpId; getline(cin, inpId);
                    cout << "[Request] Nhap loai thong tin can sua [ID] / [Name] / [Age] / [Gender] / [Address] / [OnPos] / [Wage]\nLua chon: ";
                    string inpType; getline(cin, inpType);
                    if (inpType == "ID") {
                        cout << "[Request] Nhap ID thay the: ";
                        string fixId; getline(cin, fixId);
                        stfm.changeInfor(inpType, inpId, fixId, "#", -1, "#", "#", "#", -1);
                    } else if (inpType == "Name") {
                        cout << "[Request] Nhap ten thay the: ";
                        string fixName; getline(cin, fixName);
                        stfm.changeInfor(inpType, inpId, "#", fixName, -1, "#", "#", "#", -1);
                    } else if (inpType == "Age") {
                        cout << "[Request] Nhap tuoi thay the: ";
                        int fixAge; cin >> fixAge;
                        stfm.changeInfor(inpType, inpId, "#", "#", fixAge, "#", "#", "#", -1);
                    } else if (inpType == "Gender") {
                        cout << "[Request] Nhap gioi tinh thay the: ";
                        string fixGender; getline(cin, fixGender);
                        stfm.changeInfor(inpType, inpId, "#", "#", -1, fixGender, "#", "#", -1);
                    } else if (inpType == "Address") {
                        cout << "[Request] Nhap dia chi thay the: ";
                        string fixAddress; getline(cin, fixAddress);
                        stfm.changeInfor(inpType, inpId, "#", "#", -1, "#", fixAddress, "#", -1);
                    } else if (inpType == "OnPos") {
                        cout << "[Request] Nhap vi tri lam viec thay the: ";
                        string fixOnPos; getline(cin, fixOnPos);
                        stfm.changeInfor(inpType, inpId, "#", "#", -1, "#", "#", fixOnPos, -1);
                    } else if (inpType == "Wage") {
                        cout << "[Request] Nhap luong thay the: ";
                        double fixWage; cin >> fixWage;
                        stfm.changeInfor(inpType, inpId, "#", "#", -1, "#", "#", "#", fixWage);
                    } else {
                        cout << "[Error] Khong co chuc nang nay\n";
                    }

                    endFunc;
                }

                if (btn == 4) {
                    cin.ignore();
                    cout << "[Request] Co 2 che do sap xep - [ID] / [Wage]. Lua chon: ";
                    string inpMode; getline(cin, inpMode);
                    staffSort(stfm.getData(), inpMode);
                    endFunc;
                }

                if (btn == 5) {
                    cin.ignore();
                    cout << "[Request] Co 2 loai tim kiem - [ID] / [Name]. Lua chon: ";
                    string inpType; getline(cin, inpType);
                    if (inpType == "ID") {
                        cout << "[Request] Nhap ID de tim kiem: ";
                        string inpId; getline(cin, inpId);
                        stfm.findById(inpId);
                    } else if (inpType == "Name") {
                        cout << "[Request] Nhap ten de tim kiem: ";
                        string inpName; getline(cin, inpName);
                        stfm.findByName(inpName);
                    } else {
                        cout << "[Error] Khong co chuc nang nay\n";
                    }
                    endFunc;
                }

                if (btn == 6) {
                    stfm.switchMode();
                    staffSort(stfm.getData(), stfm.getMode());
                    endFunc;    
                }

                if (btn == 7) {
                    cin.ignore();
                    cout << "[Request] Chon kieu tinh luong [One] / [All]: ";
                    string type; getline(cin, type);
                    string inpId = "#";
                    vector<float> inpTime(stfm.getData().size());
                    if (type == "One") {
                        getline(cin, inpId);
                        cin >> inpTime[0];
                    } else if (type == "All") {
                        cout << "[Request] Nhap thoi gian lam viec cho " << stfm.getData().size() << " nhan vien\n";
                        for (int i = 0; i < stfm.getData().size(); i++) {
                            cin >> inpTime[i];
                        }
                    } else {
                        cout << "[Error] Khong co chuc nang nay\n";
                        continue ;
                    }
                    stfm.calWage(type, inpId, inpTime);
                    endFunc;
                }

                if (btn == 8) {
                    stfm.expData();
                    endFunc;
                }

                if (btn == 9) {
                    cout << "[Infor] Shut down!" << "\n";
                    check = false;
                }

                if (btn <= 0 || btn > 9) {
                    cout << "[Error] Khong co chuc nang nay!" << "\n";
                    endFunc;
                }
            }
        }
};

Shelter() {
    App func;
    func.run();
}