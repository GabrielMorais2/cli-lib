#include <string.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"

int y = 6;
int incX = -1;

void printHelicopter() {
    screenSetColor(CYAN, DARKGRAY);
    screenGotoxy(0, y);
    printf(" __ _____ _____                                                                              \n");
    screenGotoxy(0, y + 1);
    printf("   |X\\___.-╨─｡_        \n");
    screenGotoxy(0, y + 2);
    printf("   ─´‾‾‷\\°★ º  ¯]─     \n");
    screenGotoxy(0, y + 3);
    printf("            ‾‾‾‾‾   \n");
}

void printTree(int position) {
    screenSetColor(GREEN, DARKGRAY);
    screenGotoxy(position, 10);
    printf("        /‾‾‾\\   \n");
    screenGotoxy(position, 11);
    printf("       /  |  \\  \n");
    screenGotoxy(position, 12);
    printf("       \\  |  /  \n");
    screenGotoxy(position, 13);
    printf("        \\ | /   \n");
    screenGotoxy(position, 14);
    printf("         \\|/    \n");
    screenGotoxy(position, 15);
    printf("          |     \n");
}

void printGround() {
    screenSetColor(GREEN, GREEN);
    screenGotoxy(0, MAXY - 1);
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||");
}

void clearTree(int position) {
    screenGotoxy(position, 10);
    printf("                ");
    screenGotoxy(position, 11);
    printf("                ");
    screenGotoxy(position, 12);
    printf("                ");
    screenGotoxy(position, 13);
    printf("                ");
    screenGotoxy(position, 14);
    printf("                ");
    screenGotoxy(position, 15);
    printf("                ");
}

void printCloud(int position, int height) {
    screenSetColor(WHITE, DARKGRAY);
    screenGotoxy(position, height);
    printf("   .--.   \n");
    screenGotoxy(position, height + 1);
    printf("  (    )  \n");
    screenGotoxy(position, height + 2);
    printf("   `--'   \n");
}

void clearCloud(int position, int height) {
    screenGotoxy(position, height);
    printf("          "); 
    screenGotoxy(position, height + 1);
    printf("          ");
    screenGotoxy(position, height + 2);
    printf("          ");
}

int main() {
    static int ch = 0;
    int treePosition1 = (MAXX / 2) - 8; 
    int treePosition2 = (MAXX / 2) + 5;
    int cloudPosition = (MAXX / 4);
    int cloudHeight = 3;
    screenInit(0);
    keyboardInit();
    timerInit(100);

    screenClear();

    printHelicopter();
    printGround();
    printCloud(cloudPosition, cloudHeight);
    screenUpdate();

    while (ch != 10) { 
        if (timerTimeOver() == 1) {
            clearTree(treePosition1);
            clearTree(treePosition2);
            clearCloud(cloudPosition, cloudHeight);

            printHelicopter();
            treePosition1 += incX;
            treePosition2 += incX;
            cloudPosition += incX;

            if (treePosition1 < MINX) {
                treePosition1 = MAXX - 10;
            }
            if (treePosition2 < MINX) {
                treePosition2 = MAXX - 25;
            }
            if (cloudPosition < MINX) {
                cloudPosition = MAXX - 15;
            }
            if (treePosition1 < treePosition2 + 6 && treePosition1 > treePosition2 - 6) {
                treePosition1 = (treePosition1 < treePosition2) ? treePosition2 + 6 : treePosition2 - 6;
            }

            printTree(treePosition1);
            printTree(treePosition2); 
            printCloud(cloudPosition, cloudHeight);
            screenUpdate();
        }
    }

    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    return 0;
}
