#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Member {
protected:
    string name;
    string id;
    string pw;
    vector<ApplyInfo> applyInfos; // applyInfos ���� �����̳ʿ� ApplyInfo ����
public:
    const string& getId();
    const string& getPw();

    Member(const string& name, const string& id, const string& pw)
        : name(name), id(id), pw(pw) {}

    void apply(const ApplyInfo& applyInfo) {
        applyInfos.push_back(applyInfo);
        //increaseApplyNum(); // ���Ϳ� ���� �� ������ ���� Ƚ�� ������Ŵ. ��� �ɼ��� ����
    }

    int getApplyNum() const {
        return applyInfos.size();
    }

    vector<ApplyInfo> showApplyInfo() {
        cout << "4.3 ���� ���� ��ȸ:\n";
        for (const ApplyInfo& applyInfo : applyInfos) {
            applyInfo.getApplyInfo();
        }
        return applyInfos;
    }

private:
    /* void increaseApplyNum() {
        // ���� ���� ����
    }*/
   
};

class NormalMember : public Member {
private:
    string ssn;
    bool norm;
public:
    NormalMember(const string& name, const string& ssn, const string& id, const string& pw)
        : Member(name, id, pw), ssn(ssn), norm(true) {}

    bool isNorm() { return norm; }

    void apply(const ApplyInfo& applyInfo) {
        Member::apply(applyInfo);
    }
};

class BizMember : public Member {
private:
    string bizNum;
    bool norm;
public:
    BizMember(const string& name, const string& bizNum, const string& id, const string& pw)
        : Member(name, id, pw), bizNum(bizNum), norm(false) {}

    bool isNorm() { return norm; }

    /*
        void showRecruitNum() {
        // ���� Ƚ���ε� �����ɶ����� ����??
    }*/

};



class MemberList {
private:
    vector<Member*> members;
    Member* currentUser;
    static MemberList* instance;

    MemberList() {}

public:
    static MemberList* getInstance();
    void addMember(Member* member);
    void removeMember(Member* member);
    void setCurrentUser(Member* member);
    Member* getCurrentUser();
    Member* findMemberById(const string& id);
};

MemberList* MemberList::instance = nullptr;

MemberList* MemberList::getInstance() {
    if (!instance) {
        instance = new MemberList();
    }
    return instance;
}

void MemberList::addMember(Member* member) {
    members.push_back(member);
    cout << "ȸ��(ID = " << members.back()->getId() << ") DB�� ���� ����\n";
}

void MemberList::removeMember(Member* target) {
    auto k = find(members.begin(), members.end(), target);
    if (k != members.end()) {
        members.erase(k);
        cout << "ȸ��(ID = " << target->getId() << ") DB���� ���� ����\n";
    }
}

void MemberList::setCurrentUser(Member* member) {
    currentUser = member;
}

Member* MemberList::getCurrentUser() {
    return currentUser;
}

Member* MemberList::findMemberById(const string& id) {
    for (Member* member : members) {
        if (member->getId() == id) {
            return member;
        }
    }
    return nullptr;
}


class ApplyInfo {
private:
    string companyName;
    int bizNum;
    string task;
    int numOfPeople;
    string deadline;
public:
    ApplyInfo(const string& companyName, const int& bizNum, const string& task, int numOfPeople, const string& deadline)
        : companyName(companyName), bizNum(bizNum), task(task), numOfPeople(numOfPeople), deadline(deadline) {}

    void getApplyInfo() const {
        cout << companyName << " " << bizNum << " " << task << " " << numOfPeople << " " << deadline << "\n";

    }
};

class Recruitment {
private:
    vector<ApplyInfo> applyInfos;
public:
    void addApplyInfo(const ApplyInfo& applyInfo) { //���� ���� ��� �Լ�, ������ ApplyInfo �ν��Ͻ��� applyInfos���Ϳ� �ִ´�
        applyInfos.push_back(applyInfo);
    }

    void cancelApply(int index) {


    }

};

class ApplyInquiryUI {  //����������ȸ�ӤӤӤ�Ŭ�����ѤѤѤ�
public:
    static void startInterface() {
        cout << "4.3 ���� ���� ��ȸ\n";
    }

    static vector<ApplyInfo> selectApplyInfo() {     //����������ȸ�ϱ� �Է� �޴� �� ���� �����ϴ°� [ȸ���̸�] [����ڹ�ȣ] [����] [�ο� ��] [��û������] applyinfo ��ҵ�
        startInterface();
        Member* currentUser = MemberList::memberList->MemberList::getCurrentUser();
        return currentUser->Member::showApplyInfo();
    }
};

class CancelApplyUI {//main���� ����ڹ�ȣ(bizNum�޾ƿ;ߵ� �׷��ߺ� �� ��Ұ���
public:
    static void startInterface() {
        cout << "4.4 ���� ���\n";
    }

    static Recruitment cancelApplyInfo(int bizNum) {
        startInterface();
        //����ڹ�ȣ �޾ƿ°ŷ� ����Ұ���
        return; //<---������ľߵ�---------------------------
    }
};

class GetRecruitNumUI {
public:
    static void startInterface() {
        cout << "5.1 ���� ���� ���\n";
    }

    static int showRecruitNumInfo() {
        startInterface();
        Member* currentUser = memberList->MemberList::getCurrentUser();

        if (currentUser->isNorm() == true) {

        }


        return currentUser->Member::getApplyNum();

    }
};

class GetApplyNumUI {
public:
    static void startInterface() {
        cout << "5.1 ���� ���� ���\n";
    }

    static int showApplyNumInfo() {
        startInterface();

        Member* currentUser = memberList->MemberList::getCurrentUser();

        return currentUser->Member::getApplyNum();
    }
};


