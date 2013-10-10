function GetDataCount(self)
	return self:GetAttribute().ScrollArea:GetRowCount()
end

function GetColumnCount(self)
	return self:GetAttribute().ScrollArea:GetColumnCount()
end

function GetFirstVisibleIndex(self)
	return self:GetAttribute().ScrollArea:GetFirstVisibleIndex()
end

function GetViewportSize(self)
	local l,t,r,b = self:GetAttribute().ScrollArea:GetObjPos()
	return r-l, b-t
end

function GetScrollSize(self)
	return self:GetAttribute().ScrollArea:GetScrollAreaSize()
end

function SetDataTable(self, dataTable)
	self:GetAttribute().ScrollArea:SetDataTable(dataTable)
	updateScrollRange(self)
	updateHeader(self)
end

function AppendItem(self, itemData)
	local rowCount = self:GetAttribute().ScrollArea:GetRowCount()
	local row = rowCount+1
	local column = 1
	self:GetAttribute().ScrollArea:SetItemDataAtIndex(itemData, row, column)
	updateScrollRange(self)
end

function SetDataModel(self, userdata, callbackTable)
	self:GetAttribute().ScrollArea:SetDataModel(userdata, callbackTable)
	updateScrollRange(self)
	self:GetAttribute().ScrollArea:UpdateItems()
	updateHeader(self)
end

function SetItemFactory(self, userdata, name, callbackTable)
	if self:GetAttribute().ScrollArea ~= nil then
		self:GetAttribute().ScrollArea:SetItemFactory(userdata, name, callbackTable)
		updateHeader(self)
	end
end

function PageUp(self)
	if self:GetAttribute().ScrollArea ~= nil then
		self:GetAttribute().ScrollArea:PageUp()
	end
end

function PageDown(self)
	if self:GetAttribute().ScrollArea ~= nil then
		self:GetAttribute().ScrollArea:PageDown()
	end
end

function SetScrollBarH(self, scrollObjH)
	local attr = self:GetAttribute()
	if scrollObjH == nil then
		attr.ScrollBarAttrs.HScrollBar = scrollObjH
		attr.ScrollBarAttrs.HsbVisible = false
		alignObjects(self)
		-- Todo: remove listeners
		return true
	end
	
	local expectedMethods = {"GetScrollPos",
							 "SetScrollPos",
							 "GetScrollRange",
							 "SetScrollRange"}
	local result = CheckMethodWithAlert(expectedMethods, scrollObjH)
	
	attr.ScrollBarAttrs.HScrollBar = scrollObjH
	attr.ScrollBarAttrs.HsbVisible = attr.ScrollBarAttrs.HsbVisible and true
	self:GetControlObject("listview.bkg"):AddChild(attr.ScrollBarAttrs.HScrollBar)
	
	-- attach listeners
	-- 两个AttachListener都是在scrollbar存在的前提下建立的，scrollbar为空时没有互相通知的必要。
	-- Todo, remove listener via cookie
	local onHSPosChange = function(self)
		local pos = self:GetScrollPos()
		attr.ScrollArea:SetScrollPosH(pos)
		if attr.HeaderAttrs.Header ~= nil then
			attr.HeaderAttrs.Header:SetScrollPos(pos)
		end
	end
	local cookie, ret = attr.ScrollBarAttrs.HScrollBar:AttachListener("OnScrollPosChange", true, onHSPosChange)
	if ret == true then
		attr.ScrollBarAttrs.CookieScrollAreaListenToScrollBarH = cookie
	end

	local onScrollAreaHPosChange = function (self)
		local pos = self:GetScrollPosH()
		attr.ScrollBarAttrs.HScrollBar:SetScrollPos(pos)
		end
	local cookie2, ret2 = attr.ScrollArea:AttachListener("OnScrollPosChange", true, onScrollAreaHPosChange)
	if ret2 == true then
		attr.ScrollBarAttrs.CookieScrollBarHListenToScrollArea = cookie2
	end
	alignObjects(self)
end

function SetScrollBarV(self, scrollObjV)
	local attr = self:GetAttribute()
	if scrollObjV == nil then
		attr.ScrollBarAttrs.VScrollBar = scrollObjV
		attr.ScrollBarAttrs.VsbVisible = false
		alignObjects(self)
		-- Todo: remove listeners
		return true
	end
	
	local expectedMethods = {"GetScrollPos",
							 "SetScrollPos",
							 "GetScrollRange",
							 "SetScrollRange"}
	local result = CheckMethodWithAlert(expectedMethods, scrollObjV, "Vertical scroll bar")
	
	attr.ScrollBarAttrs.VScrollBar = scrollObjV
	attr.ScrollBarAttrs.VsbVisible = attr.ScrollBarAttrs.VsbVisible and true
	self:GetControlObject("listview.bkg"):AddChild(attr.ScrollBarAttrs.VScrollBar)
	
	-- attach listeners
	-- 两个AttachListener都是在scrollbar存在的前提下建立的，scrollbar为空时没有互相通知的必要。
	-- Todo, remove listener via cookie
	local onScrollBarVPosChange = function(self)
		local pos = self:GetScrollPos()
		attr.ScrollArea:SetScrollPosV(math.floor(pos))
		end
	local cookie, ret = attr.ScrollBarAttrs.VScrollBar:AttachListener("OnScrollPosChange", true, onScrollBarVPosChange)
	if ret == true then
		attr.ScrollBarAttrs.CookieScrollAreaListenToScrollBar = cookie
	end

	local onScrollAreaVPosChange = function (self)
		local pos = self:GetScrollPosV()
		attr.ScrollBarAttrs.VScrollBar:SetScrollPos(pos)
		end
	local cookie2, ret2 = attr.ScrollArea:AttachListener("OnScrollPosChange", true, onScrollAreaVPosChange)
	if ret2 == true then
		attr.ScrollBarAttrs.CookieScrollBarListenToScrollArea = cookie2
	end
	alignObjects(self)
end

function SetHeader(self, headerObj)
	local attr = self:GetAttribute()
	if headerObj ==  nil then
		attr.HeaderAttrs.Header = nil
		attr.HeaderAttrs.Visible = false
		alignObjects(self)
		-- Todo: remove prev listeners
	end
	
	local expectedMethods = {"GetScrollPos",
							 "SetScrollPos",
							 "GetSectionWidthList",
							 "SetSectionWidthList"}
	local result = CheckMethodWithAlert(expectedMethods, headerObj, "ListView Header")

	attr.HeaderAttrs.Header = headerObj
	attr.HeaderAttrs.Visible = attr.HeaderAttrs.Visible and true
	self:GetControlObject("listview.bkg"):AddChild(attr.HeaderAttrs.Header)

	alignObjects(self)
	-- Todo: attach listeners
	-- 先不做交互
end

function OnInitControl(self)
	local attr = self:GetAttribute()
	local scrollArea = self:GetControlObject("listview.scrollarea")
	attr.ScrollArea = scrollArea
	if attr.ScrollArea ~= nil then 
		local function OnScrollAreaVPosChanged(saObj, eventName, oldPos, newPos)
			self:FireExtEvent("VerticalScrollPosChanged", oldPos, newPos)
		end
		attr.ScrollArea:AttachListener("VerticalScrollPosChanged", true, OnScrollAreaVPosChanged)
		
		local function OnScrollAreaHPosChanged(saObj, eventName, oldPos, newPos)
			self:FireExtEvent("HorizontalScrollPosChanged", oldPos, newPos)
		end
		attr.ScrollArea:AttachListener("HorizontalScrollPosChanged", true, OnScrollAreaHPosChanged)
		
		attr.ScrollArea:AttachListener("VisibleItemChanged", true, 
			function (saObj, eventName, newFirst, newLast)
				self:FireExtEvent("VisibleItemChanged", newFirst, newLast)
			end)
		attr.ScrollArea:AttachListener("DataChanged", true, 
			function(saObj, eventName)
				updateScrollRange(self)
				saObj:UpdateItems()
			end)
	end
	
	attr.ScrollBarAttrs = {}
	attr.ScrollBarAttrs.VsbVisible = false
	attr.ScrollBarAttrs.HsbVisible = false
	
	attr.HeaderAttrs = {}
	attr.HeaderAttrs.Visible = true
	attr.HeaderAttrs.Header = nil
	
	if attr.BackgroundTexture then
		local textureObj = self:GetControlObject("listview.bkg")
		if textureObj then
			textureObj:SetTextureID(attr.BackgroundTexture)
		end
	end

	local listViewId = self:GetID()
	if listViewId==nil then listViewId="" end
	-- Allow user to assign nil or specify another scrollbar later
	if attr.ScrollBarClassNameV then
		local objFactory = XLGetObject("Xunlei.UIEngine.ObjectFactory")
		local scrollObjV = objFactory:CreateUIObject(listViewId..".scrollbarV", attr.ScrollBarClassNameV)
		self:SetScrollBarV(scrollObjV)
	end
	
	if attr.ScrollBarClassNameH then
		local objFactory = XLGetObject("Xunlei.UIEngine.ObjectFactory")
		local scrollObjH = objFactory:CreateUIObject(listViewId..".scrollbarH", attr.ScrollBarClassNameH)
		self:SetScrollBarH(scrollObjH)
	end
	
	if attr.HeaderClassName then
		local objFactory = XLGetObject("Xunlei.UIEngine.ObjectFactory")
		local headerObj = objFactory:CreateUIObject(listViewId..".header", attr.HeaderClassName)
		self:SetHeader(headerObj)
	end
	
	if attr.PreloadDataCount then
		attr.ScrollArea:GetAttribute().PreloadDataCount = attr.PreloadDataCount
	end
end

function OnMouseWheel(self)
end

function updateScrollRange(self)
-- 先重新计算一下滚动区域是否需要滚动条
	self:GetAttribute().ScrollArea:UpdateScrollAreaSize()
	-- Todo: 是否支持自适应
	local l,t,r,b = self:GetObjPos()
	local attr = self:GetAttribute()
	local headerHeight = attr.HeaderHeight
	local scrollWidth, scrollHeight = attr.ScrollArea:GetScrollAreaSize()
	
	if attr.ScrollBarAttrs.VScrollBar ~= nil then
		setScrollBarVVisible(self, scrollHeight>(b-t-headerHeight))
		attr.ScrollBarAttrs.VScrollBar:SetScrollRange(0, 
			scrollHeight>(b-t-headerHeight) and scrollHeight-(b-t-headerHeight) or 0)
	end
	
	if attr.ScrollBarAttrs.VsbVisible then
		r = r - attr.ScrollBarSize
	end
	
	if attr.ScrollBarAttrs.HScrollBar ~= nil then
		setScrollBarHVisible(self, scrollWidth>(r-l))
		attr.ScrollBarAttrs.HScrollBar:SetScrollRange(0,
			scrollWidth>(r-l) and scrollWidth-(r-l) or 0)
	end
	alignObjects(self)
end

function updateHeader(self)
	local widthList = self:GetAttribute().ScrollArea:GetColumnWidthList()
	self:GetAttribute().HeaderAttrs.Header:SetSectionWidthList(widthList)
	local nameList = self:GetAttribute().ScrollArea:GetColumnNameList()
	self:GetAttribute().HeaderAttrs.Header:SetSectionNameList(nameList)
end

function alignObjects(self)
	local attr = self:GetAttribute()
	local l,t,r,b = self:GetObjPos()

	local vsbWidth = (attr.ScrollBarAttrs.VsbVisible and attr.ScrollBarSize or 0)
	local hsbHeight = (attr.ScrollBarAttrs.HsbVisible and attr.ScrollBarSize or 0)
	local headerHeight = (attr.HeaderAttrs.Visible and attr.HeaderHeight or 0)
	attr.ScrollArea:SetObjPos(0,headerHeight, r-l-vsbWidth, b-t-hsbHeight)
	if attr.ScrollBarAttrs.VScrollBar ~= nil then
		attr.ScrollBarAttrs.VScrollBar:SetObjPos(r-l-vsbWidth, headerHeight, r-l, b-t-hsbHeight)
	end
	if attr.ScrollBarAttrs.HScrollBar ~= nil then
		attr.ScrollBarAttrs.HScrollBar:SetObjPos(0, b-t-hsbHeight, r-l-vsbWidth, b-t)
	end

	if attr.HeaderAttrs.Header ~= nil then
		attr.HeaderAttrs.Header:SetObjPos(0,0, r-l-vsbWidth, headerHeight)
	end
end

function setScrollBarVVisible(self, visible)
	local attr = self:GetAttribute()
	if attr.ScrollBarAttrs.VScrollBar ~= nil then
		attr.ScrollBarAttrs.VScrollBar:SetVisible(visible)
		attr.ScrollBarAttrs.VsbVisible = visible
	end
end

function setScrollBarHVisible(self, visible)
	local attr = self:GetAttribute()
	if attr.ScrollBarAttrs.HScrollBar ~= nil then
		attr.ScrollBarAttrs.HScrollBar:SetVisible(visible)
		attr.ScrollBarAttrs.HsbVisible = visible
	end
end

function SetHeaderNameList(self, nameList)
	local scrollArea = self:GetControlObject("listview.scrollarea")
	if scrollArea then
		scrollArea:SetColumnNameList(nameList)
	end
	updateHeader(self)
end

-- long result,bool callNextEvent OnPosChange(UIObject sender,int oldLeft,int oldTop,int oldRight,int oldBottom,int newLeft,int newTop,int newRight,int newBottom)
function OnPosChange(self, oldLeft, oldTop, oldRight, oldBottom, newLeft, newTop, newRight, newBottom)
	local attr = self:GetAttribute()
	updateScrollRange(self)
	local scrollWidth, scrollHeight = attr.ScrollArea:GetScrollAreaSize()
	local l,t,r,b = self:GetAttribute().ScrollArea:GetObjPos()
	if scrollHeight > b-t then
		self:GetAttribute().ScrollBarAttrs.VScrollBar:SetScrollRange(0, scrollHeight-(b-t))
	end
	return 0, true
end