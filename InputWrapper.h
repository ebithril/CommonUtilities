#pragma once

#pragma comment(lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")

#include <dinput.h>

namespace CommonUtilities
{
	struct MousePosition
	{
		float myX = 0;
		float myY = 0;
	};

	class InputWrapper
	{
	public:
		InputWrapper(HINSTANCE aInstance, HWND aHwnd);
		~InputWrapper();
		void Update();
		const bool KeyPressedThisFrame(unsigned char aKey) const;
		const bool KeyReleased(unsigned char aKey) const;
		const bool IsPressingKey(unsigned char aKey) const;
		 
		const bool MouseButtonPressedThisFrame(int aButton) const;
		const bool MouseButtonReleased(int aButton) const;
		const bool IsPressingMouseButton(int aButton) const;

		const MousePosition &GetMousePostition() const;
	private:
		void UpdateMousePosition();
		void UpdatePreviousState();
		void UpdateCurrentState();

		LPDIRECTINPUTDEVICE8 myKeyboard;
		LPDIRECTINPUTDEVICE8 myMouse;

		unsigned char myKeyboardState[256];
		DIMOUSESTATE myMouseState;

		unsigned char myPreviousKeyboardState[256];
		DIMOUSESTATE myPreviousMouseState;

		MousePosition myMousePosition;

		HWND myHwnd;
	};
}