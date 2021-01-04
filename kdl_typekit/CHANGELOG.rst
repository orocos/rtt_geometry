^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Changelog for package kdl_typekit
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

2.9.4 (2021-01-04)
------------------
* Merge pull request `#32 <https://github.com/orocos/rtt_geometry/issues/32>`_ from orocos/fix/kdl_typekit-writable-source
  Fix unit tests in kdl_typekit on Travis
* kdl_typekit: fix read-only filesystem error when running unit tests on Travis CI with non-writable source-space
* Merge pull request `#31 <https://github.com/orocos/rtt_geometry/issues/31>`_ from ahoarau/patch-1
  env-hooks: only install env-hook if BUILD_LUA_RTT is enabled
* add option that defaults on
* env-hooks: only install env-hook if BUILD_LUA_RTT is enabled
  Similar to https://github.com/orocos-toolchain/ocl/commit/eb4575516af295955f341097e62da92772ccc2f1
* Contributors: Antoine Hoarau, Johannes Meyer

2.9.3 (2019-06-03)
------------------
* Merge pull request `#30 <https://github.com/orocos/rtt_geometry/issues/30>`_ from achim-k/toolchain-2.9
  kdl_typekit: Use ownProperty() instead of add() to fix memory leak.
* Merge pull request `#29 <https://github.com/orocos/rtt_geometry/issues/29>`_ from orocos/travis-ros-industrial-ci
  Use ROS industrial_ci for Travis CI builds
* kdl_typekit: fixed corba unit test if no nameserver is running yet (e.g. on Travis)
* Contributors: Achim Krauch, Johannes Meyer

2.9.2 (2019-05-16)
------------------
* kdl_typekit: remove duplicate template instantiations and moved/removed include directives (fix `#27 <https://github.com/orocos/rtt_geometry/issues/27>`_)
* Contributors: Johannes Meyer

2.9.1 (2017-07-28)
------------------

2.9.0 (2017-05-05)
------------------
* Fixed extra semicolon warnings when compiling in pedantic mode
* Merge pull request `#24 <https://github.com/orocos/rtt_geometry/issues/24>`_ from meyerj/fix/eigen3-cmake into toolchain-2.9
* Use FindEigen3.cmake config shipped with Eigen starting from version 3.3
* kdl_typekit: fixed test compilation errors
* Refactored eigen_typekit and kdl_typekit to allow compilation in catkin devel-space
* kdl_typekit: add CArrayTypeInfo variants to the typekit to support fixed-size arrays
* Merged pull request `#17 <https://github.com/orocos/rtt_geometry/pull/17>`_ from kuka-isir/eigen-corba-support into indigo-devel
  Corba / MQueue support
* kdl_typekit: Add angle/axis constructor for Rotation
* Updated changelogs and bumped version number to 2.9.0
* Contributors: Antoine Hoarau, Johannes Meyer, Stephen Roderick

2.8.1 (2015-07-21)
------------------
* Merge pull request `#14 <https://github.com/orocos/rtt_geometry/issues/14>`_ from orocos/fix/extern_template_explicit_instantiation
  kdl_typekit: fix extern declare, explicit instantiate mechanism
* kdl_typekit: fix extern declare, explicit instantiate mechanism
  We forgot the explicit instantiation, also added the channelelement type
  Signed-off-by: Ruben Smits <ruben.smits@intermodalics.eu>
* kdl_typekit: Incomplete but working unittest for kdl typekit scripting
  Signed-off-by: Ruben Smits <ruben.smits@intermodalics.eu>
* kdl_typekit: added index operators for Vector, Wrench and Twist
  Signed-off-by: Ruben Smits <ruben.smits@intermodalics.eu>
* replace lua based corba typekit test with c++ based gtest
  Signed-off-by: Ruben Smits <ruben.smits@intermodalics.eu>
* Install typekit header additionally as Types.hpp to be consistent with orogen generated typekits

2.8.0 (2015-01-23)
------------------
 * Initial release
