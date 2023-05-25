#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "member.h"
#include "recruitment.h"
using namespace std;

class ApplyInfo {
private:
	Member* normalMember;
	Recruitment* recruitment;
public:
	void setMember(Member* m) { this->normalMember = m; }
	void setRecruitment(Recruitment* r) { 
		this->recruitment = r;
		this->recruitment->addApplicants();
	}

	Recruitment* getRecruitment() { return recruitment; }
	Member* getNormalMember() { return normalMember; }
};

class ApplyInfoList {
private:
	static vector<ApplyInfo*> applyInfoList;
public:
	static void addRecruitment(ApplyInfo*);
	static vector<ApplyInfo*> getApplyListInfo();
	static Recruitment* removeApplyInfo(string);
	static map<string, int> getStatistic();
};

class ApplyUI {
public:
	static void apply(Member*, Recruitment*);
};

class Apply {
public:
	static void addNewApply(Member*, Recruitment*);
};

class ApplyInquiryUI {
public:
	static vector<ApplyInfo*> selectApplyInfo();
};

class ApplyInquiry {
public:
	static vector<ApplyInfo*> showApplyInfo();
};

class CancelApplyInfoUI {
public:
	static Recruitment* cancelApplyInfo(string);
};

class CancelApplyInfo {
public:
	static Recruitment* cancelApply(string);
};

class GetApplyNumUI {
public:
	static map<string, int> showApplyNumInfo();
};

class GetApplyNum {
public:
	static map<string, int> showApplyNum();
};