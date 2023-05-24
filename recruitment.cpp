#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <tuple>
#include "recruitment.h"
using namespace std;

std::vector<Recruitment*> RecruitmentList::recruitments = std::vector<Recruitment*>(0);

void RecruitmentList::addRecruitment(Recruitment* recruitment) {
    recruitments.push_back(recruitment);
}

void AddRecruitInfo::addNewRecruit(char* work, int num, char* deadline) {
    Recruitment* r = new Recruitment();
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