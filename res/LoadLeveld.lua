function PopulateWallsFromWallTable()
for k,v in pairs(Wall) do
    --print(table.getn(Wall))
   -- print(k)
    Level.AddWallToArray(Wall[k].color.r,Wall[k].color.g,Wall[k].color.b,k,Wall[k])
   -- print(Wall[i].width)
end
end
function PopulatePropsFromPropsTable()
for k,v in pairs(MapProps) do
    --print(table.getn(Wall))
   -- print(k)
    Level.AddPropToArray(k,MapProps[k])
   -- print(Wall[i].width)
end
end

