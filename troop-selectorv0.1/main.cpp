// troop-selectorv0.1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


// VERSION 0.1
/*
Feature list on 0.2:
    - Click (0) (1) (0) for average spacing between troop
    - Memory of ^^ between closing
0.3+:
    - GUI
    - Retained memory
    - Autosearching (1m+ GC || EXL) (maybe different exe)
*/

#include <iostream>
#include <Windows.h>
#include <conio.h>

struct AttackSelector{
    int initXPos = 0; // troop 1(0) x pos
    int initYPos = 0; // troop 1(0) y pos
    int spacing = 0; // spacing between troops
    bool attacking = 0; // has attack started t/f
    void moveTroop(char dir) {}; // Moves troop right or left // feature: typedefs for abstraction with DIRECTION: L R
    void attackFinished() {}; // Clears all init properties // feature: auto does it based off of ending screen or troop bar going away
};


int main()
{
    AttackSelector newAttack;
    
    std::cout << "Beginning Loop:" << std::endl;
    std::cout << "INSTRUCTIONS:\n\t(1) Click Backspace when you begin your attack\n\t(2) Click the middle of the first troop, the second, then the first again.\n\n Now you can use the arrow keys to move left and right across the troops." << std::endl;
    while (1) {
        LPCWSTR windowName = L"Clash of Clans";
        HWND hWND = FindWindow(NULL, windowName);
        while (hWND == NULL) {
            hWND = FindWindow(NULL, windowName);
            std::cout << "Have not found CoC" << std::endl;
        }
        
        POINT p;
        GetCursorPos(&p);
        ScreenToClient(hWND, &p);

        if (GetAsyncKeyState(VK_BACK) && !newAttack.attacking) { // BACKSPACE
            std::cout << "ATTACK HAS BEGUN" << std::endl;
            newAttack.attacking = 1;
        }

        if (newAttack.attacking) { 
            if (GetAsyncKeyState(VK_LEFT)) { // LEFT ARROW
                std::cout << "LArrow Pressed" << std::endl;
                newAttack.moveTroop('L');
                Sleep(250);

            }
            if (GetAsyncKeyState(VK_RIGHT)) { // RIGHT ARROW
                std::cout << "RArrow Pressed" << std::endl;
                newAttack.moveTroop('R');
                Sleep(250);
            }
        }

        if (GetAsyncKeyState(VK_ESCAPE)) { // ESCAPE
            std::cout << "ESC Pressed" << std::endl;
            std::cout << "Killing Program" << std::endl;
            Sleep(100);
            return 0;
        }
        
    } //end while(1)

    std::cout << "Outside End." << std::endl;
    return 0;
}

/*
a 97
< 75
d 100
> 77
q 113
esc 27
*/