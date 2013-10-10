function SetExpand(joint, expand)
	local attr = joint:GetAttribute()
	local prevState = attr.Expand
	joint:GetAttribute().Expand = expand
	local icon = joint:GetObject("image")
	if icon then
		local bitmap = nil
		if expand == true then
			bitmap = joint:GetAttribute().ExpandIcon
		elseif expand == false then
			bitmap = joint:GetAttribute().CollapseIcon
		end
		if bitmap then icon:SetBitmap(bitmap) end
		icon:SetObjPos(0,0,10,10)
	end
	if prevState ~= expand then joint:FireExtEvent("Triggered", expand) end
end

function SetIcons(joint, expandIcon, collapseIcon)
	if expandIcon then
		joint:GetAttribute().ExpandIcon = expandIcon
	end
	if collapseIcon then
		joint:GetAttribute().CollapseIcon = collapseIcon
	end
end

function IsExpand(joint)
	return joint:GetAttribute().Expand
end

function OnLButtonUp(joint, x, y)
	if joint:GetAttribute().ButtonDown == true then
		joint:GetAttribute().ButtonDown = false
		joint:SetExpand(not (joint:IsExpand()))
	end
end

function OnLButtonDown(joint, x, y)
	joint:GetAttribute().ButtonDown = true
end

function OnInitControl(joint)
	joint:SetExpand(joint:GetAttribute().Expand)
end