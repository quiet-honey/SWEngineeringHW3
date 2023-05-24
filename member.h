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
    const string& getId();
    const string& getPw();

    Member(const string& name, const string& id, const string& pw)
        : name(name), id(id), pw(pw) {}
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
};
/*class Member {
protected:
    char* name;
    char* id;
    char* pw; 
public:
    char* getId();
    char* getPw();

    Member(char* name, char* id, char* pw)
        : name(name), id(id), pw(pw){};
};

class NormalMember:public Member{
private:
    char* ssn;
    int applyNum;
public:
    NormalMember(char* name, char* ssn, char* id, char* pw) : Member(name, id, pw), ssn(ssn), applyNum(0) {
        cout << "나는 일반 회원" << "\n";
    }
};

class BizMember:public Member{
private:
    char* bizNum;
public:
    BizMember(char* name, char* bizNum, char* id, char* pw) : Member(name, id, pw), bizNum(bizNum) {
        cout << "나는 회사 회원" << "\n";
    }
};*/

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