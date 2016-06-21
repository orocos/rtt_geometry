^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Changelog for package kdl_typekit
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Forthcoming
-----------
* kdl_typekit: test constructors in typekit_scripting_test
* kdl_typekit: remove unused Boost serialization methods for vectors
  Boost serialization already knows how to handle various container types
  (see http://www.boost.org/doc/libs/1_54_0/libs/serialization/doc/tutorial.html#stl).
* kdl_typekit: Add angle/axis constructor for Rotation
* Contributors: Johannes Meyer, Stephen Roderick

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
