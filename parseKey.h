#ifndef PARSEKEY_H
#define PARSEKEY_H

#include <string.h>

// Modifiers
#define MOD_CONTROL_LEFT    (1<<0)
#define MOD_SHIFT_LEFT      (1<<1)
#define MOD_ALT_LEFT        (1<<2)
#define MOD_GUI_LEFT        (1<<3)
#define MOD_CONTROL_RIGHT   (1<<4)
#define MOD_SHIFT_RIGHT     (1<<5)
#define MOD_ALT_RIGHT       (1<<6)
#define MOD_GUI_RIGHT       (1<<7)

// Keys
#define KEY_A               4
#define KEY_1               30
#define KEY_ENTER           40
#define KEY_SPACE           44
#define KEY_F1              58
#define KEY_F2              59
#define KEY_F3              60
#define KEY_F4              61
#define KEY_F5              62
#define KEY_F6              63
#define KEY_F7              64
#define KEY_F8              65
#define KEY_F9              66
#define KEY_F10             67
#define KEY_F11             68
#define KEY_F12             69
#define KEY_UP_ARROW        0x52
#define KEY_DOWN_ARROW      0x51
#define KEY_LEFT_ARROW      0x50
#define KEY_RIGHT_ARROW     0x4F

// Typedef
typedef unsigned char byte;

typedef struct {
    byte Key;
    byte Modifier;
} KeyInfo;

byte ParseModifier(char modifier) {
    switch (modifier) {
        case '^':
            return MOD_CONTROL_LEFT;
        case '+':
            return MOD_SHIFT_LEFT;
        case '!':
            return MOD_ALT_LEFT;
        case '#':
            return MOD_GUI_LEFT;
        default:
            return 0;
    }
}

byte ParseKey(char key) {
    if ('A' <= key && key <= 'Z')
        return KEY_A + (key - 'A');
    if ('a' <= key && key <= 'z')
        return KEY_A + (key - 'a');
    if ('0' <= key && key <= '9')
        return KEY_1 + (key - '0');
    return 0;
}

byte ParseLiteralKey(char* key) {
    if (!strcmp("Enter", key))
        return KEY_ENTER;
    if (!strcmp("Space", key))
        return KEY_SPACE;
    if (!strcmp("F1", key))
        return KEY_F1;
    if (!strcmp("F2", key))
        return KEY_F2;
    if (!strcmp("F3", key))
        return KEY_F3;
    if (!strcmp("F4", key))
        return KEY_F4;
    if (!strcmp("F5", key))
        return KEY_F5;
    if (!strcmp("F6", key))
        return KEY_F6;
    if (!strcmp("F7", key))
        return KEY_F7;
    if (!strcmp("F8", key))
        return KEY_F8;
    if (!strcmp("F9", key))
        return KEY_F9;
    if (!strcmp("F10", key))
        return KEY_F10;
    if (!strcmp("F11", key))
        return KEY_F11;
    if (!strcmp("F12", key))
        return KEY_F12;
    if (!strcmp("Up", key))
        return KEY_UP_ARROW;
    if (!strcmp("Down", key))
        return KEY_DOWN_ARROW;
    if (!strcmp("Left", key))
        return KEY_LEFT_ARROW;
    if (!strcmp("Right", key))
        return KEY_RIGHT_ARROW;
    
    return 0;
}

KeyInfo ParseKeyInfo(char* keyString) {
    KeyInfo keyInfo;
    keyInfo.Key = 0;
    keyInfo.Modifier = 0;
    byte index;

    for (index = 0; index < strlen(keyString); index++) {
        char keyChar = keyString[index];
        byte parsedKey = 0;
        
        switch (keyChar) {
            case '<':
                index++;
                keyInfo.Modifier |= ParseModifier(keyString[index]);
                break;
            case '>':
                index++;
                keyInfo.Modifier |= ParseModifier(keyString[index]) << 4;
                break;
            case '{':
            {
                char keyLiteral[10];
                memset(keyLiteral, 0, 10);

                // Find the matching brace
                char* openBrace = keyString + index;
                char* closeBrace = strrchr(keyString, '}');
                strncpy(keyLiteral, openBrace + 1, closeBrace - openBrace - 1);

                // Parse it
                parsedKey = ParseLiteralKey(keyLiteral);
                if (parsedKey) {
                   keyInfo.Key = parsedKey;
                   return keyInfo;
                }
            }
            default:
                parsedKey = ParseModifier(keyChar);
                if (parsedKey) {
                    keyInfo.Modifier |= parsedKey;
                    break;
                }
                parsedKey = ParseKey(keyChar);
                if (parsedKey) {
                    keyInfo.Key = parsedKey;
                    return keyInfo;
                }
        }
    }
    // Should never get here
    return keyInfo;
}

#endif
