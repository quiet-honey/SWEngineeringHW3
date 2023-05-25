#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "member.h"
using namespace std;

// ä�� ���� class
class Recruitment {
private:
    string company;
    string bizNum;
    string work;
    int numberOfApplicants = 0; // ������ ��
    int numberOfRecruit; // ���� �ο�
    string deadline;
public:
    string getCompany() { return company; }
    string getBizNum() { return bizNum; }
    void setCompany();
    void setBizNum();

    string getWork() { return this->work; }
    int getNumberOfRecruit() { return this->numberOfRecruit; }
    int getNumberOfApplicants() { return this->numberOfApplicants; }
    string getDeadline() { return this->deadline; }
    void setWork(char* work) { this->work = work; }
    void setNumberOfRecruit(int num) { this->numberOfRecruit = num; }
    void setDeadline(char* deadline) { this->deadline = deadline; }

    void addApplicants() { ++numberOfApplicants; } // ������ �� 1 ������ ���� operation
    void removeApplicants() { --numberOfApplicants; } // ������ �� 1 ���Ҹ� ���� operation
};

// ä�� ���� ����Ʈ class
class RecruitmentList {
private:
    static vector<Recruitment*> recruitments; // ä�� ������ ����� vector
public:
    static void addRecruitment(Recruitment*);
    static vector<Recruitment*> getRecruitListinfo();
};

// ä�� ���� ��� Boundary Class
class AddRecruitInfoUI {
public:
    static void createNewRecruit(char*, int, char*);
};

// ä�� ���� ��� Control Class
class AddRecruitInfo {
public:
    static void addNewRecruit(char*, int, char*);
};

// ä�� ���� ����Ʈ ��ȸ Boundary Class
class RecruitInquiryUI {
public:
    static vector<Recruitment*> selectRecruitInfo();
};

// ä�� ���� ����Ʈ ��ȸ Control Class
class RecruitInquiry {
public:
    static vector<Recruitment*> showRecruitInfo();
};

// ä�� ���� �˻� Boundary Class
class GetRecruitmentUI {
public:
    static vector<Recruitment*> showRecruitment();
};

// ä�� ���� �˻� Control Class
class GetRecruitment {
public:
    static vector<Recruitment*> showRecruitmentDetail();
};

// ���� ���� ��� (ȸ��ȸ��) Boundary Class
class GetRecruitNumUI {
public:
    static vector<Recruitment*> showRecruitNumInfo();
};

// ���� ���� ��� (ȸ��ȸ��) Control Class
class GetRecruitNum {
public:
    static vector<Recruitment*> showRecruitNum();
};