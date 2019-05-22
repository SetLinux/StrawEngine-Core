local persist = 0
local test = 0
local baby = "MAMAN"
local move = false
local testentity = 0
result = {}
local starter = function ()
   local texture = GetTexture("/home/mohamedmedhat/StrawEngine/StrawEngine-Core/Assets/terrain.png");
   texture:init()
   owner:getSpriteAddon().Texture = texture
   owner:getSpriteAddon():setTexCoords(64 + 16,0,16,16)
   owner:getPhysicsAddon().gravity = 0
   owner:getPhysicsAddon().position = X_Vector.new(-300,0)
   testentity = createEntity(X_Vector.new(0,0))
   testentity:createScriptAddon("/home/mohamedmedhat/StrawEngine/StrawEngine-Core/Assets/stest.lua")
   baby = "MAGIRL"
end

local updater = function()
   print(testentity:getScriptAddon().returntable["move"])
   owner:getPhysicsAddon().veloctiy = X_Vector.new(0,0)
   if(window.getKey(68) == true) then
      owner:getPhysicsAddon().veloctiy = X_Vector.new(15,owner:getPhysicsAddon().veloctiy.y)      
   end
   if(window.getKey(65)) then
      owner:getPhysicsAddon().veloctiy = X_Vector.new(-15,owner:getPhysicsAddon().veloctiy.y)
   end
   if(window.getKey(87)) then
      owner:getPhysicsAddon().veloctiy = X_Vector.new(owner:getPhysicsAddon().veloctiy.x,1 * 15)
   end
   if(window.getKey(83)) then
      owner:getPhysicsAddon().veloctiy = X_Vector.new(owner:getPhysicsAddon().veloctiy.x,-1 * 15)
   end
   
end

local fixedupdater = function()
           
end


result["OnCreate"] = starter
result["OnUpdate"] = updater
result["OnFixedUpdate"] = fixedupdater
return result
 
