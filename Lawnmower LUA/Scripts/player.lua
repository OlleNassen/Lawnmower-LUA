position = {x = 200, y = 50}
speed = 3

function setPosition(x, y)
	position.x = x
	position.y = y
end

--mx = map x max, my = map y max

function collision(mx, my)
	if position.x > mx -32 then
        position.x = mx - 32
	elseif position.x < 0 then
        position.x = 0
    end
	
    if position.y > my -32 then
        position.y = my - 32
	elseif position.y < 0 then
        position.y = 0
	end

end

function move(delta, verticalDir, horizontalDir)

    if horizontalDir == 'left' then 
        position.x =  position.x - (delta * speed)
    elseif horizontalDir == 'right' then
        position.x = position.x + (delta * speed)
    end

    if verticalDir == 'up' then
        position.y = position.y - (delta * speed)
    elseif verticalDir == 'down' then
        position.y = position.y + (delta * speed)
    end

end

function getPosition()
    return position.x, position.y	
end


