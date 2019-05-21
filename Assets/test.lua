local persist = 0
local test = 0
local move = false
local baby = function()
   print("OMG IT WORKS")
end

local starter = function ()
   local texture = GetTexture("/home/mohamedmedhat/StrawEngine/StrawEngine-Core/Assets/terrain.png");
   texture:init()
   owner:getSpriteAddon().Texture = texture
   owner:getSpriteAddon():setTexCoords(64 + 16,0,16,16)
   owner:getPhysicsAddon().gravity = 0
   owner:getPhysicsAddon().position = X_Vector.new(-300,0)
end

local updater = function()
   owner:getPhysicsAddon().veloctiy = X_Vector.new(0,0)
   if(getKey(68) == true) then
         owner:getPhysicsAddon().veloctiy = X_Vector.new(15,owner:getPhysicsAddon().veloctiy.y)
   end
   if(getKey(65)) then
      owner:getPhysicsAddon().veloctiy = X_Vector.new(-15,owner:getPhysicsAddon().veloctiy.y)
   end
   if(getKey(87)) then
      owner:getPhysicsAddon().veloctiy = X_Vector.new(owner:getPhysicsAddon().veloctiy.x,1 * 15)
   end
   if(getKey(83)) then
      owner :getPhysicsAddon().veloctiy = X_Vector.new(owner:getPhysicsAddon().veloctiy.x,-1 * 15)
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
 
