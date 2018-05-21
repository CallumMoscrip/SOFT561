# CMake generated Testfile for 
# Source directory: /home/callum/buggy_ws/src/robot_upstart-jade-devel
# Build directory: /home/callum/buggy_ws/build/robot_upstart-jade-devel
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(_ctest_robot_upstart_roslint_package "/home/callum/buggy_ws/build/catkin_generated/env_cached.sh" "/usr/bin/python" "/opt/ros/kinetic/share/catkin/cmake/test/run_tests.py" "/home/callum/buggy_ws/build/test_results/robot_upstart/roslint-robot_upstart.xml" "--working-dir" "/home/callum/buggy_ws/build/robot_upstart-jade-devel" "--return-code" "/opt/ros/kinetic/share/roslint/cmake/../../../lib/roslint/test_wrapper /home/callum/buggy_ws/build/test_results/robot_upstart/roslint-robot_upstart.xml make roslint_robot_upstart")
add_test(_ctest_robot_upstart_nosetests_test "/home/callum/buggy_ws/build/catkin_generated/env_cached.sh" "/usr/bin/python" "/opt/ros/kinetic/share/catkin/cmake/test/run_tests.py" "/home/callum/buggy_ws/build/test_results/robot_upstart/nosetests-test.xml" "--return-code" "/usr/bin/cmake -E make_directory /home/callum/buggy_ws/build/test_results/robot_upstart" "/usr/bin/nosetests-2.7 -P --process-timeout=60 --where=/home/callum/buggy_ws/src/robot_upstart-jade-devel/test --with-xunit --xunit-file=/home/callum/buggy_ws/build/test_results/robot_upstart/nosetests-test.xml")
