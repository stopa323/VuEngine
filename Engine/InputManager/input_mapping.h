/*
 * input_mapping.h
 *
 *  Created on: Feb 4, 2017
 *      Author: root
 */

#ifndef ENGINE_INPUTMANAGER_INPUT_MAPPING_H_
#define ENGINE_INPUTMANAGER_INPUT_MAPPING_H_

#include <cstdint>


/* Mouse button masks */
#define MOUSE_BUTTON_LEFT						0x01
#define MOUSE_BUTTON_MIDDLE						0x02
#define MOUSE_BUTTON_RIGHT						0x03
#define MOUSE_BUTTON_WHEEL_UP					0x04
#define MOUSE_BUTTON_WHEEL_DOWN					0x05

/* Mouse button modifier masks */
#define MOUSE_BUTTON_MOD_NULL					0x0000
#define MOUSE_BUTTON_MOD_SHIFT					0x0001
#define MOUSE_BUTTON_MOD_CAPSLOCK				0x0002
#define MOUSE_BUTTON_MOD_CTRL					0x0004
#define MOUSE_BUTTON_MOD_LALT					0x0008
#define MOUSE_BUTTON_MOD_NUMLOCK				0x0010
#define MOUSE_BUTTON_MOD_SHIFT_CTRL				MOUSE_BUTTON_MOD_SHIFT | MOUSE_BUTTON_MOD_CTRL
#define MOUSE_BUTTON_MOD_SHIFT_LALT				MOUSE_BUTTON_MOD_SHIFT | MOUSE_BUTTON_MOD_LALT
#define MOUSE_BUTTON_MOD_CTRL_LALT				MOUSE_BUTTON_MOD_CTRL | MOUSE_BUTTON_MOD_LALT
#define MOUSE_BUTTON_MOD_SHIFT_CTRL_LALT		MOUSE_BUTTON_MOD_SHIFT_CTRL | MOUSE_BUTTON_MOD_LALT

/* Input modifiers */
#define INPUT_MODIFIER_NULL						0x0000
#define INPUT_MODIFIER_SHIFT					0x0001
#define INPUT_MODIFIER_CAPSLOCK					0x0002
#define INPUT_MODIFIER_CONTROL					0x0004
#define INPUT_MODIFIER_LALT						0x0008
#define INPUT_MODIFIER_NUMLOCK					0x0010

enum class EMouseEvent : uint8_t {
	UNKNOWN										= 0,

	LMB_PRESS									= 1,
	MMB_PRESS									= 2,
	RMB_PRESS									= 3,

	LMB_RELEASE									= 11,
	MMB_RELEASE									= 12,
	RMB_RELEASE									= 13,

	WHEEL_UP									= 21,
	WHEEL_DOWN									= 22,

	LMB_SHIFT_PRESS								= 31,
	LMB_CTRL_PRESS								= 32,
	LMB_LALT_PRESS								= 33,
	LMB_SHIFT_CTRL_PRESS						= 34,
	LMB_SHIFT_LALT_PRESS						= 35,
	LMB_CTRL_LALT_PRESS							= 36,
	LMB_SHIFT_CTRL_LALT_PRESS					= 37,

	MMB_SHIFT_PRESS								= 41,
	MMB_CTRL_PRESS								= 42,
	MMB_LALT_PRESS								= 43,
	MMB_SHIFT_CTRL_PRESS						= 44,
	MMB_SHIFT_LALT_PRESS						= 45,
	MMB_CTRL_LALT_PRESS							= 46,
	MMB_SHIFT_CTRL_LALT_PRESS					= 47,

	RMB_SHIFT_PRESS								= 51,
	RMB_CTRL_PRESS								= 52,
	RMB_LALT_PRESS								= 53,
	RMB_SHIFT_CTRL_PRESS						= 54,
	RMB_SHIFT_LALT_PRESS						= 55,
	RMB_CTRL_LALT_PRESS							= 56,
	RMB_SHIFT_CTRL_LALT_PRESS					= 57,

	WHEEL_UP_SHIFT								= 91,
	WHEEL_UP_CTRL								= 92,
//	WHEEL_UP_LALT								= 93, cmon its too much
//	WHEEL_UP_SHIFT_CTRL							= 94,
//	WHEEL_UP_SHIFT_LALT							= 95,
//	WHEEL_UP_CTRL_LALT							= 96,
//	WHEEL_UP_SHIFT_CTRL_LALT					= 97,

	WHEEL_DOWN_SHIFT							= 101,
	WHEEL_DOWN_CTRL								= 102
//	WHEEL_DOWN_LALT								= 103,
//	WHEEL_DOWN_SHIFT_CTRL						= 104,
//	WHEEL_DOWN_SHIFT_LALT						= 105,
//	WHEEL_DOWN_CTRL_LALT						= 106,
//	WHEEL_DOWN_SHIFT_CTRL_LALT					= 107
};

enum class EInputModifier : uint8_t {
	NOOP										= 0,
	SHIFT										= 1,
	CTRL										= 4,
	LALT										= 8,
	SHIFT_CTRL									= 5,
	SHIFT_LALT									= 9,
	SHIFT_CTRL_LALT								= 13,
	CTRL_LALT									= 12
};

enum class EInputType : uint8_t {
	UNKNOWN										= 0,
	PRESSED										= 1,
	RELEASED									= 2
};

enum class EKeyboardKey : uint8_t {
	UNKNOWN										= 0,

	KEY_ESC										= 9,
	KEY_TAB										= 23,
	KEY_DELETE									= 119,
	KEY_SPACE									= 65,
	KEY_ENTER									= 36,
	KEY_UP										= 111,
	KEY_DOWN									= 116,
	KEY_RIGHT									= 114,
	KEY_LEFT									= 113,
	KEY_0										= 19,
	KEY_1										= 10,
	KEY_2										= 11,
	KEY_3										= 12,
	KEY_4										= 13,
	KEY_5										= 14,
	KEY_6										= 15,
	KEY_7										= 16,
	KEY_8										= 17,
	KEY_9										= 18,
	KEY_NUM0									= 90,
	KEY_NUM1									= 87,
	KEY_NUM2									= 88,
	KEY_NUM3									= 89,
	KEY_NUM4									= 83,
	KEY_NUM5									= 84,
	KEY_NUM6									= 85,
	KEY_NUM7									= 79,
	KEY_NUM8									= 80,
	KEY_NUM9									= 81,
	KEY_F1										= 67,
	KEY_F2										= 68,
	KEY_F3										= 69,
	KEY_F4										= 70,
	KEY_F5										= 71,
	KEY_F6										= 72,
	KEY_F7										= 73,
	KEY_F8										= 74,
	KEY_F9										= 75,
	KEY_F10										= 76,
	KEY_F11										= 95,
	KEY_F12										= 96,
	A											= 38,
	B											= 56,
	C											= 54,
	D											= 40,
	E											= 26,
	F											= 41,
	G											= 42,
	H											= 43,
	I											= 31,
	J											= 44,
	K											= 45,
	L											= 46,
	M											= 58,
	N											= 57,
	O											= 32,
	P											= 33,
	Q											= 24,
	R											= 27,
	S											= 39,
	T											= 28,
	U											= 30,
	V											= 55,
	W											= 25,
	X											= 53,
	Y											= 29,
	Z											= 52
};

struct SKeyboardEvent {
	EKeyboardKey Key;
	EInputModifier Modifiers;
	EInputType Type;
};

#endif /* ENGINE_INPUTMANAGER_INPUT_MAPPING_H_ */
