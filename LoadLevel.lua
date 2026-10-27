for k,v in pairs(Level) do
    print("Level["..k .. "]")
end
--print(Level)
function PopulateWallsFromWallTable(wall)
for k,v in pairs(wall) do
    --print(table.getn(Wall))
   -- print(k)
    Level.AddWallToArray(wall[k].color.r,wall[k].color.g,wall[k].color.b,k,wall[k])
   -- print(Wall[i].width)
end
end
function PopulatePropsFromPropsTable(map_props)
    print("Add props!\n")
for k,v in pairs(map_props) do
    --print(table.getn(Wall))
   -- print(k)
    Level.AddPropToArray(k,map_props[k])
   -- print(Wall[i].width)
end
end

