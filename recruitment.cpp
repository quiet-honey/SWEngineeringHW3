#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <tuple>
#include "recruitment.h"
using namespace std;

vector<Recruitment*> RecruitmentList::recruitments = vector<Recruitment*>(0);

void RecruitmentList::addRecruitment(Recruitment* recruitment) {
    recruitments.push_back(recruitment);
}

void Recruitment::setCompany()
{
    MemberList* memberList = MemberList::getInstance();
    company = memberList->getCurrentUser()->getName();
}

void Recruitment::setBizNum() {
    MemberList* memberList = MemberList::getInstance();
    Member* currentUser = memberList->getCurrentUser();
    BizMember* bizMember = dynamic_cast<BizMember*>(currentUser);
    if (bizMember != nullptr) {
        const string& bizNum = bizMember->getBizNum();
        // bizNum »ç¿ë
        cout << bizNum << "\n";
    }
}

void AddRecruitInfo::addNewRecruit(char* work, int num, char* deadline) {
    Recruitment* r = new Recruitment();
    r->setCompany();
    //r->setBizNum();
    r->setWork(work);
    r->setNumberOfRecruit(num);
    r->setDeadline(deadline);

    RecruitmentList::addRecruitment(r);
}

void AddRecruitInfoUI::createNewRecruit(char* work, int num, char* deadline) {
    AddRecruitInfo::addNewRecruit(work, num, deadline);
}

vector<Recruitment*> RecruitInquiryUI::selectRecruitInfo() {
    return RecruitInquiry::showRecruitInfo();
}

vector<Recruitment*> RecruitInquiry::showRecruitInfo() {
    return RecruitmentList::getRecruitListinfo();
}

vector<Recruitment*> RecruitmentList::getRecruitListinfo() {
    return recruitments;
}