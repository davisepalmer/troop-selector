// troop-selectorv0.1.cpp : This file contains the 'main' function. Program execution begins and ends there. No headers for this btw 
// x64

// VERSION 0.2
/*
FIX: Skipping heroes sometimes (weird spacing), when on heroes activating abilities <- check personal notes for solution
Feature list on 0.3:
    - Click (0) (1) (0) for average spacing between troop
    - Memory of ^^ between closing
0.4+:
    - GUI
    - Retained memory
    - Scroll wheel and 'a' or 'd' instead of just arrow keys, maybe up and down
    - If player clicks in y = troop bar +- 50 pixels the current location changes to that
*/

#include <iostream>
#include <Windows.h>
#include <conio.h>

struct AttackSelector{
    long initXPos = 100;
    long xPos = 100; // troop 1(0) x pos
    long yPos = 100; // troop 1(0) y pos
    long spacing = 200; // spacing between troops
    bool attacking = 0; // has attack started t/f
    bool hasInitPos = 0;
    bool initPos() { // inits our troop xPos and yPos returns t/f bsed off if set yet
        std::cout << "Click the center of the first troop, second, then first again please." << std::endl;
        // on click set as xPos
        // on second click set difference as spacing
        size_t i = 0;
        while (1) {
            POINT z;
            GetCursorPos(&z);
            if (GetAsyncKeyState(VK_LBUTTON) && i == 0) {
                this->xPos = this->initXPos = z.x;
                this->yPos = z.y;
                i++;
                Sleep(150);
            }
            else if (GetAsyncKeyState(VK_LBUTTON) && i == 1) {
                this->spacing = z.x - this->xPos;
                i++;
                Sleep(150);
            }
            else if (GetAsyncKeyState(VK_LBUTTON && i >= 2)) {
                this->hasInitPos = 1;
                return 1;
            }
        }
        this->hasInitPos = 1;
        return 0;
    }; 
    void moveTroop(char dir/*, POINT currp */ ) { // Moves troop right or left // feature: typedefs for abstraction with DIRECTION: L R
        std::cout << "Begun moveTroop()" << std::endl;
        INPUT troopInput = { 0 };
        troopInput.type = INPUT_MOUSE;
        troopInput.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
        switch (dir) {
            case 'L':
                this->xPos -= spacing;
                SetCursorPos(this->xPos, this->yPos);
                break;
            case 'R':
                this->xPos += spacing;
                SetCursorPos(this->xPos, this->yPos);
                break;
        }

        SendInput(1, &troopInput, sizeof(troopInput));
        ZeroMemory(&troopInput, sizeof(troopInput));
        troopInput.type = INPUT_MOUSE;
        troopInput.mi.dwFlags = MOUSEEVENTF_LEFTUP;
        SendInput(1, &troopInput, sizeof(troopInput));
        Sleep(90);
        //SetCursorPos(currp.x, currp.y);
    };
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
        while (hWND == NULL ) {
            hWND = FindWindow(NULL, windowName);
            if (hWND != NULL)
                std::cout << "Found CoC" << std::endl;
            else
                std::cout << "Have not found CoC" << std::endl;
            Sleep(100);
        }
        
        POINT p;
        GetCursorPos(&p);
        ScreenToClient(hWND, &p);

        if (GetAsyncKeyState(VK_BACK) && !newAttack.attacking) { // BACKSPACE
            std::cout << "ATTACK HAS BEGUN" << std::endl;
            newAttack.attacking = 1;
        }

        if (newAttack.attacking && !newAttack.hasInitPos) {
            // init Troop Locs
            newAttack.initPos();
        }
        if (newAttack.attacking && newAttack.hasInitPos) {
            if (GetAsyncKeyState(VK_LEFT)) { // LEFT ARROW
                std::cout << "LArrow Pressed" << std::endl;
                newAttack.moveTroop ('L');
                SetCursorPos(p.x, p.y);
                Sleep(150);

            }
            if (GetAsyncKeyState(VK_RIGHT)) { // RIGHT ARROW
                std::cout << "RArrow Pressed" << std::endl;
                newAttack.moveTroop('R');
                SetCursorPos(p.x, p.y);
                Sleep(150);
            }
             // send back to original location
        }

        if (GetAsyncKeyState(VK_ESCAPE)) { // ESCAPE
            std::cout << "ESC Pressed" << std::endl;
            newAttack.attackFinished();
            std::cout << "Killing Program" << std::endl;
            Sleep(100);
            return 0;
        }
        
    } //end big while

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