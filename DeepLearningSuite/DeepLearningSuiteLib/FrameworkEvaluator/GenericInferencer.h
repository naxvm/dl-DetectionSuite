//
// Created by frivas on 4/02/17.
//

#ifndef SAMPLERGENERATOR_GENERICINFERENCER_H
#define SAMPLERGENERATOR_GENERICINFERENCER_H

#include "FrameworkInferencer.h"

#ifdef DARKNET_ACTIVE
#include <FrameworkEvaluator/DarknetInferencer.h>
#include <FrameworkEvaluator/TensorFlowInferencer.h>
#endif

enum INFERENCER_IMPLEMENTATIONS{INF_YOLO, INF_TENSORFLOW};


class GenericInferencer {
public:
    GenericInferencer(const std::string& netConfig, const std::string& netWeights, const std::string& classNames, const std::string& implementation);
    FrameworkInferencerPtr getInferencer();
    static std::vector<std::string> getAvailableImplementations();

private:
    INFERENCER_IMPLEMENTATIONS imp;
#ifdef DARKNET_ACTIVE
    DarknetInferencerPtr darknetInferencerPtr;
#endif

    TensorFlowInferencerPtr tensorFlowInferencerPtr;
    std::vector<std::string> availableImplementations;

    static void configureAvailablesImplementations(std::vector<std::string>& data);
    INFERENCER_IMPLEMENTATIONS getImplementation(const std::string& inferencerImplementation);
};

typedef  boost::shared_ptr<GenericInferencer> GenericInferencerPtr;


#endif //SAMPLERGENERATOR_GENERICINFERENCER_H
