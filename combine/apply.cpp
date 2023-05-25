#include "apply.h"
#include "member.h"
#include "recruitment.h"


//����
ApplyInfo ApplyUI::apply(string bizNum) {
	return Apply::addNewApply(bizNum);
}

ApplyInfo Apply::addNewApply(string bizNum) {
	vector<Recruitment*> recruitments = RecruitmentList::getRecruitListinfo();

	ApplyInfo a("","", "", 0, "");
	MemberList* memberList = MemberList::getInstance();

	for (auto recruit : recruitments) {
		if (recruit->getBizNum() == bizNum)
		{
			a.setbizNum(bizNum);
			a.setCompanyName(recruit->getCompany());
			a.setWork(recruit->getWork());
			a.setNumOfPeople(recruit->getNumberOfRecruit());
			a.setDeadline(recruit->getDeadline());
			recruit->setNumberOfApplicants(true);
		}
	}

	memberList->getCurrentUser()->putRegistration(a);

	return a;

}


//4.3 ���� ���� ��ȸ
vector<ApplyInfo> ApplyInquiryUI::selectApplyInfo() {
	ApplyInquiryUI::startInterface();
	return ApplyInquiry::showApplyInfo();
}

vector<ApplyInfo> ApplyInquiry::showApplyInfo() {
	Member* currentUser = MemberList::getInstance()->getCurrentUser();
	return currentUser->Member::applyList();
}

//4.4 ���� ���
ApplyInfo CancelApplyInfoUI::cancelApplyInfo(string bizNum) {
	CancelApplyInfoUI::startInterface();
	return CancelApplyInfo::cancelApply(bizNum);
}

ApplyInfo CancelApplyInfo::cancelApply(string bizNum) {
	Member* currentUser = MemberList::getInstance()->getCurrentUser();

	vector<Recruitment*> recruitments = RecruitmentList::getRecruitListinfo();

	for (auto recruit : recruitments) {
		if (recruit->getBizNum() == bizNum)
			recruit->setNumberOfApplicants(false);
	}
	
	return currentUser->Member::removeApplyInfo(bizNum);
}



//5.1 ���� ���� ���
map<string, int> GetApplyNumUI::showApplyNumInfo() {
	GetApplyNumUI::startInterface();
	return GetApplyNum::showApplyNum();
}

map<string, int> GetApplyNum::showApplyNum() {
	Member* currentUser = MemberList::getInstance()->getCurrentUser();
	return currentUser->Member::getApplyNum();
}
