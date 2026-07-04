#pragma once

#include "Core/Common.h"
#include "Math/Vector2.h"

#include "Engine/Input/InputCode.h"

namespace asterisk {
	class ASTERISK_ENGINE_API Input {
	protected:
		static void Initialize();
		static void ClearInput();
		static void Update();
		 
		static void OnKeyPressInternal(KeyCode code);
		static void OnKeyReleasedInternal(KeyCode code);
		 
		static void OnMousePressInternal(MouseCode code);
		static void OnMouseReleasedInternal(MouseCode code);
		 
		static void OnMouseMoveInternal(float _x, float _y);
		 
		static const Vector2& GetMousePosition();
		static const Vector2& GetMouseDelta();

	public:
		static bool IsKeyPressed(KeyCode code);
		static bool IsKeyDown(KeyCode code);
		static bool IsKeyReleased(KeyCode code);
		
		static bool IsMouseClicked(MouseCode code);
		static bool IsMouseDown(MouseCode code);
		static bool IsMouseReleased(MouseCode code);

	public:
		static bool IsShiftDown()   { return IsKeyDown(KEY_LEFT_SHIFT)   || IsKeyDown(KEY_RIGHT_SHIFT); }
		static bool IsAltDown()     { return IsKeyDown(KEY_LEFT_ALT)     || IsKeyDown(KEY_RIGHT_ALT); }
		static bool IsControlDown() { return IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL); }
	};
}

