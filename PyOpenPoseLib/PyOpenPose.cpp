//
// Created by padeler on 21/6/2017.
//
#include <boost/python.hpp>
#include "OpenPoseWrapper.h"
#include "opencv_expose.h"




#if defined(DEBUG) || defined(_DEBUG)
#   define OPENPOSE_MODULE_NAME PyOpenPoseD
#   define OPENPOSE_MODULE_NAME_STR "PyOpenPoseD"
#else
#   define OPENPOSE_MODULE_NAME PyOpenPose
#   define OPENPOSE_MODULE_NAME_STR "PyOpenPose"
#endif

namespace bpy = boost::python;




BOOST_PYTHON_MODULE(OPENPOSE_MODULE_NAME)
{
    bpy::return_value_policy<bpy::reference_existing_object> ref_existing;

    // expose opencv cv::Mat and cv::Size
    expose_opencv();

    // OpenPose wrapper
    bpy::scope s =
        bpy::class_<OpenPoseWrapper, OpenPoseWrapper::Ptr,boost::noncopyable>("OpenPose")
                .def(bpy::init<>())
                .def(bpy::init<cv::Size,cv::Size,cv::Size>())
                .def(bpy::init<cv::Size,cv::Size,cv::Size,std::string, std::string, int>())
                .def(bpy::init<cv::Size,cv::Size,cv::Size,std::string, std::string, int, bool>())
                .def(bpy::init<cv::Size,cv::Size,cv::Size,std::string, std::string, int, bool, OpenPoseWrapper::ScaleMode>())
                .def(bpy::init<cv::Size,cv::Size,cv::Size,std::string, std::string, int, bool, OpenPoseWrapper::ScaleMode, bool>())
                .def(bpy::init<cv::Size,cv::Size,cv::Size,std::string, std::string, int, bool, OpenPoseWrapper::ScaleMode, bool, bool>())
                .def("detectPose", &OpenPoseWrapper::detectPose)
                .def("detectFace", &OpenPoseWrapper::detectFace)
                .def("detectHands", &OpenPoseWrapper::detectHands)
                .def("render", &OpenPoseWrapper::render)
                .def("getKeypoints", &OpenPoseWrapper::getKeypoints)
                .def("getHeatmaps", &OpenPoseWrapper::getHeatmaps)
                .def("getHandHeatmaps", &OpenPoseWrapper::getHandHeatmaps)
            ;

    s.attr("KeypointType") = bpy::enum_<OpenPoseWrapper::KeypointType>("KeypointType")
            .value("POSE", OpenPoseWrapper::POSE)
            .value("FACE", OpenPoseWrapper::FACE)
            .value("HAND", OpenPoseWrapper::HAND)
            ;

    s.attr("ScaleMode") = bpy::enum_<OpenPoseWrapper::ScaleMode>("ScaleMode")
            .value("InputResolution", OpenPoseWrapper::ScaleMode::InputResolution)
            .value("NetOutputResolution", OpenPoseWrapper::ScaleMode::NetOutputResolution)
            .value("OutputResolution", OpenPoseWrapper::ScaleMode::OutputResolution)
            .value("ZeroToOne", OpenPoseWrapper::ScaleMode::ZeroToOne)
            .value("PlusMinusOne", OpenPoseWrapper::ScaleMode::PlusMinusOne)
            .value("UnsignedChar", OpenPoseWrapper::ScaleMode::UnsignedChar)
            ;
}
