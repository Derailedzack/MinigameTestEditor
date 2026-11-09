
--local Prop = {}
Props = {}
--Props.entity = {}
function Prop.new(tex_path,width,height,name,width_render_scale,height_render_scale)
local prop = {}
--prop[name] = {}
prop.name = name
prop.width = width
prop.height = height
prop.tex_path = tex_path
prop.width_render = width_render_scale
prop.height_render = height_render_scale
return prop
end
function Prop.init(max_props)
Prop.CreateArray(max_props)
Prop.CreateRegistryArray(max_props);
end
local TableProp = Prop.new("res/Table03.png",28,54,"table",28*2,54*2)
local StageTopProp = Prop.new("res/Stage_Top.png",48,19,"stage_top",48*2,19*2)

function Prop.register_all()
Prop.Register(TableProp,0)
Prop.Register(StageTopProp,1)
end
Prop.init(64)
Prop.register_all()




