result = {}
result["move"] = "MAMA"
local starter = function ()
end

local updater = function()
   result["move"] = true

end   

local fixedupdater = function()           

end


result["OnCreate"] = starter
result["OnUpdate"] = updater
result["OnFixedUpdate"] = fixedupdater
return result
 
