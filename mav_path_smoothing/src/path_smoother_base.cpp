#include "mav_path_smoothing/velocity_ramp_smoother.h"

namespace mav_planning {

void PathSmootherBase::setParametersFromRos(const ros::NodeHandle& nh) {
  constraints_.setParametersFromRos(nh);
}

void PathSmootherBase::setPhysicalConstraints(
    const PhysicalConstraints& constraints) {
  constraints_ = constraints;
}
const PhysicalConstraints& PathSmootherBase::getPhysicalConstraints() const {
  return constraints_;
}

bool PathSmootherBase::getPathBetweenWaypoints(
    const mav_msgs::EigenTrajectoryPointVector& waypoints,
    mav_msgs::EigenTrajectoryPoint::Vector* path) const {
  if (waypoints.size() < 2) {
    return false;
  }
  mav_msgs::EigenTrajectoryPoint start = waypoints[0];
  mav_msgs::EigenTrajectoryPointVector path_segment;

  for (const mav_msgs::EigenTrajectoryPoint& goal : waypoints) {
    if (getPathBetweenTwoPoints(start, goal, &path_segment)) {
      path->insert(path->end(), path_segment.begin(), path_segment.end());
      path_segment.clear();
      start = goal;
    } else {
      return false;
    }
  }
  return true;
}

}  // namespace mav_planning
