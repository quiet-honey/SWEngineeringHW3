#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "recruitment.h"
#include "member.h"
using namespace std;

std::vector<Recruitment*> RecruitmentList::recruitments = std::vector<Recruitment*>(0);

/*
    함수 이름 : Recruitment::setCompany()
    기능	  : Recruitment의 company(회사 이름) set
    전달 인자 : 없음
    반환값    : 없음
*/
void Recruitment::setCompany()
{
    MemberList* memberList = MemberList::getInstance();
    company = memberList->getCurrentUser()->getName();
}

/*
    함수 이름 : Recruitment::setBizNum()
    기능	  : Recruitment의 bizNum(사업자 번호) set
    전달 인자 : 없음
    반환값    : 없음
*/
void Recruitment::setBizNum() {
    MemberList* memberList = MemberList::getInstance();
    Member* currentUser = memberList->getCurrentUser();
    BizMember* bizMember = dynamic_cast<BizMember*>(currentUser);
    if (bizMember != nullptr) {
        const string& bizNum = bizMember->getBizNum();
        this->bizNum = bizNum;
    }
}

/*
    함수 이름 : RecruitmentList::addRecruitment()
    기능	  : 채용 정보 리스트(recruitments)에 추가
    전달 인자 : 채용 정보 (Recruitment*)
    반환값    : 없음
*/
void RecruitmentList::addRecruitment(Recruitment* recruitment) {
    recruitments.push_back(recruitment);
}

/*
    함수 이름 : RecruitmentList::getRecruitListinfo()
    기능	  : 채용 정보 리스트(recruitments) 반환
    전달 인자 : 없음
    반환값    : 채용 정보 리스트 (vector<Recruitment*>)
*/
vector<Recruitment*> RecruitmentList::getRecruitListinfo() {
    return recruitments;
}

/*
    함수 이름 : AddRecruitInfoUI::createNewRecruit()
    기능	  : Control Class 호출 (AddRecruitInfo::addNewRecruit)
    전달 인자 : 회사 이름(char*), 모집 인원 수(int), 신청 마감일(char*)
    반환값    : 없음
*/
void AddRecruitInfoUI::createNewRecruit(char* work, int num, char* deadline) {
    AddRecruitInfo::addNewRecruit(work, num, deadline);
}

/*
    함수 이름 : AddRecruitInfo::addNewRecruit()
    기능	  : 새로운 임시 객체 포인터 생성, setting 후 RecruitmentList::addRecruitment(Recruitment* )에 인자로 전달
    전달 인자 : 회사 이름(char*), 모집 인원 수(int), 신청 마감일(char*)
    반환값    : 없음
*/
void AddRecruitInfo::addNewRecruit(char* work, int num, char* deadline) {
    // 임시 객체 포인터 Recruitment* r
    Recruitment* r = new Recruitment();
    r->setCompany();
    r->setBizNum();
    r->setWork(work);
    r->setNumberOfRecruit(num);
    r->setDeadline(deadline);

    // 신규 객체 생성 위해 r을 인자로 전달
    RecruitmentList::addRecruitment(r);
}

/*
    함수 이름 : RecruitInquiryUI::selectRecruitInfo()
    기능	  : Control Class 호출 (RecruitInquiry::showRecruitInfo())
    전달 인자 : 없음
    반환값    : 채용 정보 리스트 (vector<Recruitment*>)
*/
vector<Recruitment*> RecruitInquiryUI::selectRecruitInfo() {
    return RecruitInquiry::showRecruitInfo();
}

/*
    함수 이름 : RecruitInquiry::showRecruitInfo()
    기능	  : RecruitmentList::getRecruitListinfo() 호출하여 채용 정보 리스트 반환
    전달 인자 : 없음
    반환값    : 채용 정보 리스트 (vector<Recruitment*>)
*/
vector<Recruitment*> RecruitInquiry::showRecruitInfo() {
    return RecruitmentList::getRecruitListinfo();
}

/*
    함수 이름 : GetRecruitmentUI::showRecruitment()
    기능	  : Control Class 호출 (RecruitInquiry::showRecruitInfo())
    전달 인자 : 없음
    반환값    : 채용 정보 리스트 (vector<Recruitment*>)
*/
vector<Recruitment*> GetRecruitmentUI::showRecruitment() {
    return RecruitInquiry::showRecruitInfo();
}

/*
    함수 이름 : GetRecruitment::showRecruitmentDetail()
    기능	  : RecruitmentList::getRecruitListinfo() 호출하여 채용 정보 리스트 반환
    전달 인자 : 없음
    반환값    : 채용 정보 리스트 (vector<Recruitment*>)
*/
vector<Recruitment*> GetRecruitment::showRecruitmentDetail() {
    return RecruitmentList::getRecruitListinfo();
}

/*
    함수 이름 : GetRecruitNumUI::showRecruitNumInfo()
    기능	  : Control Class 호출 (GetRecruitNum::showRecruitNum())
    전달 인자 : 없음
    반환값    : 채용 정보 리스트 (vector<Recruitment*>)
*/
vector<Recruitment*> GetRecruitNumUI::showRecruitNumInfo() {
    return GetRecruitNum::showRecruitNum();
}

/*
    함수 이름 : GetRecruitNum::showRecruitNum()
    기능	  : RecruitmentList::getRecruitListinfo() 호출하여 채용 정보 리스트 반환
    전달 인자 : 없음
    반환값    : 채용 정보 리스트 (vector<Recruitment*>)
*/
vector<Recruitment*>GetRecruitNum::showRecruitNum() {
    return RecruitmentList::getRecruitListinfo();
}