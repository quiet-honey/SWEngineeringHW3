#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

//��������Entity
class ApplyInfo {
private:
	string companyName;
	string bizNum;
	string work;
	int numOfPeople;
	string deadline;

public:
	ApplyInfo(string companyName, string bizNum, string work, int numOfPeople, string deadline) :
		companyName(companyName),
		bizNum(bizNum),
		work(work),
		numOfPeople(numOfPeople),
		deadline(deadline) {
	}
	void setCompanyName(string companyName) { this->companyName = companyName; }
	void setbizNum(string bizNum) { this->bizNum = bizNum; }
	void setWork(string task) { this->work = work; }
	void setNumOfPeople(int companyName) { this->numOfPeople = numOfPeople; }
	void setDeadline(string deadline) { this->deadline = deadline; }

	string getCompanyName() { return companyName; }
	string getBizNum() { return bizNum; }
	string getWork() { return work; }
	int getNumOfPeople() { return numOfPeople; }
	string getDeadline() { return deadline; }
};


//����
class ApplyUI {
public:
	static void apply(string bizNum) ;
};

class Apply {
public:
	static void addNewApply(string bizNum);
};


//4.3 ����������ȸUI
class ApplyInquiryUI {
public:
	static vector<ApplyInfo> selectApplyInfo();
	static void startInterface() { cout << "4.3 \n"; };
};

//4.3 ����������ȸ
class ApplyInquiry {
public:
	static vector<ApplyInfo> showApplyInfo() ;
};




//4.4 �������UI
class CancelApplyInfoUI {
public:
	static ApplyInfo cancelApplyInfo(string bizNum);
	static void startInterface() { cout << "4.4 \n"; };
};

//4.4 �������
class CancelApplyInfo {
public:
	static ApplyInfo cancelApply(string bizNum);
};


//5.1 �Ϲ�ȸ�����
class GetApplyNumUI {
public:
	static map<string, int> showApplyNumInfo() ;
	static void startInterface() { cout << "5.1 \n"; };
};

class GetApplyNum {
public:
	static map<string, int> showApplyNum() ;
};

//ȸ��ȸ�����
class BizMemberNumUI {

};

