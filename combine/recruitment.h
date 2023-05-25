#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "member.h"
using namespace std;

class Recruitment {
private:
    string company;
    string bizNum;

    string work;
    int numberOfApplicants;
    int numberOfRecruit;
    string deadline;
public:
    string getCompany() { return company; }
    string getBizNum() { return bizNum; }
    void setCompany();
    void setBizNum();

    string getWork() { return this->work; }
    int getNumberOfRecruit() { return this->numberOfRecruit; }
    string getDeadline() { return this->deadline; }
    void setWork(char* work) { this->work = work; }
    void setNumberOfRecruit(int num) { this->numberOfRecruit = num; }
    void setDeadline(char* deadline) { this->deadline = deadline; }
};

class RecruitmentList {
private:
    static vector<Recruitment*> recruitments;
public:
    static void addRecruitment(Recruitment*);
    static vector<Recruitment*> getRecruitListinfo();
};

class AddRecruitInfoUI {
public:
    static void createNewRecruit(char*, int, char*);
};

class AddRecruitInfo {
public:
    static void addNewRecruit(char*, int, char*);
};

class RecruitInquiryUI {
public:
    static vector<Recruitment*> selectRecruitInfo();
};

class RecruitInquiry {
public:
    static vector<Recruitment*> showRecruitInfo();
};