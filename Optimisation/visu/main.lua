------TOOLS

local clock = os.clock
function sleep(n)  -- seconds
   local t0 = clock()
   while clock() - t0 <= n do
   end
end

function love.quit()
	-- io.write("Error : Wrong file\n")
	love.event.quit()
end

function draw_elem()
    love.graphics.line(4500 / 20, w_height / 2 + 500 / 20, 5500 / 20, w_height / 2 + 500 / 20)
end
-------MAIN

function        love.load()
    love.window.setMode(1920, 1080, {resizable=false, vsync=false, minwidth=400, minheight=300})
    success = love.window.setFullscreen(true)
    w_widht, w_height = love.graphics.getDimensions()
    map = {}
    index = 1
    line = io.read("*line")
    line = io.read("*line")
    line = io.read("*line") -- we just pass the first three lines
    love.graphics.setPointSize(10)
    love.graphics.setLineStyle("smooth")
    love.graphics.setLineWidth(5)
end

function        love.update(dt)
    local splitter = 0
    local x
    local y
    while (line ~= "END MAP" and line ~= "END VISU" and line ~= nil) do
        if (line == "------") then
            line = io.read("*line")
            map[index] = "end car"
            index = index + 1
        end
        splitter = string.find(line , "||")
        --print(line)
        x = tonumber(string.sub(line, 1, splitter - 1)) / 10
        y = tonumber(string.sub(line, splitter + 2)) / 10
        y = 2 * w_height / 2 - y -- Symétrie VNER
        map[index] = {x / 2 , y / 2}
        line = io.read("*line")
        index = index + 1;
    end
    if (line == "END MAP") then
        map[index] = "end car"
    end
    if (line == "END VISU") then
        sleep(10)
        love.quit()
    end
    --if (line ~= nil) then io.write(line, "\n") end
    line = io.read("*line")
end

function        love.draw()
    local old = {0, 0}
    local bool = false
    local first = {0, 0}
    love.graphics.line(19000 / 20, 0, 19000 / 20, w_height)
    draw_elem()
    for i,v in ipairs(map) do
        --print (v)
        if (v ~= "end car") then
            --print(v[1], v[2], " and ", old[1], old[2])
            if (bool == true) then
                first = {v[1], v[2]}
            else
                test = {v[1], v[2], old[1], old[2]}
            end
            old = {v[1], v[2]}
            love.graphics.line(test)
            love.graphics.points(v)
            bool = false
        else
            test = {old[1], old[2], first[1], first[2]}
            love.graphics.line(test)
            bool = true
        end
    end -- map pleine
    --print("- - - - -")
    map = {}
    index = 1
    sleep(0.01)
end
