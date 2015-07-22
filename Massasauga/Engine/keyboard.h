#ifndef KEYBOARD_H
#define KEYBOARD_H

class Keyboard
{
public:
	Keyboard();
	void KeyPress();
	bool isUpPressed() const {return m_keyState.isUpPressed;}
	bool isDownPressed() const {return m_keyState.isDownPressed;}
	bool isLeftPressed() const {return m_keyState.isLeftPressed;}
	bool isRightPressed() const {return m_keyState.isRightPressed;}
	bool isSpaceBarPressed() const {return m_keyState.isSpaceBarPressed;}

private:
	Keyboard(const Keyboard &); // disallow copy constructor
	Keyboard & operator=(const Keyboard &); // disallow assignment operator

	struct KeyState
	{
		KeyState() : isUpPressed(false), isDownPressed(false), isLeftPressed(false), isRightPressed(false), isSpaceBarPressed(false) {}
		bool isUpPressed;
		bool isDownPressed;
		bool isLeftPressed;
		bool isRightPressed;
		bool isSpaceBarPressed;
	} m_keyState;
};
#endif