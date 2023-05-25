#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "member.h"
#include "recruitment.h"
using namespace std;

// ���� ���� class
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

// ���� ���� ����Ʈ class
class ApplyInfoList {
private:
	static vector<ApplyInfo*> applyInfoList; // ���� ������ ����� vector
public:
	static void addRecruitment(ApplyInfo*); // ä�� ������ ���� operation
	static vector<ApplyInfo*> getApplyListInfo(); // ���� ���� ��ȸ�� ���� operation
	static Recruitment* removeApplyInfo(string); // ���� ��Ҹ� ���� operation
	static map<string, int> getStatistic(); // ���� ���� ��踦 ���� operation
};

// ä�� ���� Boundary Class
class ApplyUI {
public:
	static void apply(Member*, Recruitment*);
};

// ä�� ���� Control Class
class Apply {
public:
	static void addNewApply(Member*, Recruitment*);
};

// ���� ���� ��ȸ Boundary Class
class ApplyInquiryUI {
public:
	static vector<ApplyInfo*> selectApplyInfo();
};

// ���� ���� ��ȸ Control Class
class ApplyInquiry {
public:
	static vector<ApplyInfo*> showApplyInfo();
};

// ���� ��� Boundary Class
class CancelApplyInfoUI {
public:
	static Recruitment* cancelApplyInfo(string);
};

// ���� ��� Control Class
class CancelApplyInfo {
public:
	static Recruitment* cancelApply(string);
};

// ���� ���� ��� (�Ϲ�ȸ��) Boundary Class
class GetApplyNumUI {
public:
	static map<string, int> showApplyNumInfo();
};

// ���� ���� ��� (�Ϲ�ȸ��) Control Class
class GetApplyNum {
public:
	static map<string, int> showApplyNum();
};