//
// Created by frivas on 31/01/17.
//

#include <Common/Sample.h>
#include <DatasetConverters/ClassTypeGeneric.h>
#include "DarknetInferencer.h"

DarknetInferencer::DarknetInferencer(const std::string &netConfig, const std::string &netWeights,const std::string& classNamesFile): netConfig(netConfig),netWeights(netWeights) {
    this->classNamesFile=classNamesFile;
    this->cnn = boost::shared_ptr<DarknetAPI>(new DarknetAPI((char*)this->netConfig.c_str(), (char*)this->netWeights.c_str()));
}

Sample DarknetInferencer::detectImp(const cv::Mat &image) {
    cv::Mat rgbImage;
    cv::cvtColor(image,rgbImage,CV_RGB2BGR);
    DarknetDetections detections = this->cnn->process(rgbImage);

    Sample sample;
    RectRegionsPtr regions(new RectRegions());
    ClassTypeGeneric typeConverter(classNamesFile);

    for (auto it = detections.data.begin(), end=detections.data.end(); it !=end; ++it){
        typeConverter.setId(it->classId);
        regions->add(it->detectionBox,typeConverter.getClassString());
        std::cout<< typeConverter.getClassString() << ": " << it->probability << std::endl;
    }
    sample.setRectRegions(regions);
    return sample;
}
