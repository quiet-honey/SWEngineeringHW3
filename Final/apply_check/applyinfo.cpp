#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <map>
#include "recruitment.h"
#include "member.h"
#include "applyinfo.h"

using namespace std;

std::vector<ApplyInfo*> ApplyInfoList::applyinfolist = std::vector<ApplyInfo*>(0);

void ApplyInfoList::addRecruitment(ApplyInfo* apply) {
	applyinfolist.push_back(apply);
}

void ApplyUI::apply(Member* normalmember, Recruitment* recruitment) {
	cout << "4.2. 채용 지원" << '\n';
	Apply::addNewApply(normalmember, recruitment);
}

void Apply::addNewApply(Member* normalmember, Recruitment* recruiment) {
	ApplyInfo* apply = new ApplyInfo();

	apply->setMember(normalmember);
	apply->setRecruitment(recruiment);

	ApplyInfoList::addRecruitment(apply);
}

vector<ApplyInfo*> ApplyInquiryUI::selectApplyInfo() {
	cout << "4.3. 지원정보조회" << '\n';
	return ApplyInquiry::showApplyInfo();
}

vector<ApplyInfo*> ApplyInquiry::showApplyInfo() {
	return ApplyInfoList::getApplyListInfo();
}

vector<ApplyInfo*> ApplyInfoList::getApplyListInfo(){
	return applyinfolist;
}

Recruitment* CancelApplyInfoUI::cancelApplyInfo(string bizNum) {
	cout << "4.4. 지원 취소" << '\n';
	return CancelApplyInfo::cancelApply(bizNum);
}

Recruitment* CancelApplyInfo::cancelApply(string bizNum) {
	return ApplyInfoList::removeApplyInfo(bizNum);
}

Recruitment* ApplyInfoList::removeApplyInfo(string bizNum) {
	Member* member = MemberList::getInstance()->getCurrentUser();

	for (auto apply : applyinfolist) {
		if (apply->getNormalMember()->getId() == member->getId() && apply->getNormalMember()->getPw() == member->getPw() && apply->getRecruitment()->getBizNum() == bizNum) {
			auto iter = find(applyinfolist.begin(), applyinfolist.end(), apply);
			if (iter != applyinfolist.end()) {
				applyinfolist.erase(iter);
				cout << "지원 취소 성공\n";
			}
			apply->getRecruitment()->removeApplicants();
			return apply->getRecruitment();
		}
	}
}

map<string, int> GetApplyNumUI::showApplyNumInfo() {
	return GetApplyNum::showApplyNum();
}

map<string, int> GetApplyNum::showApplyNum() {
	return ApplyInfoList::getStatistic();
}

map<string, int> ApplyInfoList::getStatistic() {
	Member* member = MemberList::getInstance()->getCurrentUser();
	map<string, int> mp;

	for (auto apply : applyinfolist) {
		if (apply->getNormalMember()->getId() == member->getId() && apply->getNormalMember()->getPw() == member->getPw()) {
			if (mp.find(apply->getRecruitment()->getWork()) != mp.end()) {
				++mp[apply->getRecruitment()->getWork()];
			}
			else {
				mp.insert({ apply->getRecruitment()->getWork(), 1 });
			}
		}
	}	
	return mp;
}