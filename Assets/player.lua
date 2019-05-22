local result  = {}
local counter = 0
local timer = 0
local timeinbetween = 0.2
local bullettexture = 0
local BulletAnimation = 0
local start = function()
   bullettexture = GetTexture("/home/mohamedmedhat/StrawEngine/StrawEngine-Core/Assets/laserBallNull.png")
   bullettexture:init()
   BulletAnimation = Animation.new()
   BulletAnimation:createAnimation(0,11)
   BulletAnimation.speed = 13
   owner:getPhysicsAddon().linearDamping = 10.0
end
local update = function(dt)
   --owner:getPhysicsAddon().velocity = X_Vector.new(0,0)
   timer = timer + dt
   if(window.getKey(68)) then
      owner:getPhysicsAddon().velocity = X_Vector.new(15,owner:getPhysicsAddon().velocity.y)
   end
   if(window.getKey(65)) then
      owner:getPhysicsAddon().velocity = X_Vector.new(-15,owner:getPhysicsAddon().velocity.y)
   end
   if(window.getKey(87)) then
      owner:getPhysicsAddon().velocity = X_Vector.new(owner:getPhysicsAddon().velocity.x,1 * 15)
   end
   if(window.getKey(83)) then
      owner:getPhysicsAddon().velocity = X_Vector.new(owner:getPhysicsAddon().velocity.x,-1 * 15)
   end
   if(window.getKey(32)) then
      if(timer > timeinbetween) then
      counter = counter + 1
      local Direction = (camera.screentoworld(X_Vector.new(window.mousexpos(),window.mouseypos())) - owner.position):normalize()
      print("TEST")
      local bullet = createEntity(owner.position + Direction * 100 , X_Vector.new(25,25),true)
      bullet:getPhysicsAddon().gravity = 0
      bullet:getSpriteAddon().Texture = bullettexture
      bullet.tag = "bullet"
      bullet:getPhysicsAddon().velocity = Direction * 100
      print(counter)
      bullet.scale = bullet.scale + 40
      bullet:createAnimatorAddon()
      bullet:getAnimatorAddon():setSpriteDimensions(X_Vector.new(32,32))
      bullet:getAnimatorAddon():setAnimation(BulletAnimation)
      timer = 0
      end
   end
end

local fixedupdate = function()   
end

result["OnCreate"] = start
result["OnUpdate"] = update
result["OnFixedUpdate"] = fixedupdate
return result
