#include "SynthKit.hpp"


struct SubtractionModule : Module {
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

	SubtractionModule() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) {}
	void step() override;

	// For more advanced Module features, read Rack's engine.hpp header file
	// - toJson, fromJson: serialization of internal data
	// - onSampleRateChange: event triggered by a change of sample rate
	// - reset, randomize: implements special behavior when user clicks these from the context menu
};


void SubtractionModule::step() {
	float top1 = inputs[TOP1_INPUT].value;
	float top2 = inputs[TOP2_INPUT].value;
	float bottom1 = inputs[BOTTOM1_INPUT].value;
	float bottom2 = inputs[BOTTOM2_INPUT].value;

	float val1 = top1 - top2;
	float val2 = bottom1 - bottom2;

	outputs[TOP_OUTPUT].value = val1;
	outputs[BOTTOM_OUTPUT].value = val2;
}


SubtractionWidget::SubtractionWidget() {
	SubtractionModule *module = new SubtractionModule();
	setModule(module);
	box.size = Vec(3 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT);

	{
		SVGPanel *panel = new SVGPanel();
		panel->box.size = box.size;
		panel->setBackground(SVG::load(assetPlugin(plugin, "res/Subtraction.svg")));
		addChild(panel);
	}

	addChild(createScrew<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
	addChild(createScrew<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

	addInput(createInput<PJ301MPort>(Vec(10, 45), module, SubtractionModule::TOP1_INPUT));
	addInput(createInput<PJ301MPort>(Vec(10, 94), module, SubtractionModule::TOP2_INPUT));

	addOutput(createOutput<PJ301MPort>(Vec(10, 143), module, SubtractionModule::TOP_OUTPUT));

	addInput(createInput<PJ301MPort>(Vec(10, 203), module, SubtractionModule::BOTTOM1_INPUT));
	addInput(createInput<PJ301MPort>(Vec(10, 252), module, SubtractionModule::BOTTOM2_INPUT));

	addOutput(createOutput<PJ301MPort>(Vec(10, 301), module, SubtractionModule::BOTTOM_OUTPUT));
}
