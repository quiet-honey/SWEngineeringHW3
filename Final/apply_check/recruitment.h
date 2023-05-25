#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "member.h"
using namespace std;

// 채용 정보 class
class Recruitment {
private:
    string company;
    string bizNum;
    string work;
    int numberOfApplicants = 0; // 지원자 수
    int numberOfRecruit; // 모집 인원
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

    void addApplicants() { ++numberOfApplicants; } // 지원자 수 1 증가를 위한 operation
    void removeApplicants() { --numberOfApplicants; } // 지원자 수 1 감소를 위한 operation
};

// 채용 정보 리스트 class
class RecruitmentList {
private:
    static vector<Recruitment*> recruitments; // 채용 정보가 저장될 vector
public:
    static void addRecruitment(Recruitment*);
    static vector<Recruitment*> getRecruitListinfo();
};

// 채용 정보 등록 Boundary Class
class AddRecruitInfoUI {
public:
    static void createNewRecruit(char*, int, char*);
};

// 채용 정보 등록 Control Class
class AddRecruitInfo {
public:
    static void addNewRecruit(char*, int, char*);
};

// 채용 정보 리스트 조회 Boundary Class
class RecruitInquiryUI {
public:
    static vector<Recruitment*> selectRecruitInfo();
};

// 채용 정보 리스트 조회 Control Class
class RecruitInquiry {
public:
    static vector<Recruitment*> showRecruitInfo();
};

// 채용 정보 검색 Boundary Class
class GetRecruitmentUI {
public:
    static vector<Recruitment*> showRecruitment();
};

// 채용 정보 검색 Control Class
class GetRecruitment {
public:
    static vector<Recruitment*> showRecruitmentDetail();
};

// 지원 정보 통계 (회사회원) Boundary Class
class GetRecruitNumUI {
public:
    static vector<Recruitment*> showRecruitNumInfo();
};

// 지원 정보 통계 (회사회원) Control Class
class GetRecruitNum {
public:
    static vector<Recruitment*> showRecruitNum();
};