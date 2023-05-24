#include "recruitment.h"

std::vector<Recruitment*> RecruitmentList::recruitments = std::vector<Recruitment*>(0);

void RecruitmentList::addRecruitment(Recruitment* recruitment){
    recruitments.push_back(recruitment);
}

void AddRecruitInfo::addNewRecruit(char* work, int num, char* deadline){
    Recruitment* r;
    r->setWork(work);
    r->setNumberOfRecruit(num);
    r->setDeadline(deadline);

    RecruitmentList::addRecruitment(r);
}

void AddRecruitInfoUI::createNewRecruit(char* work, int num, char* deadline){
    AddRecruitInfo::addNewRecruit(work, num, deadline);
}

void RecruitInquiryUI::selectRecruitInfo(){
    RecruitInquiry::showRecruitInfo();
}

void RecruitInquiry::showRecruitInfo(){
    RecruitmentList::getRecruitListinfo();
}

void RecruitmentList::getRecruitListinfo(){
    for(auto recruit:recruitments){
        cout<<recruit->getWork()<<" "<<recruit->getNumberOfRecruit()<<" "<<recruit->getDeadline()<<'\n';
    }
}