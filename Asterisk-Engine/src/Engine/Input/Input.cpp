
#include "astpch.h"

#include "Types/Containers.h"

#include "Logger/Logger.h"

#include "Engine/Input/Input.h"

#define MAX_KEYS 348
#define MAX_MOUSE_BUTTONS 7

namespace asterisk {
	enum class InputState {
		None = 0,
		Pressed,
		Down,
		Released
	};

	static UnorderedMap<KeyCode, InputState> s_currentKey;
	static UnorderedMap<KeyCode, InputState> s_lastKey;

	static UnorderedMap<MouseCode, InputState> s_currentMouseButton;
	static UnorderedMap<MouseCode, InputState> s_lastMouseButton;

	static Vector2 s_currentMousePosition = Vector2();
	static Vector2 s_lastMousePosition    = Vector2();

	static Vector2 s_mouseDelta = Vector2();

	void Input::Initialize() {
		for (int i = 0; i <= MAX_KEYS; i++) {
			s_currentKey[(KeyCode)i] = InputState::None;
			s_lastKey[(KeyCode)i]    = InputState::None;
		}

		for (int i = 0; i <= MAX_MOUSE_BUTTONS; i++) {
			s_currentMouseButton[(MouseCode)i] = InputState::None;
			s_lastMouseButton[(MouseCode)i]    = InputState::None;
		}
	}

	void Input::ClearInput() {
		for (auto& [key, state] : s_currentKey)
			state = InputState::None;

		for (auto& [btn, state] : s_currentMouseButton)
			state = InputState::None;
	}

	void Input::Update() {
		for (auto& [key, state] : s_currentKey) {
			s_lastKey[key] = state;

			// state transition
			if (state == InputState::Pressed)
				state = InputState::Down;
			else if (state == InputState::Released)
				state = InputState::None;
		}

		for (auto& [btn, state] : s_currentMouseButton) {
			s_lastMouseButton[btn] = state;

			// state transition
			if (state == InputState::Pressed)
				state = InputState::Down;
			else if (state == InputState::Released)
				state = InputState::None;
		}

		s_mouseDelta = s_currentMousePosition - s_lastMousePosition;
		s_lastMousePosition = s_currentMousePosition;
	}

	void Input::OnKeyPressInternal(KeyCode code) {
		s_currentKey[code] = InputState::Pressed;
	}

	void Input::OnKeyReleasedInternal(KeyCode code) {
		s_currentKey[code] = InputState::Released;
	}

	void Input::OnMousePressInternal(MouseCode code) {
		s_currentMouseButton[code] = InputState::Pressed;
	}

	void Input::OnMouseReleasedInternal(MouseCode code) {
		s_currentMouseButton[code] = InputState::Released;
	}

	void Input::OnMouseMoveInternal(float _x, float _y) {
		s_currentMousePosition = { _x, _y };
	}

	const Vector2& Input::GetMousePosition() {
		return s_currentMousePosition;
	}

	const Vector2& Input::GetMouseDelta() {
		return s_mouseDelta;
	}

	bool Input::IsKeyPressed(KeyCode code) {
		return s_currentKey[code] == InputState::Pressed;
	}

	bool Input::IsKeyDown(KeyCode code) {
		return s_currentKey[code] == InputState::Down;
	}

	bool Input::IsKeyReleased(KeyCode code) {
		return s_currentKey[code] == InputState::Released;
	}

	bool Input::IsMouseClicked(MouseCode code) {
		return s_currentMouseButton[code] == InputState::Pressed;
	}

	bool Input::IsMouseDown(MouseCode code) {
		return s_currentMouseButton[code] == InputState::Down;
	}

	bool Input::IsMouseReleased(MouseCode code) {
		return s_currentMouseButton[code] == InputState::Released;
	}

}
