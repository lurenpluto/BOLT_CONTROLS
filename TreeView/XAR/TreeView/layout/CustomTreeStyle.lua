function GetCustomStyle(tree)
	local style={}
	style.rad = {}
	style.GetChildrenPosList = 
		function (fsize, sizelist, fkey)
			local poslist = {}
			local left = 0
			local top = 0
			local maxWidth = 0
			for k,size in pairs(sizelist) do
				if maxWidth < size.width then maxWidth = size.width end
			end
			maxWidth = maxWidth+style.joint_size.width
			for k,size in pairs(sizelist) do
				left = maxWidth-size.width
				local pos = {left=left, top = top}
				poslist[k] = pos
				top = top + size.height+style.vertical_padding
			end
			return {left=maxWidth+style.vertical_padding, top=(top-style.vertical_padding)/2-fsize.height/2}, poslist
		end
	style.GetLinesAndJointPosList = 
		function (frect, rectlist, virtualRoot)
			local linePosList = {}
			local jointPosList = {}
			local mainHor = frect.left-style.knob_size
			local mainTop = nil
			local mainBottom = nil
			for k, rect in pairs(rectlist) do
				local left = rect.left - style.joint_node_padding - style.joint_size.width
				local top = math.floor(rect.top+rect.height/2-style.joint_size.height/2)
				jointPosList[k] = {left=left, top=top,width = style.joint_size.width, height = style.joint_size.height}
				local line = {}
				line.left= rect.left+rect.width
				line.right= frect.left-style.knob_size
				line.top=top+math.floor(style.joint_size.height/2)
				line.bottom = line.top
				linePosList[k] = line
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
				knob.left = mainHor
				knob.right = frect.left
				knob.top = math.floor(frect.top+frect.height/2)
				knob.bottom = knob.top
				linePosList["knob"] = knob
			end
			return linePosList, jointPosList
		end
	local attr = tree:GetAttribute()
	style.icon_size = {width=attr.icon_width, height =attr.icon_height}
	style.node_size = {width=attr.node_width, height = attr.node_height}
	style.vertical_padding = attr.vertical_padding
	style.horizontal_padding = attr.horizontal_padding
	style.joint_size = {width=attr.joint_width, height = attr.joint_height}
	style.joint_node_padding = attr.joint_node_padding and attr.joint_node_padding or 0
	style.knob_size = attr.knob_size
	return style
end