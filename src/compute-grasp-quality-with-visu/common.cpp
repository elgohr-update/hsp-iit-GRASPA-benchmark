#include "common.h"
#include <iostream>

#include <VirtualRobot/VirtualRobot.h>
#include <VirtualRobot/Robot.h>
#include <VirtualRobot/ManipulationObject.h>
#include <VirtualRobot/RuntimeEnvironment.h>
#include <VirtualRobot/XML/RobotIO.h>
#include <VirtualRobot/XML/ObjectIO.h>
#include <VirtualRobot/Grasping/Grasp.h>
#include <VirtualRobot/Grasping/GraspSet.h>
#include <VirtualRobot/EndEffector/EndEffector.h>
#include <GraspPlanning/GraspStudio.h>
#include <GraspPlanning/GraspQuality/GraspQualityMeasureWrenchSpace.h>
#include <GraspPlanning/ApproachMovementSurfaceNormal.h>
#include <GraspPlanning/GraspQuality/GraspEvaluationPoseUncertainty.h>



std::string common::fileBaseName(std::string const& path)
{
    //  return basename of a file, without extension

    std::string basename_with_extension = path.substr(path.find_last_of("/\\") + 1);

    return basename_with_extension.substr(0, basename_with_extension.find_last_of("."));
}

bool common::parseDataPath(std::string& data_path)
{
    //  add datapath to search path

    data_path = VirtualRobot::RuntimeEnvironment::getValue("datapath");
    if (!data_path.empty())
    {
        VirtualRobot::RuntimeEnvironment::addDataPath(data_path);
        return true;
    }

    return false;
}

bool common::parseGraspPath(std::string& grasp_path)
{
    //  this function doesn't serve much purpose, only exists for consistency

    std::string grasp_path_cmd_line = VirtualRobot::RuntimeEnvironment::getValue("graspsdir");
    if (!grasp_path_cmd_line.empty())
    {
        grasp_path = grasp_path_cmd_line;
        return true;
    }
    else
    {
        return false;
    }
}

bool common::parseSceneFilename(std::string& scene_filename)
{
    //  replace the scene filename if another is found in the search directory

    std::string scene_cmd_line_filename = VirtualRobot::RuntimeEnvironment::getValue("scene");

    if (!scene_cmd_line_filename.empty() && VirtualRobot::RuntimeEnvironment::getDataFileAbsolute(scene_cmd_line_filename))
    {
        scene_filename = scene_cmd_line_filename;
        return true;
    }
    else
    {
        return false;
    }

}

bool common::parseRobotFilename(std::string& robot_filename)
{
    //  replace robot filename if another is found in the search directory

    std::string robot_cmd_line_filename = VirtualRobot::RuntimeEnvironment::getValue("robot");

    if (!robot_cmd_line_filename.empty() && VirtualRobot::RuntimeEnvironment::getDataFileAbsolute(robot_cmd_line_filename))
    {
        robot_filename = robot_cmd_line_filename;
        return true;
    }
    else
    {
        return false;
    }

}

bool common::parseObjectFilename(std::string& object_filename)
{
    //  replace object filename if another is found in the search directory

    std::string object_cmd_line_filename = VirtualRobot::RuntimeEnvironment::getValue("object");

    if (!object_cmd_line_filename.empty() && VirtualRobot::RuntimeEnvironment::getDataFileAbsolute(object_cmd_line_filename))
    {
        object_filename = object_cmd_line_filename;
        return true;
    }
    else
    {
        return false;
    }
}

void common::listEndEffectors(const std::vector<VirtualRobot::EndEffectorPtr> robotEndEffectors)
{
    //  list any end effector in the provided vector

    std::cout << "Robot end effectors found: " << std::endl;

    for (auto eef_ptr : robotEndEffectors)
    {
        std::cout << "\t" << eef_ptr->getName() << std::endl;
        std::cout << "\tRegistered preshapes: " << std::endl;

        std::vector<std::string> eef_preshapes = eef_ptr->getPreshapes();

        for (auto pre_name : eef_preshapes)
        {
            std::cout << "\t\t" << pre_name << std::endl;
        }
    }

    return;
}

void common::listGrasps(const std::vector<VirtualRobot::GraspPtr> grasp_vec)
{
    //  display info about grasps

    std::cout << "Retrieved grasps: " << grasp_vec.size() << std::endl;

    for (auto grasp_ptr : grasp_vec)
    {
        std::cout << "\tEnd Effector: \t"   << grasp_ptr->getEefName() << std::endl;
        std::cout << "\tPreshape: \t\t"       << grasp_ptr->getPreshapeName() << std::endl;
        std::cout << "\tQuality: \t\t"        << grasp_ptr->getQuality() << std::endl;
    }

    return;

}

bool common::generateClosureTrajectory(const VirtualRobot::EndEffectorPtr& end_effector, const VirtualRobot::GraspPtr& grasp, VirtualRobot::TrajectoryPtr& closure_trajectory)
{

    //  if the grasp specifies a final configuration, generate a joint space trajectory that
    //  goes from the initial config to that

    end_effector->openActors();

    //  store the initial configuration as a Eigen vector

    VirtualRobot::RobotConfigPtr eef_initial_config = end_effector->getConfiguration();
    eef_initial_config->print();


    return true;

}
