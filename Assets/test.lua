local starter = function ()
   local texture = GetTexture("/home/mohamedmedhat/StrawEngine/StrawEngine-Core/Assets/terrain.png");
   texture:Init()
   owner.position = X_Vector.new(0,0)
   owner:GetSpriteAddon().Texture = texture
   owner:GetSpriteAddon():SetTexCoords(32+16,0,16,16)
   
end

local updater = function()
   owner.rotation = owner.rotation + 0.1
end

local fixedupdater = function()
           
end


result = {}
result["OnCreate"] = starter
result["OnUpdate"] = updater
result["OnFixedUpdate"] = fixedupdater
return result
