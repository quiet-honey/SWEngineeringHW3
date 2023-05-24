#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
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

void RecruitInquiryUI::selectRecruitInfo() {
    RecruitInquiry::showRecruitInfo();
}

void RecruitInquiry::showRecruitInfo() {
    RecruitmentList::getRecruitListinfo();
}

void RecruitmentList::getRecruitListinfo() {
    FILE* out_fp;
    out_fp = fopen("output.txt", "w+");
    for (auto recruit : recruitments) {
        fprintf(out_fp, "%s %d %s\n", recruit->getWork(), recruit->getNumberOfRecruit(), recruit->getDeadline());
        cout << recruit->getWork() << " " << recruit->getNumberOfRecruit() << " " << recruit->getDeadline() << '\n';
    }
}