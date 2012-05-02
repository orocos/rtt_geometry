local rttlib = require "rttlib"
local rtt = rtt
module("kdlutils")

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
