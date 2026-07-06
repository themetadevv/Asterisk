
#include <Engine/EntryPoint.h>
#include <Logger/Logger.h>

#include <Math/MatrixAliases.h>

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

		Matrix2x2 A(
			2, 2,
			2, 2
		);

		Matrix2x2 B(
			2, 2,
			2, 2
		);

		auto C = A * B;

		ASTR_DEBUG(
			"Matrix C: \n {} {} \n {} {}",
			C.m[0][0], C.m[1][0],
			C.m[0][1], C.m[1][1]
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