#include "WAVReader.h"
#include "WAVWriter.h"
#include "ConfigsReader.h"
#include "Instruction.h"
#include "converters/Mixer.h"
#include "converters/Muter.h"
#include "converters/Replacer.h"
#include <boost/program_options.hpp>
#include "Exceptions.h"
using namespace std;


int process(vector<WAVReader> &inputs, ConfigsReader &configReader, WAVWriter &output, int timeStep=10) {
    int currTime = 0;
    const WAVReader &mainInput = inputs[0];
    output.setHeader(mainInput.getHeader());
    output.setFmt(mainInput.getFmt());
    output.writeHeader();
    output.writeFmt();
    output.writeDataInfo(mainInput.getData().numberOfSamples * sizeof(int16_t));
    vector<Instruction> instructions;
    while (configReader.hasNext()) {
        try {
            instructions.emplace_back(configReader.readInsruction());
        } catch (InstructionException &error){
            if (error.code() != InstructionException::EMPTY_COMMAND) {
                std::cerr << "Error on line " << configReader.getLineNumber() << " in config file: ";
                std::cerr << error.what() << '\n';
                return error.code();
            }
        } catch (BasicException &error) {
            std::cerr << "Error on line " << configReader.getLineNumber() << " in config file: ";
            std::cerr << error.what() << '\n';
            return error.code();
        }
    }
    while (mainInput.hasNext()) {
        vector<SampleFlow*> flows;
        for (auto &reader : inputs) {
            try {
                flows.push_back(reader.readNext(timeStep));
            } catch (WAVException &error) {
                std::cerr << error.what() << '\n';
                return error.code();
            }
        }
        timeStep = flows[0]->getSeconds();
        SampleFlow *previousFlow = nullptr;
        for (const auto &instruction : instructions) {
            const Converter *converter = instruction.getConverter();
            SampleFlow *res = nullptr;
            try {
                res = converter->convert(previousFlow, flows, {currTime, currTime + timeStep});
            } catch (ConverterException &error) {
                delete previousFlow;
                for (const auto &item : flows) {
                    delete item;
                }
                delete res;
                std::cerr << error.what() << '\n';
                return error.code();
            }
            delete previousFlow;
            previousFlow = res;
        }
        output.writeSampleFlow(previousFlow);
        delete previousFlow;
        for (const auto &item : flows) {
            delete item;
        }
        currTime += timeStep;
    }
    return 0;
}

int main(const int argc, char **argv) {
    ConfigsReader configsReader{};
    configsReader.addConverter<Muter>("mute");
    configsReader.addConverter<Mixer>("mix");
    configsReader.addConverter<Replacer>("replace");
    boost::program_options::options_description description("General options");
    string availableConverters = "available converter commands: ";
    for (const auto &item : configsReader.getConverters()) {
        availableConverters += item + ", ";
    }
    availableConverters = availableConverters.substr(0, availableConverters.size() - 2);
    description.add_options()
        ("help,h", boost::program_options::value<string>(), (availableConverters.c_str()))
        ("config,c", boost::program_options::value<string>()->required(), "configuration file")
        ("input,i", boost::program_options::value<vector<string>>()->required(), "input .wav files")
        ("output,o", boost::program_options::value<string>()->required(), "output .wav file");
    boost::program_options::variables_map vm;
    try {
        store(boost::program_options::command_line_parser(argc, argv).options(description).run(), vm);
        if (vm.contains("help")) {
            auto converterDesctriptions = configsReader.getDescriptions();
            const string command = vm["help"].as<string>();
            if (converterDesctriptions.contains(command)) {
                std::cout << converterDesctriptions[command] << '\n';
                return 0;
            } else {
                std::cerr << "ERROR: " << "no available command with name '" + command + "'" << "\n" << description << '\n';
                return BasicException::INVALID_OPTION;
            }
        }
        notify(vm);
    } catch (boost::program_options::error& e) {
        std::cerr << "ERROR: " << e.what() << "\n" << description << '\n';
        return BasicException::INVALID_OPTION;
    }
    const vector<string> inputFiles = vm["input"].as<vector<string>>();
    const string outputFile = vm["output"].as<string>();
    const string configFile = vm["config"].as<string>();
    vector<WAVReader> readers;
    for (const auto &item : inputFiles) {
        try {
            readers.emplace_back(item);
            readers[readers.size() - 1].readAllInfo();
        } catch (WAVException &error) {
            cerr << error.what() << '\n';
            return error.code();
        }
    }
    WAVWriter writer{};
    try {
        writer.open(outputFile);
    } catch (WAVException &error) {
        cerr << error.what() << '\n';
        return error.code();
    }
    try {
        configsReader.open(configFile);
    } catch (ConfigException &error) {
        cerr << error.what() << '\n';
        return error.code();
    }
    int resCode = process(readers, configsReader, writer);
    return resCode;
}