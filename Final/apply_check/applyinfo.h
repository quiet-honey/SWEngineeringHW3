#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "member.h"
#include "recruitment.h"
using namespace std;

// 지원 정보 class
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

// 지원 정보 리스트 class
class ApplyInfoList {
private:
	static vector<ApplyInfo*> applyInfoList; // 지원 정보가 저장될 vector
public:
	static void addRecruitment(ApplyInfo*); // 채용 지원을 위한 operation
	static vector<ApplyInfo*> getApplyListInfo(); // 지원 정보 조회를 위한 operation
	static Recruitment* removeApplyInfo(string); // 지원 취소를 위한 operation
	static map<string, int> getStatistic(); // 지원 정보 통계를 위한 operation
};

// 채용 지원 Boundary Class
class ApplyUI {
public:
	static void apply(Member*, Recruitment*);
};

// 채용 지원 Control Class
class Apply {
public:
	static void addNewApply(Member*, Recruitment*);
};

// 지원 정보 조회 Boundary Class
class ApplyInquiryUI {
public:
	static vector<ApplyInfo*> selectApplyInfo();
};

// 지원 정보 조회 Control Class
class ApplyInquiry {
public:
	static vector<ApplyInfo*> showApplyInfo();
};

// 지원 취소 Boundary Class
class CancelApplyInfoUI {
public:
	static Recruitment* cancelApplyInfo(string);
};

// 지원 취소 Control Class
class CancelApplyInfo {
public:
	static Recruitment* cancelApply(string);
};

// 지원 정보 통계 (일반회원) Boundary Class
class GetApplyNumUI {
public:
	static map<string, int> showApplyNumInfo();
};

// 지원 정보 통계 (일반회원) Control Class
class GetApplyNum {
public:
	static map<string, int> showApplyNum();
};