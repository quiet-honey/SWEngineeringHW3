#pragma once
#include <iostream>
#include <vector>

using namespace std;

class Member {
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
    NormalMember(char* name, char* ssn, char* id, char* pw) : Member(name, id, pw), ssn(ssn), applyNum(0) {}
};

class BizMember:public Member{
private:
    char* bizNum;
public:
    BizMember(char* name, char* bizNum, char* id, char* pw) : Member(name, id, pw), bizNum(bizNum) {}
};

class signUpUI
{
public:
    void startInterface();
    static void signUp(char* memberType, char* name, char* num, char* id, char* pw);
    static void signUpSuccess(char* memberType, char* name, char* num, char* id, char* pw);
};

class signUp
{
public:
    static void addNewMember(char* memberType, char* name, char* num, char* id, char* pww);
};


class withdrawalUI
{
public:
    void startInterface();
    static char* withdrawal();
    static char* withdrawalSuccess(char* id);
};

class withdrawal
{
public:
    static char* deleteMember();
};

class logoutUI
{
public:
    void startInterface();
    static char* logout();
    static char* logoutSuccess(char* id);
};

class logout
{
public:
    static char* logoutRequest();
};

class loginUI
{
public:
    void startInterface();
    static void login(char* id, char* pw);
    static void loginSuccess(char* id, char* pw);
    static void loginFail();
};

class login
{
public:
    static void loginRequest(char* id, char* pw);
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
    Member* findMemberById(char* id);
};