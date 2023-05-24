#include "recruitment.h"

Recruitment::Recruitment(char* work, int num, char* deadline) : work(work), numberOfRecruit(num), deadline(deadline){
    RecruitmentList::addRecruitment(this);
}

void RecruitmentList::addRecruitment(Recruitment* recruitment){
    recruitments.push_back(recruitment);
}

void AddRecruitInfo::addNewRecruit(char* work, int num, char* deadline){
    Recruitment(work, num, deadline);
}

void AddRecruitInfoUI::createNewRecruit(char* work, int num, char* deadline){
    AddRecruitInfo::addNewRecruit(work, num, deadline);
}