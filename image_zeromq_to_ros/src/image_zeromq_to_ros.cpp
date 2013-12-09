#include <boost/thread.hpp>
#include <ros/ros.h>
#include <ros/assert.h>
#include <nodelet/nodelet.h>
#include <image_transport/image_transport.h>
#include <sensor_msgs/CameraInfo.h>
#include <sensor_msgs/image_encodings.h>
#include <camera_calibration_parsers/parse.h>
#include <zmq.h>
#include "jpeg_decompress.h"

class ImageZeroMQToROS : public nodelet::Nodelet
{
 public:
  ImageZeroMQToROS(): running_(false)
  {
    zmq_context_ = zmq_ctx_new();
    zmq_subscriber_ = zmq_socket(zmq_context_, ZMQ_SUB);
  }

  ~ImageZeroMQToROS()
  {
    if(running_)
    {
      NODELET_INFO("shutting down driver thread");
      running_ = false;
      deviceThread_->join();
      NODELET_INFO("driver thread stopped");
    }
    zmq_close(zmq_subscriber_);
    zmq_ctx_destroy(zmq_context_);
  }
 private:
  virtual void onInit()
  {
    ros::NodeHandle priv_nh(getPrivateNodeHandle());

    const int queue_size = 1;
    int rc = zmq_setsockopt(zmq_subscriber_, ZMQ_RCVHWM, &queue_size, sizeof(queue_size));
    ROS_ASSERT(rc == 0);
    rc = zmq_setsockopt(zmq_subscriber_, ZMQ_SUBSCRIBE, "", 0);
    ROS_ASSERT(rc == 0);

    std::string zmq_transport;
    priv_nh.param("zmq_transport", zmq_transport, std::string("tcp://192.168.1.106:12345"));
    rc = zmq_connect(zmq_subscriber_, zmq_transport.c_str());
    ROS_ASSERT(rc == 0);

    priv_nh.param("jpeg_decompress", jpeg_decompress_, true);

    priv_nh.param("image_width", image_width_, 752);
    priv_nh.param("image_height", image_height_, 480);
    priv_nh.param("image_channels", image_channels_, 1);

    std::string calib_filename, camera_name;
    if(priv_nh.getParam("calibration", calib_filename))
    {
      if(!camera_calibration_parsers::readCalibration(calib_filename, camera_name, camera_info_))
      {
        NODELET_ERROR("%s: failed to load calibration file", ros::this_node::getName().c_str());
      }
    }
    else
    {
      NODELET_ERROR("No calibration file specified!");
    }

    image_transport::ImageTransport it(priv_nh);
    pub_image_ = it.advertiseCamera("image_raw", 1);

    // spawn device thread
    running_ = true;
    deviceThread_ = boost::shared_ptr<boost::thread>(new boost::thread(boost::bind(&ImageZeroMQToROS::run, this)));
  }

  void run(void)
  {
    const size_t max_img_data_size = image_width_*image_height_*image_channels_;
    uint8_t *rx_buf = new uint8_t[max_img_data_size];
    uint8_t *img_buf = new uint8_t[max_img_data_size];

    int rx_img_width, rx_img_height, rx_img_channels;

    ros::Time ts_frame;

    while(running_)
    {
      int rx_length = zmq_recv(zmq_subscriber_, rx_buf, max_img_data_size, 0);
      ts_frame = ros::Time::now();
      //printf("expected: %zu, rc: %d\n", max_img_data_size, rx_length);
      if(jpeg_decompress_)
      {
        jpeg_decompress(rx_buf, rx_length, &img_buf, &rx_img_width, &rx_img_height, &rx_img_channels);
      }
      else
      {
        rx_img_width = image_width_;
        rx_img_height = image_height_;
        rx_img_channels = image_channels_;
        ROS_ASSERT(image_width_*image_height_*image_channels_ == rx_length);
      }
      const size_t img_data_size = rx_img_width*rx_img_height*rx_img_channels;

      sensor_msgs::Image::Ptr image(new sensor_msgs::Image);
      sensor_msgs::CameraInfo::Ptr camera_info(new sensor_msgs::CameraInfo(camera_info_));
      camera_info->header.frame_id = "camera";

      image->header.stamp = ts_frame;
      image->header.frame_id = "camera";
      image->height = rx_img_height;
      image->width = rx_img_width;
      if(rx_img_channels == 3)
      {
        image->encoding = sensor_msgs::image_encodings::BGR8;
        image->step = rx_img_width*3;
      }
      else
      {
        image->encoding = sensor_msgs::image_encodings::MONO8;
        image->step = rx_img_width;
      }
      image->is_bigendian = 0;
      image->data.resize(img_data_size);
      if(jpeg_decompress_)
        memcpy(&image->data[0], img_buf, img_data_size);
      else
        memcpy(&image->data[0], rx_buf, img_data_size);
      camera_info->header.stamp = image->header.stamp;
      pub_image_.publish(image, camera_info);
    }

    delete[] rx_buf;
    delete[] img_buf;
  }

  sensor_msgs::CameraInfo camera_info_;
  image_transport::CameraPublisher pub_image_;
  bool jpeg_decompress_;
  int image_width_, image_height_, image_channels_;

  void *zmq_context_, *zmq_subscriber_;
  volatile bool running_;
  boost::shared_ptr<boost::thread> deviceThread_;
};

#include <pluginlib/class_list_macros.h>
PLUGINLIB_DECLARE_CLASS(image_zeromq_to_ros, ImageZeroMQToROS, ImageZeroMQToROS, nodelet::Nodelet);
