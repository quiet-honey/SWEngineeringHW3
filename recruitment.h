#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Recruitment{
private:
    string work;
    string deadline;
    int numberOfRecruit;
public:
    Recruitment(char*, int, char*);
};

class RecruitmentList{
private:
    static vector<Recruitment*> recruitments;
public:
    static void addRecruitment(Recruitment*);
    static void getRecruitListinfo();
};

class AddRecruitInfoUI{
public:
    static void createNewRecruit(char*, int, char*);
    static void startInterface();
};

class AddRecruitInfo{
public:
    static void addNewRecruit(char*, int, char*);
};

class RecruitInquiryUI{
public:
    static void selectRecruitInfo();
    static void startInterface();
};

class RecruitInquiry{
public:
    static void showRecruitInfo();
};