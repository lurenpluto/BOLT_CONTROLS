function RegisterGlobal()
	XLSetGlobal("GetTreeStyle", GetTreeStyle)
end

function GetTreeStyle(tree)
	local attr = tree:GetAttribute()
	local styleName = attr.style_name
	if styleName == "WindowsStyle" or styleName==nil then 
		local style=GetWindowsStyle()
		style.icon_size = {width=attr.icon_width, height =attr.icon_height}
		style.horizontal_indent = attr.horizontal_indent
		style.node_size = {width=attr.node_width, height = attr.node_height}
		style.vertical_padding = attr.vertical_padding
		style.joint_size = {width=attr.joint_width, height = attr.joint_height}
		return style
	end
	if styleName == "LeftMidStyle" then 
		local style=GetLeftMidFatherStyle()
		style.icon_size = {width=attr.icon_width, height =attr.icon_height}
		style.node_size = {width=attr.node_width, height = attr.node_height}
		style.vertical_padding = attr.vertical_padding
		style.horizontal_padding = attr.horizontal_padding
		style.joint_size = {width=attr.joint_width, height = attr.joint_height}
		style.joint_node_padding = attr.joint_node_padding and attr.joint_node_padding or 0
		style.knob_size = attr.knob_size
		return style
	end
	if styleName=="MidTopStyle" then
		local style = GetMidTopStyle()
		style.icon_size = {width=attr.icon_width, height =attr.icon_height}
		style.node_size = {width=attr.node_width, height = attr.node_height}
		style.vertical_padding = attr.vertical_padding
		style.horizontal_padding = attr.horizontal_padding
		style.joint_size = {width=attr.joint_width, height = attr.joint_height}
		style.joint_node_padding = attr.joint_node_padding and attr.joint_node_padding or 0
		style.knob_size = attr.knob_size
		return style
	end
	return nil
end

function GetMidTopStyle()
	local style={}
	-- in fatherobjsize, children sub tree layout size list
	-- out father obj pos, children sub tree layout pos list
	style.GetChildrenPosList = 
		function (fsize, sizelist)
			local poslist = {}
			local left = 0
			local top = fsize.height + style.vertical_padding
			local height = 0
			local width = 0
			for k,size in pairs(sizelist) do
				poslist[k] ={left=left, top=top}
				left = left + size.width + style.horizontal_padding
				width = width + size.width + style.horizontal_padding
			end
			width = width-style.horizontal_padding
			return {left=width/2-fsize.width/2, top=0}, poslist
		end
	style.GetLinesAndJointPosList = 
		function (frect, rectlist, virtualRoot)
			local linePosList = {}
			local jointPosList = {}
			local mainLeft = nil
			local mainRight = nil
			local mainVertical = nil
			for k, rect in pairs(rectlist) do
				local rectMid = rect.left+rect.width/2
				local left = rectMid-style.joint_size.width/2
				local top = rect.top-style.joint_size.height-style.joint_node_padding
				jointPosList[k] = {left=left, top=top,width = style.joint_size.width, height = style.joint_size.height}
				local line = {}
				line.left= rectMid
				line.right= rectMid
				line.top= frect.top+frect.height+style.knob_size
				line.bottom = rect.top
				linePosList[k] = line
				if not mainVertical then mainVertical = line.top end
				if not mainLeft or mainLeft>rectMid then mainLeft = rectMid end
				if not mainRight or mainRight<rectMid then mainRight = rectMid end
			end
			if virtualRoot then 
				linePosList = {}
			else
				local main = {}
				main.left = mainLeft
				main.right = mainRight
				main.top = mainVertical
				main.bottom = mainVertical
				linePosList["main"] = main
				local knob = {}
				knob.left = frect.left+frect.width/2
				knob.right = knob.left
				knob.top = frect.top+frect.height
				knob.bottom = knob.top + style.knob_size
				linePosList["knob"] = knob
			end
			return linePosList, jointPosList
		end
	return style
end

function GetLeftMidFatherStyle()
	local style={}
	-- in fatherobjsize, children sub tree layout size list
	-- out father obj pos, children sub tree layout pos list
	style.GetChildrenPosList = 
		function (fsize, sizelist)
			local poslist = {}
			local left = fsize.width + style.horizontal_padding
			local top = 0
			for k,size in pairs(sizelist) do
				poslist[k] ={left=left, top=top}
				top = top+size.height + style.vertical_padding
			end
			return {left=0, top=(top-style.vertical_padding)/2-fsize.height/2}, poslist
		end
	style.GetLinesAndJointPosList = 
		function (frect, rectlist, virtualRoot)
			local iconSize = style.icon_size and style.icon_size or {width=20, height = 20} -- todo default
			local linePosList = {}
			local jointPosList = {}
			local mainHor = nil
			local mainTop = nil
			local mainBottom = nil
			for k, rect in pairs(rectlist) do
				local left = rect.left - style.joint_node_padding - style.joint_size.width
				local top = math.floor(rect.top+rect.height/2-style.joint_size.height/2)
				jointPosList[k] = {left=left, top=top,width = style.joint_size.width, height = style.joint_size.height}
				local line = {}
				line.left= frect.left+frect.width + style.knob_size
				line.right=rect.left
				line.top=top+math.floor(style.joint_size.height/2)
				line.bottom = line.top
				linePosList[k] = line
				if not mainHor then mainHor = line.left end
				if not mainTop or mainTop>line.top then mainTop = line.top end
				if not mainBottom or mainBottom<line.bottom then mainBottom = line.bottom end
			end
			if virtualRoot then 
				linePosList = {}
			else
				local main = {}
				main.left = mainHor
				main.right = mainHor
				main.top = mainTop
				main.bottom = mainBottom
				linePosList["main"] = main
				local knob = {}
				knob.left = frect.left+frect.width
				knob.right = main.left
				knob.top = math.floor(frect.top+frect.height/2)
				knob.bottom = knob.top
				linePosList["knob"] = knob
			end
			return linePosList, jointPosList
		end
	return style
end

function GetWindowsStyle()
	local style={}
	-- in fatherobjsize, children sub tree layout size list
	-- out father obj pos, children sub tree layout pos list
	style.GetChildrenPosList = 
		function (fsize, sizelist)
			local poslist = {}
			local indent = style.horizontal_indent and style.horizontal_indent or 30-- todo Style attribute
			local left = indent
			local padding = style.vertical_padding and style.vertical_padding or 20
			local top = padding + fsize.height
			for k,v in pairs(sizelist) do
				poslist[k] = {left=left, top=top}
				top = top + sizelist[k].height+padding
			end
			if style.icon_size.width < style.joint_size.width then 
				left = (style.joint_size.width - style.icon_size.width )/2
			else left = 0 end
			return {left=left,top=0},poslist
		end
	style.GetLinesAndJointPosList = 
		function (frect, rectlist, virtualRoot)
			local iconSize = style.icon_size and style.icon_size or {width=20, height = 20} -- todo default
			local linePosList = {}
			local jointPosList = {}
			local bottom = frect.top+frect.height
			local jointLeft = iconSize.width>style.joint_size.width and (iconSize.width-style.joint_size.width)/2 or 0
			local mid = math.max(style.joint_size.width/2,iconSize.width/2)
			for k, rect in pairs(rectlist) do
				jointPosList[k]= {left=jointLeft, top = rect.top +rect.height/2-style.joint_size.height/2, width = style.joint_size.width, height = style.joint_size.height}
				if bottom < rect.top+math.floor(rect.height/2) then bottom = rect.top+math.floor(rect.height/2)  end
				local line={}
				line.left=mid
				line.right = rect.left
				line.top=math.floor(rect.top+rect.height/2)
				line.bottom = line.top
				linePosList[k] = line
			end
			if not virtualRoot then 
				linePosList["main_line"] = {left = mid, top = frect.top+frect.height, right = mid, bottom = bottom}
			end
			return linePosList, jointPosList
		end
	return style
end
