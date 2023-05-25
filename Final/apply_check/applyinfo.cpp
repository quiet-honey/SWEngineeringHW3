#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <map>
#include "recruitment.h"
#include "member.h"
#include "applyinfo.h"

using namespace std;

std::vector<ApplyInfo*> ApplyInfoList::applyInfoList = std::vector<ApplyInfo*>(0);

/*
	함수 이름 : ApplyInfoList::addRecruitment()
	기능	  : 지원 정보 리스트(applyInfoList)에 추가
	전달 인자 : 지원 정보(ApplyInfo*)
	반환값    : 없음
*/
void ApplyInfoList::addRecruitment(ApplyInfo* apply) {
	applyInfoList.push_back(apply);
}

/*
	함수 이름 : ApplyInfoList::getApplyListInfo()
	기능	  : 지원 정보 리스트(applyInfoList) 반환
	전달 인자 : 없음
	반환값    : 지원 정보 리스트 (vector<ApplyInfo*>)
*/
vector<ApplyInfo*> ApplyInfoList::getApplyListInfo() {
	return applyInfoList;
}

/*
	함수 이름 : ApplyInfoList::removeApplyInfo()
	기능	  : 사업자 번호를 받아 지원자가 지원을 직접 취소
	전달 인자 : 사업자 번호(bizNum)
	반환값    : 삭제된 채용 정보(Recruitment*)
*/
Recruitment* ApplyInfoList::removeApplyInfo(string bizNum) {
	Member* member = MemberList::getInstance()->getCurrentUser(); // 현재 로그인한 User 변수

	for (auto apply : applyInfoList) {
		if (apply->getNormalMember()->getId() == member->getId() && apply->getNormalMember()->getPw() == member->getPw() && apply->getRecruitment()->getBizNum() == bizNum) { // 로그인한 User가 지원한 채용이 맞고 해당 채용 정보를 찾으면
			auto iter = find(applyInfoList.begin(), applyInfoList.end(), apply);
			if (iter != applyInfoList.end()) {
				applyInfoList.erase(iter); // 지원 취소
			}
			apply->getRecruitment()->removeApplicants(); // 지원 취소했으므로 지원자 수 1 감소
			return apply->getRecruitment(); // 삭제된 채용 정보 반환
		}
	}
}

/*
	함수 이름 : ApplyInfoList::getStatistic()
	기능	  : 일반 회원에 대한 통계정보 반환
	전달 인자 : 없음
	반환값    : 통계 정보 (map<업무(string), 지원 횟수(int)>)
*/
map<string, int> ApplyInfoList::getStatistic() {
	Member* member = MemberList::getInstance()->getCurrentUser(); // 현재 로그인한 User 변수
	map<string, int> mp;

	for (auto apply : applyInfoList) {
		if (apply->getNormalMember()->getId() == member->getId() && apply->getNormalMember()->getPw() == member->getPw()) { // 로그인한 User가 맞다면
			if (mp.find(apply->getRecruitment()->getWork()) != mp.end()) { // 이미 같은 업무 분야에 지원한 적이 있다면 지원 횟수 1 증가
				++mp[apply->getRecruitment()->getWork()];
			}
			else { // 그렇지 않다면 새로운 분야 1로 map에 insert
				mp.insert({ apply->getRecruitment()->getWork(), 1 });
			}
		}
	}
	return mp;
}

/*
	함수 이름 : ApplyUI::apply()
	기능	  : Control Class 호출 (Apply::addNewApply())
	전달 인자 : 지원하는 User(Member*), 지원하려는 채용 정보(Recruitment*)
	반환값    : 없음
*/
void ApplyUI::apply(Member* normalmember, Recruitment* recruitment) {
	Apply::addNewApply(normalmember, recruitment);
}

/*
	함수 이름 : Apply::addNewApply()
	기능	  : 지원 정보를 임시로 저장하는 객체 포인터 생성, ApplyInfoList에 추가하기 위해 인자로 임시 객체 포인터 전달
	전달 인자 : 지원하는 User(Member*), 지원하려는 채용 정보(Recruitment*)
	반환값    : 없음
*/
void Apply::addNewApply(Member* normalmember, Recruitment* recruiment) {
	ApplyInfo* apply = new ApplyInfo();

	apply->setMember(normalmember);
	apply->setRecruitment(recruiment);

	ApplyInfoList::addRecruitment(apply);
}

/*
	함수 이름 : ApplyInquiryUI::selectApplyInfo()
	기능	  : Control Class 호출 (ApplyInquiry::showApplyInfo())
	전달 인자 : 없음
	반환값    : 지원 정보 리스트 (vector<ApplyInfo*>)
*/
vector<ApplyInfo*> ApplyInquiryUI::selectApplyInfo() {
	return ApplyInquiry::showApplyInfo();
}

/*
	함수 이름 : ApplyInquiry::showApplyInfo()
	기능	  : ApplyInfoList에서 지원 정보 리스트 획득
	전달 인자 : 없음
	반환값    : 지원 정보 리스트 (vector<ApplyInfo*>)
*/
vector<ApplyInfo*> ApplyInquiry::showApplyInfo() {
	return ApplyInfoList::getApplyListInfo();
}

/*
	함수 이름 : CancelApplyInfoUI::cancelApplyInfo()
	기능	  : Control Class 호출 (CancelApplyInfo::cancelApply())
	전달 인자 : 사업자 번호(bizNum)
	반환값    : 삭제된 채용 정보(Recruitment*)
*/
Recruitment* CancelApplyInfoUI::cancelApplyInfo(string bizNum) {
	return CancelApplyInfo::cancelApply(bizNum);
}

/*
	함수 이름 : CancelApplyInfo::cancelApply()
	기능	  : ApplyInfoList에 지원 취소를 위하여 사업자 번호(bizNum) 전달
	전달 인자 : 사업자 번호(bizNum)
	반환값    : 삭제된 채용 정보(Recruitment*)
*/
Recruitment* CancelApplyInfo::cancelApply(string bizNum) {
	return ApplyInfoList::removeApplyInfo(bizNum);
}

/*
	함수 이름 : GetApplyNumUI::showApplyNumInfo()
	기능	  : Control Class 호출 (GetApplyNum::showApplyNum())
	전달 인자 : 없음
	반환값    : 통계 정보 (map<업무(string), 지원 횟수(int)>)
*/
map<string, int> GetApplyNumUI::showApplyNumInfo() {
	return GetApplyNum::showApplyNum();
}

/*
	함수 이름 : GetApplyNum::showApplyNum()
	기능	  : ApplyInfoList에 통계 정보 획득
	전달 인자 : 없음
	반환값    : 통계 정보 (map<업무(string), 지원 횟수(int)>)
*/
map<string, int> GetApplyNum::showApplyNum() {
	return ApplyInfoList::getStatistic();
}