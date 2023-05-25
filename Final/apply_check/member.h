#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Member {
protected:
    string name;
    string id;
    string pw;
public:
    const string& getName();
    const string& getId();
    const string& getPw();

    Member(const string& name, const string& id, const string& pw)
        : name(name), id(id), pw(pw) {}
    virtual const string& getBizNum();
};

class NormalMember : public Member {
private:
    string ssn;
    int applyNum;
public:
    NormalMember(const string& name, const string& ssn, const string& id, const string& pw)
        : Member(name, id, pw), ssn(ssn), applyNum(0) {}
};

class BizMember : public Member {
private:
    string bizNum;
public:
    BizMember(const string& name, const string& bizNum, const string& id, const string& pw)
        : Member(name, id, pw), bizNum(bizNum) {}
    const string& getBizNum() override; // 오버라이딩
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
    //void printAllMembers();
};

class signUpUI
{
public:
    static void startInterface();
    static void signUp(const string& memberType, const string& name, const string& num, const string& id, const string& pw);
    static void signUpSuccess(const string& memberType, const string& name, const string& id);
};

class signUp {
public:
    static void addNewMember(const string& memberType, const string& name, const string& num, const string& id, const string& pww);
};

class withdrawalUI {
public:
    static void startInterface();
    static string withdrawal();
    static string withdrawalSuccess(const string& id);
};

class withdrawal {
public:
    static string deleteMember();
};

class loginUI {
public:
    static void startInterface();
    static void login(const string& id, const string& pw);
    static void loginSuccess(const string& id, const string& pw);
    static void loginFail();
};

class login {
public:
    static void loginRequest(const string& id, const string& pw);
};

class logoutUI {
public:
    static void startInterface();
    static string logout();
    static string logoutSuccess(const string& id);
};

class logout {
public:
    static string logoutRequest();
};