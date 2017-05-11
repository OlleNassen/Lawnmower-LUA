position = {x = 200, y = 50}
speed = 4
score = 0

function setPosition(x, y)
	position.x = x
	position.y = y
end

--mx = map x max, my = map y max

function collision(mx, my)
	if position.x > mx -16 then
        position.x = mx - 16
	elseif position.x < 16 then
        position.x = 16
    end
	
    if position.y > my -16 then
        position.y = my - 16
	elseif position.y < 16 then
        position.y = 16
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


function collisionWithPlayer(playerPos, playerSize)
	collision = false
	intersection = 0, 0
	if position.x > playerPos.x  - playerSize / 2 
		and position.x < playerPos.x + playerSize / 2 
		and position.y > playerPos.y - playerSize / 2 
		and position.y < playerPos.y + playerSize / 2 then
		collision = true	

		if position.x > playerPos.x + playerSize / 2 then
			intersection.x = (playerPos.x + playerSize / 2) - (position.x - playerSize / 2)
		end

		if position.x > playerPos.x + playerSize / 2 then	
			intersection.x = (position.x + playerSize / 2) - (playerPos.x - playerSize / 2)
		end
		
		if position.y > playerPos.y + playerSize / 2 then
			intersection.y = (playerPos.y + playerSize / 2) - (position.y - playerSize / 2)
		end	

		if position.y < playerPos.y - playerSize / 2 then
			intersection.y = (position.y + playerSize / 2) - (playerPos.y - playerSize / 2)
		end	
	
		position.x = position.x + intersection.x
		position.y = position.y + intersection.y

		return true, intersection
	end

	return false, intersection
end


function collisionWithTile(tilePos, tileSize, type)
	collision = false
	intersection = 0, 0
	if position.x > tilePos.x  - tileSize / 2 
		and position.x < tilePos.x + tileSize / 2 
		and position.y > tilePos.y - tileSize / 2 
		and position.y < tilePos.y + tileSize / 2 then
		collision = true	
	end

	if collision == true then
		if type == 2 then
			position = 0, 0
			return false
		end
		if type == 1 then
			return false
		end
		if type == 0 then
			score = score + 1
			return true
		end
	end
	return false
end




