
#include <Engine/EntryPoint.h>
#include <Math/MatrixOperators.h>
#include <Logger/Logger.h>

#include <imgui.h>

using namespace asterisk;

class EditorLayer : public Layer {
public:
	EditorLayer() : Layer("Editor Layer") 
	{ }

	void OnAttach() override {
		auto& engine = Engine::Get();
		auto& imgui_layer = engine.GetImGuiLayer();

		ImGui::SetCurrentContext(imgui_layer.GetContext());

		Matrix2x4 A (
			1.0f, 2.0f, 3.0f, 4.0f,
			1.0f, 2.0f, 3.0f, 4.0f
		);

		Matrix4x4 B (
			1.0f, 2.0f, 3.0f, 4.0f,
			1.0f, 2.0f, 3.0f, 4.0f,
			1.0f, 2.0f, 3.0f, 4.0f,
			1.0f, 2.0f, 3.0f, 4.0f
		);

		auto C = A * B;

		ASTR_INFO(
			"Matrix: \n {}, {}, {}, {} \n {}, {}, {}, {}",
			C.m[0][0], C.m[1][0], C.m[2][0], C.m[3][0],
			C.m[0][1], C.m[1][1], C.m[2][1], C.m[3][1]
		);
	}

	void OnRender(float dt) override {
		ImGui::Begin("Editor Layer");

		ImGui::End();
	}
};

class AsteriskEditor : public asterisk::Engine {
public:
	AsteriskEditor(const asterisk::EngineSetting& _setting = asterisk::EngineSetting()) : 
		asterisk::Engine(_setting)
	{
		PushLayer(new EditorLayer());
	}
};

asterisk::Engine* asterisk::Create() {
	return new AsteriskEditor();
}