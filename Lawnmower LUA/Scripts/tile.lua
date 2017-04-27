position = {x, y}
dimensions = { 32,32 } -- size
type = name

function setPosition(x, y)
	position.x = x;
	position.y = y;
end

function getPosition()
	return position.x, position.y    
end

function changeType(inType)
	type = inType
ChangeTexture(type)  
end
