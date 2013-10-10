-- event OnInitControl --
function OnInitScrollPanel(scrollpanel)
	local viewport = scrollpanel:GetAttribute().Viewport
	local hsb = scrollpanel:GetAttribute().HScrollBar
	local vsb = scrollpanel:GetAttribute().VScrollBar
	local sa = scrollpanel:GetAttribute().ScrollArea
	scrollpanel:SetLimitChild(true)
	alignObjects(viewport, sa, hsb, vsb)
	scrollpanel:GetAttribute().HScrollPos = 0
	scrollpanel:GetAttribute().VScrollPos = 0
end

-- event OnInitControl --
function OnInitScrollArea(sa)
	local scrollpanel = sa:GetFather()
	scrollpanel:GetAttribute().ScrollArea = sa
end

function OnMouseWheel(scrollpanel, x, y, distance)
	local vsb = scrollpanel:GetAttribute().VScrollBar
	vsb:SetScrollPos(vsb:GetScrollPos()-math.floor(distance/10), true)
	vsb:FireExtEvent("OnScrollPosChange", vsb:GetScrollPos())
end

-- event OnInitControl --
function OnInitViewport(viewport)
	local scrollpanel = viewport:GetFather()
	scrollpanel:GetAttribute().Viewport = viewport
end

-- event OnInitControl --
function OnInitHSB(hsb)
	local scrollpanel = hsb:GetFather()
	scrollpanel:GetAttribute().HScrollBar = hsb
end

-- event OnInitControl --
function OnInitVSB(vsb)
	local scrollpanel = vsb:GetFather()
	scrollpanel:GetAttribute().VScrollBar = vsb
end

-- method --
function SetHScrollBar(scrollpanel, hsb)
	if scrollpanel:GetAttribute().HScrollBar ~=  nil then
		scrollpanel:GetAttribute().HScrollBar:RemoveListener("OnScrollPosChange")
		scrollpanel:RemoveChild(scrollpanel:GetAttribute().HScrollBar)
	end
	scrollpanel:GetAttribute().HScrollBar = hsb
	scrollpanel:GetAttribute().HScrollBar:AttachListener("OnScrollPosChange", true, OnHScrollPosChange)
end

-- method --
function SetVScrollBar(scrollpanel, vsb)
	if scrollpanel:GetAttribute().VScrollBar ~=  nil then
		scrollpanel:GetAttribute().VScrollBar:RemoveListener("OnScrollPosChange")
		scrollpanel:RemoveChild(scrollpanel:GetAttribute().VScrollBar)
	end
	scrollpanel:GetAttribute().VScrollBar = vsb
	scrollpanel:GetAttribute().VScrollBar:AttachListener("OnScrollPosChange", true, OnVScrollPosChange)
end

-- method -- 
function SetInnerObject(scrollpanel, sa)
	if scrollpanel:GetAttribute().ScrollArea ~= nil and scrollpanel:GetAttribute().ScrollArea ~= sa then
		scrollpanel:RemoveChild(scrollpanel:GetAttribute().ScrollArea)
	end
	scrollpanel:GetAttribute().ScrollArea = sa
	local viewport = scrollpanel:GetAttribute().Viewport
	local hsb = scrollpanel:GetAttribute().HScrollBar
	local vsb = scrollpanel:GetAttribute().VScrollBar
	scrollpanel:GetAttribute().ScrollArea:AttachListener("OnPosChange", true, OnScrollAreaPosChange)
	scrollpanel:AddChild(sa)
end

-- event OnPosChange of scroll area --
function OnScrollAreaPosChange(sa, lo, to, ro, bo, ln, tn, rn, bn)
	local scrollpanel = sa:GetFather()
	if rn-ln==ro-lo and bn-tn==bo-to then 
		if lo~=ln or to~=tn or ro~=rn or bo~=bn then
			local viewportSize = scrollpanel:GetViewportSize()
			scrollpanel:FireExtEvent("VisibleRectChanged", ln,tn,viewportSize.width, viewportSize.height)
		end
		return 0, true
	end
	local viewport = scrollpanel:GetAttribute().Viewport
	local hsb = scrollpanel:GetAttribute().HScrollBar
	local vsb = scrollpanel:GetAttribute().VScrollBar
	alignObjects(viewport, sa, hsb, vsb)
	local vpos = vsb:GetScrollPos()
	local hpos = hsb:GetScrollPos()
	sa:SetObjPos2(0-hpos, 0-vpos, rn-ln, bn-tn)
	return 0, true
end

-- event OnPosChange -- 
function OnScrollPanelPosChange(scrollpanel)
	local viewport = scrollpanel:GetAttribute().Viewport
	local hsb = scrollpanel:GetAttribute().HScrollBar
	local vsb = scrollpanel:GetAttribute().VScrollBar
	local sa = scrollpanel:GetAttribute().ScrollArea
	alignObjects(viewport, sa, hsb, vsb)
end

-- event OnScrollPosChange --
function OnHScrollPosChange(hscrollbar)
	local pos = hscrollbar:GetScrollPos()
	local scrollpanel = hscrollbar:GetObject("father")
	setScrollAreaHPos(scrollpanel, pos)
	local oldPos = scrollpanel:GetAttribute().HScrollPos
	scrollpanel:GetAttribute().HScrollPos = pos
	scrollpanel:FireExtEvent("HorizontalScrollPosChanged", oldPos, pos)
end

-- event OnScrollPosChange -- 
function OnVScrollPosChange(vscrollbar)
	local pos = vscrollbar:GetScrollPos()
	local scrollpanel = vscrollbar:GetObject("father")
	setScrollAreaVPos(scrollpanel, pos)
	local oldPos = scrollpanel:GetAttribute().VScrollPos
	scrollpanel:GetAttribute().VScrollPos = pos
	scrollpanel:FireExtEvent("VerticalScrollPosChanged", oldPos, pos)
end

-- method GetViewportSize
function GetViewportSize(scrollpanel)
	local viewport = scrollpanel:GetAttribute().Viewport
	local l,t,r,b = viewport:GetObjPos()
	return {width=(r-l),height=b-t}
end

function alignObjects(viewport, sa, hs, vs)
	if viewport and sa and vs and hs then
		local lv, tv, rv, bv = viewport:GetObjPos()
		local lsa, tsa, rsa, bsa = sa:GetObjPos()
		local widthView = rv-lv; 
		local hv = bv-tv; 
		local wsa = rsa-lsa; 
		local hsa = bsa-tsa;
		if widthView < wsa then
			if 0-lsa>wsa-widthView then lsa=widthView-wsa end
			hs:SetVisible(true)
			hs:SetChildrenVisible(true)
			hs:SetScrollRange(0, wsa-widthView, true)
		else
			lsa=0
			hs:SetVisible(false)
			hs:SetScrollRange(0, 0)
			hs:SetChildrenVisible(false)
		end
		if hv < hsa then 
			if 0-tsa>hsa-hv then tsa=hv-hsa end
			vs:SetVisible(true)
			vs:SetChildrenVisible(true)
			vs:SetScrollRange(0, hsa-hv, true)
		else
			tsa=0
			vs:SetVisible(false)
			vs:SetScrollRange(0, 0)
			vs:SetChildrenVisible(false)
		end
		sa:SetObjPos2(lsa, tsa, wsa, hsa)
	end
end

function setScrollAreaHPos(scrollpanel, pos)
	local sa = scrollpanel:GetAttribute().ScrollArea
	if sa then
		local l,t,r,b = sa:GetObjPos()
		sa:SetObjPos(0-pos, t, (r-l)-pos, b)
	end
end

function setScrollAreaVPos(scrollpanel, pos)
	local sa = scrollpanel:GetAttribute().ScrollArea
	if sa then
		local l,t,r,b = sa:GetObjPos()
		sa:SetObjPos(l, 0-pos, r, (b-t)-pos)
	end
end