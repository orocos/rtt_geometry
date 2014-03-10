--
-- rttlua example: nice printing of variables
--

local utils = require "utils"
local rttlib = require "rttlib"
local tostring = tostring

local pad=8	-- total length to pad string
local fmt="%g"	-- printf like format specifier

module("kdlpp")

-- Convert number to string and pad with whitespace.
function padn(n) return utils.rpad((fmt):format(n), pad, ' ') end

-- KDL.Vector
function KDL_Vector_tostr(v)
   return ("%s\n%s\n%s"):format(padn(v.X), padn(v.Y), padn(v.Z))
end

-- KDL.Rotation
function KDL_Rotation_tostr(rot)
   return ("%s %s %s\n%s %s %s\n%s %s %s"):format(padn(rot.X_x), padn(rot.Y_x),padn(rot.Z_x),
						  padn(rot.X_y), padn(rot.Y_y),padn(rot.Z_y),
						  padn(rot.X_z), padn(rot.Y_z),padn(rot.Z_z))
end

-- KDL.Frame
function KDL_Frame_tostr(f)
   return (
[[%s %s %s %s
%s %s %s %s
%s %s %s %s
%s %s %s %s]]):format(padn(f.M.X_x), padn(f.M.Y_x),padn(f.M.Z_x), padn(f.p.X),
		      padn(f.M.X_y), padn(f.M.Y_y),padn(f.M.Z_y), padn(f.p.Y),
		      padn(f.M.X_z), padn(f.M.Y_z),padn(f.M.Z_z), padn(f.p.Z),
		      padn(0), padn(0), padn(0), padn(1))
end

rttlib.var_pp["KDL.Vector"] = KDL_Vector_tostr
rttlib.var_pp["KDL.Rotation"] = KDL_Rotation_tostr
rttlib.var_pp["KDL.Frame"] = KDL_Frame_tostr
