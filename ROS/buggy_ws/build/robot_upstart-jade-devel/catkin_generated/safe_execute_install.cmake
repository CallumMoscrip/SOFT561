execute_process(COMMAND "/home/callum/buggy_ws/build/robot_upstart-jade-devel/catkin_generated/python_distutils_install.sh" RESULT_VARIABLE res)

if(NOT res EQUAL 0)
  message(FATAL_ERROR "execute_process(/home/callum/buggy_ws/build/robot_upstart-jade-devel/catkin_generated/python_distutils_install.sh) returned error code ")
endif()