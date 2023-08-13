#include "helpers/InputHelper.h"
#include "logger/Logger.hpp"

nn::hid::NpadBaseState InputHelper::prevControllerState{};
nn::hid::NpadBaseState InputHelper::curControllerState{};

nn::hid::KeyboardState InputHelper::curKeyboardState{};
nn::hid::KeyboardState InputHelper::prevKeyboardState{};

nn::hid::MouseState InputHelper::curMouseState{};
nn::hid::MouseState InputHelper::prevMouseState{};

nn::hid::TouchScreenState<HID_TOUCH_MAX_TOUCHES> InputHelper::curTouchState{};
nn::hid::TouchScreenState<HID_TOUCH_MAX_TOUCHES> InputHelper::prevTouchState{};

ulong InputHelper::selectedPort = -1;
bool InputHelper::isReadInput = true;
bool InputHelper::toggleInput = false;

void InputHelper::initKBM() {
  nn::hid::InitializeKeyboard();
  nn::hid::InitializeMouse();
}

void InputHelper::updatePadState() {
  prevControllerState = curControllerState;
  tryGetContState(&curControllerState, selectedPort);

  prevKeyboardState = curKeyboardState;
  nn::hid::GetKeyboardState(&curKeyboardState);

  prevMouseState = curMouseState;
  nn::hid::GetMouseState(&curMouseState);

  prevTouchState = curTouchState;
  nn::hid::GetTouchScreenState<HID_TOUCH_MAX_TOUCHES>(&curTouchState);

//  if (isHoldZR() && isHoldR() && isPressPadUp()) {
//    toggleInput = !toggleInput;
//  }
  if ((isHoldLeftStick() && isPressRightStick()) || (isHoldRightStick() && isPressLeftStick())) {
    toggleInput = !toggleInput;
  }
}

bool InputHelper::tryGetContState(nn::hid::NpadBaseState *state, ulong port) {

  nn::hid::NpadStyleSet styleSet = nn::hid::GetNpadStyleSet(port);
  isReadInput = true;
  bool result = true;

  nn::hid::GetNpadState((nn::hid::NpadFullKeyState *) state, port);

  if (styleSet.isBitSet(nn::hid::NpadStyleTag::NpadStyleFullKey)) {
    nn::hid::GetNpadState((nn::hid::NpadFullKeyState *) state, port);
  } else if (styleSet.isBitSet(nn::hid::NpadStyleTag::NpadStyleHandheld)) {
    nn::hid::GetNpadState((nn::hid::NpadHandheldState *) state, port);
  } else if (styleSet.isBitSet(nn::hid::NpadStyleTag::NpadStyleJoyDual)) {
    nn::hid::GetNpadState((nn::hid::NpadJoyDualState *) state, port);
  } else {
    result = false;
  }

  isReadInput = false;

  return result;

}

bool InputHelper::isButtonHold(nn::hid::NpadButton button) {
  return curControllerState.mButtons.isBitSet(button);
}

bool InputHelper::isButtonPress(nn::hid::NpadButton button) {
  return curControllerState.mButtons.isBitSet(button) && !prevControllerState.mButtons.isBitSet(button);
}

bool InputHelper::isButtonRelease(nn::hid::NpadButton button) {
  return !curControllerState.mButtons.isBitSet(button) && prevControllerState.mButtons.isBitSet(button);
}

bool InputHelper::isKeyHold(nn::hid::KeyboardKey key) {
  return curKeyboardState.keys.isBitSet(key);
}

bool InputHelper::isKeyPress(nn::hid::KeyboardKey key) {
  return curKeyboardState.keys.isBitSet(key) && !prevKeyboardState.keys.isBitSet(key);
}

bool InputHelper::isKeyRelease(nn::hid::KeyboardKey key) {
  return !curKeyboardState.keys.isBitSet(key) && prevKeyboardState.keys.isBitSet(key);
}

bool InputHelper::isMouseHold(nn::hid::MouseButton button) {
  return curMouseState.buttons.isBitSet(button);
}

bool InputHelper::isMousePress(nn::hid::MouseButton button) {
  return curMouseState.buttons.isBitSet(button) && !prevMouseState.buttons.isBitSet(button);
}

bool InputHelper::isMouseRelease(nn::hid::MouseButton button) {
  return !curMouseState.buttons.isBitSet(button) && prevMouseState.buttons.isBitSet(button);
}

void InputHelper::getMouseCoords(float *x, float *y) {
  *x = curMouseState.x;
  *y = curMouseState.y;
}

void InputHelper::getScrollDelta(float *x, float *y) {
  *x = curMouseState.wheelDeltaX;
  *y = curMouseState.wheelDeltaY;
}

bool InputHelper::getTouchCoords(float *x, float *y) {
  if (curTouchState.count < 1) {
    return false;
  }
  auto touch = &curTouchState.touches[0];
  *x = touch->X;
  *y = touch->Y;
  return true;
}

bool InputHelper::isTouchPress() {
  return curTouchState.count >= 1 && prevTouchState.count < 1;
}

bool InputHelper::isTouchRelease() {
  return curTouchState.count < 1 && prevTouchState.count >= 1;
}