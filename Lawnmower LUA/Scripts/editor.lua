grid = {}
for x = 0, 20 do
    grid[x] = {}
    for y = 0, 25 do
        grid[x][y] = 0
    end
end

function setTile(x, y, type)
	grid[y][x] = type
end

function saveToFile()
	save(grid)
end