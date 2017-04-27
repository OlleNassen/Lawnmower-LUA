position = {x = 200, y = 50}
speed = 3

function setPosition(x, y)
	position.x = x
	position.y = y
end

--mx = map x max, my = map y max

function collision(mx, my)
	if position.x > mx then
        position.x = mx
	elseif position.x < 0 then
        position.x = 0
    end
	
    if position.y > my then
        position.y = my
	elseif position.y < 0 then
        position.y = 0
	end

end

function move(delta, verticalDir, horizontalDir)

    if verticalDir == 'left' then 
        position.x =  position.x - (delta * speed)
    elseif verticalDir == 'right' then
        position.x = position.x + (delta * speed)
    end

    if horizontalDir == 'up' then
        position.y = position.y - (delta * speed)
    elseif horizontalDir == 'down' then
        position.y = position.y + (delta * speed)
    end

end

function getPosition()
    return position.x, position.y	
end


