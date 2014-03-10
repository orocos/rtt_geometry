local rttlib = require "rttlib"
local rtt = rtt
module("kdlutils")

rtt.getTC():getPeer("Deployer"):import("kdl_typekit")

function rotx(r)
   f = rtt.Variable("KDL.Frame")
   f.M=rtt.provides("KDL"):provides("Rotation"):RotX(r)
   return f
end
function roty(r)
   f = rtt.Variable("KDL.Frame")
   f.M=rtt.provides("KDL"):provides("Rotation"):RotY(r)
   return f
end
function rotz(r)
   f = rtt.Variable("KDL.Frame")
   f.M=rtt.provides("KDL"):provides("Rotation"):RotZ(r)
   return f
end
function transl(x,y,z)
   f = rtt.Variable("KDL.Frame")
   f:fromtab{p={Y=y,X=x,Z=z}}
   return f
end

function quat(x,y,z,w)
   return rtt.provides("KDL"):provides("Rotation"):Quaternion(x,y,z,w)
end

function get_quat(rot)
   x = rtt.Variable("double")
   y = rtt.Variable("double")
   z = rtt.Variable("double")
   w = rtt.Variable("double")
   rtt.provides("KDL"):provides("Rotation"):GetQuaternion(rot,x,y,z,w)
   return x,y,z,w
end

function inv(f)
   return rtt.provides("KDL"):provides("Frame"):Inverse(f)
end
function diff(a,b)
   local f1=rtt.Variable("KDL.Frame")
   local f2=rtt.Variable("KDL.Frame")
   f1:assign(a)
   f2:assign(b)
   return rtt.provides("KDL"):provides("Frame"):diff(f1,f2,1.0)
end

function addDelta(f,d)
   return rtt.provides("KDL"):provides("Frame"):addDelta(f,d,1.0)
end

function diff_rot(a,b,dt)
   local r1=rtt.Variable("KDL.Rotation")
   local r2=rtt.Variable("KDL.Rotation")
   local delta_time = rtt.Variable("double")
   r1:assign(a)
   r2:assign(b)
   delta_time:assign(dt)
   return rtt.provides("KDL"):provides("Rotation"):diff(r1,r2,delta_time)
end

function add_delta_rot(r,v,dt)
   return rtt.provides("KDL"):provides("Rotation"):addDelta(r,v,dt)
end

