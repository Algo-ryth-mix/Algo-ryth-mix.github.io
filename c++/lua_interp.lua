--[[!
--!Test-Script to test the basic functionallity of the Engine within the lua-scripting environment
--!
--! Raphael Baier 2019 public-domain
]]

require("lualib.animator")

Script = engine.script:new {
	counter = 0,
}

function Script:animateCube()

	--declare lambda to move the transform by -x + 2
	local mover = function (x)
		self.transform.position = vec3:new(-x + 6,0,0)
	end

	--our animation main loop
	while true do
		-- move to the right with a speed of 0.5
		co_lerp(0,1,0.5,mover)
		--wait 0.2 seconds
		co_delay(0.2)
		--move back to the left with a speed of 0.2
		co_lerp(1,0,0.2,mover)
	end
end

function Script:init()

	-- get the transform
	self.transform = self.get_components("Transform")

	--reset the transform
	self.transform.position = vec3:new(0,0,0)

	-- install an animation
	AnimationManager.installAnimation(self,"animation",self.animateCube)
end

function Script:update()

	--Update all installed animations
	AnimationManager.updateAll(self)

end
