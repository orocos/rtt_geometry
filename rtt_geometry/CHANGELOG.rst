^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Changelog for package rtt_geometry
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

2.8.1 (2015-07-21)
------------------
* Merge pull request `#14 <https://github.com/orocos/rtt_geometry/issues/14>`_ from orocos/fix/extern_template_explicit_instantiation
  kdl_typekit: fix extern declare, explicit instantiate mechanism
* Merge pull request `#13 <https://github.com/orocos/rtt_geometry/issues/13>`_ from orocos/introduce_index_operator_for_vector_wrench_twist
  kdl_typekit: added index operators for Vector, Wrench and Twist
* Merge remote-tracking branch 'origin/indigo-devel' into introduce_index_operator_for_vector_wrench_twist
* kdl_typekit: fix extern declare, explicit instantiate mechanism
  We forgot the explicit instantiation, also added the channelelement type
* kdl_typekit: Incomplete but working unittest for kdl typekit scripting
  Use indigo from now on.
* kdl_typekit: added index operators for Vector, Wrench and Twist
* replace lua based corba typekit test with c++ based gtest
* Install typekit header additionally as Types.hpp to be consistent with orogen generated typekits
* eigen_typekit: unified maintainer name in package.xml across orocos-toolchain and related packages

2.8.0 (2015-01-23)
------------------
 * Initial release
