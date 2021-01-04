^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Changelog for package eigen_typekit
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

2.9.4 (2021-01-04)
------------------
* Merge pull request `#26 <https://github.com/orocos/rtt_geometry/issues/26>`_ from ahoarau/fixed_size_vectors
  Add fixed size vectors
* addressing `#34 <https://github.com/orocos/rtt_geometry/issues/34>`_ v2 - returning temporaries
* fix last commit
* addressing `#34 <https://github.com/orocos/rtt_geometry/issues/34>`_
  https://github.com/orocos/rtt_geometry/issues/34
* remove unecessary function
* taking care of @meyerj comments
* fix fixed sized constructors
* remove matrix6
* rename vector index to vector size
* add fixed size matrices
  + Vector6d/Matrix6d
* add eigen_vector2/3/4
* Contributors: Antoine Hoarau, Johannes Meyer

2.9.3 (2019-06-03)
------------------

2.9.2 (2019-05-16)
------------------

2.9.1 (2017-07-28)
------------------
* eigen_typekit: only find_package(cmake_modules) if EIGEN3 was not found
  cmake_modules is provided by ROS indigo, but the Eigen module has been deprecated since
  ROS jade (see http://wiki.ros.org/jade/Migration#Eigen_CMake_Module_in_cmake_modules).
* Contributors: Johannes Meyer

2.9.0 (2017-05-05)
------------------
* Fixed extra semicolon warnings when compiling in pedantic mode
* Merge pull request `#24 <https://github.com/orocos/rtt_geometry/issues/24>`_ from meyerj/fix/eigen3-cmake into toolchain-2.9
* Use FindEigen3.cmake config shipped with Eigen starting from version 3.3
* Refactored eigen_typekit and kdl_typekit to allow compilation in catkin devel-space
* Merged pull request `#17 <https://github.com/orocos/rtt_geometry/pull/17>`_ from kuka-isir/eigen-corba-support into indigo-devel
  Corba / MQueue support
* Updated changelogs and bumped version number to 2.9.0
* Contributors: Antoine Hoarau, Johannes Meyer

2.8.1 (2015-07-21)
------------------
* eigen_typekit: unified maintainer name in package.xml across orocos-toolchain and related packages

2.8.0 (2015-01-23)
------------------
 * Initial release
