#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "recruitment.h"
#include "member.h"
using namespace std;

std::vector<Recruitment*> RecruitmentList::recruitments = std::vector<Recruitment*>(0);

/*
    �Լ� �̸� : Recruitment::setCompany()
    ���	  : Recruitment�� company(ȸ�� �̸�) set
    ���� ���� : ����
    ��ȯ��    : ����
*/
void Recruitment::setCompany()
{
    MemberList* memberList = MemberList::getInstance();
    company = memberList->getCurrentUser()->getName();
}

/*
    �Լ� �̸� : Recruitment::setBizNum()
    ���	  : Recruitment�� bizNum(����� ��ȣ) set
    ���� ���� : ����
    ��ȯ��    : ����
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
    �Լ� �̸� : RecruitmentList::addRecruitment()
    ���	  : ä�� ���� ����Ʈ(recruitments)�� �߰�
    ���� ���� : ä�� ���� (Recruitment*)
    ��ȯ��    : ����
*/
void RecruitmentList::addRecruitment(Recruitment* recruitment) {
    recruitments.push_back(recruitment);
}

/*
    �Լ� �̸� : RecruitmentList::getRecruitListinfo()
    ���	  : ä�� ���� ����Ʈ(recruitments) ��ȯ
    ���� ���� : ����
    ��ȯ��    : ä�� ���� ����Ʈ (vector<Recruitment*>)
*/
vector<Recruitment*> RecruitmentList::getRecruitListinfo() {
    return recruitments;
}

/*
    �Լ� �̸� : AddRecruitInfoUI::createNewRecruit()
    ���	  : Control Class ȣ�� (AddRecruitInfo::addNewRecruit)
    ���� ���� : ȸ�� �̸�(char*), ���� �ο� ��(int), ��û ������(char*)
    ��ȯ��    : ����
*/
void AddRecruitInfoUI::createNewRecruit(char* work, int num, char* deadline) {
    AddRecruitInfo::addNewRecruit(work, num, deadline);
}

/*
    �Լ� �̸� : AddRecruitInfo::addNewRecruit()
    ���	  : ���ο� �ӽ� ��ü ������ ����, setting �� RecruitmentList::addRecruitment(Recruitment* )�� ���ڷ� ����
    ���� ���� : ȸ�� �̸�(char*), ���� �ο� ��(int), ��û ������(char*)
    ��ȯ��    : ����
*/
void AddRecruitInfo::addNewRecruit(char* work, int num, char* deadline) {
    // �ӽ� ��ü ������ Recruitment* r
    Recruitment* r = new Recruitment();
    r->setCompany();
    r->setBizNum();
    r->setWork(work);
    r->setNumberOfRecruit(num);
    r->setDeadline(deadline);

    // �ű� ��ü ���� ���� r�� ���ڷ� ����
    RecruitmentList::addRecruitment(r);
}

/*
    �Լ� �̸� : RecruitInquiryUI::selectRecruitInfo()
    ���	  : Control Class ȣ�� (RecruitInquiry::showRecruitInfo())
    ���� ���� : ����
    ��ȯ��    : ä�� ���� ����Ʈ (vector<Recruitment*>)
*/
vector<Recruitment*> RecruitInquiryUI::selectRecruitInfo() {
    return RecruitInquiry::showRecruitInfo();
}

/*
    �Լ� �̸� : RecruitInquiry::showRecruitInfo()
    ���	  : RecruitmentList::getRecruitListinfo() ȣ���Ͽ� ä�� ���� ����Ʈ ��ȯ
    ���� ���� : ����
    ��ȯ��    : ä�� ���� ����Ʈ (vector<Recruitment*>)
*/
vector<Recruitment*> RecruitInquiry::showRecruitInfo() {
    return RecruitmentList::getRecruitListinfo();
}

/*
    �Լ� �̸� : GetRecruitmentUI::showRecruitment()
    ���	  : Control Class ȣ�� (RecruitInquiry::showRecruitInfo())
    ���� ���� : ����
    ��ȯ��    : ä�� ���� ����Ʈ (vector<Recruitment*>)
*/
vector<Recruitment*> GetRecruitmentUI::showRecruitment() {
    return RecruitInquiry::showRecruitInfo();
}

/*
    �Լ� �̸� : GetRecruitment::showRecruitmentDetail()
    ���	  : RecruitmentList::getRecruitListinfo() ȣ���Ͽ� ä�� ���� ����Ʈ ��ȯ
    ���� ���� : ����
    ��ȯ��    : ä�� ���� ����Ʈ (vector<Recruitment*>)
*/
vector<Recruitment*> GetRecruitment::showRecruitmentDetail() {
    return RecruitmentList::getRecruitListinfo();
}

/*
    �Լ� �̸� : GetRecruitNumUI::showRecruitNumInfo()
    ���	  : Control Class ȣ�� (GetRecruitNum::showRecruitNum())
    ���� ���� : ����
    ��ȯ��    : ä�� ���� ����Ʈ (vector<Recruitment*>)
*/
vector<Recruitment*> GetRecruitNumUI::showRecruitNumInfo() {
    return GetRecruitNum::showRecruitNum();
}

/*
    �Լ� �̸� : GetRecruitNum::showRecruitNum()
    ���	  : RecruitmentList::getRecruitListinfo() ȣ���Ͽ� ä�� ���� ����Ʈ ��ȯ
    ���� ���� : ����
    ��ȯ��    : ä�� ���� ����Ʈ (vector<Recruitment*>)
*/
vector<Recruitment*>GetRecruitNum::showRecruitNum() {
    return RecruitmentList::getRecruitListinfo();
}