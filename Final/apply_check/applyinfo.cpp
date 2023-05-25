#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <map>
#include "recruitment.h"
#include "member.h"
#include "applyinfo.h"

using namespace std;

std::vector<ApplyInfo*> ApplyInfoList::applyInfoList = std::vector<ApplyInfo*>(0);

/*
	�Լ� �̸� : ApplyInfoList::addRecruitment()
	���	  : ���� ���� ����Ʈ(applyInfoList)�� �߰�
	���� ���� : ���� ����(ApplyInfo*)
	��ȯ��    : ����
*/
void ApplyInfoList::addRecruitment(ApplyInfo* apply) {
	applyInfoList.push_back(apply);
}

/*
	�Լ� �̸� : ApplyInfoList::getApplyListInfo()
	���	  : ���� ���� ����Ʈ(applyInfoList) ��ȯ
	���� ���� : ����
	��ȯ��    : ���� ���� ����Ʈ (vector<ApplyInfo*>)
*/
vector<ApplyInfo*> ApplyInfoList::getApplyListInfo() {
	return applyInfoList;
}

/*
	�Լ� �̸� : ApplyInfoList::removeApplyInfo()
	���	  : ����� ��ȣ�� �޾� �����ڰ� ������ ���� ���
	���� ���� : ����� ��ȣ(bizNum)
	��ȯ��    : ������ ä�� ����(Recruitment*)
*/
Recruitment* ApplyInfoList::removeApplyInfo(string bizNum) {
	Member* member = MemberList::getInstance()->getCurrentUser(); // ���� �α����� User ����

	for (auto apply : applyInfoList) {
		if (apply->getNormalMember()->getId() == member->getId() && apply->getNormalMember()->getPw() == member->getPw() && apply->getRecruitment()->getBizNum() == bizNum) { // �α����� User�� ������ ä���� �°� �ش� ä�� ������ ã����
			auto iter = find(applyInfoList.begin(), applyInfoList.end(), apply);
			if (iter != applyInfoList.end()) {
				applyInfoList.erase(iter); // ���� ���
			}
			apply->getRecruitment()->removeApplicants(); // ���� ��������Ƿ� ������ �� 1 ����
			return apply->getRecruitment(); // ������ ä�� ���� ��ȯ
		}
	}
}

/*
	�Լ� �̸� : ApplyInfoList::getStatistic()
	���	  : �Ϲ� ȸ���� ���� ������� ��ȯ
	���� ���� : ����
	��ȯ��    : ��� ���� (map<����(string), ���� Ƚ��(int)>)
*/
map<string, int> ApplyInfoList::getStatistic() {
	Member* member = MemberList::getInstance()->getCurrentUser(); // ���� �α����� User ����
	map<string, int> mp;

	for (auto apply : applyInfoList) {
		if (apply->getNormalMember()->getId() == member->getId() && apply->getNormalMember()->getPw() == member->getPw()) { // �α����� User�� �´ٸ�
			if (mp.find(apply->getRecruitment()->getWork()) != mp.end()) { // �̹� ���� ���� �о߿� ������ ���� �ִٸ� ���� Ƚ�� 1 ����
				++mp[apply->getRecruitment()->getWork()];
			}
			else { // �׷��� �ʴٸ� ���ο� �о� 1�� map�� insert
				mp.insert({ apply->getRecruitment()->getWork(), 1 });
			}
		}
	}
	return mp;
}

/*
	�Լ� �̸� : ApplyUI::apply()
	���	  : Control Class ȣ�� (Apply::addNewApply())
	���� ���� : �����ϴ� User(Member*), �����Ϸ��� ä�� ����(Recruitment*)
	��ȯ��    : ����
*/
void ApplyUI::apply(Member* normalmember, Recruitment* recruitment) {
	Apply::addNewApply(normalmember, recruitment);
}

/*
	�Լ� �̸� : Apply::addNewApply()
	���	  : ���� ������ �ӽ÷� �����ϴ� ��ü ������ ����, ApplyInfoList�� �߰��ϱ� ���� ���ڷ� �ӽ� ��ü ������ ����
	���� ���� : �����ϴ� User(Member*), �����Ϸ��� ä�� ����(Recruitment*)
	��ȯ��    : ����
*/
void Apply::addNewApply(Member* normalmember, Recruitment* recruiment) {
	ApplyInfo* apply = new ApplyInfo();

	apply->setMember(normalmember);
	apply->setRecruitment(recruiment);

	ApplyInfoList::addRecruitment(apply);
}

/*
	�Լ� �̸� : ApplyInquiryUI::selectApplyInfo()
	���	  : Control Class ȣ�� (ApplyInquiry::showApplyInfo())
	���� ���� : ����
	��ȯ��    : ���� ���� ����Ʈ (vector<ApplyInfo*>)
*/
vector<ApplyInfo*> ApplyInquiryUI::selectApplyInfo() {
	return ApplyInquiry::showApplyInfo();
}

/*
	�Լ� �̸� : ApplyInquiry::showApplyInfo()
	���	  : ApplyInfoList���� ���� ���� ����Ʈ ȹ��
	���� ���� : ����
	��ȯ��    : ���� ���� ����Ʈ (vector<ApplyInfo*>)
*/
vector<ApplyInfo*> ApplyInquiry::showApplyInfo() {
	return ApplyInfoList::getApplyListInfo();
}

/*
	�Լ� �̸� : CancelApplyInfoUI::cancelApplyInfo()
	���	  : Control Class ȣ�� (CancelApplyInfo::cancelApply())
	���� ���� : ����� ��ȣ(bizNum)
	��ȯ��    : ������ ä�� ����(Recruitment*)
*/
Recruitment* CancelApplyInfoUI::cancelApplyInfo(string bizNum) {
	return CancelApplyInfo::cancelApply(bizNum);
}

/*
	�Լ� �̸� : CancelApplyInfo::cancelApply()
	���	  : ApplyInfoList�� ���� ��Ҹ� ���Ͽ� ����� ��ȣ(bizNum) ����
	���� ���� : ����� ��ȣ(bizNum)
	��ȯ��    : ������ ä�� ����(Recruitment*)
*/
Recruitment* CancelApplyInfo::cancelApply(string bizNum) {
	return ApplyInfoList::removeApplyInfo(bizNum);
}

/*
	�Լ� �̸� : GetApplyNumUI::showApplyNumInfo()
	���	  : Control Class ȣ�� (GetApplyNum::showApplyNum())
	���� ���� : ����
	��ȯ��    : ��� ���� (map<����(string), ���� Ƚ��(int)>)
*/
map<string, int> GetApplyNumUI::showApplyNumInfo() {
	return GetApplyNum::showApplyNum();
}

/*
	�Լ� �̸� : GetApplyNum::showApplyNum()
	���	  : ApplyInfoList�� ��� ���� ȹ��
	���� ���� : ����
	��ȯ��    : ��� ���� (map<����(string), ���� Ƚ��(int)>)
*/
map<string, int> GetApplyNum::showApplyNum() {
	return ApplyInfoList::getStatistic();
}