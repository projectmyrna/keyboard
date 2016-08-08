#include "DigiKeyboard.h"

const byte _numIOs = 4;
const byte _pins[_numIOs] = {0, 1, 2, 5};
const byte _outputKeys[_numIOs] = {KEY_A, KEY_S, KEY_D, KEY_F};
const byte _outputModifiers[_numIOs] = {MOD_SHIFT_LEFT, MOD_SHIFT_LEFT, MOD_SHIFT_LEFT, MOD_SHIFT_LEFT};
byte _inputs[_numIOs] = {LOW, LOW, LOW, LOW};
byte _keyStates[_numIOs] = {LOW, LOW, LOW, LOW};

void setup() {
  for (int i = 0; i < _numIOs; i++)
  {
    // Set pins to input
    pinMode(_pins[i], INPUT);
    // Pull-up
    digitalWrite(_pins[i], HIGH);
  }
}

void ReadInputs()
{
  for (int i = 0; i < _numIOs; i++)
    _inputs[i] = digitalRead(_pins[i]);
}

void SendKey(int keyIndex)
{
  // Neg-edge
  if (_inputs[keyIndex] == LOW && _keyStates[keyIndex] == HIGH)
  {
    // Press
    DigiKeyboard.sendKeyPress(0);
    DigiKeyboard.sendKeyPress(_outputKeys[keyIndex], _outputModifiers[keyIndex]);
    _keyStates[keyIndex] = _inputs[keyIndex];
  }
  // Pos-edge
  else if (_inputs[keyIndex] == HIGH && _keyStates[keyIndex] == LOW)
  {
    // Release
    DigiKeyboard.sendKeyPress(0);
    _keyStates[keyIndex] = _inputs[keyIndex];
  }
}

void SendKeys()
{
  for (int i = 0; i < _numIOs; i++)
    SendKey(i);
}

void loop() {
  // this is generally not necessary but with some older systems it seems to
  // prevent missing the first character after a delay:
  //DigiKeyboard.sendKeyStroke(0);

  ReadInputs();
  SendKeys();

  DigiKeyboard.delay(25);
}
