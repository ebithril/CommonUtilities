#include "stdafx.h"
#include "InputWrapper.h"

CommonUtilities::InputWrapper::InputWrapper(HINSTANCE aInstance, HWND aHwnd)
{
	IDirectInput8 *directInputInterface;
	DirectInput8Create(aInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, reinterpret_cast<void**>(&directInputInterface), 0);

	directInputInterface->CreateDevice(GUID_SysKeyboard, &myKeyboard, nullptr);
	directInputInterface->CreateDevice(GUID_SysMouse, &myMouse, nullptr);

	myKeyboard->SetDataFormat(&c_dfDIKeyboard);
	myMouse->SetDataFormat(&c_dfDIMouse);

	myKeyboard->SetCooperativeLevel(aHwnd, DISCL_NONEXCLUSIVE);
	myMouse->SetCooperativeLevel(aHwnd, DISCL_NONEXCLUSIVE);

	myKeyboard->Acquire();
	myMouse->Acquire();

	myHwnd = aHwnd;

	UpdateCurrentState();
}

CommonUtilities::InputWrapper::~InputWrapper()
{
	myKeyboard->Unacquire();
	myMouse->Unacquire();
}

void CommonUtilities::InputWrapper::Update()
{
	UpdatePreviousState();

	myKeyboard->Acquire();
	myMouse->Acquire();

	UpdateCurrentState();

	UpdateMousePosition();
}

void CommonUtilities::InputWrapper::UpdateCurrentState()
{
	myKeyboard->GetDeviceState(sizeof(myKeyboardState), reinterpret_cast<void**>(&myKeyboardState));
	myMouse->GetDeviceState(sizeof(DIMOUSESTATE), reinterpret_cast<void**>(&myMouseState));
}

void CommonUtilities::InputWrapper::UpdateMousePosition()
{
	myMousePosition.myX += myMouseState.lX;
	myMousePosition.myY += myMouseState.lY;

	RECT theRect;
	GetWindowRect(myHwnd, &theRect);
	float windowWidth = static_cast<float>(theRect.right - theRect.left);
	float windowHeight = static_cast<float>(theRect.bottom - theRect.top);
	if (myMousePosition.myX < 0.f)
	{
		myMousePosition.myX = 0.f;
	}
	else if (myMousePosition.myX > windowWidth)
	{
		myMousePosition.myX = windowWidth;
	}

	if (myMousePosition.myY < 0.f)
	{
		myMousePosition.myY = 0.f;
	}
	else if (myMousePosition.myY > windowHeight)
	{
		myMousePosition.myY = windowHeight;
	}
}

void CommonUtilities::InputWrapper::UpdatePreviousState()
{
	memcpy_s(myPreviousKeyboardState, sizeof(myPreviousKeyboardState), myKeyboardState, sizeof(myKeyboardState));
	memcpy_s(&myPreviousMouseState, sizeof(myPreviousMouseState), &myMouseState, sizeof(myMouseState));
}

const bool CommonUtilities::InputWrapper::KeyPressedThisFrame(unsigned char aKey) const
{
	if ((myKeyboardState[aKey] & 0x80) != 0 && (myPreviousKeyboardState[aKey] & 0x80) == 0)
	{
		return true;
	}

	return false;
}

const bool CommonUtilities::InputWrapper::KeyReleased(unsigned char aKey) const
{
	if ((myPreviousKeyboardState[aKey] & 0x80) != 0 && (myKeyboardState[aKey] & 0x80) == 0)
	{
		return true;
	}

	return false;
}

const bool CommonUtilities::InputWrapper::IsPressingKey(unsigned char aKey) const
{
	return (myKeyboardState[aKey] & 0x80) != 0;
}

const CommonUtilities::MousePosition &CommonUtilities::InputWrapper::GetMousePostition() const
{
	return myMousePosition;
}

const bool CommonUtilities::InputWrapper::MouseButtonPressedThisFrame(int aButton) const
{
	return ((myMouseState.rgbButtons[aButton] & 0x80) != 0 && (myPreviousMouseState.rgbButtons[aButton] & 0x80) == 0);
}

const bool CommonUtilities::InputWrapper::MouseButtonReleased(int aButton) const
{
	return ((myMouseState.rgbButtons[aButton] & 0x80) == 0 && (myPreviousMouseState.rgbButtons[aButton] & 0x80) != 0);
}

const bool CommonUtilities::InputWrapper::IsPressingMouseButton(int aButton) const
{
	return (myMouseState.rgbButtons[aButton] & 0x80) != 0;
}