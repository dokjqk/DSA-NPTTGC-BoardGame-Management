// DSA-NPTTGC-BoardGame-Manager.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include "Member.h"
#include "MemberList.h"

int main() {
    std::cout << "testing member class" << std::endl;

    Member m1(1, "alice");
    Member m2(2, "bob");
    Member m3(3, "charlie");

    m1.display();
    m2.display();
    m3.display();

    std::cout << "\ntesting memberlist class" << std::endl;

    MemberList memberList;

    std::cout << "\nadding members..." << std::endl;
    memberList.addMember(m1);
    memberList.addMember(m2);
    memberList.addMember(m3);

    std::cout << "\ndisplaying all members:" << std::endl;
    memberList.displayAll();

    std::cout << "\nfinding member of id 2:" << std::endl;
    Member* found = memberList.findById(2);
    if (found != nullptr) {
        found->display();
    }
    else {
        std::cout << "member not found" << std::endl;
    }

    std::cout << "\nremoving member with id 1" << std::endl;
    memberList.removeMember(1);

    std::cout << "\ndisplaying all members after removing:" << std::endl;
    memberList.displayAll();

    std::cout << "\nfinding removed member with id 1:" << std::endl;
    found = memberList.findById(1);
    if (found == nullptr) {
        std::cout << "member not found (correct)" << std::endl;
    }

    std::cout << "\ndone" << std::endl;

    return 0;
}

