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
    vector<ApplyInfo> applyInfos; // applyInfos 벡터 컨테이너에 ApplyInfo 저장
public:
    const string& getId();
    const string& getPw();

    Member(const string& name, const string& id, const string& pw)
        : name(name), id(id), pw(pw) {}

    void apply(const ApplyInfo& applyInfo) {
        applyInfos.push_back(applyInfo);
        //increaseApplyNum(); // 벡터에 저장 될 때마다 지원 횟수 증가시킴. 없어도 될수도 있음
    }

    int getApplyNum() const {
        return applyInfos.size();
    }

    vector<ApplyInfo> showApplyInfo() {
        cout << "4.3 지원 정보 조회:\n";
        for (const ApplyInfo& applyInfo : applyInfos) {
            applyInfo.getApplyInfo();
        }
        return applyInfos;
    }

private:
    /* void increaseApplyNum() {
        // 지원 숫자 증가
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
        // 지원 횟수인데 지원될때마다 증가??
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
    cout << "회원(ID = " << members.back()->getId() << ") DB에 저장 성공\n";
}

void MemberList::removeMember(Member* target) {
    auto k = find(members.begin(), members.end(), target);
    if (k != members.end()) {
        members.erase(k);
        cout << "회원(ID = " << target->getId() << ") DB에서 삭제 성공\n";
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
    void addApplyInfo(const ApplyInfo& applyInfo) { //지원 정보 등록 함수, 생성된 ApplyInfo 인스턴스를 applyInfos벡터에 넣는다
        applyInfos.push_back(applyInfo);
    }

    void cancelApply(int index) {


    }

};

class ApplyInquiryUI {  //지원정보조회ㅣㅣㅣㅣ클래스ㅡㅡㅡㅡ
public:
    static void startInterface() {
        cout << "4.3 지원 정보 조회\n";
    }

    static vector<ApplyInfo> selectApplyInfo() {     //지원정보조회니까 입력 받는 건 없음 뱉어내야하는건 [회사이름] [사업자번호] [업무] [인원 수] [신청마감일] applyinfo 요소들
        startInterface();
        Member* currentUser = MemberList::memberList->MemberList::getCurrentUser();
        return currentUser->Member::showApplyInfo();
    }
};

class CancelApplyUI {//main에서 사업자번호(bizNum받아와야됨 그래야비교 후 취소가능
public:
    static void startInterface() {
        cout << "4.4 지원 취소\n";
    }

    static Recruitment cancelApplyInfo(int bizNum) {
        startInterface();
        //사업자번호 받아온거로 취소할거임
        return; //<---여기고쳐야됨---------------------------
    }
};

class GetRecruitNumUI {
public:
    static void startInterface() {
        cout << "5.1 지원 정보 통계\n";
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
        cout << "5.1 지원 정보 통계\n";
    }

    static int showApplyNumInfo() {
        startInterface();

        Member* currentUser = memberList->MemberList::getCurrentUser();

        return currentUser->Member::getApplyNum();
    }
};


