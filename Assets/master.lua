local result  = {}
local player = 0
local test = 0
local bullets = {}
Texture = {}
local reflect = function(a,b)
   
   local middle = 2 * math.dot(a , b)
   local finalevector = (a) - ((b * middle)) 
   return finalevector
end

  
local start = function()
   player = createEntity(X_Vector.new(0,0),X_Vector.new(100,100),true)
   player:getPhysicsAddon().gravity = 0
   Texture = GetTexture("/home/mohamedmedhat/StrawEngine/StrawEngine-Core/Assets/terrain.png")
   Texture:init()
   player:getSpriteAddon().Texture = Texture
   player:getSpriteAddon():setTexCoords(64,0,16,16)
   player:createScriptAddon("/home/mohamedmedhat/StrawEngine/StrawEngine-Core/Assets/player.lua")
   player.tag = "Player"
   test  = createEntity(X_Vector.new(0,0),X_Vector.new(100,500),true)
   test:getPhysicsAddon().gravity = 0
   test:getSpriteAddon().Texture = Texture
   test:getSpriteAddon():setTexCoords(64,0,16,16)
   test:getPhysicsAddon():setBody(bodyType.staticBody)
   setContactListener(function(a,b,c)
	 if(b.tag == "bullet")then	    
	    local finalevector = reflect(b:getPhysicsAddon().velocity,c)
	    b:getPhysicsAddon().velocity = finalevector
	    if(a.tag == player) then
	       local finalevector2 = reflect(a:getPhysicsAddon().velocity,c)
	    a:getPhysicsAddon().velocity = finalevector2   * -10
	    end
	    print("B : Bullet" .. "A : " .. a.tag)
	 end

	 if(a.tag == "bullet")then	    
	    local finalevector = reflect(a:getPhysicsAddon().velocity,c)
	    a:getPhysicsAddon().velocity = finalevector
	    if(b.tag == player) then
	       local finalevector2 = reflect(b:getPhysicsAddon().velocity,c)
	       b:getPhysicsAddon().velocity = finalevector2  * -10
	    end
	 end

		      end
   );
end
local update = function(dt)


end
local fixedupdate = function()


end

result["OnCreate"] = start
result["OnUpdate"] = update
result["OnFixedUpdate"] = fixedupdate
return result
