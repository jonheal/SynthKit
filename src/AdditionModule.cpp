#include "SynthKit.hpp"


struct AdditionModule : Module {
	enum ParamIds {
		NUM_PARAMS
	};
	enum InputIds {
		TOP1_INPUT,
		TOP2_INPUT,
		BOTTOM1_INPUT,
		BOTTOM2_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		TOP_OUTPUT,
		BOTTOM_OUTPUT,
		NUM_OUTPUTS
	};
	enum LightIds {
		NUM_LIGHTS
	};

	AdditionModule() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) {}
	void step() override;

	// For more advanced Module features, read Rack's engine.hpp header file
	// - toJson, fromJson: serialization of internal data
	// - onSampleRateChange: event triggered by a change of sample rate
	// - reset, randomize: implements special behavior when user clicks these from the context menu
};


void AdditionModule::step() {
	float top1 = inputs[TOP1_INPUT].value;
	float top2 = inputs[TOP2_INPUT].value;
	float bottom1 = inputs[BOTTOM1_INPUT].value;
	float bottom2 = inputs[BOTTOM2_INPUT].value;

	float val1 = top1 + top2;
	float val2 = bottom1 + bottom2;
	outputs[TOP_OUTPUT].value = val1;
	outputs[BOTTOM_OUTPUT].value = val2;
}


AdditionWidget::AdditionWidget() {
	AdditionModule *module = new AdditionModule();
	setModule(module);
	box.size = Vec(3 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT);

	{
		SVGPanel *panel = new SVGPanel();
		panel->box.size = box.size;
		panel->setBackground(SVG::load(assetPlugin(plugin, "res/Addition.svg")));
		addChild(panel);
	}

	addChild(createScrew<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
	addChild(createScrew<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

	addInput(createInput<PJ301MPort>(Vec(10, 45), module, AdditionModule::TOP1_INPUT));
	addInput(createInput<PJ301MPort>(Vec(10, 94), module, AdditionModule::TOP2_INPUT));

	addOutput(createOutput<PJ301MPort>(Vec(10, 143), module, AdditionModule::TOP_OUTPUT));

	addInput(createInput<PJ301MPort>(Vec(10, 203), module, AdditionModule::BOTTOM1_INPUT));
	addInput(createInput<PJ301MPort>(Vec(10, 252), module, AdditionModule::BOTTOM2_INPUT));

	addOutput(createOutput<PJ301MPort>(Vec(10, 301), module, AdditionModule::BOTTOM_OUTPUT));
}
