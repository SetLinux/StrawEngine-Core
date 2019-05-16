local persist = 0
local starter = function ()
   local texture = GetTexture("/home/mohamedmedhat/StrawEngine/StrawEngine-Core/Assets/terrain.png");
   texture:init()
   owner:getSpriteAddon().Texture = texture
   owner:getSpriteAddon():setTexCoords(32+16,0,16,16)
   owner:getPhysicsAddon().gravity = 0
   owner:getPhysicsAddon().position = X_Vector.new(0,0)
end

local updater = function()
   owner:getPhysicsAddon().veloctiy = X_Vector.new(0,0)
   if(getKey(68) == true) then
         owner:getPhysicsAddon().veloctiy = X_Vector.new(1 * 4,0)
   end
   if(getKey(65)) then
      owner:getPhysicsAddon().veloctiy = X_Vector.new(-1 * 4,0)
   end
end

local fixedupdater = function()
           
end


result = {}
result["OnCreate"] = starter
result["OnUpdate"] = updater
result["OnFixedUpdate"] = fixedupdater
result[13] = 12
return result
