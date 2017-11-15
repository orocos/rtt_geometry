^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Changelog for package kdl_typekit
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

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
