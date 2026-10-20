
local Prop = {}
function Prop.new(tex_path,width,height,name,width_render_scale,height_render_scale)
    local prop = {}
    prop[name].width = width
    prop[name].height = height
    prop[name].width_render_scale = width_render_scale
    prop[name].height_render_scale = height_render_scale
    return prop
end

function Prop.addPart(parent,tex_path,width,height,width_render_scale,height_render_scale)
    parent.part[name] = {}
    parent.part[name].tex_path = tex_path
    parent.part[name].width = width
    parent.part[name].height = height
    parent.part[name].width_render = width_render_scale
    parent.part[name].height_render = height_render_scale
end
print(CreatePropArray(32))
local TableProp = Prop3.new("res/Table03.png",28,54,"table",2,2)
_G.PropEntity = {}
_G.PropEntity["Table"] = ConvertToEntity(TableProp) --Despite this having the name Table in it this is a userdatum specifically a Entity (No there won't be metatables or metamethods as well those are not neccesary as this will not be used for anything other then Prop declaration)
print(AddPropToEntArray)
AddPropToE2ntArray(0,_G.PropEntity["Table"])
--[[
local Props = {}
Props.table.width = 28
Props.table.height = 54
Props.table.width_render_scale = 56
Props.table.height_render = 108
]]--

