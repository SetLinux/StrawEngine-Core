
local starter = function ()

end

local updater = function()
   owner.position = (owner.position - X_Vector.new(8,0))   
   owner.scale = (owner.scale + X_Vector.new(0.5,0.5))
end

local fixedupdater = function()
           
end


result = {}
result["OnCreate"] = starter
result["OnUpdate"] = updater
result["OnFixedUpdate"] = fixedupdater
return result
