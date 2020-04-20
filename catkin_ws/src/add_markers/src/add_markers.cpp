#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Pose.h>
#include <cmath>


ros::Subscriber odom_sub;
ros::Publisher marker_pub;
visualization_msgs::Marker marker;
nav_msgs::Odometry p_msg;

// Set marker shape type to be a cube
uint32_t shape = visualization_msgs::Marker::CUBE;

float pickUp[3] = {5.0, 5.0, 1.0};
float dropOff[3] ={0.0, 0.0, 1.0};
float dist_pick;
float dist_drop;

bool collected = false;
bool delivered = false;
bool collecting= true;
bool delivering = false;

void odom_callback(const nav_msgs::Odometry::ConstPtr& odom_msg){
	p_msg=*odom_msg;
	float x = p_msg.pose.pose.position.x;
	float y = p_msg.pose.pose.position.y;

	dist_pick = sqrt(pow((x - pickUp[0]), 2) + pow((y - pickUp[1]), 2));
	dist_drop = sqrt(pow((x - dropOff[0]), 2) + pow((y - dropOff[1]), 2));


	if (collecting && dist_pick <0.5 ){
	    ROS_INFO("collected");
	    collecting = false;
	    collected = true;
	    //ros::Duration(5.0).sleep(); 
	    }

	if (delivering && dist_drop <0.5){    
	    ROS_INFO("delivered");
	    delivering = false;
	    delivered= true;
	    //ros::Duration(5.0).sleep();  
	    }
}

int main( int argc, char** argv )
{
	  ros::init(argc, argv, "add_markers");
	  ros::NodeHandle n;
	  ros::Rate r(1);
	  marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

	  //Subscribe to the odim topic and call odom_callback function
	  odom_sub = n.subscribe("odom", 1000, odom_callback);
	  ros::spinOnce();
	  
 
   while (ros::ok())  {
    
    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker.header.frame_id = "map";
    marker.header.stamp = ros::Time::now();

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    marker.ns = "basic_shapes";
    marker.id = 0;

    // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
    marker.type = shape;

    // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
    marker.action = visualization_msgs::Marker::ADD;

    // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
    marker.pose.position.x = pickUp[0];
    marker.pose.position.y = pickUp[1];
    marker.pose.position.z = 0;
    
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = pickUp[2];

    // Set the scale of the marker -- 1x1x1 here means 1m on a side
    marker.scale.x = 0.5;
    marker.scale.y = 0.5;
    marker.scale.z = 0.5;

    // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = 0.0f;
    marker.color.g = 1.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0;

    marker.lifetime = ros::Duration();

    // Publish the marker
    while (marker_pub.getNumSubscribers() < 1 )
    {

      if (!ros::ok())
      {
        return 0;
      }

      ROS_WARN_ONCE("Waiting for data");
      sleep(1);
      ros::spinOnce();
    }
  
    if(collecting){
	ROS_INFO_ONCE("Collection marker is displayed, robot is collecting.");
        marker_pub.publish(marker);
    }
   //robot is collectig 
   if (collected){
	ros::Duration(5.0).sleep();   
       marker.action = visualization_msgs::Marker::DELETE;
       marker_pub.publish(marker);
       // delivery location
       marker.pose.position.x = dropOff[0];
       marker.pose.position.y = dropOff[1];

       ROS_INFO("Robot collected.");       
       marker.action = visualization_msgs::Marker::ADD;
       marker_pub.publish(marker);
       ROS_INFO("Delivery marker is displayed, robot is delivering.");
       delivering = true;
       collecting = false; 
	collected = false;  
            
       }
   
   //robot  delivering 
   if (delivered ){
	ros::Duration(5.0).sleep();   
        marker.action = visualization_msgs::Marker::DELETE;
	marker_pub.publish(marker);       
        ROS_INFO("Robot delivered.");
	delivering = false;
	delivered = false;
        ros::Duration(5.0).sleep();    
        }
  
   if (!collecting && !delivering ){	
        ROS_INFO("Task completed");
        ros::Duration(15.0).sleep();
	return 0;
        }
 
   ros::spinOnce();   
    
   
   }
}
